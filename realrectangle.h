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

#ifndef PHOEBETRIA_REALRECTANGLE_H
#define PHOEBETRIA_REALRECTANGLE_H



/*                  |
                    |y
                    |
             -------+-------
                    |   x
                    |
                    |

    Origin (0,0); x increasing to right; y inreasing upwards
*/


#include "realpoint.h"

class RealRectangle
{
public:
    RealRectangle();
    RealRectangle(RealPoint lowerLeft, RealPoint upperRight);

private:
    RealPoint m_lowerLeft;
    RealPoint m_upperRight;

};

#endif // PHOEBETRIA_REALRECTANGLE_H
