//
// Created by daniel on 12/11/2017.
//

#ifndef MTM_EX3_COURSE_MANAGER_H
#define MTM_EX3_COURSE_MANAGER_H

#include "Student.h"
#include "mtm_ex3.h"
#include "cmdTypdefs.h"


typedef struct course_manager_t *CourseManager;


typedef enum {
  SYS_OUT_OF_MEMORY,
  SYS_INVALID_COMMAND_LINE_PARAMETERS,
  SYS_CANNOT_OPEN_FILE,
  SYS_NULL_PARAMETER,
  SYS_INVALID_PARAMETER,
  SYS_NOBODY_LOGGED_IN,
  SYS_ALREADY_LOGGED_IN,
  SYS_STUDENT_NOT_EXISTS,
  SYS_STUDENT_ALREADY_EXISTS,
  SYS_NOT_FRIENDS,
  SYS_ALREADY_FRIEND,
  SYS_NOT_REQUESTED,
  SYS_ALREADY_REQUESTED,
  SYS_COURSE_DOES_NOT_EXIST,
  SYS_OK
} SysResult;



///=================HELPER FUNCTIONS=======================================

/**
 * puts in result the online student
 * @param system
 * @param result - recieves the online student found in the system
 * @return SYS_STUDENT_NOT_EXISTS - there is nobody who is logged
 *         SYS_OK - otherwise
 */
SysResult getOnlineStudent(CourseManager system , Student *result);

/**
 * a helper functions that "makes" two student friends. it adds each other
 * to each other friends
 * @param system
 * @param stu1 - first student
 * @param stu2 - second student
 * @return SYS_NOT_REQUESTED - if there wasn't a friend request of the first
 *         student in the friend requests of the second student
 *         SYS_OK - otherwise
 */
SysResult handleAccept(CourseManager system , Student stu1 , Student stu2);

/**
 * checks if the points are legal according to the definition in the exercise
 * @param points
 * @return true if points are legal
 *         false if points are unlegal
 */
bool checkPoints(char* points);

/**
 * returns the set of the students
 * @param system
 * @return NULL if the parameter is NULL
 *         the set of the students otherwise
 */
Set getSetStudents(CourseManager system);

///========================================================================


/**this function allocate new space ,and create a new Set of Students
 * return value:
 * the new course system is saved in the given pointer to the function
 * SYS_MEM_PROBLEM in case of memory problem
  note: if the function ends unsuccesfully the given pointer doesn`t change
 */
SysResult createSystem(CourseManager *new);


/**this function destroy the whole system
 * deallocate memory as well
 *
 */
SysResult destroySys(CourseManager system);

/**in this functions we create a demo of a student and
 * passing a copy of him to the Set.
 * after we do it we destroy the demo using "destroyStudent"
 * from Student.h
 */
SysResult studentAdd(CourseManager sys, int student_id  ,FirstName ,LastName);


/** using "destroyStudent" from Student.h
 * to remove the student from the entire system
 *
 */
SysResult studentRemove(CourseManager system, StudentId id_c);

/**
 * logs a student with the given id into the system
 * @param system
 * @param id - the given id
 * @return SYS_ALREADY_LOGGED_IN - if there is another student online
 *         SYS_STUDENT_NOT_EXISTS - if there isn't a student with the given
 *         id in the system
 *         SYS_OK - otherwise
 */
SysResult studentLogin(CourseManager system, int id);

/**
 * logs out the student that is online
 * @param system
 * @return SYS_NOBODY_LOGGED_IN - there is nobody who is logged
 *         SYS_OK - otherwise
 */
SysResult studentLogout(CourseManager system);

/**
 * Adds a friend request of the online student to the student with the other id
 * @param system
 * @param other_id_c - the id of whe student to whom the request is added
 * @return SYS_NOBODY_LOGGED_IN - there is nobody who is logged
 *         SYS_STUDENT_NOT_EXISTS - there isn't a student with the other id
 *         in the system
 *         SYS_ALREADY_FRIEND - the two students are already friends
 *         SYS_ALREADY_REQUESTED - the online student already sent a friend
 *         request to the other student
 *         SYS_OUT_OF_MEMORY -couldn't add the requets because of a memory error
 *         SYS_OK - otherwise
 *
 */
SysResult friendRequest(CourseManager system, int other_id_c) ;

/**
 * the online student either accepts or rejects a friend requets according to
 * the action
 * @param system
 * @param other_id_c - id of a student who's request is handled
 * @param action - accept/reject
 * @return SYS_NOBODY_LOGGED_IN - there is nobody who is logged
 *         SYS_STUDENT_NOT_EXISTS - there isn't a student with the other id
 *         in the system
 *         SYS_ALREADY_FRIEND - the two students are already friends
 *         SYS_NOT_REQUESTED - there isn't a request of a student with the
 *         other id
 *         SYS_INVALID_PARAMETER - the action is illegal
 *         SYS_OK - otherwise
 */
SysResult handleRequest(CourseManager system,StudentId other_id_c,char *action);

/**
 * removes a friend with the other id of the online student's friends
 * @param system
 * @param id_c - the id of the student who is unfriended
 * @return SYS_NOBODY_LOGGED_IN - there is nobody who is logged
 *         SYS_STUDENT_NOT_EXISTS - there isn't a student with the other id
 *         SYS_NOT_FRIENDS - the two students aren't frineds
 *         SYS_OK - otherwise
 */
SysResult studentUnfriend(CourseManager system, int id_c);

/**
 * adds a grade to the grade sheet of a the online student
 * @param sys
 * @param sem - semester of the grade
 * @param id - course id
 * @param p - points of the course
 * @param g - grade
 * @return SYS_NOBODY_LOGGED_IN - there is nobody who is logged
 *         SYS_INVALID_PARAMETER - the parameters aren't legal
 *         SYS_OK- otherwise
 */
SysResult gradeSheetAdd(CourseManager sys, int sem, int id, char *p, int g);

/**
 * removes a grade of the grade sheet of a the online student
 * @param sys
 * @param sem - semester of the grade
 * @param c_id - course id
 * @return SYS_NOBODY_LOGGED_IN - there is nobody who is logged
 *         SYS_COURSE_DOES_NOT_EXIST - there is no such grade with the given
 *         course id
 *         SYS_OK - otherwise
 */
SysResult gradeSheetRemove(CourseManager sys, int sem, int c_id);

/**
 * Updates a grade in the grade sheet of the online student
 * @param sys
 * @param c_id - course id
 * @param n_g - the new grade
 * @return SYS_NOBODY_LOGGED_IN - there is nobody who is logged
 *         SYS_COURSE_DOES_NOT_EXIST - there is no such grade with the given
 *         course id
 *         SYS_INVALID_PARAMETER - the new grade is not between 0-100
 *         SYS_OK - otherwise
 */
SysResult gradeSheetUpdate(CourseManager sys, int c_id, int n_g);

/**
 * prints a full report of the online students grade sheet
 * @param system
 * @param output - File descriptor for the output channel
 * @return SYS_NOBODY_LOGGED_IN - there is nobody who is logged
 *         SYS_OK - otherwise
 */
SysResult reportFull(CourseManager system, FILE *output);

/**
 * prints a clean report of the online students grade sheet
 * @param system
 * @param output - File descriptor for the output channel
 * @return SYS_NOBODY_LOGGED_IN - there is nobody who is logged
 *         SYS_OK - otherwise
 */
SysResult reportClean(CourseManager system , FILE* output);

/**
 * prints the best grades of the online student according to the given amount
 * @param system
 * @param output- File descriptor for the output channel
 * @param amount - amount of grades to print
 * @return SYS_NOBODY_LOGGED_IN - there is nobody who is logged
 *         SYS_INVALID_PARAMETER - if the amount is lower or equal to 0
 *         SYS_OK - otherwise
 */
SysResult reportBest(CourseManager system , FILE* output , int amount);

/**
 * prints the worst grades of the online student according to the given amount
 * @param system
 * @param output- File descriptor for the output channel
 * @param amount - amount of grades to print
 * @return SYS_NOBODY_LOGGED_IN - there is nobody who is logged
 *         SYS_INVALID_PARAMETER - if the amount is lower or equal to 0
 *         SYS_OK - otherwise
 */
SysResult reportWorst(CourseManager system , FILE* output , int amount);

/**
 * prints the names of the students who are got the highest grades in the
 * given course
 * @param sys
 * @param output- File descriptor for the output channel
 * @param c_id - given course id
 * @param amount - amount of names to print
 * @return SYS_NOBODY_LOGGED_IN - there is nobody who is logged
 *         SYS_INVALID_PARAMETER - if the amount is lower or equal to 0
 *         SYS_OK - otherwise
 */
SysResult reportReference(CourseManager sys,FILE* output,int c_id,int amount);

/**
 * prints "your request was rejected" if the request is legal
 * @param sys
 * @param output - File descriptor for the output channel
 * @param c_id - given course id
 * @param req - the request "cancel_course" or "register_course" or "remove_course"
 * @return SYS_NOBODY_LOGGED_IN - there is nobody who is logged
 *         SYS_COURSE_DOES_NOT_EXIST - if the request is "remove_course" and the
 *         online student doesn't have this course in his grade sheet
 *         SYS_INVALID_PARAMETER - the request is illegal
 *         SYS_OK - otherwise
 */
SysResult reportFacultyRequest(CourseManager sys,FILE* output,int c_id,char *req);


#endif //MTM_EX3_COURSE_MANAGER_H
