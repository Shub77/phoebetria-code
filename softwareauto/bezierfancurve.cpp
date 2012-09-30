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

#include "bezierfancurve.h"

#include <QDebug>

BezierFanCurve::BezierFanCurve()
{
}

int BezierFanCurve::cubicInt(int t, int start, int co1, int co2, int end)
{
    // pre: t <= start; start < end;

    /* Convert all values >=0 && <= 1
       Calculate cubic ordinate
       Convert back to "reference" frame
     */
    int shift = 0-start;
    return cubic( (double)(t+shift)/(end+shift),
                  (double)(start+shift)/(end+shift),
                  (double)(co1+shift)/(end+shift),
                  (double)(co2+shift)/(end+shift),
                  (double)(end+shift)/(end+shift)
                ) * (end+shift) - shift;
            ;
}

void BezierFanCurve::test1(void)
{
    int rampStart = 20; // 20F (x)
    int speedRampStart = 400; // start at 400 RPM (y)
    int rampEnd = 250; // 250F (x)
    int speedRampEnd = 1400; // end at 1400 RPM (y)

    // Arbitrary values
    int cp1_x = rampEnd;
    int cp1_y = speedRampStart;

    int cp2_x = rampStart;
    int cp2_y = speedRampEnd;

    struct coord {int x; int y;};

    struct coord curve[255];

    int i = 0;
    for ( ; i < rampStart; ++i)
    {
        curve[i].x = i;
        curve[i].y = 0;
    }
    for ( ; i <= rampEnd; ++i)
    {
        curve[i].x = cubicInt(i, rampStart, cp1_x, cp2_x, rampEnd);
        curve[i].y = cubicInt(i, speedRampStart, cp1_y, cp2_y, speedRampEnd);
    }
    for (; i < 256; ++i)
    {
        curve[i].x = i;
        curve[i].y = speedRampEnd;
    }

    for (i = 0; i < 256; ++i)
    {
        qDebug() << curve[i].x << curve[i].y;
    }
}
