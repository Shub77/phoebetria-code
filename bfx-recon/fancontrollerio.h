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

#ifndef FANCONTROLLERIO_H
#define FANCONTROLLERIO_H

#include <QObject>

#include "device-io.h"
#include "profiles.h"

class FanControllerIO : public QObject
{
    Q_OBJECT
public:

    //---------------------------------------------------------------------

    enum ControlByte {

        RX_NULL                         = 0x00, /**< Not used by device. Required for calcChecksum() */

        TX_CurrentChannel               = 0x10, /**< Current selected channel (??) */

        TX_TempAndSpeed_Channel0        = 0x30, /**< IN  Temp in F and current speed (RPM) */
        TX_TempAndSpeed_Channel1        = 0x31, /**< IN   in F and current speed (RPM) */
        TX_TempAndSpeed_Channel2        = 0x32, /**< IN   in F and current speed (RPM) */
        TX_TempAndSpeed_Channel3        = 0x33, /**< IN   in F and current speed (RPM) */
        TX_TempAndSpeed_Channel4        = 0x34, /**< IN   in F and current speed (RPM) */

        RX_TempAndSpeed_Channel0        = 0x40, /**< OUT Temp in F and speed (RPM)*/
        RX_TempAndSpeed_Channel1        = 0x41, /**< OUT Temp in F and speed (RPM)*/
        RX_TempAndSpeed_Channel2        = 0x42, /**< OUT Temp in F and speed (RPM)*/
        RX_TempAndSpeed_Channel3        = 0x43, /**< OUT Temp in F and speed (RPM)*/
        RX_TempAndSpeed_Channel4        = 0x44, /**< OUT Temp in F and speed (RPM)*/

        TX_DeviceSettings               = 0x50, /**< IN  Device settings. See DeviceSetttingsFlag */
        RX_DeviceSettings               = 0x60, /**< OUT Device settings. See DeviceSetttingsFlag */

        TX_AlarmAndSpeed_Channel0       = 0x70, /**< OUT Alarm Temperature and Max RPM*/
        TX_AlarmAndSpeed_Channel1       = 0x71, /**< OUT Alarm Temperature and Max RPM*/
        TX_AlarmAndSpeed_Channel2       = 0x72, /**< OUT Alarm Temperature and Max RPM*/
        TX_AlarmAndSpeed_Channel3       = 0x73, /**< OUT Alarm Temperature and Max RPM*/
        TX_AlarmAndSpeed_Channel4       = 0x74, /**< OUT Alarm Temperature and Max RPM*/

        RX_AlarmAndSpeed_Channel0       = 0x80, /**< IN  Alarm Temperature and Max RPM*/
        RX_AlarmAndSpeed_Channel1       = 0x81, /**< IN  Alarm Temperature and Max RPM*/
        RX_AlarmAndSpeed_Channel2       = 0x82, /**< IN  Alarm Temperature and Max RPM*/
        RX_AlarmAndSpeed_Channel3       = 0x83, /**< IN  Alarm Temperature and Max RPM*/
        RX_AlarmAndSpeed_Channel4       = 0x84, /**< IN  Alarm Temperature and Max RPM*/

        TX_DeviceStatus                 = 0x90, /**< Status: Ready/Not Ready */

        RX_ACK                          = 0xF0,
        TX_NAK                          = 0xFA

    };

    //---------------------------------------------------------------------

    enum DeviceSettingsFlag {
        Auto                            = 1U << 0,
        Celcius                         = 1U << 1,
        AudibleAlarm                    = 1U << 2
    };


    //---------------------------------------------------------------------

    /** Calculates the data checksum present at the end of data blocks.
      *
      * The BitFenix Recon data block has a checksum at the end of the data.
      * The checksum for input blocks the ctrlByte does \em not influence
      * the checksum and therefore RX_NULL should be passed to this function
      * if the data is input data. If the data is output data, then the
      * ctrlByte is used in the checksum calculation and therefore should be
      * set appropriately.
      *
      * @param ctrlByte     @see FanControllerIO::ControlByte.
      * @param blockLen     The number of bytes in \em block .
      * @param block        The data to calculate a checksum for.
      */
    static unsigned char calcChecksum(
            ControlByte ctrlByte,
            int blockLen,
            const unsigned char* block
        );


    //---------------------------------------------------------------------

    /* Parsed Input from the device
     */
    class Input {

    public:

        // Set from raw data
        bool set(int blockLen, const unsigned char* block);

    private:
        ControlByte m_controlByte;
        unsigned char m_checksum;
        int m_dataLen;              // This may be < sizeof(m_data)
        unsigned char m_data[5];
    };


    //---------------------------------------------------------------------

    class Request {

    public:
        bool toURB(int blockLen, unsigned char *block, bool pad);

    private:
        ControlByte m_controlByte;
        int m_dataLen;              // This may be < sizeof(m_data)
        unsigned char m_data[4];    // Can only _send_ 4 data bytes
                                    // (incoming may have 5)
    };


    //---------------------------------------------------------------------

public:
    /* Constructors
     */
    explicit FanControllerIO(QObject *parent = 0);

    void connectSignals(void);

    bool connect(void);
    bool isConnected(void) const;
    void disconnect(void);

    bool setDeviceFlags(bool isCelcius, bool isAuto, bool isAudibleAlarm);
    bool setChannelSettings(int channel, unsigned thresholdF, unsigned speed);
    bool setFromProfile(const FanControllerProfile& profile);

    int minProbeTemp(bool inCelcius) const
        { return inCelcius ? -18 : 0; }     /* C : F */
    int maxProbeTemp(bool inCelcius) const
        { return inCelcius ? 124 : 255; }   /* C : F */

public slots:
    void onPollTimerTriggered(void);
    void onRawData(QByteArray rawdata);

private:

    DeviceIO m_io_device;


signals:
    void deviceConnected(void);
    void deviceDisconnected(void);
    void currentTemp(int probe, int temp);
    void currentRPM(int channel, int RPM);
    void maxRPM(int channel, int RPM);
    void currentAlarmTemp(int channel, int temp);
    void currentRpmOnAlarm(int channel, int RPM);
    void deviceSettings(bool isCelcius, bool isAuto, bool isAudibleAlarm);

};


#endif // FANCONTROLLERIO_H
