
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "../Headers/test_utilities.h"
#include "../Headers/list_mtm.h"



#define SET_UP(Typename) Typename examples = setUp()
#define TEAR_DOWN() tearDown(examples)
//======================= Primitive Datatype =======================||

ListElement copyString(ListElement str);

void freeString(ListElement str);

ListElement copyInt(ListElement num);

void freeInt(ListElement num);

ListElement copyDouble(ListElement num);

void freeDouble(ListElement num);

int closerTo(ListElement num1, ListElement num2,ListSortKey Key);

bool isShorterThan(ListElement str, ListFilterKey length);

static bool testPrimitiveListCreate() {
    ASSERT_TEST(listCreate(NULL, NULL) == NULL);
    List string_list = NULL;

    ASSERT_TEST(string_list = listCreate(copyString, freeString));
    ASSERT_TEST(listCreate(copyString, NULL) == NULL);
    ASSERT_TEST(listCreate(NULL, freeString) == NULL);

    List int_list = NULL;
    ASSERT_TEST(int_list = listCreate(copyInt, freeInt));
    ASSERT_TEST(listCreate(copyInt, NULL) == NULL);
    ASSERT_TEST(listCreate(NULL, freeInt) == NULL);
    listDestroy(string_list);
    listDestroy(int_list);

    return true;
}

static bool testPrimitiveListCopy() {
    ASSERT_TEST(listCopy(NULL) == NULL);

    List string_list = listCreate(copyString, freeString);
    List int_list = listCreate(copyInt, freeInt);
    List copy_string = NULL;
    List copy_int = NULL;
    ASSERT_TEST(copy_string = listCopy(string_list));
    ASSERT_TEST(copy_int = listCopy(int_list));
    listDestroy(copy_string);
    listDestroy(copy_int);
    listDestroy(string_list);
    listDestroy(int_list);

    return true;
}

static bool testPrimitiveListGetSize() {
    ASSERT_TEST(listGetSize(NULL) == -1);
    List string_list = listCreate(copyString, freeString);
    List int_list = listCreate(copyInt, freeInt);
    ASSERT_TEST(listGetSize(string_list) == 0);
    ASSERT_TEST(listGetSize(int_list) == 0);
    listDestroy(string_list);
    listDestroy(int_list);

    return true;
}

static bool testPrimitiveListGetFirst() {
    ASSERT_TEST(listGetFirst(NULL) == NULL);
    List string_list = listCreate(copyString, freeString);
    List int_list = listCreate(copyInt, freeInt);
    ASSERT_TEST(listGetFirst(string_list) == NULL);
    ASSERT_TEST(listGetFirst(int_list) == NULL);
    listDestroy(string_list);
    listDestroy(int_list);

    return true;
}

static bool testPrimitiveListGetNext() {
    ASSERT_TEST(listGetNext(NULL) == NULL);

    List string_list = listCreate(copyString, freeString);
    List int_list = listCreate(copyInt, freeInt);
    ASSERT_TEST(listGetNext(string_list) == NULL);
    ASSERT_TEST(listGetNext(int_list) == NULL);
    listDestroy(string_list);
    listDestroy(int_list);

    return true;
}

static bool testPrimitiveGetCurrent() {
    ASSERT_TEST(listGetCurrent(NULL) == NULL);
    List string_list = listCreate(copyString, freeString);
    List int_list = listCreate(copyInt, freeInt);
    ASSERT_TEST(listGetCurrent(string_list) == NULL);
    ASSERT_TEST(listGetCurrent(int_list) == NULL);
    listDestroy(string_list);
    listDestroy(int_list);

    return true;
}

static bool testPrimitiveListInsertFirst() {
    ASSERT_TEST(listInsertFirst(NULL, NULL) == LIST_NULL_ARGUMENT);
    List string_list = listCreate(copyString, freeString);
    List int_list = listCreate(copyInt, freeInt);

    int num = 7;
    ASSERT_TEST(listInsertFirst(string_list, (void *) "Pesah") == LIST_SUCCESS);
    ASSERT_TEST(listInsertFirst(int_list, (void *) &num) == LIST_SUCCESS);
    ASSERT_TEST(*(int *) listGetFirst(int_list) == 7);
    char *str = (char *) listGetFirst(string_list);
    ASSERT_TEST(strcmp(str, "Pesah") == 0);

    num = 9;
    ASSERT_TEST(listInsertFirst(int_list, (void *) &num) == LIST_SUCCESS);
    ASSERT_TEST(*(int *) listGetFirst(int_list) == 9);
    ASSERT_TEST(*(int *) listGetNext(int_list) == 7);
    ASSERT_TEST(listGetSize(int_list) == 2);

    ASSERT_TEST(
            listInsertFirst(string_list, (void *) "I'am just a peaceful string")
            == LIST_SUCCESS);
    str = (char *) listGetFirst(string_list);
    ASSERT_TEST(strcmp(str, "I'am just a peaceful string") == 0);

    ASSERT_TEST(*(int *) listGetCurrent(int_list) == 7);
    ASSERT_TEST(listGetNext(int_list) == NULL);
    str = (char *) listGetNext(string_list);
    ASSERT_TEST(strcmp(str, "Pesah") == 0);
    ASSERT_TEST(listGetSize(string_list) == 2);
    ASSERT_TEST(listGetSize(int_list) == 2);
    listDestroy(int_list);
    listDestroy(string_list);
    return true;
}

static bool testPrimitiveListInsertLast() {
    ASSERT_TEST(listInsertLast(NULL, NULL) == LIST_NULL_ARGUMENT);
    List string_list = listCreate(copyString, freeString);
    List double_list = listCreate(copyDouble, freeDouble);
    double num = 5940;
    double checker;

    ASSERT_TEST(
            listInsertLast(string_list, (void *) "Sup Man?") == LIST_SUCCESS);
    ASSERT_TEST(listInsertLast(double_list, (void *) &num) == LIST_SUCCESS);
    checker = *(double *) listGetFirst(double_list);
    ASSERT_TEST(checker == 5940);
    num = 100;
    ASSERT_TEST(listInsertFirst(double_list, (void *) &num) == LIST_SUCCESS);
    num = 200;

    ASSERT_TEST(listInsertFirst(double_list, (void *) &num) == LIST_SUCCESS);
    num = 300;
    ASSERT_TEST(listInsertLast(double_list, (void *) &num) == LIST_SUCCESS);

    checker = *(double *) listGetFirst(double_list);
    ASSERT_TEST(checker == 200);
    checker = *(double *) listGetNext(double_list);
    ASSERT_TEST(checker == 100);
    checker = *(double *) listGetNext(double_list);
    ASSERT_TEST(checker == 5940);
    checker = *(double *) listGetNext(double_list);
    ASSERT_TEST(checker == 300);

    ASSERT_TEST(listGetSize(double_list) == 4);
    List copy_double = NULL;
    ASSERT_TEST(copy_double = listCopy(double_list));
    ASSERT_TEST(listGetSize(copy_double) == 4);

    listDestroy(string_list);
    listDestroy(double_list);
    listDestroy(copy_double);
    return true;
}

static bool testPrimitiveListInsertBeforeCurrent() {
    ASSERT_TEST(listInsertBeforeCurrent(NULL, NULL) == LIST_NULL_ARGUMENT);
    List string_list = listCreate(copyString, freeString);
    ASSERT_TEST(listInsertFirst(string_list, (void *) "Hello") == LIST_SUCCESS);
    ASSERT_TEST(
            listInsertFirst(string_list, (void *) "WHATSUUP??") ==
            LIST_SUCCESS);
    ASSERT_TEST(listInsertFirst(string_list, (void *) "All g00d Man?")
                == LIST_SUCCESS);
    ASSERT_TEST(listInsertLast(string_list, (void *) "I see you making tests")
                == LIST_SUCCESS);
    ASSERT_TEST(listInsertLast(string_list, (void *) "Don't screw it up!!")
                == LIST_SUCCESS);
    char *str = NULL;
    str = (char *) listGetFirst(string_list);
    ASSERT_TEST(strcmp(str, "All g00d Man?") == 0);
    str = (char *) listGetNext(string_list);
    ASSERT_TEST(strcmp(str, "WHATSUUP??") == 0);
    str = (char *) listGetNext(string_list);
    ASSERT_TEST(strcmp(str, "Hello") == 0);

    str = (char *) listGetCurrent(string_list);
    ASSERT_TEST(strcmp(str, "Hello") == 0);

    ASSERT_TEST(listInsertBeforeCurrent(string_list, "HI IM HERE!_!")
                == LIST_SUCCESS);
    str = (char *) listGetCurrent(string_list);
    ASSERT_TEST(strcmp(str, "Hello") == 0);

    str = (char *) listGetFirst(string_list);
    ASSERT_TEST(strcmp(str, "All g00d Man?") == 0);
    str = (char *) listGetNext(string_list);
    ASSERT_TEST(strcmp(str, "WHATSUUP??") == 0);
    str = (char *) listGetNext(string_list);
    ASSERT_TEST(strcmp(str, "HI IM HERE!_!") == 0);

    listGetNext(string_list);
    listGetNext(string_list);
    listGetNext(string_list);
    listGetNext(string_list);
    listGetNext(string_list);
    ASSERT_TEST(listGetCurrent(string_list) == NULL);
    ASSERT_TEST(listInsertBeforeCurrent(string_list, "NICE TRY man")
                == LIST_INVALID_CURRENT);

    ASSERT_TEST(
            listInsertLast(string_list, (void *) "Last One") == LIST_SUCCESS);
    ASSERT_TEST(listGetSize(string_list) == 7);

    listDestroy(string_list);

    return true;
}

static bool testPrimitiveListInsertAfterCurrent() {
    ASSERT_TEST(listInsertAfterCurrent(NULL, NULL) == LIST_NULL_ARGUMENT);
    List double_list = listCreate(copyDouble, freeDouble);

    double num = 5.43;
    ASSERT_TEST(listInsertFirst(double_list, (void *) &num) == LIST_SUCCESS);
    num = 894.123;
    ASSERT_TEST(listInsertFirst(double_list, (void *) &num) == LIST_SUCCESS);
    num = 9999.9219;
    ASSERT_TEST(listInsertFirst(double_list, (void *) &num) == LIST_SUCCESS);
    num = 3.1;
    ASSERT_TEST(listInsertLast(double_list, (void *) &num) == LIST_SUCCESS);
    ASSERT_TEST(listGetCurrent(double_list) == NULL);

    double checker;
    checker = *(double *) listGetFirst(double_list);
    ASSERT_TEST(checker == 9999.9219);
    ASSERT_TEST(listGetSize(double_list) == 4);
    num = 7;
    ASSERT_TEST(
            listInsertBeforeCurrent(double_list, (void *) &num) ==
            LIST_SUCCESS);
    ASSERT_TEST(listGetSize(double_list) == 5);
    ASSERT_TEST(*(double *) listGetCurrent(double_list) == 9999.9219);
    ASSERT_TEST(*(double *) listGetFirst(double_list) == 7);

    num = 1.15;
    ASSERT_TEST(
            listInsertAfterCurrent(double_list, (void *) &num) == LIST_SUCCESS);
    ASSERT_TEST(*(double *) listGetCurrent(double_list) == 7);
    ASSERT_TEST(*(double *) listGetNext(double_list) == 1.15);
    ASSERT_TEST(listGetSize(double_list) == 6);

    ASSERT_TEST(*(double *) listGetFirst(double_list) == 7);
    ASSERT_TEST(*(double *) listGetNext(double_list) == 1.15);
    ASSERT_TEST(*(double *) listGetNext(double_list) == 9999.9219);
    ASSERT_TEST(*(double *) listGetNext(double_list) == 894.123);

    num = 8.414;
    ASSERT_TEST(
            listInsertAfterCurrent(double_list, (void *) &num) == LIST_SUCCESS);
    ASSERT_TEST(listGetSize(double_list) == 7);
    ASSERT_TEST(*(double *) listGetNext(double_list) == 8.414);
    ASSERT_TEST(*(double *) listGetNext(double_list) == 5.43);
    ASSERT_TEST(*(double *) listGetNext(double_list) == 3.1);
    listGetNext(double_list);
    listGetNext(double_list);
    listGetNext(double_list);

    num = 31209.43;
    ASSERT_TEST(listInsertAfterCurrent(double_list, (void *) &num)
                == LIST_INVALID_CURRENT);

    List copy_double = NULL;
    ASSERT_TEST(copy_double = listCopy(double_list));
    ASSERT_TEST(listGetSize(copy_double) == 7);

    listDestroy(double_list);
    listDestroy(copy_double);

    return true;
}

static bool testPrimitiveListRemoveCurrent() {
    ASSERT_TEST(listRemoveCurrent(NULL) == LIST_NULL_ARGUMENT);
    List string_list = listCreate(copyString, freeString);
    ASSERT_TEST(listRemoveCurrent(string_list) == LIST_INVALID_CURRENT);
    ASSERT_TEST(listInsertFirst(string_list, (void *) "One") == LIST_SUCCESS);
    ASSERT_TEST(listInsertFirst(string_list, (void *) "Two") == LIST_SUCCESS);
    ASSERT_TEST(listInsertFirst(string_list, (void *) "Three") == LIST_SUCCESS);
    ASSERT_TEST(listInsertLast(string_list, (void *) "Four") == LIST_SUCCESS);
    ASSERT_TEST(listInsertLast(string_list, (void *) "SO TIRED OF COUNTING.")
                == LIST_SUCCESS);

    ASSERT_TEST(listGetSize(string_list) == 5);

    char *str = NULL;
    str = (char *) listGetFirst(string_list);
    ASSERT_TEST(strcmp(str, "Three") == 0);
    ASSERT_TEST(listRemoveCurrent(string_list) == LIST_SUCCESS);
    ASSERT_TEST(listGetSize(string_list) == 4);
    str = (char *) listGetFirst(string_list);
    ASSERT_TEST(strcmp(str, "Two") == 0);
    str = (char *) listGetNext(string_list);
    ASSERT_TEST(strcmp(str, "One") == 0);
    str = (char *) listGetNext(string_list);
    ASSERT_TEST(strcmp(str, "Four") == 0);

    ASSERT_TEST(listRemoveCurrent(string_list) == LIST_SUCCESS);
    ASSERT_TEST(listGetSize(string_list) == 3);
    ASSERT_TEST(listGetCurrent(string_list) == NULL);

    str = (char *) listGetFirst(string_list);
    ASSERT_TEST(strcmp(str, "Two") == 0);
    str = (char *) listGetNext(string_list);
    ASSERT_TEST(strcmp(str, "One") == 0);
    str = (char *) listGetNext(string_list);
    ASSERT_TEST(strcmp(str, "SO TIRED OF COUNTING.") == 0);

    listGetNext(string_list);
    ASSERT_TEST(listRemoveCurrent(string_list) == LIST_INVALID_CURRENT);
    listGetNext(string_list);
    listGetNext(string_list);
    listGetNext(string_list);
    ASSERT_TEST(listRemoveCurrent(string_list) == LIST_INVALID_CURRENT);
    ASSERT_TEST(listGetSize(string_list) == 3);

    listDestroy(string_list);
    return true;
}

static bool testPrimitiveListSort() {
    ASSERT_TEST(listSort(NULL, NULL ,0) == LIST_NULL_ARGUMENT);

    List int_list = NULL;
    ASSERT_TEST(int_list = listCreate(copyInt, freeInt));

    ASSERT_TEST(listSort(int_list, NULL ,0) == LIST_NULL_ARGUMENT);
    ASSERT_TEST(listSort(NULL, closerTo , 0) == LIST_NULL_ARGUMENT);

    int num = 8;
    ASSERT_TEST(listInsertLast(int_list, (void *) &num) == LIST_SUCCESS);
    num = 5;
    ASSERT_TEST(listInsertLast(int_list, (void *) &num) == LIST_SUCCESS);
    num = 10;
    ASSERT_TEST(listInsertLast(int_list, (void *) &num) == LIST_SUCCESS);
    num = -60;
    ASSERT_TEST(listInsertLast(int_list, (void *) &num) == LIST_SUCCESS);
    num = 3218;
    ASSERT_TEST(listInsertLast(int_list, (void *) &num) == LIST_SUCCESS);
    ASSERT_TEST(listGetSize(int_list) == 5);
    ASSERT_TEST(listSort(int_list, closerTo,0) == LIST_SUCCESS);

    ASSERT_TEST(*(int *) listGetFirst(int_list) == 3218);
    ASSERT_TEST(*(int *) listGetNext(int_list) == 10);
    ASSERT_TEST(*(int *) listGetNext(int_list) == 8);
    ASSERT_TEST(*(int *) listGetNext(int_list) == 5);
    ASSERT_TEST(*(int *) listGetNext(int_list) == -60);
    num = 6000;
    ASSERT_TEST(
            listInsertBeforeCurrent(int_list, (void *) &num) == LIST_SUCCESS);
    ASSERT_TEST(*(int *) listGetCurrent(int_list) == -60);
    ASSERT_TEST(listGetSize(int_list) == 6);
    ASSERT_TEST(listGetNext(int_list) == NULL);
    ASSERT_TEST(listSort(int_list, closerTo,0) == LIST_SUCCESS);

    ASSERT_TEST(*(int *) listGetFirst(int_list) == 6000);
    ASSERT_TEST(*(int *) listGetNext(int_list) == 3218);
    ASSERT_TEST(*(int *) listGetNext(int_list) == 10);
    ASSERT_TEST(*(int *) listGetNext(int_list) == 8);
    ASSERT_TEST(*(int *) listGetNext(int_list) == 5);
    ASSERT_TEST(*(int *) listGetNext(int_list) == -60);
    listDestroy(int_list);

    return true;
}

static bool testPrimitiveListClear() {
    ASSERT_TEST(listClear(NULL) == LIST_NULL_ARGUMENT);
    return true;
}

static bool testPrimitiveListFilter() {
    ASSERT_TEST(listFilter(NULL, NULL, NULL) == NULL);
    List string_list = listCreate(copyString, freeString);
    ASSERT_TEST(listRemoveCurrent(string_list) == LIST_INVALID_CURRENT);
    ASSERT_TEST(listInsertFirst(string_list, (void *) "Apple") == LIST_SUCCESS);
    ASSERT_TEST(listInsertFirst(string_list, (void *) "Two") == LIST_SUCCESS);
    ASSERT_TEST(listInsertFirst(string_list, (void *) "Three") == LIST_SUCCESS);
    ASSERT_TEST(listInsertLast(string_list, (void *) "Four") == LIST_SUCCESS);
    ASSERT_TEST(listInsertLast(string_list, (void *) "game") == LIST_SUCCESS);
    ASSERT_TEST(listInsertLast(string_list, (void *) "TLV") == LIST_SUCCESS);
    ASSERT_TEST(listInsertLast(string_list, (void *) "PESA") == LIST_SUCCESS);
    ASSERT_TEST(listInsertLast(string_list, (void *) "SO TIRED OF COUNTING.")
                == LIST_SUCCESS);
    ASSERT_TEST(listGetSize(string_list) == 8);

    int length = 5;

    ASSERT_TEST(listFilter(string_list, NULL, (void *) &length) == NULL);
    ASSERT_TEST(listFilter(NULL, isShorterThan, (void *) &length) == NULL);

    List filtered_list = NULL;

    ASSERT_TEST(filtered_list = listFilter(string_list,
                                           isShorterThan, (void *) &length));
    char *str = NULL;
    str = (char *) listGetFirst(filtered_list);
    ASSERT_TEST(strcmp(str, "Two") == 0);
    str = (char *) listGetNext(filtered_list);
    ASSERT_TEST(strcmp(str, "Four") == 0);
    str = (char *) listGetNext(filtered_list);
    ASSERT_TEST(strcmp(str, "game") == 0);
    str = (char *) listGetNext(filtered_list);
    ASSERT_TEST(strcmp(str, "TLV") == 0);
    str = (char *) listGetNext(filtered_list);
    ASSERT_TEST(strcmp(str, "PESA") == 0);
    ASSERT_TEST(listGetSize(filtered_list) == 5);

    listDestroy(filtered_list);
    listDestroy(string_list);

    return true;
}

int compareString(ListElement str1, ListElement str2, ListFilterKey Key) {
    assert(str1 && str2);
    return (-1) * strcmp(str1, str2);
}

static bool testStringListCreate() {
    ASSERT_TEST(listCreate(NULL, NULL) == NULL);
    ASSERT_TEST(listCreate(NULL, NULL) == NULL);
    ASSERT_TEST(listCreate(copyString, NULL) == NULL);
    ASSERT_TEST(listCreate(NULL, freeString) == NULL);
    List list = listCreate(copyString, freeString);
    ASSERT_TEST(list != NULL);

    listDestroy(list);
    return true;
}

static bool testStringListCopy() {
    ASSERT_TEST(listCopy(NULL) == NULL);
    List list1 = listCreate(copyString, freeString);
    ASSERT_TEST(list1 != NULL);
    List copy1 = listCopy(list1);
    ASSERT_TEST(copy1 != NULL);
    ASSERT_TEST(listGetSize(copy1) == 0);
    listInsertFirst(list1, "Breaking Bad");
    ASSERT_TEST(listGetSize(copy1) == 0);
    listInsertLast(list1, "Game of Thrones");
    listInsertLast(list1, "The Borgias");
    listInsertLast(list1, "House of Cards");
    List copy2 = listCopy(list1);
    ASSERT_TEST(listGetSize(copy2) == 4);
    ASSERT_TEST(compareString((char *) listGetFirst(list1),
                              (char *) listGetFirst(copy2),
                              NULL) == 0);
    ASSERT_TEST(compareString((char *) listGetNext(list1),
                              (char *) listGetNext(copy2),
                              NULL) == 0);
    ASSERT_TEST(compareString((char *) listGetNext(list1),
                              (char *) listGetNext(copy2),
                              NULL) == 0);
    ASSERT_TEST(compareString((char *) listGetNext(list1),
                              (char *) listGetNext(copy2),
                              NULL) == 0);
    ASSERT_TEST(listGetNext(list1) == NULL);
    ASSERT_TEST(listGetNext(copy2) == NULL);

    listDestroy(list1);
    listDestroy(copy1);
    listDestroy(copy2);
    return true;
}

static bool testStringListFilter() {
    ASSERT_TEST(listFilter(NULL, isShorterThan, 0) == NULL);
    ASSERT_TEST(listFilter(NULL, NULL, 0) == NULL);
    List list1 = listCreate(copyString, freeString);
    listInsertLast(list1, "3264635472");
    listInsertLast(list1, "board");
    listInsertLast(list1, "whatever");
    listInsertLast(list1, "playground");
    listInsertLast(list1, "if");
    listInsertLast(list1, "you");
    ASSERT_TEST(listFilter(list1, NULL, 0) == NULL);
    ASSERT_TEST(listGetSize(list1) == 6);
    int key = 5;
    List filtered1 = listFilter(list1, isShorterThan, &key);
    ASSERT_TEST(listGetSize(filtered1) == 2);
    ASSERT_TEST(
        compareString((char *) listGetFirst(filtered1), (char *) "if", NULL) ==
            0);
    ASSERT_TEST(
        compareString((char *) listGetNext(filtered1), (char *) "you", NULL) ==
            0);
    ASSERT_TEST(listGetNext(filtered1) == NULL);
    key = -2;
    List filtered2 = listFilter(list1, isShorterThan, &key);
    ASSERT_TEST(listGetSize(filtered2) == 0);
    ASSERT_TEST(listGetFirst(filtered2) == NULL);
    key = 6;
    List filtered3 = listFilter(list1, isShorterThan, &key);
    ASSERT_TEST(listGetSize(filtered3) == 3);
    ASSERT_TEST(
        compareString((char *) listGetFirst(filtered3), (char *) "board", NULL)
            == 0);
    ASSERT_TEST(
        compareString((char *) listGetNext(filtered3), (char *) "if", NULL) == 0);
    ASSERT_TEST(
        compareString((char *) listGetNext(filtered3), (char *) "you", NULL) ==
            0);
    ASSERT_TEST(listGetNext(filtered3) == NULL);

    listDestroy(list1);
    listDestroy(filtered1);
    listDestroy(filtered2);
    listDestroy(filtered3);
    return true;
}

static bool testStringListGetSize() {
    ASSERT_TEST(listGetSize(NULL) == -1);
    List list1 = listCreate(copyString, freeString);
    ASSERT_TEST(listGetSize(list1) == 0);
    listInsertFirst(list1, "Brain wash");
    ASSERT_TEST(listGetSize(list1) == 1);
    listInsertFirst(list1, "Happy Pesach");
    ASSERT_TEST(listGetSize(list1) == 2);
    listInsertFirst(list1, "Boom boom pow");
    ASSERT_TEST(listGetSize(list1) == 3);
    listGetFirst(list1);
    listRemoveCurrent(list1);
    ASSERT_TEST(listGetSize(list1) == 2);
    listGetFirst(list1);
    ASSERT_TEST(listGetNext(list1) != NULL);
    listRemoveCurrent(list1);
    ASSERT_TEST(listGetSize(list1) == 1);

    listDestroy(list1);
    return true;
}

static bool testStringListGetFirst() {
    ASSERT_TEST(listGetFirst(NULL) == NULL);
    List list1 = listCreate(copyString, freeString);
    ASSERT_TEST(listGetFirst(list1) == NULL);
    listInsertFirst(list1, "Boom boom pow");
    ASSERT_TEST(compareString((char *) listGetFirst(list1),
                              (char *) "Boom boom pow",
                              NULL) == 0);
    listInsertBeforeCurrent(list1, "Loaded gun");
    ASSERT_TEST(
        compareString((char *) listGetFirst(list1), (char *) "Loaded gun", NULL)
            == 0);

    listDestroy(list1);
    return true;
}

static bool testStringListGetNext() {
    ASSERT_TEST(listGetNext(NULL) == NULL);
    List list1 = listCreate(copyString, freeString);
    ASSERT_TEST(listGetNext(list1) == NULL);
    listInsertLast(list1, "Bla bla bla");
    listGetFirst(list1);
    ASSERT_TEST(listGetNext(list1) == NULL);
    listInsertLast(list1, "One more time");
    listGetFirst(list1);
    ASSERT_TEST(compareString((char *) listGetNext(list1),
                              (char *) "One more time",
                              NULL) == 0);
    ASSERT_TEST(listGetNext(list1) == NULL);

    listDestroy(list1);
    return true;
}

static bool testStringListGetCurrent() {
    ASSERT_TEST(listGetCurrent(NULL) == NULL);
    List list1 = listCreate(copyString, freeString);
    ASSERT_TEST(listGetCurrent(list1) == NULL);
    listInsertFirst(list1, "Alpaca");
    ASSERT_TEST(listGetCurrent(list1) == NULL);
    listInsertLast(list1, "Camel");
    ASSERT_TEST(listGetCurrent(list1) == NULL);
    listInsertLast(list1, "Leopard");
    ASSERT_TEST(listGetCurrent(list1) == NULL);
    ASSERT_TEST(
        compareString((char *) listGetFirst(list1), (char *) "Alpaca", NULL) ==
            0);
    listInsertBeforeCurrent(list1, "Chupakabra");
    listGetFirst(list1);
    ASSERT_TEST(compareString((char *) listGetCurrent(list1),
                              (char *) "Chupakabra",
                              NULL) == 0);
    listGetNext(list1);
    ASSERT_TEST(
        compareString((char *) listGetCurrent(list1), (char *) "Alpaca", NULL)
            == 0);
    listGetNext(list1);
    ASSERT_TEST(
        compareString((char *) listGetCurrent(list1), (char *) "Camel", NULL) == 0);
    listGetNext(list1);
    ASSERT_TEST(
        compareString((char *) listGetCurrent(list1), (char *) "Leopard", NULL)
            == 0);
    listGetNext(list1);
    ASSERT_TEST(listGetCurrent(list1) == NULL);

    listDestroy(list1);
    return true;
}

static bool testStringListInsertFirst() {
    ASSERT_TEST(LIST_NULL_ARGUMENT == listInsertFirst(NULL, "bank account"));
    List list1 = listCreate(copyString, freeString);
    ASSERT_TEST(LIST_SUCCESS == listInsertFirst(list1, "debt"));
    ASSERT_TEST(LIST_SUCCESS == listInsertFirst(list1, "rent"));
    ASSERT_TEST(LIST_SUCCESS == listInsertFirst(list1, "tuition"));
    ASSERT_TEST(LIST_SUCCESS == listInsertFirst(list1, "no money"));
    ASSERT_TEST(listGetSize(list1) == 4);
    ASSERT_TEST(
        compareString((char *) listGetFirst(list1), (char *) "no money", NULL)
            == 0);
    ASSERT_TEST(
        compareString((char *) listGetNext(list1), (char *) "tuition", NULL) ==
            0);
    ASSERT_TEST(
        compareString((char *) listGetNext(list1), (char *) "rent", NULL) == 0);
    ASSERT_TEST(
        compareString((char *) listGetNext(list1), (char *) "debt", NULL) == 0);
    ASSERT_TEST(listGetNext(list1) == NULL);

    listDestroy(list1);
    return true;
}

static bool testStringListInsertLast() {
    ASSERT_TEST(LIST_NULL_ARGUMENT == listInsertLast(NULL, "bank account"));
    List list1 = listCreate(copyString, freeString);
    ASSERT_TEST(LIST_SUCCESS == listInsertLast(list1, "debt"));
    ASSERT_TEST(LIST_SUCCESS == listInsertLast(list1, "rent"));
    ASSERT_TEST(LIST_SUCCESS == listInsertLast(list1, "tuition"));
    ASSERT_TEST(LIST_SUCCESS == listInsertLast(list1, "no money"));
    ASSERT_TEST(listGetSize(list1) == 4);
    ASSERT_TEST(
        compareString((char *) listGetFirst(list1), (char *) "debt", NULL) == 0);
    ASSERT_TEST(
        compareString((char *) listGetNext(list1), (char *) "rent", NULL) == 0);
    ASSERT_TEST(
        compareString((char *) listGetNext(list1), (char *) "tuition", NULL) ==
            0);
    ASSERT_TEST(
        compareString((char *) listGetNext(list1), (char *) "no money", NULL) ==
            0);
    ASSERT_TEST(listGetNext(list1) == NULL);

    listDestroy(list1);
    return true;
}

static bool testStringListInsertBeforeCurrent() {
    ASSERT_TEST(LIST_NULL_ARGUMENT == listInsertBeforeCurrent(NULL, "effort"));
    List list1 = listCreate(copyString, freeString);
    ASSERT_TEST(listGetCurrent(list1) == NULL);
    ASSERT_TEST(
            LIST_INVALID_CURRENT == listInsertBeforeCurrent(list1, "effort"));
    listInsertFirst(list1, "success");
    ASSERT_TEST(listGetCurrent(list1) == NULL);
    ASSERT_TEST(
            LIST_INVALID_CURRENT == listInsertBeforeCurrent(list1, "effort"));
    listGetFirst(list1);
    ASSERT_TEST(LIST_SUCCESS == listInsertBeforeCurrent(list1, "effort"));
    //Order: effort, success
    ASSERT_TEST(
        compareString((char *) listGetFirst(list1), (char *) "effort", NULL) ==
            0);
    ASSERT_TEST(listGetSize(list1) == 2);
    ASSERT_TEST(
        compareString((char *) listGetNext(list1), (char *) "success", NULL) ==
            0);
    ASSERT_TEST(LIST_SUCCESS == listInsertBeforeCurrent(list1, "tears"));
    ASSERT_TEST(
        compareString((char *) listGetCurrent(list1), (char *) "success", NULL)
            == 0);
    ASSERT_TEST(LIST_SUCCESS == listInsertBeforeCurrent(list1, "blood"));
    ASSERT_TEST(
        compareString((char *) listGetCurrent(list1), (char *) "success", NULL)
            == 0);
    ASSERT_TEST(LIST_SUCCESS == listInsertBeforeCurrent(list1, "sweat"));
    ASSERT_TEST(
        compareString((char *) listGetCurrent(list1), (char *) "success", NULL)
            == 0);
    //Order should be: effort, tears, blood, sweat, success
    ASSERT_TEST(
        compareString((char *) listGetFirst(list1), (char *) "effort", NULL) ==
            0);
    ASSERT_TEST(
        compareString((char *) listGetNext(list1), (char *) "tears", NULL) == 0);
    ASSERT_TEST(
        compareString((char *) listGetNext(list1), (char *) "blood", NULL) == 0);
    ASSERT_TEST(
        compareString((char *) listGetNext(list1), (char *) "sweat", NULL) == 0);
    ASSERT_TEST(
        compareString((char *) listGetNext(list1), (char *) "success", NULL) ==
            0);
    ASSERT_TEST(listGetNext(list1) == NULL);

    listDestroy(list1);
    return true;
}

static bool testStringListInsertAfterCurrent() {
    ASSERT_TEST(LIST_NULL_ARGUMENT == listInsertAfterCurrent(NULL, "effort"));
    List list1 = listCreate(copyString, freeString);
    ASSERT_TEST(listGetCurrent(list1) == NULL);
    ASSERT_TEST(
            LIST_INVALID_CURRENT == listInsertAfterCurrent(list1, "effort"));
    listInsertFirst(list1, "effort");
    ASSERT_TEST(listGetCurrent(list1) == NULL);
    ASSERT_TEST(
            LIST_INVALID_CURRENT == listInsertAfterCurrent(list1, "success"));
    listGetFirst(list1);
    ASSERT_TEST(LIST_SUCCESS == listInsertAfterCurrent(list1, "pain"));
    ASSERT_TEST(strcmp((char *) listGetFirst(list1), (char *) "effort") == 0);
    ASSERT_TEST(listGetSize(list1) == 2);
    ASSERT_TEST(strcmp((char *) listGetNext(list1), (char *) "pain") == 0);
    ASSERT_TEST(LIST_SUCCESS == listInsertAfterCurrent(list1, "tears"));
    ASSERT_TEST(
        compareString((char *) listGetCurrent(list1), (char *) "pain", NULL) ==
            0);
    ASSERT_TEST(LIST_SUCCESS == listInsertAfterCurrent(list1, "sweat"));
    ASSERT_TEST(
        compareString((char *) listGetCurrent(list1), (char *) "pain", NULL) ==
            0);
    listGetNext(list1);
    listGetNext(list1);
    ASSERT_TEST(LIST_SUCCESS == listInsertAfterCurrent(list1, "success"));
    ASSERT_TEST(
        compareString((char *) listGetNext(list1), (char *) "success", NULL) ==
            0);
    ASSERT_TEST(listGetNext(list1) == NULL);
    ASSERT_TEST(LIST_INVALID_CURRENT == listInsertAfterCurrent(list1, "money"));
    ASSERT_TEST(
        compareString((char *) listGetFirst(list1), (char *) "effort", NULL) ==
            0);
    ASSERT_TEST(
        compareString((char *) listGetNext(list1), (char *) "pain", NULL) == 0);
    ASSERT_TEST(
        compareString((char *) listGetNext(list1), (char *) "sweat", NULL) == 0);
    ASSERT_TEST(
        compareString((char *) listGetNext(list1), (char *) "tears", NULL) == 0);
    ASSERT_TEST(
        compareString((char *) listGetNext(list1), (char *) "success", NULL) ==
            0);
    ASSERT_TEST(listGetNext(list1) == NULL);

    listDestroy(list1);
    return true;
}

static bool testStringListRemoveCurrent() {
    ASSERT_TEST(listRemoveCurrent(NULL) == LIST_NULL_ARGUMENT);
    List list1 = listCreate(copyString, freeString);
    ASSERT_TEST(listRemoveCurrent(list1) == LIST_INVALID_CURRENT);
    listInsertFirst(list1, "Brain wash");
    ASSERT_TEST(listGetSize(list1) == 1);
    listGetFirst(list1);
    ASSERT_TEST(compareString((char *) listGetCurrent(list1),
                              (char *) "Brain wash",
                              NULL) == 0);
    listInsertAfterCurrent(list1, "MATAM");
    ASSERT_TEST(listGetSize(list1) == 2);
    ASSERT_TEST(compareString((char *) listGetCurrent(list1),
                              (char *) "Brain wash",
                              NULL) == 0);
    listInsertAfterCurrent(list1, "Homework");
    ASSERT_TEST(listGetSize(list1) == 3);
    ASSERT_TEST(compareString((char *) listGetCurrent(list1),
                              (char *) "Brain wash",
                              NULL) == 0);
    listInsertAfterCurrent(list1, "A thousand lines of code");
    ASSERT_TEST(listGetSize(list1) == 4);
    ASSERT_TEST(compareString((char *) listGetCurrent(list1),
                              (char *) "Brain wash",
                              NULL) == 0);
    listInsertAfterCurrent(list1, "Not fun at all");
    ASSERT_TEST(listGetSize(list1) == 5);
    listGetFirst(list1);
    listGetNext(list1);
    ASSERT_TEST(compareString((char *) listGetCurrent(list1),
                              (char *) "Not fun at all",
                              NULL) == 0);
    ASSERT_TEST(listRemoveCurrent(list1) == LIST_SUCCESS);
    ASSERT_TEST(listRemoveCurrent(list1) == LIST_INVALID_CURRENT);
    ASSERT_TEST(listGetSize(list1) == 4);
    ASSERT_TEST(
        compareString((char *) listGetFirst(list1), (char *) "Brain wash", NULL)
            == 0);
    ASSERT_TEST(compareString((char *) listGetNext(list1),
                              (char *) "A thousand lines of code",
                              NULL) == 0);
    ASSERT_TEST(
        compareString((char *) listGetNext(list1), (char *) "Homework", NULL) ==
            0);
    ASSERT_TEST(
        compareString((char *) listGetNext(list1), (char *) "MATAM", NULL) == 0);
    ASSERT_TEST(listRemoveCurrent(list1) == LIST_SUCCESS); //Remove "MATAM"
    listGetFirst(list1);
    ASSERT_TEST(listRemoveCurrent(list1) == LIST_SUCCESS); //Remove "Brain wash"
    ASSERT_TEST(listGetSize(list1) == 2);
    ASSERT_TEST(compareString((char *) listGetFirst(list1),
                              (char *) "A thousand lines of code",
                              NULL) == 0);
    ASSERT_TEST(
        compareString((char *) listGetNext(list1), (char *) "Homework", NULL) ==
            0);
    ASSERT_TEST(listGetNext(list1) == NULL);

    listDestroy(list1);
    return true;
}

static bool testStringListSort() {
    ASSERT_TEST(listSort(NULL, compareString, NULL) == LIST_NULL_ARGUMENT);
    List list1 = listCreate(copyString, freeString);
    ASSERT_TEST(listSort(NULL, NULL,0) == LIST_NULL_ARGUMENT);
    ASSERT_TEST(listSort(list1, NULL,0) == LIST_NULL_ARGUMENT);
    ASSERT_TEST(listSort(list1, compareString, NULL) == LIST_SUCCESS);
    ASSERT_TEST(LIST_SUCCESS == listInsertLast(list1, "Generic animal"));
    ASSERT_TEST(LIST_SUCCESS == listInsertLast(list1, "Elephant"));
    ASSERT_TEST(LIST_SUCCESS == listInsertLast(list1, "Atudai"));
    ASSERT_TEST(LIST_SUCCESS == listInsertLast(list1, " "));
    ASSERT_TEST(LIST_SUCCESS == listInsertLast(list1, "911"));
    ASSERT_TEST(LIST_SUCCESS == listInsertLast(list1, "@gmail"));
    int num;
    num = strcmp("Generic animal", "Generic animal");
    ASSERT_TEST(num == 0);
    num = strcmp("a", "aaababa");
    ASSERT_TEST(num == -1);
    num = strcmp("babababa", "a");
    ASSERT_TEST(num == 1);

    listSort(list1, compareString, NULL);
    ASSERT_TEST(listGetSize(list1) == 6);
    ASSERT_TEST(compareString((char *) listGetFirst(list1),
                              (char *) "Generic animal",
                              NULL) == 0);
    ASSERT_TEST(
        compareString((char *) listGetNext(list1), (char *) "Elephant", NULL) ==
            0);
    ASSERT_TEST(
        compareString((char *) listGetNext(list1), (char *) "Atudai", NULL) == 0);
    ASSERT_TEST(
        compareString((char *) listGetNext(list1), (char *) "@gmail", NULL) == 0);
    ASSERT_TEST(
        compareString((char *) listGetNext(list1), (char *) "911", NULL) == 0);
    ASSERT_TEST(
        compareString((char *) listGetNext(list1), (char *) " ", NULL) == 0);
    ASSERT_TEST(listGetNext(list1) == NULL);

    listDestroy(list1);
    return true;
}

static bool testStringListClear() {
    ASSERT_TEST(listClear(NULL) == LIST_NULL_ARGUMENT);
    List list1 = listCreate(copyString, freeString);
    ASSERT_TEST(listGetSize(list1) == 0);
    ASSERT_TEST(listClear(list1) == LIST_SUCCESS);
    ASSERT_TEST(list1 != NULL);
    ASSERT_TEST(LIST_SUCCESS == listInsertFirst(list1, "It's"));
    ASSERT_TEST(LIST_SUCCESS == listInsertLast(list1, "a"));
    ASSERT_TEST(LIST_SUCCESS == listInsertLast(list1, "kind"));
    ASSERT_TEST(LIST_SUCCESS == listInsertLast(list1, "of"));
    ASSERT_TEST(LIST_SUCCESS == listInsertLast(list1, "magic"));
    ASSERT_TEST(listGetSize(list1) == 5);
    ASSERT_TEST(
        compareString((char *) listGetFirst(list1), (char *) "It's", NULL) == 0);
    ASSERT_TEST(
        compareString((char *) listGetNext(list1), (char *) "a", NULL) == 0);
    ASSERT_TEST(listClear(list1) == LIST_SUCCESS);
    ASSERT_TEST(listGetFirst(list1) == NULL);
    ASSERT_TEST(listGetNext(list1) == NULL);
    ASSERT_TEST(list1 != NULL);

    listDestroy(list1);
    return true;
}

static bool testStringListDestroy() {
    List list1 = listCreate(copyString, freeString);
    listDestroy(NULL);
    listDestroy(list1);

    return true;
}

int primitiveTest() {
    RUN_TEST(testPrimitiveListCreate);
    RUN_TEST(testPrimitiveListCopy);
    RUN_TEST(testPrimitiveListGetSize);
    RUN_TEST(testPrimitiveListGetFirst);
    RUN_TEST(testPrimitiveListGetNext);
    RUN_TEST(testPrimitiveGetCurrent);
    RUN_TEST(testPrimitiveListInsertFirst);
    RUN_TEST(testPrimitiveListInsertLast);
    RUN_TEST(testPrimitiveListInsertBeforeCurrent);
    RUN_TEST(testPrimitiveListInsertAfterCurrent);
    RUN_TEST(testPrimitiveListRemoveCurrent);
    RUN_TEST(testPrimitiveListSort);
    RUN_TEST(testPrimitiveListClear);
    RUN_TEST(testPrimitiveListFilter);

    RUN_TEST(testStringListCreate);
    RUN_TEST(testStringListCopy);
    RUN_TEST(testStringListFilter);
    RUN_TEST(testStringListGetSize);
    RUN_TEST(testStringListGetFirst);
    RUN_TEST(testStringListGetNext);
    RUN_TEST(testStringListGetCurrent);
    RUN_TEST(testStringListInsertFirst);
    RUN_TEST(testStringListInsertLast);
    RUN_TEST(testStringListInsertBeforeCurrent);
    RUN_TEST(testStringListInsertAfterCurrent);
    RUN_TEST(testStringListRemoveCurrent);
    RUN_TEST(testStringListSort);
    RUN_TEST(testStringListClear);
    RUN_TEST(testStringListDestroy);
    return 0;
}

ListElement copyString(ListElement str) {
    assert(str);
    char *copy = malloc(strlen(str) + 1);
    return copy ? strcpy(copy, str) : NULL;
}

void freeString(ListElement str) {
    free(str);
}

ListElement copyInt(ListElement num) {
    assert(num);
    int *temp = malloc(sizeof(int));
    if (!temp) {
        return NULL;
    }
    *temp = *(int *) num;
    return temp;
}

void freeInt(ListElement num) {
    free(num);
}

ListElement copyDouble(ListElement num) {
    assert(num);
    double *temp = malloc(sizeof(double));
    if (!temp) {
        return NULL;
    }
    *temp = *(double *) num;
    return temp;
}

void freeDouble(ListElement num) {
    free(num);
}

int closerTo(ListElement num1, ListElement num2 , ListSortKey key) {
    return *(int *) num2 - *(int *) num1;
}

bool isShorterThan(ListElement str, ListFilterKey length) {
    if (*(int *) length <= 0) return false;
    return strlen(str) < *(int *) length;
}

//======================= Person Datatype =======================||

typedef struct date_t {
    int day;
    int month;
    int year;
} Date;

typedef struct person_t {
    int id;
    char name[20];
    Date bday;
} Person;

/*
 * Person clone;
	for(int i=0;i<10;i++){
		if(i==0){
	 clone=*(Person*)listGetFirst(personslist);
		clone.id++;
		}
		else{
			clone=*(Person*)listGetNext(personslist);
					clone.id++;
		}
	}
 */

static void *personCopyHelper(void *person) {
    if (!person) {
        return NULL;
    }

    Person *copyp = malloc(sizeof(Person));
    if (!copyp) {
        return NULL;
    }

    *copyp = *(Person *) person;
    return copyp;

}

static void personDestroyHelper(void *person) {

    free(person);
    return;

}

static bool personsFilterByName(void *person, void *key) {
    int length = *(int *) key;
    Person p = *(Person *) person;

    return strlen(p.name) < length;
}

static int personsCompareByBday(void *person1,
                               void *person2,
                               ListFilterKey Key) {

    Person p1 = *(Person *) person1, p2 = *(Person *) person2;

    if (p1.bday.year > p2.bday.year) {
        return -1;
    } else if (p1.bday.year < p2.bday.year) {
        return 1;
    } else {
        if (p1.bday.month > p2.bday.month) {
            return -1;
        } else if (p1.bday.month < p2.bday.month) {
            return 1;
        } else {
            if (p1.bday.year > p2.bday.day) {
                return -1;
            } else if (p1.bday.year < p2.bday.day) {
                return 1;
            } else {
                return 0;
            }
        }
    }
}

static List personsListCreate() {
    Person yossi = {24, "yossi mizrahi", {11, 12, 1990}};
    Person roman = {21, "roman mizrahi", {12, 11, 1991}};
    Person denis = {25, "denis shishkin", {23, 10, 1982}};
    Person simon = {23, "simon zesvi", {12, 04, 1992}};
    Person evgeni = {26, "evgeni tyrov", {29, 02, 1990}};

    List personslist = listCreate(personCopyHelper, personDestroyHelper);
    ASSERT_TEST(listInsertFirst(personslist, &denis) == LIST_SUCCESS);
    ASSERT_TEST(listInsertFirst(personslist, &yossi) == LIST_SUCCESS);
    ASSERT_TEST(listInsertFirst(personslist, &roman) == LIST_SUCCESS);
    ASSERT_TEST(listInsertFirst(personslist, &simon) == LIST_SUCCESS);
    ASSERT_TEST(listInsertFirst(personslist, &evgeni) == LIST_SUCCESS);
    return personslist;
}

static bool testPersonListCreate() {
    ASSERT_TEST(listCreate(NULL, NULL) == NULL);
    ASSERT_TEST(listCreate(personCopyHelper, NULL) == NULL);
    ASSERT_TEST(listCreate(NULL, personDestroyHelper) == NULL);
    List personslist = listCreate(personCopyHelper, personDestroyHelper);
    ASSERT_TEST(personslist != NULL);
    listDestroy(personslist);

    return true;
}

static bool testPersonListCopy() {

    List personslist = personsListCreate();

    List listclone = listCopy(personslist);
    ASSERT_TEST(listclone != NULL);
    ASSERT_TEST(listCopy(NULL) == NULL);
    listDestroy(personslist);
    listDestroy(listclone);

    return true;

}

static bool testPersonListGetSize() {
    List personslist = personsListCreate();
    ASSERT_TEST(listGetSize(NULL) == -1);
    ASSERT_TEST(listGetSize(personslist) == 5);
    listClear(personslist);
    ASSERT_TEST(listGetSize(NULL) == -1);
    listDestroy(personslist);
    return true;
}

static bool testPersonListGetFirst() {
    List personslist = personsListCreate();
    ASSERT_TEST(listGetFirst(personslist) != NULL);
    ASSERT_TEST(listGetFirst(NULL) == NULL);
    listClear(personslist);
    ASSERT_TEST(listGetFirst(personslist) == NULL);
    listDestroy(personslist);
    return true;
}

static bool testPersonListGetCurrent() {
    List personslist = personsListCreate();
    ASSERT_TEST(listGetCurrent(personslist) == NULL);
    ASSERT_TEST(listGetFirst(personslist) != NULL);
    ASSERT_TEST(listGetCurrent(personslist) != NULL);
    ASSERT_TEST(listGetNext(personslist) != NULL);
    ASSERT_TEST(listGetCurrent(personslist) != NULL);
    ASSERT_TEST(listGetNext(personslist) != NULL);
    ASSERT_TEST(listGetCurrent(personslist) != NULL);
    ASSERT_TEST(listGetNext(personslist) != NULL);
    ASSERT_TEST(listGetCurrent(personslist) != NULL);
    ASSERT_TEST(listGetNext(personslist) != NULL);
    ASSERT_TEST(listGetCurrent(personslist) != NULL);
    ASSERT_TEST(listGetNext(NULL) == NULL);
    ASSERT_TEST(listGetNext(personslist) == NULL);
    ASSERT_TEST(listGetCurrent(personslist) == NULL);
    listDestroy(personslist);
    return true;
}

static bool testPersonListGetNext() {
    List pList = personsListCreate();
    ASSERT_TEST(listGetNext(pList) == NULL);
    ASSERT_TEST(listGetFirst(pList) != NULL);
    ASSERT_TEST(listGetNext(pList) != NULL);
    ASSERT_TEST(listGetNext(pList) != NULL);
    ASSERT_TEST(listGetNext(pList) != NULL);
    ASSERT_TEST(listGetNext(pList) != NULL);
    ASSERT_TEST(listGetNext(pList) == NULL);
    ASSERT_TEST(listGetNext(NULL) == NULL);
    listDestroy(pList);
    return true;
}

static bool testPersonListInsertFirst() {
    List personslist = personsListCreate();
    ASSERT_TEST(listInsertFirst(NULL, listGetFirst(personslist))
                == LIST_NULL_ARGUMENT);
    listDestroy(personslist);
    return true;
}

static bool testPersonListInsertLast() {
    List personslist = personsListCreate();
    ASSERT_TEST(listInsertLast(NULL, listGetFirst(personslist))
                == LIST_NULL_ARGUMENT);
    ASSERT_TEST(listInsertLast(personslist, listGetFirst(personslist))
                == LIST_SUCCESS);
    ASSERT_TEST(listInsertLast(personslist, listGetNext(personslist))
                == LIST_SUCCESS);
    ASSERT_TEST(listInsertLast(personslist, listGetNext(personslist))
                == LIST_SUCCESS);
    ASSERT_TEST(listInsertLast(personslist, listGetNext(personslist))
                == LIST_SUCCESS);
    ASSERT_TEST(listInsertLast(personslist, listGetNext(personslist))
                == LIST_SUCCESS);
    listDestroy(personslist);

    return true;
}

static bool testPersonListInsertBeforeCurrent() {
    List personslist = personsListCreate();
    ASSERT_TEST(listInsertBeforeCurrent(NULL, listGetFirst(personslist))
                == LIST_NULL_ARGUMENT);
    ASSERT_TEST(listInsertBeforeCurrent(personslist, listGetFirst(personslist))
                == LIST_SUCCESS);
    ASSERT_TEST(listInsertBeforeCurrent(personslist, listGetNext(personslist))
                == LIST_SUCCESS);
    ASSERT_TEST(listInsertBeforeCurrent(personslist, listGetNext(personslist))
                == LIST_SUCCESS);
    ASSERT_TEST(listInsertBeforeCurrent(personslist, listGetNext(personslist))
                == LIST_SUCCESS);
    ASSERT_TEST(listInsertBeforeCurrent(personslist, listGetNext(personslist))
                == LIST_SUCCESS);

    listDestroy(personslist);
    return true;
}

static bool testPersonListInsertAfterCurrent() {
    List personslist = personsListCreate();
    ASSERT_TEST(listInsertAfterCurrent(NULL, listGetFirst(personslist))
                == LIST_NULL_ARGUMENT);
    ASSERT_TEST(listInsertAfterCurrent(personslist, listGetFirst(personslist))
                == LIST_SUCCESS);
    listGetNext(personslist);
    ASSERT_TEST(listInsertAfterCurrent(personslist, listGetNext(personslist))
                == LIST_SUCCESS);
    listGetNext(personslist);
    ASSERT_TEST(listInsertAfterCurrent(personslist, listGetNext(personslist))
                == LIST_SUCCESS);
    listGetNext(personslist);
    ASSERT_TEST(listInsertAfterCurrent(personslist, listGetNext(personslist))
                == LIST_SUCCESS);
    listGetNext(personslist);
    ASSERT_TEST(listInsertAfterCurrent(personslist, listGetNext(personslist))
                == LIST_SUCCESS);
    listGetNext(personslist);

    listDestroy(personslist);
    return true;
}

static bool testPersonListRemoveCurrent() {
    List personslist = personsListCreate();
    ASSERT_TEST(listRemoveCurrent(personslist) == LIST_INVALID_CURRENT);
    ASSERT_TEST(listRemoveCurrent(NULL) == LIST_NULL_ARGUMENT);
    listGetFirst(personslist);
    ASSERT_TEST(listRemoveCurrent(personslist) == LIST_SUCCESS);
    listGetFirst(personslist);
    listGetNext(personslist);
    listGetNext(personslist);
    ASSERT_TEST(listRemoveCurrent(personslist) == LIST_SUCCESS);
    listGetFirst(personslist);
    listGetNext(personslist);
    listGetNext(personslist);
    ASSERT_TEST(listRemoveCurrent(personslist) == LIST_SUCCESS);
    listGetFirst(personslist);
    listGetNext(personslist);
    listGetNext(personslist);
    ASSERT_TEST(listRemoveCurrent(personslist) == LIST_INVALID_CURRENT);
    listGetFirst(personslist);
    ASSERT_TEST(listRemoveCurrent(personslist) == LIST_SUCCESS);
    listGetFirst(personslist);
    listSort(personslist, personsCompareByBday, NULL);
    ASSERT_TEST(listRemoveCurrent(personslist) == LIST_SUCCESS);

    listDestroy(personslist);
    return true;
}

static bool testPersonListSort() {
    List personslist = personsListCreate();
    ASSERT_TEST(listSort(NULL, personsCompareByBday, NULL) == LIST_NULL_ARGUMENT);
    ASSERT_TEST(listSort(personslist, NULL,0) == LIST_NULL_ARGUMENT);
    ASSERT_TEST(
        listSort(personslist, personsCompareByBday, NULL) == LIST_SUCCESS);
    listDestroy(personslist);

    return true;
}

static bool testPersonListFilter() {
    List personslist = personsListCreate();
    int key = 12;
    ASSERT_TEST(listFilter(NULL, personsFilterByName, &key) == NULL);
    ASSERT_TEST(listFilter(personslist, NULL, &key) == NULL);

    List filtredlist = listFilter(personslist, personsFilterByName, &key);
    ASSERT_TEST(filtredlist != NULL);

    listDestroy(filtredlist);
    listDestroy(personslist);

    return true;
}

static bool testPersonListClear() {
    List personslist = personsListCreate();
    ASSERT_TEST(listClear(NULL) == LIST_NULL_ARGUMENT);
    ASSERT_TEST(listClear(personslist) == LIST_SUCCESS);

    listDestroy(personslist);
    return true;
}

static bool testPersonListDestroy() {
    List personslist = personsListCreate();
    listDestroy(personslist);

    return true;
}

int personTest() {

    RUN_TEST(testPersonListCreate);
    RUN_TEST(testPersonListCopy);
    RUN_TEST(testPersonListGetSize);
    RUN_TEST(testPersonListGetFirst);
    RUN_TEST(testPersonListGetNext);
    RUN_TEST(testPersonListGetCurrent);
    RUN_TEST(testPersonListInsertFirst);
    RUN_TEST(testPersonListInsertLast);
    RUN_TEST(testPersonListInsertBeforeCurrent);
    RUN_TEST(testPersonListInsertAfterCurrent);
    RUN_TEST(testPersonListRemoveCurrent);
    RUN_TEST(testPersonListSort);
    RUN_TEST(testPersonListFilter);
    RUN_TEST(testPersonListClear);
    RUN_TEST(testPersonListDestroy);
    return 0;

}

//======================= Student Datatype =======================||

#define ASSERT_SAME_STUDENT(a, b) ASSERT_TEST(studentCompare(a,b) == 0)

enum months {
    JAN = 1, FEB, MAR, APR, MAY, JUN, JUL, AUG, SEP, OCT, NOV,
    DEC
};

/* Tests for Student element */
typedef struct date_t *pDate;

typedef struct Student_t {
    char *name;
    int id;
    pDate date;
} *Student;

static Student studentCreate(const char *name, int id, int day,
                             int month, int year);

static Student studentCopy(Student student);

static void studentDestroy(Student student);

static int studentCompare(Student a, Student b);

static char *stringDuplicate(const char *str);

static char *stringDuplicate(const char *str) {
    assert(str);
    char *result = malloc(strlen(str) + 1);
    return result ? strcpy(result, str) : NULL;
}

static void studentDestroy(Student student) {
    if (!student) {
        return;
    }
    free(student->name);
    free(student->date);
    free(student);
}

static Student studentCreate(const char *name, int id, int day,
                             int month, int year) {
    assert(name);
    Student student = malloc(sizeof(struct Student_t));
    if (!student) {
        return NULL;
    }
    student->name = stringDuplicate(name);
    if (!name) {
        studentDestroy(student);
        return NULL;
    }

    pDate date = malloc(sizeof(struct date_t));
    if (!date) {
        return NULL;
    }
    date->day = day;
    date->month = month;
    date->year = year;

    student->id = id;
    student->date = date;

    return student;
}

static Student studentCopy(Student student) {
//	assert(student);
    return studentCreate(student->name, student->id, student->date->day,
                         student->date->month, student->date->year);
}

static int studentCompare(Student a, Student b) {
    assert(a && b);

    if (a->date->year < b->date->year) {
        return 1;
    } else if (a->date->year > b->date->year) {
        return -1;
    }

    return 0;
}

static ListElement studentCopyHelper(ListElement element) {
    return studentCopy(element);
}

static void studentDestroyHelper(ListElement element) {
    studentDestroy(element);
}

static int studentCompareHelper(ListElement element1,
                               ListElement element2,
                               ListFilterKey Key) {
    return studentCompare(element1, element2);
}

static bool bornAfter(ListElement student, ListFilterKey key) {
    Student temp = (Student) student;
    return temp->date->year >= *(int *) key;
}

/**
 * This struct is used to hold a set of examples
 * This allows us to save code on reinitializing big examples in the start of
 * each test
 */
typedef struct {
    Student avivTzenzor;
    Student alizaMalek;
    Student davidZilag;
    Student yehielKimchi;
    Student yossiCohen;
    Student tamerSalman;
    List list;
} Examples;

/**
 * This function is called by the SET_UP macro in testing_utilities. This
 * function should initialize an examples struct that can be used for testing
 * the ADT
 * @return a new fully initialize examples sturct
 */
static Examples setUp() {
    Examples examples;
    examples.avivTzenzor = studentCreate
            ("Aviv Tzenzor", 111111111, 12, JAN, 1980);
    examples.alizaMalek = studentCreate
            ("Aliza Malek", 222222222, 2, MAR, 1976);
    examples.davidZilag = studentCreate
            ("David Zilag", 333333333, 23, JUN, 1969);
    examples.yehielKimchi = studentCreate
            ("Yehiel Kimchi", 444444444, 7, FEB, 1972);
    examples.yossiCohen = studentCreate
            ("Yossi Cohen", 555555555, 12, AUG, 1963);
    examples.tamerSalman = studentCreate
            ("Tamer Salman", 666666666, 12, APR, 1987);

    examples.list = listCreate(studentCopyHelper, studentDestroyHelper);
    listInsertLast(examples.list, examples.davidZilag);
    listInsertLast(examples.list, examples.alizaMalek);
    listInsertLast(examples.list, examples.yehielKimchi);
    listInsertLast(examples.list, examples.avivTzenzor);
    listInsertLast(examples.list, examples.tamerSalman);
    return examples;
}

/**
 * Called by the TEAR_DOWN macro from testing_utilities.h. This function should
 * deallocate and clear all the code
 * @param examples
 */
void tearDown(Examples examples) {
    studentDestroy(examples.avivTzenzor);
    studentDestroy(examples.alizaMalek);
    studentDestroy(examples.davidZilag);
    studentDestroy(examples.yehielKimchi);
    studentDestroy(examples.yossiCohen);
    studentDestroy(examples.tamerSalman);
    listDestroy(examples.list);
}

/**
 * List of tests, one for each function is usually a good thumb rule.
 */
static bool testStudentListCreate() {
    ASSERT_TEST(listCreate(NULL, NULL) == NULL);
    ASSERT_TEST(listCreate(NULL, NULL) == NULL);
    ASSERT_TEST(listCreate(studentCopyHelper, NULL) == NULL);
    ASSERT_TEST(listCreate(NULL, studentDestroyHelper) == NULL);
    List list = listCreate(studentCopyHelper, studentDestroyHelper);
    ASSERT_TEST(list != NULL);
    listDestroy(list);

    return true;
}

static bool testStudentListCopy() {
    SET_UP(Examples);
    ASSERT_TEST(listCopy(NULL) == NULL);
    List list = listCreate(studentCopyHelper, studentDestroyHelper);
    List copy = listCopy(list);
    ASSERT_TEST(copy != NULL);
    ASSERT_TEST(0 == listGetSize(copy));
    listInsertFirst(list, examples.yehielKimchi);
    ASSERT_TEST(0 == listGetSize(copy));

    List copy2 = listCopy(examples.list);
    ASSERT_TEST(5 == listGetSize(copy2));
    ASSERT_SAME_STUDENT(examples.davidZilag, listGetFirst(copy2));
    ASSERT_SAME_STUDENT(examples.alizaMalek, listGetNext(copy2));
    ASSERT_SAME_STUDENT(examples.yehielKimchi, listGetNext(copy2));
    ASSERT_SAME_STUDENT(examples.avivTzenzor, listGetNext(copy2));
    ASSERT_SAME_STUDENT(examples.tamerSalman, listGetNext(copy2));
    ASSERT_TEST(listGetNext(copy2) == NULL);

    listDestroy(list);
    listDestroy(copy);
    listDestroy(copy2);
    TEAR_DOWN();

    return true;
}

static bool testStudentListFilter() {
    SET_UP(Examples);
    ASSERT_TEST(LIST_SUCCESS == listInsertFirst
            (examples.list, examples.yossiCohen));
    ASSERT_TEST(6 == listGetSize(examples.list));
    int key = 1975;
    List list = listFilter(examples.list, bornAfter, &key);
    ASSERT_SAME_STUDENT(examples.alizaMalek, listGetFirst(list));
    ASSERT_SAME_STUDENT(examples.avivTzenzor, listGetNext(list));
    ASSERT_SAME_STUDENT(examples.tamerSalman, listGetNext(list));
    ASSERT_TEST(listGetNext(list) == NULL);
    listDestroy(list);
    TEAR_DOWN();
    return true;
}

static bool testStudentListGetSize() {
    SET_UP(Examples);
    List list = listCreate(studentCopyHelper, studentDestroyHelper);
    ASSERT_TEST(0 == listGetSize(list));
    listInsertFirst(list, examples.yehielKimchi);
    ASSERT_TEST(1 == listGetSize(list));
    listInsertFirst(list, examples.yehielKimchi);
    ASSERT_TEST(2 == listGetSize(list));
    listGetFirst(list);
    listRemoveCurrent(list);
    ASSERT_TEST(1 == listGetSize(list));
    listDestroy(list);
    TEAR_DOWN();
    return true;
}

static bool testStudentListGetFirst() {
    SET_UP(Examples);
    List list = listCreate(studentCopyHelper, studentDestroyHelper);
    ASSERT_TEST(listGetFirst(list) == NULL);
    Student first = listGetFirst(examples.list);
    ASSERT_SAME_STUDENT(examples.davidZilag, first);
    ASSERT_SAME_STUDENT(first, listGetFirst(examples.list));
    listDestroy(list);
    TEAR_DOWN();
    return true;
}

static bool testStudentListGetNext() {
    SET_UP(Examples);
    ASSERT_TEST(listGetNext(NULL) == NULL);
    ASSERT_TEST(listGetNext(examples.list) == NULL);
    TEAR_DOWN();
    return true;
}

static bool testStudentListGetCurrent() {
    SET_UP(Examples);
    ASSERT_TEST(listGetCurrent(examples.list) == NULL);
    ASSERT_TEST(listGetFirst(examples.list) != NULL);
    ASSERT_SAME_STUDENT(examples.davidZilag, listGetFirst(examples.list));
    ASSERT_SAME_STUDENT(examples.davidZilag, listGetCurrent(examples.list));
    ASSERT_SAME_STUDENT(examples.alizaMalek, listGetNext(examples.list));
    ASSERT_SAME_STUDENT(examples.yehielKimchi, listGetNext(examples.list));
    ASSERT_SAME_STUDENT(examples.avivTzenzor, listGetNext(examples.list));
    ASSERT_SAME_STUDENT(examples.tamerSalman, listGetNext(examples.list));
    ASSERT_SAME_STUDENT(examples.tamerSalman, listGetCurrent(examples.list));
    ASSERT_SAME_STUDENT(examples.davidZilag, listGetFirst(examples.list));
    List copy = listCopy(examples.list);
    //ASSERT_SAME_STUDENT(examples.davidZilag, listGetCurrent(copy));
    listDestroy(copy);
    TEAR_DOWN();
    return true;
}

static bool testStudentListInsertFirst() {
    SET_UP(Examples);
    ASSERT_TEST(LIST_NULL_ARGUMENT == listInsertFirst(NULL, NULL));
    ASSERT_TEST(LIST_SUCCESS ==
                listInsertFirst(examples.list, examples.yossiCohen));
    ASSERT_TEST(6 == listGetSize(examples.list));
    ASSERT_SAME_STUDENT(examples.yossiCohen, listGetFirst(examples.list));
    ASSERT_SAME_STUDENT(examples.davidZilag, listGetNext(examples.list));
    ASSERT_SAME_STUDENT(examples.alizaMalek, listGetNext(examples.list));
    ASSERT_SAME_STUDENT(examples.yehielKimchi, listGetNext(examples.list));
    ASSERT_SAME_STUDENT(examples.avivTzenzor, listGetNext(examples.list));
    ASSERT_SAME_STUDENT(examples.tamerSalman, listGetNext(examples.list));
    ASSERT_TEST(listGetNext(examples.list) == NULL);
    TEAR_DOWN();
    return true;
}

static bool testStudentListInsertLast() {
    SET_UP(Examples);
    ASSERT_TEST(LIST_NULL_ARGUMENT == listInsertLast(NULL, NULL));
    ASSERT_TEST(LIST_SUCCESS ==
                listInsertLast(examples.list, examples.yossiCohen));
    ASSERT_TEST(6 == listGetSize(examples.list));
    ASSERT_SAME_STUDENT(examples.davidZilag, listGetFirst(examples.list));
    ASSERT_SAME_STUDENT(examples.alizaMalek, listGetNext(examples.list));
    ASSERT_SAME_STUDENT(examples.yehielKimchi, listGetNext(examples.list));
    ASSERT_SAME_STUDENT(examples.avivTzenzor, listGetNext(examples.list));
    ASSERT_SAME_STUDENT(examples.tamerSalman, listGetNext(examples.list));
    ASSERT_SAME_STUDENT(examples.yossiCohen, listGetNext(examples.list));
    ASSERT_TEST(listGetNext(examples.list) == NULL);
    TEAR_DOWN();
    return true;
}

static bool testStudentListInsertBeforeCurrent() {
    SET_UP(Examples);
    ASSERT_TEST(LIST_NULL_ARGUMENT == listInsertBeforeCurrent(NULL, NULL));
    listGetFirst(examples.list);
    listGetNext(examples.list);
    ASSERT_TEST(LIST_SUCCESS == listInsertBeforeCurrent
            (examples.list, examples.yossiCohen));

    ASSERT_TEST(6 == listGetSize(examples.list));
    ASSERT_SAME_STUDENT(examples.davidZilag, listGetFirst(examples.list));
    ASSERT_SAME_STUDENT(examples.yossiCohen, listGetNext(examples.list));
    ASSERT_SAME_STUDENT(examples.alizaMalek, listGetNext(examples.list));
    ASSERT_SAME_STUDENT(examples.yehielKimchi, listGetNext(examples.list));
    ASSERT_SAME_STUDENT(examples.avivTzenzor, listGetNext(examples.list));
    ASSERT_SAME_STUDENT(examples.tamerSalman, listGetNext(examples.list));
    ASSERT_TEST(listGetNext(examples.list) == NULL);
    TEAR_DOWN();
    return true;
}

static bool testStudentListInsertAfterCurrent() {
    SET_UP(Examples);
    ASSERT_TEST(LIST_NULL_ARGUMENT == listInsertAfterCurrent(NULL, NULL));
    listGetFirst(examples.list);
    listGetNext(examples.list);
    ASSERT_TEST(LIST_SUCCESS ==
                listInsertAfterCurrent(examples.list, examples.yossiCohen));

    ASSERT_TEST(6 == listGetSize(examples.list));
    ASSERT_SAME_STUDENT(examples.davidZilag, listGetFirst(examples.list));
    ASSERT_SAME_STUDENT(examples.alizaMalek, listGetNext(examples.list));
    ASSERT_SAME_STUDENT(examples.yossiCohen, listGetNext(examples.list));
    ASSERT_SAME_STUDENT(examples.yehielKimchi, listGetNext(examples.list));
    ASSERT_SAME_STUDENT(examples.avivTzenzor, listGetNext(examples.list));
    ASSERT_SAME_STUDENT(examples.tamerSalman, listGetNext(examples.list));
    ASSERT_TEST(listGetNext(examples.list) == NULL);
    TEAR_DOWN();
    return true;
}

static bool testStudentListRemoveCurrent() {
    SET_UP(Examples);
    ASSERT_TEST(LIST_NULL_ARGUMENT == listRemoveCurrent(NULL));
    ASSERT_TEST(LIST_INVALID_CURRENT == listRemoveCurrent(examples.list));

    listGetFirst(examples.list);
    listGetNext(examples.list);
    listRemoveCurrent(examples.list);
    ASSERT_TEST(4 == listGetSize(examples.list));
    ASSERT_SAME_STUDENT(examples.davidZilag, listGetFirst(examples.list));
    ASSERT_SAME_STUDENT(examples.yehielKimchi, listGetNext(examples.list));
    ASSERT_SAME_STUDENT(examples.avivTzenzor, listGetNext(examples.list));
    ASSERT_SAME_STUDENT(examples.tamerSalman, listGetNext(examples.list));
    ASSERT_TEST(listGetNext(examples.list) == NULL);

    ASSERT_TEST(LIST_INVALID_CURRENT == listRemoveCurrent(examples.list));
    TEAR_DOWN();
    return true;
}

static bool testStudentListSort() {
    SET_UP(Examples);
    ASSERT_TEST(LIST_NULL_ARGUMENT == listSort(NULL, NULL,0));
    List list = listCreate(studentCopyHelper, studentDestroyHelper);
    ASSERT_TEST(LIST_NULL_ARGUMENT == listSort(list, NULL,0));
    ASSERT_TEST(LIST_NULL_ARGUMENT == listSort(NULL, studentCompareHelper, NULL));
    listDestroy(list);
    ASSERT_TEST(LIST_SUCCESS == listInsertFirst
            (examples.list, examples.yossiCohen));
  listSort(examples.list, studentCompareHelper, NULL);
    ASSERT_TEST(6 == listGetSize(examples.list));

    ASSERT_SAME_STUDENT(examples.tamerSalman, listGetFirst(examples.list));
    ASSERT_SAME_STUDENT(examples.avivTzenzor, listGetNext(examples.list));
    ASSERT_SAME_STUDENT(examples.alizaMalek, listGetNext(examples.list));
    ASSERT_SAME_STUDENT(examples.yehielKimchi, listGetNext(examples.list));
    ASSERT_SAME_STUDENT(examples.davidZilag, listGetNext(examples.list));
    ASSERT_SAME_STUDENT(examples.yossiCohen, listGetNext(examples.list));

    ASSERT_TEST(listGetNext(examples.list) == NULL);
    TEAR_DOWN();
    return true;
}

static bool testStudentListClear() {
    SET_UP(Examples);
    ASSERT_TEST(listClear(examples.list) == LIST_SUCCESS);
    ASSERT_TEST(0 == listGetSize(examples.list));
    List list = listCreate(studentCopyHelper, studentDestroyHelper);
    listClear(list);
    ASSERT_TEST(0 == listGetSize(list));
    listDestroy(list);
    TEAR_DOWN();
    return true;
}

static bool testStudentListDestroy() {
    listDestroy(NULL);
    return true;
}

//**======================= String testing functions =========================*/

int studentTest() {
    RUN_TEST(testStudentListCreate);
    RUN_TEST(testStudentListCopy);
    RUN_TEST(testStudentListFilter);
    RUN_TEST(testStudentListGetSize);
    RUN_TEST(testStudentListGetFirst);
    RUN_TEST(testStudentListGetNext);
    RUN_TEST(testStudentListGetCurrent);
    RUN_TEST(testStudentListInsertFirst);
    RUN_TEST(testStudentListInsertLast);
    RUN_TEST(testStudentListInsertBeforeCurrent);
    RUN_TEST(testStudentListInsertAfterCurrent);
    RUN_TEST(testStudentListRemoveCurrent);
    RUN_TEST(testStudentListSort);
    RUN_TEST(testStudentListClear);
    RUN_TEST(testStudentListDestroy);
    return 0;
}

int main() {
    primitiveTest();
    personTest();
    studentTest();

    return 0;
}