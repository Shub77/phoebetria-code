#include "gui_simplesqlqry.h"
#include "ui_gui_simplesqlqry.h"

gui_SimpleSqlQry::gui_SimpleSqlQry(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::gui_SimpleSqlQry)
{
    ui->setupUi(this);

    QList<int> sizes;
    sizes << 100 << 300;
    ui->splitter->setSizes(sizes);
}

gui_SimpleSqlQry::~gui_SimpleSqlQry()
{
    delete ui;
}
