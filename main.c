#include <stdio.h>
#include <malloc.h>
#include <string.h>


typedef struct ListItemStruct {
    struct ListItemStruct* previous;
    char* value;
    struct  ListItemStruct* next;
} ListItem;

typedef struct ListStruct {
    ListItem* head;
    ListItem* tail;
} List;

ListItem* makeListItem() {
    ListItem* newListItem = (ListItem*) malloc(sizeof(ListItem));
    newListItem->previous = NULL;
    newListItem->value = NULL;
    newListItem->next = NULL;

    return newListItem;
}

ListItem* makeListItemWithValue(char* string) {
    ListItem* newListItem = (ListItem*) malloc(sizeof(ListItem));
    newListItem->previous = NULL;
    newListItem->value = string;
    newListItem->next = NULL;

    return newListItem;
}

List* makeList() {
    List* newList = (List*) malloc(sizeof(List));
    newList->head = makeListItem();
    newList->tail = newList->head;
    return newList;
}

void printList(List* list) {
    ListItem* currentItem = list->head;

    while (currentItem->next) {
        printf("%s\n", currentItem->value);
        currentItem = currentItem->next;
    }
    printf("%s\n\n", currentItem->value);
}

void insertAfter(List* list, ListItem* currentItem, ListItem* newListItem) {
    if(list->tail == currentItem) {
        currentItem->next = newListItem;
        newListItem->previous = currentItem;
        list->tail = newListItem;
        return;
    }

    //                       <----------
    // Insert new one [Curr] <- [NEW] -> [next]
    //                       ---------->
    newListItem->previous = currentItem;
    newListItem->next = currentItem->next;

    // Point next to new one [Curr] <- [NEW] <-> [next]
    //                              ----------->
    newListItem->next->previous = newListItem;

    // Point previous to new one [Curr] <-> [NEW] <-> [next]
    currentItem->next = newListItem;
}

void appendToList(List* list, ListItem* listItem) {
    insertAfter(list, list->tail, listItem);
}

void insertBefore(List* list, ListItem* currentItem, ListItem* newListItem) {
    if(list->head == currentItem) {
        currentItem->previous = newListItem;
        newListItem->next = currentItem;
        list->head = newListItem;
        return;
    }

    //                       <----------
    // Insert new one [Prev] <- [NEW] -> [Curr]
    //                       ---------->
    newListItem->next = currentItem;
    newListItem->previous = currentItem->previous;

    // Point next to new one [Prev] <- [NEW] <-> [Curr]
    //                              ----------->
    newListItem->previous->next = newListItem;

    // Point previous to new one [Prev] <-> [NEW] <-> [Curr]
    currentItem->previous = newListItem;
}

void prependToList(List* list, ListItem* listItem) {
    insertBefore(list, list->head, listItem);
}



void destroyList(List* list) {
    ListItem* currentItem = list->head;

    while (currentItem->next) {
        currentItem = currentItem->next;
        free(currentItem->previous->value);
        free(currentItem->previous);
    }

    free(currentItem->value);
    free(currentItem);
}

char* makeCopy(char* orig) {
    char* result;
    result = (char*) malloc(strlen(orig) + 1);

    strcpy(result, orig);

    return result;
}

int main() {
    List* list = makeList();
    list->head->value = makeCopy("Init");
    printList(list);

    appendToList(list, makeListItemWithValue(makeCopy("Appended")));
    printList(list);

    appendToList(list, makeListItemWithValue(makeCopy("Appended")));
    printList(list);

    insertAfter(list, list->head, makeListItemWithValue(makeCopy("InsertAfter")));
    printList(list);

    prependToList(list, makeListItemWithValue(makeCopy("Prepended")));
    printList(list);

    destroyList(list);

    return 0;
}

