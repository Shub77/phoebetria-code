#include "io-manager.h"

IOManager::IOManager(QObject *parent) :
    QObject(parent)
{
    m_io_device.connect(PHOEBETRIA_IO_BITFENIX_RECON_VENDORID,
                        PHOEBETRIA_IO_BITFENIX_RECON_PRODUCTID);
    qDebug(m_io_device.isConnected() ? "Connected" : "NOT connected");
    connectSignals();
}

void IOManager::connectSignals(void)
{
    QObject::connect(&m_io_device, SIGNAL(dataRX(QByteArray)),
                     this, SLOT(onRawData(QByteArray)));
}

void IOManager::onPollTimerTriggered(void)
{
    qDebug("Poll");
    m_io_device.pollForData();
}

void IOManager::onRawData(QByteArray rawdata)
{
    qDebug("Got raw data");
    qDebug(rawdata.toHex());
}
