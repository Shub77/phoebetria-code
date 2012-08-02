#ifndef DEVICEIO_H
#define DEVICEIO_H

#include <QObject>
#include "hidapi.h"

class DeviceIO : public QObject
{
    Q_OBJECT
public:
    explicit DeviceIO(QObject *parent = 0);
    
    bool connect(int vendorId, int productId);

    bool disconnect(void);

    bool isConnected(void) const;

    void sendData(const QByteArray& data);

    QString lastErrorString(void) const;

signals:
    void dataRX(QByteArray data);

public slots:
    
private:
    hid_device *device;
};

#endif // DEVICEIO_H
