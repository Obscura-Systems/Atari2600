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

    // *** TEMPORARY CODE FOR TESTING INDIVIDUAL OPCODES ***


    registerA = 0xFA;
    registerX = 0x00;
    registerY = 0x08;

    memory[0xF000 % 0x2000] = 0xb1;
    memory[0xF001 % 0x2000] = 0x6A;
    memory[0x006A % 0x2000] = 0x70;
    memory[0x006B % 0x2000] = 0x42;
    memory[0x704A % 0x2000] = 0x11;


    // To reset format flags? idfk i forgor
    ios_base::fmtflags f(cout.flags());

    cout << "State prior to opcode: \n";
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
    cout << "Memory at 0x0748:\t0x";
    cout << hex << setw(2) << setfill('0') << uppercase << static_cast<int>(memory[0x4748 % 0x2000]) << endl << '\n';

    ((*this).*(opList[memory[programCounter]]))();

    cout << "State after opcode: \n";
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
    cout << "Memory at 0x0748:\t0x";
    cout << hex << setw(2) << setfill('0') << uppercase << static_cast<int>(memory[0x4748 % 0x2000]) << endl;
    
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
    setNZ(registerY);
    ++programCounter;
}

// TAX: Move Register A into Register X. Flags NZ
void CPU::OP_AA()                           
{
    registerX = registerA;
    setNZ(registerX);
    ++programCounter;
}

// TSX: Move Stack Pointer into Register X. Flags NZ
void CPU::OP_BA()
{
    registerX = stackPointer;
    setNZ(registerX);
    ++programCounter;
}

// TYA: Move Register Y into Register A. Flags Nz
void CPU::OP_98()
{
    registerA = registerY;
    setNZ(registerA);
    ++programCounter;
}

// TXA: Move Register X into Register A. Flags NZ
void CPU::OP_8A()
{
    registerA = registerX;
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
    setNZ(registerA);
    programCounter += 2;
}

// LDX #nn: Load next byte into Register X. Flags NZ
void CPU::OP_A2()
{
    registerX = memory[programCounter + 1];
    setNZ(registerX);
    programCounter += 2;
}

// LDY #nn: Load next byte into Register Y. Flags NZ
void CPU::OP_A0()
{
    registerY = memory[programCounter + 1];
    setNZ(registerY);
    programCounter += 2;
}


// Load Register From Memory

// LDA nn: Load byte at nn into Register A. Flags NZ
void CPU::OP_A5()
{
    registerA = memory[memory[programCounter + 1]];
    setNZ(registerA);
    programCounter += 2;
}

// LDA nn,X: Load byte at nn+X into register A. Flags NZ
void CPU::OP_B5()
{
    registerA = memory[memory[programCounter + 1] + registerX];
    setNZ(registerA);
    programCounter += 2;
}

// LDA nnnn: Load byte at nnnn into Register A. Flag NZ
void CPU::OP_AD()
{
    uint16_t address = (memory[programCounter + 1] << 8u) + memory[programCounter + 2];
    registerA = memory[address % 0x2000];
    setNZ(registerA);
    programCounter += 3;
}

// LDA nnnn+X: Load byte at nnnn+X into register A. Flags NZ
void CPU::OP_BD()
{
    uint16_t address = (memory[programCounter + 1] << 8u) + memory[programCounter + 2] + registerX;
    registerA = memory[address % 0x2000];
    setNZ(registerA);
    programCounter += 3;
}

// LDA nnnn+Y: Load byte at nnnn+Y into register A. Flags NZ
void CPU::OP_B9()
{
    uint16_t address = (memory[programCounter + 1] << 8u) + memory[programCounter + 2] + registerY;
    registerA = memory[address % 0x2000];
    setNZ(registerA);
    programCounter += 3;
}

// LDA (nn,X): Load byte at WORD at nn+X into Register A. Flags NZ
void CPU::OP_A1()
{
    uint16_t address = (memory[memory[programCounter + 1] + registerX] << 8u) + memory[memory[programCounter + 1] + registerX + 1];
    registerA = memory[address % 0x2000];
    setNZ(registerA);
    programCounter += 2;
}

// LDA (nn),Y: Load byte at (WORD at nn)+Y into Register A. Flags NZ
void CPU::OP_B1()
{
    uint16_t address = (memory[memory[programCounter + 1]] << 8u) + memory[memory[programCounter + 1] + 1];
    registerA = memory[(address + registerY) % 0x2000];
    setNZ(registerA);
    programCounter += 2;
}

// LDX nn: Load byte at nn into Register X. Flags NZ
void CPU::OP_A6()
{
    registerX = memory[memory[programCounter + 1]];
    setNZ(registerX);
    programCounter += 2;
}

// LDX nn+Y: Load byte at nn+Y into register X. Flags NZ
void CPU::OP_B6()
{
    registerX = memory[memory[programCounter + 1] + registerY];
    setNZ(registerX);
    programCounter += 2;
}

// LDX nnnn: Loacd byte at nnnn into Register X. Flags NZ
void CPU::OP_AE()
{
    uint16_t address = (memory[programCounter + 1] << 8u) + memory[programCounter + 2];
    registerX = memory[address % 0x2000];
    setNZ(registerX);
    programCounter += 3;
}

// LDX nnnn+Y: Load byte at nnnn+Y into Register X. Flags NZ
void CPU::OP_BE()
{
    uint16_t address = ((memory[programCounter + 1] << 8u) + memory[programCounter + 2]) + registerY;
    registerX = memory[address % 0x2000];
    setNZ(registerX);
    programCounter += 3;
}

// LDY nn: Load byte at nn into Register Y. Flags NZ
void CPU::OP_A4()
{
    registerY = memory[memory[programCounter + 1]];
    setNZ(registerY);
    programCounter += 2;
}

// LDY nn+X: Load byte at nn+X into Registewr Y. Flags NZ
void CPU::OP_B4()
{
    registerY = memory[memory[programCounter + 1] + registerX];
    setNZ(registerY);
    programCounter += 2;
}

// LDY nnnn: Load byte at nnnn into register Y. Flags NZ
void CPU::OP_AC()
{
    uint16_t address = (memory[programCounter + 1] << 8u) + memory[programCounter + 2];
    registerY = memory[address % 0x2000];
    setNZ(registerY);
    programCounter += 3;
}

// LDY nnnn+X: Load byte at nnnn+X into Register Y. Flags NZ
void CPU::OP_BC()
{
    uint16_t address = ((memory[programCounter + 1] << 8u) + memory[programCounter + 2]) + registerX;
    registerY = memory[address % 0x2000];
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
    uint16_t address = (memory[programCounter + 1] << 8u) + memory[programCounter + 2];
    memory[address % 0x2000] = registerA;
    programCounter += 3;
}

// STA nnnn,X: Move byte from register A into nnnn+X. No Flags
void CPU::OP_9D()
{
    uint16_t address = ((memory[programCounter + 1] << 8u) + memory[programCounter + 2]) + registerX;
    memory[address % 0x2000] = registerA;
    programCounter += 3;
}

// STA nnnn,Y: Move byte from register A into nnnn+Y. No Flags
void CPU::OP_99()
{
    uint16_t address = ((memory[programCounter + 1] << 8u) + memory[programCounter + 2]) + registerY;
    memory[address % 0x2000] = registerA;
    programCounter += 3;
}

// STA (nn,X): Move byte from register A into (WORD(nn+X)). No flags
void CPU::OP_81()
{
    uint16_t address = (memory[memory[programCounter + 1] + registerX] << 8u) + memory[memory[programCounter + 1] + registerX + 1];
    memory[address % 0x2000] = registerA;
    programCounter += 2;
}

// STA (nn),Y: Move byte from regiater A into (WORD(nn)+Y). No flags
void CPU::OP_91()
{
    uint16_t address = (memory[memory[programCounter + 1]] << 8u) + memory[memory[programCounter + 1] + 1];
    memory[address + registerY % 0x2000] = registerA;
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
    uint16_t address = (memory[programCounter + 1] << 8u) + memory[programCounter + 2];
    memory[address % 0x2000] = registerX;
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
    uint16_t address = (memory[programCounter + 1] << 8u) + memory[programCounter + 2];
    memory[address % 0x2000] = registerY;
    programCounter += 3;
}


// Push/Pull  *** Stack pointer needs 0x0100 added prior to use to address correct space in memory ***

// PHA: Push A. No Flags
void CPU::OP_48()
{
    uint16_t address = stackPointer + 0x0100;
    memory[address % 0x2000] = registerA;
    --stackPointer;
    ++programCounter;
}

// PHP: Push P. Writes 1 to B and unused flags.
void CPU::OP_08()
{
    uint16_t address = stackPointer + 0x0100;
    memory[address % 0x2000] = processStatusRegister;
    processStatusRegister = processStatusRegister | 0b00110000;
    --stackPointer;
    ++programCounter;
}

// PLA: Pop A. Flags NZ
void CPU::OP_68()
{
    ++stackPointer;
    uint16_t address = stackPointer + 0x0100;
    registerA = memory[address % 0x2000];
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
    uint8_t maskedMemory = memory[address % 0x2000] & 0b11001111;
    processStatusRegister = maskedProcessRegister | maskedMemory;
    ++programCounter;    
}


// TESTED TO HERE *************************


// CPU Arithmetic/Logical Operations

// Add memory to accumulator with carry

// ADC #nn: Add nn and Carry to Accumulator. Flags nzcv
void CPU::OP_69()
{
    uint8_t adder = memory[programCounter + 1] + (processStatusRegister & 0b00000001);
    uint16_t tempA = registerA + adder;   
    setCarry(tempA);
    setOverflow(registerA, adder, tempA);
    registerA = tempA & 0xFF;
    setNZ(registerA);
    programCounter += 2;
}

// ADC nn: Add [nn] and carry to Accumulator. Flags nzcv
void CPU::OP_65()
{
    uint8_t adder = memory[memory[programCounter + 1]] + (processStatusRegister & 0b00000001);
    uint16_t tempA = registerA + adder;   
    setCarry(tempA);
    setOverflow(registerA, adder, tempA);
    registerA = tempA & 0xFF;
    setNZ(registerA);
    programCounter += 2;
}

// ADC nn,X: Add [nn+X] and carry to Accumulator. Flags nzcv
void CPU::OP_75()
{
    uint8_t adder = memory[memory[programCounter + 1] + registerX] + (processStatusRegister & 0b00000001);
    uint16_t tempA = registerA + adder;   
    setCarry(tempA);
    setOverflow(registerA, adder, tempA);
    registerA = tempA & 0xFF;
    setNZ(registerA);
    programCounter += 2;
}

// ADC nnnn: Add [nnnn] and carry to Accumulator. Flags nzcv
void CPU::OP_6D()
{
    uint16_t address = (memory[programCounter + 1] << 8u) + memory[programCounter + 2];
    uint8_t adder = memory[address] + (processStatusRegister & 0b00000001);
    uint16_t tempA = registerA + adder;   
    setCarry(tempA);
    setOverflow(registerA, adder, tempA);
    registerA = tempA & 0xFF;
    setNZ(registerA);
    programCounter += 3;
}

// ADC nnnn+X: Add [nnnn+X] and carry to Accumulator. Flags nzcv
void CPU::OP_7D()
{
    uint16_t address = ((memory[programCounter + 1] << 8u) + memory[programCounter + 2]) + registerX;
    uint8_t adder = memory[address] + (processStatusRegister & 0b00000001);
    uint16_t tempA = registerA + adder;   
    setCarry(tempA);
    setOverflow(registerA, adder, tempA);
    registerA = tempA & 0xFF;
    setNZ(registerA);
    programCounter += 3;
}

// ADC nnnn+Y: Add [nnnn+Y] and carry to Accumulator. Flags nzcv
void CPU::OP_79()
{
    uint16_t address = ((memory[programCounter + 1] << 8u) + memory[programCounter + 2]) + registerY;
    uint8_t adder = memory[address] + (processStatusRegister & 0b00000001);
    uint16_t tempA = registerA + adder;   
    setCarry(tempA);
    setOverflow(registerA, adder, tempA);
    registerA = tempA & 0xFF;
    setNZ(registerA);
    programCounter += 3;
}

// ADC [[nn+X]]: Add [word[nn+X]] and carry to Accumulator. Flags nzcv
void CPU::OP_61()
{
    uint16_t address = (memory[memory[programCounter + 1] + registerX] << 8u) + memory[memory[programCounter + 1] + registerX + 1];
    uint8_t adder = memory[address] + (processStatusRegister & 0b00000001);
    uint16_t tempA = registerA + adder;   
    setCarry(tempA);
    setOverflow(registerA, adder, tempA);
    registerA = tempA & 0xFF;
    setNZ(registerA);
    programCounter += 2;
}

// ADC [[nn]+Y]: Add [word[nn]+Y] and carry to Accumulator. Flags nzcv
void CPU::OP_71()
{
    uint16_t address = (memory[memory[programCounter + 1]] << 8u) + memory[memory[programCounter + 1] + 1];
    uint8_t adder = memory[address + registerY] + (processStatusRegister & 0b00000001);
    uint16_t tempA = registerA + adder;   
    setCarry(tempA);
    setOverflow(registerA, adder, tempA);
    registerA = tempA & 0xFF;
    setNZ(registerA);
    programCounter += 2;
}

// Subtract memory from accumulator with borrow
void CPU::OP_E9(){}
void CPU::OP_E5(){}
void CPU::OP_F5(){}
void CPU::OP_ED(){}
void CPU::OP_FD(){}
void CPU::OP_F9(){}
void CPU::OP_E1(){}
void CPU::OP_F1(){}

// Logical AND memory with accumulator
void CPU::OP_29(){}
void CPU::OP_25(){}
void CPU::OP_35(){}
void CPU::OP_2D(){}
void CPU::OP_3D(){}
void CPU::OP_39(){}
void CPU::OP_21(){}
void CPU::OP_31(){}

// Exclusive-OR memory with accumulator
void CPU::OP_49(){}
void CPU::OP_45(){}
void CPU::OP_55(){}
void CPU::OP_4D(){}
void CPU::OP_5D(){}
void CPU::OP_59(){}
void CPU::OP_41(){}
void CPU::OP_51(){}

// Logical OR memory with accumulator
void CPU::OP_09(){}
void CPU::OP_05(){}
void CPU::OP_15(){}
void CPU::OP_0D(){}
void CPU::OP_1D(){}
void CPU::OP_19(){}
void CPU::OP_01(){}
void CPU::OP_11(){}

// Compare
void CPU::OP_C9(){}
void CPU::OP_C5(){}
void CPU::OP_D5(){}
void CPU::OP_CD(){}
void CPU::OP_DD(){}
void CPU::OP_D9(){}
void CPU::OP_C1(){}
void CPU::OP_D1(){}
void CPU::OP_E0(){}
void CPU::OP_E4(){}
void CPU::OP_EC(){}
void CPU::OP_C0(){}
void CPU::OP_C4(){}
void CPU::OP_CC(){}

// Bit Test
void CPU::OP_24(){}
void CPU::OP_2C(){}

// Increment by one
void CPU::OP_E6(){}
void CPU::OP_F6(){}
void CPU::OP_EE(){}
void CPU::OP_FE(){}
void CPU::OP_E8(){}
void CPU::OP_C8(){}

// Decrement by one
void CPU::OP_C6(){}
void CPU::OP_D6(){}
void CPU::OP_CE(){}
void CPU::OP_DE(){}
void CPU::OP_CA(){}
void CPU::OP_88(){}


// CPU Rotate and Shift instructions

// Shift Left Logical/Arithmetic
void CPU::OP_0A(){}
void CPU::OP_06(){}
void CPU::OP_16(){}
void CPU::OP_0E(){}
void CPU::OP_1E(){}

// Shift Right Logical
void CPU::OP_4A(){}
void CPU::OP_46(){}
void CPU::OP_56(){}
void CPU::OP_4E(){}
void CPU::OP_5E(){}

// Rotate Left through Carry
void CPU::OP_2A(){}
void CPU::OP_26(){}
void CPU::OP_36(){}
void CPU::OP_2E(){}
void CPU::OP_3E(){}

// Rotate Right Through Carry
void CPU::OP_6A(){}
void CPU::OP_66(){}
void CPU::OP_76(){}
void CPU::OP_6E(){}
void CPU::OP_7E(){}


// CPU Jump and Control Instructions

// Normal Jumps & Subroutine Calls/Returns
void CPU::OP_4C(){}
void CPU::OP_6C(){}
void CPU::OP_20(){}
void CPU::OP_40(){}
void CPU::OP_60(){}

// Conditional Branches (conditional jump to PC=PC+/-dd)
void CPU::OP_10(){}
void CPU::OP_30(){}
void CPU::OP_50(){}
void CPU::OP_70(){}
void CPU::OP_90(){}
void CPU::OP_B0(){}
void CPU::OP_D0(){}
void CPU::OP_F0(){}

// Interrupts, Exceptions, Breakpoints
void CPU::OP_00(){}       // FORCE BREAK
//void DUMMY();     // INTERRUPT
//void DUMMY();     // NMI
//void DUMMY();     // RESET

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

// Clear and set carry bit
void CPU::setCarry(uint16_t &tempRegister)
{
    processStatusRegister = processStatusRegister & 0b11111110;
    processStatusRegister = processStatusRegister | (tempRegister >> 8u);
}

// Clear and set overflow bit
void CPU::setOverflow(uint8_t &reg, uint8_t &adderValue, uint16_t &tempRegister)
{

    if((registerA & 0b10000000 == adderValue & 0b10000000) && ((registerA & 0b10000000) != (tempRegister & 0b10000000)))
    {
        processStatusRegister = processStatusRegister | 0b01000000;
    }
    else
    {
        processStatusRegister = processStatusRegister & 0b10111111;
    }
}

void CPU::setNZ(uint8_t &reg)
{
    // If destination equals 0 set zero bit, otherwise clear it
    if (reg == 0)
    {
        processStatusRegister = processStatusRegister | 0b00000010;
    }  
    else
    {
        processStatusRegister = processStatusRegister & 0b11111101;
    }

    // Set negative bit equal to destinations most significant bit
    processStatusRegister = processStatusRegister & 0b01111111;
    processStatusRegister = processStatusRegister | (reg & 0b10000000);
}

