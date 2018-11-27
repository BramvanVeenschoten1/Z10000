#include <stdio.h>
#include <stdlib.h>
#include "ops.h"
#include "misc.h"

u16 hello [] = {
    // offset to string data
    PUSH, 21,
    //string length
    PUSH, 13,
    // condition
    LREAD, 1,
    LNOT,
    JMPIF, 22,

    // putchar
    LREAD, 2,
    SRET, // we use offset from current instruction
    ADD,
    PREAD,
    PUT, // putchar
    POP,
    POP,

    // inc ptr
    LREAD, 2,
    INC,
    LWRITE, 2,
    POP,

    // dec len
    LREAD, 1,
    DEC,
    LWRITE, 1,
    POP,

    // back to condition
    JMP, -27,

    HALT,
    'H', 'e', 'l', 'l', 'o', ' ', 'W', 'o', 'r', 'l', 'd', '!', '\n',
};

int main()
{
    execute(hello, sizeof(hello));
    return 0;
}
