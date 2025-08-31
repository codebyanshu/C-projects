#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#define MEM_SIZE 1024
#define NUM_REGS 8

typedef enum
{
    NOP = 0,
    LOAD,  // LOAD reg, value
    ADD,   // ADD reg1, reg2
    SUB,   // SUB reg1, reg2
    JMP,   // JMP address
    JZ,    // JZ reg, address
    PRINT, // PRINT reg
    HALT
} Opcode;

typedef struct
{
    uint8_t opcode;
    uint8_t operand1;
    uint8_t operand2;
    uint8_t operand3;
} Instruction;

uint8_t memory[MEM_SIZE];
int32_t registers[NUM_REGS];
uint32_t pc = 0; // Program counter

Instruction fetch()
{
    Instruction instr;
    instr.opcode = memory[pc++];
    instr.operand1 = memory[pc++];
    instr.operand2 = memory[pc++];
    instr.operand3 = memory[pc++];
    return instr;
}

void execute(Instruction instr)
{
    switch (instr.opcode)
    {
    case NOP:
        break;
    case LOAD:
        registers[instr.operand1] = instr.operand2;
        break;
    case ADD:
        registers[instr.operand1] += registers[instr.operand2];
        break;
    case SUB:
        registers[instr.operand1] -= registers[instr.operand2];
        break;
    case JMP:
        pc = instr.operand1;
        break;
    case JZ:
        if (registers[instr.operand1] == 0)
            pc = instr.operand2;
        break;
    case PRINT:
        printf("R%d = %d\n", instr.operand1, registers[instr.operand1]);
        break;
    case HALT:
        exit(0);
    default:
        printf("Unknown opcode: %d\n", instr.opcode);
        exit(1);
    }
}

void load_program(const uint8_t *program, size_t size)
{
    for (size_t i = 0; i < size && i < MEM_SIZE; ++i)
        memory[i] = program[i];
}

int main(int argc, char const *argv[])
{
    // Example program: LOAD R0, 10; LOAD R1, 20; ADD R0, R1; PRINT R0; HALT
    uint8_t program[] = {
        LOAD, 0, 10, 0,
        LOAD, 1, 20, 0,
        ADD, 0, 1, 0,
        PRINT, 0, 0, 0,
        HALT, 0, 0, 0};
    load_program(program, sizeof(program));

    while (pc < MEM_SIZE)
    {
        Instruction instr = fetch();
        execute(instr);
    }
    return 0;
}