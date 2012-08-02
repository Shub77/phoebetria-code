#ifndef IOMANAGER_H
#define IOMANAGER_H

#include <QObject>
#include <QByteArray>
#include "device-io.h"

#define PHOEBETRIA_IO_BITFENIX_RECON "bitfenix-recon"
#define PHOEBETRIA_IO_BITFENIX_RECON_VENDORID 3141
#define PHOEBETRIA_IO_BITFENIX_RECON_PRODUCTID 28928

class IOManager : public QObject
{
    Q_OBJECT
public:
    explicit IOManager(QObject *parent = 0);
    
signals:
    
public slots:
    void onPollTimerTriggered(void);
    void onRawData(QByteArray rawdata);

protected:
    void connectSignals(void);

private:
    DeviceIO m_io_device;
};

#endif // IOMANAGER_H
