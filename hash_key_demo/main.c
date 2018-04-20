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
	
	/*
	//List demo
	struct list l;
	list_init (&l);
	
	struct thread *t;
	init_thread (&t, "Matthew");
	list_push_back (&l, &t->elem_l);
	
	init_thread (&t, "Michael");
	list_push_back (&l, &t->elem_l);
	
	//Iterate list
	struct list_elem *e;
	for (e = list_begin (&l); e != list_end (&l); e = list_next (e)) {
		struct thread *te = list_entry (e, struct thread, elem_l);
		printf ("%s %d\n", te->name, te->tid);
	} */
	
	//Hash demo
	struct hash h;
	init_keyed_hash (h);
	
	struct thread *t;
	init_thread (&t, "Annie");
	hash_insert (&h, &t->elem_h);
	
	init_thread (&t, "Brian");
	hash_insert (&h, &t->elem_h);
	
	init_thread (&t, "Charlie");
	hash_insert (&h, &t->elem_h);
	
	//Pull out one item from list using key
	struct hash_elem *e = hash_lookup_key (&h, 1);
	t = hash_entry (e, struct thread, elem_h);
	
	printf ("%s has a tid of %d\n", t->name, t->tid);
	
}
