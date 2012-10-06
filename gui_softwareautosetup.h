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
    
    void init(void);

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

private slots:

    void on_ctrl_rampStartTemp_valueChanged(int arg1);

    void on_ctrl_rampMidTemp_valueChanged(int arg1);

    void on_ctrl_rampEndTemp_valueChanged(int arg1);

    void on_fan_fanToMaxTemp_valueChanged(int arg1);

    void on_ctrl_rampStartSpeed_valueChanged(int arg1);

    void on_ctrl_rampMidSpeed_valueChanged(int arg1);

    void on_ctrl_rampEndSpeed_valueChanged(int arg1);

    void on_ctrl_minRpm_valueChanged(int arg1);

private:
    Ui::gui_SoftwareAutoSetup *ui;

    FanSpeedRamp m_fanCurve;

    bool m_isCelcius;

    const FanControllerData* m_fcdata;
};




#endif // GUI_SOFTWAREAUTOSETUP_H
