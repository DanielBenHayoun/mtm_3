//
// Created by daniel on 1/1/2018.
//

#ifndef MTM_EX3_CMDTYPDEFS1_H
#define MTM_EX3_CMDTYPDEFS1_H


typedef char *FirstName;
typedef char *LastName;
typedef char *Action;
typedef char *Points;
typedef char *Request;
typedef long StudentId;
typedef int FreindId;
typedef int Semester;
typedef int CourseId;
typedef int GradeNum;



#define TEST_TRUE(result, bool) if ((result) && !(bool)) { \
                                result = false; \
                                assert(result == true); \
                            }


#endif //MTM_EX3_CMDTYPDEFS1_H
