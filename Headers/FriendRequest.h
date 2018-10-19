//
// Created by daniel on 12/14/2017.
//

#ifndef MTM_EX3_REQUESTS_H
#define MTM_EX3_REQUESTS_H

#include "set.h"
#include <stdbool.h>


typedef struct  friend_request_t *FriendRequest;

typedef enum {
  REQ_APPROVED,
  REQ_WAITING,
  REQ_APPROVED_DENIED
} ReqResult;

///=================GENERIC FUNCTIONS========================================
SetElement copyFriendReq(SetElement element);

void freeFriendReq(SetElement element);

int cmpFriendReq(SetElement element1, SetElement element2);

///==========================================================================

/**
 * Creates a new friend request according to the given parameters. allocates new
 * space.to destroy a friend request the function destroyFriendReq should be
 * used.
 * @param asking_student_id - id of whom the request was sent from
 * @return the new friend request created
 *         if the creation failed returns NULL.
 */
FriendRequest createFriendReq (int asking_student_id);

/**
 * deallocates an existing friend request. frees all the memory that was
 * allocated when creating the friend request.
 * @param friendRequest - target friend request to be deallocated
 */
void destroyFriendReq(FriendRequest friendRequest);

/**
 * returns the id of the friend request
 * @param friendRequest - given friend request
 * @return -1 if the parameter friendRequest is NULL
 *         given friend request's id otherwise
 */
int getFriendReqId( FriendRequest friendRequest);


#endif //MTM_EX3_REQUESTS_H
