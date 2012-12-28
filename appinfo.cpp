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

AppInfo::AppInfo()
{
}

QString AppInfo::basicInfoReport(void)
{
    QString report;
    QString trueStr("true");
    QString falseStr("false");

    report += "===================================================================\n";
    report += "\n";
    report += "Phoebetria:  " + phoebetriaVersion() + "\n";
    report += "Using Qt:    " + qtVersion() + "\n";
    report += "OS:          " + platformInfo() + "\n";
    report += "Recon:       " + connectedToDevice() + "\n";
    report += "\n";
    report += "===================================================================\n";
    report += "\n";
    report += "Phoebetria Primary Database\n";
    report += "Exists:     " + (mainDatabaseExists() ? trueStr : falseStr) + "\n";
    report += "Connected:  " + (mainDatabaseIsConnected() ? trueStr : falseStr) + "\n";
    report += "DB Version: " + mainDatabaseVersion() + "\n";
    report += "\n";
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

QStringList AppInfo::hidDevices(void)
{
    struct hid_device_info *devs, *curr_dev;

    QStringList result;
    QString deviceStr;

    for (devs = curr_dev = hid_enumerate(0, 0)
         ; curr_dev
         ; curr_dev = curr_dev->next)
    {
        deviceStr  = "Manufacturer: ";
        deviceStr += QString::fromWCharArray(curr_dev->manufacturer_string);
        deviceStr += "\nProduct: ";
        deviceStr += QString::fromWCharArray(curr_dev->product_string);

        deviceStr += "\nVendor Id: ";
        deviceStr += QString::number(curr_dev->vendor_id, 16);

        deviceStr += "\nProduct Id: ";
        deviceStr += QString::number(curr_dev->product_id, 16);

        deviceStr += "\nSerial Number: ";
        deviceStr += QString::fromWCharArray(curr_dev->serial_number);

        deviceStr += "\nRelease: ";
        deviceStr += QString::number(curr_dev->release_number);

        result.append(deviceStr);
    }
    hid_free_enumeration(devs);
    return result;
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
