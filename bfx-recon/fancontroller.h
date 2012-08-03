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

#ifndef PHOEBETRIA_FANCONTROLLER_H
#define PHOEBETRIA_FANCONTROLLER_H

#include <QObject>
#include <QMap>
#include "device-io.h"

typedef enum fcReponseCodeCategory {
    fcResp_TempAndSpeed,
    fcResp_DeviceFlags,
    fcResp_AlarmAndSpeed,
    fcResp_DeviceStatus,
    fcResp_Handshake
} fcResponseCodeCategory;


typedef struct fcResponseCodeDef
{
    fcResponseCodeCategory category;
    char code;
    int expectedPacketLen;
    const QString desc;
} fcResponseCodeDef;

typedef struct fcRequestCodeDef
{
    char code;
    int expectedPacketLen;
} fcRequestCodeDef;


/** @internal The main reason for this class (rather than doing everything in
  * the DeviceIO class is to somewhat separate the specific parsing for the
  * bitfenix recon controller; i.e. in the future possibly other fan controllers can
  * be supported.
  */
class FanController : public QObject
{
    Q_OBJECT
public:
    explicit FanController(QObject *parent = 0);
    
    static int HID_vendorId(void);
    static int HID_productId(void);

    bool connect(void);
    void disconnect(void);

    bool isConnected(void) const;

signals:
    void deviceConnected(void);
    void deviceDisconnected(void);

public slots:
    void onPollTimerTriggered(void);
    void onRawData(QByteArray rawdata);

protected:
    void connectSignals(void);
    virtual void initResponseCodeMap(void);
    virtual void parseRawData(QByteArray rawdata);
    virtual int rawToTemp(char byte) const;
    virtual int rawToRPM(char highByte, char lowByte) const;

private:
    bool m_isConnected;
    DeviceIO m_io_device;

    static QMap<char, const fcResponseCodeDef*> m_responseCodes;
};


class FanControllerSettings
{
public:
    FanControllerSettings();

private:
    bool m_autoControl;
    bool m_reportTempInCelcius;
    bool m_displayOn;
};

#endif // PHOEBETRIA_FANCONTROLLER_H
