#include "gui_simplesqlqry.h"
#include "ui_gui_simplesqlqry.h"

#include <QListWidgetItem>
#include <QStringListModel>

#include "database.h"


gui_SimpleSqlQry::gui_SimpleSqlQry(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::gui_SimpleSqlQry)
{
    ui->setupUi(this);

    QList<int> sizes;
    sizes << 100 << 300;
    ui->splitter->setSizes(sizes);

    populateTablesList();
}

gui_SimpleSqlQry::~gui_SimpleSqlQry()
{
    delete ui;
}

void gui_SimpleSqlQry::populateTablesList(void)
{
    Database db;

    QStringList tables = db.tables();
    tables.sort();

    QAbstractItemModel* model = ui->ctrl_tableList->model();
    QStringListModel* newmodel = new QStringListModel(ui->ctrl_tableList);

    newmodel->setStringList(tables);

    ui->ctrl_tableList->setModel(newmodel);

    if (model) delete model;
}
