#ifndef TEMPERATUREMONITOR_H
#define TEMPERATUREMONITOR_H

#include <QObject>

/****************************************************************************
 ***************************************************************************/
class TemperatureSource : public QObject
{
    Q_OBJECT
public:
    explicit TemperatureSource(QObject *parent = 0);

signals:

public slots:

private:
    QString m_label;        // A name to associated with the source/probe
    int m_temperature;      //
    bool m_isCelcius;       // false == Fahrenheit
    int alarmTemperature;   // temperature to send an alarm signal; units depend on m_isCelcius
};

/****************************************************************************
 ***************************************************************************/
class TemperatureMonitor : public QObject
{
    Q_OBJECT
public:
    explicit TemperatureMonitor(QObject *parent = 0);
    
signals:
    
public slots:
    
private:
    // TODO: add list (Qlist?) of temperature sources
};


#endif // TEMPERATUREMONITOR_H
