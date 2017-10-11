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

  int c;
  int num=0;
  int type=0;
  int length=0;
  int tr=0;

  while ( (c = getopt(argc, argv, "a:s:m:d:ID")) != -1 ) {
      switch ( c ) {
          case 'type':
            if(atoi(optarg) != 2 && atoi(optarg) !=3){
                c=-1;
            }
            else if (atoi(optarg) ==2){
              type = 2;
            }
            else if (atoi(optarg) ==3){
              type = 3;
            }
          case 'tr':
            if(atoi(optarg) !=0){
                c=-1;
            }
          case 'seqnum':
            if(type == 2){
              num = atoi(optarg) +1;
            }
            else   if(type == 2){
              num = atoi(optarg);
            }
            if(num > 255){
              num=0;
            }
          case 'length':
            if( atoi(optarg) > 512){
              c=-1;
            }
            else{
              length = atoi(optarg);
            }
      }
    }

    //puis un truc de ce style?

    record_set_seqnum(r,num);
    record_set_type(r,1);
    //etc
}
