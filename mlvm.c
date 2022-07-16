#include <stdbool.h> 
#include <stdio.h>

typedef enum {
    PSH,
    POP,
    ADD,
    SET,
    END
} OpCode;

typedef enum {
    A, B, C, D, E, F, // general-purpose registers
    SP, IP, // special registers
    NUM_REGISTERS // number of registers
} Registers;

const int program[] = {
    SET, C, 99,
    END
};

bool is_running = true;
int stack[256];
int registers[NUM_REGISTERS];

void stack_push(int x) {
    registers[SP]++;
    stack[registers[SP]] = x;
}

int stack_pop() {
    return stack[registers[SP]--];
}

void eval(OpCode op_code) {
    switch(op_code) {
        case END: {
            is_running = false;
            printf("End of program\n");
            break;
        }
        case PSH: {
            int a = program[++registers[IP]];
            stack_push(a);
            printf("Pushed %d to stack\n", a);
            break;
        }
        case POP: {
            int a = stack_pop();
            printf("Popped %d from stack\n", a);
            break;
        }
        case ADD: {
            int b = stack_pop();
            int a = stack_pop();
            int res = a+b;
            stack_push(res);
            printf("Added %d to stack\n", res);
            break;
        }
        case SET: {
            int reg = program[++registers[IP]];
            int a = program[++registers[IP]];
            registers[reg] = a;
            printf("Register %d set to %d\n", reg, registers[reg]);
            break;
        }
        default: {
            printf("unknown OpCode\n");
            break;
        }
    }
}

int main() {
    registers[SP] = -1;
    registers[IP] = 0;
    
   while(is_running) {
       eval(program[registers[IP]]);
       registers[IP]++;
   }

    return 0;
}
