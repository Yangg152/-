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

#include <isa.h>

/* We use the POSIX regex functions to process regular expressions.
 * Type 'man regex' for more information about POSIX regex functions.
 */
#include <regex.h>
#include <memory/paddr.h>
#include "sdb.h"

bool outputflag = 0; //HEX flag

enum {
  TK_NOTYPE = 256,  TK_NUM = 1, TK_EQ = 2, TK_NEQ = 3, TK_AND =4, TK_OR = 5, TK_lessthan = 6, TK_bigerthan = 7,
  TK_NEG = 10, TK_Yingyong = 11, TK_HEX = 12, TK_REG = 13,

  /* TODO: Add more token types */

};

static struct rule {
  const char *regex;
  int token_type;
} rules[] = {

  /* TODO: Add more rules.
   * Pay attention to the precedence level of different rules.
   */

  {" +", TK_NOTYPE},    // spaces
  {"\\+", '+'},         // plus
  {"\\-", '-'},         // minus
  {"\\*", '*'},         // multiply
  {"\\/", '/'},         // divide
  {"0[xX][0-9a-fA-F]+", TK_HEX}, //HEX
  {"\\$(0|ra|sp|gp|tp|t[0-6]|s[0-9]|a[0-7])", TK_REG}, //reg
  {"[0-9]+", TK_NUM},   // number
  {"\\(", '('},         // (
  {"\\)", ')'},         // )
  {"==", TK_EQ},        // equal
  {"!=", TK_NEQ},        // not equal
  {"&&", TK_AND},        // &&
  {"\\|\\|", TK_OR},        // &&
  {"<=", TK_lessthan},        // less than
  {">=", TK_bigerthan},     // biger than
  {"<", '<'},        // <
  {">", '>'},        // >
};

#define NR_REGEX ARRLEN(rules)

static regex_t re[NR_REGEX] = {};

/* Rules are used for many times.
 * Therefore we compile them only once before any usage.
 */
void init_regex() {
  int i;
  char error_msg[128];
  int ret;

  for (i = 0; i < NR_REGEX; i ++) {
    ret = regcomp(&re[i], rules[i].regex, REG_EXTENDED);
    if (ret != 0) {
      regerror(ret, &re[i], error_msg, 128);
      panic("regex compilation failed: %s\n%s", error_msg, rules[i].regex);
    }
  }
}

typedef struct token {
  int type;
  char str[128];
} Token;

static Token tokens[1024] __attribute__((used)) = {};
static int nr_token __attribute__((used))  = 0;

static bool make_token(char *e) {
  memset(tokens, 0, sizeof(tokens));
  int position = 0;
  int i;
  regmatch_t pmatch;
  outputflag = false;

  nr_token = 0;

  while (e[position] != '\0') {
    /* Try all rules one by one. */
    for (i = 0; i < NR_REGEX; i ++) {
      if (regexec(&re[i], e + position, 1, &pmatch, 0) == 0 && pmatch.rm_so == 0) {
        //char *substr_start = e + position;
        int substr_len = pmatch.rm_eo;
        if (substr_len > 128)
        panic("The expression string exceeds the length");
        
        //Log("match rules[%d] = \"%s\" at position %d with len %d: %.*s",
        //   i, rules[i].regex, position, substr_len, substr_len, substr_start);

        position += substr_len;

        /* TODO: Now a new token is recognized with rules[i]. Add codes
         * to record the token in the array `tokens'. For certain types
         * of tokens, some extra actions should be performed.
         */

        switch (rules[i].token_type) {
          case 256:
            break;
          case '+':
            tokens[nr_token ++].type = '+';
            break;
          case '-':
            tokens[nr_token ++].type = '-';
            break;
          case '*':
            tokens[nr_token ++].type = '*';
            break;
          case '/':
            tokens[nr_token ++].type = '/';
            break;
          case '(':
            tokens[nr_token ++].type = '(';
            break;
          case ')':
            tokens[nr_token ++].type = ')';
            break;
          case '>':
            tokens[nr_token ++].type = '>';
            break;
          case '<':
            tokens[nr_token ++].type = '<';
            break;
          case 1:
            tokens[nr_token].type = 1;
            strncpy(tokens[nr_token++].str, &e[position - substr_len], substr_len);
            break;
          case 2:
            tokens[nr_token].type = 2;
            strcpy(tokens[nr_token++].str, "==");
            break;
          case 3:
            tokens[nr_token].type = 3;
            strcpy(tokens[nr_token++].str, "!=");
            break;
          case 4:
            tokens[nr_token].type = 4;
            strcpy(tokens[nr_token++].str, "&&");
            break;
          case 5:
            tokens[nr_token].type = 5;
            strcpy(tokens[nr_token++].str, "||");
            break;
          case 6:
            tokens[nr_token].type = 6;
            strcpy(tokens[nr_token++].str, "<=");
            break;
          case 7:
            tokens[nr_token].type = 7;
            strcpy(tokens[nr_token++].str, ">=");
            break;
          case 12:
            tokens[nr_token].type = 12;
            strncpy(tokens[nr_token++].str, &e[position - substr_len], substr_len);
            break;            
          case 13:
            tokens[nr_token].type = 13;
            strncpy(tokens[nr_token++].str, &e[position - substr_len], substr_len);
            break; 

          default: 
            printf("\"%s\" and No rules is com.\n", rules[i].regex);
            break;
        }
        break;
      }
    }

    if (i == NR_REGEX) {
      printf("no match at position %d\n%s\n%*.s^\n", position, e, position, "");
      return false;
    }
  }

  // Handling negative sign situations
  for (int i = 0; i < nr_token; i++) {
    if (tokens[i].type == '-') {
      // 如果 '-' 是第一个 token 或者前一个 token 是运算符或左括号，则视为负号
      if (i == 0 || (tokens[i - 1].type != 1)) {
        if (tokens[i - 1].type != ')')
        tokens[i].type = TK_NEG; // 假设 TK_NEG 代表负号
      }
    }
  }
  // *
  for (i = 0; i < nr_token; i ++) {
    if (tokens[i].type == '*' && (i == 0 || tokens[i - 1].type != 1 ) ) {
      if (tokens[i - 1].type != ')')
      outputflag = true;
      tokens[i].type = TK_Yingyong;
    }
  }
  //HEX
  for(int i = 0 ; i < nr_token ; i ++) {
    if(tokens[i].type == 12) {
      outputflag = true;
      uint32_t value = strtoul(tokens[i].str, NULL, 16);
      // 处理 0 的特殊情况
      if (value == 0) {
        strcpy(tokens[i].str, "0");
      } else {
        // 反转转换逻辑
        char tempStr[32];
        int index = 0;

        // 逐个字符转换
        while (value > 0) {
            int digit = value % 10;
            tempStr[index++] = '0' + digit;
            value /= 10;
        }
        tempStr[index] = '\0';

        // 反转字符串以获得正确的顺序
        int strLen = strlen(tempStr);
        for (int j = 0; j < strLen / 2; j++) {
            char temp = tempStr[j];
            tempStr[j] = tempStr[strLen - j - 1];
            tempStr[strLen - j - 1] = temp;
        }

        // 将转换后的字符串复制回 tokens[i].str
        strcpy(tokens[i].str, tempStr);
      }
    }
  }
  //reg
  for(int i = 0 ; i < nr_token ; i ++) {
    if(tokens[i].type == 13) {
      outputflag = true;
      if (tokens[i].str[0] == '$' && tokens[i].str[1] != '0') {
        memmove(tokens[i].str, tokens[i].str + 1, strlen(tokens[i].str));
      }
      bool success = false;
      uint32_t value = isa_reg_str2val(tokens[i].str, &success);
      if(success) {
        // 处理 0 的特殊情况
        if (value == 0) {
          strcpy(tokens[i].str, "0");
        } else {
          // 反转转换逻辑
          char tempStr[32];
          int index = 0;

          // 逐个字符转换
          while (value > 0) {
              int digit = value % 10;
              tempStr[index++] = '0' + digit;
              value /= 10;
          }
          tempStr[index] = '\0';

          // 反转字符串以获得正确的顺序
          int strLen = strlen(tempStr);
          for (int j = 0; j < strLen / 2; j++) {
              char temp = tempStr[j];
              tempStr[j] = tempStr[strLen - j - 1];
              tempStr[strLen - j - 1] = temp;
          }
          // 将转换后的字符串复制回 tokens[i].str
          strcpy(tokens[i].str, tempStr);
        }
      }
    }
  }

  return true;
}

bool check_parentheses(int p, int q)
{
  if (tokens[p].type != '(' || tokens[q].type != ')')
    return false;
  int balance = 0;
  for (int i = p+1; i <= q-1; i++) {
    if (tokens[i].type == '(') {
      balance++; // 遇到左括号，增加计数
    } else if (tokens[i].type == ')') {
      balance--; // 遇到右括号，减少计数
      if (balance < 0) {
        return false; // 如果右括号比左括号多，说明没有匹配的左括号
      }
    }
  }
  if(balance != 0) {
    return false;
  }
  return true;
}

//Calculate the value of an expression
uint32_t eval(int p, int q) {
  if (p > q) {
    /* Bad expression */
    printf("There is an issue with the calculation expression");
    return 0;
  }
  else if (p == q) {
    /* Single token.
      * For now this token should be a number.
      * Return the value of the number.
      */
    return atoi(tokens[p].str);
  }
  else if (check_parentheses(p, q) == true) {
    /* The expression is surrounded by a matched pair of parentheses.
      * If that is the case, just throw away the parentheses.
      */
    return eval(p + 1, q - 1);
  }

  else if (tokens[p].type == TK_Yingyong) {
    paddr_t value = eval(p + 1, q);
    //paddr_t address; 
    uint32_t result = paddr_read(value,4);
    return result;
  }
  else if (tokens[p].type == TK_NEG) {
    return -eval(p + 1, q);
  }
  else {
    int op = -1;
    int deep = 0;
    int priority = -1;
    int temp_priority = 999;
    for(int i = p; i <= q; i++){
      if(tokens[i].type == '(') {
        deep++;
      } else if(tokens[i].type == ')') {
        deep--;
      } else if(deep == 0){  
        if((tokens[i].type == '*' || tokens[i].type == '/')) {
          temp_priority = 1;
          if (priority <= temp_priority) {
            priority = temp_priority;
            op = i;
          }
        }
        if((tokens[i].type == '+' || tokens[i].type == '-')) {
          temp_priority = 2;
          if (priority <= temp_priority) {
            priority = temp_priority;
            op = i;
          }
        }
        if(tokens[i].type == '<' || tokens[i].type == '>' || tokens[i].type == 6 || tokens[i].type == 7) { // <, >, <=, >=
          temp_priority = 3;
          if (priority <= temp_priority) {
            priority = temp_priority;
            op = i;
          }
        }  
        if(tokens[i].type == 2 || tokens[i].type == 3) {  // == !=
          temp_priority = 4;
          if (priority <= temp_priority) {
            priority = temp_priority;
            op = i;
          }
        }   
        if(tokens[i].type == 4) {  // &&
          temp_priority = 5;
          if (priority <= temp_priority) {
            priority = temp_priority;
            op = i;
          }
        }  
        if(tokens[i].type == 5) {  // ||
          temp_priority = 6;
          if (priority <= temp_priority) {
            priority = temp_priority;
            op = i;
          }
        }        
      }
    }
    if(op == -1 || deep != 0){
      printf("%d  %d",p,q);
      printf("There is an issue with the calculation expression");
      return 0;
    }
    int op_type = tokens[op].type;

    uint32_t val1 = eval(p, op - 1);
    uint32_t val2 = eval(op + 1, q);

    switch (op_type) {
      case '+': 
        return val1 + val2;
      case '-': 
        return val1 - val2;
      case '*': 
        return val1 * val2;
      case '/': 
        if(val2 == 0) {
          printf("The divisor cannot be 0");
          return 0;
        }
        return val1 / val2;
      case '>': 
        return val1 > val2;
      case '<': 
        return val1 < val2;                
      case 2: 
        return val1 == val2;
      case 3: 
        return val1 != val2;
      case 4: 
        return val1 && val2;
      case 5: 
        return val1 || val2;
      case 6: 
        return val1 <= val2;
      case 7: 
        return val1 >= val2;        
      default: 
        panic("No this type");
    }
  }
}

word_t expr(char *e, bool *success) {
  if (!make_token(e)) {
    *success = false;
    return 0;
  }

  word_t result = eval(0, nr_token-1);
  *success = true;

  return result;
}

void test_expr() {

  FILE *input_file = fopen("/home/yang/Desktop/workspace/ysys-study/nemu/tools/gen-expr/build/input.txt", "r");
    if (!input_file) {
        panic("Failed to open input file.\n");
    }

    // 读取每一行
    char line[1024];
    while (fgets(line, sizeof(line), input_file) != NULL) {
        // 解析每行
        char expression[1024] =" ";
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
}

