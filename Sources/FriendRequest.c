
#include "../Headers/FriendRequest.h"
#include "../Headers/set.h"
#include <stdlib.h>
#include <assert.h>

struct  friend_request_t{
  int asking_student_id;
};

SetElement copyFriendReq(SetElement element){
  FriendRequest old_req = (FriendRequest)element;
  FriendRequest new_req = createFriendReq(old_req->asking_student_id);
  if (new_req == NULL) return NULL;
  return new_req;
}
void freeFriendReq(SetElement element){
  if(!element)
    return;
  FriendRequest request=(FriendRequest)element;
  destroyFriendReq(request);
}
int cmpFriendReq(SetElement element1, SetElement element2){
  FriendRequest req1 = (FriendRequest)element1;
  FriendRequest req2 = (FriendRequest)element2;
  if (req1->asking_student_id > req2->asking_student_id) return 1;
  if (req1->asking_student_id < req2->asking_student_id) return -1;
  return 0;
}

FriendRequest createFriendReq (int asking_student_id){
  assert(asking_student_id > 0);
  FriendRequest new = malloc(sizeof(*new));
  if (new == NULL) return NULL;
  new->asking_student_id = asking_student_id;
  return new;
}

void destroyFriendReq(FriendRequest friendRequest){
  free(friendRequest);
}


int getFriendReqId( FriendRequest friendRequest){
  if (!friendRequest) return -1;
  return friendRequest->asking_student_id;
}


