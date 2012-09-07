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
#include <QSystemTrayIcon>
#include "fancontrollerdata.h"

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

    void on_ctrl_isManual_valueChanged(int value);

    void on_ctrl_isAudibleAlarm_valueChanged(int value);

    void on_ctrl_tempScaleToggle_valueChanged(int value);

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

    void on_ctrl_SavePreset_clicked();

    void on_ctrl_LoadPreset_clicked();

private:
    void initCtrlArrays(void);

    FanControllerData& fcdata(void) const;

    void connectCustomSignals(void);

    void enableSpeedControls(bool enabled = true);

    void updateSpeedControlTooltip(int channel);
    void updateSpeedControlTooltips(void);

    int maxRPM(int channel) const;
    void updateSpeedControl(int channel, int RPM, bool updateSlider = true);
    void updateAllSpeedCtrls(void);

    void updateRpmIndicator(int channel);
    void updateRpmIndicators(void);

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

    Ui::gui_MainWindow *ui;

    // Convenience pointers to controls
    QLineEdit* m_ctrls_probeTemps[FC_MAX_CHANNELS];
    QLineEdit* m_ctrls_currentRPM[FC_MAX_CHANNELS];
    QLabel* m_ctrls_rpmIndicator[FC_MAX_CHANNELS];
    QSlider* m_ctrls_RpmSliders[FC_MAX_CHANNELS];
    QPushButton* m_ctrls_alarmTemps[FC_MAX_CHANNELS];

    QSystemTrayIcon m_trayIcon;

    /* **** DEBUGGING MENU ***/
#ifdef QT_DEBUG

    QMenu* m_debugMenu;
    QAction* m_debug_setChannelSpeed;
    QAction* m_debug_profiles;

private slots:

    void onDebugMenu_setChannelSpeed();
    void onDebugMenu_profiles();

#endif
    /* **** END DEBUGGING MENU ***/

};

#endif // GUI_MAINWINDOW_H
