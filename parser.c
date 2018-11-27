#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "misc.h"
#include "nodes.h"

typedef struct Parser {
    i8* begin;
    i8* end;
    void* heap;
    void* heapEnd;
    size_t lineNo;
} Parser;

static void* alloc(Parser* p, size_t size){
    if(p->heap + size > p->heapEnd){
        printf("Error: parser allocator out of memory.\n");
        exit(0xdeadbeef);
    }
    void* tmp = p->heap;
    p->heap += size;
    return tmp;
}

static void* parseIdentifier(Parser* p);

static void skipWhite(Parser* p){
    while(1){
        if(p->begin >= p->end)
            return;
        char* c = p->begin;
        if(*c == ' ' || *c == '\t' || *c == '\v' || *c == '\r')
            p->begin++;
        else if (*c == '\n'){
            p->lineNo++;
            p->begin++;
        }
        else return;
    }
}
static i8 parseChar(Parser* p, i8 c){
    if(p->begin >= p->end)
        return 0;
    if(*(p->begin) == c){
        if(c == '\n')
            p->lineNo++;
        p->begin++;
        return 1;
    }
    return 0;
}
static i8 parseRange(Parser* p, i8 l, i8 u){
    if(p->begin >= p->end)
        return 0;
    if(*(p->begin) >= l && *(p->begin) <= u){
        if(*(p->begin) == '\n')
            p->lineNo++;
        p->begin++;
        return 1;
    }
    return 0;
}
static i8 parseAlphaNumUnder(Parser* p){
    return
        parseRange(p, 'a', 'z') ||
        parseRange(p, 'A', 'Z') ||
        parseRange(p, '0', '9') ||
        parseChar(p, '_');
}
static i8 parseKeyword(Parser* p, i8* c){
    u32 length = strlen(c);
    if(p->begin + length >= p->end)
        return 0;
    u32 lines = 0;
    for(int i = 0; i < length; i++){
        if(p->begin[i] != c[i])
            return 0;
        if(p->begin[i] == '\n')
            lines++;
    }
    i8 tail = p->begin[length];
    if((tail >= 'a' && tail <= 'z') ||
       (tail >= 'A' && tail <= 'Z') ||
       (tail >= '0' && tail <= '9') ||
        tail == '_')
        return 0;
    else {
        p->begin += length;
        p->lineNo += lines;
        return 1;
    }
}
static void* parseNumber(Parser* p){
    Number* result = alloc(p, sizeof(Number));
    result->type = P_NUMBER;
    result->value = (u16)strtol(p->begin, &(p->begin), 10);
    return result;
}
static void* parseIdentifier(Parser* p){
    i8* begin = p->begin;
    u32 length = 0;
    while(parseAlphaNumUnder(p))
        length++;
    Identifier* result = alloc(p, sizeof(Identifier));
    result->type = P_IDENTIFIER;
    result->length = length;
    result->data = begin;
    return result;
}

void* parseStatement(Parser* p){
    if(parseKeyword(p, "var")){
        skipWhite(p);
        Identifier* id = parseIdentifier(p);
        skipWhite(p);
        if(parseChar(p, '=')){
            //Node* right = parseExpression(p);
        }
    }
    return NULL;
}

void* parseMoreStatements(Parser* p){
    Binary* result = parseStatement(p);
    skipWhite(p);
    if(p->begin >= p->end || parseChar(p, '}'))
        return result;
    else {
        Binary* right = parseMoreStatements(p);
        Binary* left = result;
        result = alloc(p, sizeof(Binary));
        result->type = P_BLOCK;
        result->left = (void*)left;
        result->right = (void*)right;
        return result;
    }
}
void* parse(i8* input, i8* end, void* heap, void* heapEnd){
    Parser p = {input, end, heap, heapEnd, 1};

    return parseMoreStatements(&p);
}
