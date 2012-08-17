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
#include <QInputDialog>
#include <cmath>
#include "gui_mainwindow.h"
#include "ui_gui_mainwindow.h"
#include "phoebetriaapp.h"
#include "bfx-recon/fancontroller.h"
#include "gui_about.h"

#ifdef QT_DEBUG
#   include <QMessageBox>

#endif //QT_DEBUG


gui_MainWindow::gui_MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::gui_MainWindow)
{
    ui->setupUi(this);

    for (int i = 0; i < FC_MAX_CHANNELS; i++) {
        m_speedSliderMovedByDevice[i] = false;
    }

    m_fcd.setIsCelcius((ui->ctrl_tempScaleToggle->value() == 1 ? true : false));
    m_fcd.setIsAuto((ui->ctrl_isManual->value() == 0 ? true : false));
    m_fcd.setIsAudibleAlarm((ui->ctrl_isAudibleAlarm->value() == 1 ? true : false));

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

    m_ctrls_alarmTemps[0] = ui->ctrl_channel1AlarmTemp;
    m_ctrls_alarmTemps[1] = ui->ctrl_channel2AlarmTemp;
    m_ctrls_alarmTemps[2] = ui->ctrl_channel3AlarmTemp;
    m_ctrls_alarmTemps[3] = ui->ctrl_channel4AlarmTemp;
    m_ctrls_alarmTemps[4] = ui->ctrl_channel5AlarmTemp;

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

void gui_MainWindow::updateSpeedControlTooltip(int channel)
{
    Q_ASSERT(channel >= 0 && channel <= 4); // pre-condition

    QString tooltip;
    tooltip += tr("Min Temp: ");
    tooltip += FanControllerData::temperatureString(
                m_fcd.minTemp(channel),
                m_fcd.isCelcius(),
                true);
    tooltip += "\n";
    tooltip += tr("Max Temp: ");
    tooltip += FanControllerData::temperatureString(
                m_fcd.maxTemp(channel),
                m_fcd.isCelcius(),
                true);
    tooltip += "\n";
    tooltip += tr("Min logged RPM: ");
    tooltip += QString::number(m_fcd.minLoggedRPM(channel));

    tooltip += "\n";
    tooltip += tr("Max logged RPM: ");
    tooltip += QString::number(m_fcd.maxLoggedRPM(channel));

    m_ctrls_RpmSliders[channel]->setToolTip(tooltip);
}

void gui_MainWindow::updateSpeedControlTooltips(void)
{
    for (int i = 0; i < FC_MAX_CHANNELS; i++) {
        updateSpeedControlTooltip(i);
    }
}

void gui_MainWindow::updateSpeedControl(int channel, int RPM)
{
    Q_ASSERT(channel >= 0 && channel <= 4); // pre-condition

    int maxRPM = m_fcd.maxRPM(channel);
    if (maxRPM < 1) maxRPM = 1;

    bool sb = m_ctrls_RpmSliders[channel]->blockSignals(true);
    m_ctrls_RpmSliders[channel]->setValue(ceil(RPM*100.0/maxRPM));
    QString RpmText;
    RpmText = RPM == 0 ? "OFF" : QString::number(RPM);
    m_ctrls_currentRPM[channel]->setText(RpmText);
    m_ctrls_RpmSliders[channel]->blockSignals(sb);

#if 0
    qDebug() << "============ Setting slider value to" << ceil(RPM*100.0/maxRPM);
    qDebug() << "============  Actual slider value is" <<  m_ctrls_RpmSliders[channel]->value();
    qDebug() << "==== Expected max RPM for channel is" << m_channelMaxRPM[channel];
#endif
}

void gui_MainWindow::updateCurrentTempControl(int channel, int temp)
{
    m_ctrls_probeTemps[channel]->setText(
                FanControllerData::temperatureString(
                    temp,
                    m_fcd.isCelcius(),
                    true) );
}

void gui_MainWindow::updateAllCurrentTempControls(void)
{
    for (int i = 0; i < FC_MAX_CHANNELS; i++) {
        updateCurrentTempControl(i, m_fcd.lastTemp(i));
    }
}


void gui_MainWindow::updateAlarmTempControl(int channel, int temp, bool isCelcius)
{
    Q_ASSERT(channel >= 0 && channel <= 4); // pre-condition

    m_ctrls_alarmTemps[channel]->setText(
        FanControllerData::temperatureString(
                    temp,
                    m_fcd.isCelcius(),
                    true) );

}

void gui_MainWindow::updateAllAlarmCtrls(bool isCelcius)
{
    for (int i = 0; i < FC_MAX_CHANNELS; i++) {
        updateAlarmTempControl(i, m_fcd.alarmTemp(i), isCelcius);
    }
}

void gui_MainWindow::updateAllSpeedCtrls(void)
{
    for (int i = 0; i < FC_MAX_CHANNELS; i++) {
        updateSpeedControl(i, m_fcd.lastRPM(i));
    }
}

void gui_MainWindow::onCurrentRPM(int channel, int RPM)
{
    Q_ASSERT(channel >= 0 && channel <= 4); // pre-condition

    if (m_fcd.lastRPM(channel) != RPM) {
        m_fcd.setLastRPM(channel, RPM);

        if (m_fcd.maxLoggedRPM(channel) < RPM) {
            m_fcd.setMaxLoggedRPM(channel, RPM);
            updateSpeedControlTooltip(channel);
        }
        if (m_fcd.minLoggedRPM(channel) > RPM
                || m_fcd.minLoggedRPM(channel) == -1) {
            m_fcd.setMinLoggedRPM(channel, RPM);
            updateSpeedControlTooltip(channel);
        }
        m_speedSliderMovedByDevice[channel] = true;

        updateSpeedControl(channel, RPM);
    }
}



void gui_MainWindow::onCurrentTemp(int channel, int tempInF)
{
    Q_ASSERT(channel >= 0 && channel <= 4); // pre-condition

    /* Sometimes -'ve temperatures are sent from the device (that are
     * incorrect). The specs page for the recon show 0-100C as the probes'
     * range, so ignore these -'ve values.
     */
    if (tempInF < 0) return;

    if (m_fcd.lastTemp(channel) != tempInF) {
        m_fcd.setLastTemp(channel, tempInF);

        updateCurrentTempControl(channel, tempInF);

        if (m_fcd.maxTemp(channel) < tempInF) {
            m_fcd.setMaxTemp(channel, tempInF);
        }
        if (m_fcd.minTemp(channel) > tempInF) {
            m_fcd.setMinTemp(channel, tempInF);
        }

        updateSpeedControlTooltip(channel);
    }
}

void gui_MainWindow::onCurrentAlarmTemp(int channel, int tempInF)
{
    Q_ASSERT(channel >= 0 && channel <= 4); // pre-condition

    if (m_fcd.alarmTemp(channel) != tempInF) {
        m_fcd.setAlarmTemp(channel, tempInF);
        updateAlarmTempControl(channel, tempInF, m_fcd.isCelcius());
    }
}


void gui_MainWindow::onDeviceSettings(bool isCelcius,
                                      bool isAuto,
                                      bool isAudibleAlarm)
{
    FanController* fc = &((PhoebetriaApp*)qApp)->fanController();

    if (m_fcd.isCelcius() != isCelcius) {
        m_fcd.setIsCelcius(isCelcius);
        m_isCelciusToggleByDevice = true;
        ui->ctrl_tempScaleToggle->setValue(isCelcius ? 1 : 0);

        updateAllAlarmCtrls(m_fcd.isCelcius());
    }

    if (m_fcd.isAuto()!= isAuto) {
        m_fcd.setIsAuto(isAuto);
        m_isAutoToggleByDevice = true;
        ui->ctrl_isManual->setValue(isAuto ? 0 : 1);
        enableDisableSpeedControls();
    }

    if (m_fcd.isAudibleAlarm() != isAudibleAlarm) {
        m_fcd.setIsAudibleAlarm(isAudibleAlarm);
        m_isAudibleAlarmByDevice = true;
        ui->ctrl_isAudibleAlarm->setValue(isAudibleAlarm ? 1 : 0);
    }
}

void gui_MainWindow::onMaxRPM(int channel, int RPM)
{
    Q_ASSERT(channel >= 0 && channel <= 4); // pre-condition

    m_fcd.setMaxRPM(channel, RPM);

    updateSpeedControl(channel, m_fcd.lastRPM(channel));
}

void gui_MainWindow::on_ctrl_isManual_valueChanged(int value)
{
   if (m_isAutoToggleByDevice) {
        m_isAutoToggleByDevice = false;
        return;
   }

    m_fcd.setIsAuto((value == 0 ? true : false));

    FanController* fc = &((PhoebetriaApp*)qApp)->fanController();

    fc->setDeviceFlags(m_fcd.isCelcius(),
                       m_fcd.isAuto(),
                       m_fcd.isAudibleAlarm()
                       );

    enableDisableSpeedControls();
}

void gui_MainWindow::on_ctrl_isAudibleAlarm_valueChanged(int value)
{
    if (m_isAudibleAlarmByDevice) {
        m_isAudibleAlarmByDevice = false;
        return;
    }

    m_fcd.setIsAudibleAlarm((value == 1 ? true : false));

    FanController* fc = &((PhoebetriaApp*)qApp)->fanController();

    fc->setDeviceFlags(m_fcd.isCelcius(),
                       m_fcd.isAuto(),
                       m_fcd.isAudibleAlarm()
                       );
}

void gui_MainWindow::on_ctrl_tempScaleToggle_valueChanged(int value)
{
    if (m_isCelciusToggleByDevice) {
        m_isCelciusToggleByDevice = false;
        return;
    }

    m_fcd.setIsCelcius((value == 1 ? true : false));

    FanController* fc = &((PhoebetriaApp*)qApp)->fanController();

    fc->setDeviceFlags(m_fcd.isCelcius(),
                       m_fcd.isAuto(),
                       m_fcd.isAudibleAlarm()
                       );

    updateAllAlarmCtrls(m_fcd.isCelcius());
    updateAllCurrentTempControls();
}

/**************************************************************************
  Debugging menu
 *************************************************************************/
#ifdef QT_DEBUG

void gui_MainWindow::onDebugMenu_setChannelSpeed()
{
    if (m_fcd.isAuto()) {
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
    --channel;
    int speed;

    speed = QInputDialog::getInt(this, tr("Speed"), tr("RPM"), 0, 0, 50000, 1, &ok);
    if (!ok) {
        qDebug() << "onDebugMenu_setChannelSpeed: Invalid speed, or cancelled";
        return;
    }

    int channelMaxRPM = m_fcd.maxRPM(channel);

    if (speed < channelMaxRPM * 0.4 && speed != 0) {
        qDebug() << "Speed is less than 40%, but not OFF. Setting to 40%";
        speed = ceil(channelMaxRPM * 0.4);
    }

    // Speeds must be in multiples of 100 RPM

    double _speed = ((int)(speed / 100.0))*100;
    speed = _speed;

    qDebug() << "reported max speed for channel"
                << channel+1
                << "is"
                << channelMaxRPM
                   ;
    qDebug() << "attempting to set channel "
                << channel+1
                << "to speed "
                << QString::number(speed)
                << "RPM"
                   ;

    FanController* fc = &((PhoebetriaApp*)qApp)->fanController();

    int channelAlarmTemp = m_fcd.alarmTemp(channel);

    if (fc->setChannelSettings(channel, channelAlarmTemp, speed)) {
        updateSpeedControl(channel, speed);
    }
}

#endif


// TODO: Move this into class ChannelData
void gui_MainWindow::setFcChannelSpeed(int channel, int RPM)
{
    FanController* fc = &((PhoebetriaApp*)qApp)->fanController();

    int channelAlarmTemp = m_fcd.alarmTemp(channel);

    if (fc->setChannelSettings(channel, channelAlarmTemp, RPM)) {
        updateSpeedControl(channel, RPM);
        m_fcd.setManualRPM(channel, RPM);
    }
}

void gui_MainWindow::userPressedChannelRpmSlider(int channel)
{
    FanController* fc = &((PhoebetriaApp*)qApp)->fanController();
    fc->blockSignals(true);
}

void gui_MainWindow::userReleasedChannelRpmSlider(int channel)
{
    FanController* fc = &((PhoebetriaApp*)qApp)->fanController();
    fc->blockSignals(false);
    int val = rpmSliderValueToRPM(channel, m_ctrls_RpmSliders[channel]->value());
    if (val != m_fcd.lastRPM(channel)) {
        setFcChannelSpeed(channel, val);
        qDebug() << "New slider value for channel"
                    << QString::number(channel+1)
                    << "is"
                    << QString::number((int)val);
    }
}

void gui_MainWindow::userChangedChannelRpmSlider(int channel, int value)
{
    FanController* fc = &((PhoebetriaApp*)qApp)->fanController();

    int val = rpmSliderValueToRPM(channel, value);
    m_ctrls_currentRPM[channel]->setText(QString::number((int)val));
    if (!m_ctrls_RpmSliders[channel]->isSliderDown()
            && val != m_fcd.lastRPM(channel)) {
        setFcChannelSpeed(channel, val);
        qDebug() << "New slider value for channel"
                    << QString::number(channel+1)
                    << "is"
                    << QString::number((int)val);
    }
}

int gui_MainWindow::rpmSliderValueToRPM(int channel, int value) const
{
    int channelMaxRPM = m_fcd.maxRPM(channel);
    int channelMinRPM = (int)(channelMaxRPM * 0.50 / 100) * 100;

    double val = value / 100.0 * channelMaxRPM;
    val = int(val / 100) * 100;
    if (val < channelMinRPM) val = 0;
    return val;
}

void gui_MainWindow::userClickedAlarmTempCtrl(int channel)
{
    int currentAlarmTemp;
    int userTemperature;
    bool ok;

    currentAlarmTemp = m_fcd.alarmTemp(channel);
    if (m_fcd.isCelcius()) {
        currentAlarmTemp = m_fcd.toCelcius(currentAlarmTemp);
    }
    FanController* fc = &((PhoebetriaApp*)qApp)->fanController();
    int minProbeTemp = fc->minProbeTemp(m_fcd.isCelcius());
    int maxProbTemp = fc->maxProbeTemp(m_fcd.isCelcius());

    QString prompt = QString(tr("Enter new alarm temperature %1"
                                " for channel %2.\nRange is %3 to %4"))
                             .arg(m_fcd.isCelcius() ? "C" : "F")
                             .arg(channel)
                             .arg(minProbeTemp)
                             .arg(maxProbTemp);

    userTemperature = QInputDialog::getInt(this,
                                           tr("Enter alarm temperature"),
                                           prompt,
                                           currentAlarmTemp,
                                           minProbeTemp,
                                           maxProbTemp,
                                           1,
                                           &ok);
    if (m_fcd.isCelcius()) {
        userTemperature = m_fcd.toFahrenheit(userTemperature);
    }

    if (userTemperature != currentAlarmTemp) {
        fc->setChannelSettings(channel, userTemperature, m_fcd.maxRPM(channel));
        updateAlarmTempControl(channel, userTemperature, m_fcd.isCelcius());
    }
}

void gui_MainWindow::on_ctrl_channel1speedSlider_sliderPressed()
{
    userPressedChannelRpmSlider(0);
}
void gui_MainWindow::on_ctrl_channel1speedSlider_sliderReleased()
{
    userReleasedChannelRpmSlider(0);
}
void gui_MainWindow::on_ctrl_channel1speedSlider_valueChanged(int value)
{
    userChangedChannelRpmSlider(0, value);
}


void gui_MainWindow::on_ctrl_channel2speedSlider_sliderPressed()
{
    userPressedChannelRpmSlider(1);
}
void gui_MainWindow::on_ctrl_channel2speedSlider_sliderReleased()
{
    userReleasedChannelRpmSlider(1);
}
void gui_MainWindow::on_ctrl_channel2speedSlider_valueChanged(int value)
{
    userChangedChannelRpmSlider(1, value);
}


void gui_MainWindow::on_ctrl_channel3speedSlider_sliderPressed()
{
    userPressedChannelRpmSlider(2);
}
void gui_MainWindow::on_ctrl_channel3speedSlider_sliderReleased()
{
    userReleasedChannelRpmSlider(2);
}
void gui_MainWindow::on_ctrl_channel3speedSlider_valueChanged(int value)
{
    userChangedChannelRpmSlider(2, value);
}


void gui_MainWindow::on_ctrl_channel4speedSlider_sliderPressed()
{
    userPressedChannelRpmSlider(3);
}
void gui_MainWindow::on_ctrl_channel4speedSlider_sliderReleased()
{
    userReleasedChannelRpmSlider(3);
}
void gui_MainWindow::on_ctrl_channel4speedSlider_valueChanged(int value)
{
    userChangedChannelRpmSlider(3, value);
}


void gui_MainWindow::on_ctrl_channel5speedSlider_sliderPressed()
{
    userPressedChannelRpmSlider(4);
}
void gui_MainWindow::on_ctrl_channel5speedSlider_sliderReleased()
{
    userReleasedChannelRpmSlider(4);
}
void gui_MainWindow::on_ctrl_channel5speedSlider_valueChanged(int value)
{
    userChangedChannelRpmSlider(4, value);
}


void gui_MainWindow::on_ctrl_channel1AlarmTemp_clicked()
{
    userClickedAlarmTempCtrl(0);
}
void gui_MainWindow::on_ctrl_channel2AlarmTemp_clicked()
{
    userClickedAlarmTempCtrl(1);
}
void gui_MainWindow::on_ctrl_channel3AlarmTemp_clicked()
{
    userClickedAlarmTempCtrl(2);
}
void gui_MainWindow::on_ctrl_channel4AlarmTemp_clicked()
{
    userClickedAlarmTempCtrl(3);
}
void gui_MainWindow::on_ctrl_channel5AlarmTemp_clicked()
{
    userClickedAlarmTempCtrl(4);
}

void gui_MainWindow::on_actionAbout_triggered()
{
    gui_About* aboutDlg = new gui_About(this);
    aboutDlg->exec();
}
