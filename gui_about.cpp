#include "gui_about.h"
#include "ui_gui_about.h"

gui_About::gui_About(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::gui_About)
{
    ui->setupUi(this);
}

gui_About::~gui_About()
{
    delete ui;
}
