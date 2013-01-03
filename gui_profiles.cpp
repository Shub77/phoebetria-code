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
    ui(new Ui::gui_Profiles),
    m_action(0)
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

    m_previewReport.clear();

    m_profileName = ui->ctrl_profileList->currentItem()->text();
    m_profileDescription = fcp.profileDescription(m_profileName);

    ui->ctrl_profileName->setText(m_profileName);
    ui->ctrl_profileDescription->setPlainText(m_profileDescription);

    fcp.load(m_profileName);

    m_previewReport += "</body></html>";
    m_previewReport += getPreviewReportCommon(fcp);

    if (fcp.isSoftwareAuto())
    {
        m_previewReport += getPreviewReportSWAuto(fcp);
    }
    else
    {
        m_previewReport += getPreviewReportManual(fcp);
    }

    m_previewReport += "<html><body>";

    QFont font = ui->ctrl_profilePreview->font();
    font.setPointSize(9);

    ui->ctrl_profilePreview->setFont(font);
    ui->ctrl_profilePreview->setHtml(m_previewReport);

}

QString gui_Profiles::getPreviewReportCommon(const FanControllerProfile& fcp) const
{
    QString report;

    report += "<table border=0>";
    report += "<tr><td width=120 align=left><h3>Profile Name:</h3</td><td width=100 align=left><h3>" + m_profileName + "</h3></td></tr>";
    report += "</table>";
    report += "<p></p>";
    report += "<table border=0>";
    report += "<tr><td width=120 align=left>Temperature Scale:</td><td width=100 align=left>" + boolToTempScale(fcp.isCelcius()) + "</td></tr>";
    report += "<tr><td width=120 align=left>Audible Alarm:</td><td width=100 align=left>" + boolToText(fcp.isAudibleAlarm()) + "</td></tr>";
    report += "<tr><td width=120 align=left>Recon Auto:</td><td width=100 align=left>" + boolToText(fcp.isAuto()) + "</td></tr>";
    report += "<tr><td width=120 align=left>Software Auto:</td><td width=100 align=left>" + boolToText(fcp.isSoftwareAuto()) + "</td></tr>";
    report += "</table>";
    report += "<p></p>";

    return report;
}
QString gui_Profiles::getPreviewReportManual(const FanControllerProfile& fcp) const
{
    const FanControllerData& fcd = ph_fanControllerData();
    QString report;

    report += "<table border=0>";
    report += "<tr><th width=120 align=left>Channel</p></th><th width=100 align=left>RPM</th><th align=left width=100>Alert Temp</th></tr>";

    for (int channel = 0; channel < FC_MAX_CHANNELS; ++channel)
    {
        QString channelRPM = QString::number(fcp.speed(channel));
        QString channelAlarm = fcd.temperatureString(fcp.alarmTemp(channel), true);

        report += "<tr><td width=120 align=left>" + ph_prefs().channelName(channel) + "</td>";
        report += "<td width=100 align=left>" + channelRPM + "</td>";
        report += "<td width=100 align=left>" + channelAlarm + "</td></tr>";
    }
    report += "</table>";

    return report;
}

QString gui_Profiles::getPreviewReportSWAuto(const FanControllerProfile& fcp) const
{
    QString report;

    report += "<table border=0><tr>";
    report += "<th width=120 align=left>Channel</p></th>";
    report += "<th width=100 align=left>Alert Temp</th>";
    report += "<th width=100 align=left>Turn Off</th>";
    report += "<th width=100 align=left>Temp Fan On</p></th>";
    report += "<th width=100 align=left>Temp/Speed Start</th>";
    report += "<th width=100 align=left>Temp/Speed Mid</th>";
    report += "<th width=100 align=left>Temp/Speed End</p></th>";
    report += "<th width=100 align=left>Temp Fan Max</th>";
    report += "<th width=100 align=left>Min RPM</th>";
    report += "<th width=100 align=left>Max RPM</p></th>";
    report += "<th width=100 align=left>Probe Afinity</th>";
    report += "<th width=100 align=left>Hysteresis Up</th>";
    report += "<th width=100 align=left>Hysteresis Down</p></th>";
    report += "<th width=100 align=left>Hysteresis Off</th>";
    report += "</tr>";

    for (int channel = 0; channel < FC_MAX_CHANNELS; ++channel)
    {
        const FanSpeedRamp& ramp = fcp.ramp(channel);
        bool isCelcius = ph_fanControllerData().isCelcius();

        QString channelAlarm = FanControllerData::temperatureString(fcp.alarmTemp(channel), true, isCelcius);
        QString temperatureF_fanOn = FanControllerData::temperatureString(ramp.temperatureF_fanOn(), true, isCelcius);
        QString tempRampStart = FanControllerData::temperatureString(ramp.temperatureF_rampStart(), true, isCelcius);
        QString speedRampStart = QString::number(ramp.speed_rampStart());
        QString tempRampMid = FanControllerData::temperatureString(ramp.temperatureF_rampMid(), true, isCelcius);
        QString speedRampMid = QString::number(ramp.speed_rampMid());
        QString tempRampEnd = FanControllerData::temperatureString(ramp.temperatureF_rampEnd(), true, isCelcius);
        QString speedRampEnd = QString::number(ramp.speed_rampEnd());

        report += "<tr><td width=120 align=left>" + ph_prefs().channelName(channel) + "</td>";
        report += "<td width=100 align=left>" + channelAlarm + "</td>";
        report += "<td width=100 align=left>" + boolToText(ramp.allowFanToTurnOff()) + "</td>";
        report += "<td width=100 align=left>" + temperatureF_fanOn + "</td>";
        report += "<td width=100 align=left>" + tempRampStart + " / " + speedRampStart+ "</td>";
        report += "<td width=100 align=left>" + tempRampMid + " / " + speedRampMid+ "</td>";
        report += "<td width=100 align=left>" + tempRampEnd + " / " + speedRampEnd+ "</td>";
        report += "<td width=100 align=left>" + QString::number(ramp.temperatureF_fanToMax()) +"</td>";
        report += "<td width=100 align=left>" + QString::number(ramp.minUsableRpm()) +"</td>";
        report += "<td width=100 align=left>" + QString::number(ramp.maxUsableRpm()) +"</td>";
        report += "<td width=100 align=left>" + QString::number(ramp.hysteresisUp()) +"</td>";
        report += "<td width=100 align=left>" + QString::number(ramp.hysteresisDown()) +"</td>";
        report += "<td width=100 align=left>" + QString::number(ramp.hysteresisFanOff()) +"</td>";
        report += "</tr>";
    }

    report += "</table>";

    return report;

}

void gui_Profiles::on_ctrl_EraseProfile_clicked()
{
    FanControllerProfile fcp;

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
    QString text;
    bool changeStartupProfile = false;
    bool changeShutdownProfile = false;

    if (m_profileName == ph_prefs().startupProfile())
    {
        text = QString ("You have selected to delete profile: "
                "%1\n\n"
                "This is currently set as your startup profile.\n"
                "Your preferences will be modified appropriately if you continue.\n\n"
                "Would you like to continue?\n").arg(m_profileName);
        changeStartupProfile = true;
    }
    else if (m_profileName == ph_prefs().shutdownProfile())
    {
        text = QString ("You have selected to delete profile:"
                "%1\n\n"
                "This is currently set as your shutdown profile. "
                "Your preferences will be modified appropriately if you continue.\n\n"
                "Would you like to continue?\n").arg(m_profileName);
        changeShutdownProfile = true;
    }
    else
    {
        text = QString("You have selected to delete profile: "
                           "%1\n\n"
                           "Would you like to continue?\n").arg(m_profileName);
    }
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
                m_profileName.clear();
                m_profileDescription.clear();
                m_action |= RefreshProfileDisplay;

                if (changeStartupProfile)
                    ph_prefs().setStartupProfile("");
                if (changeShutdownProfile)
                    ph_prefs().setShutdownProfile("");

                return;
            }
            else
            {
                QMessageBox::critical(
                            this,
                            tr("Erase failed"),
                            tr("An error occurred deleting the profile.\n"
                               "The profile has NOT been deleted!")
                            );
            }
            break;
        case QMessageBox::Cancel:
            break;
     }

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

    m_action = LoadProfile;
    this->accept();
}

void gui_Profiles::on_ctrl_SaveProfile_clicked()
{

    m_profileName = ui->ctrl_profileName->text().trimmed();
    m_profileDescription = ui->ctrl_profileDescription->toPlainText();

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

    // TODO FIXME Check that the profile name is not reserved

    m_action = SaveProfile;
    this->accept();
}

void gui_Profiles::on_ctrl_profileClose_clicked()
{
    this->close();
}
