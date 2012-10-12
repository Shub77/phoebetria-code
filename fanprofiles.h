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

#ifndef PHOEBETRIA_FAN_PROFILES_H
#define PHOEBETRIA_FAN_PROFILES_H

#include <QString>
#include <QSettings>
#include <QtSql>
#include "bfx-recon/bfxrecon.h"
#include "fanchanneldata.h"

class FanControllerData;
class QDir;

typedef struct
{
    int alarmTemp;
    int speed;
} BasicChannelData;


class FanControllerProfile
{
public:

    friend class MainDb;

    FanControllerProfile();

    QString defualtProfileLocation(void) const;
    static QStringList getProfileNames(void);

    void setProfileName(const QString& name);
    void setFilenameAndPath(const QString& filenameAndPath);

    void setFromCurrentData(const FanControllerData& data);

    bool save(const QString& profileName);
    bool load(const QString& profileName);

    static int importFromIni(QDir &dir);

    static bool erase(const QString& profileName);

    bool isCelcius(void) const;
    bool isAuto(void) const;
    bool isAudibleAlarm(void) const;
    bool isSoftwareAuto(void) const;

    const BasicChannelData& getChannelSettings(int channel) const;

    inline static bool isReservedProfileName(const QString& name);

    inline static const QString& reservedProfileNameStartChars(void);

protected:

    void initCommon(void);

    static bool loadFromIni(const QString& filenameAndPath, FanControllerProfile &dest);

private:

    QString m_defaultProfileLocation;

    QString m_name;
    QString m_fileNameAndPath;

    bool m_isCelcius;
    bool m_isAuto;
    bool m_isAudibleAlarm;
    bool m_isSoftwareAuto;

    BasicChannelData m_channelSettings[FC_MAX_CHANNELS];
};


inline bool FanControllerProfile::isCelcius(void) const
{
    return m_isCelcius;
}

inline bool FanControllerProfile::isAuto(void) const
{
    return m_isAuto;
}

inline bool FanControllerProfile::isAudibleAlarm(void) const
{
    return m_isAudibleAlarm;
}

inline bool FanControllerProfile::isSoftwareAuto(void) const
{
    return m_isSoftwareAuto;
}

inline const BasicChannelData&
    FanControllerProfile::getChannelSettings(int channel) const
{
    return m_channelSettings[channel];
}

inline bool FanControllerProfile::isReservedProfileName(const QString& name)
{
    return name.left(reservedProfileNameStartChars().length())
                == reservedProfileNameStartChars();
}

inline const QString& FanControllerProfile::reservedProfileNameStartChars(void)
{
    static QString chrs = "__";
    return chrs;
}


#endif // PHOEBETRIA_FAN_PROFILES_H
