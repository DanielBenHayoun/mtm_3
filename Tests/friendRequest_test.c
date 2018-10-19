#include "test_utilities.h"
#include "../Headers/FriendRequest.h"


bool test_getFriendReqId(){
  FriendRequest friendRequest=createFriendReq(3);
  ASSERT_TEST(getFriendReqId(friendRequest)==3);
  destroyFriendReq(friendRequest);
  ASSERT_TEST(getFriendReqId(NULL)==-1);
  return true;
}





int main(){
  RUN_TEST(test_getFriendReqId);
  return 0;
}