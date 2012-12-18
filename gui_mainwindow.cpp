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
#include "gui_softwareautosetup.h"
#include "gui_profiles.h"
#include "gui_setmanualrpm.h"
#include "maindb.h"

static const char* style_sliderOverylay_blue =
            "SliderOverlay::groove:vertical { border: 0px transparant; width: 0px; }"
            "SliderOverlay::handle:vertical {"
            "background-color: qlineargradient(spread:pad, x0:1, y2:1, x0:1, y2:1, stop:0 #02C, stop:1 #999);"
            "border: 1px solid #777; height: 5px; margin: -8px; margin-top: 1px; margin-bottom: 1px; border-radius: 2px;}"
            "SliderOverlay::add-page:vertical { border: 0px transparant; }"
            "SliderOverlay::sub-page:vertical { border: 0px transparant; }";

static const char* style_sliderOverylay_yellow =
            "SliderOverlay::groove:vertical { border: 0px transparant; width: 0px; }"
            "SliderOverlay::handle:vertical {"
            "background-color: qlineargradient(spread:pad, x0:1, y2:1, x0:1, y2:1, stop:0 #FF0, stop:1 #999);"
            "border: 1px solid #777; height: 5px; margin: -8px; margin-top: 1px; margin-bottom: 1px; border-radius: 2px;}"
            "SliderOverlay::add-page:vertical { border: 0px transparant; }"
            "SliderOverlay::sub-page:vertical { border: 0px transparant; }";

const double gui_MainWindow::toLogScale       = log(101) / 100;
const double gui_MainWindow::toLinearScale    = (log(101) - log(1)) / 100;

gui_MainWindow::gui_MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::gui_MainWindow)
{
    ui->setupUi(this);
    initCtrlArrays();

    //qApp->installEventFilter(this); // FIXME: URGENT: We're not using qApp (using PhoebetriaApp)

#if defined Q_WS_WIN
    m_trayIcon.setIcon(QIcon(":/Images/icons/16x16/phoebetria.png"));
#elif defined Q_WS_MAC
    m_trayIcon.setIcon(QIcon(":/Images/icons/22x22/phoebetria.png"));
#elif defined Q_WS_X11
    m_trayIcon.setIcon(QIcon(":/Images/icons/22x22/phoebetria.png");
#else
    m_trayIcon.setIcon(QIcon(":/Images/icons/16x16/phoebetria.png"));
#endif

#ifndef QT_DEBUG
    ui->pushButton->hide();
    ui->ctrl_syncGui->hide();
#endif

    initTrayIconMenu();

    if (ph_prefs().startMinimized())
    {
        this->setWindowState(Qt::WindowMinimized);
    }

    m_trayIcon.setToolTip("Phoebetria");
    connect(&m_trayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
            this, SLOT(onTrayIconActivated(QSystemTrayIcon::ActivationReason)));

    setWindowIcon(QIcon(":/icon16x16"));

    // Synchronise fan controller data with GUI.

    FanControllerIO* fc = &ph_fanControllerIO();

    if (fc->isConnected() == false)
    {
        ui->ctrl_logoAndStatus->setStyleSheet("background-image: url(:/Images/icons/128x128/phoebetria_red.png);");

    }

    connectCustomSignals();

    initWaitForReqChannelParams();

    initTargetRpmOverlays();
    initProbeAffinityOverlays();

    updateChannelControlTooltips();



    if (!MainDb::isValid())
    {
        QMessageBox::critical(
                    this,
                    tr("Profile database error."),
                    tr("The profile database could not be initialised"
                       " or another error has occurred. Profile management"
                       " will not work!")
                    );
        this->ui->ctrl_ModifyProfile->setEnabled(false);
    }


}



void gui_MainWindow::syncGuiCtrlsWithFanController(void)
{
    FanControllerData& fcd = fcdata();

    updateSpeedControlTooltips();
    updateAllSpeedCtrls(!fcdata().isAuto());
    updateAllAlarmCtrls(fcd.isCelcius());
    updateToggleControls();
    updateProbeAffinityOverlays();
    enableSpeedControls(!(fcdata().isAuto() || fcdata().isSoftwareAuto()));

}


void gui_MainWindow::setSoftwareAutoOn(bool yes)
{
    FanControllerData& fcd = fcdata();

    fcd.updateIsSwAuto(yes);

    updateToggleControls();
    updateAllSpeedCtrls();
}

void gui_MainWindow::initWaitForReqChannelParams(void)
{
    m_reqChannelParamsAreSet = false;

    EventDispatcher& ed = ph_phoebetriaApp()->dispatcher();

    ui->ctrl_configSoftwareAutoBtn->setEnabled(false);
    ui->ctrl_isSoftwareControlBtn->setEnabled(false);

    connect(&ed, SIGNAL(tick()),
            this, SLOT(checkForReqChannelParems()));

    checkForReqChannelParems();
}

void gui_MainWindow::initTrayIconMenu(void)
{
    m_trayIconMenu.addAction("test1");
    m_trayIconMenu.addAction("test2");

    m_trayIcon.setContextMenu(&m_trayIconMenu);
}

void gui_MainWindow::checkForReqChannelParems(void)
{

    if (!ph_fanControllerIO().isConnected())
        return;

    if (fcdata().ramp_reqParamsForInitAreSet() && !m_reqChannelParamsAreSet)
    {
        m_reqChannelParamsAreSet = true;
        ui->ctrl_configSoftwareAutoBtn->setEnabled(true);
        ui->ctrl_isSoftwareControlBtn->setEnabled(true);

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

    for (int i = 0; i < FC_MAX_CHANNELS; ++i)
    {
        delete m_ctrls_targetRpmOverlay[i];
    }
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

    m_ctrls_channel[0] = ui->ctrl_channel1Select;
    m_ctrls_channel[1] = ui->ctrl_channel2Select;
    m_ctrls_channel[2] = ui->ctrl_channel3Select;
    m_ctrls_channel[3] = ui->ctrl_channel4Select;
    m_ctrls_channel[4] = ui->ctrl_channel5Select;
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

void gui_MainWindow::enableSpeedControls(bool enabled)
{
    for (int i = 0; i < FC_MAX_CHANNELS; i++)
    {
        m_ctrls_RpmSliders[i]->setEnabled(enabled);
        m_ctrls_currentRPM[i]->setEnabled(enabled);
    }
}

void gui_MainWindow::updateSpeedControlTooltip(int channel)
{
    Q_ASSERT(channel >= 0 && channel <= 4); // pre-condition

    QString tooltip;

    tooltip += tr("Current RPM: ");
    tooltip += QString::number(fcdata().lastRPM(channel));
    tooltip += "\n";

    tooltip += tr("Target RPM: ");
    QString targetRpmStr;
    tooltip += *fcdata().targetRpmString(channel, &targetRpmStr);
    tooltip += "\n";

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

void gui_MainWindow::updateChannelControlTooltip(int channel)
{
    QString tt;

    tt = ph_prefs().channelName(channel);
    if (tt.isEmpty())
    {
        tt = "Channel ";
        tt += QString::number(channel+1);
    }
    m_ctrls_channel[channel]->setToolTip(tt);
}

void gui_MainWindow::updateChannelControlTooltips(void)
{
    for (int i = 0; i < FC_MAX_CHANNELS; ++i)
    {
        updateChannelControlTooltip(i);
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

    if (RPM == -1)
        return;

    QString RpmText;
    RpmText = RPM == 0 ? "OFF" : (RPM == RECON_MAXRPM ? QString::number(fcdata().lastRPM(channel)) :
                                                 QString::number(RPM));
    m_ctrls_currentRPM[channel]->setText(RpmText);

    if (updateSlider || RPM == RECON_MAXRPM)
    {
        int newRPM;
        if (!fcdata().isAuto()
                && fcs.isSet_manualRPM()
                && fcs.manualRPM() != RECON_MAXRPM)
        {
            newRPM = fcs.manualRPM();
        }
        else
        {
            newRPM = RPM;
        }

        int newValue = fcdata().rpmToPercentage(channel, newRPM);

        if (ph_prefs().useLogScaleRpmSliders())
            newValue = valueToLinearScale(newValue);

        bool sb = m_ctrls_RpmSliders[channel]->blockSignals(true);
        m_ctrls_RpmSliders[channel]->setValue(newValue);
        m_ctrls_RpmSliders[channel]->blockSignals(sb);

    }

    updateSpeedControlTooltip(channel);
    updateTargetRpmOverlay(channel);
}

void gui_MainWindow::updateCurrentTempControl(int channel, int temp)
{
    if (fcdata().isSoftwareAuto())
    {
        for (int i = 0; i < FC_MAX_CHANNELS; ++i)
        {
            if (fcdata().ramp(i).probeAffinity() == channel)
            {
                m_ctrls_probeTemps[i]->setText(
                            fcdata().temperatureString(temp, true));
            }
        }
    }
    else
    {
        m_ctrls_probeTemps[channel]->setText(
            fcdata().temperatureString(temp, true));
    }
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

void gui_MainWindow::updateAllSpeedCtrls(bool useManualRpm)
{
    for (int i = 0; i < FC_MAX_CHANNELS; i++)
    {
        int rpm = useManualRpm ? fcdata().manualRPM(i) : fcdata().lastRPM(i);
        updateSpeedControl(i, rpm);
    }
}

void gui_MainWindow::updateTargetRpmOverlay(int channel)
{
    int sliderPosition;

    const char *style;

    sliderPosition = fcdata().rpmToPercentage(channel, fcdata().lastRPM(channel));

    if (ph_prefs().useLogScaleRpmSliders())
        sliderPosition = valueToLinearScale(sliderPosition);

    if (fcdata().isAuto())
    {
        /* Change RPM slider overlays to blue when in hardware auto mode */
        style = style_sliderOverylay_blue;
    }
    else
    {
        if (fcdata().isManualRpmSet(channel)
                && fcdata().lastRPM(channel) != fcdata().manualRPM(channel)
                && fcdata().manualRPM(channel) != RECON_MAXRPM)
        {
            /* Slider RPM != Target RPM */
            style = style_sliderOverylay_yellow;
        }
        else
        {
            /* Slider RPM == Target RPM */
            style = style_sliderOverylay_blue;
        }
    }

    m_ctrls_targetRpmOverlay[channel]->setStyleSheet(style);
    m_ctrls_targetRpmOverlay[channel]->setValue(sliderPosition);

}

void gui_MainWindow::updateProbeAffinityOverlays(void)
{
    if (fcdata().isSoftwareAuto())
    {
        for (int channel = 0; channel < FC_MAX_CHANNELS; ++channel)
        {
            for (int i = 0; i < FC_MAX_CHANNELS; ++i)
            {
                if (fcdata().ramp(i).probeAffinity() == channel)
                {
                    if (i != channel)
                        m_ctrls_probeAffinityOverlay[i]->setText(QString::number(channel+1));
                    else
                        m_ctrls_probeAffinityOverlay[i]->setText("");
                }
            }
        }
    }
    else
    {
        for (int channel = 0; channel < FC_MAX_CHANNELS; ++channel)
        {
            m_ctrls_probeAffinityOverlay[channel]->setText("");
        }
    }
}


void gui_MainWindow::updateToggleControls(void)
{
    bool bs;

    bs = ui->ctrl_tempScaleToggleBtn->blockSignals(true);
    ui->ctrl_tempScaleToggleBtn->setChecked(fcdata().isCelcius() ? 1 : 0);
    ui->ctrl_tempScaleToggleBtn->blockSignals(bs);

    bs = ui->ctrl_isAudibleAlarmBtn->blockSignals(true);
    ui->ctrl_isAudibleAlarmBtn->setChecked(fcdata().isAudibleAlarm() ? 0 : 1);
    ui->ctrl_isAudibleAlarmBtn->blockSignals(bs);

    if (fcdata().isSoftwareAuto())
    {
        bs = ui->ctrl_isManualBtn->blockSignals(true);
        ui->ctrl_isManualBtn->setEnabled(false);
        ui->ctrl_isManualBtn->blockSignals(bs);

        bs = ui->ctrl_isSoftwareControlBtn->blockSignals(true);
        ui->ctrl_isSoftwareControlBtn->setChecked(true);
        ui->ctrl_isSoftwareControlBtn->blockSignals(bs);
    }
    else
    {
        bs = ui->ctrl_isManualBtn->blockSignals(true);
        ui->ctrl_isManualBtn->setEnabled(true);
        ui->ctrl_isManualBtn->setChecked(fcdata().isAuto() ? 0 : 1);
        ui->ctrl_isManualBtn->blockSignals(bs);

        bs = ui->ctrl_isSoftwareControlBtn->blockSignals(true);
        ui->ctrl_isSoftwareControlBtn->setChecked(false);
        ui->ctrl_isSoftwareControlBtn->blockSignals(bs);
    }
}


void gui_MainWindow::changeEvent(QEvent* e)
{
    switch (e->type())
    {
    case QEvent::WindowStateChange:
        if (this->windowState() & Qt::WindowMinimized && ph_prefs().minimizeToTray())
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

// FIXME: URGENT: Has no effect?
bool gui_MainWindow::eventFilter(QObject *obj, QEvent *event)
{
    if(ph_prefs().showTrayIconTooltips() && !Qt::WindowMinimized)
    {
        if(event->type() == QEvent::ToolTip)
        {
            return true;
        }
        else
        {
            return QMainWindow::eventFilter(obj, event);
        }
    }
    else
    {
        return QMainWindow::eventFilter(obj, event);
    }
}

void gui_MainWindow::closeEvent(QCloseEvent *e)
{
    if (!ph_prefs().quitOnClose())
    {
            //FIXME: Implement user prefenece for minimize or hide.
            //hide();
            //FIXME: Having this set after first use, susequent uses minimizes, opens then minimizes again.  (OSX only?)
            showMinimized();
            e->ignore();
    }
    else
    {
            e->accept();
    }
}

void gui_MainWindow::onTrayIconActivated(QSystemTrayIcon::ActivationReason reason)
{
    if (reason == QSystemTrayIcon::Context)
    {
        // FIXME: Implement handling of context menu etc
    }
    else
    {
#ifndef WS_OS_X
        /* This causes a crash on OSX but is needed on Windows and KDE at least
           for "normal" operation. In Windows 7, if the tray icon is not hidden
           then it stays in the tray even after maximizing the application.
           Closing the application (with the close button) then still leaves
           the tray icon and Phoebetria still running. The main window can be
           re-opened by double clicking the tray icon. This is useful to know
           when we have preferences that change the behaviour (this may be
           related to closeEvent() as well).
          */
        m_trayIcon.hide();
#endif
        this->showNormal();
        this->raise();
        this->activateWindow();
    }
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
    updateToggleControls();
    updateProbeAffinityOverlays();
    enableSpeedControls(!(isAuto || fcdata().isSoftwareAuto()));    
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
}

void gui_MainWindow::onManualRPMChanged(int channel, int RPM)
{
    if (!fcdata().isAuto() || fcdata().isSoftwareAuto())
    {
        updateSpeedControl(channel, RPM, true);
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

    if (ph_prefs().useLogScaleRpmSliders())
        value = valueToLogScale(value);

    int rpm = fcdata().percentageToRpm(channel, value, RECON_RPM_STEPSIZE);

    return rpm < channelMinRPM ? 0 : rpm;
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
    updateChannelControlTooltips();
    updateAllSpeedCtrls();
}

void gui_MainWindow::on_ctrl_ModifyProfile_clicked()
{
    gui_Profiles* profileDlg = new gui_Profiles(this);

    profileDlg->exec();

    bool updatePD = false;

    if (profileDlg->action() & gui_Profiles::LoadProfile)
    {
        if (loadProfile(profileDlg->selectedName()))
        {
            fcdata().softReset();
            ph_resetSchedulerElapsedTime();
            initWaitForReqChannelParams();
            syncGuiCtrlsWithFanController();
            updatePD = true;
        }
    }
    else if (profileDlg->action() & gui_Profiles::SaveProfile)
    {
        if (!saveProfile(profileDlg->selectedName(),
                        profileDlg->selectedDescription()))
        {
            QMessageBox::critical(
                        this,
                        tr("Save failed"),
                        tr("An error occurred saving the profile.\n"
                           "The profile has NOT been saved!")
                        );
        }
        else
        {
            updatePD = true;
        }
    }
    else if (profileDlg->action() & gui_Profiles::RefreshProfileDisplay)
    {
        updatePD = true;
    }

    if (updatePD)
    {
        updateProfileDisplay(profileDlg->selectedName(),
                             profileDlg->selectedDescription());
    }
}

bool gui_MainWindow::loadProfile(const QString& profileName)
{
    FanControllerProfile fcp;
    bool r = fcp.load(profileName);

    if (r)
    {
        FanControllerIO* fc = &ph_fanControllerIO();

        if (fc->setFromProfile(fcp))
        {
            fcdata().syncWithProfile(fcp);
        }
        else
        {
            // TODO: Display error message

            r = false;
        }
    }

    return r;
}

bool gui_MainWindow::saveProfile(const QString& profileName,
                                 const QString& description)
{

    bool bs = fcdata().blockSignals(true);

    FanControllerProfile fcp(profileName, description);

    fcp.setFromCurrentData(fcdata());

    fcdata().blockSignals(bs);

    return fcp.save(profileName);
}

void gui_MainWindow::updateProfileDisplay(const QString& profileName,
                                          const QString& description)
{
    QString label;
    QString toolTip;

    label = "Profile: " + profileName;
    ui->lbl_activeProfile->setText(label);
    toolTip = label + "\n";
    toolTip += "Description: " + description;
    ui->lbl_activeProfile->setToolTip(toolTip);
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

    if (!isAuto)
    {
        fcdata().clearAllChannelRpmAndTemp();
        ph_resetSchedulerElapsedTime();
    }
    syncGuiCtrlsWithFanController();
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

    if (dlg.userAccepted())
    {
        fcdata().clearRampTemps();
        ph_resetSchedulerElapsedTime();
        syncGuiCtrlsWithFanController();
    }
}

void gui_MainWindow::on_ctrl_isSoftwareControlBtn_toggled(bool checked)
{
    setSoftwareAutoOn(checked);
    fcdata().clearRampTemps();
    ph_resetSchedulerElapsedTime();
    syncGuiCtrlsWithFanController();
}


void gui_MainWindow::on_ctrl_channel1Select_clicked()
{
    ph_fanControllerIO().setDisplayChannel(0);
}

void gui_MainWindow::on_ctrl_channel2Select_clicked()
{
    ph_fanControllerIO().setDisplayChannel(1);
}

void gui_MainWindow::on_ctrl_channel3Select_clicked()
{
    ph_fanControllerIO().setDisplayChannel(2);
}

void gui_MainWindow::on_ctrl_channel4Select_clicked()
{
    ph_fanControllerIO().setDisplayChannel(3);
}

void gui_MainWindow::on_ctrl_channel5Select_clicked()
{
    ph_fanControllerIO().setDisplayChannel(4);
}


void gui_MainWindow::askUserForManualSpeed(int channel)
{
    gui_setManualRpm dlg(this);

    dlg.setChannelLabel(channel);
    dlg.setCurrentRpm(fcdata().manualRPM(channel));

    dlg.exec();

    if (dlg.accepted())
    {
        int val;
        FanControllerIO* fc = &ph_fanControllerIO();

        if (dlg.useMaxRpm())
        {
            val = RECON_MAXRPM;
        }
        else
        {
            val = dlg.getUserValue();
        }
        fcdata().clearAllChannelRpmAndTemp();
        fcdata().updateManualRPM(channel, val, false);
        updateSpeedControl(channel, val, true);
        fc->setChannelSettings(channel, fcdata().alarmTemp(channel), val);

        ph_resetSchedulerElapsedTime();
        syncGuiCtrlsWithFanController();
    }
}

void gui_MainWindow::on_ctrl_channel1speed_clicked()
{
    askUserForManualSpeed(0);
}


void gui_MainWindow::on_ctrl_channel2speed_clicked()
{
    askUserForManualSpeed(1);
}

void gui_MainWindow::on_ctrl_channel3speed_clicked()
{
    askUserForManualSpeed(2);
}

void gui_MainWindow::on_ctrl_channel4speed_clicked()
{
    askUserForManualSpeed(3);
}

void gui_MainWindow::on_ctrl_channel5speed_clicked()
{
    askUserForManualSpeed(4);
}

void gui_MainWindow::on_pushButton_clicked()
{
    QMessageBox msg;

    msg.setText(QString("Max poll time (ms): %1\n"
                        "Max req queue size: %2")
                .arg(ph_fanControllerIO().maxPollDelta())
                .arg(ph_fanControllerIO().maxReqQueueSize())
                );
    msg.exec();
}

void gui_MainWindow::on_ctrl_syncGui_clicked()
{
    syncGuiCtrlsWithFanController();
}

void gui_MainWindow::initTargetRpmOverlays()
{

    /* initialize target RPM indicators overlayed with the current RPM sliders */
    for (int i = 0; i < FC_MAX_CHANNELS; i++)
    {
        m_ctrls_targetRpmOverlay[i] = new SliderOverlay();
        m_ctrls_targetRpmOverlay[i]->setStyleSheet(style_sliderOverylay_blue);

        m_layout_targetRpmOverlay[i] = new QGridLayout(m_ctrls_RpmSliders[i]);
        m_layout_targetRpmOverlay[i]->setContentsMargins(0,2,0,0);
        m_layout_targetRpmOverlay[i]->addWidget(m_ctrls_targetRpmOverlay[i]);
    }
}


void gui_MainWindow::initProbeAffinityOverlays()
{
    for (int i = 0; i < FC_MAX_CHANNELS; i++)
    {
        m_ctrls_probeAffinityOverlay[i] = new LabelOverlay();

        m_layout_probeAffinityOverlay[i] = new QHBoxLayout(m_ctrls_probeTemps[i]);
        m_layout_probeAffinityOverlay[i]->setContentsMargins(0,0,3,0);
        m_layout_probeAffinityOverlay[i]->addWidget(m_ctrls_probeAffinityOverlay[i]);
    }
}

SliderOverlay::SliderOverlay(QSlider *parent)
    : QSlider(parent)
{
    setPalette(Qt::transparent);
    setAttribute(Qt::WA_TransparentForMouseEvents);
}

LabelOverlay::LabelOverlay(QLabel *parent)
    : QLabel(parent)
{
    setAttribute(Qt::WA_TransparentForMouseEvents);
    QFont font = this->font();
    font.setPointSize(font.pointSize()-1);
    this->setFont(font);
    this->setAlignment(Qt::AlignRight | Qt::AlignTop);
}
