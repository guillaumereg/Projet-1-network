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
    hostname = *(argv+1);    //interface sur lequel receiver accepte connexion
    portname = *(argv+2);    //port sur lequel receiver écoute
  }
  printf("hostname: %s portname: %s\n", hostname, portname);
//-------------------------------------------------------------------------


  struct addrinfo hints, *res;
  int err, fd, numbytes;
  memset(&hints,0,sizeof(hints));
  hints.ai_family=AF_INET6; //IPv6
  hints.ai_socktype=SOCK_DGRAM;
  hints.ai_protocol=IPPROTO_UDP; //udp
  hints.ai_flags=AI_PASSIVE; //utiliser mon ip

  if((err=getaddrinfo(hostname, portname,&hints,&res)) != 0){
    fprintf(stderr, "getaddrinfo error: %s\n", gai_strerror(err));
    exit(1);
  }

  if((fd=socket(res->ai_family,res->ai_socktype,res->ai_protocol)) ==-1){
    fprintf(stderr, "socket error %s\n", gai_strerror(fd));
    exit(1);
  }

//bind: server socket must be bound to a local address before it can listen for inbound datagrams.
  if (bind(fd,res->ai_addr,res->ai_addrlen)==-1) {
    fprintf(stderr, "bind error %s\n", gai_strerror(fd));
    exit(1);
  }

  //char *buffer = (char*)malloc(sizeof(char)*4+1);
  char buffer[5];

  struct sockaddr_storage src_addr;
  socklen_t src_addr_len = sizeof(src_addr);

  if ((numbytes = recvfrom(fd, buffer, sizeof(buffer), 0,(struct sockaddr *)&src_addr, &src_addr_len)) == -1) {
    fprintf(stderr, "recvfrom error %s\n", gai_strerror(fd));
    exit(1);
  }

  char ip6[INET6_ADDRSTRLEN];
  struct in6_addr addr = ((struct sockaddr_in6*)(&src_addr))->sin6_addr;
  inet_ntop(AF_INET6, &addr, ip6, INET6_ADDRSTRLEN);
  printf("received %d bytes from %s with port %s\n", numbytes, ip6, portname);
  printf("buffer = %s\n", buffer);

  freeaddrinfo(res);
  close(fd);

































    return 0;
}
