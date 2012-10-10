#include "gui_softwareautosetup.h"
#include "ui_gui_softwareautosetup.h"

#include "fancontrollerdata.h"
#include "phoebetriaapp.h"
#include "bfx-recon/fancontrollerio.h"

gui_SoftwareAutoSetup::gui_SoftwareAutoSetup(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::gui_SoftwareAutoSetup),
    m_ignoreSignals(false)
{
    ui->setupUi(this);
}

gui_SoftwareAutoSetup::~gui_SoftwareAutoSetup()
{
    delete ui;
}

void gui_SoftwareAutoSetup::init(FanControllerData *fcdata)
{

    m_fcdata = fcdata;
    m_isCelcius = fcdata->isCelcius();
    m_currChannel = 0;

    setupChannelComboBox();

    setupAxes(*fcdata, m_currChannel);
    setupTemperatureCtrlLimits(*fcdata);
    setupSpeedCtrlLimits(fcdata->maxRPM(m_currChannel));

    /* Use m_ramp internally and copy to/from fcdata when required */
    m_ramp = fcdata->ramp(m_currChannel);

    xferSettings_toGui(*fcdata, m_currChannel);

    drawPlot();

}

void gui_SoftwareAutoSetup::setupAxes(const FanControllerData& fcdata, int channel)
{
    const FanControllerIO* fc = &ph_fanControllerIO();
    int minProbeTemp = fc->minProbeTemp(fcdata.isCelcius())-10;
    int maxProbeTemp = fc->maxProbeTemp(fcdata.isCelcius())+10;

    ui->ctrl_plot->xAxis->setRange(minProbeTemp, maxProbeTemp);
    ui->ctrl_plot->yAxis->setRange(0, fcdata.maxRPM(channel) + 100);
}

void gui_SoftwareAutoSetup::setupTemperatureCtrlLimits(
        const FanControllerData& fcdata)
{
    const FanControllerIO* fc = &ph_fanControllerIO();

    int t_lowerLimit = fc->minProbeTemp(fcdata.isCelcius());
    int t_upperLimit = fc->maxProbeTemp(fcdata.isCelcius());

    ui->ctrl_fanOnTemp->setMinimum(t_lowerLimit);
    ui->ctrl_fanOnTemp->setMaximum(t_upperLimit);

    ui->ctrl_rampStartTemp->setMinimum(t_lowerLimit);
    ui->ctrl_rampStartTemp->setMaximum(t_upperLimit);

    ui->ctrl_rampMidTemp->setMinimum(t_lowerLimit);
    ui->ctrl_rampMidTemp->setMaximum(t_upperLimit);

    ui->ctrl_rampEndTemp->setMinimum(t_lowerLimit);
    ui->ctrl_rampEndTemp->setMaximum(t_upperLimit);

    ui->fan_fanToMaxTemp->setMinimum(t_lowerLimit);
    ui->fan_fanToMaxTemp->setMaximum(t_upperLimit);
}

void gui_SoftwareAutoSetup::setupSpeedCtrlLimits(int maxRpm)
{
    int min = m_ramp.snapToStepSize(maxRpm * 2/3);
    ui->ctrl_minRpm->setMaximum(min);

    ui->ctrl_rampStartSpeed->setMaximum(maxRpm);
    ui->ctrl_rampMidSpeed->setMaximum(maxRpm);
    ui->ctrl_rampEndSpeed->setMaximum(maxRpm);
}

void gui_SoftwareAutoSetup::setupChannelComboBox(void)
{
    int channelCount = m_fcdata->channelCount();

    bool bs = blockSignals(true);

    for (int i = 0; i < channelCount; ++i)
        ui->ctrl_channel->insertItem(i, tr("Channel %1").arg(i+1), i);

    blockSignals(bs);
}

void gui_SoftwareAutoSetup::xferSettings_toGui(const FanControllerData& fcdata,
                                               int channel)
{
    const FanSpeedRampParameters& setup = m_ramp.rampParameters();

    int t_fanOn         = fcdata.toCurrTempScale(setup.temperatureF_fanOn);
    int t_rampStart     = fcdata.toCurrTempScale(setup.temperatureF_rampStart);
    int t_rampMid       = fcdata.toCurrTempScale(setup.temperatureF_rampMid);
    int t_rampEnd       = fcdata.toCurrTempScale(setup.temperatureF_rampEnd);
    int t_fanToMax      = fcdata.toCurrTempScale(setup.temperatureF_fanToMax);

    bool bs = ignoreSignals(true);

    ui->ctrl_channel->setCurrentIndex           (channel);
    ui->ctrl_minRpm->setValue                   (setup.minUsableRpm);

    ui->ctrl_fanOnTemp->setValue                (t_fanOn);
    ui->ctrl_rampStartTemp->setValue            (t_rampStart);
    ui->ctrl_rampMidTemp->setValue              (t_rampMid);
    ui->ctrl_rampEndTemp->setValue              (t_rampEnd);
    ui->fan_fanToMaxTemp->setValue              (t_fanToMax);

    ui->ctrl_fanOnSpeed->setValue               (setup.speed_fanOn);
    ui->ctrl_rampStartSpeed->setValue           (setup.speed_rampStart);
    ui->ctrl_rampMidSpeed->setValue             (setup.speed_rampMid);
    ui->ctrl_rampEndSpeed->setValue             (setup.speed_rampEnd);

    ui->ctrl_isFanConstantSpeed->setChecked     (setup.fixedRpm);
    ui->ctrl_probeAffinity->setValue            (setup.probeAffinity);
    ui->ctrl_isFanAlwaysOn->setChecked          (!setup.allowFanToTurnOff);

    ignoreSignals(bs);

}

void gui_SoftwareAutoSetup::xferSettings_fromGui(const FanControllerData& fcdata)
{
#if 0
    FanSpeedRampParameters* setup = m_ramp.setup();

    int t_fanOn     = fcdata.toCurrTempScale(ui->ctrl_fanOnTemp->value());
    int t_rampStart = fcdata.toCurrTempScale(ui->ctrl_rampStartTemp->value());
    int t_rampMid   = fcdata.toCurrTempScale(ui->ctrl_rampMidTemp->value());
    int t_rampEnd   = fcdata.toCurrTempScale(ui->ctrl_rampEndTemp->value());
    int t_fanToMax  = fcdata.toCurrTempScale(ui->fan_fanToMaxTemp->value());

    setup->minUsableRpm             = ui->ctrl_minRpm->value();

    setup->temperatureF_fanOn       = t_fanOn;
    setup->temperatureF_rampStart   = t_rampStart;
    setup->temperatureF_rampMid     = t_rampMid;
    setup->temperatureF_rampEnd     = t_rampEnd;
    setup->temperatureF_fanToMax    = t_fanToMax;

    setup->speed_fanOn              = ui->ctrl_fanOnSpeed->value();
    setup->speed_rampStart          = ui->ctrl_rampStartSpeed->value();
    setup->speed_rampMid            = ui->ctrl_rampMidSpeed->value();
    setup->speed_rampEnd            = ui->ctrl_rampEndSpeed->value();

    setup->fixedRpm                 = ui->ctrl_isFanConstantSpeed->isChecked();
    setup->probeAffinity            = ui->ctrl_probeAffinity->value();
    setup->allowFanToTurnOff        = !ui->ctrl_isFanAlwaysOn->isChecked();
#endif
}

void gui_SoftwareAutoSetup::drawPlot(void)
{
    const QList<QPoint> ramp = m_ramp.ramp();

    //ui->ctrl_plot->clearGraphs();
    ui->ctrl_plot->removeGraph(0);

    QCPGraph* gr = ui->ctrl_plot->addGraph();

    gr->setScatterStyle(QCP::ssDisc);
    gr->setLineStyle(QCPGraph::lsStepLeft);

    for (int i = 0; i < ramp.count(); ++i)
    {
        double t;
        t = m_fcdata->toCurrTempScaleReal(ramp.at(i).x());
        gr->addData(t, ramp.at(i).y());
    }

    ui->ctrl_plot->replot();
}


void gui_SoftwareAutoSetup::regenerateCurve(void)
{
    m_ramp.generateCurve(m_fcdata->fanChannelSettings(m_currChannel).maxRPM());
    drawPlot();
}

int gui_SoftwareAutoSetup::tempInF(int t) const
{
    return m_isCelcius ? m_fcdata->toFahrenheit(t) : t;
}


void gui_SoftwareAutoSetup::on_ctrl_rampStartTemp_valueChanged(int arg1)
{
    if (m_ignoreSignals) return;
    m_ramp.setSpeedRampStart(tempInF(arg1));
    regenerateCurve();

}

void gui_SoftwareAutoSetup::on_ctrl_rampMidTemp_valueChanged(int arg1)
{
    if (m_ignoreSignals) return;
    m_ramp.setTemperatureRampMid(tempInF(arg1));
    regenerateCurve();
}

void gui_SoftwareAutoSetup::on_ctrl_rampEndTemp_valueChanged(int arg1)
{
    if (m_ignoreSignals) return;
    m_ramp.setTemperatureRampEnd(tempInF(arg1));
    regenerateCurve();
}

void gui_SoftwareAutoSetup::on_fan_fanToMaxTemp_valueChanged(int arg1)
{
    if (m_ignoreSignals) return;
    m_ramp.setTemperatureFanToMax(tempInF(arg1));
    regenerateCurve();
}

void gui_SoftwareAutoSetup::on_ctrl_rampStartSpeed_valueChanged(int arg1)
{
    if (m_ignoreSignals) return;
    m_ramp.setSpeedRampStart(arg1);
    regenerateCurve();
}

void gui_SoftwareAutoSetup::on_ctrl_rampMidSpeed_valueChanged(int arg1)
{
    if (m_ignoreSignals) return;
    m_ramp.setSpeedRampMid(arg1);
    regenerateCurve();
}

void gui_SoftwareAutoSetup::on_ctrl_rampEndSpeed_valueChanged(int arg1)
{
    if (m_ignoreSignals) return;
    m_ramp.setSpeedRampEnd(arg1);
    regenerateCurve();
}

void gui_SoftwareAutoSetup::on_ctrl_minRpm_valueChanged(int arg1)
{
    if (m_ignoreSignals) return;

    m_ramp.setMinUsableRpm(arg1);

    // TODO possibly check all speed values

    /* Could check other values here, but maybe not worth it...
       User is probably expecting to have to change the other values
       anyway if they are wrong.
     */
    if (m_ramp.rampParameters().speed_fanOn < arg1)
    {
        m_ramp.setSpeedFanOn(arg1);
        bool bs = ui->ctrl_fanOnSpeed->blockSignals(true);
        ui->ctrl_fanOnSpeed->setValue(arg1);
        ui->ctrl_fanOnSpeed->blockSignals(bs);
    }
    if (m_ramp.rampParameters().speed_rampStart < arg1)
    {
        m_ramp.setSpeedRampStart(arg1);
        bool bs = ui->ctrl_rampStartSpeed->blockSignals(true);
        ui->ctrl_rampStartSpeed->setValue(arg1);
        ui->ctrl_rampStartSpeed->blockSignals(bs);
    }

    regenerateCurve();
}

void gui_SoftwareAutoSetup::on_ctrl_channel_currentIndexChanged(int index)
{
    bool bs = ignoreSignals(true);

    m_currChannel = index;
    m_ramp = m_fcdata->ramp(index);
    setupAxes(*m_fcdata, index);
    setupTemperatureCtrlLimits(*m_fcdata);
    setupSpeedCtrlLimits(m_fcdata->maxRPM(m_currChannel));
    drawPlot();
    xferSettings_toGui(*m_fcdata, index);
    ignoreSignals(bs);
}

void gui_SoftwareAutoSetup::on_ctrl_probeAffinity_valueChanged(int arg1)
{
    m_ramp.setProbeAffinity(arg1);
}
