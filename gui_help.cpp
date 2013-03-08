#include "gui_help.h"
#include "ui_gui_help.h"
#include <QTreeWidget>
#include <QTreeWidgetItem>

gui_Help::gui_Help(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::gui_Help)
{
    ui->setupUi(this);
    ui->ctrl_helpList->expandAll();
    ui->ctrl_helpList->setColumnHidden(1, true);
    ui->ctrl_helpList->setCurrentItem(ui->ctrl_helpList->topLevelItem(0));
}

gui_Help::~gui_Help()
{
    delete ui;
}

void gui_Help::on_ctrl_helpList_currentItemChanged(QTreeWidgetItem *current, QTreeWidgetItem *previous)
{
    ui->ctrl_helpBrowser->setCurrentIndex(current->text(1).toInt());
}

void gui_Help::on_ctrl_close_clicked()
{
    this->close();
}
