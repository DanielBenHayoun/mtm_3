

#include "../Course.h"
#include "../Headers/test_utilities.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool test_createCourse(){
  Course course=createCourse(1 ,3);
  ASSERT_TEST(course);
  ASSERT_TEST(createCourse(-5,4)==NULL);
  destroyCourse(course);
  return  true;
}

bool test_getCoursId(){
  Course course=createCourse(1 ,3);
  Course course1=createCourse(234122 ,5);
  ASSERT_TEST(courseGetCourseId(course)==1);
  ASSERT_TEST(courseGetCourseId(course1)==234122);
  destroyCourse(course);
  destroyCourse(course1);
  return true;
}


bool test_getCourseLastSem(){
    Course course=createCourse(1 ,3);
    Course course1=createCourse(234112 ,5);
    ASSERT_TEST(courseGetCourseLastSem(course)==3);
    ASSERT_TEST(courseGetCourseLastSem(course1)==5);
    destroyCourse(course);
    destroyCourse(course1);
  return true;
}

bool test_courseUpdateLastSem(){
  Course course=createCourse(1 ,3);
  ASSERT_TEST(courseUpdateLastSem(course,5)==COURSE_OK);
  ASSERT_TEST(courseUpdateLastSem(NULL,5)==COURSE_ILLEGAL_PARAM);
  destroyCourse(course);
  return true;
}



int main(){
  RUN_TEST(test_createCourse);
  RUN_TEST(test_getCoursId);
  RUN_TEST(test_getCourseLastSem);
  RUN_TEST(test_courseUpdateLastSem);

  return 0;
}
