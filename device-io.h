#ifndef DEVICEIO_H
#define DEVICEIO_H

#include <QObject>
#include "hidapi.h"

class DeviceIO : public QObject
{
    Q_OBJECT
public:
    explicit DeviceIO(QObject *parent = 0);
    
    bool connect(unsigned short vendorId, unsigned short productId);

    void disconnect(void);

    bool isConnected(void) const;

    int sendData(const unsigned char *data, int len);

    QString lastErrorString(void) const;

    void setBlocking(bool block);

signals:
    void dataRX(QByteArray data);

public slots:
    void pollForData(void);

private:
    hid_device *m_device;
};

#endif // DEVICEIO_H
