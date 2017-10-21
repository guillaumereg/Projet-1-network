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

#define MAX_SEGMENT_SIZE 1024

struct node {
  char* segment;
  struct node* next;
};


//transforme le fichier en liste de segments
int putInList(struct node **first, int filePresent, char* filename){
  ssize_t bufferLength = 8; //supposont que la taille maximale du buffer est de 8 bytes au lieu de 512
  char *buffer = malloc(sizeof(char)*bufferLength);
  FILE *fp;
  if(filePresent == 0){
    fp = stdin;
  }
  else{
    fp = fopen(filename, "r");
  }
  int count=0;
  struct node *last= NULL;
  while ((count=fread(buffer, 1, bufferLength, fp)) > 0) {  //send the buffer
    //printf("count: %d buffer: %s\n",count, buffer);
    struct node* item = (struct node*)malloc(sizeof(struct node));
    item->segment = buffer;
    if(last == NULL){ //item est le premier element à ajouter dans la liste
      *first = item;
    }
    else{
      last->next = item;
    }
    last = item;
    buffer = malloc(sizeof(char)*bufferLength);
  }
  free(buffer);
  if(filePresent == 1){ //ne pas fermer stdin
    fclose(fp);
  }
  return 0;
}


//send list of segments
int sendItems(struct node *first, int sockfd){
  int sendSegmentLength = 9;
  int recvAckLength = 4;
  struct node* sendItem = first;
  char *rcvAck = malloc(recvAckLength);
  fd_set readfds, writefds;
  struct timeval tv;
  int lastItem = 0;
  while(1){
    FD_ZERO(&readfds);
    FD_ZERO(&writefds);
    FD_SET(sockfd, &readfds);
    FD_SET(sockfd, &writefds);
    tv.tv_sec = 3;
    select(sockfd + 1, &readfds, &writefds, NULL, &tv); //attend possible d'écrire ou lire sur sockfd
    if(FD_ISSET(sockfd, &readfds)){ //recevoir segment de ack
      printf("possibilité de lecture\n");
      if(recv(sockfd,(void*)rcvAck, recvAckLength, 0) == -1){
        fprintf(stderr, "recv ack error: %s\n",strerror(errno));
        return -1;
      }
      printf("received ack: %s\n", rcvAck);
      free(rcvAck);
      rcvAck = malloc(recvAckLength);
      if(lastItem == 1){ //ack of last segment received
        break;
      }
    }
    if(FD_ISSET(sockfd, &writefds)){ //envoyer segment
      printf("possibilité d'écriture\n");
      if(send(sockfd,(void*)sendItem->segment , sendSegmentLength, 0) == -1){
        fprintf(stderr, "send segment error: %s\n",strerror(errno));
        return -1;
      }
      printf("envoyé %s\n", sendItem->segment);
      sendItem = sendItem->next;
      if(sendItem == NULL){
        lastItem = 1;
      }
    }
  }
  free(rcvAck);
  printf("fin de while, plus de sendItems dispo, dernier ack reçu \n");
  return 0;
}

int removeList(struct node *first){
  struct node *removeItem;
  struct node *iter = first;
  while(iter!=NULL){
    removeItem = iter;
    printf("remove item: %s\n", removeItem->segment);
    iter = iter->next;
    free(removeItem->segment);
    free(removeItem);
  }
  return 0;
}


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
//-------------------------------------------------------------------------- connecter

  //addresse du receiver
  struct addrinfo hints1, *res1;
  int err1,fd;
  memset(&hints1,0,sizeof(hints1));
  hints1.ai_family=AF_INET6; //IPv6
  hints1.ai_socktype=SOCK_DGRAM;
  hints1.ai_protocol=IPPROTO_UDP; //udp

  if((err1=getaddrinfo(hostname,portname,&hints1,&res1)) != 0){
    fprintf(stderr, "getaddrinfo 1 error: %s\n", gai_strerror(err1));
    exit(1);
  }

/*
  //addresse du sender
  struct addrinfo hints2, *res2;
  int err2;
  memset(&hints2,0,sizeof(hints2));
  hints2.ai_family=AF_INET6; //IPv6
  hints2.ai_socktype=SOCK_DGRAM;
  hints2.ai_protocol=IPPROTO_UDP; //udp
  hints2.ai_flags = AI_PASSIVE; //utiliser l'adresse du sender

  if((err2=getaddrinfo(hostname,portname,&hints2,&res2)) != 0){
    fprintf(stderr, "getaddrinfo 2 error: %s\n", gai_strerror(err2));
    exit(1);
  }
*/

  //creation d'un socket en utilisant l'adresse de receiver
  if((fd=socket(res1->ai_family,res1->ai_socktype,res1->ai_protocol)) ==-1){
    fprintf(stderr, "socket error %s\n", gai_strerror(fd));
    exit(1);
  }
/*
  //lier adresse du sender au socket du sender
  if (bind(fd, res2->ai_addr, res2->ai_addrlen)==-1) {
      fprintf(stderr, "bind error: %s\n",strerror(errno));
      return -1;
  }
*/

  //connecte le socket à l'adresse du receiver
  if (connect(fd, res1->ai_addr, res1->ai_addrlen)==-1) {
      fprintf(stderr, "bind error: %s\n",strerror(errno));
      return -1;
  }

//---------------------------------------------------------------------------- mettre segments dans liste chainée
  struct node* list = NULL;
  putInList(&list, filePresent, filename);
  sendItems(list, fd);
  removeList(list);
  freeaddrinfo(res1);
  //freeaddrinfo(res2);
  close(fd);

  return 0;
}
