#include "gui_preferences.h"
#include "ui_gui_preferences.h"

gui_preferences::gui_preferences(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::gui_preferences)
{
    ui->setupUi(this);
}

gui_preferences::~gui_preferences()
{
    delete ui;
}
