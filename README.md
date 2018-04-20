## c demos for pintos

PintOS is a pint-sized operating system made for students to learn about operating systems concepts.

When writing pintos code, it was sometimes helpful to write demos to show functionality in a smaller code space.

It is sufficient to compile each test with `gcc *.c`. To get an understanding of what each demo does, check out the appropiate `main.c` file.

#### Hash Key Demo

Most of the files in the `hash_key_demo` folder are from the pintos kernel library. I had to change some stuff to get it to work since pintos has its own version of c.

`keyed_hash` is a file that only follows the api for the main pintos hash. It uses casting magic and simplifies the pintos hash api.

#### Stack Demo

This was my first introduction to both memcpy and writing macros. The `PUSH` and `POP` macros are designed to work with data of any size.

#### Static Block Demo

I wasn't able to get static blocks working in pintos, nor did it make the most sense to. However, I spent a lot of time trying to figure out how, and I think the way I did it was pretty cool.