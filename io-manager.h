#ifndef IOMANAGER_H
#define IOMANAGER_H

#include <QObject>
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
    static DeviceIO m_io_device;
};

#endif // IOMANAGER_H
