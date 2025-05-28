#include "CPU.h"
#include <cstdint>
#include <iomanip>
#include <iostream>
#include <bitset>

using namespace std;


CPU::CPU(/* args */)
{

    // Setup Function Pointer Table

    // CPU Memory and Register Transfers

    // Register/Immediate to Register Transfer
    opList[0xA8] = &CPU::OP_A8;
    opList[0xAA] = &CPU::OP_AA;
    opList[0xBA] = &CPU::OP_BA;
    opList[0x98] = &CPU::OP_98;
    opList[0x8A] = &CPU::OP_8A;
    opList[0x9A] = &CPU::OP_9A;
    opList[0xA9] = &CPU::OP_A9;
    opList[0xA2] = &CPU::OP_A2;
    opList[0xA0] = &CPU::OP_A0;

    // Load Register from Memory
    opList[0xA5] = &CPU::OP_A5;
    opList[0xB5] = &CPU::OP_B5;
    opList[0xAD] = &CPU::OP_AD;
    opList[0xBD] = &CPU::OP_BD;
    opList[0xB9] = &CPU::OP_B9;
    opList[0xA1] = &CPU::OP_A1;
    opList[0xB1] = &CPU::OP_B1;
    opList[0xA6] = &CPU::OP_A6;
    opList[0xB6] = &CPU::OP_B6;
    opList[0xAE] = &CPU::OP_AE;
    opList[0xBE] = &CPU::OP_BE;
    opList[0xA4] = &CPU::OP_A4;
    opList[0xB4] = &CPU::OP_B4;
    opList[0xAC] = &CPU::OP_AC;
    opList[0xBC] = &CPU::OP_BC;

    // Store Register in Memory
    opList[0x85] = &CPU::OP_85;
    opList[0x95] = &CPU::OP_95;
    opList[0x8D] = &CPU::OP_8D;
    opList[0x9D] = &CPU::OP_9D;
    opList[0x99] = &CPU::OP_99;
    opList[0x81] = &CPU::OP_81;
    opList[0x91] = &CPU::OP_91;
    opList[0x86] = &CPU::OP_86;
    opList[0x96] = &CPU::OP_96;
    opList[0x8E] = &CPU::OP_8E;
    opList[0x84] = &CPU::OP_84;
    opList[0x94] = &CPU::OP_94;
    opList[0x8C] = &CPU::OP_8C;

    // Push/Pull
    opList[0x48] = &CPU::OP_48;
    opList[0x08] = &CPU::OP_08;
    opList[0x68] = &CPU::OP_68;
    opList[0x28] = &CPU::OP_28;

    // CPU Arithmetic/Logical Operations

    // Add memory to accumulator with carry
    opList[0x69] = &CPU::OP_69;
    opList[0x65] = &CPU::OP_65;
    opList[0x75] = &CPU::OP_75;
    opList[0x6D] = &CPU::OP_6D;
    opList[0x7D] = &CPU::OP_7D;
    opList[0x79] = &CPU::OP_79;
    opList[0x61] = &CPU::OP_61;
    opList[0x71] = &CPU::OP_71;

    // Subtract memory from accumulator with borrow
    opList[0xE9] = &CPU::OP_E9;
    opList[0xE5] = &CPU::OP_E5;
    opList[0xF5] = &CPU::OP_F5;
    opList[0xED] = &CPU::OP_ED;
    opList[0xFD] = &CPU::OP_FD;
    opList[0xF9] = &CPU::OP_F9;
    opList[0xE1] = &CPU::OP_E1;
    opList[0xF1] = &CPU::OP_F1;

    // Logical AND memory with accumulator
    opList[0x29] = &CPU::OP_29;
    opList[0x25] = &CPU::OP_25;
    opList[0x35] = &CPU::OP_35;
    opList[0x2D] = &CPU::OP_2D;
    opList[0x3D] = &CPU::OP_3D;
    opList[0x39] = &CPU::OP_39;
    opList[0x21] = &CPU::OP_21;
    opList[0x31] = &CPU::OP_31;

    // Exclusive-OR memory with accumulator
    opList[0x49] = &CPU::OP_49;
    opList[0x46] = &CPU::OP_45;
    opList[0x55] = &CPU::OP_55;
    opList[0x4D] = &CPU::OP_4D;
    opList[0x5D] = &CPU::OP_5D;
    opList[0x59] = &CPU::OP_59;
    opList[0x41] = &CPU::OP_41;
    opList[0x51] = &CPU::OP_51;

    // Logical OR memory with accumulator
    opList[0x09] = &CPU::OP_09;
    opList[0x05] = &CPU::OP_05;
    opList[0x15] = &CPU::OP_15;
    opList[0x0D] = &CPU::OP_0D;
    opList[0x1D] = &CPU::OP_1D;
    opList[0x19] = &CPU::OP_19;
    opList[0x01] = &CPU::OP_01;
    opList[0x11] = &CPU::OP_11;

    // Compare
    opList[0xC9] = &CPU::OP_C9;
    opList[0xC5] = &CPU::OP_C5;
    opList[0xD5] = &CPU::OP_D5;
    opList[0xCD] = &CPU::OP_CD;
    opList[0xDD] = &CPU::OP_DD;
    opList[0xD9] = &CPU::OP_D9;
    opList[0xC1] = &CPU::OP_C1;
    opList[0xD1] = &CPU::OP_D1;
    opList[0xE0] = &CPU::OP_E0;
    opList[0xE4] = &CPU::OP_E4;
    opList[0xEC] = &CPU::OP_EC;
    opList[0xC0] = &CPU::OP_C0;
    opList[0xC4] = &CPU::OP_C4;
    opList[0xCC] = &CPU::OP_CC;

    // Bit Test
    opList[0x24] = &CPU::OP_24;
    opList[0x2C] = &CPU::OP_2C;

    // Increment by one
    opList[0xE6] = &CPU::OP_E6;
    opList[0xF6] = &CPU::OP_F6;
    opList[0xEE] = &CPU::OP_EE;
    opList[0xFE] = &CPU::OP_FE;
    opList[0xE8] = &CPU::OP_E8;
    opList[0xC8] = &CPU::OP_C8;

    // Decrement by one
    opList[0xC6] = &CPU::OP_C6;
    opList[0xD6] = &CPU::OP_D6;
    opList[0xCE] = &CPU::OP_CE;
    opList[0xDE] = &CPU::OP_DE;
    opList[0xCA] = &CPU::OP_CA;
    opList[0x88] = &CPU::OP_88;


    // CPU Rotate and Shift instructions

    // Shift Left Logical/Arithmetic
    opList[0x0A] = &CPU::OP_0A;
    opList[0x06] = &CPU::OP_06;
    opList[0x16] = &CPU::OP_16;
    opList[0x0E] = &CPU::OP_0E;
    opList[0x1E] = &CPU::OP_1E;

    // Shift Right Logical
    opList[0x4A] = &CPU::OP_4A;
    opList[0x46] = &CPU::OP_46;
    opList[0x56] = &CPU::OP_56;
    opList[0x4E] = &CPU::OP_4E;
    opList[0x5E] = &CPU::OP_5E;

    // Rotate Left through Carry
    opList[0x2A] = &CPU::OP_2A;
    opList[0x26] = &CPU::OP_26;
    opList[0x36] = &CPU::OP_36;
    opList[0x2E] = &CPU::OP_2E;
    opList[0x3E] = &CPU::OP_3E;

    // Rotate Right Through Carry
    opList[0x6A] = &CPU::OP_6A;
    opList[0x66] = &CPU::OP_66;
    opList[0x76] = &CPU::OP_76;
    opList[0x6E] = &CPU::OP_6E;
    opList[0x7E] = &CPU::OP_7E;


    // CPU Jump and Control Instructions

    // Normal Jumps & Subroutine Calls/Returns
    opList[0x4C] = &CPU::OP_4C;
    opList[0x6C] = &CPU::OP_6C;
    opList[0x20] = &CPU::OP_20;
    opList[0x40] = &CPU::OP_40;
    opList[0x60] = &CPU::OP_60;

    // Conditional Branches (conditional jump to PC=PC+/-dd)
    opList[0x10] = &CPU::OP_10;
    opList[0x30] = &CPU::OP_30;
    opList[0x50] = &CPU::OP_50;
    opList[0x70] = &CPU::OP_70;
    opList[0x90] = &CPU::OP_90;
    opList[0xB0] = &CPU::OP_B0;
    opList[0xD0] = &CPU::OP_D0;
    opList[0xF0] = &CPU::OP_F0;

    // Interrupts, Exceptions, Breakpoints
    opList[0x00] = &CPU::OP_00;      // FORCE BREAK
    //void DUMMY();     // INTERRUPT
    //void DUMMY();     // NMI
    //void DUMMY();     // RESET

    // CPU Control
    opList[0x18] = &CPU::OP_18;
    opList[0x58] = &CPU::OP_58;
    opList[0xD8] = &CPU::OP_D8;
    opList[0xB8] = &CPU::OP_B8;
    opList[0x38] = &CPU::OP_38;
    opList[0x78] = &CPU::OP_78;
    opList[0xF8] = &CPU::OP_F8;

    // No Operation
    opList[0xEA] = &CPU::OP_EA;

    // CPU Illegal Opcodes

    // SAX and LAX
    opList[0x87] = &CPU::OP_87;
    opList[0x97] = &CPU::OP_97;
    opList[0x8F] = &CPU::OP_8F;
    opList[0x83] = &CPU::OP_83;
    opList[0xA7] = &CPU::OP_A7;
    opList[0xB7] = &CPU::OP_B7;
    opList[0xAF] = &CPU::OP_AF;
    opList[0xA3] = &CPU::OP_A3;
    opList[0xB3] = &CPU::OP_B3;

    // Combined ALU-opcodes

    // ???????????????????????????????

    // Other Illegal Opcodes

    opList[0x0B] = &CPU::OP_0B;
    opList[0x2B] = &CPU::OP_2B;
    opList[0x4B] = &CPU::OP_4B;
    opList[0x6B] = &CPU::OP_6B;
    opList[0xCB] = &CPU::OP_CB;
    opList[0xEB] = &CPU::OP_EB;
    opList[0xBB] = &CPU::OP_BB;


    // NUL/NOP and KIL/JAM/HLT

    // TODO


    // Unstable Illegal Opcodes
    opList[0x8B] = &CPU::OP_8B;
    opList[0xAB] = &CPU::OP_AB;
    opList[0xBF] = &CPU::OP_BF;
    opList[0x93] = &CPU::OP_93;
    opList[0x9F] = &CPU::OP_9F;
    opList[0x9C] = &CPU::OP_9C;
    opList[0x9E] = &CPU::OP_9E;
    opList[0x9B] = &CPU::OP_9B;

    
}

CPU::~CPU()
{
}

void CPU::Cycle()
{
    // Runs opcode indicated by byte at memory[programCounter]
    ((*this).*(opList[memory[programCounter]]))(); 
    return;
}


// OPCODES //

void CPU::OP_NULL()
{

}


// CPU MEMORY AND REGISTER TRANSFERS


// Register/Immediate to Register Transfer

// TAY: Move register A into register Y. Flags NZ
void CPU::OP_A8() 
{                          
    registerY = registerA;
    clearNZ();
    setNZ(registerY);
    ++programCounter;
}

// TAX: Move Register A into Register X. Flags NZ
void CPU::OP_AA()                           
{
    registerX = registerA;
    clearNZ();
    setNZ(registerX);
    ++programCounter;
}

// TSX: Move Stack Pointer into Register X. Flags NZ
void CPU::OP_BA()
{
    registerX = stackPointer;
    clearNZ();
    setNZ(registerX);
    ++programCounter;
}

// TYA: Move Register Y into Register A. Flags Nz
void CPU::OP_98()
{
    registerA = registerY;
    clearNZ();
    setNZ(registerA);
    ++programCounter;
}

// TXA: Move Register X into Register A. Flags NZ
void CPU::OP_8A()
{
    registerA = registerX;
    clearNZ();
    setNZ(registerA);
    ++programCounter;
}

// TXS: Move Register X into the Stack Pointer. No Flags
void CPU::OP_9A()
{
    stackPointer = registerX;
    ++programCounter;
}

// LDA #nn: Load next byte into Register A. Flags NZ
void CPU::OP_A9()
{
    registerA = memory[programCounter + 1];
    clearNZ();
    setNZ(registerA);
    programCounter += 2;
}

// LDX #nn: Load next byte into Register X. Flags NZ
void CPU::OP_A2()
{
    registerX = memory[programCounter + 1];
    clearNZ();
    setNZ(registerX);
    programCounter += 2;
}

// LDY #nn: Load next byte into Register Y. Flags NZ
void CPU::OP_A0()
{
    registerY = memory[programCounter + 1];
    clearNZ();
    setNZ(registerY);
    programCounter += 2;
}


// Load Register From Memory

// LDA nn: Load byte at nn into Register A. Flags NZ
void CPU::OP_A5()
{
    registerA = memory[memory[programCounter + 1]];
    clearNZ();
    setNZ(registerA);
    programCounter += 2;
}

// LDA nn,X: Load byte at nn+X into register A. Flags NZ
void CPU::OP_B5()
{
    registerA = memory[memory[programCounter + 1] + registerX];
    clearNZ();
    setNZ(registerA);
    programCounter += 2;
}

// LDA nnnn: Load byte at nnnn into Register A. Flag NZ
void CPU::OP_AD()
{
    uint16_t address = ((memory[programCounter + 2] << 8u) + memory[programCounter + 1]) % 0x2000;
    registerA = memory[address];
    clearNZ();
    setNZ(registerA);
    programCounter += 3;
}

// LDA nnnn+X: Load byte at nnnn+X into register A. Flags NZ
void CPU::OP_BD()
{
    uint16_t address = ((memory[programCounter + 2] << 8u) + memory[programCounter + 1] + registerX) % 0x2000;
    registerA = memory[address];
    clearNZ();
    setNZ(registerA);
    programCounter += 3;
}

// LDA nnnn+Y: Load byte at nnnn+Y into register A. Flags NZ
void CPU::OP_B9()
{
    uint16_t address = ((memory[programCounter + 2] << 8u) + memory[programCounter + 1] + registerY) % 0x2000;
    registerA = memory[address];
    clearNZ();
    setNZ(registerA);
    programCounter += 3;
}

// LDA (nn,X): Load byte at WORD at nn+X into Register A. Flags NZ
void CPU::OP_A1()
{
    uint16_t address = ((memory[memory[programCounter + 1] + registerX + 1] << 8u) + memory[memory[programCounter + 1] + registerX]) % 0x2000;
    registerA = memory[address];
    clearNZ();
    setNZ(registerA);
    programCounter += 2;
}

// LDA (nn),Y: Load byte at (WORD at nn)+Y into Register A. Flags NZ
void CPU::OP_B1()
{
    uint16_t address = ((memory[memory[programCounter + 1] + 1] << 8u) + memory[memory[programCounter + 1]] + registerY) % 0x2000;
    registerA = memory[address];
    clearNZ();
    setNZ(registerA);
    programCounter += 2;
}

// LDX nn: Load byte at nn into Register X. Flags NZ
void CPU::OP_A6()
{
    registerX = memory[memory[programCounter + 1]];
    clearNZ();
    setNZ(registerX);
    programCounter += 2;
}

// LDX nn+Y: Load byte at nn+Y into register X. Flags NZ
void CPU::OP_B6()
{
    registerX = memory[memory[programCounter + 1] + registerY];
    clearNZ();
    setNZ(registerX);
    programCounter += 2;
}

// LDX nnnn: Loacd byte at nnnn into Register X. Flags NZ
void CPU::OP_AE()
{
    uint16_t address = ((memory[programCounter + 2] << 8u) + memory[programCounter + 1]) % 0x2000;
    registerX = memory[address];
    clearNZ();
    setNZ(registerX);
    programCounter += 3;
}

// LDX nnnn+Y: Load byte at nnnn+Y into Register X. Flags NZ
void CPU::OP_BE()
{
    uint16_t address = (((memory[programCounter + 2] << 8u) + memory[programCounter + 1]) + registerY) % 0x2000;
    registerX = memory[address];
    clearNZ();
    setNZ(registerX);
    programCounter += 3;
}

// LDY nn: Load byte at nn into Register Y. Flags NZ
void CPU::OP_A4()
{
    registerY = memory[memory[programCounter + 1]];
    clearNZ();
    setNZ(registerY);
    programCounter += 2;
}

// LDY nn+X: Load byte at nn+X into Registewr Y. Flags NZ
void CPU::OP_B4()
{
    registerY = memory[memory[programCounter + 1] + registerX];
    clearNZ();
    setNZ(registerY);
    programCounter += 2;
}

// LDY nnnn: Load byte at nnnn into register Y. Flags NZ
void CPU::OP_AC()
{
    uint16_t address = ((memory[programCounter + 2] << 8u) + memory[programCounter + 1]) % 0x2000;
    registerY = memory[address];
    clearNZ();
    setNZ(registerY);
    programCounter += 3;
}

// LDY nnnn+X: Load byte at nnnn+X into Register Y. Flags NZ
void CPU::OP_BC()
{
    uint16_t address = (((memory[programCounter + 2] << 8u) + memory[programCounter + 1]) + registerX) % 0x2000;
    registerY = memory[address];
    clearNZ();
    setNZ(registerY);
    programCounter += 3;
}


// Store Register in Memory

// STA nn: Move byte from Register A into nn. No Flags
void CPU::OP_85()
{
    memory[memory[programCounter + 1]] = registerA;
    programCounter += 2;
}

// STA nn,X: Move byte from Register A into nn+X. No flags
void CPU::OP_95()
{
    memory[memory[programCounter + 1] + registerX] = registerA;
    programCounter += 2;
}

// STA nnnn: Move byte from Register A into nnnn. No Flags
void CPU::OP_8D()
{
    uint16_t address = ((memory[programCounter + 2] << 8u) + memory[programCounter + 1]) % 0x2000;
    memory[address] = registerA;
    programCounter += 3;
}

// STA nnnn,X: Move byte from register A into nnnn+X. No Flags
void CPU::OP_9D()
{
    uint16_t address = (((memory[programCounter + 2] << 8u) + memory[programCounter + 1]) + registerX) % 0x2000;
    memory[address] = registerA;
    programCounter += 3;
}

// STA nnnn,Y: Move byte from register A into nnnn+Y. No Flags
void CPU::OP_99()
{
    uint16_t address = (((memory[programCounter + 2] << 8u) + memory[programCounter + 1]) + registerY) % 0x2000;
    memory[address] = registerA;
    programCounter += 3;
}

// STA (nn,X): Move byte from register A into (WORD(nn+X)). No flags
void CPU::OP_81()
{
    uint16_t address = ((memory[memory[programCounter + 1] + registerX + 1] << 8u) + memory[memory[programCounter + 1] + registerX]) % 0x2000;
    memory[address] = registerA;
    programCounter += 2;
}

// STA (nn),Y: Move byte from regiater A into (WORD(nn)+Y). No flags
void CPU::OP_91()
{
    uint16_t address = (((memory[memory[programCounter + 1] + 1] << 8u) + memory[memory[programCounter + 1]]) + registerY) % 0x2000;
    memory[address] = registerA;
    programCounter += 2;
}

// STX nn: Move byte from register X into nn. No Flags
void CPU::OP_86()
{
    memory[memory[programCounter + 1]] = registerX;
    programCounter += 2;
}

// STX nn,Y: Move byte from register X into nn+Y. No Flags
void CPU::OP_96()
{
    memory[memory[programCounter + 1] + registerY] = registerX;
    programCounter += 2;
}

// STX nnnn: Move byte from register X into nnnn. No Flags
void CPU::OP_8E()
{
    uint16_t address = ((memory[programCounter + 2] << 8u) + memory[programCounter + 1]) % 0x2000;
    memory[address] = registerX;
    programCounter += 3;
}

// STY nn: Move byte from register Y into nn. No Flags
void CPU::OP_84()
{
    memory[memory[programCounter + 1]] = registerY;
    programCounter += 2;
}

// STY nn+X: Move byte from register Y into nn+X. No Flags
void CPU::OP_94()
{
    memory[memory[programCounter + 1] + registerX] = registerY;
    programCounter += 2;
}

// STY nnnn: Move byte from register Y into nnnn. No Flags
void CPU::OP_8C()
{
    uint16_t address = ((memory[programCounter + 2] << 8u) + memory[programCounter + 1]) % 0x2000;
    memory[address] = registerY;
    programCounter += 3;
}


// Push/Pull  *** Stack pointer needs 0x0100 added prior to use to address correct space in memory ***

// PHA: Push A. No Flags
void CPU::OP_48()
{
    uint16_t address = (stackPointer + 0x0100);
    memory[address] = registerA;
    --stackPointer;
    ++programCounter;
}

// PHP: Push P. Writes 1 to B and unused flags.
void CPU::OP_08()
{
    uint16_t address = stackPointer + 0x0100;
    memory[address] = processStatusRegister | 0b00110000;
    --stackPointer;
    ++programCounter;
}

// PLA: Pop A. Flags NZ
void CPU::OP_68()
{
    ++stackPointer;
    uint16_t address = stackPointer + 0x0100;
    registerA = memory[address];
    setNZ(registerA);
    ++programCounter;
}

// PLP: Pop P. PLP cannot change B or unused flags.
void CPU::OP_28()
{
    ++stackPointer;
    uint16_t address = stackPointer + 0x0100;
    // Mask both registers and then or them to ensure B and unused do not change.
    uint8_t maskedProcessRegister = processStatusRegister & 0b00110000;
    uint8_t maskedMemory = memory[address] & 0b11001111;
    processStatusRegister = maskedProcessRegister | maskedMemory;
    ++programCounter;    
}



// CPU Arithmetic/Logical Operations

// Add memory to accumulator with carry

// ADC #nn: Add nn and Carry to Accumulator. Flags nzcv
void CPU::OP_69()
{
    if ( processStatusRegister & 0b00001000 == 0)
    {
        uint8_t adder = memory[programCounter + 1] + (processStatusRegister & 0b00000001);
        uint8_t tempA = registerA + adder;  
        clearNZCV(); 
        setCarry(registerA, tempA);
        setOverflow(registerA, adder, tempA);
        registerA = tempA & 0xFF;
        setNZ(registerA);
        programCounter += 2;
    }
    else
    {
        uint8_t adder = memory[programCounter + 1] + (processStatusRegister & 0b00000001);
        clearNZCV();
        int tempA = (((registerA >> 4u) * 10) + (registerA & 0x0F)) + (((adder >> 4u) * 10) + (adder & 0x0F));
        uint8_t binaryTempA = registerA + adder;
        setCarryDecimalAdd(tempA);
        setOverflow(registerA, adder, binaryTempA);
        tempA %= 100;
        registerA = ((tempA / 10) << 4u) + (tempA % 10);
        setNZ(registerA);
        programCounter += 2;
    }
}

// ADC nn: Add [nn] and carry to Accumulator. Flags nzcv
void CPU::OP_65()
{
    if ( processStatusRegister & 0b00001000 == 0)
    {
        uint8_t adder = memory[memory[programCounter + 1]] + (processStatusRegister & 0b00000001);
        uint8_t tempA = registerA + adder; 
        clearNZCV();  
        setCarry(registerA, tempA);
        setOverflow(registerA, adder, tempA);
        registerA = tempA & 0xFF;
        setNZ(registerA);
        programCounter += 2;
    }
    else
    {
        uint8_t adder = memory[memory[programCounter + 1]] + (processStatusRegister & 0b00000001);
        clearNZCV();
        int tempA = (((registerA >> 4u) * 10) + (registerA & 0x0F)) + (((adder >> 4u) * 10) + (adder & 0x0F));
        uint8_t binaryTempA = registerA + adder;
        setCarryDecimalAdd(tempA);
        setOverflow(registerA, adder, binaryTempA);
        tempA %= 100;
        registerA = ((tempA / 10) << 4u) + (tempA % 10);
        setNZ(registerA);
        programCounter += 2;
    }
}

// ADC nn,X: Add [nn+X] and carry to Accumulator. Flags nzcv
void CPU::OP_75()
{
    if ( processStatusRegister & 0b00001000 == 0)
    {
        uint8_t adder = memory[memory[programCounter + 1] + registerX] + (processStatusRegister & 0b00000001);
        uint8_t tempA = registerA + adder;  
        clearNZCV(); 
        setCarry(registerA, tempA);
        setOverflow(registerA, adder, tempA);
        registerA = tempA & 0xFF;
        setNZ(registerA);
        programCounter += 2;
    }
    else
    {
        uint8_t adder = memory[memory[programCounter + 1] + registerX] + (processStatusRegister & 0b00000001);
        clearNZCV();
        int tempA = (((registerA >> 4u) * 10) + (registerA & 0x0F)) + (((adder >> 4u) * 10) + (adder & 0x0F));
        uint8_t binaryTempA = registerA + adder;
        setCarryDecimalAdd(tempA);
        setOverflow(registerA, adder, binaryTempA);
        tempA %= 100;
        registerA = ((tempA / 10) << 4u) + (tempA % 10);
        setNZ(registerA);
        programCounter += 2;
    }
}

// ADC nnnn: Add [nnnn] and carry to Accumulator. Flags nzcv
void CPU::OP_6D()
{
    if ( processStatusRegister & 0b00001000 == 0)
    {
        uint16_t address = ((memory[programCounter + 2] << 8u) + memory[programCounter + 1]) % 0x2000;
        uint8_t adder = memory[address] + (processStatusRegister & 0b00000001);
        uint8_t tempA = registerA + adder;  
        clearNZCV(); 
        setCarry(registerA, tempA);
        setOverflow(registerA, adder, tempA);
        registerA = tempA & 0xFF;
        setNZ(registerA);
        programCounter += 3;
    }
    else
    {
        uint16_t address = ((memory[programCounter + 2] << 8u) + memory[programCounter + 1]) % 0x2000;
        uint8_t adder = memory[address] + (processStatusRegister & 0b00000001);
        clearNZCV();
        int tempA = (((registerA >> 4u) * 10) + (registerA & 0x0F)) + (((adder >> 4u) * 10) + (adder & 0x0F));
        uint8_t binaryTempA = registerA + adder;
        setCarryDecimalAdd(tempA);
        setOverflow(registerA, adder, binaryTempA);
        tempA %= 100;
        registerA = ((tempA / 10) << 4u) + (tempA % 10);
        setNZ(registerA);
        programCounter += 3;
    }
}

// ADC nnnn+X: Add [nnnn+X] and carry to Accumulator. Flags nzcv
void CPU::OP_7D()
{
    if ( processStatusRegister & 0b00001000 == 0)
    {
        uint16_t address = ((memory[programCounter + 2] << 8u) + memory[programCounter + 1] + registerX) % 0x2000;
        uint8_t adder = memory[address] + (processStatusRegister & 0b00000001);
        uint8_t tempA = registerA + adder; 
        clearNZCV();  
        setCarry(registerA, tempA);
        setOverflow(registerA, adder, tempA);
        registerA = tempA & 0xFF;
        setNZ(registerA);
        programCounter += 3;
    }
    else
    {
        uint16_t address = ((memory[programCounter + 2] << 8u) + memory[programCounter + 1] + registerX) % 0x2000;
        uint8_t adder = memory[address] + (processStatusRegister & 0b00000001);
        clearNZCV();
        int tempA = (((registerA >> 4u) * 10) + (registerA & 0x0F)) + (((adder >> 4u) * 10) + (adder & 0x0F));
        uint8_t binaryTempA = registerA + adder;
        setCarryDecimalAdd(tempA);
        setOverflow(registerA, adder, binaryTempA);
        tempA %= 100;
        registerA = ((tempA / 10) << 4u) + (tempA % 10);
        setNZ(registerA);
        programCounter += 3;
    }
}

// ADC nnnn+Y: Add [nnnn+Y] and carry to Accumulator. Flags nzcv
void CPU::OP_79()
{
    if ( processStatusRegister & 0b00001000 == 0)
    {
        uint16_t address = ((memory[programCounter + 2] << 8u) + memory[programCounter + 1] + registerY) % 0x2000;
        uint8_t adder = memory[address] + (processStatusRegister & 0b00000001);
        uint8_t tempA = registerA + adder;  
        clearNZCV(); 
        setCarry(registerA, tempA);
        setOverflow(registerA, adder, tempA);
        registerA = tempA & 0xFF;
        setNZ(registerA);
        programCounter += 3;
    }
    else
    {
        uint16_t address = ((memory[programCounter + 2] << 8u) + memory[programCounter + 1] + registerY) % 0x2000;
        uint8_t adder = memory[address] + (processStatusRegister & 0b00000001);
        clearNZCV();
        int tempA = (((registerA >> 4u) * 10) + (registerA & 0x0F)) + (((adder >> 4u) * 10) + (adder & 0x0F));
        uint8_t binaryTempA = registerA + adder;
        setCarryDecimalAdd(tempA);
        setOverflow(registerA, adder, binaryTempA);
        tempA %= 100;
        registerA = ((tempA / 10) << 4u) + (tempA % 10);
        setNZ(registerA);
        programCounter += 3;
    }
}

// ADC [[nn+X]]: Add [word[nn+X]] and carry to Accumulator. Flags nzcv
void CPU::OP_61()
{
    if ( processStatusRegister & 0b00001000 == 0)
    {
        uint16_t address = ((memory[memory[programCounter + 1] + registerX + 1] << 8u) + memory[memory[programCounter + 1] + registerX]) % 0x2000;
        uint8_t adder = memory[address] + (processStatusRegister & 0b00000001);
        uint8_t tempA = registerA + adder;  
        clearNZCV(); 
        setCarry(registerA, tempA);
        setOverflow(registerA, adder, tempA);
        registerA = tempA & 0xFF;
        setNZ(registerA);
        programCounter += 2;
    }
    else
    {
        uint16_t address = ((memory[memory[programCounter + 1] + registerX + 1] << 8u) + memory[memory[programCounter + 1] + registerX]) % 0x2000;
        uint8_t adder = memory[address] + (processStatusRegister & 0b00000001);
        clearNZCV();
        int tempA = (((registerA >> 4u) * 10) + (registerA & 0x0F)) + (((adder >> 4u) * 10) + (adder & 0x0F));
        uint8_t binaryTempA = registerA + adder;
        setCarryDecimalAdd(tempA);
        setOverflow(registerA, adder, binaryTempA);
        tempA %= 100;
        registerA = ((tempA / 10) << 4u) + (tempA % 10);
        setNZ(registerA);
        programCounter += 2;
    }
}

// ADC [[nn]+Y]: Add [word[nn]+Y] and carry to Accumulator. Flags nzcv
void CPU::OP_71()
{
    if ( processStatusRegister & 0b00001000 == 0)
    {
        uint16_t address = ((memory[memory[programCounter + 1] + 1] << 8u) + memory[memory[programCounter + 1]] + registerY) % 0x2000;
        uint8_t adder = memory[address] + (processStatusRegister & 0b00000001);
        uint8_t tempA = registerA + adder;  
        clearNZCV(); 
        setCarry(registerA, tempA);
        setOverflow(registerA, adder, tempA);
        registerA = tempA & 0xFF;
        setNZ(registerA);
        programCounter += 2;
    }
    else
    {
        uint16_t address = ((memory[memory[programCounter + 1] + 1] << 8u) + memory[memory[programCounter + 1]] + registerY) % 0x2000;
        uint8_t adder = memory[address] + (processStatusRegister & 0b00000001);
        clearNZCV();
        int tempA = (((registerA >> 4u) * 10) + (registerA & 0x0F)) + (((adder >> 4u) * 10) + (adder & 0x0F));
        uint8_t binaryTempA = registerA + adder;
        setCarryDecimalAdd(tempA);
        setOverflow(registerA, adder, binaryTempA);
        tempA %= 100;
        registerA = ((tempA / 10) << 4u) + (tempA % 10);
        setNZ(registerA);
        programCounter += 2;
    }
}

// TESTED TO HERE *************************


// Subtract memory from accumulator with borrow

// SBC #nn: Add carry to Accumulator then subtract 1 and #nn. Flags nzcv
void CPU::OP_E9()
{
    if ( processStatusRegister & 0b00001000 == 0)
    {
        uint8_t adder = memory[programCounter + 1];
        uint8_t tempA = (registerA + (processStatusRegister & 0b00000001)) - 1 - adder;
        clearNZCV();
        setCarry(registerA, tempA);
        setOverflow(registerA, adder, tempA);
        registerA = tempA & 0xFF;
        setNZ(registerA);
        programCounter += 2;
    }
    else
    {
        uint8_t adder = memory[programCounter + 1];
        uint8_t binaryTempA = (registerA + (processStatusRegister & 0b00000001)) - 1 - adder;
        int tempA = (((registerA >> 4u) * 10) + (registerA & 0x0F)) + (processStatusRegister & 0b00000001) - 1 - (((adder >> 4u) * 10) + (adder & 0x0F));
        clearNZCV();
        setCarryDecimalSub(tempA);
        setOverflow(registerA, adder, binaryTempA);
        if (tempA < 0)
        {
            tempA += 100;
        }
        else
        {
            tempA %= 100;
        }
        registerA = ((tempA / 10) << 4u) + (tempA % 10);
        setNZ(registerA);
        programCounter += 2;
    }
}

// SBC [nn]: Add carry to Accumulator then subtract 1 and [nn]. Flags nzcv
void CPU::OP_E5()
{
    if ( processStatusRegister & 0b00001000 == 0)
    {
        uint8_t adder = memory[memory[programCounter + 1]];
        uint8_t tempA = (registerA + (processStatusRegister & 0b00000001)) - 1 - adder;
        clearNZCV();
        setCarry(registerA, tempA);
        setOverflow(registerA, adder, tempA);
        registerA = tempA & 0xFF;
        setNZ(registerA);
        programCounter += 2;
    }
    else
    {
        uint8_t adder = memory[memory[programCounter + 1]];
        uint8_t binaryTempA = (registerA + (processStatusRegister & 0b00000001)) - 1 - adder;
        int tempA = (((registerA >> 4u) * 10) + (registerA & 0x0F)) + (processStatusRegister & 0b00000001) - 1 - (((adder >> 4u) * 10) + (adder & 0x0F));
        clearNZCV();
        setCarryDecimalSub(tempA);
        setOverflow(registerA, adder, binaryTempA);
        if (tempA < 0)
        {
            tempA += 100;
        }
        else
        {
            tempA %= 100;
        }
        registerA = ((tempA / 10) << 4u) + (tempA % 10);
        setNZ(registerA);
        programCounter += 2;
    }
}

// SBC [nn+X]: Add carry to Accumulator then subtract 1 and [nn+X]. Flags nzcv
void CPU::OP_F5()
{
    if ( processStatusRegister & 0b00001000 == 0)
    {
        uint8_t adder = memory[memory[programCounter + 1] + registerX];
        uint8_t tempA = (registerA + (processStatusRegister & 0b00000001)) - 1 - adder; 
        clearNZCV();  
        setCarry(registerA, tempA);
        setOverflow(registerA, adder, tempA);
        registerA = tempA & 0xFF;
        setNZ(registerA);
        programCounter += 2;
    }
    else
    {
        uint8_t adder = memory[memory[programCounter + 1] + registerX];
        uint8_t binaryTempA = (registerA + (processStatusRegister & 0b00000001)) - 1 - adder;
        int tempA = (((registerA >> 4u) * 10) + (registerA & 0x0F)) + (processStatusRegister & 0b00000001) - 1 - (((adder >> 4u) * 10) + (adder & 0x0F));
        clearNZCV();
        setCarryDecimalSub(tempA);
        setOverflow(registerA, adder, binaryTempA);
        if (tempA < 0)
        {
            tempA += 100;
        }
        else
        {
            tempA %= 100;
        }
        registerA = ((tempA / 10) << 4u) + (tempA % 10);
        setNZ(registerA);
        programCounter += 2;
    }
}

// SBC [nnnn]: Add carry to Accumulator then subtract 1 and [nnnn]. Flags nzcv
void CPU::OP_ED()
{
    if ( processStatusRegister & 0b00001000 == 0)
    {
        uint16_t address = ((memory[programCounter + 2] << 8u) + memory[programCounter + 1]) % 0x2000;
        uint8_t adder = memory[address];
        uint8_t tempA = (registerA + (processStatusRegister & 0b00000001)) - 1 - adder;   
        clearNZCV();
        setCarry(registerA, tempA);
        setOverflow(registerA, adder, tempA);
        registerA = tempA & 0xFF;
        setNZ(registerA);
        programCounter += 3;
    }
    else
    {
        uint16_t address = ((memory[programCounter + 2] << 8u) + memory[programCounter + 1]) % 0x2000;
        uint8_t adder = memory[address];
        uint8_t binaryTempA = (registerA + (processStatusRegister & 0b00000001)) - 1 - adder;
        int tempA = (((registerA >> 4u) * 10) + (registerA & 0x0F)) + (processStatusRegister & 0b00000001) - 1 - (((adder >> 4u) * 10) + (adder & 0x0F));
        clearNZCV();
        setCarryDecimalSub(tempA);
        setOverflow(registerA, adder, binaryTempA);
        if (tempA < 0)
        {
            tempA += 100;
        }
        else
        {
            tempA %= 100;
        }
        registerA = ((tempA / 10) << 4u) + (tempA % 10);
        setNZ(registerA);
        programCounter += 3;
    }
}

// SBC [nnnn+X]: Add carry to Accumulator then subtract 1 and [nnnn+X]. Flags nzcv
void CPU::OP_FD()
{
    if ( processStatusRegister & 0b00001000 == 0)
    {
        uint16_t address = ((memory[programCounter + 2] << 8u) + memory[programCounter + 1] + registerX) % 0x2000;
        uint8_t adder = memory[address];
        uint8_t tempA = (registerA + (processStatusRegister & 0b00000001)) - 1 - adder;   
        clearNZCV();
        setCarry(registerA, tempA);
        setOverflow(registerA, adder, tempA);
        registerA = tempA & 0xFF;
        setNZ(registerA);
        programCounter += 3;
    }
    else
    {
        uint16_t address = ((memory[programCounter + 2] << 8u) + memory[programCounter + 1] + registerX) % 0x2000;
        uint8_t adder = memory[address];
        uint8_t binaryTempA = (registerA + (processStatusRegister & 0b00000001)) - 1 - adder;
        int tempA = (((registerA >> 4u) * 10) + (registerA & 0x0F)) + (processStatusRegister & 0b00000001) - 1 - (((adder >> 4u) * 10) + (adder & 0x0F));
        clearNZCV();
        setCarryDecimalSub(tempA);
        setOverflow(registerA, adder, binaryTempA);
        if (tempA < 0)
        {
            tempA += 100;
        }
        else
        {
            tempA %= 100;
        }
        registerA = ((tempA / 10) << 4u) + (tempA % 10);
        setNZ(registerA);
        programCounter += 3;
    }
}

// SBC [nnnn+Y]: Add carry to Accumulator then subtract 1 and [nnnn+Y]. Flags nzcv
void CPU::OP_F9()
{
    if ( processStatusRegister & 0b00001000 == 0)
    {
        uint16_t address = ((memory[programCounter + 2] << 8u) + memory[programCounter + 1] + registerY) % 0x2000;
        uint8_t adder = memory[address];
        uint8_t tempA = (registerA + (processStatusRegister & 0b00000001)) - 1 - adder; 
        clearNZCV();  
        setCarry(registerA, tempA);
        setOverflow(registerA, adder, tempA);
        registerA = tempA & 0xFF;
        setNZ(registerA);
        programCounter += 3;
    }
    else
    {
        uint16_t address = ((memory[programCounter + 2] << 8u) + memory[programCounter + 1] + registerY) % 0x2000;
        uint8_t adder = memory[address];
        uint8_t binaryTempA = (registerA + (processStatusRegister & 0b00000001)) - 1 - adder;
        int tempA = (((registerA >> 4u) * 10) + (registerA & 0x0F)) + (processStatusRegister & 0b00000001) - 1 - (((adder >> 4u) * 10) + (adder & 0x0F));
        clearNZCV();
        setCarryDecimalSub(tempA);
        setOverflow(registerA, adder, binaryTempA);
        if (tempA < 0)
        {
            tempA += 100;
        }
        else
        {
            tempA %= 100;
        }
        registerA = ((tempA / 10) << 4u) + (tempA % 10);
        setNZ(registerA);
        programCounter += 3;
    }
}

// SBC [word[nn+X]]: Add carry to Accumulator then subtract 1 and [word[nn+X]]. Flags nzcv
void CPU::OP_E1()
{
    if ( processStatusRegister & 0b00001000 == 0)
    {
        uint16_t address = ((memory[memory[programCounter + 1] + registerX + 1] << 8u) + memory[memory[programCounter + 1] + registerX]) % 0x2000;
        uint8_t adder = memory[address];
        uint8_t tempA = (registerA + (processStatusRegister & 0b00000001)) - 1 - adder;  
        clearNZCV(); 
        setCarry(registerA, tempA);
        setOverflow(registerA, adder, tempA);
        registerA = tempA & 0xFF;
        setNZ(registerA);
        programCounter += 2;
    }
    else
    {
        uint16_t address = ((memory[memory[programCounter + 1] + registerX + 1] << 8u) + memory[memory[programCounter + 1] + registerX]) % 0x2000;
        uint8_t adder = memory[address];
        uint8_t binaryTempA = (registerA + (processStatusRegister & 0b00000001)) - 1 - adder;
        int tempA = (((registerA >> 4u) * 10) + (registerA & 0x0F)) + (processStatusRegister & 0b00000001) - 1 - (((adder >> 4u) * 10) + (adder & 0x0F));
        clearNZCV();
        setCarryDecimalSub(tempA);
        setOverflow(registerA, adder, binaryTempA);
        if (tempA < 0)
        {
            tempA += 100;
        }
        else
        {
            tempA %= 100;
        }
        registerA = ((tempA / 10) << 4u) + (tempA % 10);
        setNZ(registerA);
        programCounter += 2;
    }
}

// SBC [word[nn]+Y]: Add carry to Accumulator then subtract 1 and [word[nn]+Y]. Flags nzcv
void CPU::OP_F1()
{
    if ( processStatusRegister & 0b00001000 == 0)
    {
        uint16_t address = ((memory[memory[programCounter + 1] + 1] << 8u) + memory[memory[programCounter + 1]] + registerY) % 0x2000;
        uint8_t adder = memory[address];
        uint8_t tempA = (registerA + (processStatusRegister & 0b00000001)) - 1 - adder;   
        clearNZCV();
        setCarry(registerA, tempA);
        setOverflow(registerA, adder, tempA);
        registerA = tempA & 0xFF;
        setNZ(registerA);
        programCounter += 2;
    }
    else
    {
        uint16_t address = ((memory[memory[programCounter + 1] + 1] << 8u) + memory[memory[programCounter + 1]] + registerY) % 0x2000;
        uint8_t adder = memory[address];
        uint8_t binaryTempA = (registerA + (processStatusRegister & 0b00000001)) - 1 - adder;
        int tempA = (((registerA >> 4u) * 10) + (registerA & 0x0F)) + (processStatusRegister & 0b00000001) - 1 - (((adder >> 4u) * 10) + (adder & 0x0F));
        clearNZCV();
        setCarryDecimalSub(tempA);
        setOverflow(registerA, adder, binaryTempA);
        if (tempA < 0)
        {
            tempA += 100;
        }
        else
        {
            tempA %= 100;
        }
        registerA = ((tempA / 10) << 4u) + (tempA % 10);
        setNZ(registerA);
        programCounter += 2;
    }
}


// Logical AND memory with accumulator

// AND #nn: A = A AND #nn. Flags nz
void CPU::OP_29()
{
    registerA = registerA & memory[programCounter + 1];
    clearNZ();
    setNZ(registerA);
    programCounter += 2;
}

// AND [nn]: A = A AND [nn]. Flags nz
void CPU::OP_25()
{
    registerA = registerA & memory[memory[programCounter + 1]];
    clearNZ();
    setNZ(registerA);
    programCounter += 2;
}

// AND [nn+X]: A = A AND [nn+X]. Flags nz
void CPU::OP_35()
{
    registerA = registerA & memory[memory[programCounter + 1] + registerX];
    clearNZ();
    setNZ(registerA);
    programCounter += 2;
}

// AND [nnnn]: A = A AND [nnnn]. Flags nz
void CPU::OP_2D()
{
    uint16_t address = ((memory[programCounter + 2] << 8u) + memory[programCounter + 1]) % 0x2000;
    registerA = registerA & memory[address];
    clearNZ();
    setNZ(registerA);
    programCounter += 3;
}

// AND [nnnn+X]: A = A AND [nnnn+X]. Flags nz
void CPU::OP_3D()
{
    uint16_t address = (((memory[programCounter + 2] << 8u) + memory[programCounter + 1]) + registerX) % 0x2000;
    registerA = registerA & memory[address];
    clearNZ();
    setNZ(registerA);
    programCounter += 3;
}

// AND [nnnn+Y]: A = A AND [nnnn+Y]. Flags nz
void CPU::OP_39()
{
    uint16_t address = (((memory[programCounter + 2] << 8u) + memory[programCounter + 1]) + registerY) % 0x2000;
    registerA = registerA & memory[address];
    clearNZ();
    setNZ(registerA);
    programCounter += 3;
}

// AND [word[nn+X]]: A = A AND [word[nn+X]]. Flags nz
void CPU::OP_21()
{
    uint16_t address = ((memory[memory[programCounter + 1] + registerX + 1] << 8u) + memory[memory[programCounter + 1] + registerX]) % 0x2000;
    registerA = registerA & memory[address];
    clearNZ();
    setNZ(registerA);
    programCounter += 2;
}

// AND [word[nn]+Y]: A = A AND [word[nn]+Y]. Flags nz
void CPU::OP_31()
{
    uint16_t address = (((memory[memory[programCounter + 1] + 1] << 8u) + memory[memory[programCounter + 1]]) + registerY) % 0x2000;
    registerA = registerA & memory[address];
    clearNZ();
    setNZ(registerA);
    programCounter += 2;
}


// Exclusive-OR memory with accumulator

// EOR #nn: A = A XOR nn. Flags nz
void CPU::OP_49()
{
    registerA = registerA ^ memory[programCounter + 1];
    clearNZ();
    setNZ(registerA);
    programCounter += 2;
}

// EOR [nn]: A = A XOR [nn]. Flags nz
void CPU::OP_45()
{
    registerA = registerA ^ memory[memory[programCounter + 1]];
    clearNZ();
    setNZ(registerA);
    programCounter += 2;
}

// EOR [nn+X]: A = A XOR [nn+X]. Flags nz
void CPU::OP_55()
{
    registerA = registerA ^ memory[memory[programCounter + 1] + registerX];
    clearNZ();
    setNZ(registerA);
    programCounter += 2;
}

// EOR [nnnn]: A = A XOR [nnnn]. Flags nz
void CPU::OP_4D()
{
    uint16_t address = ((memory[programCounter + 2] << 8u) + memory[programCounter + 1]) % 0x2000;
    registerA = registerA ^ memory[address];
    clearNZ();
    setNZ(registerA);
    programCounter += 3;
}

// EOR [nnnn+X]: A = A XOR [nnnn+X]. Flags nz
void CPU::OP_5D()
{
    uint16_t address = ((memory[programCounter + 2] << 8u) + memory[programCounter + 1] + registerX) % 0x2000;
    registerA = registerA ^ memory[address];
    clearNZ();
    setNZ(registerA);
    programCounter += 3;
}

// EOR [nnnn+Y]: A = A XOR [nnnn+Y]. Flags nz
void CPU::OP_59()
{
    uint16_t address = ((memory[programCounter + 2] << 8u) + memory[programCounter + 1] + registerY) % 0x2000;
    registerA = registerA ^ memory[address];
    clearNZ();
    setNZ(registerA);
    programCounter += 3;
}

// EOR #[word[nn+X]]: A = A XOR [word[nn+X]]. Flags nz
void CPU::OP_41()
{
    uint16_t address = ((memory[memory[programCounter + 1] + registerX + 1] << 8u) + memory[memory[programCounter + 1] + registerX]) % 0x2000;
    registerA = registerA ^ memory[address];
    clearNZ();
    setNZ(registerA);
    programCounter += 2;
}

// EOR [word[nn]+Y]: A = A XOR [word[nn]+Y]. Flags nz
void CPU::OP_51()
{
    uint16_t address = (((memory[memory[programCounter + 1] + 1] << 8u) + memory[memory[programCounter + 1]]) + registerY) % 0x2000;
    registerA = registerA ^ memory[address];
    clearNZ();
    setNZ(registerA);
    programCounter += 2;
}


// Logical OR memory with accumulator

// ORA #nn: A = A OR nn. Flags nz
void CPU::OP_09()
{
    registerA = registerA | memory[programCounter + 1];
    clearNZ();
    setNZ(registerA);
    programCounter += 2;
}

// ORA [nn]: A = A OR [nn]. Flags nz
void CPU::OP_05()
{
    registerA = registerA | memory[memory[programCounter + 1]];
    clearNZ();
    setNZ(registerA);
    programCounter += 2;
}

// ORA [nn+X]: A = A OR [nn+X]. Flags nz
void CPU::OP_15()
{
    registerA = registerA | memory[memory[programCounter + 1] + registerX];
    clearNZ();
    setNZ(registerA);
    programCounter += 2;
}

// ORA [nnnn]: A = A OR [nnnn]. Flags nz
void CPU::OP_0D()
{
    uint16_t address = ((memory[programCounter + 2] << 8u) + memory[programCounter + 1]) % 0x2000;
    registerA = registerA | memory[address];
    clearNZ();
    setNZ(registerA);
    programCounter += 3;
}

// ORA [nnnn+X]: A = A OR [nnnn+X]. Flags nz
void CPU::OP_1D()
{
    uint16_t address = ((memory[programCounter + 2] << 8u) + memory[programCounter + 1] + registerX) % 0x2000;
    registerA = registerA | memory[address];
    clearNZ();
    setNZ(registerA);
    programCounter += 3;
}

// ORA [nnnn+Y]: A = A OR [nnnn+Y]. Flags nz
void CPU::OP_19()
{
    uint16_t address = ((memory[programCounter + 2] << 8u) + memory[programCounter + 1] + registerY) % 0x2000;
    registerA = registerA | memory[address];
    clearNZ();
    setNZ(registerA);
    programCounter += 3;
}

// ORA [word[nn+X]]: A = A OR [word[nn+X]]. Flags nz
void CPU::OP_01()
{
    uint16_t address = ((memory[memory[programCounter + 1] + registerX + 1] << 8u) + memory[memory[programCounter + 1] + registerX]) % 0x2000;
    registerA = registerA | memory[address];
    clearNZ();
    setNZ(registerA);
    programCounter += 2;
}

// ORA [word[nn+X]]: A = A OR [word[nn]+Y]. Flags nz
void CPU::OP_11()
{
    uint16_t address = (((memory[memory[programCounter + 1] + 1] << 8u) + memory[memory[programCounter + 1]]) + registerY) % 0x2000;
    registerA = registerA | memory[address];
    clearNZ();
    setNZ(registerA);
    programCounter += 2;
}


// Compare

// CMP #nn: A-#nn. Flags ncz
void CPU::OP_C9()
{
    uint8_t value = registerA - memory[programCounter + 1];
    clearNZC();
    setCarry(registerA, memory[programCounter + 1]);
    setNZ(value);
    programCounter += 2;
}

// CMP [nn]: A-[nn]. Flags ncz
void CPU::OP_C5()
{
    uint8_t value = registerA - memory[memory[programCounter + 1]];
    clearNZC();
    setCarry(registerA, memory[memory[programCounter + 1]]);
    setNZ(value);
    programCounter += 2;
}

// CMP [nn+X]: A-[nn+X]. Flags ncz
void CPU::OP_D5()
{
    uint8_t value = registerA - memory[memory[programCounter + 1] + registerX];
    clearNZC();
    setCarry(registerA, memory[memory[programCounter + 1] + registerX]);
    setNZ(value);
    programCounter += 2;
}

// CMP [nnnn]: A-[nnnn]. Flags ncz
void CPU::OP_CD()
{
    uint16_t address = ((memory[programCounter + 2] << 8u) + memory[programCounter + 1]) % 0x2000;
    uint8_t value = registerA - memory[address];
    clearNZC();
    setCarry(registerA, memory[address]);
    setNZ(value);
    programCounter += 3;
}

// CMP [nnnn+X]: A-[nnnn+X]. Flags ncz
void CPU::OP_DD()
{
    uint16_t address = ((memory[programCounter + 2] << 8u) + memory[programCounter + 1] + registerX) % 0x2000;
    uint8_t value = registerA - memory[address];
    clearNZC();
    setCarry(registerA, memory[address]);
    setNZ(value);
    programCounter += 3;
}

// CMP [nnnn+Y]: A-[nnnn+Y]. Flags ncz
void CPU::OP_D9()
{
    uint16_t address = ((memory[programCounter + 2] << 8u) + memory[programCounter + 1] + registerY) % 0x2000;
    uint8_t value = registerA - memory[address];
    clearNZC();
    setCarry(registerA, memory[address]);
    setNZ(value);
    programCounter += 3;
}

// CMP [word[nn+X]]: A-[word[nn+X]]. Flags ncz
void CPU::OP_C1()
{
    uint16_t address = ((memory[memory[programCounter + 1] + registerX + 1] << 8u) + memory[memory[programCounter + 1] + registerX]) % 0x2000;
    uint8_t value = registerA - memory[address];
    clearNZC();
    setCarry(registerA, memory[address]);
    setNZ(value);
    programCounter += 2;
}

// CMP [word[nn]+Y]: A-[word[nn]+Y]. Flags ncz
void CPU::OP_D1()
{
    uint16_t address = (((memory[memory[programCounter + 1] + 1] << 8u) + memory[memory[programCounter + 1]]) + registerY) % 0x2000;
    uint8_t value = registerA - memory[address];
    clearNZC();
    setCarry(registerA, memory[address]);
    setNZ(value);
    programCounter += 2;
}

// CPX #nn: X-#nn. Flags ncz
void CPU::OP_E0()
{
    uint8_t value = registerX - memory[programCounter + 1];
    clearNZC();
    setCarry(registerX, memory[programCounter + 1]);
    setNZ(value);
    programCounter += 2;
}

// CPX [nn]: X-[nn]. Flags ncz
void CPU::OP_E4()
{
    uint8_t value = registerX - memory[memory[programCounter + 1]];
    clearNZC();
    setCarry(registerX, memory[memory[programCounter + 1]]);
    setNZ(value);
    programCounter += 2;
}

// CPX [nnnn]: X-[nnnn]. Flags ncz
void CPU::OP_EC()
{
    uint16_t address = ((memory[programCounter + 2] << 8u) + memory[programCounter + 1]) % 0x2000;
    uint8_t value = registerX - memory[address];
    clearNZC();
    setCarry(registerX, memory[address]);
    setNZ(value);
    programCounter += 3;
}

// CPY #nn: Y-#nn. Flags ncz
void CPU::OP_C0()
{
    uint8_t value = registerY - memory[programCounter + 1];
    clearNZC();
    setCarry(registerY, memory[programCounter + 1]);
    setNZ(value);
    programCounter += 2;
}

// CPY [nn]: Y-[nn]. Flags ncz
void CPU::OP_C4()
{
    uint8_t value = registerY - memory[memory[programCounter + 1]];
    clearNZC();
    setCarry(registerY, memory[memory[programCounter + 1]]);
    setNZ(value);
    programCounter += 2;
}

// CPY [nnnn]: X-[nnnn]. Flags ncz
void CPU::OP_CC()
{
    uint16_t address = ((memory[programCounter + 2] << 8u) + memory[programCounter + 1]) % 0x2000;
    uint8_t value = registerY - memory[address];
    clearNZC();
    setCarry(registerY, memory[address]);
    setNZ(value);
    programCounter += 3;
}


// Bit Test

// BIT [nn]: Flags are set so Z=((A AND [addr])=0x00), N=[addr].Bit7, V=[addr].Bit6. N and V not affected by A.
void CPU::OP_24()
{
    processStatusRegister &= 0b00111101;
    processStatusRegister |= (memory[memory[programCounter + 1]] & 0b11000000);
    processStatusRegister |= (!(registerA & memory[memory[programCounter + 1]]) << 1u);
    programCounter += 2;
}

// BIT [nnnn]: Flags are set so Z=((A AND [addr])=0x00), N=[addr].Bit7, V=[addr].Bit6. N and V not affected by A.
void CPU::OP_2C()
{
    uint16_t address = ((memory[programCounter + 2] << 8u) + memory[programCounter + 1]) % 0x2000;
    processStatusRegister &= 0b00111101;
    processStatusRegister |= (memory[address] & 0b11000000);
    processStatusRegister |= (!(registerA & memory[address]) << 1u);
    programCounter += 3;
}


// Increment by one

// INC [nn]: [nn]=[nn]+1. Flags NZ
void CPU::OP_E6()
{
    ++memory[programCounter + 1];
    clearNZ();
    setNZ(memory[programCounter + 1]);
    programCounter += 2;
}

// INC [nn+X]: [nn+X]=[nn+X]+1. Flags NZ
void CPU::OP_F6()
{
    ++memory[programCounter + 1 + registerX];
    clearNZ();
    setNZ(memory[programCounter + 1 + registerX]);
    programCounter += 2;
}

// INC [nnnn]: [nnnn]=[nnnn]+1. Flags NZ
void CPU::OP_EE()
{
    uint16_t address = ((memory[programCounter + 2] << 8u) + memory[programCounter + 1]) % 0x2000;
    ++memory[address];
    clearNZ();
    setNZ(memory[address]);
    programCounter += 3;
}

// INC [nnnn+X]: [nnnn+X]=[nnnn+X]+1. Flags NZ
void CPU::OP_FE()
{
    uint16_t address = ((memory[programCounter + 2] << 8u) + memory[programCounter + 1] + registerX) % 0x2000;
    ++memory[address];
    clearNZ();
    setNZ(memory[address]);
    programCounter += 3;
}

// INC X: X=X+1. FLags NZ
void CPU::OP_E8()
{
    ++registerX;
    clearNZ();
    setNZ(registerX);
    ++programCounter;
}

// INC Y: Y=Y+1. Flags NZ
void CPU::OP_C8()
{
    ++registerY;
    clearNZ();
    setNZ(registerY);
    ++programCounter;
}


// Decrement by one

// DEC [nn]: [nn]=[nn]-1. Flags NZ
void CPU::OP_C6()
{
    --memory[programCounter + 1];
    clearNZ();
    setNZ(memory[programCounter + 1]);
    programCounter += 2;
}

// DEC [nn+X]: [nn+X]=[nn+X]-1. Flags NZ
void CPU::OP_D6()
{
    --memory[programCounter + 1 + registerX];
    clearNZ();
    setNZ(memory[programCounter + 1 + registerX]);
    programCounter += 2;
}

// DEC [nnnn]: [nnnn]=[nnnn]-1. Flags NZ
void CPU::OP_CE()
{
    uint16_t address = ((memory[programCounter + 2] << 8u) + memory[programCounter + 1]) % 0x2000;
    --memory[address];
    clearNZ();
    setNZ(memory[address]);
    programCounter += 3;
}

// DEC [nnnn+X]: [nnnn+X]=[nnnn+X]-1. Flags NZ
void CPU::OP_DE()
{
    uint16_t address = ((memory[programCounter + 2] << 8u) + memory[programCounter + 1] + registerX) % 0x2000;
    --memory[address];
    clearNZ();
    setNZ(memory[address]);
    programCounter += 3;
}

// DEC X: X=X-1. Flags NZ
void CPU::OP_CA()
{
    --registerX;
    clearNZ();
    setNZ(registerX);
    ++programCounter;
}

// DEC Y: Y=Y-1. FLags NZ
void CPU::OP_88()
{
    --registerY;
    clearNZ();
    setNZ(registerY);
    ++programCounter;
}



// CPU Rotate and Shift instructions

// Shift Left Logical/Arithmetic

// SHL A: Shift left A. Flags NCZ
void CPU::OP_0A()
{
    clearNZC();
    processStatusRegister |= ((registerA & 0b10000000) >> 7u);
    registerA <<= 1u;
    setNZ(registerA);
    ++programCounter;
}

// SHL [nn]: Shift left [nn]. Flags NCZ
void CPU::OP_06()
{
    clearNZC();
    processStatusRegister |= ((memory[programCounter + 1] & 0b10000000) >> 7u);
    memory[programCounter + 1] <<= 1u;
    setNZ(memory[programCounter + 1]);
    programCounter += 2;
}

// SHL [nn+X]: Shift left [nn+X]. Flags NCZ
void CPU::OP_16()
{
    clearNZC();
    processStatusRegister |= ((memory[programCounter + 1 + registerX] & 0b10000000) >> 7u);
    memory[programCounter + 1 + registerX] <<= 1u;
    setNZ(memory[programCounter + 1 + registerX]);
    programCounter += 2;
}

// SHL [nnnn]: Shift left [nnnn]. Flags NCZ
void CPU::OP_0E()
{
    uint16_t address = ((memory[programCounter + 2] << 8u) + memory[programCounter + 1]) % 0x2000;
    clearNZC();
    processStatusRegister |= ((memory[address] & 0b10000000) >> 7u);
    memory[address] <<= 1u;
    setNZ(memory[address]);
    programCounter += 3;
}

// SHL [nnnn+X]: Shift left [nnnn+X]. Flags NCZ
void CPU::OP_1E()
{
    uint16_t address = ((memory[programCounter + 2] << 8u) + memory[programCounter + 1] + registerX) % 0x2000;
    clearNZC();
    processStatusRegister |= ((memory[address] & 0b10000000) >> 7u);
    memory[address] <<= 1u;
    setNZ(memory[address]);
    programCounter += 3;
}


// Shift Right Logical

// SHR A: Shift right A. Flags NCZ
void CPU::OP_4A()
{
    clearNZC();
    processStatusRegister |= (registerA & 0b00000001);
    registerA >>= 1u;
    setNZ(registerA);
    ++programCounter;
}

// SHR [nn]: Shift right [nn]. Flags NCZ
void CPU::OP_46()
{
    clearNZC();
    processStatusRegister |= (memory[programCounter + 1] & 0b00000001);
    memory[programCounter + 1] >>= 1u;
    setNZ(memory[programCounter + 1]);
    programCounter += 2;
}

// SHR [nn+X]: Shift right [nn+X]. Flags NCZ
void CPU::OP_56()
{
    clearNZC();
    processStatusRegister |= (memory[programCounter + 1 + registerX] & 0b00000001);
    memory[programCounter + 1 + registerX] >>= 1u;
    setNZ(memory[programCounter + 1 + registerX]);
    programCounter += 2;
}

// SHR [nnnn]: Shift right [nnnn]. Flags NCZ
void CPU::OP_4E()
{
    uint16_t address = ((memory[programCounter + 2] << 8u) + memory[programCounter + 1]) % 0x2000;
    clearNZC();
    processStatusRegister |= (memory[address] & 0b00000001);
    memory[address] >>= 1u;
    setNZ(memory[address]);
    programCounter += 3;
}

// SHR [nnnn+X]: Shift right [nnnn+X]. Flags NCZ
void CPU::OP_5E()
{
    uint16_t address = ((memory[programCounter + 2] << 8u) + memory[programCounter + 1] + registerX) % 0x2000;
    clearNZC();
    processStatusRegister |= (memory[address] & 0b00000001);
    memory[address] >>= 1u;
    setNZ(memory[address]);
    programCounter += 3;
}


// Rotate Left through Carry

// RCL A: Rotate A Left Through Carry. Flags NZC
void CPU::OP_2A()
{
    uint8_t storeCarry = (processStatusRegister & 0b00000001);
    clearNZC();
    processStatusRegister |= ((registerA & 0b10000000) >> 7u);
    registerA <<= 1u;
    registerA |= storeCarry;
    setNZ(registerA);
    ++programCounter;
}

// RCL [nn]: Rotate [nn] Left Through Carry. Flags NZC
void CPU::OP_26()
{
    uint8_t storeCarry = (processStatusRegister & 0b00000001);
    clearNZC();
    processStatusRegister |= ((memory[programCounter + 1] & 0b10000000) >> 7u);
    memory[programCounter + 1] <<= 1u;
    registerA |= storeCarry;
    setNZ(memory[programCounter + 1]);
    programCounter += 2;
}

// RCL [nn+X]: Rotate [nn+X] Left Through Carry. Flags NZC
void CPU::OP_36()
{
    uint8_t storeCarry = (processStatusRegister & 0b00000001);
    clearNZC();
    processStatusRegister |= ((memory[programCounter + 1 + registerX] & 0b10000000) >> 7u);
    memory[programCounter + 1 + registerX] <<= 1u;
    registerA |= storeCarry;
    setNZ(memory[programCounter + 1 + registerX]);
    programCounter += 2;
}

// RCL [nnnn]: Rotate [nnnn] Left Through Carry. Flags NZC
void CPU::OP_2E()
{
    uint8_t storeCarry = (processStatusRegister & 0b00000001);
    uint16_t address = ((memory[programCounter + 2] << 8u) + memory[programCounter + 1]) % 0x2000;
    clearNZC();
    processStatusRegister |= ((memory[address] & 0b10000000) >> 7u);
    memory[address] <<= 1u;
    registerA |= storeCarry;
    setNZ(memory[address]);
    programCounter += 3;
}

// RCL [nnnn+X]: Rotate [nnnn+X] Left Through Carry. Flags NZC
void CPU::OP_3E()
{
    uint8_t storeCarry = (processStatusRegister & 0b00000001);
    uint16_t address = ((memory[programCounter + 2] << 8u) + memory[programCounter + 1] + registerX) % 0x2000;
    clearNZC();
    processStatusRegister |= ((memory[address] & 0b10000000) >> 7u);
    memory[address] <<= 1u;
    registerA |= storeCarry;
    setNZ(memory[address]);
    programCounter += 3;
}

// Rotate Right Through Carry

// RCR A: Rotate A Right Through Carry. Flags NZC
void CPU::OP_6A()
{
    uint8_t storeCarry = (processStatusRegister & 0b00000001);
    clearNZC();
    processStatusRegister |= (registerA & 0b00000001);
    registerA >>= 1u;
    registerA |= (storeCarry << 7u);
    setNZ(registerA);
    ++programCounter;
}

// RCR [nn]: Rotate [nn] Right Through Carry. Flags NZC
void CPU::OP_66()
{
    uint8_t storeCarry = (processStatusRegister & 0b00000001);
    clearNZC();
    processStatusRegister |= (memory[programCounter + 1] & 0b00000001);
    memory[programCounter + 1] >>= 1u;
    registerA |= (storeCarry << 7u);
    setNZ(memory[programCounter + 1]);
    programCounter += 2;
}

// RCR [nn+X]: Rotate [nn+X] Right Through Carry. Flags NZC
void CPU::OP_76()
{
    uint8_t storeCarry = (processStatusRegister & 0b00000001);
    clearNZC();
    processStatusRegister |= (memory[programCounter + 1 + registerX] & 0b00000001);
    memory[programCounter + 1 + registerX] >>= 1u;
    registerA |= (storeCarry << 7u);
    setNZ(memory[programCounter + 1 + registerX]);
    programCounter += 2;
}

// RCR [nnnn]: Rotate [nnnn] Right Through Carry. Flags NZC
void CPU::OP_6E()
{
    uint8_t storeCarry = (processStatusRegister & 0b00000001);
    uint16_t address = ((memory[programCounter + 2] << 8u) + memory[programCounter + 1]) % 0x2000;
    clearNZC();
    processStatusRegister |= (memory[address] & 0b00000001);
    memory[address] >>= 1u;
    registerA |= (storeCarry << 7u);
    setNZ(memory[address]);
    programCounter += 3;
}

// RCR [nnnn+X]: Rotate [nnnn+X] Right Through Carry. Flags NZC
void CPU::OP_7E()
{
    uint8_t storeCarry = (processStatusRegister & 0b00000001);
    uint16_t address = ((memory[programCounter + 2] << 8u) + memory[programCounter + 1] + registerX) % 0x2000;
    clearNZC();
    processStatusRegister |= (memory[address] & 0b00000001);
    memory[address] >>= 1u;
    registerA |= (storeCarry << 7u);
    setNZ(memory[address]);
    programCounter += 3;
}


// CPU Jump and Control Instructions

// Normal Jumps & Subroutine Calls/Returns

// JMP nnnn: Program Counter = nnnn. No Flags
void CPU::OP_4C()
{
    uint16_t address = ((memory[programCounter + 2] << 8u) + memory[programCounter + 1]) % 0x2000;
    programCounter = address;
}

// JMP [nnnn]: Program Counter = WORD[nnnn]
void CPU::OP_6C()
{
    uint16_t address = ((memory[programCounter + 2] << 8u) + memory[programCounter + 1]) % 0x2000;
    // This is done because of a glitch in the 6502 that does not let JMP [nnnn] cross page boundaries.
    if (memory[address] == 0xFF) 
    {
        programCounter = ((memory[address + 1 - 0x100] << 8u) + memory[address]) % 0x2000;
    }
    else
    {
        programCounter = ((memory[address + 1] << 8u) + memory[address]) % 0x2000;
    }
    
}

// CALL nnnn: Set memory at stack pointer to program counter + 2, set program counter to nnnn. No Flags
void CPU::OP_20()
{
    uint16_t address = ((memory[programCounter + 2] << 8u) + memory[programCounter + 1]) % 0x2000;
    memory[stackPointer] = programCounter >> 8u;
    --stackPointer;
    memory[stackPointer] = programCounter + 2;
    --stackPointer;
    programCounter = address;
}

// RETI: Return from BRK/IRQ/NMI. All Flags (Except Break and Unused Flags)
void CPU::OP_40()
{
    processStatusRegister &= 0b00110000;
    processStatusRegister |= (memory[stackPointer] & 0b11001111);
    ++stackPointer;
    programCounter = memory[stackPointer] << 8u;
    ++stackPointer;
    programCounter += memory[stackPointer];
}

// RET: Return from CALL. No Flags
void CPU::OP_60()
{
    ++stackPointer;
    programCounter = memory[stackPointer] << 8u;
    ++stackPointer;
    programCounter = memory[stackPointer] + 1;
}



// Conditional Branches (conditional jump to PC=PC+/-dd)

// BPL dd: Brach to PC+/-dd if N=0. No Flags
void CPU::OP_10()
{
    if ((processStatusRegister & 0b10000000) == 0x00)
    {
        int8_t newPC = programCounter + memory[programCounter + 1];
        programCounter = newPC;
    }
    else
    {
        programCounter += 2;
    }
}

// BMI dd: Brach to PC+/-dd if N=1. No Flags
void CPU::OP_30()
{
    if ((processStatusRegister & 0b10000000) == 0x80)
    {
        int8_t newPC = programCounter + memory[programCounter + 1];
        programCounter = newPC;
    }
    else
    {
        programCounter += 2;
    }
}

// BVC dd: Brach to PC+/-dd if V=0. No Flags
void CPU::OP_50()
{
    if ((processStatusRegister & 0b01000000) == 0x00)
    {
        int8_t newPC = programCounter + memory[programCounter + 1];
        programCounter = newPC;
    }
    else
    {
        programCounter += 2;
    }
}

// BVS dd: Brach to PC+/-dd if V=1. No Flags
void CPU::OP_70()
{
    if ((processStatusRegister & 0b01000000) == 0x40)
    {
        int8_t newPC = programCounter + memory[programCounter + 1];
        programCounter = newPC;
    }
    else
    {
        programCounter += 2;
    }
}

// BCC/BLT dd: Brach to PC+/-dd if C=0. No Flags
void CPU::OP_90()
{
    if ((processStatusRegister & 0b00000001) == 0x00)
    {
        int8_t newPC = programCounter + memory[programCounter + 1];
        programCounter = newPC;
    }
    else
    {
        programCounter += 2;
    }
}

// BCS/BGE dd: Brach to PC+/-dd if C=1. No Flags
void CPU::OP_B0()
{
    if ((processStatusRegister & 0b00000001) == 0x01)
    {
        int8_t newPC = programCounter + memory[programCounter + 1];
        programCounter = newPC;
    }
    else
    {
        programCounter += 2;
    }
}

// BNE/BZC dd: Brach to PC+/-dd if Z=0. No Flags
void CPU::OP_D0()
{
    if ((processStatusRegister & 0b00000010) == 0x00)
    {
        int8_t newPC = programCounter + memory[programCounter + 1];
        programCounter = newPC;
    }
    else
    {
        programCounter += 2;
    }
}

// BEQ/BZS dd: Brach to PC+/-dd if Z=1. No Flags
void CPU::OP_F0()
{
        if ((processStatusRegister & 0b00000010) == 0x02)
    {
        int8_t newPC = programCounter + memory[programCounter + 1];
        programCounter = newPC;
    }
    else
    {
        programCounter += 2;
    }
}


// Interrupts, Exceptions, Breakpoints

// BRK: Force Break. Sets B=1, [S]=PC+1
void CPU::OP_00()
{

}

// /IRQ: Interrupt. 
void CPU::interrupt()
{

}             
void CPU::nmi()
{

}             
void CPU::reset()
{

}            

// CPU Control
void CPU::OP_18(){}
void CPU::OP_58(){}
void CPU::OP_D8(){}
void CPU::OP_B8(){}
void CPU::OP_38(){}
void CPU::OP_78(){}
void CPU::OP_F8(){}

// No Operation
void CPU::OP_EA(){}

 // CPU Illegal Opcodes

// SAX and LAX
void CPU::OP_87(){}
void CPU::OP_97(){}
void CPU::OP_8F(){}
void CPU::OP_83(){}
void CPU::OP_A7(){}
void CPU::OP_B7(){}
void CPU::OP_AF(){}
void CPU::OP_A3(){}
void CPU::OP_B3(){}

// Combined ALU-opcodes

// ???????????????????????????????

// Other Illegal Opcodes

void CPU::OP_0B(){}
void CPU::OP_2B(){}
void CPU::OP_4B(){}
void CPU::OP_6B(){}
void CPU::OP_CB(){}
void CPU::OP_EB(){}
void CPU::OP_BB(){}


// NUL/NOP and KIL/JAM/HLT

// TODO


// Unstable Illegal Opcodes
void CPU::OP_8B(){}
void CPU::OP_AB(){}
void CPU::OP_BF(){}
void CPU::OP_93(){}
void CPU::OP_9F(){}
void CPU::OP_9C(){}
void CPU::OP_9E(){}
void CPU::OP_9B(){}

// set carry bit ** For CMP plug memory into tempRegister **
inline void CPU::setCarry(uint8_t &reg, uint8_t &tempRegister)
{
    if(tempRegister < reg)
    {
        processStatusRegister |= 0b00000001;
    }
}

inline void CPU::setCarryDecimalAdd(int result)
{
    if (result > 99)
    {
        processStatusRegister |= 0b00000001;
    }
}

inline void CPU::setCarryDecimalSub(int result)
{
    if (result >= 0)
    {
        processStatusRegister |= 0b00000001;
    }
}

// set overflow bits
inline void CPU::setOverflow(uint8_t &reg, uint8_t &adderValue, uint8_t &tempRegister)
{
    if(((reg & 0b10000000) == (adderValue & 0b10000000)) && ((reg & 0b10000000) != (tempRegister & 0b10000000)))
    {
        processStatusRegister |= 0b01000000;
    }
}

// Set Negative and Zero Bits
inline void CPU::setNZ(uint8_t &reg)
{
    // Set zero bit if destination is zero.
    if (reg == 0)
    {
        processStatusRegister |= 0b00000010;
    }  
    // Set negative bit equal to destinations most significant bit
    processStatusRegister |= (reg & 0b10000000);
}


// There are setup to save cycles on operations that set more than one flag.
// All Ops that set N also set Z. All Ops that set C also set NZ. All ops that set V also set NZC.
// Anything else is handled directly in op code. 
inline void CPU::clearNZ()
{
    // Clear Negative and Zero Bits
    processStatusRegister &= 0b01111101;
};

inline void CPU::clearNZC()
{
    // Clear Negative, Zero, and Carry Bits
    processStatusRegister &= 0b01111100;
};

inline void CPU::clearNZCV()
{
    // Clear Negative, Zero, Carry, and Overflow Bits
    processStatusRegister &= 0b00111100;
};

void CPU::resetState()
{
    registerA = 0x00;                  
    registerX = 0x00;                  
    registerY = 0x00;                
    programCounter = 0x0000;         
    stackPointer = 0xFF;  
    processStatusRegister = 0x20;
    for (int i = 0; i < 8192; i++)
    {
        memory[i] = 0x00;
    }

}


void CPU::reportStatus()
{
    ios_base::fmtflags f(cout.flags());
    cout << '\n';
    cout << "Register A:\t\t0x";
    cout << hex << setw(2) << setfill('0') << uppercase << static_cast<int>(registerA) << "\t\t\t";
    cout.flags(f);
    cout << "Register X:\t\t0x";
    cout << hex << setw(2) << setfill('0') << uppercase << static_cast<int>(registerX) << "\t\t\t";
    cout.flags(f);
    cout << "Register Y:\t\t0x";
    cout << hex << setw(2) << setfill('0') << uppercase << static_cast<int>(registerY) << endl;
    cout.flags(f);
    cout << "Program Counter:\t0x";
    cout << hex << setw(4) << setfill('0') << uppercase << static_cast<int>(programCounter) << "\t\t\t";
    cout.flags(f);
    cout << "Stack Pointer:\t\t0x";
    cout << hex << setw(2) << setfill('0') << uppercase << static_cast<int>(stackPointer) << "\t\t\t";
    cout.flags(f);
    cout << "PSR:\t\t\t0b" << bitset<8>(processStatusRegister) << endl;
    cout.flags(f);
    for (int i = 0; i < 8192; i++)
    {
        if (memory[i] != 0x00)
        {
            cout << "Memory[";
            cout << hex << setw(4) << setfill('0') << uppercase << static_cast<int>(i) << "]: 0x" << setw(2) << static_cast<int>(memory[i]) << endl;
        }
    }
    cout << '\n';
    
}


void CPU::setMemory(uint16_t address, uint8_t value)
{
    memory[address%0x2000] = value;
}

uint16_t CPU::readMemory(uint16_t address)
{
    return memory[address];
}




