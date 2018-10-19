//
// Created by daniel on 12/11/2017.
//
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "../Headers/set.h"
#include "../Headers/list.h"
#include "../Headers/CourseManager.h"
#include "../Headers/FriendRequest.h"
#include "../Headers/Grade.h"
#include "../Headers/Friend.h"
#include "../Headers/Student.h"
#include "../Headers/mtm_ex3.h"



struct course_manager_t{
  Set Students;
};

#define CHECK_SYS(system) \
  if (!(system)) return SYS_NULL_PARAMETER; \
   if(system->Students==NULL) return SYS_NULL_PARAMETER;


#define GET_ONLINE_STU(system , student) \
if (getOnlineStudent(system, &student) != SYS_OK) \
return SYS_NOBODY_LOGGED_IN;



SysResult  createSystem(CourseManager *new){
  CourseManager  courseManager=malloc(sizeof(*courseManager));
  if(!courseManager){
    return SYS_OUT_OF_MEMORY;
  }
  courseManager->Students=setCreate(setCopyStudent,setFreeStudent,setCmpStudent);
  if ( courseManager->Students == NULL){
    free(courseManager);
    return SYS_OUT_OF_MEMORY;
  }
  *new=courseManager;
  return SYS_OK;
}

SysResult destroySys(CourseManager system){
  if(!system) return SYS_NULL_PARAMETER;
  if(system->Students==NULL) return SYS_NULL_PARAMETER;
  setDestroy(system->Students);
  free(system);
  return SYS_OK;
}

SysResult studentAdd(CourseManager sys, int id, char *f_name, char *l_name){
  CHECK_SYS(sys);
  if (f_name == NULL || l_name == NULL ){
    return SYS_NULL_PARAMETER;
  }
  Student s = createStudent(id, f_name, l_name);
  if (s == NULL) return SYS_OUT_OF_MEMORY;
  SetResult result = setAdd(sys->Students, s);
  if (result == SET_ITEM_ALREADY_EXISTS){
    destroyStudent(s);      //we assert success
    return SYS_STUDENT_ALREADY_EXISTS;
  }
  if (result == SET_OUT_OF_MEMORY) {
    destroyStudent(s);      //we assert success
    return SYS_OUT_OF_MEMORY;
  }
  if (id<=0){
    setRemove(sys->Students,s);
    destroyStudent(s);
    return SYS_INVALID_PARAMETER;
  }
  destroyStudent(s);
  return SYS_OK;
}



SysResult studentRemove(CourseManager system, StudentId id) {
  CHECK_SYS(system);
  Student student = getStudent(system->Students, id);
  if (student == NULL) {
    return SYS_STUDENT_NOT_EXISTS;
  }
  setRemove(system->Students, student);
  return SYS_OK;
}


SysResult getOnlineStudent(CourseManager system , Student *result) {
  *result=NULL;
  CHECK_SYS(system);
  SET_FOREACH(Student, i, system->Students) {
    Status s_result = getStatus(i);
    if (s_result == online) {
      *result=i;
      return SYS_OK;
    }
  }
  return SYS_STUDENT_NOT_EXISTS;
}


SysResult studentLogin(CourseManager system, int id) {
  CHECK_SYS(system);
  Student student1;
  if (getOnlineStudent(system, &student1) == SYS_OK){
    return SYS_ALREADY_LOGGED_IN;
  }
  Student student = getStudent(system->Students, id);
  StudentResult result1 = makeOnline(student);
  if (result1 == STUDENT_ALREADY_LOGGED_IN) {
    return SYS_ALREADY_LOGGED_IN;
  }
  if(result1==STUDENT_NULL_ARG)return SYS_STUDENT_NOT_EXISTS;
  return SYS_OK;
}

SysResult studentLogout(CourseManager system) {
  CHECK_SYS(system);
  Student student;
  if (getOnlineStudent(system, &student) == SYS_OK) {
    makeOffline(student);
    return SYS_OK;
  }
  return SYS_NOBODY_LOGGED_IN;
}

SysResult friendRequest(CourseManager system, int other_id) {
  CHECK_SYS(system);
  Student student;
  GET_ONLINE_STU(system,student);
  Student other = getStudent(system->Students, other_id);
  if (!other)return SYS_STUDENT_NOT_EXISTS;
  if (alreadyFriends(student, other_id))return SYS_ALREADY_FRIEND;
  FriendRequest request = createFriendReq(getStudentId(student));
  assert(request);
  Set friend_req = getSetFriendReq(other);
  bool result = setIsIn(friend_req, request);
  //SetResult result = setAdd(friend_req, request);
  if (result == true) {
    destroyFriendReq(request);
    return SYS_ALREADY_REQUESTED;
  }
  if(setAdd(friend_req, request)==SET_OUT_OF_MEMORY){
    return SYS_OUT_OF_MEMORY;
  }
  destroyFriendReq(request);
  return SYS_OK;
}

SysResult handleRequest(CourseManager system,StudentId other_id,char *action){
  CHECK_SYS(system);
  Student student;
  GET_ONLINE_STU(system, student);
  int stu_id = getStudentId(student);
  Student other = getStudent(system->Students, other_id);
  if (!other)return SYS_STUDENT_NOT_EXISTS;
  if (alreadyFriends(student, other_id) || stu_id == other_id) {
    return SYS_ALREADY_FRIEND;
  }
  if (requestExist(student, other_id) != true) return SYS_NOT_REQUESTED;
  if (strcmp(action, "reject") == 0) {
    removeFriendReq(student, other_id);
    return SYS_OK;
  }
  if (strcmp(action, "accept") == 0) {
    return handleAccept(system, student, other);
  }
  return SYS_INVALID_PARAMETER;
}
//prob static
SysResult handleAccept(CourseManager system, Student stu1, Student stu2) {
  CHECK_SYS(system);
  int stu1_id = getStudentId(stu1);
  int stu2_id = getStudentId(stu2);
  if (requestExist(stu1, stu2_id)) {
    studentAddFriend(system->Students, stu1, stu2_id);
    studentAddFriend(system->Students, stu2, stu1_id);
    removeFriendReq(stu1, stu2_id);
    if (requestExist(stu2, stu1_id)) {
      removeFriendReq(stu2, stu1_id);
      return SYS_OK;
    }
    return SYS_OK;
  }
  return SYS_NOT_REQUESTED;
}


SysResult studentUnfriend(CourseManager system, int other_id){
  CHECK_SYS(system);
  Student student;
  GET_ONLINE_STU(system , student);
  Student other = getStudent(system->Students, other_id);
  if(!other) return SYS_STUDENT_NOT_EXISTS;
  if(studentRemoveFriend(student , other_id)!=STUDENT_OK){
    return SYS_NOT_FRIENDS;
  }
  studentRemoveFriend(other , getStudentId(student));
  return SYS_OK;
}

Set getSetStudents (CourseManager system){
  if (system == NULL) return NULL;
  return system->Students;
}

bool checkPoints(char* points) {
  if (!points || points[0]=='.')return false;
  for (int i = 0; points[i]; ++i) {
    if (points[i] <= '9' && points[i] >= '0') {
      continue;
    }
    if (i > 0 && points[i] == '.') {
      i++;
      if (points[i] != '5' && points[i] != '0') {
        return false;
      }
      i++;
      if (points[i] != '\0') {
        return false;
      } else return true;
    }
    return false;
  }
  return true;
}
//need to be static
int handleParameters(char* string ){
  if (!string)return -1;
  for (int i = 0;string[i]; ++i) {
    if(string[i] > '9' || string[i] < '0')
      return -1;
  }
  int num=atoi(string);
  return num;
}


SysResult gradeSheetAdd(CourseManager sys,int sem,int c_id,char *pts,int grd){
  CHECK_SYS(sys);
  Student student;
  GET_ONLINE_STU(sys,student);
  if(!checkPoints(pts))return SYS_INVALID_PARAMETER;
  if(sem <=0 ||c_id <= 0 ||c_id > 1000000 || grd > 100 || grd<0){
    return SYS_INVALID_PARAMETER;
  }
  studentAddGrade(student,sem,c_id,pts,grd);
  return SYS_OK;
}

SysResult gradeSheetRemove(CourseManager sys, int sem, int c_id) {
  CHECK_SYS(sys);
  Student student;
  GET_ONLINE_STU(sys, student);
  if (studentRemoveGrade(student, sem, c_id) != STUDENT_OK) {
    return SYS_COURSE_DOES_NOT_EXIST;
  }
  return SYS_OK;
}

SysResult gradeSheetUpdate(CourseManager sys, int c_id, int n_g){
  CHECK_SYS(sys);
  Student student;
  GET_ONLINE_STU(sys, student);
  if(!getCourse(student,c_id))return  SYS_COURSE_DOES_NOT_EXIST;
  if(n_g < 0 || n_g>100  ) {
    return SYS_INVALID_PARAMETER;
  }
  studentUpdateGrade(student , c_id,n_g);
  return SYS_OK;
}

SysResult reportFull(CourseManager system, FILE *output) {
  CHECK_SYS(system);
  Student student;
  GET_ONLINE_STU(system, student);
  studentPrintStuInfo(student,output);
  int max_sem = studentGetMaxSem(student);
  int cur_sem =1;
  List grades = getGradeList(student);
  while (cur_sem <= max_sem) {
    LIST_FOREACH(Grade, i, grades) {
      if (gradeGetSemester(i)!=cur_sem)continue;
      studentPrintGradeInfo(student, output, i);
    }
    studentPrintSemesterInfo(student,output,cur_sem);
    cur_sem++;
  }
  studentPrintSummary(student,output);
  return SYS_OK;
}

SysResult reportClean(CourseManager system , FILE* output){
  CHECK_SYS(system);
  Student student;
  GET_ONLINE_STU(system,student);
  studentPrintStuInfo(student,output);
  studentPrintClean(student,output);
  return SYS_OK;
}

SysResult reportBest(CourseManager system , FILE* output , int amount){
  CHECK_SYS(system);
  Student student;
  GET_ONLINE_STU(system,student);
  if(amount <= 0)
    return SYS_INVALID_PARAMETER;
  studentPrintBest(student,output,amount);
  return SYS_OK;
}


SysResult reportWorst(CourseManager system , FILE* output , int amount){
  CHECK_SYS(system);
  Student student;
  GET_ONLINE_STU(system,student);
  if(amount <= 0)
    return SYS_INVALID_PARAMETER;
  studentPrintWorst(student,output,amount);
  return SYS_OK;
}



SysResult reportReference(CourseManager sys,FILE* output,int c_id,int amount){
  CHECK_SYS(sys);
  Student student;
  GET_ONLINE_STU(sys,student);
  if(amount <= 0)
    return SYS_INVALID_PARAMETER;
  Set Students = getSetStudents(sys);
  stuReportReference(student,Students, output, c_id, amount);
  return SYS_OK;
}



SysResult reportFacultyRequest(CourseManager sys,FILE* output,int c_id,char *req){
  CHECK_SYS(sys);
  Student student;
  GET_ONLINE_STU(sys,student);
  if (strcmp(req , "remove_course") == 0) {
    StudentResult result = studentCheckCourse(student, c_id);
    if (result == STUDENT_COURSE_NOT_EXIST) return SYS_COURSE_DOES_NOT_EXIST;
  }

  if(strcmp(req,"cancel_course") != 0){
    if (strcmp(req,"register_course") != 0){
      if (strcmp(req,"remove_course") != 0){
        return SYS_INVALID_PARAMETER;
      }
    }
  }
  char *response = "your request was rejected";
  mtmFacultyResponse(output, response);
  return SYS_OK;
}

