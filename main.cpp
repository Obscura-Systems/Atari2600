#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include "CPU.h"
#include <gtest/gtest.h>

using namespace std;

CPU cpu;

uint8_t testByte = 0xFD;
uint8_t address = 0x1A;
uint16_t address16 = 0x1234;
uint16_t word = 0x1334;
uint8_t regOne = 0x03;
uint8_t regTwo = 0x04;

int counter = 0;

int main(int argc,char **argv)
{
    // Unit Testing

    // CPU should be reset before every unit test.
    // All registers and program counter set to 0. 
    // Process status register set to 0x20 because unused flag is always 1. 
    // All bytes in memory set to 0x00
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();


}

class CPU_OP_TEST : public testing::Test
{
    protected:
        CPU_OP_TEST()
        {
            cpu.resetState();
        }
        ~CPU_OP_TEST() override
        {
            //cpu.reportStatus();
        }
};

/*

UNIT TESTS

All variable combinations and outcomes should be tested
and verified. Some edge cases are purposely avoided because
they are not possible in a real world scenario (like overwriting
the memory where the opcode is before the opcode is called.)

*/

// Register/Immediate to Register Transfer

TEST_F(CPU_OP_TEST, OP_A8)                  // Y=A. NZ
{
    for (int i = 0; i < 256; i++)
    {
        cpu.resetState();
        testByte = i;
        cpu.setMemory(0x0000, 0xA8); 
        uint8_t expectedStatusRegister = (testByte == 0) ? (testByte & 0b10000000) | 0b00100010 : (testByte & 0b10000000) | 0b00100000;     
        cpu.registerA = testByte;              
        cpu.Cycle();                           
        ASSERT_EQ(cpu.registerY, testByte);
        ASSERT_EQ(cpu.processStatusRegister, expectedStatusRegister);
    }
}   
TEST_F(CPU_OP_TEST, OP_AA)                  // X=A. NZ
{
    for (int i = 0; i < 256; i++)
    {
        cpu.resetState();
        testByte = i;
        cpu.setMemory(0x0000, 0xAA); 
        uint8_t expectedStatusRegister = (testByte == 0) ? (testByte & 0b10000000) | 0b00100010 : (testByte & 0b10000000) | 0b00100000;     
        cpu.registerA = testByte;              
        cpu.Cycle();                           
        ASSERT_EQ(cpu.registerX, testByte);
        ASSERT_EQ(cpu.processStatusRegister, expectedStatusRegister);
    }
}
TEST_F(CPU_OP_TEST, OP_BA)                  // X=S NZ
{
    for (int i = 0; i < 256; i++)
    {
        cpu.resetState();
        testByte = i;
        cpu.setMemory(0x0000, 0xBA);   
        uint8_t expectedStatusRegister = (testByte == 0) ? (testByte & 0b10000000) | 0b00100010 : (testByte & 0b10000000) | 0b00100000;   
        cpu.stackPointer = testByte;           
        cpu.Cycle();                            
        ASSERT_EQ(cpu.registerX, testByte);    
        ASSERT_EQ(cpu.processStatusRegister, expectedStatusRegister); 
    }
}
TEST_F(CPU_OP_TEST, OP_98)                  // A=Y NZ
{
    for (int i = 0; i < 256; i++)
    {
        cpu.resetState();
        testByte = i;
        cpu.setMemory(0x0000, 0x98);  
        uint8_t expectedStatusRegister = (testByte == 0) ? (testByte & 0b10000000) | 0b00100010 : (testByte & 0b10000000) | 0b00100000;             
        cpu.registerY = testByte;             
        cpu.Cycle();                           
        ASSERT_EQ(cpu.registerA, testByte);
        ASSERT_EQ(cpu.processStatusRegister, expectedStatusRegister); 
    }
}
TEST_F(CPU_OP_TEST, OP_8A)                  // A=X NZ
{
    for (int i = 0; i < 256; i++)
    {
        cpu.resetState();
        testByte = i;
        cpu.setMemory(0x0000, 0x8A);   
        uint8_t expectedStatusRegister = (testByte == 0) ? (testByte & 0b10000000) | 0b00100010 : (testByte & 0b10000000) | 0b00100000;        
        cpu.registerX = testByte;             
        cpu.Cycle();                           
        ASSERT_EQ(cpu.registerA, testByte);  
        ASSERT_EQ(cpu.processStatusRegister, expectedStatusRegister); 
    }
}
TEST_F(CPU_OP_TEST, OP_9A)                  // S=X
{
    for (int i = 0; i < 256; i++)
    {
        cpu.resetState();
        testByte = i;
        cpu.setMemory(0x0000, 0x9A);         
        cpu.registerX = testByte;             
        cpu.Cycle();                            
        ASSERT_EQ(cpu.stackPointer, testByte);   
    }
}
TEST_F(CPU_OP_TEST, OP_A9)                  // A=nn NZ
{
    for (int i = 0; i < 256; i++)
    {
        cpu.resetState();
        testByte = i;
        cpu.setMemory(0x0000, 0xA9);
        uint8_t expectedStatusRegister = (testByte== 0) ? (testByte & 0b10000000) | 0b00100010 : (testByte & 0b10000000) | 0b00100000;            
        cpu.setMemory(0x0001 ,testByte);             
        cpu.Cycle();                           
        ASSERT_EQ(cpu.registerA, testByte);   
        ASSERT_EQ(cpu.processStatusRegister, expectedStatusRegister); 
    }
}
TEST_F(CPU_OP_TEST, OP_A2)                  // X=nn NZ
{
    for (int i = 0; i < 256; i++)
    {
        cpu.resetState();
        testByte = i;
        cpu.setMemory(0x0000, 0xA2);
        uint8_t expectedStatusRegister = (testByte == 0) ? (testByte & 0b10000000) | 0b00100010 : (testByte & 0b10000000) | 0b00100000;            
        cpu.setMemory(0x0001 ,testByte);             
        cpu.Cycle();                           
        ASSERT_EQ(cpu.registerX, testByte);   
        ASSERT_EQ(cpu.processStatusRegister, expectedStatusRegister);   
    }
}
TEST_F(CPU_OP_TEST, OP_A0)                  // Y=nn NZ
{
    for (int i = 0; i < 256; i++)
    {
        cpu.resetState();
        testByte = i;
        cpu.setMemory(0x0000, 0xA0);
        uint8_t expectedStatusRegister = (testByte == 0) ? (testByte & 0b10000000) | 0b00100010 : (testByte & 0b10000000) | 0b00100000;            
        cpu.setMemory(0x0001 ,testByte);             
        cpu.Cycle();                           
        ASSERT_EQ(cpu.registerY, testByte);   
        ASSERT_EQ(cpu.processStatusRegister, expectedStatusRegister);  
    }
}

// Load Register from Memory

TEST_F(CPU_OP_TEST, OP_A5)                  // A=[nn] NZ
{
    for (int i = 2; i < 256; i++)
    {
        cpu.resetState();
        testByte = 0x00;
        address = i;
        cpu.setMemory(0x0000, 0xA5);
        uint8_t expectedStatusRegister = (testByte == 0) ? (testByte & 0b10000000) | 0b00100010 : (testByte & 0b10000000) | 0b00100000;  
        cpu.setMemory(0x0001, address);
        cpu.setMemory(address, testByte);
        cpu.Cycle();
        ASSERT_EQ(cpu.registerA, testByte);
        ASSERT_EQ(cpu.processStatusRegister, expectedStatusRegister); 

        cpu.resetState();
        testByte = 0x0F;
        address = i;
        cpu.setMemory(0x0000, 0xA5);
        expectedStatusRegister = (testByte == 0) ? (testByte & 0b10000000) | 0b00100010 : (testByte & 0b10000000) | 0b00100000;  
        cpu.setMemory(0x0001, address);
        cpu.setMemory(address, testByte);
        cpu.Cycle();
        ASSERT_EQ(cpu.registerA, testByte);
        ASSERT_EQ(cpu.processStatusRegister, expectedStatusRegister); 

        cpu.resetState();
        testByte = 0xF0;
        address = i;
        cpu.setMemory(0x0000, 0xA5);
        expectedStatusRegister = (testByte == 0) ? (testByte & 0b10000000) | 0b00100010 : (testByte & 0b10000000) | 0b00100000;  
        cpu.setMemory(0x0001, address);
        cpu.setMemory(address, testByte);
        cpu.Cycle();
        ASSERT_EQ(cpu.registerA, testByte);
        ASSERT_EQ(cpu.processStatusRegister, expectedStatusRegister); 
    }
}
TEST_F(CPU_OP_TEST, OP_B5)                  // A=[nn+X] NZ
{
    for (int j = 2; j < 256; j++)
    {
        for (int k = 0; k < 256; k++)
        {
            if ( ((j + k) % 0x0100) > 1) 
            {
                cpu.resetState();
                testByte = 0x00;
                address = j;
                cpu.registerX = k;
                cpu.setMemory(0x0000, 0xB5);
                uint8_t expectedStatusRegister = (testByte == 0) ? (testByte & 0b10000000) | 0b00100010 : (testByte & 0b10000000) | 0b00100000; 
                cpu.setMemory(0x0001, address);
                cpu.setMemory((address + cpu.registerX), testByte);
                cpu.Cycle();
                ASSERT_EQ(cpu.registerA, testByte);
                ASSERT_EQ(cpu.processStatusRegister, expectedStatusRegister); 

                cpu.resetState();
                testByte = 0x0F;
                address = j;
                cpu.registerX = k;
                cpu.setMemory(0x0000, 0xB5);
                expectedStatusRegister = (testByte == 0) ? (testByte & 0b10000000) | 0b00100010 : (testByte & 0b10000000) | 0b00100000; 
                cpu.setMemory(0x0001, address);
                cpu.setMemory((address + cpu.registerX), testByte);
                cpu.Cycle();
                ASSERT_EQ(cpu.registerA, testByte);
                ASSERT_EQ(cpu.processStatusRegister, expectedStatusRegister); 

                cpu.resetState();
                testByte = 0xF0;
                address = j;
                cpu.registerX = k;
                cpu.setMemory(0x0000, 0xB5);
                expectedStatusRegister = (testByte == 0) ? (testByte & 0b10000000) | 0b00100010 : (testByte & 0b10000000) | 0b00100000; 
                cpu.setMemory(0x0001, address);
                cpu.setMemory((address + cpu.registerX), testByte);
                cpu.Cycle();
                ASSERT_EQ(cpu.registerA, testByte);
                ASSERT_EQ(cpu.processStatusRegister, expectedStatusRegister); 
            }
        }
    }
}
TEST_F(CPU_OP_TEST, OP_AD)                  // A=[nnnn] NZ
{
    for (int j = 3; j < 0x1FFF; j++)
    {
        cpu.resetState();
        testByte = 0x00;    
        address16 = j;
        cpu.setMemory(0x0000, 0xAD);
        uint8_t expectedStatusRegister = (testByte == 0) ? (testByte & 0b10000000) | 0b00100010 : (testByte & 0b10000000) | 0b00100000;  
        cpu.setMemory(0x0001, address16);
        cpu.setMemory(0x0002, (address16 >> 8u));
        cpu.setMemory(address16, testByte);
        cpu.Cycle();
        ASSERT_EQ(cpu.registerA, testByte);
        ASSERT_EQ(cpu.processStatusRegister, expectedStatusRegister); 

        cpu.resetState();
        testByte = 0x0F;    
        address16 = j;
        cpu.setMemory(0x0000, 0xAD);
        expectedStatusRegister = (testByte == 0) ? (testByte & 0b10000000) | 0b00100010 : (testByte & 0b10000000) | 0b00100000;  
        cpu.setMemory(0x0001, address16);
        cpu.setMemory(0x0002, (address16 >> 8u));
        cpu.setMemory(address16, testByte);
        cpu.Cycle();
        ASSERT_EQ(cpu.registerA, testByte);
        ASSERT_EQ(cpu.processStatusRegister, expectedStatusRegister); 

        cpu.resetState();
        testByte = 0xF0;    
        address16 = j;
        cpu.setMemory(0x0000, 0xAD);
        expectedStatusRegister = (testByte == 0) ? (testByte & 0b10000000) | 0b00100010 : (testByte & 0b10000000) | 0b00100000;  
        cpu.setMemory(0x0001, address16);
        cpu.setMemory(0x0002, (address16 >> 8u));
        cpu.setMemory(address16, testByte);
        cpu.Cycle();
        ASSERT_EQ(cpu.registerA, testByte);
        ASSERT_EQ(cpu.processStatusRegister, expectedStatusRegister); 
    }
}
TEST_F(CPU_OP_TEST, OP_BD)                  // A=[nnnn+X] NZ
{
    for (int i = 0; i < 256; i++)
    {
        for (int j = 0x0003; j < 0x1FFF; j++)
        {
            if (((i + j) % 0x2000) > 2)
            {
                cpu.resetState();
                cpu.registerA = 0xCC;
                testByte = 0x00;
                address16 = j;
                cpu.registerX = i;
                cpu.setMemory(0x0000, 0xBD);
                uint8_t expectedStatusRegister = (testByte == 0) ? (testByte & 0b10000000) | 0b00100010 : (testByte & 0b10000000) | 0b00100000; 
                cpu.setMemory(0x0001, address16);
                cpu.setMemory(0x0002, (address16 >> 8u));
                cpu.setMemory((address16 + cpu.registerX), testByte);
                cpu.Cycle();
                ASSERT_EQ(cpu.registerA, testByte);
                ASSERT_EQ(cpu.processStatusRegister, expectedStatusRegister); 

                cpu.resetState();
                cpu.registerA = 0xCC;
                testByte = 0x0F;
                address16 = j;
                cpu.registerX = i;
                cpu.setMemory(0x0000, 0xBD);
                expectedStatusRegister = (testByte == 0) ? (testByte & 0b10000000) | 0b00100010 : (testByte & 0b10000000) | 0b00100000; 
                cpu.setMemory(0x0001, address16);
                cpu.setMemory(0x0002, (address16 >> 8u));
                cpu.setMemory((address16 + cpu.registerX), testByte);
                cpu.Cycle();
                ASSERT_EQ(cpu.registerA, testByte);
                ASSERT_EQ(cpu.processStatusRegister, expectedStatusRegister); 

                cpu.resetState();
                cpu.registerA = 0xCC;
                testByte = 0xF0;
                address16 = j;
                cpu.registerX = i;
                cpu.setMemory(0x0000, 0xBD);
                expectedStatusRegister = (testByte == 0) ? (testByte & 0b10000000) | 0b00100010 : (testByte & 0b10000000) | 0b00100000; 
                cpu.setMemory(0x0001, address16);
                cpu.setMemory(0x0002, (address16 >> 8u));
                cpu.setMemory((address16 + cpu.registerX), testByte);
                cpu.Cycle();
                ASSERT_EQ(cpu.registerA, testByte);
                ASSERT_EQ(cpu.processStatusRegister, expectedStatusRegister); 
            }
        }
    }
}
TEST_F(CPU_OP_TEST, OP_B9)                  // A=[nnnn+Y] NZ
{
    for (int i = 0; i < 256; i++)
    {
        for (int j = 0x0003; j < 0x1FFF; j++)
        {
            if (((i + j) % 0x2000) > 2)
            {
                cpu.resetState();
                cpu.registerA = 0xCC;
                testByte = 0x00;
                address16 = j;
                cpu.registerY = i;
                cpu.setMemory(0x0000, 0xB9);
                uint8_t expectedStatusRegister = (testByte == 0) ? (testByte & 0b10000000) | 0b00100010 : (testByte & 0b10000000) | 0b00100000; 
                cpu.setMemory(0x0001, address16);
                cpu.setMemory(0x0002, (address16 >> 8u));
                cpu.setMemory((address16 + cpu.registerY), testByte);
                cpu.Cycle();
                ASSERT_EQ(cpu.registerA, testByte);
                ASSERT_EQ(cpu.processStatusRegister, expectedStatusRegister); 

                cpu.resetState();
                cpu.registerA = 0xCC;
                testByte = 0x0F;
                address16 = j;
                cpu.registerY = i;
                cpu.setMemory(0x0000, 0xB9);
                expectedStatusRegister = (testByte == 0) ? (testByte & 0b10000000) | 0b00100010 : (testByte & 0b10000000) | 0b00100000; 
                cpu.setMemory(0x0001, address16);
                cpu.setMemory(0x0002, (address16 >> 8u));
                cpu.setMemory((address16 + cpu.registerY), testByte);
                cpu.Cycle();
                ASSERT_EQ(cpu.registerA, testByte);
                ASSERT_EQ(cpu.processStatusRegister, expectedStatusRegister); 

                cpu.resetState();
                cpu.registerA = 0xCC;
                testByte = 0xF0;
                address16 = j;
                cpu.registerY = i;
                cpu.setMemory(0x0000, 0xB9);
                expectedStatusRegister = (testByte == 0) ? (testByte & 0b10000000) | 0b00100010 : (testByte & 0b10000000) | 0b00100000; 
                cpu.setMemory(0x0001, address16);
                cpu.setMemory(0x0002, (address16 >> 8u));
                cpu.setMemory((address16 + cpu.registerY), testByte);
                cpu.Cycle();
                ASSERT_EQ(cpu.registerA, testByte);
                ASSERT_EQ(cpu.processStatusRegister, expectedStatusRegister); 
            }
        }
    }
}
TEST_F(CPU_OP_TEST, OP_A1)                  // A=[WORD[nn+X]] NZ
{
    address = 0x02;
    for (int i = 0; i < 0xFD; i++)
    {
        for (int j = 0x0100; j < 0x2000; j++)
        {
            cpu.resetState();
            cpu.setMemory(0x0000, 0xA1);
            testByte = 0x00;
            cpu.registerX = i;
            word = j;
            uint8_t expectedStatusRegister = (testByte == 0) ? (testByte & 0b10000000) | 0b00100010 : (testByte & 0b10000000) | 0b00100000; 
            cpu.setMemory(0x0001, address);
            cpu.setMemory(address + cpu.registerX + 1, (word >> 8u));
            cpu.setMemory(address + cpu.registerX, word);
            cpu.setMemory(word, testByte);
            cpu.Cycle();
            ASSERT_EQ(cpu.registerA, testByte);
            ASSERT_EQ(cpu.processStatusRegister, expectedStatusRegister); 

            cpu.resetState();
            cpu.setMemory(0x0000, 0xA1);
            testByte = 0x0F;
            expectedStatusRegister = (testByte == 0) ? (testByte & 0b10000000) | 0b00100010 : (testByte & 0b10000000) | 0b00100000; 
            cpu.setMemory(0x0001, address);
            cpu.setMemory(address + cpu.registerX + 1, (word >> 8u));
            cpu.setMemory(address + cpu.registerX, word);
            cpu.setMemory(word, testByte);
            cpu.Cycle();
            ASSERT_EQ(cpu.registerA, testByte);
            ASSERT_EQ(cpu.processStatusRegister, expectedStatusRegister); 

            cpu.resetState();
            cpu.setMemory(0x0000, 0xA1);
            testByte = 0xF0;
            expectedStatusRegister = (testByte == 0) ? (testByte & 0b10000000) | 0b00100010 : (testByte & 0b10000000) | 0b00100000; 
            cpu.setMemory(0x0001, address);
            cpu.setMemory(address + cpu.registerX + 1, (word >> 8u));
            cpu.setMemory(address + cpu.registerX, word);
            cpu.setMemory(word, testByte);
            cpu.Cycle();
            ASSERT_EQ(cpu.registerA, testByte);
            ASSERT_EQ(cpu.processStatusRegister, expectedStatusRegister); 
        }
    }
}
TEST_F(CPU_OP_TEST, OP_B1)                  // A=[WORD[nn]+Y] NZ
{
    for (int i = 2; i < 0x100; i++)
    {
        for (int j = 0x0100; j < 0x1FFF; j++)
        {
            cpu.resetState();
            cpu.setMemory(0x0000, 0xB1);
            address = i;
            word = j;
            cpu.registerY = 0x01;
            testByte = 0xAF;
            uint8_t expectedStatusRegister = (testByte == 0) ? (testByte & 0b10000000) | 0b00100010 : (testByte & 0b10000000) | 0b00100000; 
            cpu.setMemory(0x0001, address);
            cpu.setMemory(address + 1, (word >> 8u));
            cpu.setMemory(address , word);
            cpu.setMemory(word + cpu.registerY, testByte);
            cpu.Cycle();
            ASSERT_EQ(cpu.registerA, testByte);
            ASSERT_EQ(cpu.processStatusRegister, expectedStatusRegister); 
        }
    }
}
TEST_F(CPU_OP_TEST, OP_A6)                  // X=[nn] NZ
{
    for (int i = 2; i < 256; i++)
    {
        cpu.resetState();
        testByte = 0x00;
        address = i;
        cpu.setMemory(0x0000, 0xA6);
        uint8_t expectedStatusRegister = (testByte == 0) ? (testByte & 0b10000000) | 0b00100010 : (testByte & 0b10000000) | 0b00100000;  
        cpu.setMemory(0x0001, address);
        cpu.setMemory(address, testByte);
        cpu.Cycle();
        ASSERT_EQ(cpu.registerX, testByte);
        ASSERT_EQ(cpu.processStatusRegister, expectedStatusRegister); 

        cpu.resetState();
        testByte = 0x0F;
        address = i;
        cpu.setMemory(0x0000, 0xA6);
        expectedStatusRegister = (testByte == 0) ? (testByte & 0b10000000) | 0b00100010 : (testByte & 0b10000000) | 0b00100000;  
        cpu.setMemory(0x0001, address);
        cpu.setMemory(address, testByte);
        cpu.Cycle();
        ASSERT_EQ(cpu.registerX, testByte);
        ASSERT_EQ(cpu.processStatusRegister, expectedStatusRegister); 

        cpu.resetState();
        testByte = 0xF0;
        address = i;
        cpu.setMemory(0x0000, 0xA6);
        expectedStatusRegister = (testByte == 0) ? (testByte & 0b10000000) | 0b00100010 : (testByte & 0b10000000) | 0b00100000;  
        cpu.setMemory(0x0001, address);
        cpu.setMemory(address, testByte);
        cpu.Cycle();
        ASSERT_EQ(cpu.registerX, testByte);
        ASSERT_EQ(cpu.processStatusRegister, expectedStatusRegister); 
    }
}
TEST_F(CPU_OP_TEST, OP_B6)                  // X=[nn+Y] NZ
{
    for (int j = 2; j < 256; j++)
    {
        for (int k = 0; k < 256; k++)
        {
            if ( ((j + k) % 0x0100) > 1) 
            {
                cpu.resetState();
                testByte = 0x00;
                address = j;
                cpu.registerY = k;
                cpu.setMemory(0x0000, 0xB6);
                uint8_t expectedStatusRegister = (testByte == 0) ? (testByte & 0b10000000) | 0b00100010 : (testByte & 0b10000000) | 0b00100000; 
                cpu.setMemory(0x0001, address);
                cpu.setMemory((address + cpu.registerY), testByte);
                cpu.Cycle();
                ASSERT_EQ(cpu.registerX, testByte);
                ASSERT_EQ(cpu.processStatusRegister, expectedStatusRegister); 

                cpu.resetState();
                testByte = 0x0F;
                address = j;
                cpu.registerY = k;
                cpu.setMemory(0x0000, 0xB6);
                expectedStatusRegister = (testByte == 0) ? (testByte & 0b10000000) | 0b00100010 : (testByte & 0b10000000) | 0b00100000; 
                cpu.setMemory(0x0001, address);
                cpu.setMemory((address + cpu.registerY), testByte);
                cpu.Cycle();
                ASSERT_EQ(cpu.registerX, testByte);
                ASSERT_EQ(cpu.processStatusRegister, expectedStatusRegister); 

                cpu.resetState();
                testByte = 0xF0;
                address = j;
                cpu.registerY = k;
                cpu.setMemory(0x0000, 0xB6);
                expectedStatusRegister = (testByte == 0) ? (testByte & 0b10000000) | 0b00100010 : (testByte & 0b10000000) | 0b00100000; 
                cpu.setMemory(0x0001, address);
                cpu.setMemory((address + cpu.registerY), testByte);
                cpu.Cycle();
                ASSERT_EQ(cpu.registerX, testByte);
                ASSERT_EQ(cpu.processStatusRegister, expectedStatusRegister); 
            }
        }
    }
}
TEST_F(CPU_OP_TEST, OP_AE)                  // X=[nnnn] NZ
{
    for (int j = 3; j < 0x1FFF; j++)
    {
        cpu.resetState();
        testByte = 0x00;    
        address16 = j;
        cpu.setMemory(0x0000, 0xAE);
        uint8_t expectedStatusRegister = (testByte == 0) ? (testByte & 0b10000000) | 0b00100010 : (testByte & 0b10000000) | 0b00100000;  
        cpu.setMemory(0x0001, address16);
        cpu.setMemory(0x0002, (address16 >> 8u));
        cpu.setMemory(address16, testByte);
        cpu.Cycle();
        ASSERT_EQ(cpu.registerX, testByte);
        ASSERT_EQ(cpu.processStatusRegister, expectedStatusRegister); 

        cpu.resetState();
        testByte = 0x0F;    
        address16 = j;
        cpu.setMemory(0x0000, 0xAE);
        expectedStatusRegister = (testByte == 0) ? (testByte & 0b10000000) | 0b00100010 : (testByte & 0b10000000) | 0b00100000;  
        cpu.setMemory(0x0001, address16);
        cpu.setMemory(0x0002, (address16 >> 8u));
        cpu.setMemory(address16, testByte);
        cpu.Cycle();
        ASSERT_EQ(cpu.registerX, testByte);
        ASSERT_EQ(cpu.processStatusRegister, expectedStatusRegister); 

        cpu.resetState();
        testByte = 0xF0;    
        address16 = j;
        cpu.setMemory(0x0000, 0xAE);
        expectedStatusRegister = (testByte == 0) ? (testByte & 0b10000000) | 0b00100010 : (testByte & 0b10000000) | 0b00100000;  
        cpu.setMemory(0x0001, address16);
        cpu.setMemory(0x0002, (address16 >> 8u));
        cpu.setMemory(address16, testByte);
        cpu.Cycle();
        ASSERT_EQ(cpu.registerX, testByte);
        ASSERT_EQ(cpu.processStatusRegister, expectedStatusRegister); 
    }
}
TEST_F(CPU_OP_TEST, OP_BE)                  // X=[nnnn+Y] NZ
{
    for (int i = 0; i < 256; i++)
    {
        for (int j = 0x0003; j < 0x1FFF; j++)
        {
            if (((i + j) % 0x2000) > 2)
            {
                cpu.resetState();
                cpu.registerA = 0xCC;
                testByte = 0x00;
                address16 = j;
                cpu.registerY = i;
                cpu.setMemory(0x0000, 0xBE);
                uint8_t expectedStatusRegister = (testByte == 0) ? (testByte & 0b10000000) | 0b00100010 : (testByte & 0b10000000) | 0b00100000; 
                cpu.setMemory(0x0001, address16);
                cpu.setMemory(0x0002, (address16 >> 8u));
                cpu.setMemory((address16 + cpu.registerY), testByte);
                cpu.Cycle();
                ASSERT_EQ(cpu.registerX, testByte);
                ASSERT_EQ(cpu.processStatusRegister, expectedStatusRegister); 

                cpu.resetState();
                cpu.registerA = 0xCC;
                testByte = 0x0F;
                address16 = j;
                cpu.registerY = i;
                cpu.setMemory(0x0000, 0xBE);
                expectedStatusRegister = (testByte == 0) ? (testByte & 0b10000000) | 0b00100010 : (testByte & 0b10000000) | 0b00100000; 
                cpu.setMemory(0x0001, address16);
                cpu.setMemory(0x0002, (address16 >> 8u));
                cpu.setMemory((address16 + cpu.registerY), testByte);
                cpu.Cycle();
                ASSERT_EQ(cpu.registerX, testByte);
                ASSERT_EQ(cpu.processStatusRegister, expectedStatusRegister); 

                cpu.resetState();
                cpu.registerA = 0xCC;
                testByte = 0xF0;
                address16 = j;
                cpu.registerY = i;
                cpu.setMemory(0x0000, 0xBE);
                expectedStatusRegister = (testByte == 0) ? (testByte & 0b10000000) | 0b00100010 : (testByte & 0b10000000) | 0b00100000; 
                cpu.setMemory(0x0001, address16);
                cpu.setMemory(0x0002, (address16 >> 8u));
                cpu.setMemory((address16 + cpu.registerY), testByte);
                cpu.Cycle();
                ASSERT_EQ(cpu.registerX, testByte);
                ASSERT_EQ(cpu.processStatusRegister, expectedStatusRegister); 
            }
        }
    }
}
TEST_F(CPU_OP_TEST, OP_A4)                  // Y=[nn] NZ
{
   for (int i = 2; i < 256; i++)
    {
        cpu.resetState();
        testByte = 0x00;
        address = i;
        cpu.setMemory(0x0000, 0xA4);
        uint8_t expectedStatusRegister = (testByte == 0) ? (testByte & 0b10000000) | 0b00100010 : (testByte & 0b10000000) | 0b00100000;  
        cpu.setMemory(0x0001, address);
        cpu.setMemory(address, testByte);
        cpu.Cycle();
        ASSERT_EQ(cpu.registerY, testByte);
        ASSERT_EQ(cpu.processStatusRegister, expectedStatusRegister); 

        cpu.resetState();
        testByte = 0x0F;
        address = i;
        cpu.setMemory(0x0000, 0xA4);
        expectedStatusRegister = (testByte == 0) ? (testByte & 0b10000000) | 0b00100010 : (testByte & 0b10000000) | 0b00100000;  
        cpu.setMemory(0x0001, address);
        cpu.setMemory(address, testByte);
        cpu.Cycle();
        ASSERT_EQ(cpu.registerY, testByte);
        ASSERT_EQ(cpu.processStatusRegister, expectedStatusRegister); 

        cpu.resetState();
        testByte = 0xF0;
        address = i;
        cpu.setMemory(0x0000, 0xA4);
        expectedStatusRegister = (testByte == 0) ? (testByte & 0b10000000) | 0b00100010 : (testByte & 0b10000000) | 0b00100000;  
        cpu.setMemory(0x0001, address);
        cpu.setMemory(address, testByte);
        cpu.Cycle();
        ASSERT_EQ(cpu.registerY, testByte);
        ASSERT_EQ(cpu.processStatusRegister, expectedStatusRegister); 
    }
}
TEST_F(CPU_OP_TEST, OP_B4)                  // Y=[nn+X] NZ
{
    for (int j = 2; j < 256; j++)
    {
        for (int k = 0; k < 256; k++)
        {
            if ( ((j + k) % 0x0100) > 1) 
            {
                cpu.resetState();
                testByte = 0x00;
                address = j;
                cpu.registerX = k;
                cpu.setMemory(0x0000, 0xB4);
                uint8_t expectedStatusRegister = (testByte == 0) ? (testByte & 0b10000000) | 0b00100010 : (testByte & 0b10000000) | 0b00100000; 
                cpu.setMemory(0x0001, address);
                cpu.setMemory((address + cpu.registerX), testByte);
                cpu.Cycle();
                ASSERT_EQ(cpu.registerY, testByte);
                ASSERT_EQ(cpu.processStatusRegister, expectedStatusRegister); 

                cpu.resetState();
                testByte = 0x0F;
                address = j;
                cpu.registerX = k;
                cpu.setMemory(0x0000, 0xB4);
                expectedStatusRegister = (testByte == 0) ? (testByte & 0b10000000) | 0b00100010 : (testByte & 0b10000000) | 0b00100000; 
                cpu.setMemory(0x0001, address);
                cpu.setMemory((address + cpu.registerX), testByte);
                cpu.Cycle();
                ASSERT_EQ(cpu.registerY, testByte);
                ASSERT_EQ(cpu.processStatusRegister, expectedStatusRegister); 

                cpu.resetState();
                testByte = 0xF0;
                address = j;
                cpu.registerX = k;
                cpu.setMemory(0x0000, 0xB4);
                expectedStatusRegister = (testByte == 0) ? (testByte & 0b10000000) | 0b00100010 : (testByte & 0b10000000) | 0b00100000; 
                cpu.setMemory(0x0001, address);
                cpu.setMemory((address + cpu.registerX), testByte);
                cpu.Cycle();
                ASSERT_EQ(cpu.registerY, testByte);
                ASSERT_EQ(cpu.processStatusRegister, expectedStatusRegister); 
            }
        }
    }
}
TEST_F(CPU_OP_TEST, OP_AC)                  // Y=[nnnn] NZ
{
   for (int j = 3; j < 0x1FFF; j++)
    {
        cpu.resetState();
        testByte = 0x00;    
        address16 = j;
        cpu.setMemory(0x0000, 0xAC);
        uint8_t expectedStatusRegister = (testByte == 0) ? (testByte & 0b10000000) | 0b00100010 : (testByte & 0b10000000) | 0b00100000;  
        cpu.setMemory(0x0001, address16);
        cpu.setMemory(0x0002, (address16 >> 8u));
        cpu.setMemory(address16, testByte);
        cpu.Cycle();
        ASSERT_EQ(cpu.registerY, testByte);
        ASSERT_EQ(cpu.processStatusRegister, expectedStatusRegister); 

        cpu.resetState();
        testByte = 0x0F;    
        address16 = j;
        cpu.setMemory(0x0000, 0xAC);
        expectedStatusRegister = (testByte == 0) ? (testByte & 0b10000000) | 0b00100010 : (testByte & 0b10000000) | 0b00100000;  
        cpu.setMemory(0x0001, address16);
        cpu.setMemory(0x0002, (address16 >> 8u));
        cpu.setMemory(address16, testByte);
        cpu.Cycle();
        ASSERT_EQ(cpu.registerY, testByte);
        ASSERT_EQ(cpu.processStatusRegister, expectedStatusRegister); 

        cpu.resetState();
        testByte = 0xF0;    
        address16 = j;
        cpu.setMemory(0x0000, 0xAC);
        expectedStatusRegister = (testByte == 0) ? (testByte & 0b10000000) | 0b00100010 : (testByte & 0b10000000) | 0b00100000;  
        cpu.setMemory(0x0001, address16);
        cpu.setMemory(0x0002, (address16 >> 8u));
        cpu.setMemory(address16, testByte);
        cpu.Cycle();
        ASSERT_EQ(cpu.registerY, testByte);
        ASSERT_EQ(cpu.processStatusRegister, expectedStatusRegister); 
    }
}
TEST_F(CPU_OP_TEST, OP_BC)                  // Y=[nnnn+X] NZ
{
    for (int i = 0; i < 256; i++)
    {
        for (int j = 0x0003; j < 0x1FFF; j++)
        {
            if (((i + j) % 0x2000) > 2)
            {
                cpu.resetState();
                cpu.registerA = 0xCC;
                testByte = 0x00;
                address16 = j;
                cpu.registerX = i;
                cpu.setMemory(0x0000, 0xBC);
                uint8_t expectedStatusRegister = (testByte == 0) ? (testByte & 0b10000000) | 0b00100010 : (testByte & 0b10000000) | 0b00100000; 
                cpu.setMemory(0x0001, address16);
                cpu.setMemory(0x0002, (address16 >> 8u));
                cpu.setMemory((address16 + cpu.registerX), testByte);
                cpu.Cycle();
                ASSERT_EQ(cpu.registerY, testByte);
                ASSERT_EQ(cpu.processStatusRegister, expectedStatusRegister); 

                cpu.resetState();
                cpu.registerA = 0xCC;
                testByte = 0x0F;
                address16 = j;
                cpu.registerX = i;
                cpu.setMemory(0x0000, 0xBC);
                expectedStatusRegister = (testByte == 0) ? (testByte & 0b10000000) | 0b00100010 : (testByte & 0b10000000) | 0b00100000; 
                cpu.setMemory(0x0001, address16);
                cpu.setMemory(0x0002, (address16 >> 8u));
                cpu.setMemory((address16 + cpu.registerX), testByte);
                cpu.Cycle();
                ASSERT_EQ(cpu.registerY, testByte);
                ASSERT_EQ(cpu.processStatusRegister, expectedStatusRegister); 

                cpu.resetState();
                cpu.registerA = 0xCC;
                testByte = 0xF0;
                address16 = j;
                cpu.registerX = i;
                cpu.setMemory(0x0000, 0xBC);
                expectedStatusRegister = (testByte == 0) ? (testByte & 0b10000000) | 0b00100010 : (testByte & 0b10000000) | 0b00100000; 
                cpu.setMemory(0x0001, address16);
                cpu.setMemory(0x0002, (address16 >> 8u));
                cpu.setMemory((address16 + cpu.registerX), testByte);
                cpu.Cycle();
                ASSERT_EQ(cpu.registerY, testByte);
                ASSERT_EQ(cpu.processStatusRegister, expectedStatusRegister); 
            }
        }
    }
}

// Store Register in Memory

TEST_F(CPU_OP_TEST, OP_85)                  // [nn]=A
{
    for (int i = 1; i < 256; i++)
    {
        cpu.resetState();
        cpu.setMemory(0x0000, 0x85);
        uint8_t previousStatusRegister = cpu.processStatusRegister;
        testByte = 0xAC;
        cpu.registerA = testByte;
        address = i;
        cpu.setMemory(0x0001, address);
        cpu.Cycle();
        ASSERT_EQ(cpu.readMemory(address), testByte);
        ASSERT_EQ(cpu.processStatusRegister, previousStatusRegister);
    }
}
TEST_F(CPU_OP_TEST, OP_95)                  // [nn+X]=A
{
    for (int i = 1; i < 256; i++)
    {
        for (int j = 1; j < 256; j++)
        {
            if( (i + j) % 0x100 > 1)
            {
                cpu.resetState();
                cpu.setMemory(0x0000, 0x95);
                uint8_t previousStatusRegister = cpu.processStatusRegister;
                testByte = 0xAC;
                cpu.registerA = testByte;
                cpu.registerX = j;
                address = i;
                cpu.setMemory(0x0001, address);
                cpu.Cycle();
                ASSERT_EQ(cpu.readMemory(address + cpu.registerX), testByte);
                ASSERT_EQ(cpu.processStatusRegister, previousStatusRegister);
            }
        }
    }
}
TEST_F(CPU_OP_TEST, OP_8D)                  // [nnnn]=A
{
    for (int i = 3; i < 0x1FFF; i++)
    {
        cpu.resetState();
        cpu.setMemory(0x0000, 0x8D);
        uint8_t previousStatusRegister = cpu.processStatusRegister;
        testByte = 0xAC;
        cpu.registerA = testByte;
        address16 = i;
        cpu.setMemory(0x0001, address16);
        cpu.setMemory(0x0002, (address16 >> 8u));
        cpu.Cycle();
        ASSERT_EQ(cpu.readMemory(address16), testByte);
        ASSERT_EQ(cpu.processStatusRegister, previousStatusRegister);
    }
}
TEST_F(CPU_OP_TEST, OP_9D)                  // [nnnn+X]=A
{
    for (int i = 2; i < 0x1FFE; i++)
    {
        cpu.resetState();
        cpu.setMemory(0x0000, 0x9D);
        uint8_t previousStatusRegister = cpu.processStatusRegister;
        testByte = 0xAC;
        cpu.registerA = testByte;
        address16 = i;
        cpu.registerX = 0x01;
        cpu.setMemory(0x0001, address16);
        cpu.setMemory(0x0002, (address16 >> 8u));
        cpu.Cycle();
        ASSERT_EQ(cpu.readMemory(address16 + cpu.registerX), testByte);
        ASSERT_EQ(cpu.processStatusRegister, previousStatusRegister);
    }
}
TEST_F(CPU_OP_TEST, OP_99)                  // [nnnn+Y]=A
{
    for (int i = 2; i < 0x1FFE; i++)
    {
        cpu.resetState();
        cpu.setMemory(0x0000, 0x99);
        uint8_t previousStatusRegister = cpu.processStatusRegister;
        testByte = 0xAC;
        cpu.registerA = testByte;
        address16 = i;
        cpu.registerY = 0x01;
        cpu.setMemory(0x0001, address16);
        cpu.setMemory(0x0002, (address16 >> 8u));
        cpu.Cycle();
        ASSERT_EQ(cpu.readMemory(address16 + cpu.registerY), testByte);
        ASSERT_EQ(cpu.processStatusRegister, previousStatusRegister);
    }
}
TEST_F(CPU_OP_TEST, OP_81)                  // [WORD[nn+x]]=A
{
    for (int i = 1; i < 0xFE; i++)
    {
        for (int j = 0x0100; j < 0x2000; j++)
        {
            cpu.resetState();
            cpu.setMemory(0x0000, 0x81);
            uint8_t previousStatusRegister = cpu.processStatusRegister;
            testByte = 0xAC;
            address = i;
            cpu.registerX = 0x01;
            word = j;
            cpu.registerA = testByte;
            cpu.setMemory(0x0001, address);
            cpu.setMemory(address + cpu.registerX + 1, (word >> 8u));
            cpu.setMemory(address + cpu.registerX, word);
            cpu.Cycle();
            ASSERT_EQ(cpu.readMemory(word), testByte);
            ASSERT_EQ(cpu.processStatusRegister, previousStatusRegister); 
        }
    }
}
TEST_F(CPU_OP_TEST, OP_91)                  // [WORD[nn]+y]=A
{
    for (int i = 2; i < 0xFF; i++)
    {
        for (int j = 0x0100; j < 0x1FFF; j++)
        {
            cpu.resetState();
            cpu.setMemory(0x0000, 0x91);
            uint8_t previousStatusRegister = cpu.processStatusRegister;
            testByte = 0xAC;
            address = i;
            cpu.registerY = 0x01;
            word = j;
            cpu.registerA = testByte;
            cpu.setMemory(0x0001, address);
            cpu.setMemory(address + 1, (word >> 8u));
            cpu.setMemory(address , word);
            cpu.Cycle();
            ASSERT_EQ(cpu.readMemory(word + cpu.registerY), testByte);
            ASSERT_EQ(cpu.processStatusRegister, previousStatusRegister); 
        }
    }
}
TEST_F(CPU_OP_TEST, OP_86)                  // [nn]=X
{
    for (int i = 1; i < 256; i++)
    {
        cpu.resetState();
        cpu.setMemory(0x0000, 0x86);
        uint8_t previousStatusRegister = cpu.processStatusRegister;
        testByte = 0xAC;
        cpu.registerX = testByte;
        address = i;
        cpu.setMemory(0x0001, address);
        cpu.Cycle();
        ASSERT_EQ(cpu.readMemory(address), testByte);
        ASSERT_EQ(cpu.processStatusRegister, previousStatusRegister);
    }
}
TEST_F(CPU_OP_TEST, OP_96)                  // [nn+Y]=X
{
    for (int i = 1; i < 256; i++)
    {
        for (int j = 1; j < 256; j++)
        {
            if( (i + j) % 0x100 > 1)
            {
                cpu.resetState();
                cpu.setMemory(0x0000, 0x96);
                uint8_t previousStatusRegister = cpu.processStatusRegister;
                testByte = 0xAC;
                cpu.registerX = testByte;
                cpu.registerY = j;
                address = i;
                cpu.setMemory(0x0001, address);
                cpu.Cycle();
                ASSERT_EQ(cpu.readMemory(address + cpu.registerY), testByte);
                ASSERT_EQ(cpu.processStatusRegister, previousStatusRegister);
            }
        }
    }
}
TEST_F(CPU_OP_TEST, OP_8E)                  // [nnnn]=X
{
    for (int i = 3; i < 0x1FFF; i++)
    {
        cpu.resetState();
        cpu.setMemory(0x0000, 0x8E);
        uint8_t previousStatusRegister = cpu.processStatusRegister;
        testByte = 0xAC;
        cpu.registerX = testByte;
        address16 = i;
        cpu.setMemory(0x0001, address16);
        cpu.setMemory(0x0002, (address16 >> 8u));
        cpu.Cycle();
        ASSERT_EQ(cpu.readMemory(address16), testByte);
        ASSERT_EQ(cpu.processStatusRegister, previousStatusRegister);
    }
}
TEST_F(CPU_OP_TEST, OP_84)                  // [nn]=Y
{
    for (int i = 1; i < 256; i++)
    {
        cpu.resetState();
        cpu.setMemory(0x0000, 0x84);
        uint8_t previousStatusRegister = cpu.processStatusRegister;
        testByte = 0xAC;
        cpu.registerY = testByte;
        address = i;
        cpu.setMemory(0x0001, address);
        cpu.Cycle();
        ASSERT_EQ(cpu.readMemory(address), testByte);
        ASSERT_EQ(cpu.processStatusRegister, previousStatusRegister);
    }
}
TEST_F(CPU_OP_TEST, OP_94)                  // [nn+X]=Y
{
    for (int i = 1; i < 256; i++)
    {
        for (int j = 1; j < 256; j++)
        {
            if( (i + j) % 0x100 > 1)
            {
                cpu.resetState();
                cpu.setMemory(0x0000, 0x94);
                uint8_t previousStatusRegister = cpu.processStatusRegister;
                testByte = 0xAC;
                cpu.registerY = testByte;
                cpu.registerX = j;
                address = i;
                cpu.setMemory(0x0001, address);
                cpu.Cycle();
                ASSERT_EQ(cpu.readMemory(address + cpu.registerX), testByte);
                ASSERT_EQ(cpu.processStatusRegister, previousStatusRegister);
            }
        }
    }
}
TEST_F(CPU_OP_TEST, OP_8C)                  // [nnnn]=Y
{
    for (int i = 3; i < 0x1FFF; i++)
    {
        cpu.resetState();
        cpu.setMemory(0x0000, 0x8C);
        uint8_t previousStatusRegister = cpu.processStatusRegister;
        testByte = 0xAC;
        cpu.registerY = testByte;
        address16 = i;
        cpu.setMemory(0x0001, address16);
        cpu.setMemory(0x0002, (address16 >> 8u));
        cpu.Cycle();
        ASSERT_EQ(cpu.readMemory(address16), testByte);
        ASSERT_EQ(cpu.processStatusRegister, previousStatusRegister);
    }
}

// Push/Pull

TEST_F(CPU_OP_TEST, OP_48)                  // [S]=A, S=S-1
{
    cpu.resetState();
    cpu.registerA = 0xFF;
    cpu.setMemory(0x0000, 0x48);
    cpu.Cycle();
    ASSERT_EQ(cpu.registerA, cpu.readMemory(cpu.stackPointer + 0x0101));
}
TEST_F(CPU_OP_TEST, OP_08)                  // [S]=P, S=S-1 (flags)
{
    cpu.resetState();
    cpu.setMemory(0x0000, 0x08);
    cpu.Cycle();
    ASSERT_EQ(cpu.readMemory(cpu.stackPointer + 0x0101), cpu.processStatusRegister | 0b00110000);
    ASSERT_EQ(cpu.stackPointer, 0xFE);
}
TEST_F(CPU_OP_TEST, OP_68)                  // S=S+1, A=[S]
{
    cpu.resetState();
    cpu.setMemory(0x0000, 0x68);
    cpu.setMemory(0x01FF, 0b10110001);
    --cpu.stackPointer;
    cpu.Cycle();
    ASSERT_EQ(cpu.registerA, 0b10110001);
    ASSERT_EQ(cpu.stackPointer, 0xFF);
}
TEST_F(CPU_OP_TEST, OP_28)                  // S=S+1, P=[S] (flags)
{
    cpu.resetState();
    cpu.setMemory(0x0000, 0x28);
    cpu.setMemory(0x01FF, 0b10110001);
    --cpu.stackPointer;
    cpu.Cycle();
    ASSERT_EQ(cpu.processStatusRegister, 0b10100001);
    ASSERT_EQ(cpu.stackPointer, 0xFF);
}

// Add memory to accumulator with carry

TEST_F(CPU_OP_TEST, OP_69)                  // A=A+C+nn
{

}
TEST_F(CPU_OP_TEST, OP_65)                  // A=A+C+[nn]
{

}
TEST_F(CPU_OP_TEST, OP_75)                  // A=A+C+[nn+X]
{

}
TEST_F(CPU_OP_TEST, OP_6D)                  // A=A+C+[nnnn]
{

}
TEST_F(CPU_OP_TEST, OP_7D)                  // A=A+C+[nnnn+X]
{

}
TEST_F(CPU_OP_TEST, OP_79)                  // A=A+C+[nnnn+Y]
{

}
TEST_F(CPU_OP_TEST, OP_61)                  // A=A+C+[word[nn+X]]
{

}
TEST_F(CPU_OP_TEST, OP_71)                  // A=A+C+[word[nn]+Y]
{

}

// Subtract memory from accumulator with borrow

TEST_F(CPU_OP_TEST, OP_E9)                  // A=A+C-1-nn
{

}
TEST_F(CPU_OP_TEST, OP_E5)                  // A=A+C-1-[nn]
{

}
TEST_F(CPU_OP_TEST, OP_F5)                  // A=A+C-1-[nn+X]
{

}
TEST_F(CPU_OP_TEST, OP_ED)                  // A=A+C-1-[nnnn]
{

}
TEST_F(CPU_OP_TEST, OP_FD)                  // A=A+C-1-[nnnn+X]
{

}
TEST_F(CPU_OP_TEST, OP_F9)                  // A=A+C-1-[nnnn+Y]
{

}
TEST_F(CPU_OP_TEST, OP_E1)                  // A=A+C-1-[word[nn+X]]
{

}
TEST_F(CPU_OP_TEST, OP_F1)                  // A=A+C-1-[word[nn]+Y]
{

}

// Logical AND memory with accumulator

TEST_F(CPU_OP_TEST, OP_29)                  // A=A AND nn
{

}
TEST_F(CPU_OP_TEST, OP_25)                  // A=A AND [nn]
{

}
TEST_F(CPU_OP_TEST, OP_35)                  // A=A AND [nn+X]
{

}
TEST_F(CPU_OP_TEST, OP_2D)                  // A=A AND [nnnn]
{

}
TEST_F(CPU_OP_TEST, OP_3D)                  // A=A AND [nnnn+X]
{

}
TEST_F(CPU_OP_TEST, OP_39)                  // A=A AND [nnnn+Y]
{

}
TEST_F(CPU_OP_TEST, OP_21)                  // A=A AND [word[nn+X]]
{

}
TEST_F(CPU_OP_TEST, OP_31)                  // A=A AND [word[nn]+Y]
{

}

// Exclusive-OR memory with accumulator

TEST_F(CPU_OP_TEST, OP_49)                  // A=A XOR nn
{

}
TEST_F(CPU_OP_TEST, OP_45)                  // A=A XOR [nn]
{

}
TEST_F(CPU_OP_TEST, OP_55)                  // A=A XOR [nn+X]
{

}
TEST_F(CPU_OP_TEST, OP_4D)                  // A=A XOR [nnnn]
{

}
TEST_F(CPU_OP_TEST, OP_5D)                  // A=A XOR [nnnn+X]
{

}
TEST_F(CPU_OP_TEST, OP_59)                  // A=A XOR [nnnn+Y]
{

}
TEST_F(CPU_OP_TEST, OP_41)                  // A=A XOR [word[nn+X]]
{

}
TEST_F(CPU_OP_TEST, OP_51)                  // A=A XOR [word[nn]+Y]
{

}

// Logical OR memory with accumulator

TEST_F(CPU_OP_TEST, OP_09)                  // A=A OR nn
{

}
TEST_F(CPU_OP_TEST, OP_05)                  // A=A OR [nn]
{

}
TEST_F(CPU_OP_TEST, OP_15)                  // A=A OR [nn+X]
{

}
TEST_F(CPU_OP_TEST, OP_0D)                  // A=A OR [nnnn]
{

}
TEST_F(CPU_OP_TEST, OP_1D)                  // A=A OR [nnnn+X]
{

}
TEST_F(CPU_OP_TEST, OP_19)                  // A=A OR [nnnn+Y]
{

}
TEST_F(CPU_OP_TEST, OP_01)                  // A=A OR [word[nn+X]]
{

}
TEST_F(CPU_OP_TEST, OP_11)                  // A=A OR [word[nn]+Y]
{

}

// Compare

TEST_F(CPU_OP_TEST, OP_C9)                  // A-nn
{

}
TEST_F(CPU_OP_TEST, OP_C5)                  // A-[nn]
{

}
TEST_F(CPU_OP_TEST, OP_D5)                  // A-[nn+X]
{

}
TEST_F(CPU_OP_TEST, OP_CD)                  // A-[nnnn]
{

}
TEST_F(CPU_OP_TEST, OP_DD)                  // A-[nnnn+X]
{

}
TEST_F(CPU_OP_TEST, OP_D9)                  // A-[nnnn+Y]
{

}
TEST_F(CPU_OP_TEST, OP_C1)                  // A-[word[nn+X]]
{

}
TEST_F(CPU_OP_TEST, OP_D1)                  // A-[word[nn]+Y]
{

}
TEST_F(CPU_OP_TEST, OP_E0)                  // X-nn
{

}
TEST_F(CPU_OP_TEST, OP_E4)                  // X-[nn]
{

}
TEST_F(CPU_OP_TEST, OP_EC)                  // X-[nnnn]
{

}
TEST_F(CPU_OP_TEST, OP_C0)                  // Y-nn
{

}
TEST_F(CPU_OP_TEST, OP_C4)                  // Y-[nn]
{

}
TEST_F(CPU_OP_TEST, OP_CC)                  // Y-[nnnn]
{

}

// Bit Test
// Flags are set as so: Z=((A AND [addr])=0x00), N=[addr].Bit7, V=[addr].Bit6. 
// Note that N and V are affected only by [addr] (not by A).

TEST_F(CPU_OP_TEST, OP_24)                  // test and set flags
{

}
TEST_F(CPU_OP_TEST, OP_2C)                  // test and set flags
{

}

// Increment by one

TEST_F(CPU_OP_TEST, OP_E6)                  // [nn]=[nn]+1
{

}
TEST_F(CPU_OP_TEST, OP_F6)                  // [nn+X]=[nn+X]+1
{

}
TEST_F(CPU_OP_TEST, OP_EE)                  // [nnnn]=[nnnn]+1
{

}
TEST_F(CPU_OP_TEST, OP_FE)                  // [nnnn+X]=[nnnn+X]+1
{

}
TEST_F(CPU_OP_TEST, OP_E8)                  // X=X+1
{

}
TEST_F(CPU_OP_TEST, OP_C8)                  // Y=Y+1
{

}

// Decrement by one

TEST_F(CPU_OP_TEST, OP_C6)                  // [nn]=[nn]-1
{

}
TEST_F(CPU_OP_TEST, OP_D6)                  // [nn+X]=[nn+X]-1
{

}
TEST_F(CPU_OP_TEST, OP_CE)                  // [nnnn]=[nnnn]-1
{

}
TEST_F(CPU_OP_TEST, OP_DE)                  // [nnnn+X]=[nnnn+X]-1
{

}
TEST_F(CPU_OP_TEST, OP_CA)                  // X=X-1
{

}
TEST_F(CPU_OP_TEST, OP_88)                  // Y=Y-1
{

}

// Shift Left Logical/Arithmetic

TEST_F(CPU_OP_TEST, OP_0A)                  // SHL A
{

}
TEST_F(CPU_OP_TEST, OP_06)                  // SHL [nn]
{

}
TEST_F(CPU_OP_TEST, OP_16)                  // SHL [nn+X]
{

}
TEST_F(CPU_OP_TEST, OP_0E)                  // SHL [nnnn]
{

}
TEST_F(CPU_OP_TEST, OP_1E)                  // SHL [nnnn+X]
{

}

// Shift Right Logical

TEST_F(CPU_OP_TEST, OP_4A)                  // SHR A
{

}
TEST_F(CPU_OP_TEST, OP_46)                  // SHR [nn]
{

}
TEST_F(CPU_OP_TEST, OP_56)                  // SHR [nn+X]
{

}
TEST_F(CPU_OP_TEST, OP_4E)                  // SHR [nnnn]
{

}
TEST_F(CPU_OP_TEST, OP_5E)                  // SHR [nnnn+X]
{

}

// Rotate Left through Carry

TEST_F(CPU_OP_TEST, OP_2A)                  // RCL A
{

}
TEST_F(CPU_OP_TEST, OP_26)                  // RCL [nn]
{

}
TEST_F(CPU_OP_TEST, OP_36)                  // RCL [nn+X]
{

}
TEST_F(CPU_OP_TEST, OP_2E)                  // RCL [nnnn]
{

}
TEST_F(CPU_OP_TEST, OP_3E)                  // RCL [nnnn+X]
{

}

// Rotate Right through Carry

TEST_F(CPU_OP_TEST, OP_6A)                  // RCR A
{

}
TEST_F(CPU_OP_TEST, OP_66)                  // RCR [nn]
{

}
TEST_F(CPU_OP_TEST, OP_76)                  // RCR [nn+X]
{

}
TEST_F(CPU_OP_TEST, OP_6E)                  // RCR [nnnn]
{

}
TEST_F(CPU_OP_TEST, OP_7E)                  // RCR [nnnn+X]
{

}

