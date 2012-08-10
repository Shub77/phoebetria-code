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

#include "gui_mainwindow.h"
#include "ui_gui_mainwindow.h"
#include "phoebetriaapp.h"
#include "bfx-recon/fancontroller.h"

gui_MainWindow::gui_MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::gui_MainWindow)
{
    ui->setupUi(this);
    connectCustomSignals();
}

gui_MainWindow::~gui_MainWindow()
{
    delete ui;
}

void gui_MainWindow::connectCustomSignals(void)
{
    PhoebetriaApp *app = (PhoebetriaApp*)qApp;

    connect(&app->fanController(), SIGNAL(currentRPM(int,uint)),
            this, SLOT(onCurrentRPM(int,uint)));

}


void gui_MainWindow::onCurrentRPM(int channel, uint RPM)
{
    switch (channel)
    {
    case 0:
        this->ui->ctrl_channel1speed->setText(QString::number(RPM));
        break;
    case 1:
        this->ui->ctrl_channel2speed->setText(QString::number(RPM));
        break;
    case 2:
        this->ui->ctrl_channel3speed->setText(QString::number(RPM));
        break;
    case 3:
        this->ui->ctrl_channel4speed->setText(QString::number(RPM));
        break;
    case 4:
        this->ui->ctrl_channel5speed->setText(QString::number(RPM));
        break;
    default:
        break;
    }
}
