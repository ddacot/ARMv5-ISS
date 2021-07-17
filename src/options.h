#ifndef OPTIONS_H
#define OPTIONS_H
/*
 * @filename loader.h
 * @brief defines the options class. Defines class members and command line argument options.
*/
#include "include/CLI11.hpp"
#include <QApplication>
#include <loader.h>
#include <QCommandLineParser>
class Options
{
public:
    //creates an instance of the parser class
    QCommandLineParser parser;
    QCommandLineOption *redirectToFile;

    QCommandLineOption *traceall;
    //pointer to the --mem option
    QCommandLineOption *memorySizeOption;

    //pointer to the --file option
    QCommandLineOption *elfFileOption;

    //pointer to the --test option
    QCommandLineOption *unitTest;

    //pointer to the --test option
    QCommandLineOption *exec;

    //pointer ot the --log option
    QCommandLineOption *logging;

    //variables holding the values of the arguments
    bool test, debug, help, debugToFile, execOption, loadPresent,traceallB;

    //holds the memory size
    uint32_t MEM_SIZE = 32768;

    //holds the ELF file name
    QString elfFileName = "";

    bool extractValues();
    QString getValue(QCommandLineOption *option);
    int parse(QCoreApplication *a);
    Options();
};

#endif // OPTIONS_H
