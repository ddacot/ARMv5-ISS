/*
 * @filename log.cpp
 * @brief the following file implements the logging API. Redirects error messages to specific output streams.
*/


#include "log.h"
#include <qapplication.h>
#include <stdio.h>
#include <stdlib.h>
#include <loader.h>
#include <fstream>
#include <iostream>
log::log()
{

}

Loader* log::lg = NULL;
static QApplication *app = NULL;
QString log::filename = "log.txt";
bool log::toFile = false;
/*
 * @brief MessageOutput function redirects error messages to specific streams.
 * @params message type, context, and the error message
 * @return does not return.
*/
void log::MessageOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    QByteArray localMsg = msg.toLocal8Bit();
    if(localMsg[0] == '"')
        localMsg = localMsg.remove(0,1);
    if(localMsg[localMsg.length()-1] == '"')
        localMsg = localMsg.remove(localMsg.length()-1,1);

    if(!toFile)
    {
        switch (type) {
        case QtDebugMsg:
            fprintf(stderr, "Debug: %s\n", localMsg.constData(), context.file, context.line, context.function);
            lg->UpdateLogTab("Debug: " + localMsg);
            break;
        case QtInfoMsg:
            fprintf(stdout, "Info: %s\n", localMsg.constData(), context.file, context.line, context.function);
            lg->UpdateLogTab("Info: " + localMsg);
            break;
        case QtWarningMsg:
            fprintf(stderr, "Warning: %s\n", localMsg.constData(), context.file, context.line, context.function);
            log::lg->UpdateLogTab("Warning: " + localMsg);
            break;
        case QtCriticalMsg:
            fprintf(stderr, "Critical: %s\n", localMsg.constData(), context.file, context.line, context.function);
            log::lg->UpdateLogTab("Critical: " + localMsg);
            break;
        case QtFatalMsg:
            fprintf(stderr, "Fatal: %s\n", localMsg.constData(), context.file, context.line, context.function);
            log::lg->UpdateLogTab("Fatal: " + localMsg);

            break;
        }
    }
    else
    {
        std::fstream outFile;
        outFile.open(QCoreApplication::applicationDirPath().toStdString() +  "/" + log::filename.toStdString(),std::ios_base::app| std::ios_base::out);
        switch (type) {
        case QtDebugMsg:
            outFile << "Debug: " + msg.toStdString() +"\n";
            lg->UpdateLogTab("Debug: " + localMsg);
            //lg->UpdateUiLog("Debug: " + localMsg);
            break;
        case QtInfoMsg:
            outFile << "Info: %s\n";
            //fprintf(stdout, "Info: %s\n", localMsg.constData(), context.file, context.line, context.function);
           // lg->UpdateUiLog("Info: " + localMsg);
            break;
        case QtWarningMsg:
            fprintf(stderr, "Warning: %s\n", localMsg.constData(), context.file, context.line, context.function);
            //log::lg->UpdateUiLog("Warning: " + localMsg);
            break;
        case QtCriticalMsg:
            fprintf(stderr, "Critical: %s\n", localMsg.constData(), context.file, context.line, context.function);
            //log::lg->UpdateUiLog("Critical: " + localMsg);
            break;
        case QtFatalMsg:
            fprintf(stderr, "Fatal: %s\n", localMsg.constData(), context.file, context.line, context.function);
            //log::lg->UpdateUiLog("Fatal: " + localMsg);

            break;
        }
        outFile.close();
    }
}
