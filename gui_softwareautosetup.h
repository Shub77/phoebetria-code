#ifndef GUI_SOFTWAREAUTOSETUP_H
#define GUI_SOFTWAREAUTOSETUP_H

#include <QDialog>

namespace Ui {
class gui_SoftwareAutoSetup;
}

class gui_SoftwareAutoSetup : public QDialog
{
    Q_OBJECT
    
public:
    explicit gui_SoftwareAutoSetup(QWidget *parent = 0);
    ~gui_SoftwareAutoSetup();
    
private:
    Ui::gui_SoftwareAutoSetup *ui;
};

#endif // GUI_SOFTWAREAUTOSETUP_H
