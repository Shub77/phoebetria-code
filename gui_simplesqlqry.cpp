#include "gui_simplesqlqry.h"
#include "ui_gui_simplesqlqry.h"

#include <QListWidgetItem>
#include <QStandardItemModel>

#include "database.h"


gui_SimpleSqlQry::gui_SimpleSqlQry(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::gui_SimpleSqlQry),
    m_itemModel(NULL)
{
    ui->setupUi(this);

    QList<int> sizes;
    sizes << 100 << 300;
    ui->splitter->setSizes(sizes);

    populateTablesList();
    ui->ctrl_tableList->header()->hide();
}

gui_SimpleSqlQry::~gui_SimpleSqlQry()
{
    delete ui;
    if (m_itemModel) delete m_itemModel;
}

void gui_SimpleSqlQry::populateTablesList(void)
{
    createItemModel();

    QAbstractItemModel* model = ui->ctrl_tableList->model();
    ui->ctrl_tableList->setModel(m_itemModel);
    if (model) delete model;
}

QAbstractItemModel* gui_SimpleSqlQry::createItemModel(void)
{
    PhoebetriaDb db;

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

    if (m_itemModel) delete m_itemModel;
    m_itemModel = new QStandardItemModel(0, 0, this);
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
        item->setEditable(false);
        m_itemModel->appendRow(item);
    }

    return m_itemModel;
}
