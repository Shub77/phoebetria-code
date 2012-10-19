#include "gui_profiles.h"
#include "ui_gui_profiles.h"
#include "maindb.h"
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

        QString m_profileName = ui->ctrl_profileList->currentItem()->text();

        if (fcp.read(m_profileName))
        {
            QString m_profileDescription = fcp.description();

            ui->ctrl_profileName->setText(m_profileName);
            ui->ctrl_profileDescription->setPlainText(m_profileDescription);
        }
}

void gui_Profiles::on_buttonBox_accepted()
{
    m_profileName = ui->ctrl_profileName->text();
    m_profileDescription = ui->ctrl_profileDescription->toPlainText();
}

void gui_Profiles::on_buttonBox_rejected()
{
    m_profileName = "";
    m_profileDescription = "";
}
