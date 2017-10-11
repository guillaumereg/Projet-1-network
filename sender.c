#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

#include "paquet.h"

int main(int argc, char **argv){
  struct record *r;
  r = (struct record*)malloc(sizeof(struct record));
  int a = record_init(r);
  if (a==-1){
    return -1;
  }
  record_set_payload(r,"12345\0",6);
  record_free(r);
}
