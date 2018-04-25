#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

#define CHAR_DEMO
#define ADDR_DEMO
#define PRINT_DUMP

/* These PUSH and POP macros are designed to work with any data. If you are using a
 * rvalue, then you either have to create an explicit variable, or pass its datatype to
 * the push function. It is expected that when calling this macro, esp is in scope and
 * is of type *uint8_t. It may be a pointer to something else, but then its behavior is
 * undefined. PUSH_2 is used to convert rvalues to lvalues. If you are using an lvalue,
 * specifying the type of the value you want to push has no effect, unless you accidentally
 * mention the wrong type.
 *
 * The correct push will be called depending on the amount of arguments you provide.
 * Since it isn't shown below, the correct usage for the second push is as follows: 
 * PUSH (uint64_t, 0);
 *
 * This is equivalent to doing:
 * uint64_t tmp = 0;
 * PUSH (tmp);
 *
 * 
 * MACRO SAFETY:
 * It is safe to use these macros in a single-line if statement or while loop.
 * The macro is an if statement itself, so you can't assign to it or have it
 * assign to anything. You also can't use it in an expression.
 */

/* Reads data into val. Amount read
 * depends on the size of val. */
#define POP(val) if (1) {                \
    memcpy (&val, esp, sizeof(val));     \
    esp += sizeof(val);                  \
    } else (void) 0

/* Standard PUSH. Does not work for
 * rvalues. Dependent on size. */
#define PUSH_1(val)    if (1) {          \
    esp -= sizeof(val);                  \
    memcpy (esp, &val, sizeof(val));     \
    } else (void) 0

/* Turns an rvalue into an lvalue by
 * creating a variable. */
#define PUSH_2(T, val) if (1) {          \
    T tmp = val;                         \
    esp -= sizeof(tmp);                  \
    memcpy (esp, &tmp, sizeof(tmp));     \
    } else (void) 0

#define PEEK(val)                        \
    memcpy (&val, esp, sizeof(val))      \
    

#define FIND_PUSH(A, B, FUNC, ...) FUNC
#define PUSH(...)                 \
    FIND_PUSH(__VA_ARGS__,        \
        PUSH_2(__VA_ARGS__),      \
        PUSH_1(__VA_ARGS__))

int main () {
    
    int argc = 5;
    char *argv[5] = {"echo", "kitty", "makes", "me", "smitty"};
    printf ("Printing Arguments:\n");
    for (int i = 0; i < argc; i++) {
        printf ("%d: [%s]\n", i,  argv[i]);
    }
    
    uint8_t *esp = malloc (1024);
    uint8_t *top = esp;
    uint8_t *max_esp;
    char *str;
    char *addr;
  
  /* Demonstrates PUSH and POP for regular character data. You can use any data type,
   * and the stack should copy it. Pushing pointers (strings) are demonstrated below.
   * Structs can also be pushed. */
  #ifdef CHAR_DEMO
      
    printf ("\nPushing a normal char data onto the stack DEMO\n");
    printf ("Stack pointer: %p\n", esp);
    printf ("PUSHING\n");
    str = argv[0];
    for (int i = 0; i < strlen(str); i++) {
        PUSH (str[i]);
        printf ("%p\t%c\n", esp, str[i]);
    }
    max_esp = esp;
    
    printf ("\nStack pointer: %p\n", esp);
    printf ("Now POPPING\n");
    char c;
    for (int i = 0; i < strlen(str); i++) {
        POP (c);
        printf ("%p\t%c\n", esp - 1, c);
    }
    
  #endif
    
   /* Pushing Addresses:
    * Pushing addresses is the same as pushing any other data type, however note that you
    * can't push an rvalue (this was a problem I was creating for myself when trying to
    * push addresses of an rvalue). You will either need to explicitly put your pointer
    * into a variable, or pass the type along with the address so that the macro can put
    * it into an lvalue itself. While messing with this, I found you can cast pointers to
    * uint32_t or uint64_t depending on your system architecture. I wouldn't recommend
    * doing that though, as casting creates rvalues and casting back is a pain. */
  #ifdef ADDR_DEMO
      
    printf ("\nPushing an address onto the stack DEMO\n");
    printf ("Stack pointer: %p\n", esp);
    printf ("PUSHING\n");
    for (int i = 0; i < argc; i++) {
        PUSH (argv[i]);
        printf ("%p\t%p\t%s\n", esp, argv[i], argv[i]);
    }
    if (max_esp > esp) {
        max_esp = esp;
    }
    
    printf ("\nStack pointer: %p\n", esp);
    printf ("Now POPPING\n");
    for (int i = 0; i < argc; i++) {
        POP (addr);
        printf ("%p\t%p\t%s\n", esp - 8, addr, addr);
    }
    
  #endif
  
    /* Dumps everything I want to know about the stack into the console. */
  #ifdef PRINT_DUMP
    str = NULL;
    uint64_t diff = (uint64_t) top - (uint64_t) max_esp;
    esp = top;
    printf ("\nAddress        Hex    Dec    Char\n");
    for (int i = 0; i <= diff; i++) {
        
        if (i != 0 && i % sizeof(uint64_t) == 0) {
            
            memcpy (&addr, &esp[-i], sizeof(addr));
            str = (char*) addr;
            
            printf ("%p \t0x%02x \t%d \t%c\t%p\t%s\n\n",
                &esp[-i], esp[-i], esp[-i], esp[-i], (char*) addr, str);
        } else {
            printf ("%p \t0x%02x \t%d \t%c \n", &esp[-i], esp[-i], esp[-i], esp[-i]);
        }
    }
  
  #endif
  
    free (top);
}


