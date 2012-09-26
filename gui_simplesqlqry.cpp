#include "gui_simplesqlqry.h"
#include "ui_gui_simplesqlqry.h"

#include <QListWidgetItem>
#include <QStandardItemModel>
#include <QTableView>
#include <QSqlQueryModel>
#include <QDialog>
#include <QLayout>

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

    sizes.clear();
    sizes << 400 << 100;
    ui->verticalSplitter->setSizes(sizes);

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
    PhoebetriaDbMgr db;

    QStringList tables = db.tables(db.connectionName());
    tables.sort();

    QList<QStringList> columnNames;

    QStringList names;
    for (int i = 0; i < tables.count(); ++i)
    {
        names = db.tableFields(db.connectionName(), tables.at(i));
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

void gui_SimpleSqlQry::on_ctrl_execute_clicked()
{
    QString sql = ui->ctrl_sql->toPlainText().simplified();
    if (sql.isEmpty())
    {
        ui->ctrl_messages->appendPlainText(tr("ERROR: Nothing to execute\n"));
        return;
    }

    QSqlDatabase db = QSqlDatabase::database(PhoebetriaDbMgr::connectionName());

    //QSqlQuery qry(sql, db);

    //bool ok = executeQuery(&qry, sql);
    //bool ok = db.exec(qry)

    QSqlQuery qry = db.exec(sql);
    bool ok = !qry.isValid() && qry.lastError().type() == QSqlError::NoError;

    QString txt;
    txt = ok ? tr("Success") : tr("Failure: %1").arg(qry.lastError().text());
    ui->ctrl_messages->appendPlainText(txt);

    qDebug() << qry.size();
    qDebug() << "Query is:" << (qry.isActive() ? "Active" : "Not active");


    if (ok && qry.isSelect())
    {
        displayResult(sql, db);
    }

}

bool gui_SimpleSqlQry::executeQuery(QSqlQuery* qry, const QString& sql)
{
    QSqlDatabase db = QSqlDatabase::database(PhoebetriaDbMgr::connectionName());

    qry->exec();

    return qry->lastError().type() == QSqlError::NoError;
}

void gui_SimpleSqlQry::displayResult(const QString& qry, QSqlDatabase& db)
{
    QSqlQueryModel* model;

    QDialog *dlg = new QDialog(this);
    dlg->setAttribute(Qt::WA_DeleteOnClose);


    QLabel* sqlText = new QLabel();
    sqlText->setText(qry);


    QTableView* view = new QTableView();
    QFont font = view->font();
    font.setFamily("Arial");
    font.setPointSize(8);
    view->setFont(font);

    QVBoxLayout *layout = new QVBoxLayout;;
    dlg->setLayout(layout);
    layout->addWidget(sqlText);
    layout->addWidget(view);
    //layout->setContentsMargins(0,0,0,0);

    model = new QSqlQueryModel(view);
    model->setQuery(qry, db);
    view->setModel(model);

    dlg->resize(800, 400);
    dlg->show();
}


