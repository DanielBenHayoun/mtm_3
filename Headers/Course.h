//
// Created by daniel on 12/23/2017.
//

#ifndef MTM_EX3_COURSE_H
#define MTM_EX3_COURSE_H
#include "set.h"
typedef struct course_t *Course;


typedef enum {
  COURSE_OK,
  COURSE_MEM_PROBLEM,
  COURSE_ILLEGAL_PARAM
}CourseResult;


///=================GENERIC FUNCTIONS=========================================
SetElement copyCourse(SetElement element);

void freeCourse(SetElement element);

int cmpCourse(SetElement element1, SetElement element2);

///===========================================================================

/**
 * Creates a new course according to the given parameters. allocates new space.
 * to destroy a Course the function destroyCourse should be used.
 * @param id - given id
 * @param last_sem -given semester
 * @return returns the new Course created.
 *         if the creation failed returns NULL.
 */
Course createCourse(int id, int last_sem);

/**
 * deallocates an existing course. frees all the memory that was allocated
 * when creating the course.
 * @param course - target course to be deallocated
 */
void destroyCourse(Course course);

/**
 * returns the id of a given course
 * @param course - the course who's id is returned
 * @return -1 if the parameter course is NULL
 *        course's id otherwise
 */
int courseGetCourseId(Course course);

/**
 * Updates the semester of a given course according to the given semester
 * @param course - the course to be updated
 * @param semester - the new semester
 * @return COURSE_ILLEGAL_PARAM - if the parameter course is NULL
 *         COURSE_OK - otherwise
 */
CourseResult courseUpdateLastSem(Course course, int semester);

/**
 * returns the semester of a given course
 * @param course - the given course
 * @return -1 if the parameter course is NULL
 *          course's semester otherwise
 */
int courseGetCourseLastSem(Course course);


#endif //MTM_EX3_COURSE_H
