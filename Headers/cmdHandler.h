

#ifndef MTM_HW2_MTM_ESCAPE_FILEHANDLER_H_H
#define MTM_HW2_MTM_ESCAPE_FILEHANDLER_H_H

#include <stdbool.h>
#include "../Headers/CourseManager.h"

enum {
  ONE_CMD = 1,
  THREE_CMD = 3,
  SIZE_OF_NON_ARG = 2,
  MAX_CMD_SIZE = 5
};

typedef enum {
  STANDART_INPUT,
  STANDART_OUTPUT,
  INPUT_FLAG_FIRST,
  INPUT_FLAG_SECOND,
  OUTPUT_FLAG_FIRST,
  OUTPUT_FLAG_SECOND
} FlagResult;

typedef enum {
  CMD_OUT_OF_MEMORY,
  CMD_INVALID_COMMAND_LINE_PARAMETERS,
  CMD_CANNOT_OPEN_FILE,
  CMD_NULL_PARAMETER,
  CMD_INVALID_PARAMETER,
  CMD_NOT_LOGGED_IN,
  CMD_ALREADY_LOGGED_IN,
  CMD_STUDENT_NOT_EXISTS,
  CMD_STUDENT_ALREADY_EXISTS,
  CMD_NOT_FRIENDS,
  CMD_ALREADY_FRIEND,
  CMD_NOT_REQUESTED,
  CMD_ALREADY_REQUESTED,
  CMD_COURSE_DOES_NOT_EXIST,
  CMD_SUCCESS
} CmdResult;

typedef enum {
  STUDENT_CMD_ADD,
  STUDENT_CMD_REMOVE,
  STUDENT_CMD_LOGIN,
  STUDENT_CMD_LOGOUT,
  STUDENT_CMD_FRIEND_REQ,
  STUDENT_CMD_HANDLE_REQ,
  STUDENT_CMD_UNFRIEND,
  STUDENT_CMD_ERROR_COMMAND
} StudentCommand;

typedef enum {
  GRADE_CMD_ADD,
  GRADE_CMD_REMOVE,
  GRADE_CMD_UPDATE,
  GRADE_CMD_ERROR_COMMAND
} GradeCommand;

typedef enum {
  REPORT_CMD_FULL,
  REPORT_CMD_CLEAN,
  REPORT_CMD_BEST,
  REPORT_CMD_WORST,
  REPORT_CMD_REFERENCE,
  REPORT_CMD_FACULTY_REQ,
  REPORT_CMD_ERROR_COMMAND
} ReportCommand;

typedef char *argument;

/*======================= CMD MAIN API as in pdf =========================== */

//Student commands.
CmdResult cmdStudentAdd(argument *arg_array, CourseManager sys);

CmdResult cmdStudentRemove(argument *arg_array, CourseManager sys);

CmdResult cmdStudentLogin(argument *arg_array , CourseManager sys);

CmdResult cmdStudentLogout(CourseManager sys);

CmdResult cmdStudentFriendRequest(argument *arg_array, CourseManager sys);

CmdResult cmdStudentHandleRequest(argument *arg_array, CourseManager sys);

CmdResult cmdStudentUnfriend(argument *arg_array, CourseManager sys);

//Grade commands.
CmdResult cmdGradeAdd(argument *arg_array, CourseManager sys);

CmdResult cmdGradeRemove(argument *arg_array, CourseManager sys);

CmdResult cmdGradeUpdate(argument *arg_array, CourseManager sys);

//Report commands.
CmdResult cmdReportFull(CourseManager sys, FILE *output);

CmdResult cmdReportClean(CourseManager sys, FILE *output);

CmdResult cmdReportBest(argument *arg_array, CourseManager sys, FILE *output);

CmdResult cmdReportWorst(argument *arg_array, CourseManager sys, FILE *output);

CmdResult cmdReportReference(argument*,CourseManager ,FILE*);

CmdResult cmdReportreFacultyRequest(argument* ,CourseManager, FILE*);


/*========================= CMD HANDLER API =============================== */

void cmdInit(char **argv, FILE **file, FlagResult flag);

void cmdDestroy(argument arg1, argument arg2, argument *arg_array, int len);

bool cmdCheckCommandSizeLegal(int argc);

bool cmdCheckFatalError(CmdResult result);

bool cmdCheckIfCommandLegal(char *command_line);

CmdResult cmdCheckValidFlags(int argc, char **argv, FlagResult *flag);

CmdResult cmdSwitch(int argc, char **argv, FILE **input, FILE **output);

argument *cmdSetForCommand(argument *arg1,
                           argument *arg2,
                           char *command_line,
                           int *len);

CmdResult cmdExeCommand(argument arg1,
                        argument arg2,
                        argument *arg_array,
                        CourseManager sys,
                        FILE *output);

MtmErrorCode cmdConvertErrorMessage(CmdResult result);

CmdResult cmdConvertETSResult(SysResult result);

StudentCommand cmdConvertToStudentEnum(argument arg);

GradeCommand cmdConvertToGradeEnum(argument arg);

ReportCommand cmdConvertToReportEnum(argument arg);


#endif //MTM_HW2_MTM_ESCAPE_FILEHANDLER_H_H
