#ifndef GUI_SOFTWAREAUTOSETUP_H
#define GUI_SOFTWAREAUTOSETUP_H

#include <QDialog>

#include "fancurve.h"

namespace Ui {
class gui_SoftwareAutoSetup;
}

class gui_SoftwareAutoSetup : public QDialog
{
    Q_OBJECT
    
public:
    explicit gui_SoftwareAutoSetup(QWidget *parent = 0);
    ~gui_SoftwareAutoSetup();
    
    void init(void);

private:
    Ui::gui_SoftwareAutoSetup *ui;

    FanCurve m_fanCurve;
};

#endif // GUI_SOFTWAREAUTOSETUP_H
