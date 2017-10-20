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
//--------------------------------------------------------------------------
  struct addrinfo hints, *res;
  int err, fd, numbytes;
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

//----------------------------------------------------------------------------


  ssize_t bufferLength = 8; //supposont que la taille maximale du buffer est de 8 bytes au lieu de 512
  char *buffer = malloc(sizeof(char)*bufferLength);
  FILE *fp;
  if(filePresent == 0){  //envoyer contenu de stdin dans un fichier et l'envoyer
    fp = stdin;
  }
  else{
    fp = fopen(filename, "r");
  }
  int count;
  while ((count=fread(buffer, 1, bufferLength, fp)) > 0) {  //send the buffer
    printf("count: %d\n",count);
    printf("buffer: %s\n",buffer);

    if ((numbytes = sendto(fd,buffer,bufferLength,0,res->ai_addr,res->ai_addrlen))==-1) {
      fprintf(stderr, "sendto error: %s\n", gai_strerror(numbytes));
      exit(1);
    }
    printf("sent %d bytes to %s to port %s\n", numbytes, hostname, portname);
    free(buffer);
    buffer = malloc(sizeof(char)*bufferLength);
  }
  free(buffer);
  if(filePresent == 1){
    fclose(fp);
  }

  freeaddrinfo(res);
  close(fd);

  return 0;
}
