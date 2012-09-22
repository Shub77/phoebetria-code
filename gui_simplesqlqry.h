#ifndef GUI_SIMPLESQLQRY_H
#define GUI_SIMPLESQLQRY_H

#include <QDialog>

// Fwd declarations
class QStandardItemModel;
class QAbstractItemModel;
class QSqlQuery;

namespace Ui {
class gui_SimpleSqlQry;
}

class gui_SimpleSqlQry : public QDialog
{
    Q_OBJECT
    
public:
    explicit gui_SimpleSqlQry(QWidget *parent = 0);
    ~gui_SimpleSqlQry();
    
protected:

    void populateTablesList(void);

    QAbstractItemModel* createItemModel(void);

    bool executeQuery(QSqlQuery* qry, const QString& sql);

private slots:


    void on_ctrl_execute_clicked();

private:
    Ui::gui_SimpleSqlQry *ui;

    QStandardItemModel* m_itemModel;
};

#endif // GUI_SIMPLESQLQRY_H
