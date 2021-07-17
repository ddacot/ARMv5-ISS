#ifndef KEYPRESS_H
#define KEYPRESS_H
#include <QObject>
class KeyPress : public QObject
{
     Q_OBJECT
public:
    KeyPress();

    bool eventFilter(QObject *obj, QEvent *event);
};

#endif // KEYPRESS_H
