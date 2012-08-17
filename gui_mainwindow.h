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
#include <QSlider>
#include "profiles.h"
#include "fanchanneldata.h"

namespace Ui {
class gui_MainWindow;
}

class gui_MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit gui_MainWindow(QWidget *parent = 0);
    ~gui_MainWindow();

public slots:
    void onCurrentRPM(int channel, int RPM);
    void onCurrentTemp(int channel, int tempInF);
    void onCurrentAlarmTemp(int channel, int tempInF);
    void onDeviceSettings(bool isCelcius, bool isAuto, bool isAudibleAlarm);
    void onMaxRPM(int channel, int RPM);

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
private:
    void initCtrlArrays(void);
    void connectCustomSignals(void);

    void enableDisableSpeedControls(void);

    void updateSpeedControlTooltip(int channel);
    void updateSpeedControlTooltips(void);

    void updateSpeedControl(int channel, int RPM);
    void updateAllSpeedCtrls(void);
    void updateAlarmTempControl(int channel);
    void updateAllAlarmCtrls(void);

    int rpmSliderValueToRPM(int channel, int value) const;

    void setFcChannelSpeed(int channel, int RPM);

    void userPressedChannelRpmSlider(int channel);
    void userReleasedChannelRpmSlider(int channel);
    void userChangedChannelRpmSlider(int channel, int value);

    Ui::gui_MainWindow *ui;

    // Convenience pointers to controls
    QLineEdit* m_ctrls_probeTemps[FC_MAX_CHANNELS];
    QLineEdit* m_ctrls_currentRPM[FC_MAX_CHANNELS];
    QSlider* m_ctrls_RpmSliders[FC_MAX_CHANNELS];
    QLineEdit* m_ctrls_alarmTemps[FC_MAX_CHANNELS];

#if 0
    // Common data
    bool m_isCelcius;
    bool m_isAuto;
    bool m_isAudibleAlarm;

    // Channel sepecific data
    FanChannelData m_channelData[FC_MAX_CHANNELS];
#endif

    FanControllerProfile m_fp;  // fp == fan profile

    // Blocking flags
    bool m_isAutoToggleByDevice;
    bool m_isCelciusToggleByDevice;
    bool m_isAudibleAlarmByDevice;

    bool m_speedSliderMovedByDevice[FC_MAX_CHANNELS];


    /* **** DEBUGGING MENU ***/
#ifdef QT_DEBUG

    QMenu* m_debugMenu;
    QAction* m_debug_setChannelSpeed;

private slots:

    void onDebugMenu_setChannelSpeed();

#endif
    /* **** END DEBUGGING MENU ***/

};

#endif // GUI_MAINWINDOW_H
