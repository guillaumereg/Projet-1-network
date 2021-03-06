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
#include <sys/select.h>

#include "paquet.h"


int recvItems(int sockfd){
  int recvSegmentLength = 9;
  int sendAckLength = 4;
  char *rcvSegment = (char *)malloc(recvSegmentLength);
  fd_set readfds, writefds;
  char ack [4]= "ack\0";
  int testSelect;

  struct timeval tv;
  while(1){
    FD_ZERO(&readfds);
    FD_ZERO(&writefds);
    FD_SET(sockfd, &readfds);
    FD_SET(sockfd, &writefds);
    tv.tv_sec = 5;
    tv.tv_usec = 0;
    testSelect = select(sockfd + 1, &readfds, &writefds, NULL, &tv);
    printf("testSelect: %d\n",testSelect);
    if(testSelect == -1){ //erreur
      fprintf(stderr, "recv select error: %s\n",strerror(errno));
      return -1;
    }
    else if(FD_ISSET(sockfd, &readfds) ){ //recevoir segment
      printf("possibilité de lecture\n");
      if(recv(sockfd,(void*)rcvSegment, recvSegmentLength, 0) == -1){
        fprintf(stderr, "recv segment error: %s\n",strerror(errno));
        return -1;
      }
      printf("received segment: %s\n", rcvSegment);
      if(FD_ISSET(sockfd, &writefds)){ //envoyer ack
        printf("possibilité envoyer ack\n");
        if(send(sockfd,(void*)ack , sendAckLength, 0) == -1){
          fprintf(stderr, "send ack error: %s\n",strerror(errno));
          return -1;
        }
        printf("sent ack\n");
      }
      free(rcvSegment);
      rcvSegment = malloc(recvSegmentLength);
    }
    else { //timout a expiré, plus de paquets à recevoir, seul writefds est dispo
      printf("timout expiré.\n");
      break;
    }
  }
  printf("fini recv while\n");
  free(rcvSegment);
  return 0;
}

void printSegment(const pkt_t* pkt){
    printf("HEADER----------\n");
    printf("type: %d\n", pkt_get_type(pkt));
    printf("tr: %d\n", pkt_get_tr(pkt));
    printf("window: %d\n", pkt_get_window(pkt));
    printf("seqnum: %d\n", pkt_get_seqnum(pkt));
    printf("length: %d\n", pkt_get_length(pkt));
    printf("PACKET---------------\n");
    printf("timestamp: %d\n", pkt_get_timestamp(pkt));
    printf("CRC1: %d\n", pkt_get_crc1(pkt));
    //printf("payload: %s CRC2: %d\n", pkt_get_payload(pkt), pkt_get_crc2(pkt));
    printf("payload: ? CRC2: %d\n", pkt_get_crc2(pkt));
    printf("---------------------------------------\n");
}

int main(int argc, char **argv){

/*


  int option = 0;
  int filePresent = 0;
  char* filename = NULL;
  char* hostname;
  char* portname;

  while ((option = getopt(argc, argv,"f:")) != -1) {
    switch (option) {
      case 'f' :
        filename = optarg;
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

  //addresse du receiver
  struct addrinfo hints1, *res1;
  int err1, fd;
  memset(&hints1,0,sizeof(hints1));
  hints1.ai_family=AF_INET6; //IPv6
  hints1.ai_socktype=SOCK_DGRAM;
  hints1.ai_protocol=IPPROTO_UDP; //udp
  hints1.ai_flags = AI_PASSIVE; //utiliser l'adresse du sender

  if((err1=getaddrinfo(hostname,portname,&hints1,&res1)) != 0){
    fprintf(stderr, "getaddrinfo 2 error: %s\n", gai_strerror(err1));
    exit(1);
  }

  //creation d'un socket en utilisant l'adresse du receiver
  if((fd=socket(res1->ai_family,res1->ai_socktype,res1->ai_protocol)) ==-1){
    fprintf(stderr, "socket error %s\n", gai_strerror(fd));
    exit(1);
  }

  //lier adresse du receiver au socket
  if (bind(fd, res1->ai_addr, res1->ai_addrlen)==-1) {
      fprintf(stderr, "bind error: %s\n",strerror(errno));
      return -1;
  }

  //recuperer adresse du sender et connecter sur cette addresse avec le socket du receiver
  char* peek = (char*)malloc(sizeof(char)*1024);
  struct sockaddr_in6 *senderAddress = (struct sockaddr_in6 *)malloc(sizeof(struct sockaddr_in6));
  socklen_t addrlen = sizeof(*senderAddress);
  if(recvfrom(fd, peek, 1024, MSG_PEEK, (struct sockaddr *)senderAddress, &addrlen) == -1){
    fprintf(stderr, "recvfrom error: %s\n",strerror(errno));
    return -1;
  }
  if(connect(fd,(struct sockaddr *)senderAddress, addrlen) == -1){
    fprintf(stderr, "connect error: %s\n",strerror(errno));
    return -1;
  }
  free(peek);

  recvItems(fd);
  free(senderAddress);
  freeaddrinfo(res1);
  close(fd);
*/


  pkt_t *pkt= pkt_new();

  char *payload = malloc(sizeof(char)*5);
  payload="test\0";
  pkt_set_type(pkt, (const uint8_t) 1);
  pkt_set_tr(pkt, (const uint8_t) 0);
  pkt_set_window(pkt, (const uint8_t) 3);
  pkt_set_seqnum(pkt, (const uint8_t) 42);
  pkt_set_length(pkt, (const uint16_t) 5); //taille payload en bytes
  pkt_set_timestamp(pkt, (const uint16_t) 0);
  pkt_set_payload(pkt, payload, (const uint16_t) pkt_get_length(pkt));

  printSegment(pkt);
//--------------------------------- marche
  char *buf = malloc(1024);
  size_t len = 1024;
  pkt_encode(pkt, buf, &len);
  printf("paquet est encodé\n");
  pkt_t *pkt2 = NULL;
  pkt_decode(buf, (size_t)1024, pkt2);
  printf("avantMessageErreur\n");
  printSegment(pkt2);
  printf("apresMessageErreur\n");
  pkt_del(pkt);
  return 0;
}
