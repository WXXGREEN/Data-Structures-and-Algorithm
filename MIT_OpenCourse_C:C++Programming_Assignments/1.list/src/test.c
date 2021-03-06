#include "list.h"
#include <stdio.h>

int sq(int x) { return x * x; }

int plus(int x, int y) { return x + y; }

int main(void) {
  int N = 5;
  List list = empty_list();

  for (int i = 0; i < N; ++i) {
    list_append(&list, i);
  }
  list_insert_before(&list, -1, 1);
  list_print(list);
  list_delete(&list, 3);
  list_print(list);
  list_apply(&list, sq);
  list_print(list);
  int res = list_reduce(&list, plus);
  printf("plus result:%d\n", res);
  list_print(list);
  list_clear(&list);
  return 0;
}
