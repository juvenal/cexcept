/*===
cexcept: example1.c 2.0.0 (2001-Jul-12-Thu)
Adam M. Costello <amc@cs.berkeley.edu>

An example application that demonstrates how to use version 2.0.* of the
cexcept.h interface.  See README for copyright information.

This application is single-threaded and uses a global exception context.

See example2.c for a demonstration of nested try blocks, avoidance of
global variables by passing the context in function arguments, and the
use of a polymorphic exception type.

===*/


#include <stdio.h>
#include <stdlib.h>


/* The following declarations would normally go in a separate .h file: */

#include "cexcept.h"
define_exception_type(int);
extern struct exception_context the_exception_context[1];

/* End of separate .h file. */


void demo_throw(int fail) {
	fprintf(stderr, "enter demo_throw(%d)\n", fail);
	if (fail) {
		throw 42;
	}
	fprintf(stderr, "return from demo_throw(%d)\n", fail);
}


void foo(int fail) {
	fprintf(stderr, "enter foo(%d)\n", fail);
	demo_throw(fail);
	fprintf(stderr, "return from foo(%d)\n", fail);
}


/* Globally accessible storage for the exception context: */

struct exception_context the_exception_context[1];


int main(int argc, char *argv[]) {
	int e;

	try {
		foo(0);
		foo(1);
		foo(2);
	}
	catch(e)
		fprintf(stderr, "exception %d\n", e);

 	try
		foo(3);

	catch_anonymous
		fprintf(stderr, "anonymous exception\n");

	return EXIT_SUCCESS;
}
