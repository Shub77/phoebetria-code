
#include "softwareauto.h"

#include <QDebug>
#include "bfx-recon/fancontrollerio.h"
#include "fancontrollerdata.h"

SoftwareAuto::SoftwareAuto(QObject *parent) :
    QObject(parent),
    m_preStateStored(false)
{
}

void SoftwareAuto::storeCurrentState(FanControllerData& fcData)
{
    m_preSwAutoState.setFromCurrentData(fcData);
    m_preStateStored = true;
}


bool SoftwareAuto::switchOn(FanControllerIO& fcIO, FanControllerData& fcData)
{
    if (!m_preStateStored)
    {
        /* Save the current state of the Recon so we can restore it when s/ware
           auto is switched off or the application ends
          */
        storeCurrentState(fcData);
    }

    if (fcData.isAuto())
    {
        /* Switch to manual mode... s/w will set appropriate fan speeds
         */
        fcIO.setDeviceFlags(fcData.isCelcius(),
                            false,   // manual
                            fcData.isAudibleAlarm()
                            );
    }

    fcData.setIsSwAuto(true);

    return true;
}

bool SoftwareAuto::switchOff(FanControllerIO& fcIO, FanControllerData& fcData)
{

    if (!fcData.isSoftwareAuto())
    {
        qDebug() << "Error: Attempt swith OFFs/w but not in s/w auto mode";
        return false;
    }

    if (!m_preStateStored)
    {
        qDebug() << "Error: State of the the Recon prior to s/ware auto not stored";
        return false;

    }
    // Restore previous fan controller state

    bool r;
    r = fcIO.setFromProfile(m_preSwAutoState);

    if (!r)
        qDebug() << "Swithing OFF s/ware auto failed";
    else
        m_preStateStored = false;

    fcData.setIsSwAuto(!r);

    return r;
}
