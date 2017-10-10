#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char **argv){
  printf("hello from sender\n");

  struct record * r;
  unsigned int type = 0;
  unsigned int tr = 0;
  unsigned int window = 0;
  unsigned int seqnum = 0;
  unsigned int length = 0;
  unsigned int timestamp = 0;
  unsigned int crc1 = 0;
  unsigned char * payload = 0;
  unsigned int crc2 = 0;

  int a = record_init(r,type,tr,window,seqnum,length,timestamp,crc1,payload,crc2);
  if (a==-1){
    return -1;
  }

  record_free(r);


}
