#ifndef OPS_H_INCLUDED
#define OPS_H_INCLUDED

enum Operation {
    HALT,
    JMPIF,
    JMP,
    SRET,
    RET,
    PUSH,
    LREAD,
    LWRITE,
    PREAD,
    PWRITE,
    LEA,
    ADD,
    SUB,
    MUL,
    DIV,
    MOD,
    LSH,
    RSH,
    AND,
    OR,
    XOR,
    LESS,
    INC,
    DEC,
    BNOT,
    LNOT,
    PUT,
    GET,
    POP,
};

#endif // OPS_H_INCLUDED
