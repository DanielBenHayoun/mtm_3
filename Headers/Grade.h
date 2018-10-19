//
// Created by Dina on 16-Dec-17.
//

#ifndef EX3_GRADE_H
#define EX3_GRADE_H

#include "list.h"

typedef struct grade_t *Grade;

typedef enum {
  GRADE_OK,
  GRADE_MEM_PROBLEM,
  GRADE_ILLEGAL_PARAM
}GradeResult;


///=================GENERIC FUNCTIONS==========================================
ListElement copyGrade(ListElement element);

void freeGrade(ListElement element);

///===========================================================================

/**
 * Creates a new grade according to the given parameters. allocates new space.
 * to destroy a grade the function destroyGrade should be used.
 * @param semester - given semsester
 * @param course_id - given course id
 * @param points - given points
 * @param grade - given grade
 * @return returns the new grade created.
 *         if the creation failed returns NULL.
 */
Grade createGrade(int semester,  int course_id, char *points, int grade);

/**
 * deallocates an existing grade. frees all the memory that was allocated
 * when creating the grade.
 * @param grade - target grade to be deallocated
 */
void destroyGrade (Grade grade);

/**
 * returns the id of a given grade
 * @param grade - the grade who's id is returned
 * @return -1 if the parameter grade is NULL
 *        grade's id otherwise
 */
int gradeGetCourseId(Grade grade);

/**
 * returns the grade of a given Grade
 * @param grade - the Grade who's grade is returned
 * @return -1 if the parameter grade is NULL
 *        grade's grade otherwise
 */
int gradeGetGrade(Grade grade);

/**
 * returns the pointer to the given grade's points.
 * @param grade - given grade
 * @return NULL if the parameter grade is NULL
 *         the pointer to the given grade's points otherwise.
 */
char* gradeGetCoursePoints(Grade grade);

/**
 * returns the semester of a given grade
 * @param grade - the grade who's semester is returned
 * @return -1 if the parameter grade is NULL
 *        grade's semester otherwise
 */
int gradeGetSemester(Grade grade);

/**
 * updates a given Grade with a new grade
 * @param grade - the Grade to be updated
 * @param new_grade - the new grade
 * @return GRADE_ILLEGAL_PARAM - if the parameter grade is NULL
 *         GRADE_OK - otherwise
 */
GradeResult gradeUpdateGrade(Grade grade, int new_grade);

/**
 * sorts a list of grades in high to low order
 * @param listOfGrades - the list of grades to be sorted
 */
void sortListGrades(List listOfGrades) ;

/**
 * sorts a list of grades in low to high order
 * @param listOfGrades - the list of grades to be sorted
 */
void sortListGradesMin(List listOfGrades);



#endif //EX3_GRADE_H
