#include <stdio.h>
#include "tps_unit_test.h"
#include "linked-list.h"

TEST_INIT_GLOBAL

void test_create(void) {
  ll_list *list = ll_create();
  tps_assert(list != NULL);
  ll_free(list);
}
void test_append(void) {
  ll_list *list = ll_create();
  ll_append(list, 1);
  ll_append(list, 2);
  tps_assert(list != NULL);
  tps_assert(ll_get(list, 0) == 1);
  tps_assert(ll_get(list, 1) == 2);
  ll_free(list);
}

void test_append2(void) {
  ll_list *list = ll_create();
  for(int i = 0; i < 20; i++)
    ll_append(list, i);
  tps_assert(list != NULL);
  tps_assert(ll_get(list, 19) == 19);
  ll_free(list);
}

void test_malloc_error(void) {
  __remaining_alloc = 0;
  ll_list *list = ll_create();
  tps_assert(list == NULL);
  ll_free(list);
  __remaining_alloc = -1;
}

void test_size(void) {

  ll_list *list = ll_create();
  for(int i = 0; i < 20; i++)
    ll_append(list, i);

  tps_assert(ll_size(list) == 20);
  ll_free(list);
}

void test_size_big(void) {

  ll_list *list = ll_create();
  for(int i = 0; i < 100000; i++)
    ll_prepend(list, i);

  for(int i = 0; i < 100000; i++)
  {
    tps_assert(ll_size(list) == 100000);
  }
  ll_free(list);
}
void test_prepend(void) {

  ll_list *list = ll_create();
  for(int i = 0; i < 20; i++)
    ll_append(list, i);
  
  tps_assert(ll_get(list, 0) == 0);

  ll_prepend(list, 100);
  tps_assert(ll_get(list, 0) == 100);
  tps_assert(ll_get(list, 1) == 0);
  tps_assert(ll_size(list) == 21);
  ll_free(list);
}

void test_first_last(void) {

  ll_list *list = ll_create();
  for(int i = 0; i < 20; i++)
    ll_append(list, i);
  
  tps_assert(ll_first(list) == 0);
  tps_assert(ll_last(list) == 19);
  ll_free(list);
}

void test_pop_last(void) {

  ll_list *list = ll_create();
  for(int i = 0; i < 20; i++)
    ll_append(list, i);
  
  tps_assert(ll_size(list) == 20);
  tps_assert(ll_get(list, 19) == 19);

  ll_pop_last(list);

  tps_assert(ll_get(list, 18) == 18);
  tps_assert(ll_last(list) == 18);
  tps_assert(ll_size(list) == 19);
  ll_free(list);
}
void test_pop_first(void) {

  ll_list *list = ll_create();
  for(int i = 0; i < 20; i++)
    ll_append(list, i);
  
  tps_assert(ll_size(list) == 20);
  tps_assert(ll_get(list, 0) == 0);

  ll_pop_first(list);

  tps_assert(ll_get(list, 0) == 1);
  tps_assert(ll_size(list) == 19);
  ll_free(list);
}

void test_insert(void){

  ll_list *list = ll_create();
  for(int i = 0; i < 20; i++)
    ll_append(list, i);
  
  ll_insert(list,100, 10);

  tps_assert(ll_size(list) == 21);
  tps_assert(ll_get(list, 9) == 9);
  tps_assert(ll_get(list, 10) == 100);
  printf("test VALLEUR 11: %i\n",ll_get(list,11));
  tps_assert(ll_get(list, 11) == 10);
  ll_free(list);
}

void test_remove(void){

  ll_list *list = ll_create();
  for(int i = 0; i < 20; i++)
    ll_append(list, i);
  
  ll_remove(list,10);

  tps_assert(ll_size(list) == 19);
  tps_assert(ll_get(list, 9) == 9);
  tps_assert(ll_get(list, 10) == 11);
  ll_free(list);
}


int main(void)
{
  TEST(test_create);
  TEST(test_append);
  TEST(test_append2);
  TEST(test_malloc_error);
  TEST(test_size);
  TEST(test_prepend);
  TEST(test_first_last);
  TEST(test_pop_first);
  TEST(test_pop_last);
  TEST(test_size_big);
  TEST(test_insert);
  TEST(test_remove);
}
