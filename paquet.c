#include <stdint.h>
#include <stdlib.h>

/* struct header
 * Structure représentant l'entête d'un paquet
 */
struct header{
    unsigned int Type:2;
    unsigned int TR:1;
    unsigned int Window:5;
    unsigned int Seqnum:8;
    unsigned int Length:16;
};

/* struct record
 * Structure représentant un paquet
 */
struct record {
    struct  header * Header;
    unsigned int Timestamp;
    unsigned int CRC1;
    unsigned char * Payload;
    unsigned int CRC2;
};

/*
* création d'un paquet de données
*/
int record_init(  unsigned int Type,unsigned int TR,unsigned int Window,unsigned int Seqnum,unsigned int Length,unsigned int Timestamp,unsigned int CRC1,unsigned char * Payload,unsigned int CRC2){

  struct record * r = (struct record *) malloc (sizeof(struct record));
  r->Header = (struct header *) malloc (sizeof(struct header));
  r->Payload =  malloc (sizeof(512));
  if(r->Header==NULL)
  {
      return -1;
  }

  r->Header->Type=Type;
  r->Header->TR=TR;
  r->Header->Window=Window;
  r->Header->Seqnum=Seqnum;
  r->Header->Length=Length;
  r->Timestamp=Timestamp;
  r->CRC1=CRC1;
  r->Payload=Payload;
  r->CRC2=CRC2;

  return 0;
}

/*
*Libération du paquet
*/
void record_free(struct record *r)
{
      free(r->Header);
      free(r->Payload);
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
  return r->Header->Type;
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
  return r->Header->TR;
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
  return r->Header->Window;
}

/**
 * Modifie le Window d'un enregistrement
 * @pre: r != NULL && Window !=NULL
 */
void record_set_Window(const struct record *r,   unsigned int Window)
{
  if (r != NULL ){
    r->Header->Window=Window;
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
  return r->Header->Seqnum;
}

/**
 * Modifie le Seqnum d'un enregistrement
 * @pre: r != NULL && Seqnum!=NULL
 */
void record_set_Seqnum(const struct record *r,  unsigned int Seqnum)
{
  if (r != NULL ){
    r->Header->Seqnum=Seqnum;
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
  return r->Header->Length;
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
  return r->Timestamp;
}

/**
 * Modifie le Timestamp d'un enregistrement
 * @pre: r != NULL && Timestamp!=NULL
 */
void record_set_Timestamp(const struct record *r,  unsigned int Timestamp)
{
  if (r != NULL ){
    r->Timestamp=Timestamp;
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
  return r->CRC1;
}

/**
 * Modifie le CRC1 d'un enregistrement
 * @pre: r != NULL && CRC1!=NULL
 */
void record_set_CRC1(const struct record *r,  unsigned int CRC1)
{
  if (r != NULL ){
    r->CRC1=CRC1;
  }
}

/**
 * Renvoie le Payload d'un enregistrement
 * @pre: r != NULL
 */
char record_get_Payload(const struct record *r)
{
  if (r == NULL ){
    return -1;
  }
  return r->Payload;
}

/**
 * Modifie le PAyload d'un enregistrement
 * @pre: r != NULL && Payload!=NULL
 */
void record_set_Payload(const struct record *r,  unsigned char * Payload)
{
  if (r != NULL && Payload!= NULL){
    r->Payload= Payload;
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
  return r->CRC2;
}

/**
 * Modifie le CRC1 d'un enregistrement
 * @pre: r != NULL && CRC1!=NULL
 */
void record_set_CRC2(const struct record *r,  unsigned int CRC2)
{
  if (r != NULL ){
    r->CRC2=CRC2;
  }
}