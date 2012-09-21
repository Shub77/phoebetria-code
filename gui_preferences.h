#ifndef GUI_PREFERENCES_H
#define GUI_PREFERENCES_H

#include <QDialog>

namespace Ui {
class gui_preferences;
}

class gui_preferences : public QDialog
{
    Q_OBJECT
    
public:
    explicit gui_preferences(QWidget *parent = 0);
    ~gui_preferences();
    
private:
    Ui::gui_preferences *ui;
};

#endif // GUI_PREFERENCES_H
