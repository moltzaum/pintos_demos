#include "list.h"
#include "hash.h"
#include "keyed_hash.h"
#include <stdio.h>
#include <stdlib.h>

static int next_tid = 0;

int get_tid() {
	return next_tid++;
}

struct thread {
	int tid;
	struct hash_elem elem_h;
	char* name;
	struct list_elem elem_l;
};

void init_thread (struct thread **t, char* name) {
	*t = malloc (sizeof (struct thread));
	(*t)->name = name;
	(*t)->tid = get_tid();
}

struct page {
    void* uaddr;
    struct hash_elem elem_h;
    char* data;
};

void init_page (struct page **p, char* name) {
    *p = malloc (sizeof (struct page));
    (*p)->uaddr = name;
    (*p)->data = name;
}

/*	
	This is a quick demo with a spoof thread struct. The important thing to know
	about the thread struct is that it should look like this:
	
	struct thread {
		int tid;
		struct hash_elem elem_h;
		...
	}
	
	This may work for us a little bit, but it is important to note that we would be
	unable to have a thread be a part of two different keyed hash tables. The
	limitation exists because `hash_key_less` requires `elem` from a `hash_key`.
*/

int main() {
	
	//Hash demo
	struct hash h;
	init_keyed_hash (h);
	
	char* a = "Annie";
	char* b = "Brian";
	char* c = "Charlie";
	
	struct page *p;
	init_page (&p, a);
	hash_insert (&h, &p->elem_h);
	
	init_page (&p, b);
	hash_insert (&h, &p->elem_h);
	
	init_page (&p, c);
	hash_insert (&h, &p->elem_h);
	
	//Pull out one item from list using key
	struct hash_elem *e = hash_lookup_key (&h, (int) a);
	p = hash_entry (e, struct page, elem_h);
	
	printf ("%s has a key of %p\n", p->data, p->uaddr);
	
}
