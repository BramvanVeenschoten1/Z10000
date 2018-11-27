#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "ops.h"
#include "misc.h"

void execute(u16* code, u16 length){
    u16 state [0x10000];
    memcpy(&state[2], code, length);
    state[0] = length + 2;
    state[1] = 2;
    while(state[state[1]]){
        {
            for(int i = length + 2; i < state[0]; i++){
                printf("%X, ", state[i]);
            }
            putchar('\n');
        }
        switch(state[state[1]]){
            case JMPIF: {
                state[1]++;
                state[0]--;
                u16 offset = state[state[1]];
                if(state[state[0]])
                    state[1] += offset;
                break;
            }
            case JMP: {
                state[1]++;
                u16 offset = state[state[1]];
                state[1] += offset;
                break;
            }
            case SRET: {
                state[state[0]] = state[1];
                state[0]++;
                break;
            }
            case RET: {
                state[0]--;
                state[1] = state[state[0]];
                break;
            }
            case PUSH: {
                state[1]++;
                state[state[0]] = state[state[1]];
                state[0]++;
                break;
            }
            case LREAD:{
                state[1]++;
                u16 offset = state[state[1]];
                state[state[0]] = state[state[0] - offset];
                state[0]++;
                break;
            }
            case LWRITE:{
                state[1]++;
                u16 offset = state[state[1]];
                state[state[0] - offset - 1] = state[state[0] - 1];
                break;
            }
            case PREAD: {
                state[state[0]] = state[state[state[0] - 1]];
                state[0]++;
                break;
            }
            case PWRITE: {
                state[0]--;
                state[state[state[0] - 1]] = state[state[0]];
                break;
            }
            case LEA: {
                state[1]++;
                u16 offset = state[state[1]];
                state[state[0]] = state[0] - offset;
                state[0]++;
                break;
            }
            case ADD:  state[0]--; state[state[0] - 1] +=  state[state[0]]; break;
            case SUB:  state[0]--; state[state[0] - 1] -=  state[state[0]]; break;
            case MUL:  state[0]--; state[state[0] - 1] *=  state[state[0]]; break;
            case DIV:  state[0]--; state[state[0] - 1] /=  state[state[0]]; break;
            case MOD:  state[0]--; state[state[0] - 1] %=  state[state[0]]; break;
            case LSH:  state[0]--; state[state[0] - 1] <<= state[state[0]]; break;
            case RSH:  state[0]--; state[state[0] - 1] >>= state[state[0]]; break;
            case AND:  state[0]--; state[state[0] - 1] &=  state[state[0]]; break;
            case OR:   state[0]--; state[state[0] - 1] |=  state[state[0]]; break;
            case XOR:  state[0]--; state[state[0] - 1] ^=  state[state[0]]; break;
            case LESS: state[0]--; state[state[0] - 1] =
                       (state[state[0] - 1] < state[state[0]]);             break;
            case INC:  state[state[0] - 1]++;                               break;
            case DEC:  state[state[0] - 1]--;                               break;
            case BNOT: state[state[0] - 1] = ~state[state[0] - 1];          break;
            case LNOT: state[state[0] - 1] = !state[state[0] - 1];          break;
            case PUT:  putchar(state[state[0] - 1]);                        break;
            case GET:  state[state[0] - 1] = (u8)getchar();                 break;
            case POP:  state[0]--;                                          break;
        }
        state[1]++;
    }
}
