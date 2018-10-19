//
// Created by Dina on 15-Dec-17.
//

#ifndef EX3_STUDENT_H
#define EX3_STUDENT_H

#include "set.h"
#include "Friend.h"
#include "Course.h"
#include "Grade.h"
#include <stdio.h>
typedef struct student_t *Student;

///this is a field that tells the status of the student

typedef enum {
  online,
  offline
} Status;


typedef enum {
  STUDENT_OK,
  STUDENT_ILLEGAL_PAR,
  STUDENT_MEMORY_ERROR,
  STUDENT_ALREADY_LOGGED_IN,
  STUDENT_ALREADY_LOGGED_OUT,
  STUDENT_NULL_ARG,
  STUDENT_REQ_NOT_EXIST,
  STUDENT_COURSE_NOT_EXIST,
  STUDENT_ALREADY_FRIENDS,
  STUDENT_NOT_FRIENDS,
  STUDENT_NOT_EXISTS
} StudentResult;


///generic functions
//=============================================================================
SetElement setCopyStudent(SetElement element);
void setFreeStudent(SetElement);
int setCmpStudent(SetElement, SetElement);

//=============================================================================

/**creates a new student according to the giving parameters
 * also allocate new space .who ever use this function need to remember
 * to realese the memory with destroy student
 * we assert the giving paramters are correct
 * retruning value: a pointer to the new student
 * NULL otherwise
 */
Student createStudent (int id, char *first_name, char *last_name);

/** deallocate student and all the fields as well
 */
void destroyStudent(Student student);

/**makes the status of  the given student online
 * return value :
 * STUDENT_ALREADY_LOGGED_IN if already online
 * STUDENT_OK otherwise
 */
StudentResult makeOnline( Student student);

/**makes the status of the student  offline
 * return value :
 * STUDENT_ALREADY_LOGGED_OUT if already offline
 * STUDENT_OK otherwise
 */
StudentResult makeOffline( Student student);

/**return a bool according to the status of the given student
 * STUDENT_NULL_ARG if NULL was sent
 * otherwise Online/Offline
 */
Status getStatus(Student student);


/**
 * this functions add a new friend according to given id
 * @param students-set of students
 * @param student -target student
 * @param other_id - the id of the other student
 * @return STUDENT_NULL_ARG if target student is NULL
 * STUDENT_ALREADY_FEIENDS
 * STUDENT_OK
 *
 */
StudentResult studentAddFriend(Set students, Student student, int other_id);

/**
 *
 * @param friends- set of friends of selected student
 * @param id -a friend id
 * @return - Friend if exists NULL otherwise
 */
Friend getFriend(Set friends, int id);

/**
 *
 * @param student - targes student
 * @return set of friends or NULL if student is NULL
 */
Set getSetFriend(  Student student);

/**
 *
 * @param student
 * @return
 */
int getStudentId( Student student);

Set getSetFriendReq(  Student student);

char *getFirstName(Student student);

char *getLastName(Student student);

/**
 * this function tells if student has a friend with the given id
 * @param student -target student
 * @param other_id - the friend we looking for
 * @return true - if freinds , false otherwise
 */
bool alreadyFriends(Student student, int other_id); //write test , chabge order

/**
 * tells if there is already existed freind request with the given id
 * @param student - target student
 * @param other_id - the request we looking for
 * @return true if exists, false otherwise
 */
bool requestExist(Student student , int other_id);//write test

/**function that gets an id of ather student
 * and removes the friend request frot the given student if exists
 * return value : STUDENT_REQ_NOT_EXIST if no such request
 *STODENT_OK otherwise
 */

StudentResult removeFriendReq(Student student , int other_id);

/** the function is here because we want to allow flexability in the system
 **param: id and set of students
 * return : NULL if no such student
 * Student with the given id otherwise
 */
Student getStudent(Set students, int id);

/**
 * remove a friend from the student friends
 * @param student
 * @param other_id - the id of the  friend
 * @return STUDENT_NULL_ARG - if null was sent
 *         STUDENT_NOT_FRIENDS-if the other id doesnt match to any friend
 *          STUDENT_NOT_EXISTS-if the other id is of a student that does not
 *                              exists in the sytem
 *          STUDENT_OK -otherwise
 */
StudentResult studentRemoveFriend(Student student ,int other_id);

/**
 * adds a grade to the student gradesheet
 * @param stu target student
 * @param sem semester
 * @param c_id course id
 * @param pts points
 * @param grd grade
 * @return STUDENT_NULL_ARG - if null was sent
 *          STUDENT_OK - otherwise
 */
StudentResult studentAddGrade(Student stu,int sem,int c_id,char* pts,int grd);

/**
 * remove a grade from the student gradesheet
 * @param student
 * @param semester
 * @param course_id
 * @return  STUDENT_NULL_ARG- if null was sent
 *          STUDENT_COURSE_NOT_EXIST - if the student never took the course
 *          STUDENT_OK- otherwise
 */
StudentResult studentRemoveGrade(Student student , int semester,int course_id);

/**
 * returns a list of grades
 * @param student - target
 * @return NULL - if null was sent
 */
List getGradeList(Student student);//check if needed

/**
 * updates the last grade of the given course
 * @param student
 * @param course_id
 * @param new_g - new grade
 * @return STUDENT_NULL_ARG- if null was sent
 *          STUDENT_COURSE_NOT_EXIST - if the student never took the course
 *          STUDENT_OK- otherwise
 */
StudentResult studentUpdateGrade(Student student ,int course_id , int new_g);
/**
 * returns the last semester of the student
 * @param student
 * @return -1 - if null was sent
 *          a positive number otherwise
 */
int studentGetMaxSem(Student student);


Course getCourse(Student student , int c_id);//added

/**
 * type of function that add courses to the student
 * @param student - the student we want to make the change on
 * @param c_id - an int of course id
 * @return STUDENT_NULL_ARG if null was sent
 */
StudentResult studentAddCourse(Student student,
                               int c_id,
                               int semester,
                               char *pts);//added

/**
 *type of function that print to the output the student info
 * this funcion use mtmtmPrintStudentInfo from mtm_ex3.h
 * @param student
 * @param output-File descriptor for the output channe
 */
void studentPrintStuInfo(Student student, FILE *output);//added



/**
 *  Prints grade details.
 * @using:
 * mtmPrintGradeInfo
 * calcEffectivePointsForSem
 * calcEffectivePointsForCourse
 * @param student
 * @param output File descriptor for the output channe
 * @param grade
 */
void studentPrintGradeInfo(Student student, FILE *output, Grade grade);//added




/**
 * this function update the last_semester field in the given course , to be
 *the last time this course id is appeard inside the list of the grades.
 * this assures us that every time we want to access the last grade of a course,
 * it would be updated, if no course is finded the update will be to 0
 * @param student
 * @param c_id
 */
void studentUpdateCourseLast(Student student, int c_id);//added

/** Prints a line containing semester details.
 *  using mtmPrintSemesterInfo
 *
 * @param student
 * @param output- File descriptor for the output channel.
 * @param semester  - The semester number.
 */
void studentPrintSemesterInfo(Student student , FILE *output ,int semester );

/**
 * Prints a line containing the summery of a given student's grade sheet
 * @param student
 * @param output - File descriptor for the output channel.
 */
void studentPrintSummary(Student student , FILE* output );

/**
 * prints a  report of  clean grade-sheet , according to criteries of
 * course system
 * @param student the target student
 * @param output  File descriptor for the output channel.
 */
void studentPrintClean(Student student , FILE* output);

/**
 * prints the best effective grades of a student according to the given amount
 * @param student the target student
 * @param output File descriptor for the output channel.
 * @param amount positive number
 */
void studentPrintBest(Student student,FILE* output, int amount);

/**
* prints the worst effective grades of a student according to the given amount
 * @param student the target student
 * @param output File descriptor for the output channel.
 * @param amount of grades
 */
void studentPrintWorst(Student student,FILE* output, int amount);

/**
 * prints the names of the students friends , who got the best grades
 * in a given course
 *
 * @param s - student
 * @param Students - a Set of students in the system
 * @param output- File descriptor for the output channel.
 * @param c_id - course id
 * @param amount- of frineds
 */

void stuReportReference(Student s,Set Students,FILE* output,int c_id,int amount);

/**
 * checks if the student took this course
 * @param student
 * @param c_id -course id
 * @return if he did not take the course STUDENT_COURSE_NOT_EXIST
 * STUDENT_OK otherwise
 */
StudentResult studentCheckCourse(Student student, int c_id);


#endif //EX3_STUDENT_H
