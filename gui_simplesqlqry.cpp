#include "gui_simplesqlqry.h"
#include "ui_gui_simplesqlqry.h"

#include <QListWidgetItem>
#include <QStringListModel>
#include <QStandardItemModel>

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

    QList<QStringList> columnNames;

    QStringList names;
    for (int i = 0; i < tables.count(); ++i)
    {
        names = db.tableFields(tables.at(i));
        /* Append even if the result is empty because the column names
         * list needs to be in the same order as tables.
         */
        columnNames.append(names);
    }

    QStandardItemModel* itemModel = new QStandardItemModel(0, 0, this);
    for (int i = 0; i < tables.count(); ++i)
    {
        QStandardItem* item = new QStandardItem(tables.at(i));
        const QStringList* fields = &columnNames.at(i);
        for (int j = 0; j < fields->count(); ++j)
        {
            QStandardItem* child = new QStandardItem(fields->at(j));
            child->setEditable(false);
            item->appendRow(child);
        }
        itemModel->appendRow(item);
    }

    QAbstractItemModel* model = ui->ctrl_tableList->model();

    ui->ctrl_tableList->setModel(itemModel);

    if (model) delete model;

    ui->ctrl_tableList->header()->hide();
}
