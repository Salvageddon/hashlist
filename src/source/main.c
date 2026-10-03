#include <stdio.h>
#include <stdlib.h>
#include "../include/hashlist.h"
#include <salvagames/memoryleaks.h>

typedef struct{
    int a;
    float b;
    char * dynamic;
} Test;

Test * createTest(int a, float b){
    Test * o = malloc(sizeof(Test));

    o->a = a;
    o->b = b;
    o->dynamic = malloc(20);

    for(int i = 0; i < 19; i++){
        o->dynamic[i] = i + 'a';
    }

    o->dynamic[19] = '\0';

    return o;
}

void freeTest(void * test){
    Test * t = test;

    free(t->dynamic);
    free(t);
}

void displayList(Hashlist list){
    printf("\n=== %d Items total: ===\n", list.length);
    for(int i = 0; i < list.length; i++){
        unsigned int key = HLS_getKey(list, i);
        int index = HLS_getIndex(list, key);

        Test * test1 = HLS_getByIndex(list, i);
        Test * test2 = HLS_get(list, key);

        printf("[%d , (%d : 0x%x)]: %d %f %s\n", index, key, key, test1->a, test2->b, test1->dynamic);
    }
    printf("\n");
}

int main(){
    Hashlist list = HLS_createList();

    HLS_add(&list, 1, createTest(10, 0.5F), &freeTest);
    HLS_add(&list, 2, createTest(20, 1.5F), &freeTest);
    HLS_add(&list, 3, createTest(30, 2.5F), &freeTest);
    HLS_add(&list, 4, createTest(40, 3.5F), &freeTest);
    HLS_add(&list, 5, createTest(50, 4.5F), &freeTest);
    HLS_add(&list, 6, createTest(60, 5.5F), &freeTest);
    HLS_add(&list, 7, createTest(70, 6.5F), &freeTest);
    HLS_add(&list, 8, createTest(80, 7.5F), &freeTest);

    displayList(list);

    HLS_addAt(&list, 4, 0xA1000000, createTest(90, 8.5F), &freeTest);

    displayList(list);

    HLS_remove(&list, 1, 1);

    displayList(list);

    HLS_removeAt(&list, 6, 1);

    displayList(list);

    HLS_set(list, 0xa1000000, createTest(10, 0.5F), &freeTest, 1);
    HLS_setAt(list, 6, createTest(15, 3.14F), &freeTest, 1);
    HLS_setKey(list, 5, 0xA2000000);
    HLS_setKeyAt(list, 0, 0xB1000000);

    displayList(list);

    HLS_clear(&list, 1);

    displayList(list);

    return 0;
}