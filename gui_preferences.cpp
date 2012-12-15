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

#include "gui_preferences.h"
#include "ui_gui_preferences.h"

#include "phoebetriaapp.h"

gui_Preferences::gui_Preferences(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::gui_Preferences)
{
    ui->setupUi(this);
    initControls();
}

gui_Preferences::~gui_Preferences()
{
    delete ui;
}

void gui_Preferences::initControls(void)
{
    ui->ctrl_minimizeOnStart->setChecked(ph_prefs().startMinimized());
    ui->ctrl_minimizeToTray->setChecked(ph_prefs().minimizeToTray());
    ui->ctrl_showTooltipOnMinimize->setChecked(ph_prefs().showTrayIconTooltips());
    ui->ctrl_useLogRpmScale->setChecked(ph_prefs().useLogScaleRpmSliders());
    ui->ctrl_quitOnClose->setChecked(ph_prefs().quitOnClose());

    //ui->ctrl_startupProfile->setsetChecked(ph_prefs().setStartupProfile());
    //ui->ctrl_shutdownProfile->setChecked(ph_prefs().setShutdownProfile());
}

void gui_Preferences::commitChanges(void) const
{
    ph_prefs().setStartMinimized(ui->ctrl_minimizeOnStart->isChecked());
    ph_prefs().setMinimizeToTray(ui->ctrl_minimizeToTray->isChecked());
    ph_prefs().setShowIconTooltips(ui->ctrl_showTooltipOnMinimize->isChecked());
    ph_prefs().setUseLogScaleRpmSliders(ui->ctrl_useLogRpmScale->isChecked());
    ph_prefs().setQuitOnClose(ui->ctrl_quitOnClose->isChecked());

    //ph_prefs().setStartupProfile(ui->ctrl_startupProfile->currentText());
    //ph_prefs().setShutdownProfile(ui->ctrl_shutdownProfile->currentText());

    ph_prefs().sync();
}

void gui_Preferences::on_ctrl_actionButtons_accepted()
{
    commitChanges();
}
