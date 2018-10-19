//
// Created by Dina on 16-Dec-17.
//

#include "../Headers/set.h"
#include "../Headers/Friend.h"
#include <stdlib.h>
#include <assert.h>
#include <string.h>

struct friend_t {
  int id;
  char *first_name;
  char *last_name;
  int max_grade;
};


SetElement setCopyFriend(SetElement element){
  Friend old = (Friend)element;
  Friend new=createFriend(old->id,old->first_name,old->last_name,old->max_grade);
  if (new == NULL) return NULL;
  return new;
}

void setFreeFriend(SetElement element){
  Friend friend = (Friend)element;
  destroyFriend(friend);
}

int setCompareFriend(SetElement element1, SetElement element2){
  Friend friend1 = (Friend)element1;
  Friend friend2 = (Friend)element2;
  return friend1->id - friend2->id;
}


Friend createFriend(int id, char *first_name, char *last_name, int max_grade) {
  if (first_name == NULL || last_name == NULL) return NULL;
  Friend friend = malloc(sizeof(*friend));
  if (friend == NULL) return NULL;
  friend->id= id;
  friend->max_grade=max_grade;
  friend->first_name = malloc(strlen(first_name)+1);
  if (friend->first_name == NULL){
    free(friend);
    return NULL;
  }
  strcpy(friend->first_name, first_name);
  friend->last_name = malloc(strlen(last_name)+1);
  if (friend->last_name == NULL){
    free(friend->first_name);
    free(friend);
    return NULL;
  }
  strcpy(friend->last_name, last_name);
  return friend;
}

void destroyFriend (Friend friend){
  free(friend->first_name);
  free(friend->last_name);
  free(friend);
}

int getFriendId( Friend friend){
  if(!friend) return -1;
  return friend->id;
}

int getFriendGrade(Friend friend){
  if(!friend) return -1;
  return friend->max_grade;
}

char* getFriendFirstName(Friend friend){
  if(!friend)return NULL;
  return friend->first_name;
}

char* getFriendLastName(Friend friend){
  if(!friend)return NULL;
  return friend->last_name;
}