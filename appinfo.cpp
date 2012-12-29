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

#include "appinfo.h"

#include <QSysInfo>
#include <QDebug>
#include <QFile>
#include <QByteArray>

#include "builddetails.h"
#include "phoebetriaapp.h"
#include "hidapi.h"
#include "maindb.h"
#include "phoebetriaapp.h"

AppInfo::AppInfo()
{
}

QString AppInfo::basicInfoReport(void)
{
    QString report;
    QString trueStr("true");
    QString falseStr("FALSE");

    report += "===================================================================\n";
    report += "Phoebetria:      " + phoebetriaVersion() + "\n";
    report += "Using Qt:        " + qtVersion() + "\n";
    report += "OS:              " + platformInfo() + "\n";
    report += "Recon:           " + connectedToDevice() + "\n";
    report += "\n";
    report += "===================================================================\n";
    report += "Database\n";
    report += "\n";
    report += "Main DB Exists: " + (mainDatabaseExists() ? trueStr : falseStr) + "\n";
    report += "Driver ok:      " + (databaseDriverLoaded() ? trueStr : falseStr) + "\n";
    report += "Connected:      " + (mainDatabaseIsConnected() ? trueStr : falseStr) + "\n";
    report += "DB Version:     " + mainDatabaseVersion() + "\n";
    report += "\n";
    report += "===================================================================\n";
    report += "\n";
    report += "Misc.\n";
    report += "\n";
    report += "Max. elapsed time between device polling: "
            + QString::number(maxFanControllerPollTime()) + " ms\n\n";
    report += "Item                   Ch0      Ch1      Ch2      Ch3      Ch4\n";
    report += "Last probe temps: " + channelTemps(false) + "\n";
    report += "Avg. probe temps: " + channelTemps(true) + "\n";
    report += "...\n";
    report += "===================================================================\n";
    report += "\n";

    report += "HID Devices:\n";

    QStringList dl = AppInfo::hidDevices();
    for (int i = 0; i < dl.count(); i++)
    {
        report += "\n" + dl.at(i) + "\n";
    }
    report += "===================================================================\n";

    return report;
}

QString AppInfo::qtVersion(void)
{
    return BuildDetails::qtVersion();
}

QString AppInfo::phoebetriaVersion(void)
{
    return BuildDetails::versionStr().trimmed()
            + " " + BuildDetails::buildDateTimeStr();
}

QString AppInfo::platformInfo(void)
{
    return osVersionAsString();
}

QString AppInfo::connectedToDevice(void)
{
    bool isConn = ph_fanControllerIO().isConnected();

    return isConn ? "Device Connected" : "Device NOT Connected";
}

unsigned long AppInfo::maxFanControllerPollTime(void)
{
    return ph_fanControllerIO().maxPollDelta();
}

QString AppInfo::channelTemp(int channel, bool getAverage)
{
    const FanChannelData& cd = ph_fanControllerData().fanChannelSettings(channel);
    int T;

    if (getAverage)
        T = cd.tempAveraged();
    else
        T = cd.lastTemp();

    if (ph_fanControllerData().isCelcius())
        T = ph_fanControllerData().toCelcius(T);

    QString s = QString("%1").arg(T, 8);
    return s;
}

QString AppInfo::channelTemps(bool getAverage)
{
    QString s;

    for (int i = 0; i < FC_MAX_CHANNELS; ++i)
    {
        if (i != 0)
            s += " ";
        s += channelTemp(i, getAverage);
    }
    if (ph_fanControllerData().isCelcius())
        s += " C";
    else
        s += " F";

    return s;
}

QStringList AppInfo::hidDevices(void)
{
    struct hid_device_info *devs, *curr_dev;

    QStringList result;
    QString deviceStr;

    for (devs = curr_dev = hid_enumerate(0, 0)
         ; curr_dev
         ; curr_dev = curr_dev->next)
    {
        deviceStr  = "Manufacturer:  ";
        deviceStr += QString::fromWCharArray(curr_dev->manufacturer_string);
        deviceStr += "\nProduct:       ";
        deviceStr += QString::fromWCharArray(curr_dev->product_string);

        deviceStr += "\nVendor Id:     ";
        deviceStr += QString("%1").arg(curr_dev->vendor_id, 4, 16, QChar('0'));

        deviceStr += "\nProduct Id:    ";
        deviceStr += QString("%1").arg(curr_dev->product_id, 4, 16, QChar('0'));

        deviceStr += "\nSerial Number: ";
        deviceStr += QString::fromWCharArray(curr_dev->serial_number);

        deviceStr += "\nRelease:       ";
        deviceStr += QString::number(curr_dev->release_number);

        result.append(deviceStr);
    }
    hid_free_enumeration(devs);
    return result;
}

bool AppInfo::databaseDriverLoaded(void)
{
    return DatabaseManager::driverIsAvailable();
}

bool AppInfo::mainDatabaseExists(void)
{
    return MainDb::verifyDbAndPathExist();
}

bool AppInfo::mainDatabaseIsConnected(void)
{
    return MainDb::isValid();
}

QString AppInfo::mainDatabaseVersion(void)
{
    MainDb mdb;

    return mdb.schemaVersion();
}

QString AppInfo::mainDatabasePath(void)
{
    return DatabaseManager::dbFilenameWithPath(DatabaseManager::PrimaryDb);
}


/*********************************************************************
 Private member functions
 *********************************************************************/

QString AppInfo::osVersionAsString(void)
{
     QString os;

#if defined Q_OS_WIN || defined Q_OS_WIN32

    enum QSysInfo::WinVersion v;
    v = QSysInfo::windowsVersion();
    switch (v)
    {
    case QSysInfo::WV_NT:
        os = "Windows NT";
        break;
    case QSysInfo::WV_2000:
        os = "Windows 2000";
        break;
    case QSysInfo::WV_XP:
        os = "Windows XP";
        break;
    case QSysInfo::WV_2003:
        os = "Windows 2003";
        break;
    case QSysInfo::WV_VISTA:
        os = "Windows Vista";
        break;
    case QSysInfo::WV_WINDOWS7:
        os = "Windows 7";
        break;
    case QSysInfo::WV_WINDOWS8:
        os = "Windows 8";
        break;
    default:
        os = "Windows (Unknown Version)";
        break;
    }

#elif defined Q_OS_MAC
    os = "Machintosh";
#elif defined Q_OS_LINUX
    QFile f;

    f.setFileName("/proc/version");
    if (f.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QByteArray ba = f.readAll();
        os = ba.simplified();
        f.close();
    }

    if (os.isEmpty())
    {
        os = "Linux";
    }

#else
    os = "Unknown";
#endif

    return os;
}
