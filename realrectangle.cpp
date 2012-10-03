#include "realrectangle.h"

RealRectangle::RealRectangle()
{
}

RealRectangle::RealRectangle(RealPoint lowerLeft, RealPoint upperRight)
    : m_lowerLeft(lowerLeft),
      m_upperRight(upperRight)
{
}
