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

    QStringList items = fcp.getProfileNames();

    bool bs = ui->ctrl_profileList->blockSignals(true);

    for (int i = 0; i < items.count(); ++i)
    {
        const QString& item = items.at(i);
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
    m_profileName = ui->ctrl_profileName->text();
    m_profileDescription = ui->ctrl_profileDescription->toPlainText();

    bool bs1 = this->blockSignals(true);
    bool bs2 = fcdata().blockSignals(true);

    FanControllerProfile fcp(m_profileName, m_profileDescription);
    fcp.setFromCurrentData(fcdata());

    this->blockSignals(bs1);
    fcdata().blockSignals(bs2);

    qDebug() << "GUI Profiles:" << m_profileName;

    if (fcp.save(m_profileName))
    {
        getProfileList();
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

    bool success = false;

    if (fcp.load(m_profileName))
    {
        FanControllerIO* fc = &ph_fanControllerIO();

        if (fc->setFromProfile(fcp))
        {
            fcdata().syncWithProfile(fcp);
//            updateSpeedControlTooltips();
//            updateAllSpeedCtrls();
//            updateAllAlarmCtrls(fcdata().isCelcius());
//            updateToggleControls();
//            enableSpeedControls(!fcp.isAuto());

            success = true;
        }
    }
}
