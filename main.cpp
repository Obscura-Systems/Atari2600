#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include "CPU.h"
#include <gtest/gtest.h>

using namespace std;

CPU cpu;

uint8_t testByte = 0x00;

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
            testByte = rand();
        }
        ~CPU_OP_TEST() override
        {
            //cpu.reportStatus();
        }
};

// Register/Immediate to Register Transfer

TEST_F(CPU_OP_TEST, OP_A8)                  // Y=A. NZ
{

    cpu.setMemory(0x0000, 0xA8); 
    testByte = 0x00;          
    cpu.registerA = testByte;              
    cpu.Cycle();                           
    EXPECT_EQ(cpu.registerY, testByte);
    EXPECT_EQ(cpu.processStatusRegister, 0b00100010);
    cpu.resetState();

    cpu.setMemory(0x0000, 0xA8); 
    testByte = 0x0F;          
    cpu.registerA = testByte;              
    cpu.Cycle();                           
    EXPECT_EQ(cpu.registerY, testByte);
    EXPECT_EQ(cpu.processStatusRegister, 0b00100000);
    cpu.resetState();

    cpu.setMemory(0x0000, 0xA8); 
    testByte = 0x80;          
    cpu.registerA = testByte;              
    cpu.Cycle();                           
    EXPECT_EQ(cpu.registerY, testByte);
    EXPECT_EQ(cpu.processStatusRegister, 0b10100000);

}   
TEST_F(CPU_OP_TEST, OP_AA)                  // X=A. NZ
{
    cpu.setMemory(0x0000, 0xAA); 
    testByte = 0x00;       
    cpu.registerA = testByte;              
    cpu.Cycle();                           
    EXPECT_EQ(cpu.registerX, testByte);
    EXPECT_EQ(cpu.processStatusRegister, 0b00100010);
    cpu.resetState();    

    cpu.setMemory(0x0000, 0xAA); 
    testByte = 0x0F;       
    cpu.registerA = testByte;              
    cpu.Cycle();                           
    EXPECT_EQ(cpu.registerX, testByte);
    EXPECT_EQ(cpu.processStatusRegister, 0b00100000);
    cpu.resetState();  

    cpu.setMemory(0x0000, 0xAA); 
    testByte = 0x80;       
    cpu.registerA = testByte;              
    cpu.Cycle();                           
    EXPECT_EQ(cpu.registerX, testByte);
    EXPECT_EQ(cpu.processStatusRegister, 0b10100000);   
}
TEST_F(CPU_OP_TEST, OP_BA)                  // X=S NZ
{
    cpu.setMemory(0x0000, 0xBA);   
    testByte = 0x00;   
    cpu.stackPointer = testByte;           
    cpu.Cycle();                            
    EXPECT_EQ(cpu.registerX, testByte);    
    EXPECT_EQ(cpu.processStatusRegister, 0b00100010); 
    cpu.resetState();

    cpu.setMemory(0x0000, 0xBA);   
    testByte = 0x0F;   
    cpu.stackPointer = testByte;           
    cpu.Cycle();                            
    EXPECT_EQ(cpu.registerX, testByte);    
    EXPECT_EQ(cpu.processStatusRegister, 0b00100000); 
    cpu.resetState();

    cpu.setMemory(0x0000, 0xBA);   
    testByte = 0x80;   
    cpu.stackPointer = testByte;           
    cpu.Cycle();                            
    EXPECT_EQ(cpu.registerX, testByte);    
    EXPECT_EQ(cpu.processStatusRegister, 0b10100000); 
}
TEST_F(CPU_OP_TEST, OP_98)                  // A=Y NZ
{
    cpu.setMemory(0x0000, 0x98);  
    testByte = 0x00;           
    cpu.registerY = testByte;             
    cpu.Cycle();                           
    EXPECT_EQ(cpu.registerA, testByte);
    EXPECT_EQ(cpu.processStatusRegister, 0b00100010); 
    cpu.resetState();

    cpu.setMemory(0x0000, 0x98);  
    testByte = 0x0F;           
    cpu.registerY = testByte;             
    cpu.Cycle();                           
    EXPECT_EQ(cpu.registerA, testByte);
    EXPECT_EQ(cpu.processStatusRegister, 0b00100000); 
    cpu.resetState();

    cpu.setMemory(0x0000, 0x98);  
    testByte = 0x80;           
    cpu.registerY = testByte;             
    cpu.Cycle();                           
    EXPECT_EQ(cpu.registerA, testByte);
    EXPECT_EQ(cpu.processStatusRegister, 0b10100000); 
}
TEST_F(CPU_OP_TEST, OP_8A)                  // A=X NZ
{
    cpu.setMemory(0x0000, 0x8A);   
    testByte = 0x00;        
    cpu.registerX = testByte;             
    cpu.Cycle();                           
    EXPECT_EQ(cpu.registerA, testByte);  
    EXPECT_EQ(cpu.processStatusRegister, 0b00100010); 
    cpu.resetState();  

    cpu.setMemory(0x0000, 0x8A);   
    testByte = 0x0F;        
    cpu.registerX = testByte;             
    cpu.Cycle();                           
    EXPECT_EQ(cpu.registerA, testByte);  
    EXPECT_EQ(cpu.processStatusRegister, 0b00100000); 
    cpu.resetState();  

    cpu.setMemory(0x0000, 0x8A);   
    testByte = 0x80;        
    cpu.registerX = testByte;             
    cpu.Cycle();                           
    EXPECT_EQ(cpu.registerA, testByte);  
    EXPECT_EQ(cpu.processStatusRegister, 0b10100000); 
}
TEST_F(CPU_OP_TEST, OP_9A)                  // S=X
{
    cpu.setMemory(0x0000, 0x9A);           
    cpu.registerX = testByte;             
    cpu.Cycle();                            
    EXPECT_EQ(cpu.stackPointer, testByte);    
}
TEST_F(CPU_OP_TEST, OP_A9)                  // A=nn NZ
{
    cpu.setMemory(0x0000, 0xA9);
    testByte = 0x00;            
    cpu.setMemory(0x0001 ,testByte);             
    cpu.Cycle();                           
    EXPECT_EQ(cpu.registerA, testByte);   
    EXPECT_EQ(cpu.processStatusRegister, 0b00100010); 
    cpu.resetState();  

    cpu.setMemory(0x0000, 0xA9);
    testByte = 0x0F;            
    cpu.setMemory(0x0001 ,testByte);             
    cpu.Cycle();                           
    EXPECT_EQ(cpu.registerA, testByte);   
    EXPECT_EQ(cpu.processStatusRegister, 0b00100000); 
    cpu.resetState();

    cpu.setMemory(0x0000, 0xA9);
    testByte = 0x80;            
    cpu.setMemory(0x0001 ,testByte);             
    cpu.Cycle();                           
    EXPECT_EQ(cpu.registerA, testByte);   
    EXPECT_EQ(cpu.processStatusRegister, 0b10100000); 
}
TEST_F(CPU_OP_TEST, OP_A2)                  // X=nn NZ
{
    cpu.setMemory(0x0000, 0xA2);
    testByte = 0x00;            
    cpu.setMemory(0x0001 ,testByte);             
    cpu.Cycle();                           
    EXPECT_EQ(cpu.registerX, testByte);   
    EXPECT_EQ(cpu.processStatusRegister, 0b00100010); 
    cpu.resetState();  

    cpu.setMemory(0x0000, 0xA2);
    testByte = 0x0F;            
    cpu.setMemory(0x0001 ,testByte);             
    cpu.Cycle();                           
    EXPECT_EQ(cpu.registerX, testByte);   
    EXPECT_EQ(cpu.processStatusRegister, 0b00100000); 
    cpu.resetState();

    cpu.setMemory(0x0000, 0xA2);
    testByte = 0x80;            
    cpu.setMemory(0x0001 ,testByte);             
    cpu.Cycle();                           
    EXPECT_EQ(cpu.registerX, testByte);   
    EXPECT_EQ(cpu.processStatusRegister, 0b10100000);     
}
TEST_F(CPU_OP_TEST, OP_A0)                  // Y=nn NZ
{
    cpu.setMemory(0x0000, 0xA0);
    testByte = 0x00;            
    cpu.setMemory(0x0001 ,testByte);             
    cpu.Cycle();                           
    EXPECT_EQ(cpu.registerY, testByte);   
    EXPECT_EQ(cpu.processStatusRegister, 0b00100010); 
    cpu.resetState();  

    cpu.setMemory(0x0000, 0xA0);
    testByte = 0x0F;            
    cpu.setMemory(0x0001 ,testByte);             
    cpu.Cycle();                           
    EXPECT_EQ(cpu.registerY, testByte);   
    EXPECT_EQ(cpu.processStatusRegister, 0b00100000); 
    cpu.resetState();

    cpu.setMemory(0x0000, 0xA0);
    testByte = 0x80;            
    cpu.setMemory(0x0001 ,testByte);             
    cpu.Cycle();                           
    EXPECT_EQ(cpu.registerY, testByte);   
    EXPECT_EQ(cpu.processStatusRegister, 0b10100000);   
}

// Load Register from Memory

TEST_F(CPU_OP_TEST, OP_A5)                  // A=[nn] NZ
{
    cpu.setMemory(0x0000, 0xA5);
    uint8_t address = rand() % (0xFE - 0x04) + 0x04;
    testByte = 0x00;
    cpu.setMemory(0x0001, address);
    cpu.setMemory(address, testByte);
    cpu.Cycle();
    EXPECT_EQ(cpu.registerA, testByte);
    EXPECT_EQ(cpu.processStatusRegister, 0b00100010); 
    cpu.resetState();  

    cpu.setMemory(0x0000, 0xA5);
    address = rand() % (0xFE - 0x04) + 0x04;
    testByte = 0x0F;
    cpu.setMemory(0x0001, address);
    cpu.setMemory(address, testByte);
    cpu.Cycle();
    EXPECT_EQ(cpu.registerA, testByte);
    EXPECT_EQ(cpu.processStatusRegister, 0b00100000); 
    cpu.resetState();  

    cpu.setMemory(0x0000, 0xA5);
    address = rand() % (0xFE - 0x04) + 0x04;
    testByte = 0x80;
    cpu.setMemory(0x0001, address);
    cpu.setMemory(address, testByte);
    cpu.Cycle();
    EXPECT_EQ(cpu.registerA, testByte);
    EXPECT_EQ(cpu.processStatusRegister, 0b10100000); 
}
TEST_F(CPU_OP_TEST, OP_B5)                  // A=[nn+X] NZ
{
    cpu.setMemory(0x0000, 0xB5);
    cpu.registerX = rand();
    uint8_t address = rand();
    while (cpu.registerX + address <=3)
    {
        address = rand();
    }
    testByte = 0x00;
    cpu.setMemory(0x0001, address);
    cpu.setMemory((address + cpu.registerX), testByte);
    cpu.Cycle();
    EXPECT_EQ(cpu.registerA, testByte);
    EXPECT_EQ(cpu.processStatusRegister, 0b00100010); 
    cpu.resetState();  

    cpu.setMemory(0x0000, 0xB5);
    cpu.registerX = rand();
    address = rand();
    while (cpu.registerX + address <=3)
    {
        address = rand();
    }
    testByte = 0x0F;
    cpu.setMemory(0x0001, address);
    cpu.setMemory((address + cpu.registerX), testByte);
    cpu.Cycle();
    EXPECT_EQ(cpu.registerA, testByte);
    EXPECT_EQ(cpu.processStatusRegister, 0b00100000); 
    cpu.resetState();  

    cpu.setMemory(0x0000, 0xB5);
    cpu.registerX = rand();
    address = rand();
    while (cpu.registerX + address <=3)
    {
        address = rand();
    }
    testByte = 0x80;
    cpu.setMemory(0x0001, address);
    cpu.setMemory((address + cpu.registerX), testByte);
    cpu.Cycle();
    EXPECT_EQ(cpu.registerA, testByte);
    EXPECT_EQ(cpu.processStatusRegister, 0b10100000);
}
TEST_F(CPU_OP_TEST, OP_AD)                  // A=[nnnn] NZ
{
    cpu.setMemory(0x0000, 0xAD);
    uint16_t address = rand() % (0xFFFE - 0x0004) + 0x0004;
    testByte = 0x00;
    cpu.setMemory(0x0001, address);
    cpu.setMemory(0x0002, (address >> 8u));
    cpu.setMemory(address, testByte);
    cpu.Cycle();
    EXPECT_EQ(cpu.registerA, testByte);
    EXPECT_EQ(cpu.processStatusRegister, 0b00100010); 
    cpu.resetState();  

    cpu.setMemory(0x0000, 0xAD);
    address = rand() % (0xFFFE - 0x0004) + 0x0004;
    testByte = 0x0F;
    cpu.setMemory(0x0001, address);
    cpu.setMemory(0x0002, (address >> 8u));
    cpu.setMemory(address, testByte);
    cpu.Cycle();
    EXPECT_EQ(cpu.registerA, testByte);
    EXPECT_EQ(cpu.processStatusRegister, 0b00100000); 
    cpu.resetState();  

    cpu.setMemory(0x0000, 0xAD);
    address = rand() % (0xFFFE - 0x0004) + 0x0004;
    testByte = 0x80;
    cpu.setMemory(0x0001, address);
    cpu.setMemory(0x0002, (address >> 8u));
    cpu.setMemory(address, testByte);
    cpu.Cycle();
    EXPECT_EQ(cpu.registerA, testByte);
    EXPECT_EQ(cpu.processStatusRegister, 0b10100000);
}
TEST_F(CPU_OP_TEST, OP_BD)                  // A=[nnnn+X] NZ
{
    cpu.setMemory(0x0000, 0xBD);
    uint16_t address = rand();
    cpu.registerX = rand();
    while (cpu.registerX + address <= 0x03 || cpu.registerX + address == 0xFFFF)
    {
        address = rand();
    }
    testByte = 0x00;
    cpu.setMemory(0x0001, address);
    cpu.setMemory(0x0002, (address >> 8u));
    cpu.setMemory(address + cpu.registerX, testByte);
    cpu.Cycle();
    EXPECT_EQ(cpu.registerA, testByte);
    EXPECT_EQ(cpu.processStatusRegister, 0b00100010); 
    cpu.resetState(); 

    cpu.setMemory(0x0000, 0xBD);
    address = rand();
    cpu.registerX = rand();
    while (cpu.registerX + address <= 0x03 || cpu.registerX + address == 0xFFFF)
    {
        address = rand();
    }
    testByte = 0x0F;
    cpu.setMemory(0x0001, address);
    cpu.setMemory(0x0002, (address >> 8u));
    cpu.setMemory(address + cpu.registerX, testByte);
    cpu.Cycle();
    EXPECT_EQ(cpu.registerA, testByte);
    EXPECT_EQ(cpu.processStatusRegister, 0b00100000); 
    cpu.resetState(); 

    cpu.setMemory(0x0000, 0xBD);
    address = rand();
    cpu.registerX = rand();
    while (cpu.registerX + address <= 0x03 || cpu.registerX + address == 0xFFFF)
    {
        address = rand();
    }
    testByte = 0x80;
    cpu.setMemory(0x0001, address);
    cpu.setMemory(0x0002, (address >> 8u));
    cpu.setMemory(address + cpu.registerX, testByte);
    cpu.Cycle();
    EXPECT_EQ(cpu.registerA, testByte);
    EXPECT_EQ(cpu.processStatusRegister, 0b10100000); 
}
TEST_F(CPU_OP_TEST, OP_B9)                  // A=[nnnn+Y] NZ
{
    cpu.setMemory(0x0000, 0xB9);
    uint16_t address = rand();
    cpu.registerY = rand();
    while (cpu.registerY + address <= 0x03 || cpu.registerX + address == 0xFFFF)
    {
        address = rand();
    }
    testByte = 0x00;
    cpu.setMemory(0x0001, address);
    cpu.setMemory(0x0002, (address >> 8u));
    cpu.setMemory(address + cpu.registerY, testByte);
    cpu.Cycle();
    EXPECT_EQ(cpu.registerA, testByte);
    EXPECT_EQ(cpu.processStatusRegister, 0b00100010); 
    cpu.resetState();

    cpu.setMemory(0x0000, 0xB9);
    address = rand();
    cpu.registerY = rand();
    while (cpu.registerY + address <= 0x03 || cpu.registerX + address == 0xFFFF)
    {
        address = rand();
    }
    testByte = 0x0F;
    cpu.setMemory(0x0001, address);
    cpu.setMemory(0x0002, (address >> 8u));
    cpu.setMemory(address + cpu.registerY, testByte);
    cpu.Cycle();
    EXPECT_EQ(cpu.registerA, testByte);
    EXPECT_EQ(cpu.processStatusRegister, 0b00100000); 
    cpu.resetState(); 

    cpu.setMemory(0x0000, 0xB9);
    address = rand();
    cpu.registerY = rand();
    while (cpu.registerY + address <= 0x03 || cpu.registerX + address == 0xFFFF)
    {
        address = rand();
    }
    testByte = 0x80;
    cpu.setMemory(0x0001, address);
    cpu.setMemory(0x0002, (address >> 8u));
    cpu.setMemory(address + cpu.registerY, testByte);
    cpu.Cycle();
    EXPECT_EQ(cpu.registerA, testByte);
    EXPECT_EQ(cpu.processStatusRegister, 0b10100000); 
}
TEST_F(CPU_OP_TEST, OP_A1)                  // A=[WORD[nn+X]] NZ
{
    cpu.setMemory(0x0000, 0xA1);
    uint8_t address = rand();
    uint16_t word = rand() % (0xFFFE - 0x0004) + 0x0004;
    cpu.registerX = rand();
    while (cpu.registerX + address <= 0x03 || cpu.registerX + address == 0xFF)
    {
        address = rand();
    }
    testByte = 0x00;
    cpu.setMemory(0x0001, address);
    cpu.setMemory(address + cpu.registerX + 1, (word >> 8u));
    cpu.setMemory(address + cpu.registerX, word);
    cpu.setMemory(word, testByte);
    cpu.Cycle();
    EXPECT_EQ(cpu.registerA, testByte);
    EXPECT_EQ(cpu.processStatusRegister, 0b00100010); 
    cpu.resetState();

    cpu.setMemory(0x0000, 0xA1);
    address = rand();
    word = rand() % (0xFFFE - 0x0004) + 0x0004;
    cpu.registerX = rand();
    while (cpu.registerX + address <= 0x03 || cpu.registerX + address == 0xFF)
    {
        address = rand();
    }
    testByte = 0x0F;
    cpu.setMemory(0x0001, address);
    cpu.setMemory(address + cpu.registerX + 1, (word >> 8u));
    cpu.setMemory(address + cpu.registerX, word);
    cpu.setMemory(word, testByte);
    cpu.Cycle();
    EXPECT_EQ(cpu.registerA, testByte);
    EXPECT_EQ(cpu.processStatusRegister, 0b00100000); 
    cpu.resetState();

    cpu.setMemory(0x0000, 0xA1);
    address = rand();
    word = rand() % (0xFFFE - 0x0004) + 0x0004;
    cpu.registerX = rand();
    while (cpu.registerX + address <= 0x03 || cpu.registerX + address == 0xFF)
    {
        address = rand();
    }
    testByte = 0x80;
    cpu.setMemory(0x0001, address);
    cpu.setMemory(address + cpu.registerX + 1, (word >> 8u));
    cpu.setMemory(address + cpu.registerX, word);
    cpu.setMemory(word, testByte);
    cpu.Cycle();
    EXPECT_EQ(cpu.registerA, testByte);
    EXPECT_EQ(cpu.processStatusRegister, 0b10100000);
}
TEST_F(CPU_OP_TEST, OP_B1)                  // A=[WORD[nn]+Y] NZ
{
    cpu.setMemory(0x0000, 0xB1);
    uint8_t address = rand();
    uint16_t word = rand() % (0xFFFE - 0x0004) + 0x0004;
    cpu.registerY = rand();
    while (cpu.registerY + word <= 0x03 || cpu.registerY + word == 0xFFFF)
    {
        cpu.registerY = rand();
    }
    testByte = 0x00;
    cpu.setMemory(0x0001, address);
    cpu.setMemory(address + 1, (word >> 8u));
    cpu.setMemory(address , word);
    cpu.setMemory(word + cpu.registerY, testByte);
    cpu.Cycle();
    EXPECT_EQ(cpu.registerA, testByte);
    EXPECT_EQ(cpu.processStatusRegister, 0b00100010); 
    cpu.resetState();

    cpu.setMemory(0x0000, 0xB1);
    address = rand();
    word = rand() % (0xFFFE - 0x0004) + 0x0004;
    cpu.registerY = rand();
    while (cpu.registerY + word <= 0x03 || cpu.registerY + word == 0xFFFF)
    {
        cpu.registerY = rand();
    }
    testByte = 0x0F;
    cpu.setMemory(0x0001, address);
    cpu.setMemory(address + 1, (word >> 8u));
    cpu.setMemory(address , word);
    cpu.setMemory(word + cpu.registerY, testByte);
    cpu.Cycle();
    EXPECT_EQ(cpu.registerA, testByte);
    EXPECT_EQ(cpu.processStatusRegister, 0b00100000); 
    cpu.resetState();

    cpu.setMemory(0x0000, 0xB1);
    address = rand();
    word = rand() % (0xFFFE - 0x0004) + 0x0004;
    cpu.registerY = rand();
    while (cpu.registerY + word <= 0x03 || cpu.registerY + word == 0xFFFF)
    {
        cpu.registerY = rand();
    }
    testByte = 0x80;
    cpu.setMemory(0x0001, address);
    cpu.setMemory(address + 1, (word >> 8u));
    cpu.setMemory(address , word);
    cpu.setMemory(word + cpu.registerY, testByte);
    cpu.Cycle();
    EXPECT_EQ(cpu.registerA, testByte);
    EXPECT_EQ(cpu.processStatusRegister, 0b10100000); 
}
TEST_F(CPU_OP_TEST, OP_A6)                  // X=[nn] NZ
{
    cpu.setMemory(0x0000, 0xA6);
    uint8_t address = rand() % (0xFE - 0x04) + 0x04;
    testByte = 0x00;
    cpu.setMemory(0x0001, address);
    cpu.setMemory(address, testByte);
    cpu.Cycle();
    EXPECT_EQ(cpu.registerX, testByte);
    EXPECT_EQ(cpu.processStatusRegister, 0b00100010); 
    cpu.resetState();  

    cpu.setMemory(0x0000, 0xA6);
    address = rand() % (0xFE - 0x04) + 0x04;
    testByte = 0x0F;
    cpu.setMemory(0x0001, address);
    cpu.setMemory(address, testByte);
    cpu.Cycle();
    EXPECT_EQ(cpu.registerX, testByte);
    EXPECT_EQ(cpu.processStatusRegister, 0b00100000); 
    cpu.resetState();  

    cpu.setMemory(0x0000, 0xA6);
    address = rand() % (0xFE - 0x04) + 0x04;
    testByte = 0x80;
    cpu.setMemory(0x0001, address);
    cpu.setMemory(address, testByte);
    cpu.Cycle();
    EXPECT_EQ(cpu.registerX, testByte);
    EXPECT_EQ(cpu.processStatusRegister, 0b10100000); 
}
TEST_F(CPU_OP_TEST, OP_B6)                  // X=[nn+Y] NZ
{
    cpu.setMemory(0x0000, 0xB6);
    cpu.registerY = rand();
    uint8_t address = rand();
    while (cpu.registerY + address <=3)
    {
        address = rand();
    }
    testByte = 0x00;
    cpu.setMemory(0x0001, address);
    cpu.setMemory((address + cpu.registerY), testByte);
    cpu.Cycle();
    EXPECT_EQ(cpu.registerX, testByte);
    EXPECT_EQ(cpu.processStatusRegister, 0b00100010); 
    cpu.resetState();  

    cpu.setMemory(0x0000, 0xB6);
    cpu.registerY = rand();
    address = rand();
    while (cpu.registerY + address <=3)
    {
        address = rand();
    }
    testByte = 0x0F;
    cpu.setMemory(0x0001, address);
    cpu.setMemory((address + cpu.registerY), testByte);
    cpu.Cycle();
    EXPECT_EQ(cpu.registerX, testByte);
    EXPECT_EQ(cpu.processStatusRegister, 0b00100000); 
    cpu.resetState();  

    cpu.setMemory(0x0000, 0xB6);
    cpu.registerY = rand();
    address = rand();
    while (cpu.registerY + address <=3)
    {
        address = rand();
    }
    testByte = 0x80;
    cpu.setMemory(0x0001, address);
    cpu.setMemory((address + cpu.registerY), testByte);
    cpu.Cycle();
    EXPECT_EQ(cpu.registerX, testByte);
    EXPECT_EQ(cpu.processStatusRegister, 0b10100000);
}
TEST_F(CPU_OP_TEST, OP_AE)                  // X=[nnnn] NZ
{
    cpu.setMemory(0x0000, 0xAE);
    uint16_t address = rand() % (0xFFFE - 0x0004) + 0x0004;
    testByte = 0x00;
    cpu.setMemory(0x0001, address);
    cpu.setMemory(0x0002, (address >> 8u));
    cpu.setMemory(address, testByte);
    cpu.Cycle();
    EXPECT_EQ(cpu.registerX, testByte);
    EXPECT_EQ(cpu.processStatusRegister, 0b00100010); 
    cpu.resetState();  

    cpu.setMemory(0x0000, 0xAE);
    address = rand() % (0xFFFE - 0x0004) + 0x0004;
    testByte = 0x0F;
    cpu.setMemory(0x0001, address);
    cpu.setMemory(0x0002, (address >> 8u));
    cpu.setMemory(address, testByte);
    cpu.Cycle();
    EXPECT_EQ(cpu.registerX, testByte);
    EXPECT_EQ(cpu.processStatusRegister, 0b00100000); 
    cpu.resetState();  

    cpu.setMemory(0x0000, 0xAE);
    address = rand() % (0xFFFE - 0x0004) + 0x0004;
    testByte = 0x80;
    cpu.setMemory(0x0001, address);
    cpu.setMemory(0x0002, (address >> 8u));
    cpu.setMemory(address, testByte);
    cpu.Cycle();
    EXPECT_EQ(cpu.registerX, testByte);
    EXPECT_EQ(cpu.processStatusRegister, 0b10100000);
}
TEST_F(CPU_OP_TEST, OP_BE)                  // X=[nnnn+Y] NZ
{
    cpu.setMemory(0x0000, 0xBE);
    uint16_t address = rand();
    cpu.registerY = rand();
    while (cpu.registerY + address <= 0x03 || cpu.registerY + address == 0xFFFF)
    {
        address = rand();
    }
    testByte = 0x00;
    cpu.setMemory(0x0001, address);
    cpu.setMemory(0x0002, (address >> 8u));
    cpu.setMemory(address + cpu.registerY, testByte);
    cpu.Cycle();
    EXPECT_EQ(cpu.registerX, testByte);
    EXPECT_EQ(cpu.processStatusRegister, 0b00100010); 
    cpu.resetState(); 

    cpu.setMemory(0x0000, 0xBE);
    address = rand();
    cpu.registerY = rand();
    while (cpu.registerY + address <= 0x03 || cpu.registerY + address == 0xFFFF)
    {
        address = rand();
    }
    testByte = 0x0F;
    cpu.setMemory(0x0001, address);
    cpu.setMemory(0x0002, (address >> 8u));
    cpu.setMemory(address + cpu.registerY, testByte);
    cpu.Cycle();
    EXPECT_EQ(cpu.registerX, testByte);
    EXPECT_EQ(cpu.processStatusRegister, 0b00100000); 
    cpu.resetState(); 

    cpu.setMemory(0x0000, 0xBE);
    address = rand();
    cpu.registerY = rand();
    while (cpu.registerY + address <= 0x03 || cpu.registerY + address == 0xFFFF)
    {
        address = rand();
    }
    testByte = 0x80;
    cpu.setMemory(0x0001, address);
    cpu.setMemory(0x0002, (address >> 8u));
    cpu.setMemory(address + cpu.registerY, testByte);
    cpu.Cycle();
    EXPECT_EQ(cpu.registerX, testByte);
    EXPECT_EQ(cpu.processStatusRegister, 0b10100000); 
}
TEST_F(CPU_OP_TEST, OP_A4)                  // Y=[nn] NZ
{
    cpu.setMemory(0x0000, 0xA4);
    uint8_t address = rand() % (0xFE - 0x04) + 0x04;
    testByte = 0x00;
    cpu.setMemory(0x0001, address);
    cpu.setMemory(address, testByte);
    cpu.Cycle();
    EXPECT_EQ(cpu.registerY, testByte);
    EXPECT_EQ(cpu.processStatusRegister, 0b00100010); 
    cpu.resetState();  

    cpu.setMemory(0x0000, 0xA4);
    address = rand() % (0xFE - 0x04) + 0x04;
    testByte = 0x0F;
    cpu.setMemory(0x0001, address);
    cpu.setMemory(address, testByte);
    cpu.Cycle();
    EXPECT_EQ(cpu.registerY, testByte);
    EXPECT_EQ(cpu.processStatusRegister, 0b00100000); 
    cpu.resetState();  

    cpu.setMemory(0x0000, 0xA4);
    address = rand() % (0xFE - 0x04) + 0x04;
    testByte = 0x80;
    cpu.setMemory(0x0001, address);
    cpu.setMemory(address, testByte);
    cpu.Cycle();
    EXPECT_EQ(cpu.registerY, testByte);
    EXPECT_EQ(cpu.processStatusRegister, 0b10100000);
}
TEST_F(CPU_OP_TEST, OP_B4)                  // Y=[nn+X] NZ
{
    cpu.setMemory(0x0000, 0xB4);
    cpu.registerX = rand();
    uint8_t address = rand();
    while (cpu.registerX + address <=3)
    {
        address = rand();
    }
    testByte = 0x00;
    cpu.setMemory(0x0001, address);
    cpu.setMemory((address + cpu.registerX), testByte);
    cpu.Cycle();
    EXPECT_EQ(cpu.registerY, testByte);
    EXPECT_EQ(cpu.processStatusRegister, 0b00100010); 
    cpu.resetState();  

    cpu.setMemory(0x0000, 0xB4);
    cpu.registerX = rand();
    address = rand();
    while (cpu.registerX + address <=3)
    {
        address = rand();
    }
    testByte = 0x0F;
    cpu.setMemory(0x0001, address);
    cpu.setMemory((address + cpu.registerX), testByte);
    cpu.Cycle();
    EXPECT_EQ(cpu.registerY, testByte);
    EXPECT_EQ(cpu.processStatusRegister, 0b00100000); 
    cpu.resetState();  

    cpu.setMemory(0x0000, 0xB4);
    cpu.registerX = rand();
    address = rand();
    while (cpu.registerX + address <=3)
    {
        address = rand();
    }
    testByte = 0x80;
    cpu.setMemory(0x0001, address);
    cpu.setMemory((address + cpu.registerX), testByte);
    cpu.Cycle();
    EXPECT_EQ(cpu.registerY, testByte);
    EXPECT_EQ(cpu.processStatusRegister, 0b10100000);
}
TEST_F(CPU_OP_TEST, OP_AC)                  // Y=[nnnn] NZ
{
    cpu.setMemory(0x0000, 0xAC);
    uint16_t address = rand() % (0xFFFE - 0x0004) + 0x0004;
    testByte = 0x00;
    cpu.setMemory(0x0001, address);
    cpu.setMemory(0x0002, (address >> 8u));
    cpu.setMemory(address, testByte);
    cpu.Cycle();
    EXPECT_EQ(cpu.registerY, testByte);
    EXPECT_EQ(cpu.processStatusRegister, 0b00100010); 
    cpu.resetState();  

    cpu.setMemory(0x0000, 0xAC);
    address = rand() % (0xFFFE - 0x0004) + 0x0004;
    testByte = 0x0F;
    cpu.setMemory(0x0001, address);
    cpu.setMemory(0x0002, (address >> 8u));
    cpu.setMemory(address, testByte);
    cpu.Cycle();
    EXPECT_EQ(cpu.registerY, testByte);
    EXPECT_EQ(cpu.processStatusRegister, 0b00100000); 
    cpu.resetState();  

    cpu.setMemory(0x0000, 0xAC);
    address = rand() % (0xFFFE - 0x0004) + 0x0004;
    testByte = 0x80;
    cpu.setMemory(0x0001, address);
    cpu.setMemory(0x0002, (address >> 8u));
    cpu.setMemory(address, testByte);
    cpu.Cycle();
    EXPECT_EQ(cpu.registerY, testByte);
    EXPECT_EQ(cpu.processStatusRegister, 0b10100000);
}
TEST_F(CPU_OP_TEST, OP_BC)                  // Y=[nnnn+X] NZ
{
    cpu.setMemory(0x0000, 0xBC);
    uint16_t address = rand();
    cpu.registerX = rand();
    while (cpu.registerX + address <= 0x03 || cpu.registerX + address == 0xFFFF)
    {
        address = rand();
    }
    testByte = 0x00;
    cpu.setMemory(0x0001, address);
    cpu.setMemory(0x0002, (address >> 8u));
    cpu.setMemory(address + cpu.registerX, testByte);
    cpu.Cycle();
    EXPECT_EQ(cpu.registerY, testByte);
    EXPECT_EQ(cpu.processStatusRegister, 0b00100010); 
    cpu.resetState(); 

    cpu.setMemory(0x0000, 0xBC);
    address = rand();
    cpu.registerX = rand();
    while (cpu.registerX + address <= 0x03 || cpu.registerX + address == 0xFFFF)
    {
        address = rand();
    }
    testByte = 0x0F;
    cpu.setMemory(0x0001, address);
    cpu.setMemory(0x0002, (address >> 8u));
    cpu.setMemory(address + cpu.registerX, testByte);
    cpu.Cycle();
    EXPECT_EQ(cpu.registerY, testByte);
    EXPECT_EQ(cpu.processStatusRegister, 0b00100000); 
    cpu.resetState(); 

    cpu.setMemory(0x0000, 0xBC);
    address = rand();
    cpu.registerX = rand();
    while (cpu.registerX + address <= 0x03 || cpu.registerX + address == 0xFFFF)
    {
        address = rand();
    }
    testByte = 0x80;
    cpu.setMemory(0x0001, address);
    cpu.setMemory(0x0002, (address >> 8u));
    cpu.setMemory(address + cpu.registerX, testByte);
    cpu.Cycle();
    EXPECT_EQ(cpu.registerY, testByte);
    EXPECT_EQ(cpu.processStatusRegister, 0b10100000); 
}

// Store Register in Memory

TEST_F(CPU_OP_TEST, OP_85)                  // [nn]=A
{

}
TEST_F(CPU_OP_TEST, OP_95)                  // [nn+X]=A
{

}
TEST_F(CPU_OP_TEST, OP_8D)                  // [nnnn]=A
{

}
TEST_F(CPU_OP_TEST, OP_9D)                  // [nnnn+X]=A
{

}
TEST_F(CPU_OP_TEST, OP_99)                  // [nnnn+Y]=A
{

}
TEST_F(CPU_OP_TEST, OP_81)                  // [WORD[nn+x]]=A
{

}
TEST_F(CPU_OP_TEST, OP_91)                  // [WORD[nn]+y]=A
{

}
TEST_F(CPU_OP_TEST, OP_86)                  // [nn]=X
{

}
TEST_F(CPU_OP_TEST, OP_96)                  // [nn+Y]=X
{

}
TEST_F(CPU_OP_TEST, OP_8E)                  // [nnnn]=X
{

}
TEST_F(CPU_OP_TEST, OP_84)                  // [nn]=Y
{

}
TEST_F(CPU_OP_TEST, OP_94)                  // [nn+X]=Y
{

}
TEST_F(CPU_OP_TEST, OP_8C)                  // [nnnn]=Y
{

}

// Push/Pull

TEST_F(CPU_OP_TEST, OP_48)                  // [S]=A, S=S-1
{

}
TEST_F(CPU_OP_TEST, OP_08)                  // [S]=P, S=S-1 (flags)
{

}
TEST_F(CPU_OP_TEST, OP_68)                  // S=S+1, A=[S]
{

}
TEST_F(CPU_OP_TEST, OP_28)                  // S=S+1, P=[S] (flags)
{

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

