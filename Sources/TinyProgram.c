//
// Created by Dina on 17-Dec-17.
//
#include "../Headers/Grade.h"
#include "../Headers/FriendRequest.h"
#include "../Headers/Friend.h"
#include "../Headers/Student.h"
#include "../Headers/CourseManager.h"
#include "../Headers/list.h"
#include "../Headers/set.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ASSERT_TEST(b) do { \
        if (!(b)) { \
                printf("\nAssertion failed"); \
                return false; \
        } \
} while (0)

/**
 * Macro used for running a test from the main function
 */
#define RUN_TEST(test) do { \
        printf("Running "#test"... "); \
        if (test()) { \
            printf("[OK]\n");\
        } else { \
        	printf("[Failed]\n"); \
        } \
} while(0)


bool studentAddTest(){
  CourseManager c;
  createSystem(&c);
  SysResult result;
  ASSERT_TEST(c);
  result=studentAdd(c, NULL , "svsvs", "vsvvs");
  ASSERT_TEST(result==SYS_NULL_ARGUMENT);
  result=studentAdd(c, "434", NULL, "fgdf");
  ASSERT_TEST(result == SYS_NULL_ARGUMENT);
  result = studentAdd(c, "3453", "sfsf", NULL);
  ASSERT_TEST(result == SYS_NULL_ARGUMENT);
  result = studentAdd(c,"-36337", "dfdf" ,"fefv");
  ASSERT_TEST(result == SYS_ILLEGAL_PAR);

  destroySys(c);
  return true;
}

int main() {
  RUN_TEST(studentAddTest);

  return 1;
}