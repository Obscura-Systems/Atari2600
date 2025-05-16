#pragma once
#include <cstdint>
#include <vector>


class CPU
{

public:
    CPU();
    ~CPU();

    void Cycle();


    // ROM
    std::vector<uint8_t> rom;                    // Fits 4K ROMs only. Fix Later. Needs Bank switching for larger carts

private:
    // Registers
    uint8_t registerA{0x00};                    // Accumulator
    uint8_t registerX{0x00};                    // Index Register X
    uint8_t registerY{0x00};                    // Index Register Y
    uint16_t programCounter{0x1000};            // Program Counter
    uint8_t stackPointer{0xFF};                 // Stack Pointer. Stack located at 0x0100 to 0x01FF. Points to first FREE
    uint8_t processStatusRegister{0x20};   // Bit  Name    Expl.
                                            // 0    C       Carry           (0=No carry, 1=Carry)
                                            // 1    Z       Zero            (0=Nonzero, 1=Zero)
                                            // 2    I       IRQ Disable     (0=IRQ Enable, 1=IRQ Disable)
                                            // 3    D       Decimal Mode    (0=Normal, 1-BCD Mode for ADC/SBC opcodes)
                                            // 4    B       Break Flag      (0=IRQ/NMI, 1=RESET of BRK/PHP opcode)
                                            // 5    -       Not Used        (Always 1)
                                            // 6    V       Overflow        (0=No Overflow, 1=Overflow)
                                            // 7    N       Negative/Sign   (0=Positive, 1=Negative)

    // Memory. Complete 8K address space. 0x0FFF to 0x1FFF. Lower 4K for internal memory. Upper 4K is for external (ROM)
    uint8_t memory[8192]{};

    // Opcodes

    void OP_NULL();

    // CPU Memory and Register Transfers

    // Register/Immedaite to Register Transfer
    void OP_A8();
    void OP_AA();
    void OP_BA();
    void OP_98();
    void OP_8A();
    void OP_9A();
    void OP_A9();
    void OP_A2();
    void OP_A0();

    // Load Register from Memory
    void OP_A5();
    void OP_B5();
    void OP_AD();
    void OP_BD();
    void OP_B9();
    void OP_A1();
    void OP_B1();
    void OP_A6();
    void OP_B6();
    void OP_AE();
    void OP_BE();
    void OP_A4();
    void OP_B4();
    void OP_AC();
    void OP_BC();

    // Store Register in Memory
    void OP_85();
    void OP_95();
    void OP_8D();
    void OP_9D();
    void OP_99();
    void OP_81();
    void OP_91();
    void OP_86();
    void OP_96();
    void OP_8E();
    void OP_84();
    void OP_94();
    void OP_8C();

    // Push/Pull
    void OP_48();
    void OP_08();
    void OP_68();
    void OP_28();

    // CPU Arithmetic/Logical Operations

    // Add memory to accumulator with carry
    void OP_69();
    void OP_65();
    void OP_75();
    void OP_6D();
    void OP_7D();
    void OP_79();
    void OP_61();
    void OP_71();

    // Subtract memory from accumulator with borrow
    void OP_E9();
    void OP_E5();
    void OP_F5();
    void OP_ED();
    void OP_FD();
    void OP_F9();
    void OP_E1();
    void OP_F1();

    // Logical AND memory with accumulator
    void OP_29();
    void OP_25();
    void OP_35();
    void OP_2D();
    void OP_3D();
    void OP_39();
    void OP_21();
    void OP_31();

    // Exclusive-OR memory with accumulator
    void OP_49();
    void OP_45();
    void OP_55();
    void OP_4D();
    void OP_5D();
    void OP_59();
    void OP_41();
    void OP_51();

    // Logical OR memory with accumulator
    void OP_09();
    void OP_05();
    void OP_15();
    void OP_0D();
    void OP_1D();
    void OP_19();
    void OP_01();
    void OP_11();

    // Compare
    void OP_C9();
    void OP_C5();
    void OP_D5();
    void OP_CD();
    void OP_DD();
    void OP_D9();
    void OP_C1();
    void OP_D1();
    void OP_E0();
    void OP_E4();
    void OP_EC();
    void OP_C0();
    void OP_C4();
    void OP_CC();

    // Bit Test
    void OP_24();
    void OP_2C();

    // Increment by one
    void OP_E6();
    void OP_F6();
    void OP_EE();
    void OP_FE();
    void OP_E8();
    void OP_C8();

    // Decrement by one
    void OP_C6();
    void OP_D6();
    void OP_CE();
    void OP_DE();
    void OP_CA();
    void OP_88();


    // CPU Rotate and Shift instructions

    // Shift Left Logical/Arithmetic
    void OP_0A();
    void OP_06();
    void OP_16();
    void OP_0E();
    void OP_1E();

    // Shift Right Logical
    void OP_4A();
    void OP_46();
    void OP_56();
    void OP_4E();
    void OP_5E();

    // Rotate Left through Carry
    void OP_2A();
    void OP_26();
    void OP_36();
    void OP_2E();
    void OP_3E();

    // Rotate Right Through Carry
    void OP_6A();
    void OP_66();
    void OP_76();
    void OP_6E();
    void OP_7E();


    // CPU Jump and Control Instructions

    // Normal Jumps & Subroutine Calls/Returns
    void OP_4C();
    void OP_6C();
    void OP_20();
    void OP_40();
    void OP_60();
    
    // Conditional Branches (conditional jump to PC=PC+/-dd)
    void OP_10();
    void OP_30();
    void OP_50();
    void OP_70();
    void OP_90();
    void OP_B0();
    void OP_D0();
    void OP_F0();
    
    // Interrupts, Exceptions, Breakpoints
    void OP_00();       // FORCE BREAK
    //void DUMMY();     // INTERRUPT
    //void DUMMY();     // NMI
    //void DUMMY();     // RESET

    // CPU Control
    void OP_18();
    void OP_58();
    void OP_D8();
    void OP_B8();
    void OP_38();
    void OP_78();
    void OP_F8();

    // No Operation
    void OP_EA();


    // CPU Illegal Opcodes

    // SAX and LAX
    void OP_87();
    void OP_97();
    void OP_8F();
    void OP_83();
    void OP_A7();
    void OP_B7();
    void OP_AF();
    void OP_A3();
    void OP_B3();

    // Combined ALU-opcodes

    // ???????????????????????????????

    // Other Illegal Opcodes

    void OP_0B();
    void OP_2B();
    void OP_4B();
    void OP_6B();
    void OP_CB();
    void OP_EB();
    void OP_BB();


    // NUL/NOP and KIL/JAM/HLT

    // TODO


    // Unstable Illegal Opcodes
    void OP_8B();
    void OP_AB();
    void OP_BF();
    void OP_93();
    void OP_9F();
    void OP_9C();
    void OP_9E();
    void OP_9B();


    typedef void (CPU::*CPUFunc)();
    CPUFunc opList[0xFF + 1];

};

