#ifndef GUI_SIMPLESQLQRY_H
#define GUI_SIMPLESQLQRY_H

#include <QDialog>

// Fwd declarations
class QStandardItemModel;
class QAbstractItemModel;

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
private slots:


private:
    Ui::gui_SimpleSqlQry *ui;

    QStandardItemModel* m_itemModel;
};

#endif // GUI_SIMPLESQLQRY_H
