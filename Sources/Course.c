

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "../Headers/set.h"
#include "../Headers/list.h"
#include "../Headers/CourseManager.h"
#include "../Headers/Grade.h"
#include "../Headers/FriendRequest.h"
#include "../Headers/Friend.h"
#include "../Headers/Student.h"
#include "../Headers/mtm_ex3.h"
#include "../Headers/Course.h"

struct course_t{
  int id;
  int last_sem;
};

SetElement copyCourse(SetElement element){
  if (element == NULL) return NULL;
  Course old= (Course)element;
  Course new= createCourse(old->id, old->last_sem);
  if (new == NULL) return NULL;
  return new;
}

void freeCourse(SetElement element){
  if(!element)
    return;
  Course old= (Course)element;
  destroyCourse(old);
}
int cmpCourse(SetElement element1, SetElement element2){
  Course course1 = (Course)element1;
  Course course2 = (Course)element2;
  return course1->id-course2->id;
}

Course createCourse(int id, int last_sem) {
if(id < 0) return NULL;
  Course new = malloc(sizeof(*new));
  if (new == NULL) return NULL;
  new->id = id;
  new->last_sem=last_sem;
  return new;
}

void destroyCourse(Course course){
  free(course);
}


int courseGetCourseId(Course course){
  if (!course) return -1;
  return course->id;
}

CourseResult courseUpdateLastSem(Course course, int semester){
  if(!course)return COURSE_ILLEGAL_PARAM;
  course->last_sem=semester;
  return COURSE_OK;
}

int courseGetCourseLastSem(Course course){
  if (!course)return -1;
  return course->last_sem;
}
