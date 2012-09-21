#include "gui_preferences.h"
#include "ui_gui_preferences.h"

gui_Preferences::gui_Preferences(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::gui_Preferences)
{
    ui->setupUi(this);
}

gui_Preferences::~gui_Preferences()
{
    delete ui;
}
