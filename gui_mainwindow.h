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

#define FC_MAX_CHANNELS 5

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
    void onDeviceSettings(bool isCelcius, bool isAuto, bool isAudibleAlarm);
    void onMaxRPM(int channel, int RPM);
private slots:

    void on_ctrl_isManual_valueChanged(int value);

    void on_ctrl_isAudibleAlarm_valueChanged(int value);

    void on_ctrl_tempScaleToggle_valueChanged(int value);

private:
    void initCtrlArrays(void);
    void connectCustomSignals(void);

    void enableDisableSpeedControls(void);
    void updateSpeedControlTooltips(void);

    QString temperatureString(int t) const;

    void forceTempCtrlsToUpdate(void);

    Ui::gui_MainWindow *ui;

    int m_maxTemps[FC_MAX_CHANNELS];
    int m_minTemps[FC_MAX_CHANNELS];
    int m_lastTemps[FC_MAX_CHANNELS];
    int m_minLoggedRPMs[FC_MAX_CHANNELS];
    int m_maxLoggedRPMs[FC_MAX_CHANNELS];
    int m_lastRPMs[FC_MAX_CHANNELS];
    int m_alarmTemps[FC_MAX_CHANNELS];
    int m_channelMaxRPM[FC_MAX_CHANNELS];


    QLineEdit* m_ctrls_probeTemps[FC_MAX_CHANNELS];
    QLineEdit* m_ctrls_currentTemps[FC_MAX_CHANNELS];
    QSlider* m_ctrls_RpmSliders[FC_MAX_CHANNELS];

    bool m_isCelcius;
    bool m_isAuto;
    bool m_isAudibleAlarm;

    bool m_isAutoToggleByDevice;
    bool m_isCelciusToggleByDevice;
    bool m_isAudibleAlarmByDevice;

};

#endif // GUI_MAINWINDOW_H
