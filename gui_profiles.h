/*  Copyright 2012 Craig Robbins and Christopher Ferris

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with the program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef GUI_PROFILES_H
#define GUI_PROFILES_H

#include <QDialog>
#include "fancontrollerdata.h"

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

    const QString& selectedName(void) const;
    const QString& selectedDescription(void) const;
    
private slots:
    void on_ctrl_profileList_itemClicked();

    void on_ctrl_SaveProfile_clicked();

    void on_ctrl_EraseProfile_clicked();

    void on_ctrl_LoadProfile_clicked();

private:
    Ui::gui_Profiles *ui;

    bool getProfileList(void);

    QStringList m_ProfileList;
    QString m_profileDescription;
    QString m_profileName;

    FanControllerData& fcdata(void) const;
};

inline const QString& gui_Profiles::selectedName(void) const
{
    return m_profileName;
}

inline const QString& gui_Profiles::selectedDescription(void) const
{
    return m_profileDescription;
}


#endif // GUI_PROFILES_H
