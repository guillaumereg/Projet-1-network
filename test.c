#include <CUnit/Basic.h>
#include <CUnit/CUnit.h>

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include <zlib.h>

#include "paquet.h"
#include "receiver.h"
#include "sender.h"




//test création
void test_new()
{
	  pkt_t * pkt_test = pkt_new();

	  CU_ASSERT_PTR_NOT_NULL(pkt_test);
    CU_ASSERT_PTR_NOT_NULL(pkt_test);

	  pkt_del(pkt_test);
}


//test supression
void test_del()
{
	pkt_t * pkt_test = pkt_new();

	pkt_del(pkt_test);

	CU_ASSERT_PTR_NULL(pkt_test);
  CU_ASSERT_PTR_NULL(pkt_test);
}


//test type
void test_type() {

    pkt_t * pkt_test = pkt_new();

    //Test des cas où cela fonctionne

    CU_ASSERT(pkt_set_type(pkt_test, 1) == PKT_OK);
    CU_ASSERT(pkt_get_type(pkt_test) == 1);
    CU_ASSERT(pkt_get_type(pkt_test) == 1);

    CU_ASSERT(pkt_set_type(pkt_test, 2) == PKT_OK);
    CU_ASSERT(pkt_get_type(pkt_test) == 2);
    CU_ASSERT(pkt_get_type(pkt_test) == 2);

    CU_ASSERT(pkt_set_type(pkt_test, 3) == PKT_OK);
    CU_ASSERT(pkt_get_type(pkt_test) == 3);
    CU_ASSERT(pkt_get_type(pkt_test) == 3);

    // Test des erreurs

    CU_ASSERT(pkt_set_type(pkt_test, 4) == E_TYPE);
    CU_ASSERT(pkt_get_type(pkt_test) != 4);
    CU_ASSERT(pkt_set_type(pkt_test, 0) == E_TYPE);
    CU_ASSERT(pkt_get_type(pkt_test) != 0);


    pkt_del(pkt_test);
}

//test tr
void test_tr() {

    pkt_t * pkt_test = pkt_new();

    //Test des cas où cela fonctionne

    CU_ASSERT(pkt_set_tr(pkt_test, 1) == PKT_OK);
    CU_ASSERT(pkt_get_tr(pkt_test) == 1);
    CU_ASSERT(pkt_get_tr(pkt_test) == 1);

    CU_ASSERT(pkt_set_tr(pkt_test, 0) == PKT_OK);
    CU_ASSERT(pkt_get_tr(pkt_test) == 0);
    CU_ASSERT(pkt_get_tr(pkt_test) == 0);


    // Test des erreurs

    CU_ASSERT(pkt_set_tr(pkt_test, 2) == E_TR);
    CU_ASSERT(pkt_get_tr(pkt_test) != 2);


    pkt_del(pkt_test);
}

//test window
void test_window() {

    pkt_t * pkt_test = pkt_new();

    //Test des cas où cela fonctionne

    CU_ASSERT(pkt_set_window(pkt_test, 0) == PKT_OK);
    CU_ASSERT(pkt_get_window(pkt_test) == 0);
    CU_ASSERT(pkt_get_window(pkt_test) == 0);

    CU_ASSERT(pkt_set_window(pkt_test, 31) == PKT_OK);
    CU_ASSERT(pkt_get_window(pkt_test) == 31);
    CU_ASSERT(pkt_get_window(pkt_test) == 31);


    // Test des erreurs

    CU_ASSERT(pkt_set_window(pkt_test, 32) == E_WINDOW);
    CU_ASSERT(pkt_get_window(pkt_test) != 32);


    pkt_del(pkt_test);
}


//test seqnum
void test_seqnum() {

    pkt_t * pkt_test = pkt_new();

    //Test des cas où cela fonctionne

    CU_ASSERT(pkt_set_seqnum(pkt_test, 0) == PKT_OK);
    CU_ASSERT(pkt_get_seqnum(pkt_test) == 0);
    CU_ASSERT(pkt_get_seqnum(pkt_test) == 0);

    CU_ASSERT(pkt_set_seqnum(pkt_test, 255) == PKT_OK);
    CU_ASSERT(pkt_get_seqnum(pkt_test) == 255);
    CU_ASSERT(pkt_get_seqnum(pkt_test) == 255);


    pkt_del(pkt_test);
}


//test length
void test_length() {

    pkt_t * pkt_test = pkt_new();

    //Test des cas où cela fonctionne

    CU_ASSERT(pkt_set_length(pkt_test, 0) == PKT_OK);
    CU_ASSERT(pkt_get_length(pkt_test) == 0);
    CU_ASSERT(pkt_get_length(pkt_test) == 0);

    CU_ASSERT(pkt_set_length(pkt_test, 512) == PKT_OK);
    CU_ASSERT(pkt_get_length(pkt_test) == 512);
    CU_ASSERT(pkt_get_length(pkt_test) == 512);


    // Test des erreurs

    CU_ASSERT(pkt_set_length(pkt_test, 513) == E_LENGTH);
    CU_ASSERT(pkt_get_length(pkt_test) != 513);


    pkt_del(pkt_test);
}

//test timestamp
void test_timestamp() {

    pkt_t * pkt_test = pkt_new();


    CU_ASSERT(pkt_set_timestamp(pkt_test, 0) == PKT_OK);
    CU_ASSERT(pkt_get_timestamp(pkt_test) == 0);
    CU_ASSERT(pkt_get_timestamp(pkt_test) == 0);


    pkt_del(pkt_test);
}


//test payload
void test_payload() {

    pkt_t * pkt_test = pkt_new();

    //Test cas de base

    CU_ASSERT(pkt_set_payload(pkt_test,"Maison", 6) == PKT_OK);
    CU_ASSERT_STRING_EQUAL(pkt_get_payload(pkt_test), "Maison");
    CU_ASSERT_STRING_EQUAL(pkt_get_payload(pkt_test), "Maison");
    CU_ASSERT(pkt_get_length(pkt_test) == 6);
    CU_ASSERT(pkt_get_length(pkt_test) == 6);

    //Test nul

    CU_ASSERT(pkt_set_payload(pkt_test,NULL, 0) == PKT_OK);
    CU_ASSERT(pkt_get_length(pkt_test) == 0);

    //Test incohérence

    CU_ASSERT(pkt_set_payload(pkt_test,"abc", 4) == E_UNCONSISTENT);


    pkt_del(pkt_test);
}


//test encode et decode
void test_encode_decode() {

    pkt_t * pkt_test = pkt_new();

  //creation pkt

    CU_ASSERT(pkt_set_type(pkt_test, (const uint8_t) 1) == PKT_OK);
    CU_ASSERT(pkt_set_tr(pkt_test, (const uint8_t) 0) ==PKT_OK);
    CU_ASSERT(pkt_set_window(pkt_test, (const uint8_t) 3) ==PKT_OK);
    CU_ASSERT(pkt_set_seqnum(pkt_test, (const uint8_t) 42) ==PKT_OK);
    CU_ASSERT(pkt_set_length(pkt_test, (const uint16_t) 5) ==PKT_OK);
    CU_ASSERT(pkt_set_timestamp(pkt_test, (const uint16_t) 0) ==PKT_OK);
    CU_ASSERT(pkt_set_payload(pkt_test, "abcde" , (const uint16_t)5) ==PKT_OK);

  //test encode
    char *buf = malloc(1024);
    size_t len = 1024;
    CU_ASSERT(pkt_encode(pkt_test, buf, &len) == PKT_OK);

  //test decode
    pkt_t *pkt_test2 = pkt_new();
    CU_ASSERT(pkt_decode(buf, len, pkt_test2) == PKT_OK);


  //test avant = après

    CU_ASSERT(pkt_get_type(pkt_test) == (pkt_get_type(pkt_test2)));
    CU_ASSERT(pkt_get_tr(pkt_test) == (pkt_get_tr(pkt_test2)));
    CU_ASSERT(pkt_get_window(pkt_test) == (pkt_get_window(pkt_test2)));
    CU_ASSERT(pkt_get_seqnum(pkt_test) == (pkt_get_seqnum(pkt_test2)));
    CU_ASSERT(pkt_get_length(pkt_test) == (pkt_get_length(pkt_test2)));
    CU_ASSERT(pkt_get_timestamp(pkt_test) == (pkt_get_timestamp(pkt_test2)));
    CU_ASSERT(pkt_get_crc1(pkt_test) == (pkt_get_crc1(pkt_test2)));
    CU_ASSERT(pkt_get_payload(pkt_test) == (pkt_get_payload(pkt_test2)));
    CU_ASSERT(pkt_get_crc2(pkt_test) == (pkt_get_crc2(pkt_test2)));



    pkt_del(pkt_test);
    pkt_del(pkt_test2);
}

void main(int argc, const char *argv[])
{

    // initialisation registre CUnit
    if(CUE_SUCCESS != CU_initialize_registry()) {
        return(CU_get_error());
    }

    //création suite test
    CU_pSuite test = NULL;
    test = CU_add_suite("Ensemble des tests", NULL, NULL);

    if (test == NULL) {
        CU_cleanup_registry();
        return(CU_get_error());
    }

//ensemble des tests
    if      (
        (NULL == CU_add_test(test, "new", test_new)) ||
        (NULL == CU_add_test(test, "del", test_del)) ||
        (NULL == CU_add_test(test, "type", test_type)) ||
        (NULL == CU_add_test(test, "tr", test_tr)) ||
        (NULL == CU_add_test(test, "window", test_window)) ||
        (NULL == CU_add_test(test, "seqnum", test_seqnum)) ||
        (NULL == CU_add_test(test, "length", test_length)) ||
        (NULL == CU_add_test(test, "timestamp", test_timestamp)) ||
        (NULL == CU_add_test(test, "payload", test_payload)) ||
        (NULL == CU_add_test(test, "encode_decode", test_encode_decode)) ||
    )
    {
        CU_cleanup_registry();
        return CU_get_error();
    }

    CU_basic_run_tests();
    CU_cleanup_registry();
    return 0;
}
