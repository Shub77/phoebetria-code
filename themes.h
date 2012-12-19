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

#ifndef THEMES_H
#define THEMES_H

#include <QStringList>

class Themes
{
public:
    Themes();

    static void getCustomThemeFilenames(QStringList *dest);

    static QString themePath(void);

    static QString getStyleSheet(const QString& filename);

    static bool setAppStyleSheet(const QString& filename);

    inline static QString getBuiltInStyleSheet(void);
    inline static bool setAppToBuiltInStyleSheet(void);
};

QString Themes::getBuiltInStyleSheet(void)
{
    return getStyleSheet(":/other/Phoebetria.qss");
}

bool Themes::setAppToBuiltInStyleSheet(void)
{
    return setAppStyleSheet(":/other/Phoebetria.qss");
    //FIXME: Testing
    //return setAppStyleSheet(":/other/Phoebetria-Dark.qss");
}

#endif // THEMES_H
