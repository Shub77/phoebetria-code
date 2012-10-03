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

#ifndef GUI_SIMPLESQLQRY_H
#define GUI_SIMPLESQLQRY_H

#include <QDialog>

// Fwd declarations
class QStandardItemModel;
class QAbstractItemModel;
class QSqlQuery;
class QSqlDatabase;

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
    void displayResult(const QString &qry, QSqlDatabase& db);

private slots:


    void on_ctrl_execute_clicked();

private:
    Ui::gui_SimpleSqlQry *ui;

    QStandardItemModel* m_itemModel;
};

#endif // GUI_SIMPLESQLQRY_H
