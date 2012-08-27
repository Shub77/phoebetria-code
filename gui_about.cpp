#include "gui_about.h"
#include "ui_gui_about.h"

#include "builddetails.h"

gui_About::gui_About(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::gui_About)
{
    ui->setupUi(this);
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
