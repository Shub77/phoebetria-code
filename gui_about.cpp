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

#include "gui_about.h"
#include "ui_gui_about.h"

#include "builddetails.h"

gui_About::gui_About(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::gui_About)
{
    ui->setupUi(this);
    this->setFixedSize(this->size());   // Disable resizing
    ui->ctrl_version->setText("Version " + BuildDetails::versionStr());
    ui->ctrl_build->setText("Build date: " + BuildDetails::buildDateTimeStr());
}

gui_About::~gui_About()
{
    delete ui;
}


void gui_About::on_ctrl_aboutDlgBtnBox_clicked(QAbstractButton *button)
{
    (void)(button); // Unused

    this->close();
}
