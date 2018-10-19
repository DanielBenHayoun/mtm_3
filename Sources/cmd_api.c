//
// Created by daniel on 1/1/2018.
//



#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "../Headers/cmdHandler.h"



//Student commands.
CmdResult cmdStudentAdd(argument *arg_array, CourseManager sys) {
  StudentId studentId = (StudentId)atoi(arg_array[0]);
  if(studentId>=1000000000)
    return CMD_INVALID_PARAMETER;
  FirstName firstName = (FirstName)arg_array[1];
  LastName lastName=(LastName)arg_array[2];
  SysResult result = studentAdd(sys, (int)studentId, firstName ,lastName);
  return cmdConvertETSResult(result);
}

CmdResult cmdStudentRemove(argument *arg_array, CourseManager sys) {
  StudentId studentId= (StudentId)atoi(arg_array[0]);
  SysResult result = studentRemove(sys, studentId);
  return cmdConvertETSResult(result);
}

CmdResult cmdStudentLogin(argument *arg_array , CourseManager sys){
  StudentId studentId= (StudentId)atoi(arg_array[0]);
  SysResult result = studentLogin(sys, studentId);
  return cmdConvertETSResult(result);
}

CmdResult cmdStudentLogout(CourseManager sys){
  SysResult result = studentLogout(sys);
  return cmdConvertETSResult(result);
}

CmdResult cmdStudentFriendRequest(argument *arg_array, CourseManager sys){
  FreindId freindId=(FreindId)atoi(arg_array[0]);
  SysResult result = friendRequest(sys,freindId);
  return cmdConvertETSResult(result);
}

CmdResult cmdStudentHandleRequest(argument *arg_array, CourseManager sys){
  FreindId freindId=(FreindId)atoi(arg_array[0]);
  Action action=(Action)arg_array[1];
  SysResult result = handleRequest(sys,freindId,action);
  return cmdConvertETSResult(result);
}

CmdResult cmdStudentUnfriend(argument *arg_array, CourseManager sys){
  FreindId freindId=(FreindId)atoi(arg_array[0]);
  SysResult result = studentUnfriend(sys,freindId);
  return cmdConvertETSResult(result);
}

//Grade commands.
CmdResult cmdGradeAdd(argument *arg_array, CourseManager sys) {
  Semester semester = (Semester)atoi(arg_array[0]);
  CourseId courseid = (CourseId)atoi(arg_array[1]);
  Points points = (Points)arg_array[2];
  GradeNum gradeNum = (GradeNum) atoi(arg_array[3]);
  SysResult result = gradeSheetAdd(sys,semester,courseid,points, gradeNum);
  return cmdConvertETSResult(result);
}

CmdResult cmdGradeRemove(argument *arg_array, CourseManager sys) {
  Semester semester = (Semester)atoi(arg_array[0]);
  CourseId courseid = (CourseId)atoi(arg_array[1]);
  SysResult result = gradeSheetRemove(sys, semester, courseid);
  return cmdConvertETSResult(result);
}


CmdResult cmdGradeUpdate(argument *arg_array, CourseManager sys) {
  CourseId courseid  = (CourseId)atoi(arg_array[0]);
  GradeNum newgrade = (GradeNum)atoi(arg_array[1]);
  SysResult result = gradeSheetUpdate(sys, courseid, newgrade);
  return cmdConvertETSResult(result);
}


//Report commands.
CmdResult cmdReportFull(CourseManager sys, FILE *output) {
  SysResult result = reportFull(sys, output);
  return cmdConvertETSResult(result);
}

CmdResult cmdReportClean(CourseManager sys, FILE *output){
  SysResult result = reportClean(sys, output);
  return cmdConvertETSResult(result);
}

CmdResult cmdReportBest(argument *arg_array, CourseManager sys, FILE *output) {
  int amount  = atoi(arg_array[0]);
  SysResult result = reportBest(sys, output , amount);
  return cmdConvertETSResult(result);
}


CmdResult cmdReportWorst(argument *arg_array, CourseManager sys, FILE *output) {
  int amount  = atoi(arg_array[0]);
  SysResult result = reportWorst(sys, output , amount);
  return cmdConvertETSResult(result);
}

CmdResult cmdReportReference(argument *arg_array, CourseManager sys, FILE *output) {
  CourseId courseid  = (CourseId)atoi(arg_array[0]);
  int amount  = atoi(arg_array[1]);
  SysResult result = reportReference(sys, output ,courseid ,amount);
  return cmdConvertETSResult(result);
}

CmdResult cmdReportreFacultyRequest(argument* arg_array ,CourseManager sys, FILE* output ){
  CourseId courseid  = (CourseId)atoi(arg_array[0]);
  Request request =(Request) arg_array[1];
  SysResult result = reportFacultyRequest(sys, output ,courseid ,request);
  return cmdConvertETSResult(result);

}
