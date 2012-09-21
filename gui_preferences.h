#ifndef GUI_PREFERENCES_H
#define GUI_PREFERENCES_H

#include <QDialog>

namespace Ui
{
class gui_Preferences;
}

class gui_Preferences : public QDialog
{
    Q_OBJECT
    
public:
    explicit gui_Preferences(QWidget *parent = 0);
    ~gui_Preferences();
    
private:
    Ui::gui_Preferences *ui;
};

#endif // GUI_PREFERENCES_H
