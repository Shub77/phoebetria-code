#include "gui_softwareautosetup.h"
#include "ui_gui_softwareautosetup.h"

#include "fancontrollerdata.h"
#include "phoebetriaapp.h"
#include "bfx-recon/fancontrollerio.h"

gui_SoftwareAutoSetup::gui_SoftwareAutoSetup(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::gui_SoftwareAutoSetup)
{
    ui->setupUi(this);
}

gui_SoftwareAutoSetup::~gui_SoftwareAutoSetup()
{
    delete ui;
}

void gui_SoftwareAutoSetup::init(void)
{
    const FanControllerData& fcdata = ph_fanControllerData();

    int channel = 0;

    m_fcdata = &fcdata;

    m_isCelcius = fcdata.isCelcius();

    m_fanCurve.init(fcdata, channel);

    setupAxes(fcdata, channel);
    setupTemperatureCtrlLimits(fcdata);
    setupSpeedCtrlLimits(fcdata.maxRPM(channel));

    setupChannelComboBox();

    xferSettings_toGui(fcdata, channel);

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
    ui->ctrl_minRpm->setMaximum(maxRpm);
    ui->ctrl_rampStartSpeed->setMaximum(maxRpm);
    ui->ctrl_rampMidSpeed->setMaximum(maxRpm);
    ui->ctrl_rampEndSpeed->setMaximum(maxRpm);
}

void gui_SoftwareAutoSetup::setupChannelComboBox(void)
{
    for (int i = 0; i < FC_MAX_CHANNELS; ++i)
        ui->ctrl_channel->insertItem(i, tr("Channel %1").arg(i+1), i);
}

void gui_SoftwareAutoSetup::xferSettings_toGui(const FanControllerData& fcdata,
                                               int channel)
{
    const FanSpeedRampData* setup = m_fanCurve.setup();

    int t_fanOn         = fcdata.toCurrTempScale(setup->temperatureF_fanOn);
    int t_rampStart     = fcdata.toCurrTempScale(setup->temperatureF_rampStart);
    int t_rampMid       = fcdata.toCurrTempScale(setup->temperatureF_rampMid);
    int t_rampEnd       = fcdata.toCurrTempScale(setup->temperatureF_rampEnd);
    int t_fanToMax      = fcdata.toCurrTempScale(setup->temperatureF_fanToMax);

    bool bs = blockSignals(true);

    ui->ctrl_channel->setCurrentIndex           (channel);
    ui->ctrl_minRpm->setValue                   (setup->minUsableRpm);

    ui->ctrl_fanOnTemp->setValue                (t_fanOn);
    ui->ctrl_rampStartTemp->setValue            (t_rampStart);
    ui->ctrl_rampMidTemp->setValue              (t_rampMid);
    ui->ctrl_rampEndTemp->setValue              (t_rampEnd);
    ui->fan_fanToMaxTemp->setValue              (t_fanToMax);

    ui->ctrl_fanOnSpeed->setValue               (setup->speed_fanOn);
    ui->ctrl_rampStartSpeed->setValue           (setup->speed_rampStart);
    ui->ctrl_rampMidSpeed->setValue             (setup->speed_rampMid);
    ui->ctrl_rampEndSpeed->setValue             (setup->speed_rampEnd);

    ui->ctrl_isFanConstantSpeed->setChecked     (setup->fixedRpm);
    ui->ctrl_probeAffinity->setValue            (setup->probeAffinity);
    ui->ctrl_isFanAlwaysOn->setChecked          (!setup->allowFanToTurnOff);

    blockSignals(bs);

}

void gui_SoftwareAutoSetup::xferSettings_fromGui(const FanControllerData& fcdata)
{
    FanSpeedRampData* setup = m_fanCurve.setup();

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

}

void gui_SoftwareAutoSetup::drawPlot(void)
{
    const QList<QPoint> ramp = m_fanCurve.ramp();

    //ui->ctrl_plot->clearGraphs();
    ui->ctrl_plot->removeGraph(0);

    QCPGraph* gr = ui->ctrl_plot->addGraph();

    gr->setScatterStyle(QCP::ssDisc);

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
    int channel = 0;        // FIXME

    m_fanCurve.generateCurve(m_fcdata->fanChannelSettings(channel).maxRPM());
    drawPlot();
}

int gui_SoftwareAutoSetup::tempInF(int t) const
{
    return m_isCelcius ? m_fcdata->toFahrenheit(t) : t;
}


void gui_SoftwareAutoSetup::on_ctrl_rampStartTemp_valueChanged(int arg1)
{
    m_fanCurve.setup()->temperatureF_rampStart = tempInF(arg1);
    regenerateCurve();

}

void gui_SoftwareAutoSetup::on_ctrl_rampMidTemp_valueChanged(int arg1)
{
    m_fanCurve.setup()->temperatureF_rampMid = tempInF(arg1);
    regenerateCurve();
}

void gui_SoftwareAutoSetup::on_ctrl_rampEndTemp_valueChanged(int arg1)
{
    m_fanCurve.setup()->temperatureF_rampEnd = tempInF(arg1);
    regenerateCurve();
}

void gui_SoftwareAutoSetup::on_fan_fanToMaxTemp_valueChanged(int arg1)
{
    m_fanCurve.setup()->temperatureF_fanToMax = tempInF(arg1);
    regenerateCurve();
}

void gui_SoftwareAutoSetup::on_ctrl_rampStartSpeed_valueChanged(int arg1)
{
    m_fanCurve.setup()->speed_rampStart = arg1;
    regenerateCurve();
}

void gui_SoftwareAutoSetup::on_ctrl_rampMidSpeed_valueChanged(int arg1)
{
    m_fanCurve.setup()->speed_rampMid = arg1;
    regenerateCurve();
}

void gui_SoftwareAutoSetup::on_ctrl_rampEndSpeed_valueChanged(int arg1)
{
    m_fanCurve.setup()->speed_rampEnd = arg1;
    regenerateCurve();
}
