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

#include <QDebug>
#include <QStandardItemModel>
#include "gui_mainwindow.h"
#include "ui_gui_mainwindow.h"
#include "phoebetriaapp.h"
#include "bfx-recon/fancontroller.h"

gui_MainWindow::gui_MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::gui_MainWindow)
{
    ui->setupUi(this);

    for (int i = 0; i < FC_MAX_CHANNELS; i++) {
        m_maxTemps[i] = m_minTemps[i] = m_lastTemps[i]
                = m_minRPMs[i] = m_maxRPMs[i] = m_lastRPMs[i] = 0;

        /* Init to 1400 for now -- will be updated the first time we get real
         * values from the device
         */
        m_alarmTemps[i] = 1400;
    }

    m_isCelcius = ui->ctrl_tempScaleToggle->value() == 1 ? true : false;
    m_isAuto = ui->ctrl_isManual->value() == 0 ? true : false;
    m_isAudibleAlarm = ui->ctrl_isAudibleAlarm->value() == 1 ? true : false;

    m_isAutoToggleByDevice = false;
    m_isAutoToggleByDevice = false;
    m_isAudibleAlarmByDevice = false;

    initCtrlArrays();
    connectCustomSignals();
}

gui_MainWindow::~gui_MainWindow()
{
    delete ui;
}

void gui_MainWindow::initCtrlArrays(void)
{
    m_probeTempCtrls[0] = ui->ctrl_probe1Temp;
    m_probeTempCtrls[1] = ui->ctrl_probe2Temp;
    m_probeTempCtrls[2] = ui->ctrl_probe3Temp;
    m_probeTempCtrls[3] = ui->ctrl_probe4Temp;
    m_probeTempCtrls[4] = ui->ctrl_probe5Temp;

    m_channelTempCtrls[0] = ui->ctrl_channel1speed;
    m_channelTempCtrls[1] = ui->ctrl_channel2speed;
    m_channelTempCtrls[2] = ui->ctrl_channel3speed;
    m_channelTempCtrls[3] = ui->ctrl_channel4speed;
    m_channelTempCtrls[4] = ui->ctrl_channel5speed;

    m_minChannelTempCtrls[0] = ui->ctrl_channel1MinSpeed;
    m_minChannelTempCtrls[1] = ui->ctrl_channel2MinSpeed;
    m_minChannelTempCtrls[2] = ui->ctrl_channel3MinSpeed;
    m_minChannelTempCtrls[3] = ui->ctrl_channel4MinSpeed;
    m_minChannelTempCtrls[4] = ui->ctrl_channel5MinSpeed;

    m_maxChannelTempCtrls[0] = ui->ctrl_channel1MaxSpeed;
    m_maxChannelTempCtrls[1] = ui->ctrl_channel2MaxSpeed;
    m_maxChannelTempCtrls[2] = ui->ctrl_channel3MaxSpeed;
    m_maxChannelTempCtrls[3] = ui->ctrl_channel4MaxSpeed;
    m_maxChannelTempCtrls[4] = ui->ctrl_channel5MaxSpeed;

    m_channelSpeedSliders[0] = ui->ctrl_channel1speedSlider;
    m_channelSpeedSliders[1] = ui->ctrl_channel2speedSlider;
    m_channelSpeedSliders[2] = ui->ctrl_channel3speedSlider;
    m_channelSpeedSliders[3] = ui->ctrl_channel4speedSlider;
    m_channelSpeedSliders[4] = ui->ctrl_channel5speedSlider;
}


void gui_MainWindow::connectCustomSignals(void)
{
    PhoebetriaApp *app = (PhoebetriaApp*)qApp;

    connect(&app->fanController(), SIGNAL(currentRPM(int,int)),
            this, SLOT(onCurrentRPM(int,int)));
    connect(&app->fanController(), SIGNAL(currentTemp(int,int)),
            this, SLOT(onCurrentTemp(int,int)));
    connect(&app->fanController(), SIGNAL(deviceSettings(bool,bool,bool)),
            this, SLOT(onDeviceSettings(bool,bool,bool)));
    connect(&app->fanController(), SIGNAL(currentRpmOnAlarm(int, int)),
            this, SLOT(onCurrentRpmOnAlarm(int, int)));
}

void gui_MainWindow::updateMinMaxRPMs(int channel, int RPM)
{
    if (m_minRPMs[channel] > RPM || m_minRPMs[channel] == 0) {
        m_minRPMs[channel] = RPM;
        updateMinSpeedControl(channel, RPM);
    }

    if (m_maxRPMs[channel] < RPM) {
        m_maxRPMs[channel] = RPM;
        updateMaxSpeedControl(channel, RPM);
    }
}

void gui_MainWindow::updateMinSpeedControl(int channel, int RPM)
{
    m_minChannelTempCtrls[channel]->setText(QString::number(RPM));
}

void gui_MainWindow::updateMaxSpeedControl(int channel, int RPM)
{
    m_maxChannelTempCtrls[channel]->setText(QString::number(RPM));
}

void gui_MainWindow::enableDisableSpeedControls(void)
{
    bool enabled = ui->ctrl_isManual->value() == 1 ? true : false;

    for (int i = 0; i < FC_MAX_CHANNELS; i++) {
        m_channelSpeedSliders[i]->setEnabled(enabled);
    }
}

QString gui_MainWindow::temperatureString(int t) const
{
    QString r;
    int _t = m_isCelcius ? (t-32)*5/9 : t;
    r = QString::number(_t);
    r += (m_isCelcius ? " C" : " F");
    return r;
}

void gui_MainWindow::forceTempCtrlsToUpdate(void)
{
    // Force temp controls to be updated.
    // TODO: there is a better way to do this
    for (int i = 0; i < FC_MAX_CHANNELS; i++) {
        // The -1 is just to make sure the temp is different;
        // it will updated next refresh from the device
        onCurrentTemp(i, m_lastTemps[i] - 1);
    }
}

void gui_MainWindow::onCurrentRPM(int channel, int RPM)
{
    if (channel < 0 || channel > 4) {
        qDebug() << "Channel out of range ::onCurrentRPM" << channel;
        return;
    }

    if (m_lastRPMs[channel] != RPM) {
        m_lastRPMs[channel] = RPM;
        m_channelTempCtrls[channel]->setText(QString::number(RPM));
        updateMinMaxRPMs(channel, RPM);

        // TODO: Get Max RPM From controller
        int alarmTemp = m_alarmTemps[channel];
        m_channelSpeedSliders[channel]->setValue(RPM*100.0/alarmTemp);
    }
}



void gui_MainWindow::onCurrentTemp(int channel, int tempInF)
{
    if (channel < 0 || channel > 4) {
        qDebug() << "Channel out of range ::onCurrentTemp" << channel;
        return;
    }
    if (m_lastTemps[channel] != tempInF) {
        m_lastTemps[channel] = tempInF;
        m_probeTempCtrls[channel]->setText(temperatureString(tempInF));
    }
}

void gui_MainWindow::onDeviceSettings(bool isCelcius,
                                      bool isAuto,
                                      bool isAudibleAlarm)
{
    FanController* fc = &((PhoebetriaApp*)qApp)->fanController();

    if (m_isCelcius != isCelcius) {
        m_isCelcius = isCelcius;
        m_isCelciusToggleByDevice = true;
        ui->ctrl_tempScaleToggle->setValue(m_isCelcius ? 1 : 0);

        forceTempCtrlsToUpdate();
    }

    if (m_isAuto != isAuto) {
        m_isAuto = isAuto;
        m_isAutoToggleByDevice = true;
        ui->ctrl_isManual->setValue(m_isAuto ? 0 : 1);
        enableDisableSpeedControls();
    }

    if (m_isAudibleAlarm != isAudibleAlarm) {
        m_isAudibleAlarm = isAudibleAlarm;
        m_isAudibleAlarmByDevice = true;
        ui->ctrl_isAudibleAlarm->setValue(m_isAudibleAlarm ? 1 : 0);
    }

}

void gui_MainWindow::onCurrentRpmOnAlarm(int channel, int RPM)
{
    if (channel < 0 || channel > 4) {
        qDebug() << "Channel out of range ::onCurrentRpmOnAlarm" << channel;
        return;
    }
    m_alarmTemps[channel] = RPM;
}

void gui_MainWindow::on_ctrl_isManual_valueChanged(int value)
{
   if (m_isAutoToggleByDevice) {
        m_isAutoToggleByDevice = false;
        return;
   }

    m_isAuto = value == 0 ? true : false;

    FanController* fc = &((PhoebetriaApp*)qApp)->fanController();

    fc->setDeviceFlags(m_isCelcius, m_isAuto, m_isAudibleAlarm);

    enableDisableSpeedControls();
}

void gui_MainWindow::on_ctrl_isAudibleAlarm_valueChanged(int value)
{
    if (m_isAudibleAlarmByDevice) {
        m_isAudibleAlarmByDevice = false;
        return;
    }

    m_isAudibleAlarm = value == 1 ? true : false;

    FanController* fc = &((PhoebetriaApp*)qApp)->fanController();

    fc->setDeviceFlags(m_isCelcius, m_isAuto, m_isAudibleAlarm);
}

void gui_MainWindow::on_ctrl_tempScaleToggle_valueChanged(int value)
{
    if (m_isCelciusToggleByDevice) {
        m_isCelciusToggleByDevice = false;
        return;
    }

    m_isCelcius = value == 1 ? true : false;

    FanController* fc = &((PhoebetriaApp*)qApp)->fanController();

    fc->setDeviceFlags(m_isCelcius, m_isAuto, m_isAudibleAlarm);

    forceTempCtrlsToUpdate();
}

