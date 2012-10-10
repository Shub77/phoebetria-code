#ifndef GUI_SOFTWAREAUTOSETUP_H
#define GUI_SOFTWAREAUTOSETUP_H

#include <QDialog>

#include "fanramp.h"

// Fwd decls
class FanControllerData;

namespace Ui {
class gui_SoftwareAutoSetup;
}

class gui_SoftwareAutoSetup : public QDialog
{
    Q_OBJECT
    
public:
    explicit gui_SoftwareAutoSetup(QWidget *parent = 0);
    ~gui_SoftwareAutoSetup();
    
    void init(FanControllerData* fcdata);

protected:

    void setupAxes(const FanControllerData & fcdata, int channel);
    void setupTemperatureCtrlLimits(const FanControllerData & fcdata);
    void setupSpeedCtrlLimits(int maxRpm);
    void setupChannelComboBox(void);

    void xferSettings_toGui(const FanControllerData &fcdata, int channel);
    void xferSettings_fromGui(const FanControllerData &fcdata);

    void drawPlot(void);

    void regenerateCurve(void);

    int tempInF(int t) const;

    inline bool ignoreSignals(bool ignore = true);

private slots:

    void on_ctrl_rampStartTemp_valueChanged(int arg1);

    void on_ctrl_rampMidTemp_valueChanged(int arg1);

    void on_ctrl_rampEndTemp_valueChanged(int arg1);

    void on_fan_fanToMaxTemp_valueChanged(int arg1);

    void on_ctrl_rampStartSpeed_valueChanged(int arg1);

    void on_ctrl_rampMidSpeed_valueChanged(int arg1);

    void on_ctrl_rampEndSpeed_valueChanged(int arg1);

    void on_ctrl_minRpm_valueChanged(int arg1);

    void on_ctrl_channel_currentIndexChanged(int index);

    void on_ctrl_probeAffinity_valueChanged(int arg1);

private:
    Ui::gui_SoftwareAutoSetup *ui;

    bool m_isCelcius;

    int m_currChannel;

    bool m_ignoreSignals;

    FanSpeedRamp m_ramp;

    FanControllerData* m_fcdata;
};

bool gui_SoftwareAutoSetup::ignoreSignals(bool ignore)
{
    bool r = m_ignoreSignals;
    m_ignoreSignals = ignore;
    return r;
}



#endif // GUI_SOFTWAREAUTOSETUP_H
