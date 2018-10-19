
#include "../Headers/mtm_ex3.h"
#include "../Headers/cmdHandler.h"

int CourseManagerSystem(int argc, char **argv) {
  if (!cmdCheckCommandSizeLegal(argc)) {
    mtmPrintErrorMessage(stderr, MTM_INVALID_COMMAND_LINE_PARAMETERS);
    return 1;
  }
  FILE *input = NULL;
  FILE *output = NULL;
  CmdResult result = cmdSwitch(argc, argv, &input, &output);
  if (result != CMD_SUCCESS) {
    mtmPrintErrorMessage(stderr, cmdConvertErrorMessage(result));
    return 1;
  }
  char command_line[MAX_LEN] = "";
  argument *arg_array = NULL;
  argument arg1 = NULL;
  argument arg2 = NULL;
  int len = 0;
  CourseManager sys;
   if(createSystem(&sys)!=SYS_OK)return -1;
  if (sys == NULL) { return -1; }

  while (fgets(command_line, MAX_LEN, input) != NULL) {
    if (!cmdCheckIfCommandLegal(command_line)) {
      continue;
    }
    arg_array = cmdSetForCommand(&arg1, &arg2, command_line, &len);
    result = cmdExeCommand(arg1, arg2, arg_array, sys, output);
    if (result != CMD_SUCCESS) {
      mtmPrintErrorMessage(stderr, cmdConvertErrorMessage(result));
      if (cmdCheckFatalError(result)) {
        cmdDestroy(arg1, arg2, arg_array, len - SIZE_OF_NON_ARG);
        break;
      }
    }
    cmdDestroy(arg1, arg2, arg_array, len - SIZE_OF_NON_ARG);
  }
  destroySys(sys);
  fclose(input);
  fclose(output);
  return 0;
}

int main(int argc, char **argv) {
  return CourseManagerSystem(argc, argv);
}