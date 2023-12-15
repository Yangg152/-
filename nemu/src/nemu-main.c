/***************************************************************************************
* Copyright (c) 2014-2022 Zihao Yu, Nanjing University
*
* NEMU is licensed under Mulan PSL v2.
* You can use this software according to the terms and conditions of the Mulan PSL v2.
* You may obtain a copy of Mulan PSL v2 at:
*          http://license.coscl.org.cn/MulanPSL2
*
* THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
* EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
* MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
*
* See the Mulan PSL v2 for more details.
***************************************************************************************/

#include <common.h>

void init_monitor(int, char *[]);
void am_init_monitor();
void engine_start();
int is_exit_status_bad();
word_t expr(char *e, bool *success);

int main(int argc, char *argv[]) {
  /* Initialize the monitor. */
#ifdef CONFIG_TARGET_AM
  am_init_monitor();
#else
  init_monitor(argc, argv);
#endif

  FILE *input_file = fopen("/home/yang/Desktop/workspace/ysys-study/nemu/tools/gen-expr/build/input.txt", "r");
    if (!input_file) {
        panic("Failed to open input file.\n");
    }

    // 读取每一行
    char line[1024];
    while (fgets(line, sizeof(line), input_file) != NULL) {
        // 解析每行
        char expression[1024];
        if (sscanf(line, "%*u %[^\n]", expression) != 1) {
            fprintf(stderr, "Invalid input format: %s", line);
            continue;
        }

        printf("success");
        printf("Read expression: %s\n", expression);
        // 调用 expr 函数进行表达式求值
        bool success = false;
        word_t result = expr(expression, &success);

        //检查结果
        if (success) {
            printf("Expression result: %u\n", result);
        } else {
            printf("Expression parsing failed: %s\n", expression);
        }
    }

    // 关闭文件
    fclose(input_file);

  /* Start engine. */
  engine_start();

  return is_exit_status_bad();
}
