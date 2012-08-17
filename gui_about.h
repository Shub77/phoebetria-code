#ifndef GUI_ABOUT_H
#define GUI_ABOUT_H

#include <QDialog>

namespace Ui {
class gui_About;
}

class gui_About : public QDialog
{
    Q_OBJECT
    
public:
    explicit gui_About(QWidget *parent = 0);
    ~gui_About();
    
private:
    Ui::gui_About *ui;
};

#endif // GUI_ABOUT_H
