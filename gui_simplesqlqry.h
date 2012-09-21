#ifndef GUI_SIMPLESQLQRY_H
#define GUI_SIMPLESQLQRY_H

#include <QDialog>

namespace Ui {
class gui_SimpleSqlQry;
}

class gui_SimpleSqlQry : public QDialog
{
    Q_OBJECT
    
public:
    explicit gui_SimpleSqlQry(QWidget *parent = 0);
    ~gui_SimpleSqlQry();
    
private:
    Ui::gui_SimpleSqlQry *ui;
};

#endif // GUI_SIMPLESQLQRY_H
