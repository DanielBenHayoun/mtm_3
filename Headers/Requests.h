//
// Created by daniel on 12/14/2017.
//

#ifndef MTM_EX3_REQUESTS_H
#define MTM_EX3_REQUESTS_H
#include <stdbool.h>


typedef struct  requests_t *Requests;


typedef enum {
  REQ_APPROVED,
  REQ_WAITING,
  REQ_APPROVED_DENIED
} ReqResult;



#endif //MTM_EX3_REQUESTS_H
