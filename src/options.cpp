/*
 * @filename options.cpp
 * @brief the following class implements the command line argument parser.
*/

#include "options.h"
#include "include/CLI11.hpp"
#include <QApplication>
#include <loader.h>
#include <QCoreApplication>
#include <QDebug>
#include "log.h"


Options::Options()
{
    parser.setApplicationDescription("ELF Loader");
    parser.addHelpOption();
    parser.addVersionOption();

    memorySizeOption = new QCommandLineOption("mem",
                QCoreApplication::translate("Loader", "Sets memory size."),
                QCoreApplication::translate("Loader", "memory"));

    memorySizeOption->setDefaultValue("32768");

    elfFileOption = new QCommandLineOption ("load",
                QCoreApplication::translate("Loader", "Open ELF file <filename>"),
                QCoreApplication::translate("Loader", "filename"));

    unitTest = new QCommandLineOption(QStringList()<<"t" << "test");
    unitTest->setDefaultValue("0");

    exec = new QCommandLineOption(QStringList()<<"exec" << "exec");
    exec->setDefaultValue("0");

    redirectToFile = new QCommandLineOption(QStringList()<<"r" << "redirect");
    redirectToFile->setDefaultValue("0");

    logging = new QCommandLineOption(QStringList()<<"l" << "log");
    logging->setDefaultValue("0");

    traceall = new QCommandLineOption(QStringList()<< "traceall");
    traceall->setDefaultValue("0");

    parser.addOption(*traceall);
    parser.addOption(*memorySizeOption);
    parser.addOption(*exec);
    parser.addOption(*elfFileOption);
    parser.addOption(*unitTest);
    parser.addOption(*logging);
    parser.addOption(*redirectToFile);

}
/*
 * @brief parse function parses the arguments list.
 * @params accepts a pointer to the QApp.
 * @return returns 0 if successful.
*/
int Options::parse(QCoreApplication *a)
{
    parser.process(*a);
    return 0;
}

/*
 * @brief returns the value of argument stored in <option>
 * @params accepts a pointer to the Option object
 * @return returns the value passed as a parameter.
*/
QString Options::getValue(QCommandLineOption *option)
{
    return parser.value(*option);
}

/*
 * @brief extractValues function extracts the values form argument list.
 * @params accepts a pointer to the QApp.
 * @return returns 0 if successful.
*/
bool Options::extractValues()
{
    //extract CL Arguments
    try {
        traceallB = parser.isSet(*traceall);
        execOption = parser.isSet(*exec);
        MEM_SIZE = getValue(memorySizeOption).toUInt();
        elfFileName = QCoreApplication::applicationDirPath() +  "/" + getValue(elfFileOption);
        loadPresent = parser.isSet(*elfFileOption);
        test = parser.isSet(*unitTest);
        debugToFile = parser.isSet(*redirectToFile);

    } catch (std::exception &e) {
        qDebug() << "Parsing arguments failed";
        return 1;
    }
    return 0;
}

