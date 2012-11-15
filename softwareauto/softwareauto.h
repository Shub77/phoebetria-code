#ifndef SOFTWAREAUTO_H
#define SOFTWAREAUTO_H

#include <QObject>

#include "fanprofiles.h"

// Fwd Decls
class FanControllerIO;
class FanControllerData;

class SoftwareAuto : public QObject
{
    Q_OBJECT
public:
    explicit SoftwareAuto(QObject *parent = 0);

    void storeCurrentState(FanControllerData& fcData);

    bool switchOn(FanControllerIO& fcIO, FanControllerData& fcData);
    bool switchOff(FanControllerIO& fcIO, FanControllerData& fcData);  

signals:

public slots:

private:

    bool m_preStateStored;
    FanControllerProfile m_preSwAutoState;
};

#endif // SOFTWAREAUTO_H
