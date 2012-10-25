#include "gui_profiles.h"
#include "ui_gui_profiles.h"

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

// TODO: FIXME: Replace accepted() rejected() with custom functions
//              So abort/error can be handled more gracefully

void gui_Profiles::on_buttonBox_accepted()
{
    bool overwrite = true;

    QString pName = ui->ctrl_profileName->text();

    // TODO: FIXME: Also need to check for reserved profile names

    if (pName.isEmpty())
    {
        QMessageBox::warning(this,
                             tr("File not saved."),
                             tr("Invalid filename."));
        on_buttonBox_rejected();
    }

    if (!ui->ctrl_profileList->findItems(pName,
                                        Qt::MatchExactly).isEmpty())
    {
        if (QMessageBox::question(this,
                                  tr("Replace file?"),
                                  tr("Overwrite existing profile %1?")
                                    .arg(pName),
                                  QMessageBox::Yes,
                                  QMessageBox::No) == QMessageBox::No)
        {
            overwrite = false;
        }
    }
    if (overwrite)
    {
        m_profileName = pName;
        m_profileDescription = ui->ctrl_profileDescription->toPlainText();
    }
    else
        on_buttonBox_rejected();
}

void gui_Profiles::on_buttonBox_rejected()
{
    m_profileName = "";
    m_profileDescription = "";
}
