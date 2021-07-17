/*
 * @filename loader.cpp
 * @brief the following file implements the functions for the Loader class.
 * Loads and reads an ELF file into memory
*/

#include <fstream>
#include <iostream>
#include <cmath>
#include <cstring>
#include "loader.h"
#include "ui_loader.h"
#include <QDir>
#include "instruction.h"
#include <QCoreApplication>
#include <QDebug>
#include <QFileDialog>
#include "worker.h"
#include <QThread>
#include <QDialog>
#include <QInputDialog>
#include <fstream>
#include "getinstructioninstance.h"
#include <sstream>
#include <QShortcut>
#include <QEvent>
#include <QKeyEvent>
#include <QListWidgetItem>
Loader::Loader(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Loader)
{
    ui->setupUi(this);

    ui->memoryTable->resizeRowsToContents();
    ui->memoryTable->resizeColumnsToContents();

    ui->flagsPanel->resizeColumnsToContents();
    ui->flagsPanel->resizeRowsToContents();

    ui->dissasemblyPanel->resizeRowsToContents();
    ui->actionTrace->toggle();

    ui->actionTrace->setChecked(true);
    Computer.traceFilePointer = &this->traceLogFileHnd;
    Computer.cpu.notifier = &(this->notifier);

    keyCtrlB = new QShortcut(this);
    keyCtrlB->setKey(Qt::CTRL + Qt::Key_B);

    connect(keyCtrlB, SIGNAL(activated()), this, SLOT(KeyB_activated()));
    connect(&notifier, SIGNAL(printToConsole(QChar)), this, SLOT(UpdateConsoleTab(QChar)));
    //connect(this, ui->consoleTab->keyPressEvent(), this, SLOT(UpdateConsoleTab(QChar)));

    ui->consoleTab->installEventFilter(this);
}

void Loader::KeyB_activated()
{
    Computer.breakpoints.push_back(Computer.regs.ReadWord(R15));
}

void Loader::UpdateUi()
{
    LoadDisassemblyPanel();
    LoadMemoryTab();
    LoadStackTab();
    LoadConsoleTab();
    LoadRegistersPanel();
    LoadFlagsPanel();

    QString mode = "";
    switch (Computer.cpu.mode)
    {
    case CPU_MODE::IRQ:
        mode = "IRQ";
        break;
    case CPU_MODE::SVC:
        mode = "SVC";
        break;
    case CPU_MODE::SYS:
        mode = "SYS";
        break;

    }

   // ui->cpuModeTexted->setText("CPU Mode: " + mode);
    ui->statusBar->showMessage("RAM Checksum: " + QString::number(Computer.ram.calculateChecksum()) + " | " + "Entry Point: 0x" + QString::number(this->ENTRY_POINT, 16).rightJustified(8, '0').toUpper() + " | " + "CPU Mode: " + mode);

}

void Loader::LoadDisassemblyPanel()
{
    QStringList filename = elfFileName.split('/');
    ui->groupBox_4->setTitle("Dissassebly - " + filename[filename.count()-1]);

    QStringList horzHeaders;

    activeRow = (Computer.regs.ReadWord(Computer.cpu.GET_REG_ADDR(R15)) - startPC) / 4;

    if(activeRow > 8 || activeRow < 0)
    {
        startPC = Computer.regs.ReadWord(Computer.cpu.GET_REG_ADDR(R15));
        int pc = startPC;
        QTableWidgetItem *item, *item2;
        for(int i = 0; i < ui->dissasemblyPanel->rowCount(); i++)
        {
             horzHeaders << "0x" + QString::number((uint32_t)pc, 16).rightJustified(8, '0').toUpper();
             Instruction *instr = GetInstructionInstance::GetInstruction(Computer.ram.ReadWord(pc));

             item = ui->dissasemblyPanel->item(i, 0);
                         if(!item)
                         {
                             item = new QTableWidgetItem();
                             ui->dissasemblyPanel->setItem(i, 1, item);
                         }
             item2 = ui->dissasemblyPanel->item(i, 1);
                         if(!item)
                         {
                             item = new QTableWidgetItem();
                             ui->dissasemblyPanel->setItem(i, 1, item);
                         }
             if(instr != NULL)
             {
                 instr->decode();
                 item->setText("0x" + QString::number((uint32_t)instr->assembledInstruction, 16).rightJustified(8, '0').toUpper());
                 item2->setText(instr->dissassembledInstruction);
             }
             else
             {
                 item->setText("0x" + QString::number((uint32_t)Computer.ram.ReadWord(pc), 16).rightJustified(8, '0').toUpper());
                 item2->setText("");
             }
             pc+=4;
       }

       activeRow = 0;
    }

    ui->dissasemblyPanel->selectRow(activeRow);
    ui->dissasemblyPanel->setVerticalHeaderLabels(horzHeaders);
    ui->dissasemblyPanel->resizeRowsToContents();
}

void Loader::LoadMemoryTab()
{
    uint32_t address;
    QTableWidgetItem *item;
    if(ui->memoryAdress->text().isEmpty())
    {
        address = 0;
    }
    else
    {
        std::stringstream ss;
        ss << std::hex << ui->memoryAdress->text().toStdString();
        ss >> address;

    }
        QStringList horzHeaders;

        //qDebug()<< QString::number(ui->memoryTable->rowCount());
        for(int i = 0; i < ui->memoryTable->rowCount(); i++)
        {
           horzHeaders << "0x" + QString::number(address, 16).rightJustified(8, '0').toUpper();

            for(int j = 0; j < ui->memoryTable->columnCount() / 2; j++)
            {
                uint8_t val = Computer.ram.ReadByte(address);

                QTableWidgetItem *item = ui->memoryTable->item(i, j);
                            if(!item) {
                                item = new QTableWidgetItem();
                                ui->memoryTable->setItem(i, j, item);
                            }
                item->setText(QString::number(val, 16).rightJustified(2, '0').toUpper());
                item->setTextAlignment(Qt::AlignCenter);

                QTableWidgetItem *item2 = ui->memoryTable->item(i, j + 17);
                            if(!item2) {
                                item2 = new QTableWidgetItem();
                                ui->memoryTable->setItem(i, j + 17, item2);
                            }

                item2->setText(val < 33? '.' : QChar(val));
                item2->setTextAlignment(Qt::AlignCenter);

                address++;
            }
        }
        ui->memoryTable->setVerticalHeaderLabels(horzHeaders);



        setStyleSheet("QHeaderView::section:horizontal {color:#3C3299; margin: 0; border: 0px} \
                       QHeaderView::section:vertical {color:#3C3299; margin-left: 5; border: 0px} \
                       QTableWidget QTableCornerButton::section {margin-right: 0; border: 0px solid} \
                        QTableWidget::item { margin: 0px; }");


}

void Loader::LoadStackTab()
{
    int addr = Computer.regs.ReadWord(Computer.cpu.GET_REG_ADDR(R13));
    QStringList horzHeaders;
    QTableWidgetItem *item;
    for(int i = 0; i < ui->stackTable->rowCount();  i++)
    {
        item = ui->stackTable->item(i, 0);
        if(!item) {
            item = new QTableWidgetItem();
            ui->flagsPanel->setItem(i, 0, item);
        }
        item->setText("");
        horzHeaders << "";
    }
    ui->stackTable->setVerticalHeaderLabels(horzHeaders);
    horzHeaders.clear();
    for(int i = 0; i < ui->stackTable->rowCount() && addr <= 0x7000 && addr >= 0 ;  i++)
    {
        horzHeaders << "0x" + QString::number((uint32_t)addr, 16).rightJustified(8, '0').toUpper();
        item = ui->stackTable->item(i, 0);
        item->setText("0x" + QString::number((uint32_t)Computer.ram.ReadWord(addr), 16).rightJustified(8, '0').toUpper());

        addr+=4;
     }

    ui->stackTable->setVerticalHeaderLabels(horzHeaders);

}

void Loader::LoadConsoleTab()
{

}

void Loader::LoadRegistersPanel()
{
    QTableWidgetItem *item;
    for(int i = 0; i < ui->registerList->count(); i++)
    {
//            QTableWidgetItem *item = ui->registersPanel->item(i, 0);
//                        if(!item) {
//                            item = new QTableWidgetItem();
//                            ui->registersPanel->setItem(i, 0, item);
//                        }
//            item->setText("0x" + QString::number((uint32_t)Computer.regs.ReadWord(Instruction::cpu->GET_REG_ADDR(i)), 16).rightJustified(8, '0').toUpper());

//            item = ui->registersPanel->item(i, 1);
//                        if(!item) {
//                            item = new QTableWidgetItem();
//                            ui->registersPanel->setItem(i, 1, item);
//                        }
//            item->setText(QString::number((uint32_t)Computer.regs.ReadWord(Instruction::cpu->GET_REG_ADDR(i)), 10));
//

                    QListWidgetItem *item = ui->registerList->item(i);
                    item->setText(regNames[i] + " =  0x" + QString::number((uint32_t)Computer.regs.ReadWord(Instruction::cpu->GET_REG_ADDR(i)), 16).rightJustified(8, '0').toUpper());


                    //item->setText(QString::number((uint32_t)Computer.regs.ReadWord(Instruction::cpu->GET_REG_ADDR(i)), 10));

    }

    //ui->registersPanel->resizeColumnsToContents();
    //ui->registersPanel->resizeRowsToContents();
}

void Loader::LoadFlagsPanel()
{
   // int MSB = Computer.flags.ReadByte(3);

    uint8_t f[5];

    f[0] = Computer.cpu.regs->TestFlag(Computer.cpu.GET_REG_ADDR(CPSR), N_bit);
    f[1] = Computer.cpu.regs->TestFlag(Computer.cpu.GET_REG_ADDR(CPSR), Z_bit);
    f[2] = Computer.cpu.regs->TestFlag(Computer.cpu.GET_REG_ADDR(CPSR), C_bit);
    f[3] = Computer.cpu.regs->TestFlag(Computer.cpu.GET_REG_ADDR(CPSR), V_bit);
    f[4] = Computer.cpu.regs->TestFlag(Computer.cpu.GET_REG_ADDR(CPSR), I_bit);

    for(int j = 0; j < ui->flagsPanel->columnCount(); j++)
    {
        QTableWidgetItem *item = ui->flagsPanel->item(0, j);
                    if(!item) {
                        item = new QTableWidgetItem();
                        ui->flagsPanel->setItem(0, j, item);
                    }
        item->setText(QString::number(f[j], 10));
        item->setTextAlignment(Qt::AlignCenter);
    }
    ui->flagsPanel->resizeRowsToContents();
}

bool Loader::isElf(Elf32_Ehdr *header)
{
    if (!(header->e_ident[0] == '\x7f' &&
          header->e_ident[1] == 'E' &&
          header->e_ident[2] == 'L' &&
          header->e_ident[3] == 'F')) {

        return 0;
    }
    return 1;
}

int Loader::ReadElf()
{
    std::ifstream strm;
    std::fstream outFile;

    strm.open(elfFileName.toStdString(), std::ios_base::in | std::ios_base::binary); // prog.exe should be in ELF format

    if (!strm)
    {
        qDebug() << ("Could not open " + QCoreApplication::applicationDirPath() + "/" + elfFileName);
        return 1;
    }
    else
    {
        qDebug() <<("Opening file " + elfFileName + "..");
    }

    qDebug() << "Loading ELF file into RAM..";

    // read ELF header
    strm.read((char*)&elfHeader, sizeof(elfHeader));

    if (!strm) {

        qDebug() << ("Error reading ELF header");
        return 1;
    }

    if(!isElf(&elfHeader))
    {
        qDebug() << "Input file is not an ELF file.";
        return 1;
    }

    //get entry point
    this->Computer.cpu.ENTRY_POINT_ADDR = elfHeader.e_entry;
    this->Computer.cpu.STACK_ADDR = 0x7000;

    //Get Adress of First Program Header
    int address = (int)elfHeader.e_phoff;

    qDebug() << ("Number Of Program Headers " + QString::number(elfHeader.e_phnum));
    qDebug() << ("First Program Header Offset: " + QString::number(address));

    Elf32_Phdr progHeader;
    unsigned char *segmentData;

    for(int i = 0; i < elfHeader.e_phnum; i++)
    {
        qDebug() <<("Current Adress " + QString::number(address));
        strm.clear();
        strm.seekg(address);

        // read first program header entry
        strm.read(((char*)&progHeader), elfHeader.e_phentsize);
        if(!strm)
        {
            qDebug() << "Could not read the program headers..";
            return 1;
        }

        qDebug() <<("Header #: " + QString::number(i));
        qDebug() <<("Header Offset: " + QString::number(progHeader.p_offset));
        qDebug() <<("Header Virtual Addr: " + QString::number(progHeader.p_vaddr));
        qDebug() <<("Header Memory size: " + QString::number(progHeader.p_memsz));
        qDebug() <<("Header File Size: " + QString::number(progHeader.p_filesz));
        qDebug() <<("Header Flag: " + QString::number(progHeader.p_type));

        if(progHeader.p_type == PT_LOAD)
        {
            strm.clear();
            strm.seekg(progHeader.p_offset);

            char *data = new char[progHeader.p_filesz];

            memset(data, 0, progHeader.p_filesz);
            strm.read(data, progHeader.p_filesz);

            if(!strm)
            {
                qDebug() << "Could not read the program headers..";
                return 1;
            }

            this->Computer.ram.LoadIntoMemory(data, progHeader.p_vaddr, progHeader.p_filesz);

            delete[] data;
        }

        address += elfHeader.e_phentsize;
        qDebug() <<("------------- ");

        }

    strm.close();
    return 0;

}

void Loader::UpdateLogTab(QString str)
{
    ui->logTab->append(str);
}

Loader::~Loader()
{
    delete ui;
}

void Loader::on_actionOpen_triggered()
{
    QString fn = QFileDialog::getOpenFileName(this,
        tr("Open File"), QDir::currentPath() , tr("Executable Files (*.exe);; All Files (*.*)"));

    if(!fn.isEmpty())
    {
        elfFileName = fn;
    }
    Computer.restart();

    if(ReadElf())
    {
        qDebug() << "Could not parse the ELF file.";
    }
    else
    {
        this->startPC = -1;
        this->Computer.initRegs();

    }
    UpdateUi();



}

void Loader::on_memoryAdress_returnPressed()
{
    LoadMemoryTab();
}

void Loader::on_actionRun_triggered()
{
    ui->actionRun->setEnabled(false);
    QThread *thread = new QThread;
    Worker *wrk = new Worker(&this->Computer);
    wrk->moveToThread(thread);

    connect(thread, SIGNAL (started()), wrk, SLOT (run()));
    connect(wrk, SIGNAL (finished()), thread, SLOT (quit()));
    connect(wrk, SIGNAL (finished()), this, SLOT (UpdateUi()));
    connect(thread, SIGNAL (finished()), thread, SLOT (deleteLater()));
    connect(thread, SIGNAL (finished()), this, SLOT (Run_finished()));
    thread->start();

}

void Loader::on_actionStep_triggered()
{
    QThread *thread = new QThread;
    Worker *wrk = new Worker(&this->Computer);
    wrk->moveToThread(thread);

    connect(thread, SIGNAL (started()), wrk, SLOT (step()));
    connect(wrk, SIGNAL (finished()), thread, SLOT (quit()));
    connect(wrk, SIGNAL (finished()), this, SLOT (UpdateUi()));
    connect(thread, SIGNAL (finished()), thread, SLOT (deleteLater()));
    thread->start();

}

void Loader::on_actionReset_triggered()
{

    Computer.restart();
    Computer.cpu.keyboardInput.clear();
    Computer.traceFilePointer->close();
    ui->consoleTab->clear();
    if(ReadElf())
    {
        qDebug() << "Could not parse the ELF file.";
    }

    Computer.initRegs();
    UpdateUi();
    this->startPC = 1;
}

void Loader::on_actionAddBreakpoint_triggered()
{
    uint32_t address;
    QString text = QInputDialog::getText(this,"Add Breakpoint","Breakpoint Address: ",QLineEdit::Normal,"", nullptr,Qt::Popup);

    try {
        bool ok;
        address = text.toInt(&ok, 16);
        Computer.breakpoints.push_back(address);
    } catch (std::exception &e) {
        qDebug() << "Sorry, could not add the breakpoint. Try again";
    }
}

void Loader::on_actionStop_triggered()
{
    Computer.cpu.HLT = true;
}

void Loader::Run_finished()
{
    ui->actionRun->setEnabled(true);
}

void Loader::on_actionTrace_toggled(bool arg1)
{
    if(arg1)
    {
        traceLogFileHnd.open(QCoreApplication::applicationDirPath().toStdString() +  "/" + traceLogFile.toStdString(),std::ios_base::trunc | std::ios_base::out);
        Computer.traceEnable = 1;
        if(!traceLogFileHnd)
        {
            qDebug() << "Could not open the trace file..";
        }
    }
    else
    {
        Computer.traceEnable = 0;
        traceLogFileHnd.flush();
        traceLogFileHnd.close();
    }
}

void Loader::UpdateConsoleTab(QChar c)
{
    ui->consoleTab->setText(ui->consoleTab->toPlainText() + c);

}

bool Loader::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::KeyPress) {
        QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
        int key = keyEvent->key();
        //qDebug("Ate key press %c , %d", key, keyEvent->key());

        if(key == Qt::Key_Return)
        {
             //qDebug() << key;
             Computer.cpu.keyboardInput.enqueue('\r');
             Computer.cpu.keyboardInput.enqueue('\0');
             //Computer.cpu.lastCharacter = '\r';

        }
        else
        {
            if(key >= 48 && key <= 128)
            {
                Computer.cpu.keyboardInput.enqueue(key);

                //Computer.cpu.lastCharacter = key;
            }

            if(key >= 0 && key <= 10)
            {
                key += '0';
                Computer.cpu.keyboardInput.enqueue(key);
                //Computer.cpu.lastCharacter = key;
            }

        }

//        while(!Computer.cpu.keyboardInput.empty())
//        {
//            qDebug() << (uint8_t)Computer.cpu.keyboardInput.dequeue();
//        }
        Computer.cpu.IRQ_flag = true;

        return true;
    } else {
        // standard event processing
        return QObject::eventFilter(obj, event);
    }
}
