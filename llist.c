#include "llist.h"

llist_t *llist_new(llist_free_func fn) {

    llist_t *li = NULL;

    li = malloc(sizeof *li);
    if (li == NULL) {
	printf("Error malloc llist\n");
	exit(EXIT_FAILURE);
    }

    li->first = NULL;
    li->length=0;
    li->free_func = fn;
    return li;
}


llist_elem_t *llist_newElem(void *data) {

    llist_elem_t *e = NULL;
    e = malloc(sizeof *e);
    if (e == NULL) {
	printf("Error malloc llist_elem\n");
	exit(EXIT_FAILURE);
    }

    e->data = data;
    e->next = NULL;
    return e;
}


void llist_freeElem(llist_elem_t *e, llist_free_func fn) {

    if (fn != NULL)
	fn(e->data);
    free(e);
}


void llist_free(llist_t *li) {

    if (li != NULL) {

	llist_elem_t *curr = li->first;
	llist_elem_t *next;
	while (curr != NULL) {
	    next = curr->next;
	    llist_freeElem(curr, li->free_func);
	    curr = next;
	}

	free(li);
    }
}



void llist_add(llist_t *li, void *val) {

    if (li != NULL) {

	llist_elem_t *new = llist_newElem(val);

	/* empty list, simply update first element */
	if (li->first == NULL) {
	    li->first = new;
	}
	else {
	    /* move to the end of list, add element */
	    llist_elem_t *tmp = li->first;
	    while (tmp->next != NULL)
		tmp = tmp->next;
	    tmp->next = new;
	}

	li->length++;
    }
}


void llist_insertAt(llist_t *li, void *val, int pos) {

    llist_elem_t *e = llist_newElem(val);

    if (pos == 0) {
	e->next = li->first;
	li->first = e;
    }

    else if (pos > 0 && pos <= li->length) {

	llist_elem_t *tmp = li->first;
	for (unsigned int i=0; i<(pos-1); i++) {
	    tmp = tmp->next;
	}

	e->next = tmp->next;
	tmp->next = e;
    }

    li->length++;
}


void *llist_get(llist_t *li, int pos) {

    if (li == NULL || pos > (li->length - 1) || pos < 0)
	return NULL;

    /* loop up to pos and return data */
    llist_elem_t *r = li->first;
    for (unsigned int i=0; i<pos; i++) {
	r = r->next;
	if (r == NULL)
	    return NULL;
    }
    return r->data;
}


int llist_find(llist_t *li, void *val) {

    int index = 0;

    llist_elem_t *tmp = li->first;
    while (tmp != NULL) {
	if (tmp->data == val)
	    return index;
	tmp = tmp->next;
	index++;
    }
    return -1;
}

int llist_findCmp(llist_t *li, void *val, llist_cmp_func fn) {

    int index = 0;

    llist_elem_t *tmp = li->first;
    while (tmp != NULL) {
	if (fn(tmp->data, val))
	    return index;
	tmp = tmp->next;
	index++;
    }
    return -1;
}


void llist_print(llist_t *li, llist_print_func fn) {

    if (li != NULL) {

	llist_elem_t *tmp = li->first;
	while (tmp != NULL) {
	    fn(tmp->data);
	    if (tmp->next != NULL) {
		printf(", ");
		fflush(stdin);
	    }
	    tmp = tmp->next;
	}
	printf("\n");
    }
}


void llist_print_int(void *data) {
    printf("%d", (int) data);
    fflush(stdin);
}
