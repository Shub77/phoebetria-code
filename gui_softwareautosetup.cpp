#include "gui_softwareautosetup.h"
#include "ui_gui_softwareautosetup.h"

gui_SoftwareAutoSetup::gui_SoftwareAutoSetup(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::gui_SoftwareAutoSetup)
{
    ui->setupUi(this);
}

gui_SoftwareAutoSetup::~gui_SoftwareAutoSetup()
{
    delete ui;
}
