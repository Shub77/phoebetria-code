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

#ifndef BEZIERFANCURVE_H
#define BEZIERFANCURVE_H

class BezierFanCurve
{
public:
    BezierFanCurve();

    inline double cubic(double t,
                        double start,
                        double co1,
                        double co2,
                        double end);
};


double BezierFanCurve::cubic(double t,
                             double start,
                             double co1,
                             double co2,
                             double end)
{
    double mt = 1 - t;
    return mt*mt*mt*start + 3*mt*mt*t*co1 + 3*mt*t*t*co2 + t*t*t*end;
}

#endif // BEZIERFANCURVE_H
