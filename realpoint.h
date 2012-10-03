#ifndef PHOEBETRIA_REALPOINT_H
#define PHOEBETRIA_REALPOINT_H

class RealPoint
{
public:
    RealPoint();
    explicit RealPoint(RealPoint& point);
    RealPoint(double x, double y);

private:

    double m_x;
    double m_y;
};

#endif // PHOEBETRIA_REALPOINT_H
