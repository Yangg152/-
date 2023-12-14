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

enum {
  TK_NOTYPE = 256,  TK_NUM = 1, TK_EQ = 2, TK_NEG = 3,

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
  {"==", TK_EQ},        // equal
  {"[0-9]*", TK_NUM},   // number
  {"\\(", '('},         // (
  {"\\)", ')'},         // )

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
  char str[32];
} Token;

static Token tokens[128] __attribute__((used)) = {};
static int nr_token __attribute__((used))  = 0;

static bool make_token(char *e) {
  int position = 0;
  int i;
  regmatch_t pmatch;

  nr_token = 0;

  while (e[position] != '\0') {
    /* Try all rules one by one. */
    for (i = 0; i < NR_REGEX; i ++) {
      if (regexec(&re[i], e + position, 1, &pmatch, 0) == 0 && pmatch.rm_so == 0) {
        char *substr_start = e + position;
        int substr_len = pmatch.rm_eo;
        if (substr_len > 32)
        panic("The expression string exceeds the length");

        Log("match rules[%d] = \"%s\" at position %d with len %d: %.*s",
            i, rules[i].regex, position, substr_len, substr_len, substr_start);

        position += substr_len;

        /* TODO: Now a new token is recognized with rules[i]. Add codes
         * to record the token in the array `tokens'. For certain types
         * of tokens, some extra actions should be performed.
         */

        switch (rules[i].token_type) {
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
          case 1:
            tokens[nr_token].type = 1;
            strncpy(tokens[nr_token++].str, &e[position - substr_len], substr_len);
            break;
          case 2:
            tokens[nr_token].type = 2;
            strcpy(tokens[nr_token++].str, "==");
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

  //Handling negative sign situations
  for (int i = 0; i < nr_token; i++) {
    if (tokens[i].type == '-') {
      // 如果 '-' 是第一个 token 或者前一个 token 是运算符或左括号，则视为负号
      if (i == 0 || tokens[i - 1].type != 1) {
        tokens[i].type = TK_NEG; // 假设 TK_NEG 代表负号
      }
    }
  }

  return true;
}

bool check_parentheses(int p, int q)
{
  if (tokens[p].type != '(' || tokens[q].type != ')')
    return false;
  int l, r;
  l = p;
  r = q;
  while (l < q)
  {
    if(tokens[l].type == '(') {
      if(tokens[q].type == ')') {
        l++;
        r--;
        continue;
      } else {
        r--;
      }
    } else if (tokens[l].type == ')') {
      return false;
    } else {
      l++;
    }
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
  else if (tokens[p].type == 3) {
    return -eval(p + 1, q);
  }
  else {
    int op = -1;
    int deep = 0;
    int priority = 999;
    int temp_priority = 0;
    for(int i = p; i <= q; i++){
      if(tokens[i].type == '(') {
        deep++;
      } else if(tokens[i].type == ')') {
        deep--;
      } else if(deep == 0){  
        if(tokens[i].type == 2) {  // ==
          temp_priority = 1;
          if (priority > temp_priority) {
            priority = temp_priority;
            op = i;
          }
        } 
        if((tokens[i].type == '+' || tokens[i].type == '-')) {
          temp_priority = 2;
          if (priority > temp_priority) {
            priority = temp_priority;
            op = i;
          }
        }
        if((tokens[i].type == '*' || tokens[i].type == '/')) {
          temp_priority = 3;
          if (priority > temp_priority) {
            priority = temp_priority;
            op = i;
          }
        }
      }
    }
    if(op == -1 || deep != 0){
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
      case 2: 
        return val1 == val2;
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


