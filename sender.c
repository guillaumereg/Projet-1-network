#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <getopt.h>

#include "paquet.h"

int main(int argc, char **argv){
  /*
  struct record *r;
  r = (struct record*)malloc(sizeof(struct record));
  int a = record_init(r);
  if (a==-1){
    return -1;
  }
  record_set_payload(r,"12345\0",6);
  record_free(r);

  */
  /*
  terminal: ./sender 1 2 3 > text.txt
  printf("hello %s \n", *(argv+3));

  terminal: ./sender < text.txt
  int ch;
    do {
      ch = fgetc(stdin);
      putchar(ch);
  } while (ch != EOF
  */

  int option = 0;
  int filePresent = 0;
  char* filename = NULL;
  char* node;  //www.qqch.com ou IPv6
  char* service; //http ou numero port

  while ((option = getopt(argc, argv,"f:")) != -1) {
    switch (option) {
      case 'f' : filename = optarg;
        filePresent = 1;
        break;
      default: break;
      }
  }
  if(filePresent == 1){  //position fixe = argv[1] ?
    node = *(argv+3);
    service = *(argv+4);
  }
  else{
    node = *(argv+1);
    service = *(argv+2);
  }

  return 0;
}
