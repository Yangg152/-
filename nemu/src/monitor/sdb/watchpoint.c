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

#include "sdb.h"

#define NR_WP 32

typedef struct watchpoint {
  int NO;
  struct watchpoint *next;
  bool flag; 
  char expr[100];
  uint32_t new_value;
  uint32_t old_value;

} WP;

static WP wp_pool[NR_WP] = {};
static WP *head = NULL, *free_ = NULL;

void init_wp_pool() {
  int i;
  for (i = 0; i < NR_WP; i ++) {
    wp_pool[i].NO = i;
    wp_pool[i].next = (i == NR_WP - 1 ? NULL : &wp_pool[i + 1]);
  }

  head = NULL;
  free_ = wp_pool;
}

// 申请一个新的监视点
WP* new_wp(){
  for(WP* p = free_ ; p -> next != NULL ; p = p -> next){
      if( p -> flag == false){
          p -> flag = true;
          if(head == NULL){
              head = p;
          }
          return p;
      }
  }
  printf("No unuse point.\n");
  assert(0);
  return NULL;
}

// 释放监视点
void free_wp(WP *wp) {
    if (head == NULL) {
        printf("Watchpoint list is empty.\n");
        return;
    }

    if (head->NO == wp->NO) {
        // 要释放的是链表的头节点
        head->flag = false;
        head = NULL;
        printf("Free watchpoint success.\n");
        return;
    }

    // 遍历链表查找要释放的监视点
    for (WP* p = head; p->next != NULL; p = p->next) {
        if (p->next->NO == wp->NO) {
            // 找到了要释放的节点
            wp->flag = false;
            memset(wp->expr, 0, sizeof(wp->expr));  // 使用memset清空表达式字符串
            wp->new_value = 0;
            wp->old_value = 0;
            p->next = p->next->next;
            printf("Free watchpoint success.\n");
            return;
        }
    }

    // 如果循环结束仍未找到要释放的节点
    printf("Watchpoint not found in the list.\n");
}

void sdb_watchpoint_display(){
    bool flag = true;
    for(int i = 0 ; i < NR_WP ; i ++){
        if(wp_pool[i].flag){
            printf("Watchpoint.No: %d, expr = \"%s\", old_value = 0x%08x, new_value = 0x%08x\n",
                    wp_pool[i].NO, wp_pool[i].expr, wp_pool[i].old_value, wp_pool[i].new_value);
                flag = false;
        }
    }
    if(flag) printf("No watchpoint now.\n");
}

void delete_watchpoint(int no){
  for(int i = 0 ; i < NR_WP ; i ++)
    if(wp_pool[i].NO == no){
      free_wp(&wp_pool[i]);
      return ;
  }
}

void create_watchpoint(char* args){
  WP* p =  new_wp();
  strcpy(p -> expr, args);
  bool success = false;
  uint32_t tmp = expr(p -> expr,&success);
  if(success) p -> old_value = tmp;
  else printf("There was an issue with expr evaluation when creating a watchpoint\n");
  printf("Create watchpoint No.%d success.\n", p -> NO);
}

bool scan_all_watchpoint(){
  for(int i = 0 ; i < NR_WP; i ++){
    if(wp_pool[i].flag)
    {
        bool success = false;
        uint32_t tmp = expr(wp_pool[i].expr, &success);
        if(success){
            if(tmp != wp_pool[i].new_value)
            {
              wp_pool[i].new_value = wp_pool[i].old_value;
              wp_pool[i].new_value = tmp;
              return true;
            }
            else
              return false;
        }
        else{
            printf("expr error.\n");
            assert(0);
        }
    }
  }
  return false;
}



