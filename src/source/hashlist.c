#include "../include/hashlist.h"
#include <salvagames/memoryleaks.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct HASHLISTITEM{
    void * value;
    void (*destructor)(void * value);
    unsigned int key;
    int index;
    HashlistItem * next;
} HashlistItem;

HashlistItem * createItem(){
    return malloc(sizeof(HashlistItem));
}

void freeItem(HashlistItem * item, int freeVal){
    if(freeVal) item->destructor(item->value);
    free(item);
}

HashlistItem * getItemIndex(Hashlist list, int index){
    if(index < 0) return NULL;

    HashlistItem * item = list.origin;

    for(int i = 0; i < index; i++){
        item = item->next;
    }

    return item;
}

HashlistItem * getItemKey(Hashlist list, unsigned int key){
    HashlistItem * item = list.origin;
    HashlistItem * o = NULL;

    for(int i = 0; i < list.length; i++){
        if(key == item->key){
            o = item;
            break;
        }
        else{
            item = item->next;
        }
    }

    return o;
}

int checkIfIndexInRange(int len, int index){
    return index >= 0 && index < len;
}

void updateIndexes(Hashlist list){
    HashlistItem * item = list.origin;

    for(int i = 0; i < list.length; i++){
        item->index = i;
        item = item->next;
    }
}

Hashlist HLS_createList(void){
    return (Hashlist){
        NULL, 0
    };
}

void HLS_add(Hashlist * Hashlist, unsigned int key, void * value, void (*destructor)(void * value)){
    if(!Hashlist){
        printf("Hashlist (add()): Target Hashlist cannot be NULL.\n");
        return;
    }

    if(!value){
        printf("Hashlist (add()): Value cannot be NULL.\n");
        return;
    }

    if(!destructor){
        printf("Hashlist (add()): Destructor cannot be NULL.\n");
        return;
    }

    if(getItemKey(*Hashlist, key)){
        printf("Hashlist (add()): Key already exists.\n");
        return;
    }

    HashlistItem * item = getItemIndex(*Hashlist, Hashlist->length - 1);
    
    HashlistItem * newItem = createItem();
    newItem->value = value;
    newItem->destructor = destructor;
    newItem->key = key;
    newItem->index = Hashlist->length;
    newItem->next = NULL;

    if(!item){
        Hashlist->origin = newItem;
    }
    else{
        item->next = newItem;
    }

    Hashlist->length++;
}

void HLS_addAt(Hashlist * Hashlist, int index, unsigned int key, void * value, void (*destructor)(void * value)){
    if(!Hashlist){
        printf("Hashlist (addAt()): Target Hashlist cannot be NULL.\n");
        return;
    }

    if(!value){
        printf("Hashlist (addAt()): Value cannot be NULL.\n");
        return;
    }

    if(!destructor){
        printf("Hashlist (addAt()): Destructor cannot be NULL.\n");
        return;
    }

    if(getItemKey(*Hashlist, key)){
        printf("Hashlist (addAt()): Key already exists.\n");
        return;
    }

    if(!checkIfIndexInRange(Hashlist->length + 1, index)){
        printf("Hashlist (addAt()): Invalid index.\n");
        return;
    }

    HashlistItem * newItem = createItem();
    newItem->value = value;
    newItem->destructor = destructor;
    newItem->key = key;
    newItem->index = index;
    newItem->next = NULL;

    if(index == Hashlist->length){
        HashlistItem * item = getItemIndex(*Hashlist, index);
        item->next = newItem;
    }
    else{
        HashlistItem * prev = getItemIndex(*Hashlist, index - 1);

        if(!prev){
            HashlistItem * next = Hashlist->origin;
            Hashlist->origin = newItem;
            newItem->next = next;
        }
        else{
            HashlistItem * next = prev->next;
            prev->next = newItem;
            newItem->next = next;
        }
    }
    
    Hashlist->length++;

    updateIndexes(*Hashlist);
}

void HLS_remove(Hashlist * Hashlist, unsigned int key, int freeVal){
    if(!Hashlist){
        printf("Hashlist (remove()): Target Hashlist cannot be NULL.\n");
        return;
    }

    HashlistItem * item = getItemKey(*Hashlist, key);
    if(!item) return;

    HashlistItem * prev = getItemIndex(*Hashlist, item->index - 1);
    HashlistItem * next = item->next;

    if(!prev){
        Hashlist->origin = next;
    }
    else{
        prev->next = next;
    }

    freeItem(item, freeVal);
    Hashlist->length--;
    
    updateIndexes(*Hashlist);
}

void HLS_removeAt(Hashlist * Hashlist, int index, int freeVal){
    if(!Hashlist){
        printf("Hashlist (removeAt()): Target Hashlist cannot be NULL.\n");
        return;
    }

    if(!checkIfIndexInRange(Hashlist->length, index)){
        printf("Hashlist (removeAt()): Invalid index.\n");
        return;
    }

    HashlistItem * item = getItemIndex(*Hashlist, index);
    HashlistItem * prev = getItemIndex(*Hashlist, index - 1);
    HashlistItem * next = item->next;

    if(!prev){
        Hashlist->origin = next;
    }
    else{
        prev->next = next;
    }

    freeItem(item, freeVal);
    Hashlist->length--;
    
    updateIndexes(*Hashlist);
}

void HLS_set(Hashlist Hashlist, unsigned int key, void * newValue, void (*destructor)(void * newValue), int freeOldVal){
    if(!newValue){
        printf("Hashlist (set()): New value cannot be NULL.\n");
        return;
    }

    if(!destructor){
        printf("Hashlist (set()): Destructor cannot be NULL.\n");
        return;
    }

    HashlistItem * item = getItemKey(Hashlist, key);

    if(item != NULL){
        if(freeOldVal) item->destructor(item->value);
        item->value = newValue;
        item->destructor = destructor;
    }
}

void HLS_setAt(Hashlist Hashlist, int index, void * newValue, void (*destructor)(void * newValue), int freeOldVal){
    if(!newValue){
        printf("Hashlist (setAt()): New value cannot be NULL.\n");
        return;
    }

    if(!destructor){
        printf("Hashlist (setAt()): Destructor cannot be NULL.\n");
        return;
    }

    if(!checkIfIndexInRange(Hashlist.length, index)){
        printf("Hashlist (setAt()): Invalid index.\n");
        return;
    }

    HashlistItem * item = getItemIndex(Hashlist, index);

    if(freeOldVal) item->destructor(item->value);
    item->value = newValue;
    item->destructor = destructor;
}

void HLS_setKey(Hashlist Hashlist, unsigned int key, unsigned int newKey){
    if(getItemKey(Hashlist, newKey)){
        printf("Hashlist (setKey()): New key already exists.\n");
        return;
    }
    
    HashlistItem * item = getItemKey(Hashlist, key);
    if(item != NULL) item->key = newKey;
}

void HLS_setKeyAt(Hashlist Hashlist, int index, unsigned int newKey){
    if(!checkIfIndexInRange(Hashlist.length, index)){
        printf("Hashlist (setKeyAt()): Invalid index.\n");
        return;
    }

    if(getItemKey(Hashlist, newKey)){
        printf("Hashlist (setKeyAt()): New key already exists.\n");
        return;
    }

    HashlistItem * item = getItemIndex(Hashlist, index);
    item->key = newKey;
}

void * HLS_get(Hashlist Hashlist, unsigned int key){
    HashlistItem * item = getItemKey(Hashlist, key);
    return !item ? NULL : item->value;
}

int HLS_getIndex(Hashlist Hashlist, unsigned int key){
    HashlistItem * item = getItemKey(Hashlist, key);
    return !item ? -1 : item->index;
}

void * HLS_getByIndex(Hashlist Hashlist, int index){
    if(!checkIfIndexInRange(Hashlist.length, index)){
        printf("Hashlist (getByIndex()): Invalid index.\n");
        return NULL;
    }

    return getItemIndex(Hashlist, index)->value;
}

unsigned int HLS_getKey(Hashlist Hashlist, int index){
    if(!checkIfIndexInRange(Hashlist.length, index)){
        printf("Hashlist (getKey()): Invalid index.\n");
        return 0;
    }

    return getItemIndex(Hashlist, index)->key;
}

void HLS_clear(Hashlist * Hashlist, int freeVal){
    if(!Hashlist){
        printf("Hashlist (clearList()): Target Hashlist cannot be NULL.\n");
        return;
    }

    HashlistItem * item = Hashlist->origin;

    for(int i = 0; i < Hashlist->length; i++){
        HashlistItem * nextItem = item->next;
        freeItem(item, freeVal);
        item = nextItem;
    }

    Hashlist->length = 0;
    Hashlist->origin = NULL;
}