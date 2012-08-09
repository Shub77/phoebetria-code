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
    fcResp_Handshake,

    fcReq_GetChannelSettings,
    fcReq_GetDeviceStatus,
    fcReq_GetCurrentChannel,
    fcReq_GetDeviceFlags

} fcCommandCategory;


typedef struct fcCommandDef
{
    fcCommandCategory category;
    int channel;                // if applicable
    unsigned char commandByte;
    const QString desc;         // natural language description
} fcCommandDef;


class FcData {

    friend class FanController;

public:
    FcData();
    FcData(const QByteArray& rawData);

    unsigned char calcChecksum(bool isRequest) const;

    bool setFromRawData(const QByteArray& rawdata);
    bool toRawData(char *dest, int buffLen, bool pad = true);
protected:

private:
    int channel;                // if applicable
    unsigned char checksum;
    const fcCommandDef* command;
    QByteArray data;
};


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
    bool isReady(void) { return m_deviceIsReady; }

    bool isConnected(void) const;

    static const fcCommandDef* commandDef(char cmd) { return m_commandDefs.value(cmd); }
signals:
    void deviceConnected(void);
    void deviceDisconnected(void);

public slots:
    void onPollTimerTriggered(void);
    void onRawData(QByteArray rawdata);

protected:
    void connectSignals(void);
    virtual void initCommandDefs(void);

    virtual bool parseRawData(QByteArray rawdata, FcData* parsedData);

    virtual void parseTempAndSpeed(int channel, const QByteArray& rawdata);
    virtual void parseDeviceFlags(const QByteArray& rawdata);
    virtual void parseAlarmAndSpeed(int channel, const QByteArray& rawdata);
    virtual void parseDeviceStatus(const QByteArray& rawdata);
    virtual void parseHandshake(const QByteArray& rawdata);

    virtual void requestDeviceStatus(void);

    virtual int rawToTemp(unsigned char byte) const;
    virtual unsigned rawToRPM(char highByte, char lowByte) const;

private:
    bool m_deviceIsReady;
    DeviceIO m_io_device;

    static QMap<char, const fcCommandDef*> m_commandDefs;

    unsigned m_pollNumber;
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
