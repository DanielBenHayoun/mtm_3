//
// Created by Dina on 16-Dec-17.
//

#ifndef EX3_FRIEND_H
#define EX3_FRIEND_H

#include "set.h"

typedef struct friend_t *Friend;

///===================GENERIC FUNCTIONS====================================
SetElement setCopyFriend(SetElement element);

void setFreeFriend(SetElement element);

int setCompareFriend(SetElement element1, SetElement element2);

///========================================================================
/**
 * Creates a new friend according to the given parameters. allocates new space.
 * to destroy a friend the function destroyFriend should be used.
 * @param id - given id
 * @param first_name -given first name
 * @param last_name - given last name
 * @param max_grade - given grade
 * @return the new friend created
 *         if the creation failed returns NULL.
 */
Friend createFriend(int id, char *first_name, char *last_name, int max_grade);

/**
 * deallocates an existing friend. frees all the memory that was allocated
 * when creating the friend.
 * @param friend - target friend to be deallocated
 */
void destroyFriend (Friend friend);

/**
 * returns the given friend id.
 * @param friend - given friend
 * @return -1 if the parameter friend is NULL
 *         given friend's id otherwise
 */
int getFriendId( Friend friend);

/**
 * returns the given friend grade.
 * @param friend - given friend
 * @return -1 if the parameter friend is NULL
 *         given friend's grade otherwise
 */
int getFriendGrade(Friend friend);

/**
 * returns the pointer to the given friend's first name.
 * @param friend - given friend
 * @return NULL if the parameter friend is NULL
 *         the pointer to the given friend's first name otherwise.
 */
char* getFriendFirstName(Friend friend);

/**
 * returns the pointer to the given friend's last name.
 * @param friend - given friend
 * @return NULL if the parameter friend is NULL
 *         the pointer to the given friend's last name otherwise.
 */
char* getFriendLastName(Friend friend);


#endif //EX3_FRIEND_H
