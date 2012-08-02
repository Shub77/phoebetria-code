#include "io-manager.h"

IOManager::IOManager(QObject *parent) :
    QObject(parent)
{
}

void IOManager::onPollTimerTriggered(void)
{
    qDebug("Poll");
}
