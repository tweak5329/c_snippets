#include <stdlib.h>
#include <stdio.h>

#include "llist.h"


bool my_cmp(void *a, void *b) {
    if (((int) a) > (int) b)
	return true;
    else
	return false;
}

typedef struct foo_s {
    int *x;
    int l;
} foo_t;


void my_free(void *foo) {
    free(((foo_t *) foo)->x);
}


foo_t *newFoo(int nb, int base) {

    foo_t *f = NULL;
    f = malloc(sizeof *f);
    if (f == NULL) {
	printf("Error malloc foo\n");
    }

    f->x = malloc(nb * sizeof(int));
    for (unsigned int i=0; i < nb; i++)
	f->x[i] = base+i;
    f->l = nb;

    return f;
}


void print_foo(void *f) {

    foo_t *d = (foo_t*) f;
    for(unsigned int i = 0; i < d->l; i++)
	printf("%d ", d->x[i]);
}


int main(int argc, char *argv[]) {

    printf("Testing linked lists...\n");

    llist_t *li = llist_new(NULL);

    llist_add(li, (void*)3);
    llist_add(li, (void*)6);
    llist_add(li, (void*)1);
    llist_add(li, (void*)209);
    llist_print(li, &llist_print_int);
    llist_insertAt(li, (void*)7, 0);
    llist_print(li, &llist_print_int);

    foo_t *r = llist_get(li, 0);
    foo_t *s = llist_get(li, 2);
    printf("li[0] = %d\n", (int) r);
    printf("li[2] = %d\n", (int) s);
    printf("index of 6: %d\n", llist_find(li, (void*)205));
    printf("index of >10: %d\n", llist_findCmp(li, (void*)10, &my_cmp));
    llist_free(li);

    llist_t *la = llist_new(&my_free);

    foo_t *f = newFoo(5, -1);
    llist_add(la, f);

    f = newFoo(10, 42);
    llist_add(la, f);

    f = newFoo(4, 238);
    llist_add(la, f);

    llist_print(la, &print_foo);
    llist_free(la);

    return EXIT_SUCCESS;
}
