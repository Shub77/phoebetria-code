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

#ifndef PHOEBETRIA_FANCURVE_H
#define PHOEBETRIA_FANCURVE_H

class FanCurve
{
public:
    FanCurve();

    inline double bezierCubic(double t,
                              double start,
                              double cp1,
                              double cp2,
                              double end);
};


double FanCurve::bezierCubic(double t,
                             double start,
                             double cp1,
                             double cp2,
                             double end)
{
    double mt = 1 - t;
    return mt*mt*mt*start + 3*mt*mt*t*cp1 + 3*mt*t*t*cp2 + t*t*t*end;
}

#endif // PHOEBETRIA_FANCURVE_H
