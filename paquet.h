#ifndef _PROTOCOL_H
#define _PROTOCOL_H
//
// Created by Guillaume Reginster and Guillaume Neiricks
// on 07-10-17
//



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
    unsigned char Payload;
    unsigned int CRC2;
};

/*
* création d'un paquet de données
*/
int record_init(struct record *r);


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
int record_get_TR(const struct record *r);

/**
 * Renvoie le Window d'un enregistrement
 * @pre: r != NULL
 */
int record_get_Window(const struct record *r);

/**
 * Modifie le Window d'un enregistrement
 * @pre: r != NULL && Window != NULL
 */
void record_set_Window(const struct record *r,unsigned int Window:5);

/**
 * Renvoie le Seqnum d'un enregistrement
 * @pre: r != NULL
 */
int record_get_Seqnum(const struct record *r);

/**
 * Modifie le Seqnum d'un enregistrement
 * @pre: r != NULL && Seqnum!=NULL
 */
void record_set_Seqnum(const struct record *r,  unsigned int Seqnum:8);

/**
 * Renvoie le Length d'un enregistrement
 * @pre: r != NULL
 */
int record_get_Length(const struct record *r);

/**
 * Renvoie le Timestamp d'un enregistrement
 * @pre: r != NULL
 */
int record_get_Timestamp(const struct record *r);

/**
 * Modifie le Timestamp d'un enregistrement
 * @pre: r != NULL && Timestamp!=NULL
 */
void record_set_Timestamp(const struct record *r,  unsigned int Timestamp);

/**
 * Renvoie le CRC1 d'un enregistrement
 * @pre: r != NULL
 */
int record_get_CRC1(const struct record *r);

/**
 * Modifie le CRC1 d'un enregistrement
 * @pre: r != NULL && CRC1!=NULL
 */
void record_set_CRC1(const struct record *r,  unsigned int CRC1);

/**
 * Renvoie le Payload d'un enregistrement
 * @pre: r != NULL
 */
char record_get_Payload(const struct record *r);

/**
 * Modifie le Payload d'un enregistrement
 * @pre: r != NULL && Payload!=NULL
 */
void record_set_Payload(const struct record *r,  unsigned char Payload);

/**
 * Renvoie le CRC2 d'un enregistrement
 * @pre: r != NULL
 */
int record_get_CRC2(const struct record *r);

/**
 * Modifie le CRC2 d'un enregistrement
 * @pre: r != NULL && CRC2!=NULL
 */
void record_set_CRC2(const struct record *r,  unsigned int CRC2);
