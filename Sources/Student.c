//
// Created by Dina on 15-Dec-17.
//

#include "../Headers/list.h"
#include "../Headers/Friend.h"
#include "../Headers/FriendRequest.h"
#include "../Headers/Grade.h"
#include "../Headers/Student.h"
#include "../Headers/mtm_ex3.h"
#include "../Headers/Course.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>


struct student_t{
  int id;
  char *first_name;
  char *last_name;
  Status status;
  Set friends;
  Set friendRequests;
  List grades;
  Set Courses; //added
};

///======================STATIC FUNCTIONS=====================================
static int calcEffectiveSportPts(Student student , int *e_grd) ;

/**
 * The number of failed course points, multiplied by 2.
*     A failed course is a course with a grade lower than 55. Courses failed
*     multiple times are counted multiple times.
 * @param grades
 * @param semester
 * @return
 */
static int calcFailedPointsForSem(List grades, int semester);

/**
 * this function preapare the points of the given course for printing
 * maybe should be static function.
 * this function uses "atof"(converts string to float)
 * @param points
 * @return The number of course points, multiplied by 2
 */
static int preparePointsForPrint(char* points);

/**
 *
 * @param student
 * @param semester
 * @param e_grd - this will hold the total effective grade .
 * @return The sum of the effective course grades, when
*     each grade is multiplied by the number of course points, multiplied by 2.
 */
static int calcEffectivePointsForSem(Student student, int semester, int *e_grd);

/**
 *
 *
 * @param student
 * @param sem
 * @param c_id
 * @param e_grd
 * @return The number of total effective course points,
*     multiplied by 2. Effective points are points of courses whose grade counts.
*     A grade doesn't count if another grade of the same course id appears later
*     in the semester.
 */
static int calcEffectivePointsForCourse(Student student,int sem,int c_id,
                                        int *e_grd);

/**
 * the number of total course points, multiplied by 2.
 *     Courses taken multiple times are counted multiple times.
 * @param grades
 * @param semester
 * @return
 */
static int calcTotalPointsForSem(List grades, int semester);

static int calcTotalEffectivePtsAndGrade(Student student, int *e_grd) ;

static bool isBetween(ListElement element, ListFilterKey key) ;

static List createFilteredList(List listOfGrades) ;

static int calcEffectivePointsForSemN2(Student student,List grades, int semester, int *e_grd);

static bool isSportCourse(ListElement element, ListFilterKey key) ;

static List createFilteredList2(List listOfGrades) ;

static List makeList(Student student);

static int closerTo(ListElement num1, ListElement num2, ListSortKey value);

static void sortCourses(List listOfInts) ;

static int printCleanSportGrade(Student student,FILE *output,int c_id,int *_grd,
                                int flag, List grades);

static int printEffectivePointsForCourse(Student student,FILE* output,
                                         int semester, int c_id, int *e_grd);

static int higherThan(ListElement element1, ListElement element2 ,
                      ListSortKey value);
static void sortFriends(List listOfFriends);

static int FindMaxGrade(Student student, int course_id);



///=====================GENERIC FUNCTIONS=====================================
SetElement setCopyStudent(SetElement element) {
  if (element == NULL) return NULL;
  Student student = (Student) element;
  Student
      new = createStudent(student->id, student->first_name, student->last_name);
  if (new == NULL) return NULL;
  setDestroy(new->friends);
  new->friends = setCopy(student->friends);
  if (new->friends == NULL) {
    free(new->first_name);
    free(new->last_name);
    setDestroy(new->friends);
    setDestroy(new->friendRequests);
    listDestroy(new->grades);
  }
  setDestroy(new->friendRequests);
  new->friendRequests = setCopy(student->friendRequests);
  if (new->friendRequests == NULL) {
    free(new->first_name);
    free(new->last_name);
    setDestroy(new->friends);
    setDestroy(new->friendRequests);
    listDestroy(new->grades);
  }
  listDestroy(new->grades);
  new->grades = listCopy(student->grades);
  if (new->grades == NULL) {
    free(new->first_name);
    free(new->last_name);
    setDestroy(new->friends);
    setDestroy(new->friendRequests);
    listDestroy(new->grades);
  }
  setDestroy(new->Courses);
  new->Courses = setCopy(student->Courses);
  if (new->Courses == NULL) {
    free(new->first_name);
    free(new->last_name);
    setDestroy(new->friends);
    setDestroy(new->Courses);
    setDestroy(new->friendRequests);
    listDestroy(new->grades);
  }
    return new;
}


void setFreeStudent(SetElement element){
  Student student = (Student)element;
  destroyStudent(student);
}

int setCmpStudent(SetElement element1, SetElement element2){
  Student student1 = (Student)element1;
  Student student2 = (Student)element2;
  return student1->id - student2->id;
}

///=========================================================================

///====================STATIC FUNCTIONS======================================


static StudentResult handleName(Student s, char *first_name, char *last_name){
  s->first_name = malloc(strlen(first_name)+1);
  if (s->first_name == NULL){
    free(s);
    return STUDENT_MEMORY_ERROR;
  }
  strcpy(s->first_name, first_name);
  s->last_name = malloc(strlen(last_name)+1);
  if (s->last_name == NULL) {
    free(s->first_name);
    free(s);
    return STUDENT_MEMORY_ERROR;
  }
  strcpy(s->last_name, last_name);
  return STUDENT_OK;
}

static Student handleFields( Student student){
  student->Courses=setCreate(copyCourse ,freeCourse , cmpCourse);
  if(student->Courses == NULL) {
    free(student->first_name);
    free(student->last_name);
    free(student);
    return NULL;
  }
  student->friends = setCreate(setCopyFriend, setFreeFriend, setCompareFriend);
  if(student->friends == NULL) {
    free(student->first_name);
    free(student->last_name);
    free(student);
    setDestroy(student->Courses);
    return NULL;
  }
  student->friendRequests=setCreate(copyFriendReq, freeFriendReq, cmpFriendReq);
  if (student->friendRequests == NULL){
    free(student->first_name);
    free(student->last_name);
    setDestroy(student->friends);
    free(student);
    return NULL;
  }
  student->grades = listCreate(copyGrade, freeGrade);
  if (student->grades == NULL){
    free(student->first_name);
    free(student->last_name);
    setDestroy(student->friends);
    setDestroy(student->friendRequests);
    free(student);
    return NULL;
  }
  return student;
}

///===========================================================================

Student createStudent (int id, char *first_name, char *last_name){
 if(  first_name == NULL || last_name == NULL) return NULL;
  Student student = malloc(sizeof(*student));
  if( student == NULL ) return NULL;
  student->id=id;
  StudentResult result = handleName(student, first_name, last_name);
  if ( result != STUDENT_OK) {
    free(student);
    return NULL;
  }
  handleFields(student);
  student->status = offline;
  return student;
}

void destroyStudent(Student student){
  if(!student) return;
  free(student->first_name);
  free(student->last_name);
  setDestroy(student->friends);
  setDestroy(student->Courses);
  setDestroy(student->friendRequests);
  listDestroy(student->grades);
  free(student);
}


int getStudentId( Student student){
  if(!student) return -1;
  return student->id;
}

StudentResult makeOnline( Student student){
  if(!student) return STUDENT_NULL_ARG;
  if( student->status == online){
    return STUDENT_ALREADY_LOGGED_IN;
  }
  student->status=online;
  return STUDENT_OK;
}

StudentResult makeOffline( Student student){
  if(!student) return STUDENT_NULL_ARG;
  if( student->status == offline){
    return STUDENT_ALREADY_LOGGED_OUT;
  }
  student->status=offline;
  return STUDENT_OK;
}

Status getStatus(Student student){
  return student->status;
}

Friend getFriend(Set friends, int id) {
  if (!friends) return  NULL;
  SET_FOREACH(Friend , i , friends) {
    if (getFriendId(i) == id) {
      return i;
    }
  }
  return NULL;
}

Set getSetFriend(  Student student){
  return student->friends;
}


Set getSetFriendReq(  Student student){
  return student->friendRequests;
}

char *getFirstName(Student student){
  if(student!=NULL){
    return student->first_name;
  }
  return NULL;
}

char *getLastName(Student student){
  if(student!=NULL){
    return student->last_name;
  }
  return NULL;
}

Student getStudent(Set students, int id) {
  if (!students) return  NULL;
  SET_FOREACH(Student , i , students) {
    if (getStudentId(i) == id) {
      return i;
    }
  }
  return NULL;
}

bool alreadyFriends(Student student, int other_id) {
  Set friends = getSetFriend(student);
  Friend afriend = getFriend(friends, other_id);
  int student_id = getStudentId(student);
  if (afriend != NULL || student_id == other_id) {
    return true;
  }
  return false;
}

bool requestExist(Student student , int other_id){
  Set friend_req = getSetFriendReq(student);
  FriendRequest request = createFriendReq(other_id);
  assert(request);
  if (setIsIn(friend_req, request) != true) {
    destroyFriendReq(request);
    return false; // if not requested
  }
  destroyFriendReq(request);
  return true;
}

StudentResult removeFriendReq(Student student , int other_id){
  Set friend_req = getSetFriendReq(student);
  FriendRequest request = createFriendReq(other_id);
  assert(request);
  if(requestExist(student,other_id)){
    setRemove(friend_req,request);
    destroyFriendReq(request);
    return STUDENT_OK;
  }
  destroyFriendReq(request);
  return STUDENT_REQ_NOT_EXIST;
}

//version 2
StudentResult studentAddFriend(Set students, Student student, int id) {
  if (alreadyFriends(student,id)){
    return STUDENT_ALREADY_FRIENDS;
  }
  Student student1= getStudent(students, id);
  if(!student1)return STUDENT_NOT_EXISTS;
  char *fname=getFirstName(student1);
  char *lname=getLastName(student1);
  if (fname != NULL && student != NULL && lname != NULL) {
    Friend new = createFriend(id, fname, lname, 0);
    if (new != NULL) {
      if (setAdd(student->friends, new) == SET_SUCCESS) {
        destroyFriend(new);
        return STUDENT_OK;
      }
    }
    destroyFriend(new);
  }
  return STUDENT_NULL_ARG;
}


StudentResult studentRemoveFriend(Student student ,int other_id){
  if(!student) return STUDENT_NULL_ARG;
  Friend aFriend=getFriend(student->friends , other_id);
  if(!aFriend || other_id==student->id) return STUDENT_NOT_FRIENDS;
 if( setRemove(student->friends,aFriend)!=SET_SUCCESS){
   return STUDENT_NOT_EXISTS;
 }
  return STUDENT_OK;
}
Course getCourse(Student student , int c_id){
  SET_FOREACH(Course , c , student->Courses){
    if(courseGetCourseId(c)==c_id ){
      return c;
    }
  }
  return NULL;
}

StudentResult studentAddCourse(Student student,
                               int c_id,
                               int semester,
                               char *pts) {
  if(!student) return STUDENT_NULL_ARG;
  Course tmp_c= createCourse(c_id, semester);
  setAdd(student->Courses,tmp_c);
  destroyCourse(tmp_c);
  return STUDENT_OK;
}

void studentUpdateCourseLast(Student student, int c_id){
  int max=0;
  List tmp=listCopy(student->grades);
  LIST_FOREACH(Grade, grd , tmp){
    if(gradeGetCourseId(grd)==c_id){
      if(gradeGetSemester(grd) > max){
        max=gradeGetSemester(grd);
      }
    }
  }
  Course course=getCourse(student,c_id);
  if(!max){
    setRemove(student->Courses,course);
    listDestroy(tmp);
    return;
  }
  courseUpdateLastSem(course,max);
  listDestroy(tmp);
}

StudentResult studentAddGrade(Student stu,int sem,int c_id,char* pts,int grd){
  if(!stu) return STUDENT_NULL_ARG;
  if(!pts)return STUDENT_NULL_ARG;
  Grade grade1=createGrade(sem , c_id , pts , grd );
  listInsertLast(stu->grades , grade1);
  destroyGrade(grade1);
  Course course=getCourse(stu , c_id);
  if(!course){
    studentAddCourse(stu, c_id, sem, pts);
  }
  studentUpdateCourseLast(stu,c_id);
  return STUDENT_OK;
}

StudentResult studentRemoveGrade(Student student , int semester,int course_id) {
  if (!student) return STUDENT_NULL_ARG;
  int counter = 0;
  LIST_FOREACH(Grade, g, student->grades) {
    if (gradeGetCourseId(g) != course_id)continue;
    if (gradeGetSemester(g) == semester) {
      counter++;
    }
  }
  if (!counter)
    return STUDENT_COURSE_NOT_EXIST;
  LIST_FOREACH(Grade, j, student->grades) {
    if (gradeGetCourseId(j) != course_id)continue;
    if (gradeGetSemester(j) == semester) {
      counter--;
      if (!counter) {
        listRemoveCurrent(student->grades);
        studentUpdateCourseLast(student, course_id);
        return STUDENT_OK;
      }
    }
  }
  return STUDENT_OK;
}

List getGradeList(Student student){
  if(!student)return NULL;
  return student->grades;
}



StudentResult studentUpdateGrade(Student student ,int course_id , int new_g){
  if (!student) return STUDENT_NULL_ARG;
  int counter = 0;
  Course course=getCourse(student,course_id);
  if(!course)return STUDENT_COURSE_NOT_EXIST;
  int max_sem=courseGetCourseLastSem(course);
  LIST_FOREACH(Grade, i, student->grades) {
    if (gradeGetCourseId(i) == course_id) {
      if (gradeGetSemester(i) == max_sem) {
        max_sem = gradeGetSemester(i);
        counter++;
        continue;
      }
    }
  }
  if (!counter)
    return STUDENT_COURSE_NOT_EXIST;
  LIST_FOREACH(Grade, j, student->grades) {
    if (gradeGetCourseId(j) == course_id) {
      if (gradeGetSemester(j) == max_sem) {
        counter--;
        if (!counter) {
          gradeUpdateGrade(j, new_g);
          //courseUpdateLastSem(getCourse(student, course_id),
                             // gradeGetSemester(i));
          return STUDENT_OK;
        }
      }
    }
  }
  return STUDENT_OK;
}

 int studentGetMaxSem(Student student){
  if(!student)return -1;
  int max=0;
  LIST_FOREACH(Grade , i , student->grades){
    if(gradeGetSemester(i)>max){
      max= gradeGetSemester(i);
    }
  }
  return max;
}


void studentPrintStuInfo(Student student, FILE *output){
  if(!student)return ;
  mtmPrintStudentInfo(output,student->id,student->first_name,student->last_name);
}
//added
void studentPrintGradeInfo(Student student, FILE *output, Grade grade) {
  if(!student)return;
  int points=preparePointsForPrint(gradeGetCoursePoints(grade));
  mtmPrintGradeInfo(output,gradeGetCourseId(grade),points,gradeGetGrade(grade));
}

static int preparePointsForPrint(char *points) {
  if (!points)return -1;
  double j = atof(points);
  int result = j * 2;
  return result;
}

void studentPrintSemesterInfo(Student student , FILE *output ,int semester ){
  if(!student)return;
  int e_grd=0;
  int e_pts=calcEffectivePointsForSem(student, semester,&e_grd );
  int t_pts=calcTotalPointsForSem(student->grades,semester);
  int f_pts= calcFailedPointsForSem(student->grades, semester);
  if(!e_pts && !e_grd  && !t_pts)return;
  mtmPrintSemesterInfo(output,semester,t_pts,f_pts,e_pts,e_grd);
}

static int calcEffectivePointsForSem(Student student, int semester, int *e_grd) {
  List tmp_list = listCopy(student->grades);
  Set tmp_set=setCreate(copyCourse,freeCourse,cmpCourse);
  int result = 0;
  int cur_course_id = 0;
  LIST_FOREACH(Grade, i, tmp_list) {
    if (gradeGetSemester(i) != semester)continue;
    Course course= createCourse(gradeGetCourseId(i), 0);
    if (setIsIn(tmp_set,course)){
      destroyCourse(course);
      continue;
    }
    cur_course_id = gradeGetCourseId(i);
    result +=calcEffectivePointsForCourse(student,semester,cur_course_id,e_grd);
    setAdd(tmp_set,course);
    destroyCourse(course);
  }
  setDestroy(tmp_set);
  listDestroy(tmp_list);
  return result;
}



static int calcEffectivePointsForCourse(Student student, int semester, int c_id, int *e_grd) {
  List tmp = listCopy(student->grades);
  int counter = 0;
  int result = 0;
  LIST_FOREACH(Grade, i, tmp) {
    if (gradeGetCourseId(i) == c_id) {
      if (gradeGetSemester(i) == semester) {
        counter++;
      }
    }
  }
  if (!counter) {
    listDestroy(tmp);
    return 0;
  }
  LIST_FOREACH(Grade, j, tmp) {
    if (gradeGetCourseId(j) == c_id) {
      if (gradeGetSemester(j) == semester) {
        counter--;
        if (!counter) {
          char *points = gradeGetCoursePoints(j);
          result = preparePointsForPrint(points);
          *e_grd+=(result*(gradeGetGrade(j)));//changed
          break;
        }
      }
    }
  }
  listDestroy(tmp);
  return result;
}


static int calcFailedPointsForSem(List grades, int semester) {
  List tmp = listCopy(grades);
  int result = 0;
  char *temp_points;
  LIST_FOREACH(Grade, i, tmp) {
    if (gradeGetSemester(i) != semester)continue;
    if (gradeGetGrade(i) < 55) {
      temp_points = gradeGetCoursePoints(i);
      result += preparePointsForPrint(temp_points);
    }
  }
  listDestroy(tmp);
  return result;
}

static int calcTotalPointsForSem(List grades, int semester) {
  int sum=0;
  List tmp = listCopy(grades);
  LIST_FOREACH(Grade,i,tmp){
    if(gradeGetSemester(i)==semester){
      sum+=preparePointsForPrint(gradeGetCoursePoints(i));
    }
  }
  listDestroy(tmp);
  return sum;
}

void studentPrintSummary(Student student , FILE* output ){
  int max_sem=studentGetMaxSem(student);
  int cur_sem=1;
  int total_pts=0;
  int total_f_pts=0;
  int e_pts=0;
  int e_grd=0;
  while( cur_sem <=max_sem ) {
    total_pts += calcTotalPointsForSem(student->grades, cur_sem);
    total_f_pts += calcFailedPointsForSem(student->grades, cur_sem);
    cur_sem++;
  }
  e_pts= calcTotalEffectivePtsAndGrade(student, &e_grd);
  e_pts+=calcEffectiveSportPts(student,&e_grd);
  mtmPrintSummary(output,total_pts,total_f_pts,e_pts,e_grd);
}

static int calcTotalEffectivePtsAndGrade(Student student, int *e_grd) {
  List tmp=createFilteredList(student->grades);
  int result=0;
  SET_FOREACH(Course , c , student->Courses){
    if(courseGetCourseId(c)>=390000 && courseGetCourseId(c)<= 399999 )continue;
    int e_sem=courseGetCourseLastSem(c);
    result+=calcEffectivePointsForCourse(student,e_sem,courseGetCourseId(c),e_grd);
  }
  listDestroy(tmp);
  return result;
}


static int calcEffectiveSportPts(Student student , int *e_grd) {
  List tmp=createFilteredList2(student->grades);
  int max_sem=studentGetMaxSem(student);
  int cur_sem=1;
  int result=0;
  while(cur_sem<=max_sem){
    result+=calcEffectivePointsForSemN2(student,tmp,cur_sem,e_grd);
    cur_sem++;
  }
  listDestroy(tmp);
  return result;
}



static bool isBetween(ListElement element, ListFilterKey key) {
  Grade grade=(Grade)element;
  int n_key=*(int*)key;
  if(gradeGetCourseId(grade) >=n_key && gradeGetCourseId(grade) <=399999){
    return false;
  }
  return true ;
}

static List createFilteredList(List listOfGrades) {
     int key= 390000;
     return listFilter(listOfGrades, isBetween, &key);
 }

static int calcEffectivePointsForSemN2(Student student,List  grades, int semester, int *e_grd) {
  List tmp_list = listCopy(grades);
  Set tmp_set=setCreate(copyCourse,freeCourse,cmpCourse);
  int result = 0;
  int cur_course_id = 0;
  LIST_FOREACH(Grade, i, tmp_list) {
    if (gradeGetSemester(i) != semester)continue;
    Course course= createCourse(gradeGetCourseId(i), 0);
    if (setIsIn(tmp_set,course)){
      destroyCourse(course);
      continue;
    }
    cur_course_id = gradeGetCourseId(i);
    result +=calcEffectivePointsForCourse(student,semester,cur_course_id,e_grd);
    setAdd(tmp_set,course);
    destroyCourse(course);
  }
  setDestroy(tmp_set);
  listDestroy(tmp_list);
  return result;
}


static bool isSportCourse(ListElement element, ListFilterKey key) {
  Grade grade=(Grade)element;
  int n_key=*(int*)key;
  if(gradeGetCourseId(grade) >=n_key &&gradeGetCourseId(grade) <=399999){
    return true;
  }
  return false ;
}


static List createFilteredList2(List listOfGrades) {
  int key= 390000;
  return listFilter(listOfGrades, isSportCourse, &key);
}


void studentPrintClean(Student student , FILE* output){
  if(!student)return;
  int e_grd=0,e_pts=0;
  List new=makeList(student);
  sortCourses(new);
  LIST_FOREACH(Course, course, new){
    int c_id=courseGetCourseId(course);
  if(c_id >= 390000 && c_id<= 399999){
    e_pts+= printCleanSportGrade(student, output, c_id, &e_grd, 0, NULL);
    continue;
  }
    int e_sem=courseGetCourseLastSem(course);
    e_pts+=printEffectivePointsForCourse(student,output,e_sem,c_id,&e_grd);
  }
  mtmPrintCleanSummary(output,e_pts,e_grd);
  listDestroy(new);
}

static List makeList(Student student){
List new=listCreate(copyCourse,freeCourse);
  SET_FOREACH(Course ,course , student->Courses){
    listInsertLast(new,course);
  }
  return new;
}

static int closerTo(ListElement element1, ListElement element2, ListSortKey value) {
  Course course1=(Course)element1;
  Course course2=(Course)element2;
  int id1 = courseGetCourseId(course1);
    int id2 = courseGetCourseId(course2);
    return id1 - id2;
}

static void sortCourses(List listOfCourses) {
   int key = 0;
   listSort(listOfCourses, closerTo, &key);
 }

static int printCleanSportGrade(Student student, FILE *output, int c_id,
                                int *e_grd, int flag, List grades) {
  int result=0,cur_sem = 1,counter = 0, sum=0;
  List tmp_list = listCopy(student->grades);
  Course course = getCourse(student, c_id);
  int max_sem = courseGetCourseLastSem(course);
  while (cur_sem <= max_sem) {
    LIST_FOREACH(Grade, g, tmp_list) {
      if (gradeGetCourseId(g) == c_id) {
        if (gradeGetSemester(g) == cur_sem) {
          counter++;
        }
      }
    }
    if (!counter) {
      cur_sem++;
      continue;
    }
    LIST_FOREACH(Grade, i, tmp_list) {
      if (gradeGetCourseId(i) == c_id) {
        if (gradeGetSemester(i) == cur_sem) {
          counter--;
          if (!counter) {
            if(flag){
              listInsertLast(grades,i);
              continue;
            }
            char *points = gradeGetCoursePoints(i);
            studentPrintGradeInfo(student,output,i);
            result = preparePointsForPrint(points);
            sum+=result;
            *e_grd+=(result*(gradeGetGrade(i)));//changed
            break;
          }
        }
      }
    }
    cur_sem++;
  }
  listDestroy(tmp_list);
  return sum;
}


static int printEffectivePointsForCourse(Student student,FILE* output,
                                         int semester, int c_id, int *e_grd) {
  List tmp = listCopy(student->grades);
  int counter = 0;
  int result = 0;
  LIST_FOREACH(Grade, i, tmp) {
    if (gradeGetCourseId(i) == c_id) {
      if (gradeGetSemester(i) == semester) {
        counter++;
      }
    }
  }
  if (!counter){
    listDestroy(tmp);
    return 0;
  }
  LIST_FOREACH(Grade, j, tmp) {
    if (gradeGetCourseId(j) == c_id) {
      if (gradeGetSemester(j) == semester) {
        counter--;
        if (!counter) {
          char *points = gradeGetCoursePoints(j);
          studentPrintGradeInfo(student,output,j);
          result = preparePointsForPrint(points);
          *e_grd+=(result*(gradeGetGrade(j)));//changed
          break;
        }
      }
    }
  }
  listDestroy(tmp);
  return result;
}

void studentPrintBest(Student student,FILE* output, int amount){
  List e_list= listCopy(student->grades);
  listClear(e_list);
  listGetFirst(e_list);
  SET_FOREACH(Course , course , student->Courses) {
    int e_sem = courseGetCourseLastSem(course);
    int e_grd = 0,c_id= courseGetCourseId(course);
    if(c_id >= 390000 && c_id<= 399999){
      printCleanSportGrade(student,output,c_id,&e_grd,1,e_list);
      continue;
    }
    int pts = calcEffectivePointsForCourse(student,e_sem,c_id,&e_grd);
    //if (pts == 0) continue;
    char s[10];
    double d=(double)pts/2;
    sprintf(s,"%f", d);
    if(!pts){
      printCleanSportGrade(student,output,c_id,&e_grd,1,e_list);
      continue;
    }
    Grade grade = createGrade(e_sem, c_id, s, (e_grd) /pts);
    listInsertLast(e_list, grade);
    destroyGrade(grade);
  }
  sortListGrades(e_list );
  LIST_FOREACH(Grade , g , e_list) {
    studentPrintGradeInfo(student, output, g);
    amount--;
    if (!amount)break;
  }
  listDestroy(e_list);
}


void studentPrintWorst(Student student,FILE* output, int amount){
  List e_list= listCopy(student->grades);
  listClear(e_list);
  listGetFirst(e_list);
  SET_FOREACH(Course , course , student->Courses) {
    int e_sem = courseGetCourseLastSem(course);
    int e_grd = 0,c_id= courseGetCourseId(course);
    if(c_id >= 390000 && c_id<= 399999){
      printCleanSportGrade(student,output,c_id,&e_grd,1,e_list);
      continue;
    }
    int pts = calcEffectivePointsForCourse(student,e_sem,c_id,&e_grd);
    if (pts == 0) {
      printCleanSportGrade(student,output,c_id,&e_grd,1,e_list);
      continue;
    }
    char s[10];
    double d=(double)pts/2;
    sprintf(s,"%f", d);
    Grade grade = createGrade(e_sem, c_id, s, (e_grd) /pts);
    listInsertLast(e_list, grade);
    destroyGrade(grade);
  }
  sortListGradesMin(e_list );
  LIST_FOREACH(Grade , g , e_list) {
    studentPrintGradeInfo(student, output, g);
    amount--;
    if (!amount)break;
  }
  listDestroy(e_list);
}


static int higherThan(ListElement element1, ListElement element2, ListSortKey value){
  Friend friend1=(Friend)element1;
  Friend friend2=(Friend)element2;
  int grade1= getFriendGrade(friend1);
  int grade2= getFriendGrade(friend2);
  int id1 = getFriendId(friend1);
  int id2 = getFriendId(friend2);
  if (grade1==grade2){
    return id1-id2;
  }
  return grade2-grade1;
}

static void sortFriends(List listOfFriends) {
  int key=0;
  listSort(listOfFriends, higherThan, &key);
}

static int FindMaxGrade(Student student, int course_id){
  int max_grade=-1;
  LIST_FOREACH(Grade, g, student->grades){
    if (gradeGetCourseId(g)!=course_id) continue;
    if (gradeGetGrade(g) > max_grade){
      max_grade= gradeGetGrade(g);
    }
  }
  return max_grade;
}

void stuReportReference(Student s,Set Students,FILE* output,int c_id,int amount) {
  List best_friends = listCreate(setCopyFriend, setFreeFriend);
  SET_FOREACH(Friend, f, s->friends) {
    Student f_stu = getStudent(Students, getFriendId(f));
    int max_grade = FindMaxGrade(f_stu, c_id);
    if (max_grade == -1) continue;
    Friend friend =createFriend(f_stu->id, f_stu->first_name, f_stu->last_name, max_grade);
    listInsertLast(best_friends, friend);
    destroyFriend(friend);
  }
  sortFriends(best_friends);
  LIST_FOREACH(Friend, f, best_friends){
    mtmPrintStudentName(output,getFriendFirstName(f),getFriendLastName(f));
    amount--;
    if (!amount)break;
  }
  listDestroy(best_friends);
}

StudentResult studentCheckCourse(Student student, int c_id){
  int course_exists=0;
  LIST_FOREACH(Grade, g, student->grades){
    if (gradeGetCourseId(g) == c_id){
      course_exists=1;
      break;
    }
  }
  if (course_exists == 0){
    return STUDENT_COURSE_NOT_EXIST;
  }
    return STUDENT_OK;
}














