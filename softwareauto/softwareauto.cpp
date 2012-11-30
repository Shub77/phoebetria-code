/*  Copyright 2012 Craig Robbins and Christopher Ferris

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with the program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "softwareauto.h"

#include <QDebug>
#include "bfx-recon/fancontrollerio.h"
#include "fancontrollerdata.h"
#include "phoebetriaapp.h"

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
    /* Save the current state of the Recon so we can restore it when s/ware
       auto is switched off or the application ends
      */
    storeCurrentState(fcData);

    fcData.setIsSwAuto(true);

    if (fcData.isAuto())
    {
        /* Switch to manual mode... s/w will set appropriate fan speeds
         */
        fcIO.setDeviceFlags(fcData.isCelcius(),
                            false,   // manual
                            fcData.isAudibleAlarm()
                            );
    }

    return true;
}

bool SoftwareAuto::switchOff(FanControllerIO& fcIO, FanControllerData& fcData)
{

    if (!fcData.isSoftwareAuto())
    {
        qDebug() << "Error: Attempt swith OFFs/w but not in s/w auto mode";
        return false;
    }

    // Set to auto. This is in leiu of the code below that is #ifdefd away
    FanControllerData& fcd = ph_fanControllerData();

    fcIO.clearRequestQueue();

    fcIO.setDeviceFlags(fcd.isCelcius(),
                        true,
                        fcd.isAudibleAlarm()
                        );
    fcData.updateIsAuto(true, false);
    fcData.setIsSwAuto(false);
    return true;

#if 0

    FIXME

    This does not work as intended if a profile was loaded that is s/ware
    auto. When loading the pre-state is not stored correctly. A better way
    to load a profile is for the manage profiles dialog to let the main
    dialog know that a profile should be loaded and the profile loaded
    from the main window rather than from the manage profiles dialog. This
    way pre-states could be properly stored.

    if (!m_preStateStored)
    {
        qDebug() << "Error: State of the the Recon prior to s/ware auto not stored."
                 << "Setting to Auto";

        FanControllerData& fcd = ph_fanControllerData();

        fcIO.setDeviceFlags(fcd.isCelcius(),
                            true,
                            fcd.isAudibleAlarm()
                            );
        fcData.updateIsAuto(true, false);
        fcData.setIsSwAuto(false);
        return true;

    }
    // Restore previous fan controller state

    bool r;
    r = fcIO.setFromProfile(m_preSwAutoState);

    if (!r)
    {
        qDebug() << "Swithing OFF s/ware auto failed";
        return false;
    }
    else
        m_preStateStored = false;

    fcData.setIsSwAuto(false);

    return r;
#endif
}
