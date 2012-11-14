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
#include <QFileDialog>
#include <QMessageBox>
#include <QCloseEvent>
#include <cmath>
#include "gui_mainwindow.h"
#include "ui_gui_mainwindow.h"
#include "phoebetriaapp.h"
#include "bfx-recon/fancontrollerio.h"
#include "gui_about.h"
#include "gui_preferences.h"
#include "fanprofiles.h"
#include "qglobal.h"
#include "gui_simplesqlqry.h"
#include "gui_softwareautosetup.h"
#include "gui_profiles.h"

gui_MainWindow::gui_MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::gui_MainWindow),
    m_softwareAuto(parent)
{
    ui->setupUi(this);

    // Stop resizing
    //this->setFixedSize(this->size());

    // Make sure the "Control" tab is at the front
//    if (ui->tabWidget->currentIndex() != 0)
//    {
//        ui->tabWidget->setCurrentIndex(0);
//    }

#if defined Q_WS_WIN
    m_trayIcon.setIcon(QIcon(":/icon16x16"));
#elif defined Q_WS_MAC
    m_trayIcon.setIcon(QIcon(":/icon22x22"));
#elif defined Q_WS_X11
    m_trayIcon.setIcon(QIcon(":/icon22x22"));
#else
    m_trayIcon.setIcon(QIcon(":/icon16x16"));
#endif

    m_trayIcon.setToolTip("Phoebetria");
    connect(&m_trayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
            this, SLOT(onTrayIconActivated(QSystemTrayIcon::ActivationReason)));

    setWindowIcon(QIcon(":/icon16x16"));

    initCtrlArrays();
    populate_ctrl_PresetName();

    // Synchronise fan controller data with GUI.

    FanControllerIO* fc = &ph_fanControllerIO();

    if (fc->isConnected() == false)
    {
        ui->ctrl_logoAndStatus->setStyleSheet("background-image: url(:/Images/phoebetria_icon_error.png);");
    }

    connectCustomSignals();
    initWaitForReqChannelParams();

}

void gui_MainWindow::closeEvent(QCloseEvent *event)
{
    // URGENT
    // FIXME: This will not work. What needs to happen is for the close
    //        to be delayed until the RECON actually ACKs the commands
    //        to return it to the state it was in before software auto
    //        was turned on.
    //
    setSoftwareAutoOn(false);
    event->accept();
}

void gui_MainWindow::syncGuiCtrlsWithFanController(void)
{
    FanControllerData& fcd = fcdata();

    updateSpeedControlTooltips();
    updateAllSpeedCtrls();
    updateAllAlarmCtrls(fcd.isCelcius());
    updateToggleControls();
    enableSpeedControls(!fcd.isAuto());
}


void gui_MainWindow::setSoftwareAutoOn(bool yes)
{
    FanControllerData& fcd = fcdata();

    if (yes)
    {
        m_softwareAuto.switchOn(ph_fanControllerIO(), fcd);
    }
    else
    {
        m_softwareAuto.switchOff(ph_fanControllerIO(), fcd);
    }

    updateToggleControls();
    updateAllSpeedCtrls();
    updateRpmIndicators();
}

void gui_MainWindow::initWaitForReqChannelParams(void)
{
    m_reqChannelParamsAreSet = false;

    EventDispatcher& ed = ph_phoebetriaApp()->dispatcher();

    connect(&ed, SIGNAL(tick()),
            this, SLOT(checkForReqChannelParems()));

    checkForReqChannelParems();
}

void gui_MainWindow::checkForReqChannelParems(void)
{

    if (!ph_fanControllerIO().isConnected())
        return;

    if (fcdata().ramp_reqParamsForInitAreSet())
    {
        m_reqChannelParamsAreSet = true;
        ui->ctrl_configSoftwareAutoBtn->setEnabled(true);

        EventDispatcher& ed = ph_phoebetriaApp()->dispatcher();

        disconnect(&ed, SIGNAL(tick()));

        fcdata().initAllRamps();
    }
}

bool gui_MainWindow::customAutoAvailable(void) const
{
    return m_reqChannelParamsAreSet;
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

    m_ctrls_rpmIndicator[0] = ui->ctrl_channel1RpmIndicator;
    m_ctrls_rpmIndicator[1] = ui->ctrl_channel2RpmIndicator;
    m_ctrls_rpmIndicator[2] = ui->ctrl_channel3RpmIndicator;
    m_ctrls_rpmIndicator[3] = ui->ctrl_channel4RpmIndicator;
    m_ctrls_rpmIndicator[4] = ui->ctrl_channel5RpmIndicator;

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

FanControllerData& gui_MainWindow::fcdata(void) const
{
    return ph_fanControllerData();
}

void gui_MainWindow::connectCustomSignals(void)
{
    const FanControllerData& fcd = fcdata();

    // **** Signals for common settings

    connect(&fcd, SIGNAL(controlMode_changed(bool)),
            this, SLOT(onControlModeChanged(bool)));

    connect(&fcd, SIGNAL(temperatureScale_changed(bool)),
            this, SLOT(onTemperatureScaleChanged(bool)));

    connect(&fcd, SIGNAL(alarmIsAudible_changed(bool)),
            this, SLOT(onIsAudibleAlarmChanged(bool)));

    // **** Channel related signals

    connect(&fcd, SIGNAL(RPM_changed(int,int)),
            this, SLOT(onCurrentRPM(int,int)));

    connect(&fcd, SIGNAL(manualRPM_changed(int,int)),
            this, SLOT(onManualRPMChanged(int,int)));

    connect(&fcd, SIGNAL(temperature_changed(int,int)),
            this, SLOT(onCurrentTemp(int,int)));

    connect(&fcd, SIGNAL(maxRPM_changed(int, int)),
            this, SLOT(onMaxRPM(int, int)));

    connect(&fcd, SIGNAL(currentAlarmTemp_changed(int,int)),
            this, SLOT(onCurrentAlarmTemp(int,int)));


    // **** Logging related signals

    connect(&fcd, SIGNAL(minLoggedRPM_changed(int,int)),
            this, SLOT(onMinLoggedRpmChanged(int,int)));

    connect(&fcd, SIGNAL(maxLoggedRPM_changed(int,int)),
            this, SLOT(onMaxLoggedRpmChanged(int,int)));

    connect(&fcd, SIGNAL(minLoggedTemp_changed(int,int)),
            this, SLOT(onMinLoggedTempChanged(int,int)));

    connect(&fcd, SIGNAL(maxLoggedTemp_changed(int,int)),
            this, SLOT(onMaxLoggedTempChanged(int,int)));
}


void gui_MainWindow::populate_ctrl_PresetName(void)
{
    FanControllerProfile fcp;
    ui->ctrl_PresetName->clear();

    QStringList items = fcp.getProfileNames();

    bool bs = ui->ctrl_PresetName->blockSignals(true);

    for (int i = 0; i < items.count(); ++i)
    {
        const QString& item = items.at(i);
        // Skip reserved profile names
        if (FanControllerProfile::isReservedProfileName(item)) continue;
        ui->ctrl_PresetName->addItem(item);
    }

    ui->ctrl_PresetName->blockSignals(bs);
}

void gui_MainWindow::enableSpeedControls(bool enabled)
{
    //bool enabled = ui->ctrl_isManual->value() == 1 ? true : false;
    //bool enabled = !fcdata().isAuto();

    for (int i = 0; i < FC_MAX_CHANNELS; i++)
    {
        m_ctrls_RpmSliders[i]->setEnabled(enabled);
    }
}

void gui_MainWindow::updateSpeedControlTooltip(int channel)
{
    Q_ASSERT(channel >= 0 && channel <= 4); // pre-condition

    QString tooltip;

    tooltip += tr("Min Temp: ");
    tooltip += fcdata().temperatureString(
                   fcdata().minTemp(channel),
                   true);

    tooltip += "\n";
    tooltip += tr("Max Temp: ");
    tooltip += fcdata().temperatureString(
                   fcdata().maxTemp(channel),
                   true);

    tooltip += "\n";
    tooltip += tr("Min logged RPM: ");
    tooltip += QString::number(fcdata().minLoggedRPM(channel));

    tooltip += "\n";
    tooltip += tr("Max logged RPM: ");
    tooltip += QString::number(fcdata().maxLoggedRPM(channel));

    m_ctrls_RpmSliders[channel]->setToolTip(tooltip);
}


void gui_MainWindow::updateSpeedControlTooltips(void)
{
    for (int i = 0; i < FC_MAX_CHANNELS; i++)
    {
        updateSpeedControlTooltip(i);
    }
}

int gui_MainWindow::maxRPM(int channel) const
{
    int mrpm;

    mrpm = ph_fanControllerData().maxRPM(channel);
    return mrpm < 0 ? 0 : mrpm;
}

void gui_MainWindow::updateSpeedControl(int channel, int RPM, bool updateSlider)
{
    Q_ASSERT(channel >= 0 && channel <= 4); // pre-condition

    const FanChannelData& fcs = fcdata().fanChannelSettings(channel);


    QString RpmText;
    RpmText = RPM == 0 ? "OFF" : QString::number(RPM);
    m_ctrls_currentRPM[channel]->setText(RpmText);

    if (updateSlider)
    {
        int newRPM;
        if (!fcdata().isAuto() && fcs.isSet_manualRPM())
        {
            newRPM = fcs.manualRPM();
        }
        else
        {
            newRPM = RPM;
        }

        // Avoid potential division by 0
        int ch_maxRPM = maxRPM(channel);
        if (ch_maxRPM < 1) ch_maxRPM = 1;

        bool sb = m_ctrls_RpmSliders[channel]->blockSignals(true);
        m_ctrls_RpmSliders[channel]->setValue(ceil(newRPM*100.0/ch_maxRPM));
        m_ctrls_RpmSliders[channel]->blockSignals(sb);
    }
}

void gui_MainWindow::updateCurrentTempControl(int channel, int temp)
{
    m_ctrls_probeTemps[channel]->setText(
        fcdata().temperatureString(temp, true)
    );
}

void gui_MainWindow::updateAllCurrentTempControls(void)
{
    for (int i = 0; i < FC_MAX_CHANNELS; i++)
    {
        updateCurrentTempControl(i, fcdata().lastTemp(i));
    }
}


void gui_MainWindow::updateAlarmTempControl(int channel, int temp, bool isCelcius)
{
    Q_ASSERT(channel >= 0 && channel <= 4); // pre-condition

    (void)isCelcius; // Unused

    m_ctrls_alarmTemps[channel]->setText(
        fcdata().temperatureString(temp, true)
    );

}

void gui_MainWindow::updateAllAlarmCtrls(bool isCelcius)
{
    for (int i = 0; i < FC_MAX_CHANNELS; i++)
    {
        updateAlarmTempControl(i, fcdata().alarmTemp(i), isCelcius);
    }
}

void gui_MainWindow::updateAllSpeedCtrls(void)
{
    for (int i = 0; i < FC_MAX_CHANNELS; i++)
    {
        updateSpeedControl(i, fcdata().lastRPM(i));
    }
}

void gui_MainWindow::updateRpmIndicator(int channel)
{
    QString style;

    if (fcdata().isAuto())
    {
        style = "background-image: url(:/Images/bar_green.png);margin:0px;";
        m_ctrls_rpmIndicator[channel]->setToolTip(tr("Auto"));
    }
    else
    {
        if (fcdata().isManualRpmSet(channel)
                && fcdata().lastRPM(channel) != fcdata().manualRPM(channel)
                && fcdata().manualRPM(channel) != 0)
        {
            style = "background-image: url(:/Images/bar_yellow.png);margin:0px;";
                    }
        else
        {
            style = "background-image: url(:/Images/bar_green.png);margin:0px;";

        }
        m_ctrls_rpmIndicator[channel]->setToolTip(QString(tr("Manual RPM = %1"))
                                                  .arg(fcdata().manualRPM(channel))
                                                  );
    }

    m_ctrls_rpmIndicator[channel]->setStyleSheet(style);


}

void gui_MainWindow::updateRpmIndicators(void)
{
    for (int i = 0; i < FC_MAX_CHANNELS; i++)
    {
        updateRpmIndicator(i);
    }
}

void gui_MainWindow::updateToggleControls(void)
{
    ui->ctrl_tempScaleToggleBtn->setChecked(fcdata().isCelcius() ? 1 : 0);
    ui->ctrl_isAudibleAlarmBtn->setChecked(fcdata().isAudibleAlarm() ? 0 : 1);

    if (fcdata().isSoftwareAuto())
    {
        ui->ctrl_isManualBtn->setEnabled(false);
        ui->ctrl_isSoftwareControlBtn->setChecked(true);
    }
    else
    {
        ui->ctrl_isManualBtn->setEnabled(true);
        ui->ctrl_isManualBtn->setChecked(fcdata().isAuto() ? 0 : 1);
        ui->ctrl_isSoftwareControlBtn->setChecked(false);
    }
}


void gui_MainWindow::changeEvent(QEvent* e)
{
    switch (e->type())
    {
    case QEvent::WindowStateChange:
        if (this->windowState() & Qt::WindowMinimized)
        {
            if (QSystemTrayIcon::isSystemTrayAvailable())
            {
                QTimer::singleShot(0, this, SLOT(hide()));
                m_trayIcon.show();
            }
        }

        break;

    default:
        break;
    }

    QMainWindow::changeEvent(e);
}


void gui_MainWindow::onTrayIconActivated(QSystemTrayIcon::ActivationReason reason)
{
    (void)reason; //Unused

    m_trayIcon.hide();
    this->showNormal();
    this->raise();
    this->activateWindow();
}

/* ------------------------------------------------------------------------
   Slots for common settings
   ----------------------------------------------------------------------*/

void gui_MainWindow::onTemperatureScaleChanged(bool isCelcius)
{
    bool bs = ui->ctrl_tempScaleToggleBtn->blockSignals(true);
    ui->ctrl_tempScaleToggleBtn->setChecked(isCelcius ? 1 : 0);
    ui->ctrl_tempScaleToggleBtn->blockSignals(bs);
}

void gui_MainWindow::onControlModeChanged(bool isAuto)
{
    bool bs = ui->ctrl_isManualBtn->blockSignals(true);
    ui->ctrl_isManualBtn->setChecked(isAuto ? 0 : 1);
    ui->ctrl_isManualBtn->blockSignals(bs);
    enableSpeedControls(!(isAuto || fcdata().isSoftwareAuto()));
    updateRpmIndicators();
}

void gui_MainWindow::onIsAudibleAlarmChanged(bool isAudibleAlarm)
{
    bool bs = ui->ctrl_isAudibleAlarmBtn->blockSignals(true);
    ui->ctrl_isAudibleAlarmBtn->setChecked(isAudibleAlarm ? 0 : 1);
    bs = ui->ctrl_isAudibleAlarmBtn->blockSignals(bs);
}

/* ------------------------------------------------------------------------
   Channel related slots
   ----------------------------------------------------------------------*/

void gui_MainWindow::onCurrentRPM(int channel, int RPM)
{
    Q_ASSERT(channel >= 0 && channel <= 4); // pre-condition

    updateSpeedControl(channel, RPM, fcdata().isAuto());
    updateRpmIndicator(channel);
}

void gui_MainWindow::onManualRPMChanged(int channel, int RPM)
{
    if (!fcdata().isAuto())
    {
        updateSpeedControl(channel, RPM, true);
        updateRpmIndicator(channel);
    }
}

void gui_MainWindow::onCurrentTemp(int channel, int tempInF)
{
    Q_ASSERT(channel >= 0 && channel <= 4); // pre-condition

    updateCurrentTempControl(channel, tempInF);
}

void gui_MainWindow::onCurrentAlarmTemp(int channel, int tempInF)
{
    Q_ASSERT(channel >= 0 && channel <= 4); // pre-condition

    updateAlarmTempControl(channel, tempInF, fcdata().isCelcius());
}

void gui_MainWindow::onMaxRPM(int channel, int RPM)
{
    (void)RPM; // Unused

    Q_ASSERT(channel >= 0 && channel <= 4); // pre-condition

    updateSpeedControl(channel, fcdata().lastRPM(channel));
}


/* ------------------------------------------------------------------------
   Logging related slots
   ----------------------------------------------------------------------*/

void gui_MainWindow::onMinLoggedRpmChanged(int channel, int rpm)
{
    (void)rpm;  // Unused
    updateSpeedControlTooltip(channel);
}

void gui_MainWindow::onMaxLoggedRpmChanged(int channel, int rpm)
{
    (void)rpm;  // Unused
    updateSpeedControlTooltip(channel);
}

void gui_MainWindow::onMinLoggedTempChanged (int channel, int temperature)
{
    (void)temperature;  // Unused
    updateSpeedControlTooltip(channel);
}

void gui_MainWindow::onMaxLoggedTempChanged (int channel, int temperature)
{
    (void)temperature;  // Unused
    updateSpeedControlTooltip(channel);
}


/* ------------------------------------------------------------------------
   GUI slots
   ----------------------------------------------------------------------*/

//    FIXME:  removed after adding icons instead of toggles
//void gui_MainWindow::on_ctrl_isManual_valueChanged(int value)
//{
////    FanControllerIO* fc = &ph_fanControllerIO();
////    bool isAuto = value == 0 ? true : false;

////    fcdata().updateIsAuto(isAuto, false);

////    fc->setDeviceFlags(fcdata().isCelcius(),
////                       isAuto,
////                       fcdata().isAudibleAlarm()
////                      );

////    enableSpeedControls(!isAuto);
////    updateAllSpeedCtrls();
////    updateRpmIndicators();
//}

//void gui_MainWindow::on_ctrl_isAudibleAlarm_valueChanged(int value)
//{
////    FanControllerIO* fc = &ph_fanControllerIO();
////    bool isAudible = value == 1 ? true : false;

////    fcdata().updateIsAudibleAlarm(isAudible, false);

////    fc->setDeviceFlags(fcdata().isCelcius(),
////                       fcdata().isAuto(),
////                       isAudible
////                      );
//}

//void gui_MainWindow::on_ctrl_tempScaleToggle_valueChanged(int value)
//{
////    FanControllerIO* fc = &ph_fanControllerIO();
////    bool isC = value == 1 ? true : false;

////    fcdata().updateIsCelcius(isC, false);

////    fc->setDeviceFlags(isC,
////                       fcdata().isAuto(),
////                       fcdata().isAudibleAlarm()
////                      );

////    updateAllAlarmCtrls(isC);
////    updateAllCurrentTempControls();
//}


void gui_MainWindow::userPressedChannelRpmSlider(int channel)
{
    (void)channel; // Unused
    FanControllerIO* fc = &ph_fanControllerIO();
    fc->blockSignals(true);
}

void gui_MainWindow::userReleasedChannelRpmSlider(int channel)
{

    FanControllerIO* fc = &ph_fanControllerIO();
    fc->blockSignals(false);
    int val = rpmSliderValueToRPM(channel, m_ctrls_RpmSliders[channel]->value());
    // TODO: this should probably be last manual setting
    if (val != fcdata().lastRPM(channel) || val == 0)
    {
        fcdata().updateManualRPM(channel, val, false);
        fc->setChannelSettings(channel, fcdata().alarmTemp(channel), val);
        updateSpeedControl(channel, val, true);
    }
}

void gui_MainWindow::userChangedChannelRpmSlider(int channel, int value)
{
    int val = rpmSliderValueToRPM(channel, value);
    m_ctrls_currentRPM[channel]->setText(QString::number((int)val));
    // TODO: this should probably be last manual setting
    if ( !m_ctrls_RpmSliders[channel]->isSliderDown()
            && (val != fcdata().lastRPM(channel) || val == 0))
    {
        fcdata().updateManualRPM(channel, val, false);
        FanControllerIO* fc = &ph_fanControllerIO();
        fc->setChannelSettings(channel, fcdata().alarmTemp(channel), val);
        updateSpeedControl(channel, val, true);
    }
}

int gui_MainWindow::rpmSliderValueToRPM(int channel, int value) const
{
    int channelMaxRPM = maxRPM(channel);
    int channelMinRPM = floor(channelMaxRPM * 0.50 / 100) * 100;

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

    currentAlarmTemp = fcdata().alarmTemp(channel);
    if (fcdata().isCelcius())
    {
        currentAlarmTemp = FanControllerData::toCelcius(currentAlarmTemp);
    }
    FanControllerIO* fc = &ph_fanControllerIO();
    int minProbeTemp = fc->minProbeTemp(fcdata().isCelcius());
    int maxProbTemp = fc->maxProbeTemp(fcdata().isCelcius());

    QString prompt = QString(tr("Enter new alarm temperature %1"
                                " for channel %2.\nRange is %3 to %4"))
                     .arg(fcdata().isCelcius() ? "C" : "F")
                     .arg(channel + 1)
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
    if (fcdata().isCelcius())
    {
        userTemperature = FanControllerData::toFahrenheit(userTemperature);
    }

    if (userTemperature != currentAlarmTemp)
    {

        fcdata().updateAlarmTemp(channel, userTemperature, false);

        int RpmToSet;

        RpmToSet = fcdata().isAuto()
                        ? fcdata().lastRPM(channel)
                        : fcdata().manualRPM(channel);

        fc->setChannelSettings(channel, userTemperature, RpmToSet);
        updateAlarmTempControl(channel, userTemperature, fcdata().isCelcius());
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
    gui_About aboutDlg(this);
    aboutDlg.exec();
}

void gui_MainWindow::on_actionPreferences_triggered()
{
    gui_Preferences preferencesDlg(this);
    preferencesDlg.exec();
}

void gui_MainWindow::on_actionSQL_Query_triggered()
{
    gui_SimpleSqlQry* sqlQryDlg = new gui_SimpleSqlQry(this);
    sqlQryDlg->setAttribute(Qt::WA_DeleteOnClose);
    sqlQryDlg->setWindowModality(Qt::NonModal);
    sqlQryDlg->show();
    sqlQryDlg->raise();
    sqlQryDlg->activateWindow();
}

//    FIXME:  removed after moving this function to profiles form
//bool gui_MainWindow::loadProfile(void)
//{
//    /*FanControllerProfile fcp;
//    QString m_profileName = ui->ctrl_PresetName->currentText();
//    if (m_profileName.isEmpty()) return false;

//    bool success = false;

//    if (fcp.load(m_profileName))
//    {
//        FanControllerIO* fc = &ph_fanControllerIO();

//        if (fc->setFromProfile(fcp))
//        {
//            fcdata().syncWithProfile(fcp);
//            updateSpeedControlTooltips();
//            updateAllSpeedCtrls();
//            updateAllAlarmCtrls(fcdata().isCelcius());
//            updateToggleControls();
//            enableSpeedControls(!fcp.isAuto());

//            success = true;
//        }
//    }

//    return success;*/
//}

//void gui_MainWindow::on_ctrl_configSoftwareAuto_clicked()
//{
////    gui_SoftwareAutoSetup* dlg = new gui_SoftwareAutoSetup(this);

////    fcdata().initAllRamps();

////    dlg->init(&fcdata());

////    dlg->exec();

////    if (!fcdata().isSoftwareAuto())
////    {
////        m_softwareAuto.switchOn(ph_fanControllerIO(), fcdata());
////    }
//}

//void gui_MainWindow::on_ctrl_PresetName_currentIndexChanged(int index)
//{
//    (void)index;    //unused
//    loadProfile();

//}

void gui_MainWindow::on_ctrl_ModifyProfile_clicked()
{
    int idx = ui->ctrl_PresetName->currentIndex();

    gui_Profiles* profileDlg = new gui_Profiles(this);

    profileDlg->exec();

    //QString m_profileName = profileDlg->selectedName();
    //QString m_profileDescription = profileDlg->selectedDescription();

    populate_ctrl_PresetName();

    ui->ctrl_PresetName->setCurrentIndex(idx);

    // Need to update controls in case a new profile was loaded
    syncGuiCtrlsWithFanController();

}

void gui_MainWindow::on_ctrl_tempScaleToggleBtn_toggled(bool checked)
{
    FanControllerIO* fc = &ph_fanControllerIO();
    bool isC = checked == 1 ? true : false;

    fcdata().updateIsCelcius(isC, false);

    fc->setDeviceFlags(isC,
                       fcdata().isAuto(),
                       fcdata().isAudibleAlarm()
                      );

    updateAllAlarmCtrls(isC);
    updateAllCurrentTempControls();
}

void gui_MainWindow::on_ctrl_isManualBtn_toggled(bool checked)
{
    FanControllerIO* fc = &ph_fanControllerIO();
    bool isAuto = checked == 0 ? true : false;

    fcdata().updateIsAuto(isAuto, false);

    fc->setDeviceFlags(fcdata().isCelcius(),
                       isAuto,
                       fcdata().isAudibleAlarm()
                      );

    enableSpeedControls(!isAuto);
    updateAllSpeedCtrls();
    updateRpmIndicators();
}

void gui_MainWindow::on_ctrl_isAudibleAlarmBtn_toggled(bool checked)
{
    FanControllerIO* fc = &ph_fanControllerIO();
    bool isAudible = checked ? false : true;

    fcdata().updateIsAudibleAlarm(isAudible, false);

    fc->setDeviceFlags(fcdata().isCelcius(),
                       fcdata().isAuto(),
                       isAudible
                      );
}

void gui_MainWindow::on_ctrl_configSoftwareAutoBtn_clicked()
{
    gui_SoftwareAutoSetup dlg(this);

    dlg.init(&fcdata());

    dlg.exec();
}

void gui_MainWindow::on_ctrl_isSoftwareControlBtn_toggled(bool checked)
{
    setSoftwareAutoOn(checked);
    enableSpeedControls(!(fcdata().isAuto() || fcdata().isSoftwareAuto()));
    updateRpmIndicators();
}

