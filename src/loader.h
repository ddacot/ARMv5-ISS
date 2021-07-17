/*
 * @filename loader.h
 * @brief defines the Loader class and the Main user interface.
*/


#ifndef LOADER_H
#define LOADER_H

#include <QMainWindow>
#include "elf.h"
#include "memory.h"
#include "computer.h"
#include <fstream>
#include <QShortcut>
#include "notify.h"
#include "keypress.h"
namespace Ui {
class Loader;
}

class Loader : public QMainWindow
{
    Q_OBJECT

public:
    computer Computer;
    Notify notifier;
    KeyPress keyPressMonitor;

    const QIcon arrow = QIcon(":/Images/Images/arrow.png");
    const QIcon empty = QIcon("");
    //instance of an elf header
    Elf32_Ehdr elfHeader;
    QString elfFileName;

    //holds the value of the entry point.
    uint32_t ENTRY_POINT = 0;
    //pointer to a list of program headers
    std::vector<Elf32_Phdr*> progHeaders;
    const QString regNames[17] = {"R0", "R1", "R2","R3","R4","R5","R6","R7","R8","R9","R10","R11","R12","R13","R14","R15", "CPSR"};

    QShortcut *keyCtrlB;

    QString traceLogFile = "trace.log";
    std::fstream traceLogFileHnd;

    //flag variables
    int activeRow = 8;
    bool enable_textChanged = true;
    int startPC = 1;
    int ReadElf();

    bool isElf(Elf32_Ehdr *elfHeader);
    void LoadDisassemblyPanel();
    void LoadMemoryTab();
    void LoadStackTab();
    void LoadConsoleTab();
    void LoadRegistersPanel();
    void LoadFlagsPanel();
    //void UpdateConsoleTab();
    void UpdateLogTab(QString str);

    bool eventFilter(QObject *obj, QEvent *event);

    //void UpdateUi();

    explicit Loader(QWidget *parent = nullptr);
    ~Loader();

public:
    Ui::Loader *ui;

public slots:
    void UpdateUi();
    void KeyB_activated();
    void UpdateConsoleTab(QChar c);

private slots:

    void Run_finished();
    void on_actionOpen_triggered();
    void on_memoryAdress_returnPressed();
    void on_actionRun_triggered();
    void on_actionStep_triggered();
    void on_actionReset_triggered();
    void on_actionAddBreakpoint_triggered();
    void on_actionStop_triggered();
    void on_actionTrace_toggled(bool arg1);
    //void on_consoleTab_textChanged();
};

#endif // LOADER_H
