#include <stdint.h>
#include <stdlib.h>

/* struct header
 * Structure représentant l'entête d'un paquet
 */
struct header{
    unsigned int type:2;
    unsigned int tr:1;
    unsigned int window:5;
    unsigned int seqnum:8;
    unsigned int length:16;
};

/* struct record
 * Structure représentant un paquet
 */
struct record {
    struct  header * header;
    unsigned int timestamp;
    unsigned int crc1;
    unsigned char * payload;
    unsigned int crc2;
};

/*
* création d'un paquet de données
*/
int record_init(struct record *r ,unsigned int type,unsigned int tr,unsigned int window,unsigned int seqnum,unsigned int length,unsigned int timestamp,unsigned int crc1,unsigned char * payload,unsigned int crc2){

  r = (struct record *) malloc (sizeof(struct record));
  r->header = (struct header *) malloc (sizeof(struct header));
  r->payload =  malloc (sizeof(512));
  if(r==NULL || r->header==NULL || r->payload==NULL )
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
int record_get_TR(const struct record *r)
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
void record_set_Window(struct record *r,   unsigned int window)
{
  if (r != NULL ){
    r->header->window=window;
  }
}

/**
 * Renvoie le Seqnum d'un enregistrement
 * @pre: r != NULL
 */
int record_get_Seqnum(const struct record *r)
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
void record_set_Seqnum(struct record *r,  unsigned int seqnum)
{
  if (r != NULL ){
    r->header->seqnum=seqnum;
  }
}

/**
 * Renvoie le Length d'un enregistrement
 * @pre: r != NULL
 */
int record_get_Length(const struct record *r)
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
int record_get_Timestamp(const struct record *r)
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
void record_set_Timestamp(struct record *r,  unsigned int timestamp)
{
  if (r != NULL ){
    r->timestamp=timestamp;
  }
}

/**
 * Renvoie le CRC1 d'un enregistrement
 * @pre: r != NULL
 */
int record_get_CRC1(const struct record *r)
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
void record_set_CRC1(struct record *r,  unsigned int crc1)
{
  if (r != NULL ){
    r->crc1=crc1;
  }
}

/**
 * Renvoie le Payload d'un enregistrement
 * @pre: r != NULL
 */
char * record_get_Payload(const struct record *r)
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
void record_set_Payload(struct record *r,  unsigned char * payload)
{
  if (r != NULL && payload!= NULL){
    r->payload= payload;
  }
}
/**
 * Renvoie le CRC2 d'un enregistrement
 * @pre: r != NULL
 */
int record_get_CRC2(const struct record *r)
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
void record_set_CRC2(struct record *r,  unsigned int crc2)
{
  if (r != NULL ){
    r->crc2=crc2;
  }
}
