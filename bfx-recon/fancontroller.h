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
#include <QQueue>
#include "device-io.h"

typedef enum fcReponseCodeCategory {
    fcResp_TempAndSpeed,
    fcResp_DeviceFlags,
    fcResp_AlarmAndSpeed,
    fcResp_DeviceStatus,
    fcResp_Handshake,

    fcReq_TempAndSpeed,
    fcReq_AlarmAndSpeed,
    fcReq_DeviceFlags,
    fcReq_DeviceStatus,

    fcReq_CurrentChannel,

    fcSet_DeviceFlags
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

    int dataLen(void) const;
protected:

private:
    int channel;                // if applicable
    unsigned char checksum;
    const fcCommandDef* command;
    QByteArray data;
    int m_dataLen;
    int m_blockCommandsAfterExecuting_timeout;
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
    bool isReady(void);

    bool isInterfaceConnected(void) const;

    bool setDeviceFlags(bool isCelcius, bool isAuto, bool isAudibleAlarm);

    static const fcCommandDef* getResponseDef(unsigned char cmd);
    static const fcCommandDef* getCommandDef(fcCommandCategory category,
                                             int channel);

    bool waitingForAck(void) const { return m_blockRequestsTimeout > 0; }

signals:
    void deviceConnected(void);
    void deviceDisconnected(void);
    void currentTemp(int probe, int temp);
    void currentRPM(int channel, int RPM);
    void maxRPM(int channel, int RPM);
    void currentAlarmTemp(int channel, int temp);
    void currentRpmOnAlarm(int channel, unsigned RPM);
    void deviceSettings(bool isCelcius, bool isAuto, bool isAudibleAlarm);

public slots:
    void onPollTimerTriggered(void);
    void onRawData(QByteArray rawdata);

protected:
    void connectSignals(void);

    virtual bool parseRawData(QByteArray rawdata, FcData* parsedData);

    virtual void parseTempAndSpeed(int channel, const QByteArray& rawdata);
    virtual void parseDeviceFlags(const QByteArray& rawdata);
    virtual void parseAlarmAndSpeed(int channel, const QByteArray& rawdata);
    virtual void parseDeviceStatus(const QByteArray& rawdata);
    virtual void parseHandshake(const QByteArray& rawdata);

    virtual void requestDeviceStatus(void);
    virtual void requestTempAndSpeed(int channel);
    virtual void requestAlarmAndSpeed(int channel);
    virtual void requestDeviceFlags(void);

    virtual int rawToTemp(unsigned char byte) const;
    virtual int rawToRPM(char highByte, char lowByte) const;

    void issueCommand(const FcData &cmd);
    void processCommandQueue(void);

    void blockRequests(int count) { m_blockRequestsTimeout = count; }

private:
    bool m_deviceIsReady;
    DeviceIO m_io_device;

    static QMap<char, const fcCommandDef*> m_commandDefs;

    unsigned m_pollNumber;
    unsigned m_channelCycle;

    int m_blockRequestsTimeout;

    QQueue<FcData> m_cmdQueue;
};


#endif // PHOEBETRIA_FANCONTROLLER_H
