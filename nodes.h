#ifndef NODES_H_INCLUDED
#define NODES_H_INCLUDED

typedef enum Node {
    P_DECL,
    P_MOV,
    P_ADD,
    P_SUB,
    P_MUL,
    P_DIV,
    P_MOD,
    P_LHS,
    P_RHS,
    P_AND,
    P_OR,
    P_XOR,
    P_CMP,
    P_INC,
    P_DEC,
    p_BNOT,
    P_LNOT,
    P_PUT,
    P_GET,

    P_BLOCK,
    P_IF,
    P_ELSE,
    P_WHILE,
    P_SWITCH,
    P_CASE,

    P_IDENTIFIER,
    P_NUMBER,
} Node;

typedef struct Number {
    Node type;
    u16 value;
} Number;

typedef struct Identifier {
    Node type;
    i8* data;
    size_t length;
} Identifier;

typedef struct Unary {
    Node type;
    Node* expression;
} Unary;

typedef struct Binary {
    Node type;
    Node* left;
    Node* right;
} Binary;

typedef struct Ternary {
    Node type;
    Node* left;
    Node* middle;
    Node* right;
} Ternary;

#endif // NODES_H_INCLUDED
