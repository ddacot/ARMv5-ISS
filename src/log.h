/*
 * @filename loader.h
 * @brief defines the log class. Defines class members.
*/

#ifndef LOG_H
#define LOG_H
#include <qapplication.h>
#include <stdio.h>
#include <stdlib.h>
#include "loader.h"
class log
{
public:
    static void MessageOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg);
    //static Loader* getWindowHandle();

    static QString filename;
    //pointer to the Loader instance
    static Loader *lg;
    static bool toFile;
    //pointer to the QApp
    static QApplication *app;
    log();
};

#endif // LOG_H
