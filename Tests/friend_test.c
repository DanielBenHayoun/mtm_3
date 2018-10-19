//
// Created by daniel on 1/8/2018.
//

#include "../Headers/Friend.h"
#include "../Headers/test_utilities.h"
#include <string.h>

bool test_Friend(){
  Friend aFriend=createFriend(1,"a","A",0);
  Friend bFriend=createFriend(1,"b","B",0);
  Friend cFriend=createFriend(1,"c","C",0);
  ASSERT_TEST(strcmp(getFriendFirstName(aFriend),"a")==0);
  ASSERT_TEST(strcmp(getFriendFirstName(bFriend),"b")==0);
  ASSERT_TEST(strcmp(getFriendFirstName(bFriend),"b")==0);
  ASSERT_TEST(strcmp(getFriendLastName(aFriend),"A" )==0);
  ASSERT_TEST(strcmp(getFriendLastName(bFriend),"B" )==0);
  ASSERT_TEST(strcmp(getFriendLastName(cFriend),"C" )==0);
  destroyFriend(aFriend);
  destroyFriend(bFriend);
  destroyFriend(cFriend);

  return true;

}

int main(){
  RUN_TEST(test_Friend);
  return 0;
}