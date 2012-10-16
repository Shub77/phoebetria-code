#ifndef GUI_PROFILES_H
#define GUI_PROFILES_H

#include <QDialog>

namespace Ui {
class gui_Profiles;
}

class gui_Profiles : public QDialog
{
    Q_OBJECT
    
public:
    explicit gui_Profiles(QWidget *parent = 0);
    ~gui_Profiles();

    bool init();

    bool saveProfile(void);
    bool eraseProfile(void);

    
private slots:
    void on_ctrl_profileList_itemClicked();

private:
    Ui::gui_Profiles *ui;

    bool getProfileList(void);

    QString m_profileDescription;
    QString m_profileName;
};

#endif // GUI_PROFILES_H
