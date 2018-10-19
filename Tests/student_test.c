#include <stdio.h>
#include "../Headers/set.h"
#include "../Headers/list.h"
#include "../Headers/Student.h"
#include "../Headers/CourseManager.h"
#include "../Headers/FriendRequest.h"
#include <stdbool.h>
#include <string.h>


#define ASSERT_TEST(b) do { \
        if (!(b)) { \
                printf("\nAssertion failed"); \
                return false; \
        } \
} while (0)

/**
 * Macro used for running a test from the main function
 */
#define RUN_TEST(test) do { \
        printf("Running "#test"... "); \
        if (test()) { \
            printf("[OK]\n");\
        } else { \
        	printf("[Failed]\n"); \
        } \
} while(0)



void displayStudent(Student student){
  printf("\n");
  if (student == NULL) printf("student is NULL\n");
  printf("students %d friends are: \n", getStudentId(student));
  SET_FOREACH(Friend , i, getSetFriend(student)){
    printf("%d\n", getFriendId(i));
  }
  printf("students friend requests are: \n");
  SET_FOREACH(FriendRequest , i, getSetFriendReq(student)){
    printf("%d\n", getFriendReqId(i));
  }
}

void displayFriends(Set friends) {
  printf("\n");
  if (friends == NULL) printf("friends is NULL\n");
  printf("the friends are: \n");
  SET_FOREACH(Friend, i, friends) {
    printf("%d \n", getFriendId(i));
  }
}

bool test_create(){

  Student student ;
  student= createStudent(1, NULL, "levy");
  ASSERT_TEST(student==NULL);

  student= createStudent(002, "dina", "kes");
  ASSERT_TEST(student!=NULL);
  destroyStudent(student);

  student= createStudent(002, "dina", NULL);
  ASSERT_TEST(student==NULL);


  return true;
}


bool test_getStudent(){

  Set Students=setCreate(setCopyStudent,setFreeStudent,setCmpStudent);
  Student  student= createStudent(1, "a", "b" );


  Student student1=createStudent(2, "b", "c");
  setAdd(Students,student);
  setAdd(Students,student1);

  //good casees
  Student result= getStudent(Students, 1);
  ASSERT_TEST(result!=NULL);

  result= getStudent(Students, 2);
  ASSERT_TEST(result!=NULL);

  //bad cases
  result= getStudent(Students, 3);
  ASSERT_TEST(result==NULL);

  result= getStudent(NULL, 3);
  ASSERT_TEST(result==NULL);


  destroyStudent(student);
  setDestroy(Students);
  destroyStudent(student1);

  return true;
}

bool test_makeOnline(){
  Student  student= createStudent(1, "a", "b");
  Student student1= createStudent(2, "b", "c");
  //good cases
  StudentResult result=makeOnline(student);
  ASSERT_TEST(result==STUDENT_OK);

  result=makeOnline(student1);
  ASSERT_TEST(result==STUDENT_OK);

  //bad cases
  result=makeOnline(student);
  ASSERT_TEST(result==STUDENT_ALREADY_LOGGED_IN);

  result=makeOnline(student1);
  ASSERT_TEST(result==STUDENT_ALREADY_LOGGED_IN);

  destroyStudent(student);
  destroyStudent(student1);
  return true;
}

bool test_makeoffline(){
  Student  student= createStudent(1, "a", "b");
  Student student1= createStudent(2, "b", "c");
  makeOnline(student);
  makeOnline(student1);
  //good case
  StudentResult result=makeOffline(student);
  ASSERT_TEST(result==STUDENT_OK);

  result=makeOffline(student1);
  ASSERT_TEST(result==STUDENT_OK);

  //bad cases
  result=makeOffline(student);
  ASSERT_TEST(result==STUDENT_ALREADY_LOGGED_OUT);

  result=makeOffline(student1);
  ASSERT_TEST(result==STUDENT_ALREADY_LOGGED_OUT);
  destroyStudent(student);
  destroyStudent(student1);
  return true;
}

bool test_getStatus (){
  Student  student= createStudent(1, "a", "b");
  Student student1= createStudent(2, "b", "c");
  Status result = getStatus(student);
  ASSERT_TEST(result == offline);
  result = getStatus(student1);
  ASSERT_TEST(result == offline);
  makeOnline(student);
  result= getStatus(student);
  ASSERT_TEST(result == online);
  makeOnline(student1);
  result = getStatus(student1);
  ASSERT_TEST(result == online);
  makeOffline(student);
  result=getStatus(student);
  ASSERT_TEST(result == offline);
  destroyStudent(student);
  destroyStudent(student1);
  return true;
}


/*bool test_addfriend(){
  Student student= createStudent(1, "a", "b");

  int flag=0;
  Friend aFriend = createFriend(2,"c","d");
  ASSERT_TEST(studentAddFriend(NULL, student, 0) ==STUDENT_OK);     ///why do we check this
  Set friends=getSetFriend(student);
  SET_FOREACH(Friend , f ,friends){
    if( getFriendId(f)==2){
      flag=1;
      break;
    }
    return false;
  }
  ASSERT_TEST(flag==1);
  destroyFriend(aFriend);
  destroyStudent(student);
  return true;
}*/



bool test_studentAddFriend(){
  Set Students=setCreate(setCopyStudent,setFreeStudent,setCmpStudent);
  Student student= createStudent(1, "a", "b" );
  Student student1=createStudent(2, "c", "d");
  setAdd(Students,student);
  setAdd(Students,student1);
 // Friend aFriend = createFriend(3,"e","h");
  ASSERT_TEST(getStudent(Students, 3) == NULL);  ///checks case student_not_exixts
  Student student_f = createStudent(3, "e", "h");
  setAdd (Students, student_f);
  ASSERT_TEST(studentAddFriend(Students, student, 3) == STUDENT_OK);
  int flag=0;
  Set friends=getSetFriend(student);
  SET_FOREACH(Friend , f ,friends){
    if( getFriendId(f)==3){
      flag=1;
      break;
    }
    return false;
  }
  ASSERT_TEST(flag == 1);
  ASSERT_TEST(studentAddFriend(Students, student, 3) == STUDENT_ALREADY_FRIENDS);
  //destroyFriend(aFriend);
  destroyStudent(student);
  destroyStudent(student1);
  destroyStudent(student_f);
  setDestroy(Students);
  return true;

}


bool test_getFriend(){
  Set friends = setCreate(setCopyFriend, setFreeFriend, setCompareFriend);
  ASSERT_TEST(friends != NULL);
  Friend f1 = createFriend( 1, "a", "b", 0);
  Friend f2 = createFriend( 2, "c", "d", 0);
  Friend f3 = createFriend( 3, "e", "f", 0);
  ASSERT_TEST(f1 != NULL);
  ASSERT_TEST(f2 != NULL);
  ASSERT_TEST(f3 != NULL);
  SetResult result = setAdd(friends, f1);
  ASSERT_TEST(result == SET_SUCCESS);
  result = setAdd(friends, f2);
  ASSERT_TEST(result == SET_SUCCESS);
  Friend g1 = getFriend(friends, 1);
  ASSERT_TEST(getFriendId(f1) == getFriendId(g1));
  Friend g2 = getFriend(friends, 2);
  ASSERT_TEST(getFriendId(f2) == getFriendId(g2));
  ASSERT_TEST(getFriend(friends, 3) == NULL);
  setDestroy(friends);
  destroyFriend(f1);
  destroyFriend(f2);
  destroyFriend(f3);
  return true;

}

bool test_getSetFriend(){
  Student student1= createStudent(1, "a", "b" );
  ASSERT_TEST( getSetFriend(student1) != NULL);
  destroyStudent(student1);
  return true;
}

bool test_getStudentId(){
  Student student1= createStudent(1, "a", "b" );
  ASSERT_TEST(getStudentId(student1) == 1);
  destroyStudent(student1);
  return true;
}

bool test_getSetFriendReq(){
  Student student1= createStudent(1, "a", "b" );
  ASSERT_TEST( getSetFriendReq(student1) != NULL);
  destroyStudent(student1);
  return true;
}

bool test_getFirstName(){
  Student student1= createStudent(1, "abc", "DEF" );
  char *fname = getFirstName(student1);
  ASSERT_TEST( strcmp (fname, "abc") == 0);
  ASSERT_TEST(getFirstName(NULL) == NULL);
  destroyStudent(student1);
  return true;
}


bool test_getLastName(){
  Student student1= createStudent(1, "abc", "DEF" );
  char *lname = getLastName(student1);
  ASSERT_TEST( strcmp (lname, "DEF") == 0);
  ASSERT_TEST(getLastName(NULL) == NULL);
  destroyStudent(student1);
  return true;
}

bool test_alreadyFriends(){
  Set Students=setCreate(setCopyStudent,setFreeStudent,setCmpStudent);
  Student student1= createStudent(1, "a", "b" );
  Student student2=createStudent(2, "c", "d");
  setAdd(Students, student1);
  setAdd(Students, student2);
  ASSERT_TEST(alreadyFriends(student1, 2) == 0);
  studentAddFriend(Students, student1, 2);
  ASSERT_TEST(alreadyFriends(student1, 2) == 1);
  ASSERT_TEST(alreadyFriends(student1, 1) == 1);
  destroyStudent(student1);
  destroyStudent(student2);
  setDestroy(Students);
  return true;
}

bool test_requestExist(){
  CourseManager c;
  createSystem(&c);
  studentAdd(c,1, "A" ,"a");
  studentAdd(c,2, "B" ,"b");
  studentAdd(c,3, "C" ,"c");
  Student student = getStudent(getSetStudents(c), 1);
  studentLogin(c, 3);
  friendRequest(c,1);
  studentLogout(c);
  ASSERT_TEST(requestExist(student,3) == 1);
  ASSERT_TEST(requestExist(student,2) == 0);
  destroySys(c);
  return true;
}

bool test_removeFriendReq(){
  CourseManager c;
  createSystem(&c);
  studentAdd(c,1, "A" ,"a");
  studentAdd(c,2, "B" ,"b");
  studentAdd(c,3, "C" ,"c");
  Student student = getStudent(getSetStudents(c), 1);
  studentLogin(c, 3);
  friendRequest(c,1);
  studentLogout(c);
  ASSERT_TEST(requestExist(student, 3) == 1 );
  ASSERT_TEST(removeFriendReq(student, 3) == STUDENT_OK);
  ASSERT_TEST(requestExist(student, 3) == 0 );
  ASSERT_TEST(removeFriendReq(student, 3) == STUDENT_REQ_NOT_EXIST);
  ASSERT_TEST(removeFriendReq(student, 2) == STUDENT_REQ_NOT_EXIST);
  destroySys(c);
  return true;
}

bool test_studentRemoveFriend(){
  Set Students=setCreate(setCopyStudent,setFreeStudent,setCmpStudent);
  Student student1= createStudent(1, "a", "b" );
  Student student2=createStudent(2, "c", "d");
  Student student3=createStudent(3, "e", "f");
  setAdd(Students,student1);
  setAdd(Students,student2);
  setAdd(Students,student3);
  StudentResult result = studentAddFriend(Students, getStudent(Students, 1), 2);
  ASSERT_TEST(result == STUDENT_OK);
  ASSERT_TEST(studentRemoveFriend(NULL, 2) == STUDENT_NULL_ARG);
  ASSERT_TEST(studentRemoveFriend(getStudent(Students, 1), 3) == STUDENT_NOT_FRIENDS);
  ASSERT_TEST(studentRemoveFriend(getStudent(Students, 1), 1) == STUDENT_NOT_FRIENDS);
  ASSERT_TEST(studentRemoveFriend(getStudent(Students, 1), 2) == STUDENT_OK);
  destroyStudent(student1);
  destroyStudent(student2);
  destroyStudent(student3);
  setDestroy(Students);
  return true;
}


bool test_studentAddGrade(){
  Student student1= createStudent(1, "a", "b" );
  ASSERT_TEST(studentAddGrade(student1,1,234122,"3",98)==STUDENT_OK);
  ASSERT_TEST(listGetSize(getGradeList(student1))==1);
  destroyStudent(student1);
  return true;

}


bool test_studentRemoveGrade(){
  Student student1= createStudent(1, "a", "b" );
  ASSERT_TEST(studentAddGrade(student1,1,234122,"3",98)==STUDENT_OK);
  ASSERT_TEST(studentRemoveGrade(student1,1,234122)==STUDENT_OK);
  ASSERT_TEST(listGetSize(getGradeList(student1))==0);
  destroyStudent(student1);
  return true;

}


bool test_studentUpdateCourseLast(){
  Student student1= createStudent(1, "a", "b" );
  ASSERT_TEST(studentAddGrade(student1,1,234122,"3",98)==STUDENT_OK);
  ASSERT_TEST(studentAddGrade(student1,1,234122,"3",100)==STUDENT_OK);
  ASSERT_TEST(studentAddGrade(student1,2,234122,"3",100)==STUDENT_OK);
  ASSERT_TEST(studentAddGrade(student1,2,234122,"3",100)==STUDENT_OK);
  ASSERT_TEST(studentRemoveGrade(student1,1,234122)==STUDENT_OK);
  ASSERT_TEST(courseGetCourseLastSem(getCourse(student1,234122))==2);
  ASSERT_TEST(studentRemoveGrade(student1,2,234122)==STUDENT_OK);
  ASSERT_TEST(studentRemoveGrade(student1,2,234122)==STUDENT_OK);
  ASSERT_TEST(courseGetCourseLastSem(getCourse(student1,234122))==1);
  LIST_FOREACH(Grade,g,getGradeList(student1)){
    studentPrintGradeInfo(student1,stdout,g);
  }
  ASSERT_TEST(studentRemoveGrade(student1,1,234122)==STUDENT_OK);
  ASSERT_TEST(courseGetCourseLastSem(getCourse(student1,234122))==-1);
  destroyStudent(student1);
  return true;
}

bool test_studentUpdateGrade(){
  Student student1= createStudent(1, "a", "b" );
  ASSERT_TEST(studentAddGrade(student1,1,234122,"3",98)==STUDENT_OK);
  ASSERT_TEST(studentAddGrade(student1,1,234122,"3",100)==STUDENT_OK);
  ASSERT_TEST(studentUpdateGrade(student1,234122,50)==STUDENT_OK);
  LIST_FOREACH(Grade , g , getGradeList(student1)){
    if(gradeGetGrade(g)==50){
      destroyStudent(student1);
      return true;
    }
  }
  destroyStudent(student1);
  return false;

}

bool test_studentPrintBest(){
  Student student1= createStudent(1, "a", "b" );

  ASSERT_TEST(studentAddGrade(student1,1,11,"3",10)==STUDENT_OK);
  ASSERT_TEST(studentAddGrade(student1,1,22,"3",20)==STUDENT_OK);
  ASSERT_TEST(studentAddGrade(student1,1,33,"3",30)==STUDENT_OK);
  ASSERT_TEST(studentAddGrade(student1,1,44,"3",40)==STUDENT_OK);
  ASSERT_TEST(studentAddGrade(student1,1,390000,"3",80)==STUDENT_OK);
  ASSERT_TEST(studentAddGrade(student1,1,390000,"3",20)==STUDENT_OK);
  ASSERT_TEST(studentAddGrade(student1,2,399000,"3",50)==STUDENT_OK);
  ASSERT_TEST(studentAddGrade(student1,1,44,"3",40)==STUDENT_OK);
  studentPrintBest(student1,stdout,3);
  studentPrintBest(student1,stdout,5);
  destroyStudent(student1);
  return true;
}


int main(){
  RUN_TEST(test_create);
  RUN_TEST(test_getStudent);
  RUN_TEST(test_makeOnline);
  RUN_TEST(test_makeoffline);
  RUN_TEST(test_getStatus);
  //RUN_TEST(test_addfriend);
  RUN_TEST(test_studentAddFriend);
  RUN_TEST(test_getFriend);
  RUN_TEST(test_getSetFriend);
  RUN_TEST(test_getStudentId);
  RUN_TEST(test_getSetFriendReq);
  RUN_TEST(test_getFirstName);
  RUN_TEST(test_getLastName);
  RUN_TEST(test_alreadyFriends);
  RUN_TEST(test_requestExist);
  RUN_TEST(test_removeFriendReq);
  RUN_TEST(test_studentRemoveFriend);
  RUN_TEST(test_studentAddGrade);
  RUN_TEST(test_studentRemoveGrade);
  RUN_TEST(test_studentUpdateGrade);
  RUN_TEST(test_studentUpdateCourseLast);
  RUN_TEST(test_studentPrintBest);
  return 0;
}

