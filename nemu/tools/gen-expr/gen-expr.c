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
    sprintf(num, "%u", choose(100));  // Generate a random number
    strncat(buf, num, MAX_EXPR_LENGTH - strlen(buf));
}

void gen_rand_op() {
    const char *ops = "+-*/";
    int len = strlen(buf);
    
    if (len == 0 || strchr("+-*/(", buf[len - 1]) != NULL) {
        // 如果buf为空或最后一个字符是运算符或左括号，则不添加新的运算符
        return;
    }

    char op[3] = {' ', ops[choose(strlen(ops))], ' '};
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
    if (strlen(buf) >= MAX_EXPR_LENGTH - 10) {
        return;
    }

    switch (choose(3)) {
        case 0:
            gen_num();
            break;
        case 1:
            // 增加条件来限制递归深度
            if (num_open_parentheses < 2 && strlen(buf) + 2 < MAX_EXPR_LENGTH - 1) {
                gen('(');
                num_open_parentheses++;
                gen_rand_expr();
                if (strlen(buf) + num_open_parentheses < MAX_EXPR_LENGTH - 1) {
                    gen(')');
                    num_open_parentheses--;
                } else {
                    buf[strlen(buf) - 1] = '\0'; // 移除未匹配的左括号
                    num_open_parentheses--;
                }
            } else {
                gen_rand_expr();  // 避免过深递归
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
    int desired_output_count = 10; // 默认输出10条
    if (argc > 1) {
        sscanf(argv[1], "%d", &desired_output_count);
    }

    int output_count = 0;
    while (output_count < desired_output_count) {
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

        unsigned result;
        ret = fscanf(fp, "%u", &result);
        pclose(fp);

        if (ret != EOF && strstr(buf, "/ 0") == NULL) {
            unsigned threshold = 1000000; // 设置阈值
            if (result < threshold) {
                printf("%u %s\n", result, buf);
                output_count++; // 只有有效结果才增加输出计数
            }
        }
    }
    return 0;
}