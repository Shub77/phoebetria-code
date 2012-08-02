#if 0

#ifndef IOMANAGER_H
#define IOMANAGER_H

#include <QObject>
#include <QByteArray>
#include "device-io.h"



class IOManager : public QObject
{
    Q_OBJECT
public:
    explicit IOManager(QObject *parent = 0);
    
signals:
    
public slots:
    void onPollTimerTriggered(void);




private:

};

#endif // IOMANAGER_H

#endif
