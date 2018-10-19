//
// Created by Dina on 08-Jan-18.
//

#include <stdio.h>
#include <string.h>
#include "../Headers/set.h"
#include "../Headers/list.h"
#include "../Headers/Grade.h"



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


bool test_createGrade(){
  Grade grade = createGrade(3, 4, "1.5", 90);
  ASSERT_TEST(grade != NULL);
  destroyGrade(grade);
  Grade grade1 = createGrade(3,5, NULL, 43);
  ASSERT_TEST(grade1==NULL);
  return true;
}

bool test_gradeGetSemester(){
  Grade grade = createGrade(3, 4, "1.5", 90);
  int sem=gradeGetSemester(grade);
  ASSERT_TEST(sem == 3);
  sem = gradeGetSemester(NULL);
  ASSERT_TEST(sem == -1);
  destroyGrade(grade);
  return true;
}
bool test_gradeGetGrade(){
  Grade grade = createGrade(3, 4, "1.5", 90);
  int grade1=gradeGetGrade(grade);
  ASSERT_TEST(grade1 == 90);
  grade1 = gradeGetGrade(NULL);
  ASSERT_TEST(grade1 == -1);
  destroyGrade(grade);
  return true;
}

bool test_gradeGetCoursePoints(){
  Grade grade = createGrade(3, 4, "1.5", 90);
  char *points = gradeGetCoursePoints(grade);
  ASSERT_TEST(strcmp(points, "1.5") == 0);
  points = gradeGetCoursePoints(NULL);
  ASSERT_TEST(points == NULL);
  destroyGrade(grade);
  return true;
}

bool test_gradeGetCourseId(){
  Grade grade = createGrade(3, 4, "1.5", 90);
  int course_id=gradeGetCourseId(grade);
  ASSERT_TEST(course_id == 4);
  course_id = gradeGetCourseId(NULL);
  ASSERT_TEST(course_id == -1);
  destroyGrade(grade);
  return true;
}

bool test_gradeUpdateGrade(){
  Grade grade = createGrade(3, 4, "1.5", 90);
  GradeResult result = gradeUpdateGrade(grade, 100);
  ASSERT_TEST(result == GRADE_OK);
  result = gradeUpdateGrade(NULL, 80 );
  ASSERT_TEST( result == GRADE_ILLEGAL_PARAM);
  destroyGrade(grade);
  return true;
}

bool test_sortListGrades(){
  List list = listCreate(copyGrade, freeGrade);
  Grade grade1 = createGrade(3, 4, "1.5", 10);
  Grade grade2 = createGrade(3, 4, "1.5", 20);
  Grade grade3 = createGrade(3, 4, "1.5", 30);
  listInsertLast(list, grade1);
  listInsertLast(list, grade2);
  listInsertLast(list, grade3);
  sortListGrades(list);
  ASSERT_TEST( gradeGetGrade(listGetFirst(list)) == 30);
  ASSERT_TEST( gradeGetGrade(listGetNext(list)) == 20);
  ASSERT_TEST( gradeGetGrade(listGetNext(list)) == 10);
  destroyGrade(grade1);
  destroyGrade(grade2);
  destroyGrade(grade3);
  listDestroy(list);
  return true;
}

bool test_sortListGradesMin(){
  List list = listCreate(copyGrade, freeGrade);
  Grade grade1 = createGrade(3, 4, "1.5", 10);
  Grade grade2 = createGrade(3, 4, "1.5", 20);
  Grade grade3 = createGrade(3, 4, "1.5", 30);
  listInsertLast(list, grade3);
  listInsertLast(list, grade2);
  listInsertLast(list, grade1);
  sortListGradesMin(list);
  ASSERT_TEST( gradeGetGrade(listGetFirst(list)) == 10);
  ASSERT_TEST( gradeGetGrade(listGetNext(list)) == 20);
  ASSERT_TEST( gradeGetGrade(listGetNext(list)) == 30);
  destroyGrade(grade1);
  destroyGrade(grade2);
  destroyGrade(grade3);
  listDestroy(list);
  return true;
}

int main(){
  RUN_TEST(test_createGrade);
  RUN_TEST(test_gradeGetSemester);
  RUN_TEST(test_gradeGetGrade);
  RUN_TEST(test_gradeGetCoursePoints);
  RUN_TEST(test_gradeGetCourseId);
  RUN_TEST(test_gradeUpdateGrade);
  RUN_TEST(test_sortListGrades);
  RUN_TEST(test_sortListGradesMin);
  return 0;
}