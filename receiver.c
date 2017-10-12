#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <getopt.h>

#include "paquet.h"

int main(int argc, char **argv){


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
    if(filePresent == 1){
      printf("end getopt, filePresent: %d filename: %s\n", filePresent, filename);
      node = *(argv+3);
      service = *(argv+4);
    }
    else{
      node = *(argv+1);
      service = *(argv+2);
    }
    printf("node: %s service: %s\n", node, service);

}
