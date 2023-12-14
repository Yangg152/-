#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include <string.h>

#define MAX_EXPR_LENGTH 500

static char buf[MAX_EXPR_LENGTH + 1] = {};
static char code_buf[MAX_EXPR_LENGTH + 128] = {};
static char *code_format =
    "#include <stdio.h>\n"
    "int main() { "
    "  unsigned result = %s; "
    "  printf(\"%%u\", result); "
    "  return 0; "
    "}";

uint32_t choose(uint32_t n) {
    return rand() % n;
}

void gen_num() {
    char num[16];
    sprintf(num, "%u", choose(1000));  // Generate a random number
    strncat(buf, num, MAX_EXPR_LENGTH - strlen(buf));
}

void gen_rand_op() {
    const char *ops = "+-*/";
    char op[3] = { ' ', ops[choose(strlen(ops))], ' ' };
    strncat(buf, op, MAX_EXPR_LENGTH - strlen(buf));
}

void gen(char c) {
    int len = strlen(buf);
    if (len < MAX_EXPR_LENGTH) {
        buf[len] = c;
        buf[len + 1] = '\0';
    }
}

static int num_open_parentheses = 0;

static void gen_rand_expr() {
    if (strlen(buf) + num_open_parentheses >= MAX_EXPR_LENGTH - 1) {
        return; // 减去1预留空间来添加结束符号'\0'
    }

    switch (choose(3)) {
    case 0:
        gen_num();
        break;
    case 1:
        if (num_open_parentheses < 3 && strlen(buf) + 2 < MAX_EXPR_LENGTH - 1) {
            gen('(');
            num_open_parentheses++;
            gen_rand_expr();
            if (strlen(buf) + num_open_parentheses < MAX_EXPR_LENGTH - 1) {
                gen(')');
                num_open_parentheses--;
            } else { // 如果没有足够的空间来安全地关闭括号，就不要添加它
                // 退回刚才添加的左括号
                buf[strlen(buf) - 1] = '\0';
                num_open_parentheses--;
            }
        } else {
            gen_rand_expr();  // 如果括号数量达到上限，生成一个不含括号的子表达式
        }
        break;
    default:
        gen_rand_expr();
        if (choose(100) < 30) {
            for (int i = 0; i < choose(4); i++) {
                gen(' ');
            }
        }
        gen_rand_op();
        if (choose(100) < 30) {
            for (int i = 0; i < choose(4); i++) {
                gen(' ');
            }
        }
        gen_rand_expr();
        break;
    }
}


int main(int argc, char *argv[]) {
    int seed = time(0);
    num_open_parentheses = 0;
    srand(seed);
    int loop = 1;
    if (argc > 1) {
        sscanf(argv[1], "%d", &loop);
    }
    int i;
    for (i = 0; i < loop; i++) {
        buf[0] = '\0';
        gen_rand_expr();

        sprintf(code_buf, code_format, buf);

        FILE *fp = fopen("/tmp/.code.c", "w");
        assert(fp != NULL);
        fputs(code_buf, fp);
        fclose(fp);

        int ret = system("gcc /tmp/.code.c -o /tmp/.expr");
        if (ret != 0) continue;

        fp = popen("/tmp/.expr", "r");
        assert(fp != NULL);

        int result;
        ret = fscanf(fp, "%d", &result);
        pclose(fp);

        if (ret != EOF) {
            // 检查是否除零
            if (strstr(buf, "/ 0") == NULL) {
                printf("%u %s\n", result, buf);
            }
        }
    }
    return 0;
}