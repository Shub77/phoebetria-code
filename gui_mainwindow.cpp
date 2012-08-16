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
#include <cmath>
#include "gui_mainwindow.h"
#include "ui_gui_mainwindow.h"
#include "phoebetriaapp.h"
#include "bfx-recon/fancontroller.h"

#ifdef QT_DEBUG
#   include <QMessageBox>
#   include <QInputDialog>
#endif //QT_DEBUG

gui_MainWindow::gui_MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::gui_MainWindow)
{
    ui->setupUi(this);

    for (int i = 0; i < FC_MAX_CHANNELS; i++) {
        m_maxTemps[i] = 0;
        m_maxLoggedRPMs[i] = 0;
        m_lastRPMs[i] = -1;
        m_minLoggedRPMs[i] = -1;
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

    /* **** DEBUGGING MENU ***/
#ifdef QT_DEBUG

    m_debugMenu = ui->menuBar->addMenu("Debug");
    m_debug_setChannelSpeed = m_debugMenu->addAction("Set channel speed");

    connect(m_debug_setChannelSpeed, SIGNAL(triggered()),
            this, SLOT(onDebugMenu_setChannelSpeed()));

#endif
    /* **** END DEBUGGING MENU ***/
}

gui_MainWindow::~gui_MainWindow()
{
    delete ui;
}

void gui_MainWindow::initCtrlArrays(void)
{
    m_ctrls_probeTemps[0] = ui->ctrl_probe1Temp;
    m_ctrls_probeTemps[1] = ui->ctrl_probe2Temp;
    m_ctrls_probeTemps[2] = ui->ctrl_probe3Temp;
    m_ctrls_probeTemps[3] = ui->ctrl_probe4Temp;
    m_ctrls_probeTemps[4] = ui->ctrl_probe5Temp;

    m_ctrls_currentRPM[0] = ui->ctrl_channel1speed;
    m_ctrls_currentRPM[1] = ui->ctrl_channel2speed;
    m_ctrls_currentRPM[2] = ui->ctrl_channel3speed;
    m_ctrls_currentRPM[3] = ui->ctrl_channel4speed;
    m_ctrls_currentRPM[4] = ui->ctrl_channel5speed;

    m_ctrls_RpmSliders[0] = ui->ctrl_channel1speedSlider;
    m_ctrls_RpmSliders[1] = ui->ctrl_channel2speedSlider;
    m_ctrls_RpmSliders[2] = ui->ctrl_channel3speedSlider;
    m_ctrls_RpmSliders[3] = ui->ctrl_channel4speedSlider;
    m_ctrls_RpmSliders[4] = ui->ctrl_channel5speedSlider;

    m_ctrls_alarmTemps[0] = ui->ctrl_channel1alarmTemp;
    m_ctrls_alarmTemps[1] = ui->ctrl_channel2alarmTemp;
    m_ctrls_alarmTemps[2] = ui->ctrl_channel3alarmTemp;
    m_ctrls_alarmTemps[3] = ui->ctrl_channel4alarmTemp;
    m_ctrls_alarmTemps[4] = ui->ctrl_channel5alarmTemp;

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
    connect(&app->fanController(), SIGNAL(currentAlarmTemp(int,int)),
            this, SLOT(onCurrentAlarmTemp(int,int)));
}

void gui_MainWindow::enableDisableSpeedControls(void)
{
    bool enabled = ui->ctrl_isManual->value() == 1 ? true : false;

    for (int i = 0; i < FC_MAX_CHANNELS; i++) {
        m_ctrls_RpmSliders[i]->setEnabled(enabled);
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
        m_ctrls_RpmSliders[i]->setToolTip(tooltip);
    }
}

void gui_MainWindow::updateSpeedControl(int channel, int RPM)
{
    Q_ASSERT(channel >= 0 && channel <= 4); // pre-condition

    int maxRPM = m_channelMaxRPM[channel];
    if (maxRPM < 1) maxRPM = 1;

    m_ctrls_RpmSliders[channel]->setValue(ceil(RPM*100.0/maxRPM));
    qDebug() << "============ Setting slider value to" << ceil(RPM*100.0/maxRPM);
    qDebug() << "============  Actual slider value is" <<  m_ctrls_RpmSliders[channel]->value();
    qDebug() << "==== Expected max RPM for channel is" << m_channelMaxRPM[channel];

    m_ctrls_currentRPM[channel]->setText(QString::number(RPM));
}


void gui_MainWindow::updateAlarmTempControl(int channel)
{
    Q_ASSERT(channel >= 0 && channel <= 4); // pre-condition

    m_ctrls_alarmTemps[channel]->setText(
                temperatureString(m_alarmTemps[channel]) );
}


QString gui_MainWindow::temperatureString(int t) const
{
    QString r;
    int _t = m_isCelcius ? ceil((t-32)*5.0/9) : t;
    r = QString::number(_t);
    r += (m_isCelcius ? " C" : " F");
    return r;
}

void gui_MainWindow::updateAllSpeedCtrls(void)
{
    for (int i = 0; i < FC_MAX_CHANNELS; i++) {
        updateSpeedControl(i, m_lastRPMs[i]);
    }
}


void gui_MainWindow::updateAllAlarmCtrls(void)
{
    for (int i = 0; i < FC_MAX_CHANNELS; i++) {
        updateAlarmTempControl(i);
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

        if (m_maxLoggedRPMs[channel] < RPM) {
            m_maxLoggedRPMs[channel] = RPM;
            updateSpeedControlTooltips();
        }
        if (m_minLoggedRPMs[channel] > RPM
                 || m_minLoggedRPMs[channel] == -1) {
            m_minLoggedRPMs[channel] = RPM;
            updateSpeedControlTooltips();
        }

        updateSpeedControl(channel, RPM);
    }
}



void gui_MainWindow::onCurrentTemp(int channel, int tempInF)
{
    if (channel < 0 || channel > 4) {
        qDebug() << "Channel out of range ::onCurrentTemp" << channel;
        return;
    }

    /* Sometimes -'ve temperatures are sent from the device (that are
     * incorrect). The specs page for the recon show 0-100C as the probes'
     * range, so ignore these -'ve values.
     */
    if (tempInF < 0) return;

    if (m_lastTemps[channel] != tempInF) {
        m_lastTemps[channel] = tempInF;

        m_ctrls_probeTemps[channel]->setText(temperatureString(tempInF));

        if (m_minTemps[channel] > tempInF) {
            m_minTemps[channel] = tempInF;
        }

        if (m_maxTemps[channel] < tempInF) {
            m_maxTemps[channel] = tempInF;
        }

        updateSpeedControlTooltips();
    }
}

void gui_MainWindow::onCurrentAlarmTemp(int channel, int tempInF)
{
    if (channel < 0 || channel > 4) {
        qDebug() << "Channel out of range ::onCurrentTemp" << channel;
        return;
    }

    if (m_alarmTemps[channel] != tempInF) {
        m_alarmTemps[channel] = tempInF;
        updateAlarmTempControl(channel);
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

        updateAllSpeedCtrls();
        updateAllAlarmCtrls();
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

void gui_MainWindow::onMaxRPM(int channel, int RPM)
{
    if (channel < 0 || channel > 4) {
        qDebug() << "Channel out of range ::onCurrentRpmOnAlarm" << channel;
        return;
    }
    m_channelMaxRPM[channel] = RPM;

    updateSpeedControl(channel, m_lastRPMs[channel]);
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

    updateAllSpeedCtrls();
}

/**************************************************************************
  Debugging menu
 *************************************************************************/
#ifdef QT_DEBUG

void gui_MainWindow::onDebugMenu_setChannelSpeed()
{
    if (m_isAuto) {
        QMessageBox mbox;
        mbox.setText("Recon must be in manual mode to set channel speed");
        mbox.exec();
        return;
    }

    bool ok;
    int channel;
    channel = QInputDialog::getInt(this, tr("Channel (1-5)"), tr("Channel"), 0, 1, 5, 1, &ok);
    if (!ok) {
        qDebug() << "onDebugMenu_setChannelSpeed: Channel invalid, or cancelled";
        return;
    }
    int speed;

    speed = QInputDialog::getInt(this, tr("Speed"), tr("RPM"), 0, 0, 50000, 1, &ok);
    if (!ok) {
        qDebug() << "onDebugMenu_setChannelSpeed: Invalid speed, or cancelled";
        return;
    }

    if (speed < m_channelMaxRPM[channel-1] * 0.4 && speed != 0) {
        qDebug() << "Speed is less than 40%, but not OFF. Setting to 40%";
        speed = ceil(m_channelMaxRPM[channel-1] * 0.4);
    }

    // Speeds must be in multiples of 100 RPM
    //double _speed = m_channelMaxRPM[channel-1] * 0.4;
    double _speed = ((int)(speed / 100.0))*100;
    speed = _speed;

    qDebug() << "reported max speed for channel"
                << channel
                << "is"
                << m_channelMaxRPM[channel-1]
                   ;
    qDebug() << "attempting to set channel "
                << QString::number(channel)
                << "to speed "
                << QString::number(speed)
                << "RPM"
                   ;

    FanController* fc = &((PhoebetriaApp*)qApp)->fanController();

    if (fc->setChannelSettings(channel-1, m_alarmTemps[channel-1], speed)) {
        updateSpeedControl(channel-1, speed);
    }


}

#endif
