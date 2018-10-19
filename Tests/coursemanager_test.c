#include "../Headers/test_utilities.h"
#include "../Headers/Grade.h"
#include "../Headers/FriendRequest.h"
#include "../Headers/Friend.h"
#include "../Headers/Student.h"
#include "../Headers/CourseManager.h"
#include "../Headers/list.h"
#include "../Headers/set.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>




bool test_createSystem(){
  CourseManager c=NULL;
  SysResult result = createSystem(&c);
  ASSERT_TEST(result == SYS_OK);
  ASSERT_TEST(c != NULL);
  destroySys(c);
  return true;
}


bool test_studentAdd(){
  CourseManager c;
  createSystem(&c);
  SysResult result;
  ASSERT_TEST(c);
  result=studentAdd(c, 0 , "svsvs", "vsvvs");
  ASSERT_TEST(result==SYS_INVALID_PARAMETER);
  result=studentAdd(c, 43, 0, "fgdf");
  ASSERT_TEST(result == SYS_NULL_PARAMETER);
  result = studentAdd(c, 3453, "sfsf", 0);
  ASSERT_TEST(result == SYS_NULL_PARAMETER);
  result = studentAdd(c,-36337, "dfdf" ,"fefv");
  ASSERT_TEST(result == SYS_INVALID_PARAMETER);
  ASSERT_TEST(studentAdd(c,1, "A" ,"a")==SYS_OK);
  ASSERT_TEST(studentAdd(c,1, "A" ,"a")==SYS_STUDENT_ALREADY_EXISTS);
  destroySys(c);
  return true;
}


bool test_studentRemove(){
  CourseManager c;
  createSystem(&c);
  studentAdd(c,1, "A" ,"a");
  studentAdd(c,2, "B" ,"b");
  studentAdd(c,3, "C" ,"c");
  studentAdd(c,4, "D" ,"d");
  studentAdd(c,5, "E" ,"e");
  //good cases
  SysResult result = studentRemove(c, 1);
  ASSERT_TEST(result == SYS_OK);
  result = studentRemove(c, 2);
  ASSERT_TEST(result == SYS_OK);
  result = studentRemove(c, 3);
  ASSERT_TEST(result == SYS_OK);
  result = studentRemove(c, 4);
  ASSERT_TEST(result == SYS_OK);
  result = studentRemove(c, 5);
  ASSERT_TEST(result == SYS_OK);
  result = studentRemove(c, 1);
  //bad cases
  ASSERT_TEST(result == SYS_STUDENT_NOT_EXISTS);
  result = studentRemove(c, 2);
  ASSERT_TEST(result == SYS_STUDENT_NOT_EXISTS);
  result = studentRemove(c, 0);
  ASSERT_TEST(result == SYS_STUDENT_NOT_EXISTS);
  destroySys(c);
  return true;
}

bool test_studentLogin(){
  CourseManager c;
  createSystem(&c);
  studentAdd(c,1, "A" ,"a");
  studentAdd(c,2, "B" ,"b");
  studentAdd(c,3, "C" ,"c");
  //good cases
  SysResult result = studentLogin(c, 1);
  ASSERT_TEST(result == SYS_OK);
  result = studentLogin(c, 2);
  ASSERT_TEST(result == SYS_ALREADY_LOGGED_IN);
  result = studentLogin(c, 3);
  ASSERT_TEST(result == SYS_ALREADY_LOGGED_IN);
  //bad cases
  result = studentLogin(c,-1);
  ASSERT_TEST(result == SYS_ALREADY_LOGGED_IN);
  result = studentLogin(c, 0);
  ASSERT_TEST(result == SYS_ALREADY_LOGGED_IN);
  result = studentLogin(c, 4);
  ASSERT_TEST(result == SYS_ALREADY_LOGGED_IN);
  result = studentLogin(c, 1);
  ASSERT_TEST(result == SYS_ALREADY_LOGGED_IN);

  destroySys(c);
  return true;

}

bool test_studentLogout(){
  CourseManager c;
  createSystem(&c);
  studentAdd(c,1, "A" ,"a");
  studentAdd(c,2, "B" ,"b");
  studentAdd(c,3, "C" ,"c");
  studentLogin(c, 3);
  SysResult result = studentLogout(c);
  ASSERT_TEST(result == SYS_OK);
  result = studentLogout(c);
  ASSERT_TEST(result == SYS_NOBODY_LOGGED_IN);
  destroySys(c);
  return true;
}
 //need to be static
bool test_getOnlineStudent(){
  CourseManager c;
  createSystem(&c);
  studentAdd(c,1, "A" ,"a");
  studentAdd(c,2, "B" ,"b");
  studentAdd(c,3, "C" ,"c");
  Student student;
  ASSERT_TEST(getOnlineStudent(c, &student) == SYS_STUDENT_NOT_EXISTS);
  ASSERT_TEST(student == NULL);
  studentLogin(c, 1);
  ASSERT_TEST(getOnlineStudent(c, &student) == SYS_OK);
  destroySys(c);
  return true;
}



bool test_friendRequest(){
  CourseManager c;
  createSystem(&c);
  studentAdd(c,1, "A" ,"a");
  studentAdd(c,2, "B" ,"b");
  studentAdd(c,3, "C" ,"c");
  ASSERT_TEST(friendRequest(c,1)==SYS_NOBODY_LOGGED_IN);
  studentLogin(c, 3);
  ASSERT_TEST(friendRequest(c,1)==SYS_OK);
  ASSERT_TEST(friendRequest(c,2)==SYS_OK);
  ASSERT_TEST(friendRequest(c,3)==SYS_ALREADY_FRIEND);
  ASSERT_TEST(friendRequest(c,4)==SYS_STUDENT_NOT_EXISTS);
  ASSERT_TEST(friendRequest(c,2)==SYS_ALREADY_REQUESTED);

  studentLogout(c);
  destroySys(c);
  return true;
}

bool test_handleRequst(){
  CourseManager c;
  createSystem(&c);
  studentAdd(c,1, "A" ,"a");
  studentAdd(c,2, "B" ,"b");
  studentAdd(c,3, "C" ,"c");

  studentLogin(c, 1);
  friendRequest(c,3);
  studentLogout(c);
  studentLogin(c,3);
  ASSERT_TEST(handleRequest(c, 1, "reject") == SYS_OK);
  //this is for the programmer
  ASSERT_TEST(removeFriendReq(getStudent(getSetStudents(c),3 ), 1) == STUDENT_REQ_NOT_EXIST);
  studentLogout(c);

  studentLogin(c, 3);
  friendRequest(c,1);
  friendRequest(c,2);
  studentLogout(c);
  studentLogin(c, 1);
  ASSERT_TEST(handleRequest(c ,3 , "accept" )==SYS_OK);
  ASSERT_TEST(handleRequest(c ,3 , "accept" )==SYS_ALREADY_FRIEND);
  ASSERT_TEST(handleRequest(c ,2 , "accept" )==SYS_NOT_REQUESTED);
  studentLogout(c);
  studentLogin(c , 2);
  ASSERT_TEST(handleRequest(c , 3, "f")==SYS_INVALID_PARAMETER);
  ASSERT_TEST(handleRequest(c , 3, "accept")==SYS_OK);
  ASSERT_TEST(handleRequest(c , 3, "accept")==SYS_ALREADY_FRIEND);
  ASSERT_TEST(handleRequest(c , 4, "accept")==SYS_STUDENT_NOT_EXISTS);
  studentLogout(c);
  ASSERT_TEST(handleRequest(c , 3, "accept")==SYS_NOBODY_LOGGED_IN);
    studentLogin(c , 2);
  ASSERT_TEST(handleRequest(c , 3, "f")==SYS_ALREADY_FRIEND);
  ASSERT_TEST(handleRequest(c , -5, "f")==SYS_STUDENT_NOT_EXISTS);
  destroySys(c);
  return true;
}

bool test_getSetStudents(){
  CourseManager c;
  createSystem(&c);
  ASSERT_TEST(getSetStudents(c) != NULL);
  destroySys(c);
  return true;
}

 //static
bool test_handleAccept(){
  CourseManager c;
  createSystem(&c);
  studentAdd(c,1, "A" ,"a");
  studentAdd(c,2, "B" ,"b");
  studentAdd(c,3, "C" ,"c");
  studentLogin(c, 3);
  Student s1 = getStudent(getSetStudents(c), 1);
  Student s2 = getStudent(getSetStudents(c), 2);
  Student s3 = getStudent(getSetStudents(c), 3);
  ASSERT_TEST(handleAccept(c, s3, s1) == SYS_NOT_REQUESTED);
  ASSERT_TEST(handleAccept(c, s3, s2) == SYS_NOT_REQUESTED);
  friendRequest(c,1);
  friendRequest(c,2);
  studentLogout(c);
  studentLogin(c, 1);
  //displayStudent(s1);
  //displayStudent(s2);
  //displayStudent(s3);
  ASSERT_TEST(handleAccept(c, s1, s2) == SYS_NOT_REQUESTED);
  ASSERT_TEST(handleAccept(c, s1, s3) == SYS_OK);
  ASSERT_TEST(handleAccept(c, s1, s3) == SYS_NOT_REQUESTED);
  friendRequest(c, 2);
  studentLogout(c);
  studentLogin(c, 2);
  ASSERT_TEST(handleAccept(c, s2, s1) == SYS_OK);
  ASSERT_TEST(handleAccept(c, s2, s1) == SYS_NOT_REQUESTED);
  ASSERT_TEST(handleAccept(c, s2, s3) == SYS_OK);
  ASSERT_TEST(handleAccept(c, s2, s3) == SYS_NOT_REQUESTED);

  destroySys(c);
  return true;
}

bool test_studentUnfriend(){
  CourseManager c;
  createSystem(&c);
  studentAdd(c,1, "A" ,"a");
  studentAdd(c,2, "B" ,"b");
  studentAdd(c,3, "C" ,"c");
  ASSERT_TEST(studentUnfriend(c, 1) == SYS_NOBODY_LOGGED_IN);
  studentLogin(c, 3);
  ASSERT_TEST(studentUnfriend(c,4) == SYS_STUDENT_NOT_EXISTS);
  friendRequest(c,1);
  friendRequest(c,2);
  studentLogout(c);
  studentLogin(c, 1);
  ASSERT_TEST(handleRequest(c ,3, "accept" )==SYS_OK);
  ASSERT_TEST(studentUnfriend(c,3)==SYS_OK);
  ASSERT_TEST(studentUnfriend(c,2) == SYS_NOT_FRIENDS);
  destroySys(c);
  return true;
}






bool test_gradeSheetAdd(){
  CourseManager c;
  createSystem(&c);
  studentAdd(c,1, "A" ,"a");
  ASSERT_TEST(gradeSheetAdd(c,1,1,"0.5",50)==SYS_NOBODY_LOGGED_IN);
  studentLogin(c,1);
  ASSERT_TEST(gradeSheetAdd(c,1,1,"0.5",50)==SYS_OK);
  ASSERT_TEST(gradeSheetAdd(c,-5,1,"0.5",50)==SYS_INVALID_PARAMETER);
  ASSERT_TEST(gradeSheetAdd(c,3,-1,"0.5",50)==SYS_INVALID_PARAMETER);
  ASSERT_TEST(gradeSheetAdd(c,3,1,"0.55",50)==SYS_INVALID_PARAMETER);
  ASSERT_TEST(gradeSheetAdd(c,3,1,"0.05",50)==SYS_INVALID_PARAMETER);
  ASSERT_TEST(gradeSheetAdd(c,3,1,"0.1",50)==SYS_INVALID_PARAMETER);
  ASSERT_TEST(gradeSheetAdd(c,3,1,"15.1",50)==SYS_INVALID_PARAMETER);
  destroySys(c);
  return true;
}

bool test_gradeSheetRemove(){
  CourseManager c;
  createSystem(&c);
  studentAdd(c,1, "A" ,"a");
  ASSERT_TEST(gradeSheetRemove(c,1,1)==SYS_NOBODY_LOGGED_IN);
  studentLogin(c,1);
  ASSERT_TEST(gradeSheetAdd(c,1,1,"0.5",50)==SYS_OK);
  ASSERT_TEST(gradeSheetRemove(c,1,1)==SYS_OK);
  ASSERT_TEST(gradeSheetAdd(c,1,1,"0.5",50)==SYS_OK);
  ASSERT_TEST(gradeSheetRemove(c,2,1)==SYS_COURSE_DOES_NOT_EXIST);
  ASSERT_TEST(gradeSheetAdd(c,2,2,"0.5",50)==SYS_OK);
  ASSERT_TEST(gradeSheetAdd(c,3,3,"0.5",50)==SYS_OK);
  ASSERT_TEST(gradeSheetRemove(c,2,2)==SYS_OK);
  ASSERT_TEST(gradeSheetRemove(c,2,2)==SYS_COURSE_DOES_NOT_EXIST);
  ASSERT_TEST(gradeSheetAdd(c,4,4,"0.5",50)==SYS_OK);
  ASSERT_TEST(gradeSheetAdd(c,4,4,"0.5",50)==SYS_OK);
  ASSERT_TEST(gradeSheetRemove(c,4,4)==SYS_OK);
  ASSERT_TEST(gradeSheetRemove(c,4,4)==SYS_OK);
  studentLogout(c);
  studentAdd(c,2,"B","b");
  studentLogin(c,1);
  ASSERT_TEST(gradeSheetAdd(c,1,1,"0.5",50)==SYS_OK);
  ASSERT_TEST(gradeSheetRemove(c,1,1)==SYS_OK);
  ASSERT_TEST(gradeSheetAdd(c,1,1,"0.5",50)==SYS_OK);
  ASSERT_TEST(gradeSheetRemove(c,2,1)==SYS_COURSE_DOES_NOT_EXIST);
  ASSERT_TEST(gradeSheetAdd(c,2,2,"0.5",50)==SYS_OK);
  ASSERT_TEST(gradeSheetAdd(c,3,3,"0.5",50)==SYS_OK);
  ASSERT_TEST(gradeSheetRemove(c,2,2)==SYS_OK);
  ASSERT_TEST(gradeSheetRemove(c,2,2)==SYS_COURSE_DOES_NOT_EXIST);
  ASSERT_TEST(gradeSheetAdd(c,4,4,"0.5",50)==SYS_OK);
  ASSERT_TEST(gradeSheetAdd(c,4,4,"0.5",50)==SYS_OK);
  ASSERT_TEST(gradeSheetRemove(c,4,4)==SYS_OK);
  ASSERT_TEST(gradeSheetRemove(c,4,4)==SYS_OK);
  destroySys(c);
  return true;
}

bool test_gradeSheetUpdate(){
  CourseManager c;
  createSystem(&c);
  studentAdd(c,1, "A" ,"a");
  ASSERT_TEST(gradeSheetRemove(c,1,1)==SYS_NOBODY_LOGGED_IN);
  studentLogin(c,1);
  gradeSheetAdd(c,1,1,"0.5",50);
  gradeSheetAdd(c,1,2,"0.5",50);
  ASSERT_TEST(gradeSheetUpdate(c,1,80)==SYS_OK);
  ASSERT_TEST(gradeSheetUpdate(c,3,80)==SYS_COURSE_DOES_NOT_EXIST);
  ASSERT_TEST(gradeSheetUpdate(c,1,120)==SYS_INVALID_PARAMETER);
  ASSERT_TEST(gradeSheetUpdate(c,2,-50)==SYS_INVALID_PARAMETER);
  destroySys(c);
  return true;
}

bool test_repurtFull(){
  CourseManager c;
  createSystem(&c);
  studentAdd(c,1, "A" ,"a");
  ASSERT_TEST(reportClean(c,stdout)==SYS_NOBODY_LOGGED_IN);
  studentLogin(c, 1);
  gradeSheetAdd(c,1,104012,"5.5",4);
  gradeSheetAdd(c,1,104167,"5.0" ,43);
  gradeSheetAdd(c,1,104167,"5.0" ,71);
  gradeSheetAdd(c,1,234114,"4.0" ,88);
  gradeSheetAdd(c,1,234145,"3.0" ,98);
  gradeSheetAdd(c,1,394808,"1.0" ,92);
  gradeSheetAdd(c,2,104013,"5.5" ,66);
  gradeSheetAdd(c,2,104013,"5.5" ,63);
  gradeSheetAdd(c,2,114071,"3.5" ,98);
  gradeSheetAdd(c,2,234118,"3.0" ,98);
  gradeSheetAdd(c,2,234122,"3.0" ,28);
  gradeSheetAdd(c,2,234122,"3.0" ,96);
  gradeSheetAdd(c,2,234141,"3.0" ,73);
  gradeSheetAdd(c,2,394806,"1.0" ,96);
  gradeSheetAdd(c,3,94412,"4.0" ,80);
  gradeSheetAdd(c,3,104134,"2.5" ,82);
  gradeSheetAdd(c,3,134058,"3.0" ,70);
  gradeSheetAdd(c,3,234218,"3.0" ,75);
  gradeSheetAdd(c,3,234262,"3.0" ,94);
  gradeSheetAdd(c,3,234293,"4.0" ,71);
  gradeSheetAdd(c,3,394902,"1.5" ,96);
  gradeSheetAdd(c,4,125001,"3.0" ,69);
  gradeSheetAdd(c,4,134020,"3.5" ,56);
  gradeSheetAdd(c,4,134020,"3.5" ,76);
  gradeSheetAdd(c,4,234123,"4.5" ,94);
  gradeSheetAdd(c,4,234247,"3.0" ,95);
  gradeSheetAdd(c,4,234267,"3.0" ,60);
  gradeSheetAdd(c,4,234267,"3.0" ,68);
  gradeSheetAdd(c,4,236353,"3.0" ,78);
  gradeSheetAdd(c,4,394902,"1.5" ,92);
  gradeSheetAdd(c,5,234107,"4.0" ,51);
  gradeSheetAdd(c,5,234107,"4.0" ,63);
  gradeSheetAdd(c,5,234900,"2.0" ,74);
  gradeSheetAdd(c,5,236327,"3.0" ,77);
  gradeSheetAdd(c,5,236334,"3.0" ,64);
  gradeSheetAdd(c,5,236334,"3.0" ,68);
  gradeSheetAdd(c,5,236343,"3.0" ,80);
  gradeSheetAdd(c,5,236360,"3.0" ,71);
  gradeSheetAdd(c,5,324440,"2.0" ,79);
  gradeSheetAdd(c,5,394902,"1.5" ,97);
  gradeSheetAdd(c,6,94591,"3.5" ,86);
  gradeSheetAdd(c,6,234319,"3.0" ,93);
  gradeSheetAdd(c,6,236370,"3.0" ,90);
  gradeSheetAdd(c,6,236504,"3.0" ,89);
  gradeSheetAdd(c,6,236604,"2.0" ,65);
  gradeSheetAdd(c,6,236653,"3.0" ,87);
  gradeSheetAdd(c,6,324290,"2.0" ,73);
  gradeSheetAdd(c,6,394902,"1.5" ,93);
  gradeSheetAdd(c,7,104174,"3.5" ,25);
  gradeSheetAdd(c,7,104174,"3.5" ,90);
  gradeSheetAdd(c,7,236350,"3.0" ,84);
  gradeSheetAdd(c,7,236503,"3.0" ,71);
  gradeSheetAdd(c,7,236603,"2.0" ,71);
  gradeSheetAdd(c,7,236703,"3.0" ,44);
  gradeSheetAdd(c,7,394902,"1.5" ,98);
  gradeSheetRemove(c,4,125001);
  gradeSheetUpdate(c,236703,100);
  reportFull(c, stdout);
  studentAdd(c,2, "B" ,"b");
  studentLogout(c);
  studentLogin(c,2);
  gradeSheetAdd(c,5,394902,"1.5" ,97);
  gradeSheetAdd(c,6,94591,"3.5" ,86);
  gradeSheetAdd(c,6,94591,"0.0" ,86);
  gradeSheetUpdate(c,94591,56);
  gradeSheetAdd(c,7,236703,"3.0" ,44);
  reportFull(c,stdout);
  destroySys(c);
  return true;

}

bool test_reportClean(){
  CourseManager c;
  createSystem(&c);
  studentAdd(c,1, "A" ,"a");
  ASSERT_TEST(reportClean(c,stdout)==SYS_NOBODY_LOGGED_IN);
  studentLogin(c, 1);
  gradeSheetAdd(c,1,104012,"5.5" ,84);
  gradeSheetAdd(c,1,104167,"5.0" ,43);
  gradeSheetAdd(c,1,104167,"5.0" ,71);
  gradeSheetAdd(c,1,234114,"4.0" ,88);
  gradeSheetAdd(c,1,234145,"3.0" ,98);
  gradeSheetAdd(c,1,394808,"1.0" ,92);
  gradeSheetAdd(c,2,104013,"5.5" ,66);
  gradeSheetAdd(c,2,104013,"5.5" ,63);
  gradeSheetAdd(c,2,114071,"3.5" ,98);
  gradeSheetAdd(c,2,234118,"3.0" ,98);
  gradeSheetAdd(c,2,234122,"3.0" ,28);
  gradeSheetAdd(c,2,234122,"3.0" ,96);
  gradeSheetAdd(c,2,234141,"3.0" ,73);
  gradeSheetAdd(c,2,394806,"1.0" ,96);
  gradeSheetAdd(c,3,94412,"4.0" ,80);
  gradeSheetAdd(c,3,104134,"2.5" ,82);
  gradeSheetAdd(c,3,134058,"3.0" ,70);
  gradeSheetAdd(c,3,234218,"3.0" ,75);
  gradeSheetAdd(c,3,234262,"3.0" ,94);
  gradeSheetAdd(c,3,234293,"4.0" ,71);
  gradeSheetAdd(c,3,394902,"1.5" ,96);
  gradeSheetAdd(c,4,125001,"3.0" ,69);
  gradeSheetAdd(c,4,134020,"3.5" ,56);
  gradeSheetAdd(c,4,134020,"3.5" ,76);
  gradeSheetAdd(c,4,234123,"4.5" ,94);
  gradeSheetAdd(c,4,234247,"3.0" ,95);
  gradeSheetAdd(c,4,234267,"3.0" ,60);
  gradeSheetAdd(c,4,234267,"3.0" ,68);
  gradeSheetAdd(c,4,236353,"3.0" ,78);
  gradeSheetAdd(c,4,394902,"1.5" ,92);
  gradeSheetAdd(c,5,234107,"4.0" ,51);
  gradeSheetAdd(c,5,234107,"4.0" ,63);
  gradeSheetAdd(c,5,234900,"2.0" ,74);
  gradeSheetAdd(c,5,236327,"3.0" ,77);
  gradeSheetAdd(c,5,236334,"3.0" ,64);
  gradeSheetAdd(c,5,236334,"3.0" ,68);
  gradeSheetAdd(c,5,236343,"3.0" ,80);
  gradeSheetAdd(c,5,236360,"3.0" ,71);
  gradeSheetAdd(c,5,324440,"2.0" ,79);
  gradeSheetAdd(c,5,394902,"1.5" ,97);
  gradeSheetAdd(c,6,94591,"3.5" ,86);
  gradeSheetAdd(c,6,234319,"3.0" ,93);
  gradeSheetAdd(c,6,236370,"3.0" ,90);
  gradeSheetAdd(c,6,236504,"3.0" ,89);
  gradeSheetAdd(c,6,236604,"2.0" ,65);
  gradeSheetAdd(c,6,236653,"3.0" ,87);
  gradeSheetAdd(c,6,324290,"2.0" ,73);
  gradeSheetAdd(c,6,394902,"1.5" ,93);
  gradeSheetAdd(c,7,104174,"3.5" ,25);
  gradeSheetAdd(c,7,104174,"3.5" ,90);
  gradeSheetAdd(c,7,236350,"3.0" ,84);
  gradeSheetAdd(c,7,236503,"3.0" ,71);
  gradeSheetAdd(c,7,236603,"2.0" ,71);
  gradeSheetAdd(c,7,236703,"3.0" ,44);
  gradeSheetAdd(c,7,394902,"1.5" ,98);
  gradeSheetRemove(c,4,125001);
  gradeSheetUpdate(c,236703,100);
  ASSERT_TEST(reportClean(c,stdout)==SYS_OK);
  destroySys(c);
  return true;
}

bool test_reportBest(){
  CourseManager c;
  createSystem(&c);
  studentAdd(c,1, "A" ,"a");
  ASSERT_TEST(reportClean(c,stdout)==SYS_NOBODY_LOGGED_IN);
  studentLogin(c, 1);
  gradeSheetAdd(c,1,104012,"5.5" ,84);
  gradeSheetAdd(c,1,104167,"5.0" ,43);
  gradeSheetAdd(c,1,104167,"5.0" ,71);
  gradeSheetAdd(c,1,234114,"4.0" ,88);
  gradeSheetAdd(c,1,234145,"3.0" ,98);
  gradeSheetAdd(c,1,394808,"1.0" ,92);
  gradeSheetAdd(c,2,104013,"5.5" ,66);
  gradeSheetAdd(c,2,104013,"5.5" ,63);
  gradeSheetAdd(c,2,114071,"3.5" ,98);
  gradeSheetAdd(c,2,234118,"3.0" ,98);
  gradeSheetAdd(c,2,234122,"3.0" ,28);
  gradeSheetAdd(c,2,234122,"3.0" ,96);
  gradeSheetAdd(c,2,234141,"3.0" ,73);
  gradeSheetAdd(c,2,394806,"1.0" ,96);
  gradeSheetAdd(c,3,94412,"4.0" ,80);
  gradeSheetAdd(c,3,104134,"2.5" ,82);
  gradeSheetAdd(c,3,134058,"3.0" ,70);
  gradeSheetAdd(c,3,234218,"3.0" ,75);
  gradeSheetAdd(c,3,234262,"3.0" ,94);
  gradeSheetAdd(c,3,234293,"4.0" ,71);
  gradeSheetAdd(c,3,394902,"1.5" ,96);
  gradeSheetAdd(c,4,125001,"3.0" ,69);
  gradeSheetAdd(c,4,134020,"3.5" ,56);
  gradeSheetAdd(c,4,134020,"3.5" ,76);
  gradeSheetAdd(c,4,234123,"4.5" ,94);
  gradeSheetAdd(c,4,234247,"3.0" ,95);
  gradeSheetAdd(c,4,234267,"3.0" ,60);
  gradeSheetAdd(c,4,234267,"3.0" ,68);
  gradeSheetAdd(c,4,236353,"3.0" ,78);
  gradeSheetAdd(c,4,394902,"1.5" ,92);
  gradeSheetAdd(c,5,234107,"4.0" ,51);
  gradeSheetAdd(c,5,234107,"4.0" ,63);
  gradeSheetAdd(c,5,234900,"2.0" ,74);
  gradeSheetAdd(c,5,236327,"3.0" ,77);
  gradeSheetAdd(c,5,236334,"3.0" ,64);
  gradeSheetAdd(c,5,236334,"3.0" ,68);
  gradeSheetAdd(c,5,236343,"3.0" ,80);
  gradeSheetAdd(c,5,236360,"3.0" ,71);
  gradeSheetAdd(c,5,324440,"2.0" ,79);
  gradeSheetAdd(c,5,394902,"1.5" ,97);
  gradeSheetAdd(c,6,94591,"3.5" ,86);
  gradeSheetAdd(c,6,234319,"3.0" ,93);
  gradeSheetAdd(c,6,236370,"3.0" ,90);
  gradeSheetAdd(c,6,236504,"3.0" ,89);
  gradeSheetAdd(c,6,236604,"2.0" ,65);
  gradeSheetAdd(c,6,236653,"3.0" ,87);
  gradeSheetAdd(c,6,324290,"2.0" ,73);
  gradeSheetAdd(c,6,394902,"1.5" ,93);
  gradeSheetAdd(c,7,104174,"3.5" ,25);
  gradeSheetAdd(c,7,104174,"3.5" ,90);
  gradeSheetAdd(c,7,236350,"3.0" ,84);
  gradeSheetAdd(c,7,236503,"3.0" ,71);
  gradeSheetAdd(c,7,236603,"2.0" ,71);
  gradeSheetAdd(c,7,236703,"3.0" ,44);
  gradeSheetAdd(c,7,394902,"1.5" ,98);
  gradeSheetRemove(c,4,125001);
  gradeSheetUpdate(c,236703,100);
  ASSERT_TEST(reportBest(c,stdout,-3)==SYS_INVALID_PARAMETER);
  ASSERT_TEST(reportBest(c,stdout,0)==SYS_INVALID_PARAMETER);
  ASSERT_TEST(reportBest(c,stdout,3)==SYS_OK);
  destroySys(c);
  return true;
}

bool test_reportWorst(){
  CourseManager c;
  createSystem(&c);
  studentAdd(c,1, "A" ,"a");
  ASSERT_TEST(reportClean(c,stdout)==SYS_NOBODY_LOGGED_IN);
  studentLogin(c, 1);
  gradeSheetAdd(c,1,104012,"5.5" ,84);
  gradeSheetAdd(c,1,104167,"5.0" ,43);
  gradeSheetAdd(c,1,104167,"5.0" ,71);
  gradeSheetAdd(c,1,234114,"4.0" ,88);
  gradeSheetAdd(c,1,234145,"3.0" ,98);
  gradeSheetAdd(c,1,394808,"1.0" ,92);
  gradeSheetAdd(c,2,104013,"5.5" ,66);
  gradeSheetAdd(c,2,104013,"5.5" ,63);
  gradeSheetAdd(c,2,114071,"3.5" ,98);
  gradeSheetAdd(c,2,234118,"3.0" ,98);
  gradeSheetAdd(c,2,234122,"3.0" ,28);
  gradeSheetAdd(c,2,234122,"3.0" ,96);
  gradeSheetAdd(c,2,234141,"3.0" ,73);
  gradeSheetAdd(c,2,394806,"1.0" ,96);
  gradeSheetAdd(c,3,94412,"4.0" ,80);
  gradeSheetAdd(c,3,104134,"2.5" ,82);
  gradeSheetAdd(c,3,134058,"3.0" ,70);
  gradeSheetAdd(c,3,234218,"3.0" ,75);
  gradeSheetAdd(c,3,234262,"3.0" ,94);
  gradeSheetAdd(c,3,234293,"4.0" ,71);
  gradeSheetAdd(c,3,394902,"1.5" ,96);
  gradeSheetAdd(c,4,125001,"3.0" ,69);
  gradeSheetAdd(c,4,134020,"3.5" ,56);
  gradeSheetAdd(c,4,134020,"3.5" ,76);
  gradeSheetAdd(c,4,234123,"4.5" ,94);
  gradeSheetAdd(c,4,234247,"3.0" ,95);
  gradeSheetAdd(c,4,234267,"3.0" ,60);
  gradeSheetAdd(c,4,234267,"3.0" ,68);
  gradeSheetAdd(c,4,236353,"3.0" ,78);
  gradeSheetAdd(c,4,394902,"1.5" ,92);
  gradeSheetAdd(c,5,234107,"4.0" ,51);
  gradeSheetAdd(c,5,234107,"4.0" ,63);
  gradeSheetAdd(c,5,234900,"2.0" ,74);
  gradeSheetAdd(c,5,236327,"3.0" ,77);
  gradeSheetAdd(c,5,236334,"3.0" ,64);
  gradeSheetAdd(c,5,236334,"3.0" ,68);
  gradeSheetAdd(c,5,236343,"3.0" ,80);
  gradeSheetAdd(c,5,236360,"3.0" ,71);
  gradeSheetAdd(c,5,324440,"2.0" ,79);
  gradeSheetAdd(c,5,394902,"1.5" ,97);
  gradeSheetAdd(c,6,94591,"3.5" ,86);
  gradeSheetAdd(c,6,234319,"3.0" ,93);
  gradeSheetAdd(c,6,236370,"3.0" ,90);
  gradeSheetAdd(c,6,236504,"3.0" ,89);
  gradeSheetAdd(c,6,236604,"2.0" ,65);
  gradeSheetAdd(c,6,236653,"3.0" ,87);
  gradeSheetAdd(c,6,324290,"2.0" ,73);
  gradeSheetAdd(c,6,394902,"1.5" ,93);
  gradeSheetAdd(c,7,104174,"3.5" ,25);
  gradeSheetAdd(c,7,104174,"3.5" ,90);
  gradeSheetAdd(c,7,236350,"3.0" ,84);
  gradeSheetAdd(c,7,236503,"3.0" ,71);
  gradeSheetAdd(c,7,236603,"2.0" ,71);
  gradeSheetAdd(c,7,236703,"3.0" ,44);
  gradeSheetAdd(c,7,394902,"1.5" ,98);
  gradeSheetRemove(c,4,125001);
  gradeSheetUpdate(c,236703,100);
  ASSERT_TEST(reportWorst(c,stdout,-3)==SYS_INVALID_PARAMETER);
  ASSERT_TEST(reportWorst(c,stdout,0)==SYS_INVALID_PARAMETER);
  ASSERT_TEST(reportWorst(c,stdout,3)==SYS_OK);
  destroySys(c);
  return true;
}

bool test_reportReference(){
  CourseManager c;
  createSystem(&c);
  studentAdd(c,111111118,"Ariel","Wershal") ;
  studentAdd(c,222222226,"Eran","Channover");
  ASSERT_TEST(reportClean(c,stdout)==SYS_NOBODY_LOGGED_IN);
  studentLogin(c,111111118);
  friendRequest(c,222222226);
  studentLogout(c);
  studentLogin(c,222222226 );
  handleRequest(c,111111118 ,"accept");
  gradeSheetAdd(c, 1, 234122,"3.0", 100);
  studentLogout(c);
  studentLogin(c,111111118);
  gradeSheetAdd(c,1,104012,"5.5" ,84);
  gradeSheetAdd(c,1,104167,"5.0" ,43);
  gradeSheetAdd(c,1,104167,"5.0" ,71);
  gradeSheetAdd(c,1,234114,"4.0" ,88);
  gradeSheetAdd(c,1,234145,"3.0" ,98);
  gradeSheetAdd(c,1,394808,"1.0" ,92);
  gradeSheetAdd(c,2,104013,"5.5" ,66);
  gradeSheetAdd(c,2,104013,"5.5" ,63);
  gradeSheetAdd(c,2,114071,"3.5" ,98);
  gradeSheetAdd(c,2,234118,"3.0" ,98);
  gradeSheetAdd(c,2,234122,"3.0" ,28);
  gradeSheetAdd(c,2,234122,"3.0" ,96);
  gradeSheetAdd(c,2,234141,"3.0" ,73);
  gradeSheetAdd(c,2,394806,"1.0" ,96);
  gradeSheetAdd(c,3,94412,"4.0" ,80);
  gradeSheetAdd(c,3,104134,"2.5" ,82);
  gradeSheetAdd(c,3,134058,"3.0" ,70);
  gradeSheetAdd(c,3,234218,"3.0" ,75);
  gradeSheetAdd(c,3,234262,"3.0" ,94);
  gradeSheetAdd(c,3,234293,"4.0" ,71);
  gradeSheetAdd(c,3,394902,"1.5" ,96);
  gradeSheetAdd(c,4,125001,"3.0" ,69);
  gradeSheetAdd(c,4,134020,"3.5" ,56);
  gradeSheetAdd(c,4,134020,"3.5" ,76);
  gradeSheetAdd(c,4,234123,"4.5" ,94);
  gradeSheetAdd(c,4,234247,"3.0" ,95);
  gradeSheetAdd(c,4,234267,"3.0" ,60);
  gradeSheetAdd(c,4,234267,"3.0" ,68);
  gradeSheetAdd(c,4,236353,"3.0" ,78);
  gradeSheetAdd(c,4,394902,"1.5" ,92);
  gradeSheetAdd(c,5,234107,"4.0" ,51);
  gradeSheetAdd(c,5,234107,"4.0" ,63);
  gradeSheetAdd(c,5,234900,"2.0" ,74);
  gradeSheetAdd(c,5,236327,"3.0" ,77);
  gradeSheetAdd(c,5,236334,"3.0" ,64);
  gradeSheetAdd(c,5,236334,"3.0" ,68);
  gradeSheetAdd(c,5,236343,"3.0" ,80);
  gradeSheetAdd(c,5,236360,"3.0" ,71);
  gradeSheetAdd(c,5,324440,"2.0" ,79);
  gradeSheetAdd(c,5,394902,"1.5" ,97);
  gradeSheetAdd(c,6,94591,"3.5" ,86);
  gradeSheetAdd(c,6,234319,"3.0" ,93);
  gradeSheetAdd(c,6,236370,"3.0" ,90);
  gradeSheetAdd(c,6,236504,"3.0" ,89);
  gradeSheetAdd(c,6,236604,"2.0" ,65);
  gradeSheetAdd(c,6,236653,"3.0" ,87);
  gradeSheetAdd(c,6,324290,"2.0" ,73);
  gradeSheetAdd(c,6,394902,"1.5" ,93);
  gradeSheetAdd(c,7,104174,"3.5" ,25);
  gradeSheetAdd(c,7,104174,"3.5" ,90);
  gradeSheetAdd(c,7,236350,"3.0" ,84);
  gradeSheetAdd(c,7,236503,"3.0" ,71);
  gradeSheetAdd(c,7,236603,"2.0" ,71);
  gradeSheetAdd(c,7,236703,"3.0" ,44);
  gradeSheetAdd(c,7,394902,"1.5" ,98);
  gradeSheetRemove(c,4,125001);
  gradeSheetUpdate(c,236703,100);
  ASSERT_TEST(reportReference(c,stdout,394902,-6)==SYS_INVALID_PARAMETER);
  ASSERT_TEST(reportReference(c,stdout,394902,0)==SYS_INVALID_PARAMETER);
  ASSERT_TEST(reportReference(c,stdout,234122, 3)==SYS_OK);
  destroySys(c);
  return true;
}

bool test_reportFacultyRequest(){
  CourseManager c;
  createSystem(&c);
  studentAdd(c,1, "A" ,"a");
  ASSERT_TEST(reportFacultyRequest(c, stdout, 104012,"cancel_course") == SYS_NOBODY_LOGGED_IN);
  studentLogin(c, 1);
  gradeSheetAdd(c,1,104012,"5.5",84);
  gradeSheetAdd(c,1,104167,"5.0",43);
  gradeSheetAdd(c,1,104167,"5.0",71);
  gradeSheetAdd(c,1,234114,"4.0",88);
  ASSERT_TEST(reportFacultyRequest(c, stdout, 104012,"cancel_course") == SYS_OK);
  ASSERT_TEST(reportFacultyRequest(c, stdout, 12, "register_course") == SYS_OK);
  ASSERT_TEST(reportFacultyRequest(c, stdout, 104167, "remove_course") == SYS_OK);
  ASSERT_TEST(reportFacultyRequest(c, stdout, 11, "remove_course") == SYS_COURSE_DOES_NOT_EXIST);
  ASSERT_TEST(reportFacultyRequest(c, stdout, 104012,"cancel_coursE") == SYS_INVALID_PARAMETER);
  destroySys(c);
  return true;
}


int main() {
  RUN_TEST(test_createSystem);
  RUN_TEST(test_studentAdd);
  //RUN_TEST(test_handleId);
  RUN_TEST(test_studentRemove);
  RUN_TEST(test_studentLogin);
  RUN_TEST(test_studentLogout);
  RUN_TEST(test_getOnlineStudent);
  RUN_TEST(test_friendRequest);
  RUN_TEST(test_handleRequst);
  RUN_TEST(test_getSetStudents);
  RUN_TEST(test_handleAccept);
  RUN_TEST(test_studentUnfriend);
  RUN_TEST(test_gradeSheetAdd);
  RUN_TEST(test_gradeSheetRemove);
  RUN_TEST(test_gradeSheetUpdate);
  RUN_TEST(test_repurtFull);
  RUN_TEST(test_reportClean);
  RUN_TEST(test_reportBest);
  RUN_TEST(test_reportWorst);
  RUN_TEST(test_reportReference);
  RUN_TEST(test_reportFacultyRequest);

  return 0;
}