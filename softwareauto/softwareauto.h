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

#ifndef SOFTWAREAUTO_H
#define SOFTWAREAUTO_H

#include <QObject>

#include "fanprofiles.h"

// Fwd Decls
class FanControllerIO;
class FanControllerData;

class SoftwareAuto : public QObject
{
    Q_OBJECT
public:
    explicit SoftwareAuto(QObject *parent = 0);

    void storeCurrentState(FanControllerData& fcData);

    bool switchOn(FanControllerIO& fcIO, FanControllerData& fcData);
    bool switchOff(FanControllerIO& fcIO, FanControllerData& fcData);  

signals:

public slots:

private:

    bool m_preStateStored;
    FanControllerProfile m_preSwAutoState;
};

#endif // SOFTWAREAUTO_H
