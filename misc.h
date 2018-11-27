#ifndef MISC_H_INCLUDED
#define MISC_H_INCLUDED

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long u32;
typedef unsigned long long u64;
typedef char i8;
typedef short i16;
typedef long i32;
typedef long long i64;

void* parse(i8*,i8*,void*,void*);
void execute(u16* code, u16 length);

#endif // MISC_H_INCLUDED
