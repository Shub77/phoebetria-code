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

#ifndef PROFILES_H
#define PROFILES_H

#include <QString>
#include <QSettings>
#include "fancontrollerdata.h"
#include "fanchanneldata.h"

typedef struct {
    int alarmTemp;
    int speed;
} BasicChannelData;

class FanControllerProfile
{
public:

    FanControllerProfile();
    ~FanControllerProfile();

    QString defualtProfileLocation(void) const;

    void setProfileName(const QString& name);
    void setFilenameAndPath(const QString& filenameAndPath);

    void setFromCurrentData(const FanControllerData& data);

    bool save(const QString& filenameAndPath);
    bool load(const QString& filenameAndPath);
    void reset(void);


protected:

    void initCommon(void);

private:

    QString m_defaultProfileLocation;

    QString m_name;
    QString m_fileNameAndPath;

    bool m_isCelcius;
    bool m_isAuto;
    bool m_isAudibleAlarm;

    BasicChannelData m_channelSettings[FC_MAX_CHANNELS];
};

#endif // PROFILES_H
