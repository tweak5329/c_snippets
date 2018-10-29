#pragma once


#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>


typedef void (*llist_free_func)(void *);
typedef void (*llist_print_func)(void *);
typedef bool (*llist_cmp_func)(void *, void *);


typedef struct llist_elem_s {

    void *data;
    struct llist_elem_s *next;

} llist_elem_t;


typedef struct llist_s {

    llist_elem_t *first;
    int           length;
    llist_free_func free_func;

} llist_t;


// LList creation / deletion
llist_t *llist_new(llist_free_func fn);
llist_elem_t *llist_newElem(void *data);                  // static
void llist_freeElem(llist_elem_t *e, llist_free_func fn); // static
void llist_free(llist_t *li);

// Add / remove element
void llist_add(llist_t *li, void *val);
//void llist_push(llist_t *li, void *val); // = add ?
//void *llist_pop(llist_t *li);
void llist_insertAt(llist_t *li, void *val, int pos);

// Get / find element
void *llist_get(llist_t *li, int pos);
int llist_find(llist_t *li, void *val);
int llist_findCmp(llist_t *li, void *val, llist_cmp_func fn);

// LList iteration

// Utilities
void llist_print(llist_t *li, llist_print_func fn);
void llist_print_int(void *data);
