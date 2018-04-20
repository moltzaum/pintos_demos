#include <stdio.h>
#include <string.h>
#include "static.h"
#include "foo.h"

STATIC {
	printf ("Static block from main\n");
}

STATIC {
	printf ("Static block from main #2\n");
}

int main () {
	printf ("%s\n%d\n%s\n%s\n%s", __FILE__, __LINE__, __DATE__, __TIME__, __TIMESTAMP__);
}

STATIC {
	printf ("Static block from main #3\n");
}