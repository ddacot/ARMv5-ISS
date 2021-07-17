#include "testinstructions.h"
#include "computer.h"
#include <QDebug>
#include "instruction.h"
testinstructions::testinstructions()
{
    comp = new computer();
    //comp->regs.WriteWord(R15, 0);
    //qDebug() << comp->regs.ReadWord(R15);
//    testMOV();
//    testADD();
//    testMVN();
//    testSUB();
//    testRSB();
//    testMUL();
//    testAND();
//    testORR();
//    testEOR();
//    testBIC();
//    testSTR();
//    testLDR();
//    testSTM();
//    testLDM();

//    testB();
//    testBX();
//    testCMP();

    //testMRS();
    //testMSR();
    //testMOVS();

    //testUXTH();
    //testUXTB();
    //testUXTAH();
    //testUXTAB();
    //testUHADD();
    //testUHADDSUBX();
     testUHSUB();

}

void testinstructions::testUHSUB()
{
    comp->restart();
    comp->regs.WriteWord(comp->cpu.GET_REG_ADDR(R2), 0xFFFFFFFF);
    comp->ram.WriteWord(0, 0xE6721F73);
    //comp->regs.WriteWord(R15, 0);
    comp->step();

    assert(comp->cpu.regs->ReadWord(comp->cpu.GET_REG_ADDR(R1)) == 0x7fff7fff);

    comp->restart();
    comp->regs.WriteWord(comp->cpu.GET_REG_ADDR(R2), 0xFFFFFFFF);
    comp->ram.WriteWord(0, 0xE6721FF3);
    //comp->regs.WriteWord(R15, 0);
    comp->step();

    assert(comp->cpu.regs->ReadWord(comp->cpu.GET_REG_ADDR(R1)) == 0x7f7f7f7f);
}

void testinstructions::testUHADDSUBX()
{
    comp->restart();
    comp->regs.WriteWord(comp->cpu.GET_REG_ADDR(R2), 1200);
    comp->ram.WriteWord(0, 0xE6721F33);
    //comp->regs.WriteWord(R15, 0);
    comp->step();

    assert(comp->cpu.regs->ReadWord(comp->cpu.GET_REG_ADDR(R1)) == 0x258);
}


void testinstructions::testUHADD()
{
    comp->restart();
    comp->regs.WriteWord(comp->cpu.GET_REG_ADDR(R2), 0xFFFFFFFF);
    comp->ram.WriteWord(0, 0xE6721F13);
    //comp->regs.WriteWord(R15, 0);
    comp->step();

    assert(comp->cpu.regs->ReadWord(comp->cpu.GET_REG_ADDR(R1)) == 0x7fff7fff);

    comp->restart();
    comp->regs.WriteWord(comp->cpu.GET_REG_ADDR(R2), 0xFFFFFFFF);
    comp->ram.WriteWord(0, 0xE6721F93);
    //comp->regs.WriteWord(R15, 0);
    comp->step();

    assert(comp->cpu.regs->ReadWord(comp->cpu.GET_REG_ADDR(R1)) == 0x7f7f7f7f);
}

void testinstructions::testUXTAB()
{
    comp->restart();
    comp->regs.WriteWord(comp->cpu.GET_REG_ADDR(R2), 0xFFFFFFFF);
    comp->ram.WriteWord(0, 0xE6E31072);
    //comp->regs.WriteWord(R15, 0);
    comp->step();

    assert(comp->cpu.regs->ReadWord(comp->cpu.GET_REG_ADDR(R1)) == 0xFF);

    comp->restart();
    comp->regs.WriteWord(comp->cpu.GET_REG_ADDR(R2), 0xFFFFFFFF);
    comp->ram.WriteWord(0, 0xE6C31072);
    //comp->regs.WriteWord(R15, 0);
    comp->step();

    assert(comp->cpu.regs->ReadWord(comp->cpu.GET_REG_ADDR(R1)) == 0xFF00FF);
}

void testinstructions::testUXTAH()
{
    comp->restart();
    comp->regs.WriteWord(comp->cpu.GET_REG_ADDR(R2), 0xFFFFFFFF);
    comp->ram.WriteWord(0, 0xE6F31072);
    //comp->regs.WriteWord(R15, 0);
    comp->step();

    assert(comp->cpu.regs->ReadWord(comp->cpu.GET_REG_ADDR(R1)) == 0x0000FFFF);
}


void testinstructions::testUXTB()
{
    comp->restart();
    comp->regs.WriteWord(comp->cpu.GET_REG_ADDR(R2), 0xFFFFFFFF);
    comp->ram.WriteWord(0, 0xE6CF1072);
    //comp->regs.WriteWord(R15, 0);
    comp->step();
    //qDebug() << comp->cpu.regs->ReadWord(comp->cpu.GET_REG_ADDR(R1));
    assert(comp->cpu.regs->ReadWord(comp->cpu.GET_REG_ADDR(R1)) == 0x00FF00FF);


    comp->restart();
    comp->regs.WriteWord(comp->cpu.GET_REG_ADDR(R2), 0xFFFFFFFF);
    comp->ram.WriteWord(0, 0xE6EF1072);
    //comp->regs.WriteWord(R15, 0);
    comp->step();
    //qDebug() << comp->cpu.regs->ReadWord(comp->cpu.GET_REG_ADDR(R1));
    assert(comp->cpu.regs->ReadWord(comp->cpu.GET_REG_ADDR(R1)) == 0x000000FF);

}

void testinstructions::testUXTH()
{
    comp->restart();
    comp->regs.WriteWord(comp->cpu.GET_REG_ADDR(R2), 0xFFFFFFFF);
    comp->ram.WriteWord(0, 0xE6FF1072);
    //comp->regs.WriteWord(R15, 0);
    comp->step();
    //qDebug() << comp->cpu.regs->ReadWord(comp->cpu.GET_REG_ADDR(R1));
    assert(comp->cpu.regs->ReadWord(comp->cpu.GET_REG_ADDR(R1)) == 0xFFFF);

}

void testinstructions::testMRS()
{
    comp->restart();
    //comp->regs.WriteWord(R0, 5);
    comp->ram.WriteWord(0, 0xe10f1000);
    //comp->regs.WriteWord(R15, 0);
    comp->step();
    assert(comp->cpu.regs->ReadWord(comp->cpu.GET_REG_ADDR(R1)) == comp->cpu.regs->ReadWord(comp->cpu.GET_REG_ADDR(CPSR))) ;
}

void testinstructions::testMSR()
{
    // --------------------------------------
    comp->restart();
    //comp->regs.WriteWord(R0, 5);
    comp->ram.WriteWord(0, 0xe129f002);
    //comp->regs.WriteWord(R15, 0);
    comp->step();
    assert(comp->cpu.regs->ReadWord(comp->cpu.GET_REG_ADDR(R2)) == comp->cpu.regs->ReadWord(comp->cpu.GET_REG_ADDR(CPSR))) ;

    //----------------
}
void testinstructions::testCMP()
{
    // --------------------------------------
    comp->restart();
    comp->regs.WriteWord(R0, 5);
    comp->ram.WriteWord(0, 0xE3500003);
    comp->regs.WriteWord(R15, 0);

    comp->step();
    assert(comp->cpu.flags->TestFlag(0, C_bit) == 1);

    //----------------

    comp->ram.WriteWord(0, 0xE35004FF);
    comp->regs.WriteWord(R15, 0);

    comp->step();
    assert(comp->cpu.flags->TestFlag(0, C_bit) == 0);
}

void testinstructions::testB()
{
    //positive B and Link
    comp->restart();
    comp->ram.WriteWord(0, 0xEB00000E);
    comp->regs.WriteWord(R15, 0);
    comp->step();

    assert(comp->regs.ReadWord(R15) == 64);
    assert(comp->regs.ReadWord(R14) == 4);
}

void testinstructions::testBX()
{
    comp->restart();
    comp->ram.WriteWord(0, 0xE12FFF11);
    comp->regs.WriteWord(R15, 0);
    comp->regs.WriteWord(R1, 64);
    comp->step();

    qDebug() << comp->regs.ReadWord(R15);

    assert(comp->regs.ReadWord(R15) == 64);
    assert(comp->regs.ReadWord(R14) == 4);
}

void testinstructions::testMOV()
{
    comp->restart();
    //MOV IMMEDIATE
    //e3a02030 mov r2, #48
    comp->ram.WriteWord(0, 3818922032);
    comp->regs.WriteWord(R15, 0);
    comp->step();
    assert(comp->regs.ReadWord(Instruction::cpu->GET_REG_ADDR(comp->cpu.currentInstruction->Rd)) == 48);

    //MOV IMMEDIATE
    //e3a014a1 mov r1, #-1593835520
    comp->ram.WriteWord(0, 3818919073);
    comp->regs.WriteWord(R15, 0);
    comp->step();
    assert(comp->regs.ReadWord(Instruction::cpu->GET_REG_ADDR(comp->cpu.currentInstruction->Rd)) == -0x5f000000);

    //MOV REG
    //e1a02000        mov     r2, r0
    comp->regs.WriteWord(R15, 0);
    comp->ram.WriteWord(0, 0xE3A00009);
    comp->step();
    assert(comp->regs.ReadWord(Instruction::cpu->GET_REG_ADDR(comp->cpu.currentInstruction->Rd)) == 9);
    comp->ram.WriteWord(4, 0xe1a02000);
    comp->step();
    assert(comp->regs.ReadWord(Instruction::cpu->GET_REG_ADDR(comp->cpu.currentInstruction->Rd)) == 9);

    //MOV REG PC
    //e1a0200f    mov     r2, pc
    comp->regs.WriteWord(R15, 0);
    comp->ram.WriteWord(0, 0xe1a0200f);
    comp->step();
    assert(comp->regs.ReadWord(Instruction::cpu->GET_REG_ADDR(comp->cpu.currentInstruction->Rd)) == 8);

    //MOV LSR
    //e1a02121        lsr     r2, r1, #2
    comp->regs.WriteWord(R15, 0);
    comp->ram.WriteWord(0, 0xE3A01005);
    comp->step();
    assert(comp->regs.ReadWord(Instruction::cpu->GET_REG_ADDR(comp->cpu.currentInstruction->Rd)) == 5);
    comp->ram.WriteWord(4, 0xe1a02121);
    comp->step();
    assert(comp->regs.ReadWord(Instruction::cpu->GET_REG_ADDR(comp->cpu.currentInstruction->Rd)) == 1);

    //e1a02081        lsl     r2, r1, #1
    comp->regs.WriteWord(R15, 0);
    comp->ram.WriteWord(0, 0xE3A01005);
    comp->step();
    assert(comp->regs.ReadWord(Instruction::cpu->GET_REG_ADDR(comp->cpu.currentInstruction->Rd)) == 5);
    comp->ram.WriteWord(4, 0xe1a02081);
    comp->step();
    assert(comp->regs.ReadWord(Instruction::cpu->GET_REG_ADDR(comp->cpu.currentInstruction->Rd)) == 10);

    //e1a02260 mov r2, r0, ror #4
    comp->regs.WriteWord(R15, 0);
    comp->ram.WriteWord(0, 0xE3A00010);
    comp->step();
    assert(comp->regs.ReadWord(Instruction::cpu->GET_REG_ADDR(comp->cpu.currentInstruction->Rd)) == 16);
    comp->ram.WriteWord(4, 0xE1A02260);
    comp->step();
    assert(comp->regs.ReadWord(Instruction::cpu->GET_REG_ADDR(comp->cpu.currentInstruction->Rd)) == 1);

    //e1a02141 mov r2, r1, asr #2
    comp->ram.WriteWord(0, 3818917896);
    comp->ram.WriteWord(4, 3785367873);
    comp->regs.WriteWord(R15, 0);
    comp->step();
    comp->step();
    assert(comp->regs.ReadWord(Instruction::cpu->GET_REG_ADDR(comp->cpu.currentInstruction->Rd)) == 2);

}

void testinstructions::testADD()
{
    comp->restart();

    //mov r2, #2
    comp->ram.WriteWord(0, 0xE3A02002);
    comp->regs.WriteWord(R15, 0);
    comp->step();
    assert(comp->regs.ReadWord(Instruction::cpu->GET_REG_ADDR(comp->cpu.currentInstruction->Rd)) == 2);

    //mov r0, #0
    comp->ram.WriteWord(4, 0xE3A00000);
    comp->step();
    assert(comp->regs.ReadWord(Instruction::cpu->GET_REG_ADDR(comp->cpu.currentInstruction->Rd)) == 0);

    //add r0, r2, r2, lsl #2
    comp->ram.WriteWord(8, 0xE0820102);
    comp->step();
    assert(comp->regs.ReadWord(Instruction::cpu->GET_REG_ADDR(comp->cpu.currentInstruction->Rd)) == 10);


}

void testinstructions::testMVN()
{
    comp->restart();

    //mvn r2, #1
    comp->ram.WriteWord(0, 0xE3E03001);
    comp->regs.WriteWord(R15, 0);
    comp->step();
    assert(comp->regs.ReadWord(Instruction::cpu->GET_REG_ADDR(comp->cpu.currentInstruction->Rd)) == -2);

}

void testinstructions::testSUB()
{
    comp->restart();
    //mov r4, #12
    comp->ram.WriteWord(0, 0xE3A0400C);
    comp->regs.WriteWord(R15, 0);
    comp->step();
    assert(comp->regs.ReadWord(Instruction::cpu->GET_REG_ADDR(comp->cpu.currentInstruction->Rd)) == 12);

    //sub r5, r4, #3
    comp->ram.WriteWord(4, 0xE2445003);
    comp->step();
    assert(comp->regs.ReadWord(Instruction::cpu->GET_REG_ADDR(comp->cpu.currentInstruction->Rd)) == 9);
}

void testinstructions::testRSB()
{
    comp->restart();
    //mov r4, #12
    comp->ram.WriteWord(0, 0xE3A0400C);
    comp->regs.WriteWord(R15, 0);
    comp->step();
    assert(comp->regs.ReadWord(Instruction::cpu->GET_REG_ADDR(comp->cpu.currentInstruction->Rd)) == 12);

    //rsb r5, r4, #3
    comp->ram.WriteWord(4, 0xE2645003);
    comp->step();
    assert(comp->regs.ReadWord(Instruction::cpu->GET_REG_ADDR(comp->cpu.currentInstruction->Rd)) == -9);
}

void testinstructions::testMUL()
{
    comp->restart();
    //mov r1, #5
    comp->ram.WriteWord(0, 0xE3A01005);
    comp->regs.WriteWord(R15, 0);
    comp->step();
    assert(comp->regs.ReadWord(Instruction::cpu->GET_REG_ADDR(comp->cpu.currentInstruction->Rd)) == 5);

    comp->ram.WriteWord(4, 0xE3A02019);
    comp->step();
    assert(comp->regs.ReadWord(Instruction::cpu->GET_REG_ADDR(comp->cpu.currentInstruction->Rd)) == 25);

    comp->ram.WriteWord(8, 0xE0050291);
    comp->step();
    assert(comp->regs.ReadWord(Instruction::cpu->GET_REG_ADDR(comp->cpu.currentInstruction->Rd)) == 125);
}

void testinstructions::testAND()
{
    comp->restart();
    //mov r1, #5
    comp->ram.WriteWord(0, 0xE3A01005);
    comp->regs.WriteWord(R15, 0);
    comp->step();
    assert(comp->regs.ReadWord(Instruction::cpu->GET_REG_ADDR(comp->cpu.currentInstruction->Rd)) == 5);

    //mov r2, #25
    comp->ram.WriteWord(4, 0xE3A02019);
    comp->step();
    assert(comp->regs.ReadWord(Instruction::cpu->GET_REG_ADDR(comp->cpu.currentInstruction->Rd)) == 25);

    //and r5, r1,r2
    comp->ram.WriteWord(8, 0xE0015002);
    comp->step();
    assert(comp->regs.ReadWord(Instruction::cpu->GET_REG_ADDR(comp->cpu.currentInstruction->Rd)) == 1);
}

void testinstructions::testORR()
{
    comp->ram.WriteWord(0, 0xE3A01005);
    comp->regs.WriteWord(R15, 0);
    comp->step();
    assert(comp->regs.ReadWord(Instruction::cpu->GET_REG_ADDR(comp->cpu.currentInstruction->Rd)) == 5);

    //mov r2, #25
    comp->ram.WriteWord(4, 0xE3A02019);
    comp->step();
    assert(comp->regs.ReadWord(Instruction::cpu->GET_REG_ADDR(comp->cpu.currentInstruction->Rd)) == 25);

    //orr r5, r1,r2
    comp->ram.WriteWord(8, 0xE1815002);
    comp->step();
    assert(comp->regs.ReadWord(Instruction::cpu->GET_REG_ADDR(comp->cpu.currentInstruction->Rd)) == 29);
}

void testinstructions::testEOR()
{
    comp->ram.WriteWord(0, 0xE3A01005);
    comp->regs.WriteWord(R15, 0);
    comp->step();
    assert(comp->regs.ReadWord(Instruction::cpu->GET_REG_ADDR(comp->cpu.currentInstruction->Rd)) == 5);

    //mov r2, #25
    comp->ram.WriteWord(4, 0xE3A02019);
    comp->step();
    assert(comp->regs.ReadWord(Instruction::cpu->GET_REG_ADDR(comp->cpu.currentInstruction->Rd)) == 25);

    //eor r5, r1,r2
    comp->ram.WriteWord(8, 0xE0215002);
    comp->step();
    assert(comp->regs.ReadWord(Instruction::cpu->GET_REG_ADDR(comp->cpu.currentInstruction->Rd)) == 28);
}

void testinstructions::testBIC()
{
        comp->ram.WriteWord(0, 0xE3A01005);
        comp->regs.WriteWord(R15, 0);
        comp->step();
        assert(comp->regs.ReadWord(Instruction::cpu->GET_REG_ADDR(comp->cpu.currentInstruction->Rd)) == 5);

        //mov r2, #25
        comp->ram.WriteWord(4, 0xE3A02019);
        comp->step();
        assert(comp->regs.ReadWord(Instruction::cpu->GET_REG_ADDR(comp->cpu.currentInstruction->Rd)) == 25);

        //bic r5, r1,r2
        comp->ram.WriteWord(8, 0xE1C15002);
        comp->step();
        qDebug() << comp->regs.ReadWord(Instruction::cpu->GET_REG_ADDR(comp->cpu.currentInstruction->Rd));
        assert(comp->regs.ReadWord(Instruction::cpu->GET_REG_ADDR(comp->cpu.currentInstruction->Rd)) == 4);
    }

void testinstructions::testSTR()
    {
        comp->restart();
        comp->regs.WriteWord(R15, 0);
        comp->regs.WriteWord(R11, 0x00006ffc);
        comp->regs.WriteWord(R3, 0x00000271);
        comp->ram.WriteWord(0, 0xE50B300C);

        comp->step();

        //qDebug() << comp->ram.ReadWord(0x00000271);
        assert(comp->ram.ReadWord(0x00006ffc - 12) == 0x00000271);




}

void testinstructions::testLDR()
{
    comp->restart();

    //mov r1, #22
    comp->ram.WriteWord(0, 0xE3A01016);
    comp->regs.WriteWord(R15, 0);
    comp->step();

    //mov r4, #12
    comp->ram.WriteWord(4, 0xE3A0400c);
    //comp->regs.WriteWord(R15, 0);
    comp->step();

    //mov r2,#2
    comp->ram.WriteWord(8, 0xE3A02002);
    comp->step();


    comp->ram.WriteWord(12,  0xE7841102);
    comp->step();

    //ldr r5, [r2]
//    comp->ram.WriteWord(16, 0xE5925000);
//    comp->step();

//    assert(comp->regs.ReadWord(Instruction::cpu->GET_REG_ADDR(comp->cpu.currentInstruction->Rd)) == 2);

//    //ldr r10, [r4, r2, lsl #2]
//    comp->ram.WriteWord(0, 0xE794A102);
//    comp->regs.WriteWord(R15, 0);
//    comp->step();

//    assert(comp->regs.ReadWord(Instruction::cpu->GET_REG_ADDR(comp->cpu.currentInstruction->Rd)) == 22);

    //mov r10, #64
    comp->ram.WriteWord(16, 0xE3A0A040);
    comp->ram.WriteWord(60, 17);
    comp->step();

    //ldr r6, [r10, #-4]
    comp->ram.WriteWord(20,  0xE51A6004);
    comp->step();

    assert(comp->regs.ReadWord(Instruction::cpu->GET_REG_ADDR(comp->cpu.currentInstruction->Rd)) == 17);




}

void testinstructions::testSTM()
{
    comp->restart();

    //22
    //2
    //12

    //12 - r5
    //2 - r6
    //22 - r7
    //mov r1, #22
    comp->ram.WriteWord(0, 0xE3A01016);
    comp->regs.WriteWord(R15, 0);
    comp->step();

    //mov r4, #12
    comp->ram.WriteWord(4, 0xE3A0400c);
    comp->step();

    //mov r2, #2
    comp->ram.WriteWord(8, 0xE3A02002);
    comp->step();

    //mov r13, #64
    comp->ram.WriteWord(12, 0xE3A0D040);
    comp->step();

    //stmfd sp, {r1, r2, r4}
    comp->ram.WriteWord(16, 0xE90D0016);
    comp->step();

    assert(comp->cpu.ram->ReadWord(60) == 12);

}

void testinstructions::testLDM()
{
    //mov r13, #52
    comp->ram.WriteWord(20, 0xE3A0D034);
    comp->regs.WriteWord(R15, 20);
    comp->step();

    //ldmfd sp, {r5, r6, r7}
    comp->ram.WriteWord(24, 0xE89D00E0);
    comp->step();
    assert(comp->cpu.regs->ReadWord(R7) == 12);
}
