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

#ifndef GUI_MAINWINDOW_H
#define GUI_MAINWINDOW_H

#include <QMainWindow>
#include <QLineEdit>
#include <QLabel>
#include <QSlider>
#include <QPushButton>
#include <QLayout>
#include <QSystemTrayIcon>
#include "fancontrollerdata.h"

class sliderOverlay : public QSlider
{
public:
     explicit sliderOverlay(QSlider *parent = 0);
};

namespace Ui
{
class gui_MainWindow;
}

class gui_MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit gui_MainWindow(QWidget *parent = 0);
    ~gui_MainWindow();

    void syncGuiCtrlsWithFanController(void);
    void setSoftwareAutoOn(bool yes = true);

protected:

public slots:

    void changeEvent(QEvent* e);
    void onTrayIconActivated(QSystemTrayIcon::ActivationReason reason);

    // **** Slots for common settings
    void onControlModeChanged(bool isAuto);
    void onIsAudibleAlarmChanged(bool isAudibleAlarm);
    void onMaxRPM(int channel, int RPM);

    // **** Channel related slots
    void onCurrentRPM(int channel, int RPM);
    void onManualRPMChanged(int channel, int RPM);
    void onCurrentTemp(int channel, int tempInF);
    void onCurrentAlarmTemp(int channel, int tempInF);
    void onTemperatureScaleChanged(bool isCelcius);

    // **** Logging related slots
    void onMinLoggedRpmChanged(int channel, int rpm);
    void onMaxLoggedRpmChanged(int channel, int rpm);
    void onMinLoggedTempChanged (int channel, int temperature);
    void onMaxLoggedTempChanged (int channel, int temperature);

private slots:

    void checkForReqChannelParems(void);

    void on_ctrl_channel1speedSlider_sliderPressed();
    void on_ctrl_channel1speedSlider_sliderReleased();
    void on_ctrl_channel1speedSlider_valueChanged(int value);

    void on_ctrl_channel2speedSlider_sliderPressed();
    void on_ctrl_channel2speedSlider_sliderReleased();
    void on_ctrl_channel2speedSlider_valueChanged(int value);

    void on_ctrl_channel3speedSlider_sliderPressed();
    void on_ctrl_channel3speedSlider_sliderReleased();
    void on_ctrl_channel3speedSlider_valueChanged(int value);

    void on_ctrl_channel4speedSlider_sliderPressed();
    void on_ctrl_channel4speedSlider_sliderReleased();
    void on_ctrl_channel4speedSlider_valueChanged(int value);

    void on_ctrl_channel5speedSlider_sliderPressed();
    void on_ctrl_channel5speedSlider_sliderReleased();
    void on_ctrl_channel5speedSlider_valueChanged(int value);

    void on_ctrl_channel1AlarmTemp_clicked();
    void on_ctrl_channel2AlarmTemp_clicked();
    void on_ctrl_channel3AlarmTemp_clicked();
    void on_ctrl_channel4AlarmTemp_clicked();
    void on_ctrl_channel5AlarmTemp_clicked();

    void on_actionAbout_triggered();
    void on_actionPreferences_triggered();

    void on_ctrl_ModifyProfile_clicked();

    void on_ctrl_tempScaleToggleBtn_toggled(bool checked);

    void on_ctrl_isManualBtn_toggled(bool checked);

    void on_ctrl_isAudibleAlarmBtn_toggled(bool checked);

    void on_ctrl_configSoftwareAutoBtn_clicked();

    void on_ctrl_isSoftwareControlBtn_toggled(bool checked);

    void askUserForManualSpeed(int channel);

    void on_ctrl_channel1Select_clicked();

    void on_ctrl_channel2Select_clicked();

    void on_ctrl_channel3Select_clicked();

    void on_ctrl_channel4Select_clicked();

    void on_ctrl_channel5Select_clicked();

    void on_ctrl_channel1speed_clicked();

    void on_ctrl_channel2speed_clicked();

    void on_ctrl_channel3speed_clicked();

    void on_ctrl_channel4speed_clicked();

    void on_ctrl_channel5speed_clicked();

    void on_pushButton_clicked();

    void on_ctrl_syncGui_clicked();

private:

    void initCtrlArrays(void);

    void initWaitForReqChannelParams(void);

    bool customAutoAvailable(void) const;

    FanControllerData& fcdata(void) const;

    void connectCustomSignals(void);

    void enableSpeedControls(bool enabled = true);

    void updateSpeedControlTooltip(int channel);
    void updateSpeedControlTooltips(void);

    int maxRPM(int channel) const;
    void updateSpeedControl(int channel, int RPM, bool updateSlider = true);
    void updateAllSpeedCtrls(bool useManualRpm = false);

    void updateRpmIndicator(int channel);

    void updateToggleControls(void);

    void updateCurrentTempControl(int channel, int temp);
    void updateAllCurrentTempControls(void);
    void updateAlarmTempControl(int channel, int temp, bool isCelcius);
    void updateAllAlarmCtrls(bool isCelcius);

    int rpmSliderValueToRPM(int channel, int value) const;

    void userPressedChannelRpmSlider(int channel);
    void userReleasedChannelRpmSlider(int channel);
    void userChangedChannelRpmSlider(int channel, int value);

    void userClickedAlarmTempCtrl(int channel);

    bool loadProfile(const QString& profileName);
    bool saveProfile(const QString& profileName, const QString& description);

    void updateProfileDisplay(const QString& profileName,
                              const QString& description);

    Ui::gui_MainWindow *ui;

    // Convenience pointers to controls
    QLineEdit* m_ctrls_probeTemps[FC_MAX_CHANNELS];
    QPushButton* m_ctrls_currentRPM[FC_MAX_CHANNELS];
    QSlider* m_ctrls_RpmSliders[FC_MAX_CHANNELS];
    sliderOverlay* m_ctrls_rpmIndicator[FC_MAX_CHANNELS];
    QGridLayout* m_layout_rpmIndicator[FC_MAX_CHANNELS];
    QPushButton* m_ctrls_alarmTemps[FC_MAX_CHANNELS];

    QSystemTrayIcon m_trayIcon;

    bool m_reqChannelParamsAreSet;

    void initTargetRpmIndicators();

};

#endif // GUI_MAINWINDOW_H
