// CamIO 2: demo_array.c
// Copyright (C) 2013: Matthew P. Grosvenor (matthew.grosvenor@cl.cam.ac.uk) 
// Licensed under BSD 3 Clause, please see LICENSE for more details. 

#include "../data_structs/vector/vector_std.h"
#include "../utils/util.h"

#include <stdio.h>


static int cmp_i64(i64* lhs, i64* rhs)
{
    if(*lhs < *rhs){
        return -1;
    }

    if(*lhs > *rhs){
        return 1;
    }

    return 0;
}


void dump_array_i64(ch_vector_i64_t* al)
{
    printf("There are %lli items in the list\n", al->count);
    for(i64* i = al->first; i < al->end; i = al->next(al, i)){
        printf("%lli,", *i);
    }
    printf("\n");
}


static i64 test1_i64(i64* test_data)
{
    i64 result = 1;
    /* Test the initial conditions and equality of new (empty) array lists*/
    (void)test_data;
    ch_vector_i64_t* al1 = ch_vector_i64_new(0,cmp_i64);
    CH_ASSERT(al1->_vector->_array->_array_backing == NULL);
    CH_ASSERT(al1->first == NULL);
    CH_ASSERT(al1->last == NULL);
    CH_ASSERT(al1->end == NULL);
    CH_ASSERT(al1->_vector->count == 0);
    CH_ASSERT(al1->_vector->size == 0);
    CH_ASSERT(al1->_vector->_cmp == (cmp_void_f)cmp_i64);
    CH_ASSERT(al1->count == 0);
    CH_ASSERT(al1->size == 0);

    ch_vector_i64_t* al2 = ch_vector_i64_new(0,cmp_i64);
    CH_ASSERT(al2 != al1);
    CH_ASSERT(al1->eq(al1,al2));
    CH_ASSERT(al1->eq(al2,al1));
    al1->delete(al1);
    al2->delete(al2);
    return result;
}


/* Test the initial conditions and equality of new non-empty array lists*/
static i64 test2_i64(i64* test_data)
{
    i64 result = 1;

    (void)test_data;
    ch_vector_i64_t* al1 = ch_vector_i64_new(1,cmp_i64);
    CH_ASSERT(al1->_vector->first);
    CH_ASSERT(al1->first == al1->_vector->first);
    CH_ASSERT(al1->last == al1->first);
    CH_ASSERT(al1->end == al1->last);
    CH_ASSERT(al1->_vector->count == 0);
    CH_ASSERT(al1->_vector->size == 1);
    CH_ASSERT(al1->_vector->_cmp == (cmp_void_f)cmp_i64);
    CH_ASSERT(al1->count == 0);
    CH_ASSERT(al1->size == 1);

    ch_vector_i64_t* al2 = ch_vector_i64_new(1,cmp_i64);

    CH_ASSERT(al2 != al1);
    CH_ASSERT(al1->eq(al1,al2));
    CH_ASSERT(al1->eq(al2,al1));
    al1->delete(al1);
    al2->delete(al2);

    return result;
}

/* Insert an element into an array of size 0. Use both push back and push front*/
static i64 test3_i64(i64* test_data)
{
    i64 result = 1;

    ch_vector_i64_t* al1 = ch_vector_i64_new(0,cmp_i64);
    CH_ASSERT(al1->push_back(al1, test_data[0]));
    CH_ASSERT(al1->_vector->first);
    CH_ASSERT(al1->first == al1->_vector->first);
    CH_ASSERT(al1->last == al1->first);
    CH_ASSERT(al1->end != al1->last);
    CH_ASSERT(*al1->first == test_data[0]);
    CH_ASSERT(*al1->last == test_data[0]);
    CH_ASSERT(al1->_vector->count == 1);
    CH_ASSERT(al1->_vector->size == 1);
    CH_ASSERT(al1->_vector->_cmp == (cmp_void_f)cmp_i64);
    CH_ASSERT(al1->count == 1);
    CH_ASSERT(al1->size == 1);

    ch_vector_i64_t* al2 = ch_vector_i64_new(0,cmp_i64);
    CH_ASSERT(al2 != al1);
    CH_ASSERT(!al1->eq(al1,al2));
    CH_ASSERT(al2->push_front(al2, test_data[0]));

    CH_ASSERT(al1->eq(al1,al2));
    CH_ASSERT(al2->eq(al2,al1));
    CH_ASSERT(al1->first != al2->first);
    al1->delete(al1);
    al2->delete(al2);
    return result;
}



/* Insrt an element into an array of size 1*/
static i64 test4_i64(i64* test_data)
{
    i64 result = 1;

    ch_vector_i64_t* al1 = ch_vector_i64_new(1,cmp_i64);
    CH_ASSERT(al1->push_back(al1, test_data[0]));
    CH_ASSERT(al1->_vector->first);
    CH_ASSERT(al1->first == al1->_vector->first);
    CH_ASSERT(al1->last == al1->first);
    CH_ASSERT(al1->end != al1->last);
    CH_ASSERT(*al1->first == test_data[0]);
    CH_ASSERT(*al1->last == test_data[0]);
    CH_ASSERT(al1->_vector->count == 1);
    CH_ASSERT(al1->_vector->size == 1);
    CH_ASSERT(al1->_vector->_cmp == (cmp_void_f)cmp_i64);
    CH_ASSERT(al1->count == 1);
    CH_ASSERT(al1->size == 1);

    ch_vector_i64_t* al2 = ch_vector_i64_new(1,cmp_i64);
    CH_ASSERT(al2->push_front(al2, test_data[0]));

    CH_ASSERT(al2 != al1);
    CH_ASSERT(al1->eq(al1,al2));
    CH_ASSERT(al2->eq(al2,al1));
    CH_ASSERT(al1->first != al2->first);
    al1->delete(al1);
    al2->delete(al2);
    return result;
}

/* Insert an element into an array of size 10*/
static i64 test5_i64(i64* test_data)
{
    i64 result = 1;

    ch_vector_i64_t* al1 = ch_vector_i64_new(10,cmp_i64);
    CH_ASSERT(al1->push_back(al1, test_data[0]));
    CH_ASSERT(al1->_vector->first);
    CH_ASSERT(al1->first == al1->_vector->first);
    CH_ASSERT(al1->last == al1->first);
    CH_ASSERT(al1->end != al1->last);
    CH_ASSERT(*al1->first == test_data[0]);
    CH_ASSERT(*al1->last == test_data[0]);
    CH_ASSERT(al1->_vector->count == 1);
    CH_ASSERT(al1->_vector->size == 10);
    CH_ASSERT(al1->_vector->_cmp == (cmp_void_f)cmp_i64);
    CH_ASSERT(al1->count == 1);
    CH_ASSERT(al1->size == 10);

    ch_vector_i64_t* al2 = ch_vector_i64_new(10,cmp_i64);
    CH_ASSERT(al2->push_front(al2, test_data[0]));

    CH_ASSERT(al2 != al1);
    CH_ASSERT(al1->eq(al1,al2));
    CH_ASSERT(al2->eq(al2,al1));
    CH_ASSERT(al1->first != al2->first);
    al1->delete(al1);
    al2->delete(al2);
    return result;
}


/* Insert 2 elements into an array of size 0 and 1. Use both push back and push front*/
static i64 test6_i64(i64* test_data)
{
    i64 result = 1;

    ch_vector_i64_t* al1 = ch_vector_i64_new(0,cmp_i64);
    CH_ASSERT(al1->push_back(al1, test_data[0]));
    CH_ASSERT(al1->push_back(al1, test_data[1]));
    CH_ASSERT(al1->_vector->first);
    CH_ASSERT(al1->first == al1->_vector->first);
    CH_ASSERT(al1->last != al1->first);
    CH_ASSERT(al1->end != al1->last);
    CH_ASSERT(*al1->first == test_data[0]);
    CH_ASSERT(*al1->last == test_data[1]);
    CH_ASSERT(al1->_vector->count == 2);
    CH_ASSERT(al1->_vector->size == 2);
    CH_ASSERT(al1->_vector->_cmp == (cmp_void_f)cmp_i64);
    CH_ASSERT(al1->count == 2);
    CH_ASSERT(al1->size == 2);

    ch_vector_i64_t* al2 = ch_vector_i64_new(1,cmp_i64);
    CH_ASSERT(al2->first == al2->_vector->first);
    CH_ASSERT(al2->last == al2->first);
    CH_ASSERT(al2->end == al2->last);


    CH_ASSERT(al2->push_front(al2, test_data[1]));
    CH_ASSERT(al2->first == al2->_vector->first);
    CH_ASSERT(al2->last == al2->first);
    CH_ASSERT(al2->end != al2->last);
    CH_ASSERT(*al2->first == test_data[1]);

    CH_ASSERT(al2->push_front(al2, test_data[0]));
    CH_ASSERT(al2->first == al2->_vector->first);
    CH_ASSERT(al2->last != al2->first);
    CH_ASSERT(al2->end != al2->last);

    CH_ASSERT(*al2->first == test_data[0]);
    CH_ASSERT(*al2->last == test_data[1]);

    CH_ASSERT(al2 != al1);
    CH_ASSERT(al1->eq(al1,al2));
    CH_ASSERT(al2->eq(al2,al1));
    CH_ASSERT(al1->first != al2->first);
    al1->delete(al1);
    al2->delete(al2);
    return result;
}


/* Insert 2 elements into an array of size 0 and 1. Remove the head element. */
static i64 test7_i64(i64* test_data)
{
    i64 result = 1;
    i64* rmv_1 = NULL;
    i64* rmv_2 = NULL;

    ch_vector_i64_t* al1 = ch_vector_i64_new(0,cmp_i64);
    ch_vector_i64_t* al2 = ch_vector_i64_new(2,cmp_i64);

    /* Make sure that this works a few times over */
    for(i64 i = 0; i < 10; i++){

        CH_ASSERT(al1->push_back(al1, test_data[0]));
        CH_ASSERT(al1->push_back(al1, test_data[1]));
        CH_ASSERT(al1->first == al1->_vector->first);

        CH_ASSERT(al2->push_front(al2, test_data[1]));
        CH_ASSERT(al2->push_front(al2, test_data[0]));

        rmv_1 = al1->first;
        rmv_2 = al2->first;
        CH_ASSERT(*al1->remove(al1,rmv_1) == test_data[1]);
        CH_ASSERT(*al2->remove(al2,rmv_2) == test_data[1]);

        CH_ASSERT(al1->last == al1->first);
        CH_ASSERT(al1->end != al1->last);
        CH_ASSERT(*al1->first == test_data[1]);
        CH_ASSERT(*al1->last == test_data[1]);
        CH_ASSERT(al1->_vector->count == 1);
        CH_ASSERT(al1->_vector->size == 2);
        CH_ASSERT(al1->count == 1);
        CH_ASSERT(al1->size == 2);

        CH_ASSERT(al2->last == al2->first);
        CH_ASSERT(al2->end != al2->last);
        CH_ASSERT(*al2->first == test_data[1]);
        CH_ASSERT(*al2->last == test_data[1]);
        CH_ASSERT(al2->_vector->count == 1);
        CH_ASSERT(al2->_vector->size == 2);
        CH_ASSERT(al2->count == 1);
        CH_ASSERT(al2->size == 2);

        CH_ASSERT(al1->eq(al1,al2));
        CH_ASSERT(al2->eq(al2,al1));
        CH_ASSERT(al1->first != al2->first);

        CH_ASSERT(al1->remove(al1,al1->first) == NULL);
        CH_ASSERT(al2->remove(al2,al2->last) == NULL);

        CH_ASSERT(al1->last == al1->first);
        CH_ASSERT(al1->end == al1->last);
        CH_ASSERT(al1->_vector->count == 0);
        CH_ASSERT(al1->_vector->size == 2);
        CH_ASSERT(al1->count == 0);
        CH_ASSERT(al1->size == 2);

        CH_ASSERT(al2->last == al2->first);
        CH_ASSERT(al2->end == al2->last);
        CH_ASSERT(al2->_vector->count == 0);
        CH_ASSERT(al2->_vector->size == 2);
        CH_ASSERT(al2->count == 0);
        CH_ASSERT(al2->size == 2);

        CH_ASSERT(al1->eq(al1,al2));
        CH_ASSERT(al2->eq(al2,al1));
    }


    al1->delete(al1);
    al2->delete(al2);
    return result;
}


static i64 test8_i64(i64* test_data)
{
    i64 result = 1;

    (void)test_data;
    ch_vector_i64_t* al1 = ch_vector_i64_new(0,cmp_i64);
    ch_vector_i64_t* al2 = ch_vector_i64_new(0,cmp_i64);

    al1->sort(al1);

    CH_ASSERT(al2 != al1);
    CH_ASSERT(al1->_vector->first == NULL);
    CH_ASSERT(al1->first == NULL);
    CH_ASSERT(al1->last == NULL);
    CH_ASSERT(al1->end == NULL);
    CH_ASSERT(al1->_vector->count == 0);
    CH_ASSERT(al1->_vector->size == 0);
    CH_ASSERT(al1->_vector->_cmp == (cmp_void_f)cmp_i64);
    CH_ASSERT(al1->count == 0);
    CH_ASSERT(al1->size == 0);

    CH_ASSERT(al1->eq(al1,al2));
    CH_ASSERT(al1->eq(al2,al1));
    al1->delete(al1);
    al2->delete(al2);
    return result;
}

static i64 test9_i64(i64* test_data)
{
    i64 result = 1;

    ch_vector_i64_t* al1 = ch_vector_i64_new(0,cmp_i64);
    ch_vector_i64_t* al2 = ch_vector_i64_new(0,cmp_i64);

    CH_ASSERT(al1->push_back(al1, test_data[0]));
    CH_ASSERT(al2->push_front(al2, test_data[0]));

    al1->sort(al1);

    CH_ASSERT(al2 != al1);
    CH_ASSERT(al1->_vector->first);
    CH_ASSERT(al1->first == al1->_vector->first);
    CH_ASSERT(al1->last == al1->last);
    CH_ASSERT(al1->end == al1->last + 1);
    CH_ASSERT(al1->_vector->count == 1);
    CH_ASSERT(al1->_vector->size == 1);
    CH_ASSERT(al1->_vector->_cmp == (cmp_void_f)cmp_i64);
    CH_ASSERT(al1->count == 1);
    CH_ASSERT(al1->size == 1);

    CH_ASSERT(al1->eq(al1,al2));
    CH_ASSERT(al1->eq(al2,al1));

    al1->delete(al1);
    al2->delete(al2);
    return result;
}

static i64 test10_i64(i64* test_data)
{
    i64 result = 1;
    ch_vector_i64_t* al1 = ch_vector_i64_new(0,cmp_i64);
    ch_vector_i64_t* al2 = ch_vector_i64_new(0,cmp_i64);

    CH_ASSERT(al1->push_back(al1, test_data[0]));
    CH_ASSERT(al1->push_back(al1, test_data[1]));
    CH_ASSERT(al2->push_front(al2, test_data[0]));
    CH_ASSERT(al2->push_front(al2, test_data[1]));

    al1->sort(al1);

    CH_ASSERT(al2 != al1);
    CH_ASSERT(al1->_vector->first);
    CH_ASSERT(al1->first == al1->_vector->first);
    CH_ASSERT(al1->last == al1->last);
    CH_ASSERT(al1->end == al1->last + 1);
    CH_ASSERT(al1->_vector->count == 2);
    CH_ASSERT(al1->_vector->size == 2);
    CH_ASSERT(al1->_vector->_cmp == (cmp_void_f)cmp_i64);
    CH_ASSERT(al1->count == 2);
    CH_ASSERT(al1->size == 2);

    CH_ASSERT(al1->eq(al1,al2));
    CH_ASSERT(al1->eq(al2,al1));

    al1->delete(al1);
    al2->delete(al2);
    return result;
}

//Push two carrays on and make sure the results are the same.
static i64 test11_i64(i64* test_data, i64* test_result)
{
    i64 result = 1;

    ch_vector_i64_t* al1 = ch_vector_i64_new(0,cmp_i64);
    ch_vector_i64_t* al2 = ch_vector_i64_new(0,cmp_i64);

    for(i64 i = 0; i < 10; i++){
        al1->push_back_carray(al1,test_data, 15);

        CH_ASSERT(al1->first == al1->_vector->first);
        CH_ASSERT(al1->last == al1->last);
        CH_ASSERT(al1->end == al1->last + 1);

        al1->sort(al1);

        CH_ASSERT(al1->first == al1->_vector->first);
        CH_ASSERT(al1->last == al1->last);
        CH_ASSERT(al1->end == al1->last + 1);

    }

    al2->push_back_carray(al2,test_result, 150);

    CH_ASSERT(al2 != al1);
    CH_ASSERT(al1->_vector->first);
    CH_ASSERT(al1->first == al1->_vector->first);
    CH_ASSERT(al1->last == al1->last);
    CH_ASSERT(al1->end == al1->last + 1);
    CH_ASSERT(al1->_vector->count == 150);
    CH_ASSERT(al1->_vector->size == 256);
    CH_ASSERT(al1->_vector->_cmp == (cmp_void_f)cmp_i64);
    CH_ASSERT(al1->count == 150);
    CH_ASSERT(al1->size == 256);

    CH_ASSERT(al1->eq(al1,al2));
    CH_ASSERT(al1->eq(al2,al1));

    al1->delete(al1);
    al2->delete(al2);
    return result;
}


static i64 test12_i64(i64* test_data)
{
    i64 result = 1;

    ch_vector_i64_t* al1 = ch_vector_i64_new(0,cmp_i64);

    CH_ASSERT(al1->find(al1,al1->first, al1->end, test_data[1]) == NULL);


    al1->delete(al1);

    return result;
}


static i64 test13_i64(i64* test_data)
{
    i64 result = 1;

    ch_vector_i64_t* al1 = ch_vector_i64_new(0,cmp_i64);
    al1->push_back_carray(al1, test_data, 3);

    CH_ASSERT(*al1->find(al1,al1->first, al1->end, test_data[1]) == test_data[1]);

    al1->delete(al1);

    return result;
}

static i64 test14_i64(i64* test_data)
{
    i64 result = 1;

    ch_vector_i64_t* al1 = ch_vector_i64_new(0,cmp_i64);
    al1->push_back_carray(al1, test_data, 3);

    CH_ASSERT(al1->find(al1,al1->first, al1->end, 42) == NULL);
    CH_ASSERT(al1->find(al1,al1->end, al1->end, 42) == NULL);
    CH_ASSERT(al1->find(al1,al1->first, al1->first + 1, test_data[1]) == NULL);
    CH_ASSERT(al1->find(al1,al1->first + 2, al1->first + 2, test_data[2]) == NULL);
    CH_ASSERT(*al1->find(al1,al1->first, al1->first + 2, test_data[1]) == test_data[1]);

    al1->delete(al1);

    return result;
}


/* Found a bug in the equaility operator. This should stimulate it*/
static i64 test15_i64(i64* test_data)
{
    i64 result = 1;

    ch_vector_i64_t* al1 = ch_vector_i64_new(0,cmp_i64);
    CH_ASSERT(al1->push_back(al1, test_data[0]));
    CH_ASSERT(al1->_vector->first);
    CH_ASSERT(al1->first == al1->_vector->first);
    CH_ASSERT(al1->last == al1->first);
    CH_ASSERT(al1->end != al1->last);
    CH_ASSERT(*al1->first == test_data[0]);
    CH_ASSERT(*al1->last == test_data[0]);
    CH_ASSERT(al1->_vector->count == 1);
    CH_ASSERT(al1->_vector->size == 1);
    CH_ASSERT(al1->_vector->_cmp == (cmp_void_f)cmp_i64);
    CH_ASSERT(al1->count == 1);
    CH_ASSERT(al1->size == 1);

    ch_vector_i64_t* al2 = ch_vector_i64_new(0,cmp_i64);
    CH_ASSERT(!al1->eq(al1,al2));
    CH_ASSERT(al2->push_front(al2, test_data[1]));

    CH_ASSERT(al2 != al1);

    CH_ASSERT(!al1->eq(al1,al2));
    CH_ASSERT(!al2->eq(al2,al1));
    CH_ASSERT(al1->first != al2->first);
    al1->delete(al1);
    al2->delete(al2);
    return result;
}

//Found a bug push_back carray. This stimulated it
static i64 test16_i64(i64* test_data)
{
    i64 result = 1;

    ch_vector_i64_t* al1 = ch_vector_i64_new(0,cmp_i64);
    ch_vector_i64_t* al2 = ch_vector_i64_new(0,cmp_i64);
    CH_ASSERT(al1->push_back(al1, test_data[0]));
    CH_ASSERT(al1->push_back_carray(al1, &test_data[1],7));
    CH_ASSERT(al1->push_back_carray(al1, &test_data[8],7));
    CH_ASSERT(al2->push_back_carray(al2, &test_data[0],15));


    CH_ASSERT(al1->eq(al1,al2));
    CH_ASSERT(al2->eq(al2,al1));
    al1->delete(al1);
    al2->delete(al2);
    return result;
}

//Found another bug push_back carray. This also stimulated it
static i64 test17_i64(i64* test_data)
{
    i64 result = 1;
    (void)test_data;

    char* data1[2] = { "06", "03" };
    char* data2 = "0603";

    CH_VECTOR(i8)* key_buff1 = CH_VECTOR_NEW(i8,1024,CH_VECTOR_CMP(i8));
    key_buff1->push_back_carray(key_buff1,(i8*)data1[0],2);
    key_buff1->push_back_carray(key_buff1,(i8*)data1[1],2);

    CH_VECTOR(i8)* key_buff2 = CH_VECTOR_NEW(i8,1024,CH_VECTOR_CMP(i8));
    key_buff2->push_back_carray(key_buff2,(i8*)data2,4);

    CH_ASSERT(key_buff2->eq(key_buff2, key_buff1));

    return result;
}

/* Testing the new clear method*/
static i64 test18_i64(i64* test_data)
{
    i64 result = 1;

    ch_vector_i64_t* v1 = ch_vector_i64_new(0,cmp_i64);
    ch_vector_i64_t* v2 = ch_vector_i64_new(0,cmp_i64);
    CH_ASSERT(v1->push_back_carray(v1, test_data, 15));
    v1->clear(v1);
    CH_ASSERT(v1->eq(v1,v2));
    CH_ASSERT(v2->eq(v2,v1));
    return result;
}

int main(int argc, char** argv)
{
    (void)argc;
    (void)argv;

    i64 test_array[15] = {8,5,1,3,4,6,7,9,7,1,6,1,0,1,6};
    i64 test_array_sorted[150] = {0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,3,3,3,3,3,3,3,3,3,3,4,4,4,4,4,4,4,4,4,4,5,5,5,5,5,5,5,5,5,5,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,8,8,8,8,8,8,8,8,8,8,9,9,9,9,9,9,9,9,9,9};

    i64 test_result = 0;

    printf("CH Data Structures: Vector Test 01: ");  printf("%s", (test_result = test1_i64(test_array)) ? "PASS\n" : "FAIL\n"); if(!test_result) return 1;
    printf("CH Data Structures: Vector Test 02: ");  printf("%s", (test_result = test2_i64(test_array)) ? "PASS\n" : "FAIL\n"); if(!test_result) return 1;
    printf("CH Data Structures: Vector Test 03: ");  printf("%s", (test_result = test3_i64(test_array)) ? "PASS\n" : "FAIL\n"); if(!test_result) return 1;
    printf("CH Data Structures: Vector Test 04: ");  printf("%s", (test_result = test4_i64(test_array)) ? "PASS\n" : "FAIL\n"); if(!test_result) return 1;
    printf("CH Data Structures: Vector Test 05: ");  printf("%s", (test_result = test5_i64(test_array)) ? "PASS\n" : "FAIL\n"); if(!test_result) return 1;
    printf("CH Data Structures: Vector Test 06: ");  printf("%s", (test_result = test6_i64(test_array)) ? "PASS\n" : "FAIL\n"); if(!test_result) return 1;
    printf("CH Data Structures: Vector Test 07: ");  printf("%s", (test_result = test7_i64(test_array)) ? "PASS\n" : "FAIL\n"); if(!test_result) return 1;
    printf("CH Data Structures: Vector Test 08: ");  printf("%s", (test_result = test8_i64(test_array)) ? "PASS\n" : "FAIL\n"); if(!test_result) return 1;
    printf("CH Data Structures: Vector Test 09: ");  printf("%s", (test_result = test9_i64(test_array)) ? "PASS\n" : "FAIL\n"); if(!test_result) return 1;
    printf("CH Data Structures: Vector Test 10: ");  printf("%s", (test_result = test10_i64(test_array)) ? "PASS\n" : "FAIL\n"); if(!test_result) return 1;
    printf("CH Data Structures: Vector Test 11: ");  printf("%s", (test_result = test11_i64(test_array, test_array_sorted)) ? "PASS\n" : "FAIL\n"); if(!test_result) return 1;
    printf("CH Data Structures: Vector Test 12: ");  printf("%s", (test_result = test12_i64(test_array)) ? "PASS\n" : "FAIL\n"); if(!test_result) return 1;
    printf("CH Data Structures: Vector Test 13: ");  printf("%s", (test_result = test13_i64(test_array)) ? "PASS\n" : "FAIL\n"); if(!test_result) return 1;
    printf("CH Data Structures: Vector Test 14: ");  printf("%s", (test_result = test14_i64(test_array)) ? "PASS\n" : "FAIL\n"); if(!test_result) return 1;
    printf("CH Data Structures: Vector Test 15: ");  printf("%s", (test_result = test15_i64(test_array)) ? "PASS\n" : "FAIL\n"); if(!test_result) return 1;
    printf("CH Data Structures: Vector Test 16: ");  printf("%s", (test_result = test16_i64(test_array)) ? "PASS\n" : "FAIL\n"); if(!test_result) return 1;
    printf("CH Data Structures: Vector Test 17: ");  printf("%s", (test_result = test17_i64(test_array)) ? "PASS\n" : "FAIL\n"); if(!test_result) return 1;
    printf("CH Data Structures: Vector Test 17: ");  printf("%s", (test_result = test18_i64(test_array)) ? "PASS\n" : "FAIL\n"); if(!test_result) return 1;

    return 0;
}


