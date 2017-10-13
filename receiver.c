#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <getopt.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

#include "paquet.h"

int main(int argc, char **argv){


    int option = 0;
    int filePresent = 0;
    char* filename = NULL;
    char* hostname;
    char* portname;

    while ((option = getopt(argc, argv,"f:")) != -1) {
      switch (option) {
        case 'f' : filename = optarg;
          filePresent = 1;
          break;
        default: break;
        }
    }
    if(filePresent == 1){
      hostname = *(argv+3);
      portname = *(argv+4);
      printf("filePresent: %d filename: %s\n", filePresent, filename);
    }
    else{
      hostname = *(argv+1);
      portname = *(argv+2);
    }
    printf("hostname: %s portname: %s\n", hostname, portname);
    return 0;
}
