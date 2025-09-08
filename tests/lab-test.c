#include <stdlib.h>
#include <stdio.h>
#include "harness/unity.h"
#include "../src/lab.h"


void setUp(void) {
  printf("Setting up tests...\n");
}

void tearDown(void) {
  printf("Tearing down tests...\n");
}

void test_func_list_create(void) {
  int num_1 = 5;
  int num_2 = 6;
  int num_3 = 4;
  List *list_1 = list_create(LIST_LINKED_SENTINEL);
  TEST_ASSERT_NOT_NULL(list_1);
  list_destroy(list_1, NULL);
}

void test_func_list_destroy(void) {
  char *myString = (char *)malloc(sizeof(char) * (15));
  List *list_1 = list_create(LIST_LINKED_SENTINEL);
  list_append(list_1,myString);
  FreeFunc func_1 = free;
  list_destroy(list_1, free); // Mainly test for bugs/crashes
  list_1=NULL;
  TEST_ASSERT_NULL(list_1);
}

void test_func_list_append(void) {
  int num_1 = 5;
  int num_2 = 6;
  int num_3 = 4;
  List *list_1 = list_create(LIST_LINKED_SENTINEL);
  list_append(list_1, &num_1);
  list_append(list_1, &num_2);
  list_append(list_1, &num_3);
  TEST_ASSERT_EQUAL_INT(3, list_size(list_1));
  list_destroy(list_1, NULL);
}

void test_func_list_insert(void) {
  int num_1 = 5;
  int num_2 = 6;
  int num_3 = 4;
  int num_4 = 11;
  int num_5 = 29;
  int num_6 = 29;
  List *list_1 = list_create(LIST_LINKED_SENTINEL);
  list_append(list_1, &num_1);
  list_append(list_1, &num_2);
  list_append(list_1, &num_3);
  list_append(list_1, &num_4);
  list_insert(list_1, 0, &num_5);
  list_insert(list_1, 3, &num_6);
  TEST_ASSERT_EQUAL_INT(6, list_size(list_1));
  list_destroy(list_1, NULL);
}

void test_func_list_remove(void) {
  int num_1 = 5;
  int num_2 = 6;
  int num_3 = 4;
  int num_4 = 11;
  int num_5 = 23;
  List *list_1 = list_create(LIST_LINKED_SENTINEL);
  list_append(list_1, &num_1);
  list_append(list_1, &num_2);
  list_append(list_1, &num_3);
  list_append(list_1, &num_4);
  list_append(list_1, &num_5);
  list_remove(list_1, 1);
  list_remove(list_1, 3);
  TEST_ASSERT_EQUAL_INT(3, list_size(list_1));
  list_destroy(list_1, NULL);
}

void test_func_list_get(void) {
  int num_1 = 5;
  int num_2 = 6;
  int num_3 = 21;
  int num_4 = 11;
  int num_5 = 45;
  List *list_1 = list_create(LIST_LINKED_SENTINEL);
  list_append(list_1, &num_1);
  list_append(list_1, &num_2);
  list_append(list_1, &num_3);
  list_append(list_1, &num_4);
  list_append(list_1, &num_5);  
  int *value_1 = list_get(list_1, 1);
  int *value_2 = list_get(list_1, 3);
  TEST_ASSERT_EQUAL_INT(6, *value_1);
  TEST_ASSERT_EQUAL_INT(11, *value_2);
  list_destroy(list_1, NULL);
}

void test_func_list_is_empty(void) {
  int num_1 = 5;
  int num_2 = 6;
  int num_3 = 21;
  int num_4 = 11;
  List *list_1 = list_create(LIST_LINKED_SENTINEL);
  TEST_ASSERT_TRUE(list_is_empty(list_1));
  list_append(list_1, &num_1);
  list_append(list_1, &num_2);
  list_append(list_1, &num_3);
  list_append(list_1, &num_4);
  TEST_ASSERT_FALSE(list_is_empty(list_1));
  list_destroy(list_1, NULL);
}

void test_func_list_create_invalid_list_type(void) {
  int num_1 = 5;
  int num_2 = 6;
  int num_3 = 21;
  int num_4 = 11;
  List *list_1 = list_create(-1);
  TEST_ASSERT_NULL(list_1);
}

void test_func_list_insert_out_of_bounds() {
  int num_1 = 5;
  int num_2 = 6;
  int num_3 = 4;
  int num_4 = 11;
  List *list_1 = list_create(LIST_LINKED_SENTINEL);
  list_append(list_1, &num_1);
  list_append(list_1, &num_2);
  list_append(list_1, &num_3);
  list_append(list_1, &num_4);
  bool isSuccess = list_insert(list_1, 11, &num_4);
  TEST_ASSERT_FALSE(isSuccess);
  list_destroy(list_1, NULL);
}

void test_func_list_remove_out_of_bounds() {
  int num_1 = 5;
  int num_2 = 6;
  int num_3 = 4;
  int num_4 = 11;
  List *list_1 = list_create(LIST_LINKED_SENTINEL);
  list_append(list_1, &num_1);
  list_append(list_1, &num_2);
  list_append(list_1, &num_3);
  list_append(list_1, &num_4);
  bool isSuccess = list_remove(list_1, 11);
  TEST_ASSERT_FALSE(isSuccess);
  list_destroy(list_1, NULL);
}

void test_func_list_get_out_of_bounds() {
  int num_1 = 5;
  int num_2 = 6;
  int num_3 = 4;
  int num_4 = 11;
  List *list_1 = list_create(LIST_LINKED_SENTINEL);
  list_append(list_1, &num_1);
  list_append(list_1, &num_2);
  list_append(list_1, &num_3);
  list_append(list_1, &num_4);
  bool isSuccess = list_get(list_1, 22);
  TEST_ASSERT_FALSE(isSuccess);
  list_destroy(list_1, NULL);
}

int main(void) {
  UNITY_BEGIN();
  RUN_TEST(test_func_list_create);
  RUN_TEST(test_func_list_destroy);
  RUN_TEST(test_func_list_append);
  RUN_TEST(test_func_list_insert);
  RUN_TEST(test_func_list_remove);
  RUN_TEST(test_func_list_get);
  RUN_TEST(test_func_list_is_empty);
  RUN_TEST(test_func_list_create_invalid_list_type);
  RUN_TEST(test_func_list_insert_out_of_bounds);
  RUN_TEST(test_func_list_remove_out_of_bounds);
  RUN_TEST(test_func_list_get_out_of_bounds);
  return UNITY_END();
}
