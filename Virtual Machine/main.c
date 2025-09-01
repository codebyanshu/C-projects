#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

typedef enum
{
    INST_PUSH,
    INST_POP,
    INST_ADD,
    INST_SUB,
    INST_MUL,
    INST_DIV,
    INST_PRINT
} Inst_Sets;

typedef struct
{
    Inst_Sets type;
    int value;
} Inst;

#define DEF_INST_PUSH(x) {.type = INST_PUSH,.value = x}
#define DEF_INST_POP() {.type = INST_POP}
#define DEF_INST_ADD() {.type = INST_ADD}
#define DEF_INST_SUB() {.type = INST_SUB}
#define DEF_INST_MUL() {.type = INST_MUL}
#define DEF_INST_DIV() {.type = INST_DIV}
#define DEF_INST_PRINT() {.type = INST_PRINT}

Inst program[] = {
    DEF_INST_PUSH(5),
    DEF_INST_PUSH(10),
    // DEF_INST_ADD(),
    // DEF_INST_PRINT()

};

#define PROGRAM_SIZE (sizeof(program) / sizeof(program[0]))
#define MAX_STACK_SIZE 1024
int stack_size;
int stack[MAX_STACK_SIZE];

void push(int value)
{
    if (stack_size >= MAX_STACK_SIZE)
    {
        fprintf(stderr, "ERROR: Stack Overflow\n");
        exit(1);
    }
    stack[stack_size] = value;
    stack_size++;
}

int pop()
{

    return stack[--stack_size];
}

void print_stack()
{
    for (int i = stack_size -1; i >= 0; i--)
    {
        printf("%d\n", stack[i]);
    }
}

void write_program_to_file(char *file_path){
    FILE *file = fopen(file_path,"wb");
    if (file == NULL)
    {
       fprintf(stderr,"Error: Could not write to file %s\n",file_path);
       exit(1);
    }

    fwrite(program,sizeof(program[0]),PROGRAM_SIZE,file);

    fclose(file);
}
Inst *read_program_from_file(char *file_path){
    FILE *file = fopen(file_path,"rb");
    if (file == NULL)
    {
       fprintf(stderr,"Error: Could not read to file %s\n",file_path);
       exit(1);
    }

    Inst *instruction = malloc(sizeof(Inst) * MAX_STACK_SIZE);
    fseek(file,0,SEEK_END);
    int length = ftell(file);
    fseek(file,0,SEEK_SET);
    fread(instruction,sizeof(instruction[0]),length,file);

    fclose(file);
    return instruction;
}

int main(int argc, char const *argv[])
{

    int a, b;
    write_program_to_file("test.tim");
    Inst *loaded_program = read_program_from_file("test.tim");
    for (size_t ip = 0; ip < PROGRAM_SIZE; ip++)
    {
        switch (loaded_program[ip].type)
        {
        case INST_PUSH:
            push(loaded_program[ip].value);
            break;
        case INST_POP:
            pop();
            break;
        case INST_ADD:
            a = pop();
            b = pop();
            push(a + b);
            break;
        case INST_SUB:
            a = pop();
            b = pop();
            push(a - b);
            break;
        case INST_MUL:
            a = pop();
            b = pop();
            push(a * b);
            break;
        case INST_DIV:
            a = pop();
            b = pop();
            push(a / b);
            break;
        case INST_PRINT:
            printf("%d\n", pop());

            break;
        }
    }
    print_stack();

    printf("Hello World");

    return 0;
}