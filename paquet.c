#include <stdint.h>
#include <stdlib.h>

#include "paquet.h"
/* struct header
 * Structure représentant l'entête d'un paquet
 */


/*
* création d'un paquet de données
*/
int record_init(struct record *r ,unsigned int type,unsigned int tr,unsigned int window,unsigned int seqnum,unsigned int length,unsigned int timestamp,unsigned int crc1,char * payload, unsigned int crc2){

  r = (struct record *) malloc (sizeof(struct record));
  if(r==NULL)
  {
      return -1;
  }

  r->payload =  (char*) malloc (length);
  if(r->payload==NULL )
  {
      return -1;
  }

  r->header->type=type;
  r->header->tr=tr;
  r->header->window=window;
  r->header->seqnum=seqnum;
  r->header->length=length;
  r->timestamp=timestamp;
  r->crc1=crc1;
  r->payload=payload;
  r->crc2=crc2;

  return 0;
}

/*
*Libération du paquet
*/
void record_free(struct record *r)
{
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
void record_set_window(struct record *r, unsigned int window)
{
  if (r != NULL ){
    r->header->window=window;
  }
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
void record_set_seqnum(struct record *r,  unsigned int seqnum)
{
  if (r != NULL ){
    r->header->seqnum=seqnum;
  }
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
void record_set_timestamp(struct record *r,  unsigned int timestamp)
{
  if (r != NULL ){
    r->timestamp=timestamp;
  }
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
void record_set_crc1(struct record *r,  unsigned int crc1)
{
  if (r != NULL ){
    r->crc1=crc1;
  }
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
 * Modifie le PAyload d'un enregistrement
 * @pre: r != NULL && Payload!=NULL
 */
void record_set_payload(struct record *r, char * payload)
{
  if (r != NULL && payload!= NULL){
    r->payload= payload;
  }
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
void record_set_crc2(struct record *r,  unsigned int crc2)
{
  if (r != NULL ){
    r->crc2=crc2;
  }
}
