#include <CUnit/Basic.h>
#include <CUnit/CUnit.h>

#include <stdlib.h>
#include <string.h>

#include <zlib.h>



//test type
void test_pkt_type(void) {

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
void test_pkt_tr(void) {

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
void test_pkt_window(void) {

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
void test_pkt_seqnum(void) {

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
void test_pkt_length(void) {

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


void test_pkt_payload(void) {

    pkt_t * pkt_test = pkt_new();

    //Test cas de base

    CU_ASSERT(pkt_set_payload(pkt_test,"Maison", 6) == PKT_OK);
    CU_ASSERT_STRING_EQUAL(pkt_get_payload(pkt_test), "Maison");
    CU_ASSERT_STRING_EQUAL(pkt_get_payload(pkt_test), "Maison");
    CU_ASSERT(pkt_get_length(pkt_test) == 6);
    CU_ASSERT(pkt_get_length(pkt_test) == 6);

    //Test nul

    CU_ASSERT(pkt_set_payload(pkt_test,NULL, 0) == PKT_OK);
    CU_ASSERT_STRING_EQUAL(pkt_get_payload(pkt_test), NULL);
    CU_ASSERT(pkt_get_length(pkt_test) == 0);

    //Test incohérence

    CU_ASSERT(pkt_set_payload(pkt_test,"abc", 4) == E_UNCONSISTENT);


    pkt_del(pkt);
}
