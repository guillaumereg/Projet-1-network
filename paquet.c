#include <stdint.h>
#include <stdlib.h>
#include <string.h>


#include <zlib.h>



#include "paquet.h"


struct header{   //4 bytes
    unsigned int type:2;
    unsigned int tr:1;
    unsigned int window:5;
    unsigned int seqnum:8;
    unsigned int length:16;
};

struct __attribute__((__packed__)) pkt {
  struct  header * header;  //8 bytes + 4 bytes
  unsigned int timestamp;  //4 bytes
  unsigned int crc1;   //4 bytes
  char * payload;   //8 bytes
  unsigned int crc2;   //4 bytes
};





/* Alloue et initialise une struct pkt
 * @return: NULL en cas d'erreur */
pkt_t* pkt_new(){

  struct pkt  * r= NULL;
  r->header = (struct header *)malloc (sizeof(struct header));
  if(r->header==NULL)
  {
      return NULL;
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

  return r;
}

/* Libere le pointeur vers la struct pkt, ainsi que toutes les
 * ressources associees
 */
void pkt_del(pkt_t* r)
{
      free(r->header);
      free(r->payload);
      free(r);
}

pkt_status_code pkt_decode(const char *data, const size_t len, pkt_t *pkt)
{

  if( len < 4)
	{
		return E_NOHEADER;
  }
  memcpy(pkt, data, 4);

  uint8_t type=pkt_get_type(pkt);
	if(type !=1 && type!=2 && type!=3){
    return E_TYPE;
  }

  uint16_t length = pkt_get_length(pkt);;
  if (length > 512 ){
    return E_LENGTH;
  }
  if (length != len){
    return E_UNCONSISTENT;
  }

  uint8_t tr =  pkt_get_tr(pkt);
  if ((type == 2 || type ==3) && tr !=0 ){
    return E_TR;
  }


  uint32_t crc1 = (int)crc32(0, (const void *)data, 4+length);
  memcpy(&pkt->crc1, data + length + 4, 4);
  if (crc1 != pkt->crc1){
      return E_CRC;
  }

  uint32_t crc2 = (int)crc32(0, (const void *)data, 4+length);
  memcpy(&pkt->crc2, data + length + 4, 4);
  if (crc2 != pkt->crc2){
      return E_CRC;
  }

 return PKT_OK;

}


pkt_status_code pkt_encode(const pkt_t* pkt, char *buf, size_t *len)
{

    memcpy(buf, pkt, 2);

    uint16_t length = (pkt->header->length);
    memcpy(buf + 2, &length, 2);
    *len = 4;

    uint32_t crc1 = (int)crc32(0, (const void *) buf, 4+length);
    memcpy(buf + *len, &crc1, 4);
    *len += 4;

    char *payload = (char *)pkt_get_payload(pkt);

    if (payload != NULL)
    {
        int lon = pkt_get_length(pkt);
        if (lon % 4)
            lon += 4 - lon % 4;
        memcpy(buf + *len, payload, lon);

        *len += lon;

        uint32_t crc2 = (int)crc32(0, (const void *) buf, 4+length);
        memcpy(buf + *len, &crc2, 4);
        *len += 4;
    }

    return PKT_OK;
}


ptypes_t pkt_get_type     (const pkt_t* r)
{
  if (r == NULL ){
    return -1;
  }
  return r->header->type;
}

/**
 * Change le type d'un enregistrement
 * @pre: r != NULL
 */
pkt_status_code pkt_set_type     (pkt_t* r, const ptypes_t type)
{
  if (r != NULL ){
    r->header->type=type;
    return 0;
  }
  return -1;
}

/**
 * Renvoie le TR d'un enregistrement
 * @pre: r != NULL
 */
uint8_t  pkt_get_tr       (const pkt_t* r)
{
  if (r == NULL ){
    return -1;
  }
  return r->header->tr;
}

/**
 * Change le tr d'un enregistrement
 * @pre: r != NULL
 */
pkt_status_code pkt_set_tr       (pkt_t* r, const uint8_t tr)
{
  if (r != NULL ){
    r->header->tr=tr;
    return 0;
  }
  return -1;
}

/**
 * Renvoie le Window d'un enregistrement
 * @pre: r != NULL
 */
uint8_t  pkt_get_window   (const pkt_t* r)
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
pkt_status_code pkt_set_window   (pkt_t* r, const uint8_t window)
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
uint8_t  pkt_get_seqnum   (const pkt_t* r)
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
pkt_status_code pkt_set_seqnum   (pkt_t* r, const uint8_t seqnum)
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
uint16_t pkt_get_length   (const pkt_t* r)
{
  if (r == NULL ){
    return -1;
  }
  return r->header->length;
}

/**
 * Modifie le length d'un enregistrement
 * @pre: r != NULL && Seqnum!=NULL
 */
pkt_status_code pkt_set_length   (pkt_t* r, const uint16_t length)
{
  if (r != NULL ){
    r->header->length=length;
    return 0;
  }
  return -1;
}

/**
 * Renvoie le Timestamp d'un enregistrement
 * @pre: r != NULL
 */
uint32_t pkt_get_timestamp(const pkt_t* r)
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
pkt_status_code pkt_set_timestamp(pkt_t* r, const uint32_t timestamp)
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
uint32_t pkt_get_crc1     (const pkt_t* r)
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
pkt_status_code pkt_set_crc1     (pkt_t* r, const uint32_t crc1)
{
  if (r != NULL ){
    r->crc1=crc1;
    return 0;
  }
  return -1;
}

/* Renvoie un pointeur vers le payload du paquet, ou NULL s'il n'y
 * en a pas.
 */
const char* pkt_get_payload(const pkt_t* r)
{
  if (r == NULL ){
    return NULL;
  }
  return r->payload;
}

/* Defini la valeur du champs payload du paquet.
 * @data: Une succession d'octets representants le payload
 * @length: Le nombre d'octets composant le payload
 * @POST: pkt_get_length(pkt) == length */
pkt_status_code pkt_set_payload(pkt_t* r,
                                const char *data,
                                const uint16_t length)
{
  r->payload = (char*)malloc(sizeof(char)*length);
  if(r == NULL){
    return -1;
  }
  memcpy(r->payload,data,length);
  return 0;
}
/* Renvoie le CRC2 dans l'endianness native de la machine. Si
 * ce field n'est pas present, retourne 0.
 */
uint32_t pkt_get_crc2(const pkt_t* r)
{
  if (r == NULL ){
    return 0;
  }
  return r->crc2;
}

/* Setter pour CRC2. Les valeurs fournies sont dans l'endianness
 * native de la machine!
 */
pkt_status_code pkt_set_crc2(pkt_t* r, const uint32_t crc2)
{
  if (r != NULL ){
    r->crc2=crc2;
    return 0;
  }
  return -1;
}
