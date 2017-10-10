#ifndef _PAQUET_H
#define _PAQUET_H
//
// Created by Guillaume Reginster and Guillaume Neiricks
// on 07-10-17
//

struct header{   //4 bytes
    unsigned int type:2;
    unsigned int tr:1;
    unsigned int window:5;
    unsigned int seqnum:8;
    unsigned int length:16;
};

/* struct record
 * Structure représentant un paquet
 */
struct record {  //32 bytes
    struct  header * header;  //8 bytes + 4 bytes
    unsigned int timestamp;  //4 bytes
    unsigned int crc1;   //4 bytes
    char * payload;   //8 bytes
    unsigned int crc2;   //4 bytes
};

/*
* création d'un paquet de données
*/
int record_init(struct record *r ,unsigned int type,unsigned int tr,unsigned int window,unsigned int seqnum,unsigned int length,unsigned int timestamp,unsigned int crc1,char * payload, unsigned int crc2);

/*
*Libération du paquet
*/
void record_free(struct record *r);

/**
 * Renvoie le type d'un enregistrement
 * @pre: r != NULL
 */
int record_get_type(const struct record *r);

/**
 * Renvoie le TR d'un enregistrement
 * @pre: r != NULL
 */
int record_get_tr(const struct record *r);

/**
 * Renvoie le Window d'un enregistrement
 * @pre: r != NULL
 */
int record_get_window(const struct record *r);

/**
 * Modifie le Window d'un enregistrement
 * @pre: r != NULL && Window != NULL
 */
void record_set_window(struct record *r, unsigned int window);

/**
 * Renvoie le Seqnum d'un enregistrement
 * @pre: r != NULL
 */
int record_get_seqnum(const struct record *r);

/**
 * Modifie le Seqnum d'un enregistrement
 * @pre: r != NULL && Seqnum!=NULL
 */
void record_set_seqnum(struct record *r,  unsigned int seqnum);

/**
 * Renvoie le Length d'un enregistrement
 * @pre: r != NULL
 */
int record_get_length(const struct record *r);

/**
 * Renvoie le Timestamp d'un enregistrement
 * @pre: r != NULL
 */
int record_get_timestamp(const struct record *r);

/**
 * Modifie le Timestamp d'un enregistrement
 * @pre: r != NULL && Timestamp!=NULL
 */
void record_set_timestamp(struct record *r,  unsigned int timestamp);

/**
 * Renvoie le CRC1 d'un enregistrement
 * @pre: r != NULL
 */
int record_get_crc1(const struct record *r);

/**
 * Modifie le CRC1 d'un enregistrement
 * @pre: r != NULL && CRC1!=NULL
 */
void record_set_crc1(struct record *r,  unsigned int crc1);

/**
 * Renvoie le Payload d'un enregistrement
 * @pre: r != NULL
 */
char * record_get_payload(const struct record *r);

/**
 * Modifie le Payload d'un enregistrement
 * @pre: r != NULL && Payload!=NULL
 */
void record_set_payload(struct record *r, char * payload);

/**
 * Renvoie le CRC2 d'un enregistrement
 * @pre: r != NULL
 */
int record_get_crc2(const struct record *r);

/**
 * Modifie le CRC2 d'un enregistrement
 * @pre: r != NULL && CRC2!=NULL
 */
void record_set_crc2(struct record *r,  unsigned int crc2);

#endif
