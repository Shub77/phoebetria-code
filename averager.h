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

#ifndef AVERAGER_H
#define AVERAGER_H

class Averager
{
public:
    Averager();
    ~Averager();

    void addSampleValue(int value);

    void clear(void);

    inline int average(void) const;

protected:

    int updateStoredAverage(void);

private:

    static const int m_sampleSize;

    int* m_samples;
    int m_pos;
    int m_storedAverage;


};

int Averager::average(void) const
{
    return m_storedAverage;
}

#endif // AVERAGER_H
