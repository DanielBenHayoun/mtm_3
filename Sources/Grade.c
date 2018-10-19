//
// Created by daniel on 12/15/2017.
//

#include "../Headers/Grade.h"
#include "../Headers/list.h"
#include <stdlib.h>
#include <string.h>
#include <assert.h>


struct grade_t {
  int semester;
  int course_id;
  char *points;
  int grade;
};

///==================GENERIC FUNCTIONS=======================================

ListElement copyGrade(ListElement element){
  Grade old = (Grade)element;
  Grade new = createGrade(old->semester, old->course_id,old->points,old->grade);
  if (new == NULL) return NULL;
  return new;
}

void freeGrade(ListElement element){
  if(!element)
    return;
  Grade grade = (Grade)element;
  destroyGrade(grade);
}

///==========================================================================

///====================STATIC FUNCTIONS======================================
/**
 * the comparison function for sortListGrades function.
 */
static int sortGrades(ListElement element1,ListElement element2,ListSortKey value);

/**
 * the comparison function for sortListGradesMin function.
 */
static int sortGradesMin(ListElement element1,ListElement element2,ListSortKey value);

///==========================================================================


Grade createGrade (int semester, int course_id, char *points, int grade){
  if (points == NULL) return NULL;
  Grade new_grade = malloc(sizeof(*new_grade));
  if (new_grade == NULL) return NULL;
  new_grade->semester = semester;
  new_grade->course_id = course_id;
  new_grade->points = malloc(strlen(points)+1);
  if (new_grade->points == NULL){
    free(new_grade);
    return NULL;
  }
  strcpy(new_grade->points, points);
  new_grade->grade = grade;
  return new_grade;
}

void destroyGrade (Grade grade){
  if(!grade)
    return;
  free(grade->points);
  free(grade);
}


int gradeGetSemester(Grade grade){
  if(!grade)return -1;
  return grade->semester;
}

int gradeGetGrade(Grade grade){
  if(!grade)return -1;
  return grade->grade;
}
char* gradeGetCoursePoints(Grade grade){
  if(!grade)return NULL;
  return grade->points;
}

int gradeGetCourseId(Grade grade){
  if(!grade)return -1;
  return grade->course_id;
}

GradeResult gradeUpdateGrade(Grade grade, int new_grade){
  if (!grade)return GRADE_ILLEGAL_PARAM;
  grade->grade=new_grade;
  return GRADE_OK;
}

static int sortGrades( ListElement element1 , ListElement element2,
                       ListSortKey value){
  Grade grade1=(Grade)element1;
  Grade grade2=(Grade)element2;
  if(grade1->grade==grade2->grade ){
    if(grade1->semester==grade2->semester){
      return grade1->course_id-grade2->course_id;
    }
    return grade1->semester-grade2->semester;
  }
  return grade2->grade-grade1->grade;
}

void sortListGrades(List listOfGrades) {
  int key = 0;
  listSort(listOfGrades, sortGrades, &key);
}

static int sortGradesMin(ListElement element1 ,ListElement element2,
                         ListSortKey value){
  Grade grade1=(Grade)element1;
  Grade grade2=(Grade)element2;
  if (grade1->grade==grade2->grade){
    if (grade1->semester == grade2->semester){
      return grade1->course_id-grade2->course_id;
    }
    return grade1->semester-grade2->semester;
  }
  return grade1->grade-grade2->grade;
}

void sortListGradesMin(List listOfGrades){
  int key = 0;
  listSort(listOfGrades, sortGradesMin, &key);
}

