
#include <stdlib.h>
#include <string.h>
#include "../Headers/test_utilities.h"
#include "../Headers/cmdHandler.h"


bool testCmdCheckCommandSizeLegal();

bool testCmdSwitch();

bool testCmdSetForCommand();

typedef struct {
    FILE *input;
    FILE *output;
} Files;

static Files setUp();

/**
 * We only tested the non-trivial functions in cmd_handler api.
 * @return
 */
int main() {
    RUN_TEST(testCmdCheckCommandSizeLegal);
    RUN_TEST(testCmdSwitch);
    RUN_TEST(testCmdSetForCommand);

    return 0;
}

bool testCmdCheckCommandSizeLegal() {
    bool result = true;
    TEST_TRUE(result, cmdCheckCommandSizeLegal(1));
    TEST_TRUE(result, cmdCheckCommandSizeLegal(3));
    TEST_TRUE(result, cmdCheckCommandSizeLegal(5));
    result = false;
    TEST_TRUE(result, cmdCheckCommandSizeLegal(4));
    TEST_TRUE(result, cmdCheckCommandSizeLegal(6));
    TEST_TRUE(result, cmdCheckCommandSizeLegal(0));
    TEST_TRUE(result, cmdCheckCommandSizeLegal(2));
    TEST_TRUE(result, cmdCheckCommandSizeLegal(60));
    return true;
}

bool testCmdSwitch() {
    Files files = setUp();
    char *arg1 = "mtm_escape";
    char *arg2 = "-i";
    char *arg3 = "test.in";
    char *arg4 = "-o";
    char *arg5 = "test.out";

    char **argv = malloc(sizeof(*argv) * 5);
    argv[0] = arg1;
    argv[1] = arg2;
    argv[2] = arg3;
    argv[3] = arg4;
    argv[4] = arg5;

    //command size is asserted to be legal.
    ASSERT_TEST(cmdSwitch(3, argv, &files.input, &files.output) ==
                CMD_CANNOT_OPEN_FILE);

    char *arg = "-l";
    argv[1] = arg;
    ASSERT_TEST(cmdSwitch(3, argv, &files.input, &files.output) ==
                CMD_INVALID_COMMAND_LINE_PARAMETERS);

    arg = "-ii";
    argv[1] = arg;
    ASSERT_TEST(cmdSwitch(3, argv, &files.input, &files.output) ==
                CMD_INVALID_COMMAND_LINE_PARAMETERS);

    free(argv);
    return true;
}

bool testCmdSetForCommand() {
    argument arg1 = NULL;
    argument arg2 = NULL;
    argument *arg_array = NULL;
    int len = 0;
    char command_line[MAX_LEN];

    strcpy(command_line, "report day");
    arg_array = cmdSetForCommand(&arg1, &arg2, command_line, &len);
    bool result = true;
    TEST_TRUE(result, !strcmp(arg1, "report"))
    TEST_TRUE(result, !strcmp(arg2, "day"))
    ASSERT_TEST(len == 2);

    cmdDestroy(arg1, arg2, arg_array, len - SIZE_OF_NON_ARG);
    arg1 = NULL;
    arg2 = NULL;

    strcpy(command_line, "room remove");
    arg_array = cmdSetForCommand(&arg1, &arg2, command_line, &len);
    TEST_TRUE(result, !strcmp(arg1, "room"))
    TEST_TRUE(result, !strcmp(arg2, "remove"))
    ASSERT_TEST(len == 2);

    cmdDestroy(arg1, arg2, arg_array, len - SIZE_OF_NON_ARG);
    arg1 = NULL;
    arg2 = NULL;

    strcpy(command_line, "hello WorlD");
    arg_array = cmdSetForCommand(&arg1, &arg2, command_line, &len);
    TEST_TRUE(result, !strcmp(arg1, "hello"))
    TEST_TRUE(result, !strcmp(arg2, "WorlD"))
    ASSERT_TEST(len == 2);

    cmdDestroy(arg1, arg2, arg_array, len - SIZE_OF_NON_ARG);
    arg1 = NULL;
    arg2 = NULL;

    strcpy(command_line, "shalom hi -i -o");
    arg_array = cmdSetForCommand(&arg1, &arg2, command_line, &len);
    TEST_TRUE(result, !strcmp(arg_array[0], "-i"))
    TEST_TRUE(result, !strcmp(arg_array[1], "-o"))
    ASSERT_TEST(len == 4);

    cmdDestroy(arg1, arg2, arg_array, len - SIZE_OF_NON_ARG);
    arg1 = NULL;
    arg2 = NULL;

    strcpy(command_line, "shalom hi -i -o here we are");
    arg_array = cmdSetForCommand(&arg1, &arg2, command_line, &len);
    TEST_TRUE(result, !strcmp(arg_array[0], "-i"))
    TEST_TRUE(result, !strcmp(arg_array[1], "-o"))
    TEST_TRUE(result, !strcmp(arg_array[2], "here"))
    TEST_TRUE(result, !strcmp(arg_array[3], "we"))
    TEST_TRUE(result, !strcmp(arg_array[4], "are"))
    ASSERT_TEST(len == 7);

    cmdDestroy(arg1, arg2, arg_array, len - SIZE_OF_NON_ARG);

    return true;
}


static Files setUp() {
    Files files;
    files.input = NULL;
    files.output = NULL;
    return files;
}