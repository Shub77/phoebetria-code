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
        m_maxTemps[i] = m_minLoggedRPMs[i] = m_maxLoggedRPMs[i] = m_lastRPMs[i] = 0;
        m_lastTemps[i] = -1;
        m_minTemps[i] = 9999;

        m_alarmTemps[i] = -1;
        m_channelMaxRPM[i] = 1400;
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
    connect(&app->fanController(), SIGNAL(maxRPM(int, int)),
            this, SLOT(onMaxRPM(int, int)));
}

void gui_MainWindow::enableDisableSpeedControls(void)
{
    bool enabled = ui->ctrl_isManual->value() == 1 ? true : false;

    for (int i = 0; i < FC_MAX_CHANNELS; i++) {
        m_channelSpeedSliders[i]->setEnabled(enabled);
    }
}

void gui_MainWindow::updateSpeedControlTooltips(void)
{
    for (int i = 0; i < FC_MAX_CHANNELS; i++) {
        QString tooltip;
        tooltip += tr("Min Temp: ");
        tooltip += temperatureString(m_minTemps[i]);
        tooltip += "\n";
        tooltip += tr("Max Temp: ");
        tooltip += temperatureString(m_maxTemps[i]);
        tooltip += "\n";
        tooltip += tr("Min logged RPM: ");
        tooltip += QString::number(m_minLoggedRPMs[i]);
        tooltip += "\n";
        tooltip += tr("Max logged RPM: ");
        tooltip += QString::number(m_maxLoggedRPMs[i]);
        m_channelSpeedSliders[i]->setToolTip(tooltip);
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

        int maxRPM = m_channelMaxRPM[channel];
        //TODO: Check that alarmTemp != 0
        if (maxRPM < 1) maxRPM = 1;
        m_channelSpeedSliders[channel]->setValue(RPM*100.0/maxRPM);
    }
}



void gui_MainWindow::onCurrentTemp(int channel, int tempInF)
{
    if (channel < 0 || channel > 4) {
        qDebug() << "Channel out of range ::onCurrentTemp" << channel;
        return;
    }
    if (tempInF == -1) return;

    if (m_lastTemps[channel] != tempInF) {
        m_lastTemps[channel] = tempInF;
        m_probeTempCtrls[channel]->setText(temperatureString(tempInF));

        /* Sometimes -'ve temperatures are sent from the device (that are
         * incorrect). The specs page for the recon show 0-100C as the probes'
         * range, so ignore these -'ve values.
         */
        if (m_minTemps[channel] > tempInF && tempInF > -1) {
            m_minTemps[channel] = tempInF;
        }

        if (m_maxTemps[channel] < tempInF) {
            m_maxTemps[channel] = tempInF;
        }

        updateSpeedControlTooltips();
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



    // ************* TEST
    //FanController* fc = &((PhoebetriaApp*)qApp)->fanController();

    if (0)//!m_isAuto) {
        unsigned alarmTemp = this->m_alarmTemps[0];
        fc->setChannelSettings(0, alarmTemp, 1000);
    }

    // ************ END TEST

}

void gui_MainWindow::onMaxRPM(int channel, int RPM)
{
    if (channel < 0 || channel > 4) {
        qDebug() << "Channel out of range ::onCurrentRpmOnAlarm" << channel;
        return;
    }
    m_channelMaxRPM[channel] = RPM;
    forceTempCtrlsToUpdate();
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

