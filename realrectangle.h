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
