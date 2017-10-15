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
  char* hostname;  //www.qqch.com ou IPv6
  char* portname; //http ou numero port

  while ((option = getopt(argc, argv,"f:")) != -1) {
    switch (option) {
      case 'f' :
        filename = optarg;
        filePresent = 1;
        break;
      default: break;
      }
  }
  if(filePresent == 1){  //position fixe = argv[1] ?
    hostname = *(argv+3);
    portname = *(argv+4);
    printf("filePresent: %d filename: %s\n", filePresent, filename);
  }
  else{
    hostname = *(argv+1);   //adresse ip du receiver
    portname = *(argv+2);   //port sur lequel receiver recoit
  }
  printf("hostname: %s portname: %s\n", hostname, portname);

  //-------------------------------------------------------------------

  struct addrinfo hints, *res;
  int err, fd, numbytes;
  char datagram[5] = "test\0";
  memset(&hints,0,sizeof(hints));
  hints.ai_family=AF_INET6; //IPv6
  hints.ai_socktype=SOCK_DGRAM;
  hints.ai_protocol=IPPROTO_UDP; //udp
  hints.ai_flags=AI_ADDRCONFIG;

  if((err=getaddrinfo(hostname,portname,&hints,&res)) != 0){
    fprintf(stderr, "getaddrinfo error: %s\n", gai_strerror(err));
    exit(1);
  }

  if((fd=socket(res->ai_family,res->ai_socktype,res->ai_protocol)) ==-1){
    fprintf(stderr, "socket error %s\n", gai_strerror(fd));
    exit(1);
  }


  if ((numbytes = sendto(fd,datagram,sizeof(datagram),0,res->ai_addr,res->ai_addrlen))==-1) {
    fprintf(stderr, "sendto error: %s\n", gai_strerror(numbytes));
    exit(1);
  }


  // région expérimentale
  if(filePresent == 1 ){

        FILE *lectureFichier = NULL;
        char octetActu ;
        char listeOctet[512];
        int nbrOctet=0;
        int nbrOctetTotal=0;


        lectureFichier = fopen(filename, "rb");

        if(lectureFichier == NULL)
        {
            exit(1);
        }


        while( fread(&octetActu, 1, sizeof(octetActu), lectureFichier) != 0)
        {
            listeOctet[nbrOctet]=octetActu;
            nbrOctet++;
            nbrOctetTotal++;

            if(nbrOctet == 512){

              listeOctet[nbrOctet]='\0';
              nbrOctet=0;

              if ((numbytes = sendto(fd,listeOctet,sizeof(listeOctet),0,res->ai_addr,res->ai_addrlen))==-1) {
                fprintf(stderr, "sendto error: %s\n", gai_strerror(numbytes));
                exit(1);
              }

              strcpy(listeOctet, ""); //chaine "nulle"
            }
        }

        if ((numbytes = sendto(fd,listeOctet,nbrOctet,0,res->ai_addr,res->ai_addrlen))==-1) {
          fprintf(stderr, "sendto error: %s\n", gai_strerror(numbytes));
          exit(1);
        }

        numbytes=nbrOctetTotal;
        fclose(lectureFichier);
        filePresent=0;
    }



  char ip6[INET6_ADDRSTRLEN];
  struct in6_addr addr = ((struct sockaddr_in6*)(res->ai_addr))->sin6_addr;
  printf("hostname: %s: ntop: %s\n", hostname, inet_ntop(AF_INET6, &addr, ip6, INET6_ADDRSTRLEN));
  printf("sent %d bytes to %s to port %s\n", numbytes, ip6, portname);

  freeaddrinfo(res);
  close(fd);


  return 0;
}
