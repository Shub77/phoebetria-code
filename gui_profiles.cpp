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

#include "gui_profiles.h"
#include "ui_gui_profiles.h"
#include "phoebetriaapp.h"

#include <QDebug>
#include <QMessageBox>

#include "fanprofiles.h"

gui_Profiles::gui_Profiles(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::gui_Profiles)
{
    ui->setupUi(this);

    init();
}

gui_Profiles::~gui_Profiles()
{
    delete ui;
}

bool gui_Profiles::init(void)
{
    getProfileList();
    return true;
}

bool gui_Profiles::getProfileList(void)
{
    FanControllerProfile fcp;
    ui->ctrl_profileList->clear();

    QStringList m_ProfileList = fcp.getProfileNames();

    bool bs = ui->ctrl_profileList->blockSignals(true);

    for (int i = 0; i < m_ProfileList.count(); ++i)
    {
        const QString& item = m_ProfileList.at(i);
        // Skip reserved profile names
        if (FanControllerProfile::isReservedProfileName(item)) continue;
        ui->ctrl_profileList->addItem(item);
    }

    ui->ctrl_profileList->blockSignals(bs);

    return true;
}

void gui_Profiles::on_ctrl_profileList_itemClicked()
{
    FanControllerProfile fcp;

    m_profileName = ui->ctrl_profileList->currentItem()->text();
    m_profileDescription = fcp.profileDescription(m_profileName);

    ui->ctrl_profileName->setText(m_profileName);
    ui->ctrl_profileDescription->setPlainText(m_profileDescription);
}

void gui_Profiles::on_ctrl_SaveProfile_clicked()
{
    m_profileName = ui->ctrl_profileName->text().trimmed();
    m_profileDescription = ui->ctrl_profileDescription->toPlainText();

    bool bs1 = this->blockSignals(true);
    bool bs2 = fcdata().blockSignals(true);

    if (m_profileName.trimmed().isEmpty())
    {
        QMessageBox::critical(
                    this,
                    tr("Invalid profile name"),
                    tr("The profile name you have entered is\n"
                       " blank, please enter a valid name!")
                    );
        return;
    }

    FanControllerProfile fcp(m_profileName, m_profileDescription);
    fcp.setFromCurrentData(fcdata());

    this->blockSignals(bs1);
    fcdata().blockSignals(bs2);

    if (fcp.save(m_profileName))
    {
        getProfileList();
        this->close();
    }
    else
    {
        QMessageBox::critical(
                    this,
                    tr("Save failed"),
                    tr("An error occurred saving the profile.\n"
                       "The profile has NOT been saved!")
                    );
        return;
    }
}

void gui_Profiles::on_ctrl_EraseProfile_clicked()
{
    FanControllerProfile fcp;

//    if (m_profileName == ui->ctrl_profileName->currentText())
//    {
//        //TODO: Error while trying to delete Profile being used?
//        return;
//    }

    if (FanControllerProfile::isReservedProfileName(m_profileName))
    {
        QMessageBox::critical(
                    this,
                    tr("Invalid profile name"),
                    tr("Profile names beginning with %1"
                       " are reserved.\nThe profile has not been erased!")
                    .arg(FanControllerProfile::reservedProfileNameStartChars())
                    );

        return;
    }

    if (!fcp.getProfileNames().contains(m_profileName))
    {
        return; // Nothing to delete; i.e. profile does not exist
    }

    QMessageBox msgbox;
    QString text = QString("You have selected to delete profile:\n"
                           "%1\n\n"
                           "Would you like to continue?\n").arg(m_profileName);
    msgbox.setWindowTitle("Erase Profile");
    msgbox.setText(text);
    msgbox.addButton(QMessageBox::Ok);
    msgbox.addButton(QMessageBox::Cancel);

    int status = msgbox.exec();
    switch (status) {
        case QMessageBox::Ok:
            if (fcp.erase(m_profileName))
            {
                getProfileList();
                ui->ctrl_profileName->clear();
                ui->ctrl_profileDescription->clear();

                return;
            };
            break;
        case QMessageBox::Cancel:
            break;
     }

}

FanControllerData& gui_Profiles::fcdata(void) const
{
    return ph_fanControllerData();
}

void gui_Profiles::on_ctrl_LoadProfile_clicked()
{
    FanControllerProfile fcp;

    if (!fcp.getProfileNames().contains(m_profileName))
    {
        QMessageBox::critical(
                    this,
                    tr("Profile not found!"),
                    tr("Profile named: %1 was not found!"
                       "\n\nPlease verify the name and try again.")
                    .arg(ui->ctrl_profileName->text())
                    );
        return;

    }

    bool success = false;

    if (fcp.load(m_profileName))
    {
        FanControllerIO* fc = &ph_fanControllerIO();

        if (fc->setFromProfile(fcp))
        {
            fcdata().syncWithProfile(fcp);
            success = true;
            this->accept();
        }
        else
        {
            // TODO: Display error message
        }
    }
}
