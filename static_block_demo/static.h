#include <stdio.h>

#ifndef STATIC_BLOCK_H
#define STATIC_BLOCK_H

//This link was helpful when trying to figure out how to use __COUNTER__ to create a new function.
//https://stackoverflow.com/questions/652815/has-anyone-ever-had-a-use-for-the-counter-pre-processor-macro

/* This is a static block implementation in c. It works primarily using the predefined
 * macro __COUNTER__ which is NOT a part of the c standard, though it is relatively
 * common (supported by Intel, GCC, Clang and MSVC). The static block implementation
 * also uses __attribute__ ((constructor)), which as far as I can tell is standard c.
 * The constructor just gives whatever function it is attached to the guarantee to run
 * before main.
 * 
 * It is necessary to have levels of indirection for the paste macro, otherwise the result
 * of the concatenation would be "static_magic___COUNTER_" instead of actually evaluating
 * __COUNTER__.
 * 
 * I considered trying to make use of __FILE__, __LINE__, __DATE__, or __TIME__ since I
 * found them before __COUNTER__ (as they are standard), but they are either not unique
 * enough, or do not work well for function names.
 */

//I haven't actually been able to test this, but it should theoretically work.
//I think an error would occur without this check, but maybe it would be more readable?
#ifndef __COUNTER__
#error __COUNTER__ is not supported by your compiler.
#endif

//pastes tokens literally, so b should be evaluated at this point
#define CONCAT_PARAMETERIZED(a, b) a##b

//b is __COUNTER__, which becomes evaluated calling the next macro
#define CONCAT_MACRO_CONSTANT(a, b) CONCAT_PARAMETERIZED(a, b)

#define STATIC __attribute__ ((constructor)) \
	void CONCAT_MACRO_CONSTANT(static_magic_, __COUNTER__)()

//This is the first solution I had to create unique static blocks:
//#define STATIC(name) __attribute__ ((constructor)) void static_magic_##name()

#endif
