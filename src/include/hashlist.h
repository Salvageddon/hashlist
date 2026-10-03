#pragma once

typedef struct HASHLISTITEM HashlistItem;

typedef struct{
    HashlistItem * origin; //first item on the hashlist
    int length; //item count of the hashlist
} Hashlist;

/*
    Initialize hashlist
*/
Hashlist HLS_createList(void);

/*
    Add item to a hashlist at the end of it
    \param Hashlist target hashlist
    \param key key of the new item
    \param value object to be added of any type
    \param destructor destructor of added object
*/
void HLS_add(Hashlist * Hashlist, unsigned int key, void * value, void (*destructor)(void * value));

/*
    Add item to a hashlist at specified index
    \param Hashlist target hashlist
    \param index position on the hashlist to be added at
    \param key key of the new item
    \param value object to be added of any type
    \param destructor destructor of added object
*/
void HLS_addAt(Hashlist * Hashlist, int index, unsigned int key, void * value, void (*destructor)(void * value));

/*
    Remove item by key
    \param Hashlist target hashlist
    \param key key of the item to be removed
    \param freeValue pass 1 if you want to invoke the destructor. Otherwise pass 0, but be ware of mem leaks.
*/
void HLS_remove(Hashlist * Hashlist, unsigned int key, int freeVal);

/*
    Remove item from specified index
    \param Hashlist target hashlist
    \param index position on the hashlist to be removed
    \param freeValue pass 1 if you want to invoke the destructor. Otherwise pass 0, but be ware of mem leaks.
*/
void HLS_removeAt(Hashlist * Hashlist, int index, int freeVal);

/*
    Set an item at specified position on the hashlist
    \param Hashlist target hashlist
    \param key key of the element to be changed. This will not change with the item.
    \param newValue object to be added of any type
    \param destructor destructor of added object
    \param freeOldValue pass 1 if you want to invoke the old value destructor. Otherwise pass 0, but be ware of mem leaks.
*/
void HLS_set(Hashlist Hashlist, unsigned int key, void * newValue, void (*destructor)(void * newValue), int freeOldVal);

/*
    Set an item at specified position on the hashlist
    \param Hashlist target hashlist
    \param index position on the hashlist to be changed
    \param newValue object to be added of any type
    \param destructor destructor of added object
    \param freeOldValue pass 1 if you want to invoke the old value destructor. Otherwise pass 0, but be ware of mem leaks.
*/
void HLS_setAt(Hashlist Hashlist, int index, void * newValue, void (*destructor)(void * newValue), int freeOldVal);

/*
    Switch an item key
    \param Hashlist target hashlist
    \param key Old key of the item to find to be changed
    \param newKey New key value
*/
void HLS_setKey(Hashlist Hashlist, unsigned int key, unsigned int newKey);

/*
    Switch an item key at specified index
    \param Hashlist target hashlist
    \param index position on the hashlist to have keys changed
    \param key New key value
*/
void HLS_setKeyAt(Hashlist Hashlist, int index, unsigned int key);

/*
    Return item by specified key
    \param Hashlist target list
    \param key key of the item to be returned
*/
void * HLS_get(Hashlist Hashlist, unsigned int key);

/*
    Return index by specified key
    \param Hashlist target list
    \param key key of the index to be returned
*/
int HLS_getIndex(Hashlist Hashlist, unsigned int key);

/*
    Return item from specified index
    \param Hashlist target list
    \param index position on the list to be returned
*/
void * HLS_getByIndex(Hashlist Hashlist, int index);

/*
    Return key from specified index
    \param Hashlist target list
    \param index position of the key to be returned
*/
unsigned int HLS_getKey(Hashlist Hashlist, int index);

/*
    Clear the hashlist
    \param Hashlist target hashlist
    \param freeValue pass 1 if you want to invoke the destructors. Otherwise pass 0, but be ware of mem leaks.
*/
void HLS_clear(Hashlist * Hashlist, int freeVal);