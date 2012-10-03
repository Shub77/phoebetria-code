#include "realpoint.h"

RealPoint::RealPoint()
    : m_x(0),
      m_y(0)
{
}

RealPoint::RealPoint(RealPoint& point)
    : m_x(point.m_x),
      m_y(point.m_y)
{
}

RealPoint::RealPoint(double x, double y)
    : m_x(x),
      m_y(y)
{
}
