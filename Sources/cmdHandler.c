
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../Headers/cmdHandler.h"

static char *cmdStringCopy(char *to, char *from);

static int cmdGetCommandLength(char *cmd_copy);

bool cmdCheckCommandSizeLegal(int argc) {
  if (argc > MAX_CMD_SIZE)
    return false;
  switch (argc) {
    case 2:
      return false;
    case 4:
      return false;
    default:
      return true;
  }
}

bool cmdCheckIfCommandLegal(char *command_line) {
  char *cmd_copy = NULL;
  cmd_copy = cmdStringCopy(cmd_copy, command_line);

  char *temp = strtok(cmd_copy, " \t");

  if (temp == NULL || temp[0] == '#' || temp[0] == '\n' || temp[0] == '\r'
      || temp[0] == '\t') {
    free(cmd_copy);
    return false;
  }
  free(cmd_copy);
  return true;
}

CmdResult cmdCheckValidFlags(int argc, char **argv, FlagResult *flag) {
  if (argc == ONE_CMD)
    return CMD_SUCCESS;
  if (!strcmp(argv[1], "-i")) {
    *flag = INPUT_FLAG_FIRST;
  } else if (!strcmp(argv[1], "-o")) {
    *flag = OUTPUT_FLAG_FIRST;
  } else
    return CMD_INVALID_COMMAND_LINE_PARAMETERS;

  if (argc == MAX_CMD_SIZE) {
    if (!strcmp(argv[1], argv[3])) {
      return CMD_INVALID_COMMAND_LINE_PARAMETERS;
    } else if (!strcmp(argv[3], "-i") || !strcmp(argv[3], "-o")) {
      return CMD_SUCCESS;
    } else
      return CMD_INVALID_COMMAND_LINE_PARAMETERS;
  }
  return CMD_SUCCESS;
}

void cmdInit(char **argv, FILE **file, FlagResult flag) {
  switch (flag) {
    case (STANDART_INPUT):
      *file = stdin;
      break;
    case (STANDART_OUTPUT):
      *file = stdout;
      break;
    case (INPUT_FLAG_FIRST):
      *file = fopen(argv[2], "r");
      break;
    case (INPUT_FLAG_SECOND):
      *file = fopen(argv[4], "r");
      break;
    case (OUTPUT_FLAG_FIRST):
      *file = fopen(argv[2], "w");
      break;
    case (OUTPUT_FLAG_SECOND):
      *file = fopen(argv[4], "w");
      break;
  }
}

CmdResult cmdSwitch(int argc, char **argv, FILE **input, FILE **output) {
  FlagResult flag;
  if (cmdCheckValidFlags(argc, argv, &flag) != CMD_SUCCESS) {
    return CMD_INVALID_COMMAND_LINE_PARAMETERS;
  }
  switch (argc) {
    case (ONE_CMD):
      cmdInit(argv, input, STANDART_INPUT);
      cmdInit(argv, output, STANDART_OUTPUT);
      if (!*input || !*output)
        return CMD_CANNOT_OPEN_FILE;
      break;
    case (THREE_CMD):
      if (flag == INPUT_FLAG_FIRST) {
        cmdInit(argv, input, INPUT_FLAG_FIRST);
        cmdInit(argv, output, STANDART_OUTPUT);
        if (!*input)
          return CMD_CANNOT_OPEN_FILE;
      } else {
        cmdInit(argv, output, OUTPUT_FLAG_FIRST);
        cmdInit(argv, input, STANDART_INPUT);
        if (!*output)
          return CMD_CANNOT_OPEN_FILE;
      }
      break;

    case MAX_CMD_SIZE:
      if (flag == INPUT_FLAG_FIRST) {
        cmdInit(argv, input, INPUT_FLAG_FIRST);
        cmdInit(argv, output, OUTPUT_FLAG_SECOND);
      } else {
        cmdInit(argv, input, INPUT_FLAG_SECOND);
        cmdInit(argv, output, OUTPUT_FLAG_FIRST);
      }
      if (!*input || !*output)
        return CMD_CANNOT_OPEN_FILE;
      break;
    default:; //Won't reach here.
  }
  return CMD_SUCCESS;
}

argument *cmdSetForCommand(argument *arg1, argument *arg2, char *command_line,
                           int *len) {
  char *cmd_copy = NULL;
  cmd_copy = cmdStringCopy(cmd_copy, command_line);
  if (cmd_copy == NULL) { return NULL; }
  *len = cmdGetCommandLength(cmd_copy);
  free(cmd_copy);

  argument *arg_array = NULL;
  if (*len - SIZE_OF_NON_ARG != 0) {
    arg_array = malloc((*len - SIZE_OF_NON_ARG) * sizeof(*arg_array));
    if (!arg_array) {
      return NULL;
    }
  }


  char *temp = strtok(command_line, " \t\n\r");
  *arg1 = cmdStringCopy(*arg1, temp);
  temp = strtok(NULL, " \t\n\r");
  *arg2 = cmdStringCopy(*arg2, temp);

  argument temp_arg = NULL;
  for (int i = 0;; i++) {
    temp = strtok(NULL, " \t\n\r");
    if (!temp)
      break;
    temp_arg = cmdStringCopy(temp_arg, temp);
    if (temp_arg == NULL) { return NULL; }
    arg_array[i] = temp_arg;
  }

  return arg_array;
}

//remember to change
CmdResult cmdExeCommand(argument arg1, argument arg2, argument *arg_array,
                        CourseManager sys, FILE *output) {
  CmdResult result = CMD_INVALID_COMMAND_LINE_PARAMETERS;
  if (!strcmp(arg1, "student")) {
    StudentCommand student_command = cmdConvertToStudentEnum(arg2);
    switch (student_command) {
      case (STUDENT_CMD_ADD):
        result = cmdStudentAdd(arg_array, sys);
        break;
      case (STUDENT_CMD_REMOVE):
        result = cmdStudentRemove(arg_array, sys);
        break;
      case (STUDENT_CMD_LOGIN):
        result=cmdStudentLogin(arg_array, sys);
        break;
      case (STUDENT_CMD_LOGOUT):
        result=cmdStudentLogout(sys);
        break;
      case (STUDENT_CMD_FRIEND_REQ):
        result=cmdStudentFriendRequest(arg_array,sys);
        break;
      case (STUDENT_CMD_HANDLE_REQ):
        result=cmdStudentHandleRequest(arg_array , sys);
        break;
      case (STUDENT_CMD_UNFRIEND):
        result=cmdStudentUnfriend(arg_array,sys);
        break;
      case (STUDENT_CMD_ERROR_COMMAND):
        result = CMD_INVALID_COMMAND_LINE_PARAMETERS;
    }
  } else if (!strcmp(arg1, "grade_sheet")) {
    GradeCommand grade_command = cmdConvertToGradeEnum(arg2);
    switch (grade_command) {
      case (GRADE_CMD_ADD):
        result = cmdGradeAdd(arg_array, sys);
        break;
      case (GRADE_CMD_REMOVE):
        result = cmdGradeRemove(arg_array, sys);
        break;
      case (GRADE_CMD_UPDATE):
        result = cmdGradeUpdate(arg_array, sys);
        break;
      case (GRADE_CMD_ERROR_COMMAND):
        result = CMD_INVALID_COMMAND_LINE_PARAMETERS;
    }
  } else if (!strcmp(arg1, "report")) {
    ReportCommand report_command = cmdConvertToReportEnum(arg2);
    switch (report_command) {
      case (REPORT_CMD_FULL):
        result = cmdReportFull(sys, output);
        break;
      case (REPORT_CMD_CLEAN):
        result = cmdReportClean(sys, output);
        break;
      case (REPORT_CMD_BEST):
        result = cmdReportBest(arg_array, sys, output);
        break;
      case (REPORT_CMD_WORST):
        result = cmdReportWorst(arg_array, sys, output);
        break;
      case (REPORT_CMD_REFERENCE):
        result = cmdReportReference(arg_array, sys, output);
        break;
     case (REPORT_CMD_FACULTY_REQ):
        result = cmdReportreFacultyRequest(arg_array, sys, output);
        break;
      case (REPORT_CMD_ERROR_COMMAND):
        result = CMD_INVALID_COMMAND_LINE_PARAMETERS;
    }
  }
  return result;
}

void cmdDestroy(argument arg1, argument arg2, argument *arg_array, int len) {
  free(arg1);
  free(arg2);

  if (arg_array == NULL) { return; }
  for (int i = 0; i < len; i++) {
    free(arg_array[i]);
  }
  free(arg_array);

}

StudentCommand cmdConvertToStudentEnum(argument arg) {
  if (!strcmp(arg, "add"))
    return STUDENT_CMD_ADD;
  else if (!strcmp(arg, "remove"))
    return STUDENT_CMD_REMOVE;
  else if (!strcmp(arg,"login"))
    return STUDENT_CMD_LOGIN;
  else if (!strcmp(arg,"logout"))
    return STUDENT_CMD_LOGOUT;
  else if (!strcmp(arg,"friend_request"))
    return STUDENT_CMD_FRIEND_REQ;
  else if (!strcmp(arg,"handle_request"))
    return STUDENT_CMD_HANDLE_REQ;
  else if (!strcmp(arg,"unfriend"))
    return STUDENT_CMD_UNFRIEND;
  return STUDENT_CMD_ERROR_COMMAND;
}

GradeCommand cmdConvertToGradeEnum(argument arg) {
  if (!strcmp(arg, "add"))
    return GRADE_CMD_ADD;
  else if (!strcmp(arg, "remove"))
    return GRADE_CMD_REMOVE;
  else if (!strcmp(arg, "update"))
    return GRADE_CMD_UPDATE;
  return GRADE_CMD_ERROR_COMMAND;
}



ReportCommand cmdConvertToReportEnum(argument arg) {
  if (!strcmp(arg, "full"))
    return REPORT_CMD_FULL;
  else if (!strcmp(arg, "clean"))
    return REPORT_CMD_CLEAN;
  else if (!strcmp(arg, "best"))
    return REPORT_CMD_BEST;
  else if (!strcmp(arg, "worst"))
    return REPORT_CMD_WORST;
  else if (!strcmp(arg, "reference"))
    return REPORT_CMD_REFERENCE;
  else if (!strcmp(arg, "faculty_request"))
    return REPORT_CMD_FACULTY_REQ;
  return REPORT_CMD_ERROR_COMMAND;
}

MtmErrorCode cmdConvertErrorMessage(CmdResult result) {
  switch (result) {
    case (CMD_INVALID_COMMAND_LINE_PARAMETERS):
      return MTM_INVALID_COMMAND_LINE_PARAMETERS;
    case (CMD_OUT_OF_MEMORY):
      return MTM_OUT_OF_MEMORY;
    case (CMD_CANNOT_OPEN_FILE):
      return MTM_CANNOT_OPEN_FILE;
    case (CMD_INVALID_PARAMETER):
      return MTM_INVALID_PARAMETERS;
    case (CMD_NOT_LOGGED_IN):
      return MTM_NOT_LOGGED_IN;
    case (CMD_ALREADY_LOGGED_IN):
      return MTM_ALREADY_LOGGED_IN;
    case (CMD_STUDENT_NOT_EXISTS):
      return MTM_STUDENT_DOES_NOT_EXIST;
    case (CMD_STUDENT_ALREADY_EXISTS):
      return MTM_STUDENT_ALREADY_EXISTS;
    case (CMD_NOT_FRIENDS):
      return MTM_NOT_FRIEND;
    case (CMD_ALREADY_FRIEND):
      return MTM_ALREADY_FRIEND;
    case (CMD_NOT_REQUESTED):
      return MTM_NOT_REQUESTED;
    case (CMD_ALREADY_REQUESTED):
      return MTM_ALREADY_REQUESTED;
    case (CMD_COURSE_DOES_NOT_EXIST):
      return MTM_COURSE_DOES_NOT_EXIST;
    case (CMD_SUCCESS):
      return MTM_COURSE_DOES_NOT_EXIST;//just for default
    case (CMD_NULL_PARAMETER):
      return MTM_COURSE_DOES_NOT_EXIST;//just for default
  }
  return MTM_COURSE_DOES_NOT_EXIST;///just for default
}

CmdResult cmdConvertETSResult(SysResult result) {
  switch (result) {
    case (SYS_INVALID_COMMAND_LINE_PARAMETERS):
      return CMD_INVALID_COMMAND_LINE_PARAMETERS;
    case (SYS_OUT_OF_MEMORY):
      return CMD_OUT_OF_MEMORY;
    case (SYS_CANNOT_OPEN_FILE):
      return CMD_CANNOT_OPEN_FILE;
    case (SYS_NULL_PARAMETER):
      return CMD_NULL_PARAMETER;
    case (SYS_INVALID_PARAMETER):
      return CMD_INVALID_PARAMETER;
    case (SYS_NOBODY_LOGGED_IN):
      return CMD_NOT_LOGGED_IN;
    case (SYS_ALREADY_LOGGED_IN):
      return CMD_ALREADY_LOGGED_IN;
    case (SYS_STUDENT_NOT_EXISTS):
      return CMD_STUDENT_NOT_EXISTS;
    case (SYS_STUDENT_ALREADY_EXISTS):
      return CMD_STUDENT_ALREADY_EXISTS;
    case (SYS_NOT_FRIENDS):
      return CMD_NOT_FRIENDS;
    case (SYS_ALREADY_FRIEND):
      return CMD_ALREADY_FRIEND;
    case (SYS_NOT_REQUESTED):
      return CMD_NOT_REQUESTED;
    case (SYS_ALREADY_REQUESTED):
      return CMD_ALREADY_REQUESTED;
    case (SYS_COURSE_DOES_NOT_EXIST):
      return CMD_COURSE_DOES_NOT_EXIST;
    case (SYS_OK):
      return CMD_SUCCESS;
  }
  return CMD_SUCCESS;
}

bool cmdCheckFatalError(CmdResult result) {
  switch (result) {
    case (CMD_INVALID_COMMAND_LINE_PARAMETERS):
      return true;
    case (CMD_CANNOT_OPEN_FILE):
      return true;
    case (CMD_OUT_OF_MEMORY):
      return true;
    default:
      return false;
  }
}

/** ===================== STATIC FUNCTIONS ========================*/
static char *cmdStringCopy(char *to, char *from) {
  to = malloc(sizeof(*from) * (strlen(from) + 1));
  if (!to) {
    return NULL;
  }
  strcpy(to, from);
  return to;
}

static int cmdGetCommandLength(char *cmd_copy) {
  int len = 0;
  char *temp = strtok(cmd_copy, " \t\n\r");
  while (temp != NULL) {
    len++;
    temp = strtok(NULL, " \t\n\r");
  }
  return len;
}