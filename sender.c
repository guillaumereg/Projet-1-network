#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

#include "paquet.h"

int main(int argc, char **argv){
  printf("hello from sender\n");

  struct record * r;
  unsigned int type = 0;
  unsigned int tr = 0;
  unsigned int window = 0;
  unsigned int seqnum = 0;
  unsigned int timestamp = 0;
  unsigned int crc1 = 0;
  char * payload = "12345\0";
  unsigned int length = 6;    //12345 contient 5 lettres + \0
  unsigned int crc2 = 0;

  r = NULL;
  int a = record_init(r,type,tr,window,seqnum,length,timestamp,crc1,payload,crc2);
  //printf("size of r: %lu \n", sizeof(*r));
  if (a==-1){
    return -1;
  }
  printf("before\n");
  record_free(r);
  printf("after\n");

}
