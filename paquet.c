#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "paquet.h"


/*
* initialisation d'un paquet de données
*/
int record_init(struct record *r){

  r->header = (struct header *)malloc (sizeof(struct header));
  if(r->header==NULL)
  {
      return -1;
  }

  r->header->type=0;
  r->header->tr=0;
  r->header->window=0;
  r->header->seqnum=0;
  r->header->length=0;
  r->timestamp=0;
  r->crc1=0;
  r->payload=NULL;
  r->crc2=0;

  return 0;
}

/*
*Libération du paquet
*/
void record_free(struct record *r)
{
      free(r->header);
      free(r->payload);
      free(r);
}

/**
 * Renvoie le type d'un enregistrement
 * @pre: r != NULL
 */
int record_get_type(const struct record *r)
{
  if (r == NULL ){
    return -1;
  }
  return r->header->type;
}

/**
 * Renvoie le TR d'un enregistrement
 * @pre: r != NULL
 */
int record_get_tr(const struct record *r)
{
  if (r == NULL ){
    return -1;
  }
  return r->header->tr;
}

/**
 * Renvoie le Window d'un enregistrement
 * @pre: r != NULL
 */
int record_get_Window(const struct record *r)
{
  if (r == NULL ){
    return -1;
  }
  return r->header->window;
}

/**
 * Modifie le Window d'un enregistrement
 * @pre: r != NULL && Window !=NULL
 */
int record_set_window(struct record *r, unsigned int window)
{
  if (r != NULL ){
    r->header->window=window;
    return 0;
  }
  return -1;
}

/**
 * Renvoie le Seqnum d'un enregistrement
 * @pre: r != NULL
 */
int record_get_seqnum(const struct record *r)
{
  if (r == NULL ){
    return -1;
  }
  return r->header->seqnum;
}

/**
 * Modifie le Seqnum d'un enregistrement
 * @pre: r != NULL && Seqnum!=NULL
 */
int record_set_seqnum(struct record *r,  unsigned int seqnum)
{
  if (r != NULL ){
    r->header->seqnum=seqnum;
    return 0;
  }
  return -1;
}

/**
 * Renvoie le Length d'un enregistrement
 * @pre: r != NULL
 */
int record_get_length(const struct record *r)
{
  if (r == NULL ){
    return -1;
  }
  return r->header->length;
}

/**
 * Renvoie le Timestamp d'un enregistrement
 * @pre: r != NULL
 */
int record_get_timestamp(const struct record *r)
{
  if (r == NULL ){
    return -1;
  }
  return r->timestamp;
}

/**
 * Modifie le Timestamp d'un enregistrement
 * @pre: r != NULL && Timestamp!=NULL
 */
int record_set_timestamp(struct record *r,  unsigned int timestamp)
{
  if (r != NULL ){
    r->timestamp=timestamp;
    return 0;
  }
  return -1;
}

/**
 * Renvoie le CRC1 d'un enregistrement
 * @pre: r != NULL
 */
int record_get_crc1(const struct record *r)
{
  if (r == NULL ){
    return -1;
  }
  return r->crc1;
}

/**
 * Modifie le CRC1 d'un enregistrement
 * @pre: r != NULL && CRC1!=NULL
 */
int record_set_crc1(struct record *r,  unsigned int crc1)
{
  if (r != NULL ){
    r->crc1=crc1;
    return 0;
  }
  return -1;
}

/**
 * Renvoie le Payload d'un enregistrement
 * @pre: r != NULL
 */
char* record_get_payload(const struct record *r)
{
  if (r == NULL ){
    return NULL;
  }
  return r->payload;
}

/**
 * définit le payload d'un enregistrement
 * @pre: r != NULL && buf!=NULL && n>=0
 */
int record_set_payload(struct record *r, const char * buf, int n)
{
  r->payload = (char*)malloc(sizeof(char)*n);
  if(r == NULL){
    return -1;
  }
  memcpy(r->payload,buf,n);
  return 0;
}
/**
 * Renvoie le CRC2 d'un enregistrement
 * @pre: r != NULL
 */
int record_get_crc2(const struct record *r)
{
  if (r == NULL ){
    return -1;
  }
  return r->crc2;
}

/**
 * Modifie le CRC1 d'un enregistrement
 * @pre: r != NULL && CRC1!=NULL
 */
int record_set_crc2(struct record *r,  unsigned int crc2)
{
  if (r != NULL ){
    r->crc2=crc2;
    return 0;
  }
  return -1;
}
