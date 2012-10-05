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

    m_fanCurve.init(fcdata, channel);

    setupAxes(fcdata, channel);
    setupTemperatureCtrlLimits(fcdata);

    setupChannelComboBox();

    xferSettings_toGui(fcdata, channel);

    const QList<QPoint> ramp = m_fanCurve.ramp();

    QCPGraph* gr = new QCPGraph(ui->ctrl_plot->xAxis, ui->ctrl_plot->yAxis);
    gr->setScatterStyle(QCP::ssDisc);

    for (int i = 0; i < ramp.count(); ++i)
    {
        int t;
        t = fcdata.toCurrTempScale(ramp.at(i).x());
        gr->addData(t, ramp.at(i).y());
    }
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

void gui_SoftwareAutoSetup::setupChannelComboBox(void)
{
    for (int i = 0; i < FC_MAX_CHANNELS; ++i)
        ui->ctrl_channel->insertItem(i, tr("Channel %1").arg(i+1), i);
}

void gui_SoftwareAutoSetup::xferSettings_toGui(const FanControllerData& fcdata,
                                               int channel)
{
    const FanCurveData* setup = m_fanCurve.setup();

    int t_fanOn         = fcdata.toCurrTempScale(setup->temperatureF_fanOn);
    int t_rampStart     = fcdata.toCurrTempScale(setup->temperatureF_rampStart);
    int t_rampMid       = fcdata.toCurrTempScale(setup->temperatureF_rampMid);
    int t_rampEnd       = fcdata.toCurrTempScale(setup->temperatureF_rampEnd);
    int t_fanToMax      = fcdata.toCurrTempScale(setup->temperatureF_fanToMax);

    ui->ctrl_channel->setCurrentIndex           (channel);
    ui->ctrl_minRpm->setValue                   (setup->minUsableRpm);
    ui->ctrl_fanOnTemp->setValue                (t_fanOn);
    ui->ctrl_rampStartTemp->setValue            (t_rampStart);
    ui->ctrl_rampMidTemp->setValue              (t_rampMid);
    ui->ctrl_rampEndTemp->setValue              (t_rampEnd);
    ui->fan_fanToMaxTemp->setValue              (t_fanToMax);
    ui->ctrl_rampStartSpeed->setValue           (setup->speed_rampStart);
    ui->ctrl_rampMidSpeed->setValue             (setup->speed_rampMid);
    ui->ctrl_rampEndSpeed->setValue             (setup->speed_rampEnd);

    ui->ctrl_isFanConstantSpeed->setChecked     (setup->fixedRpm);
    ui->ctrl_probeAffinity->setValue            (setup->probeAffinity);
    ui->ctrl_isFanAlwaysOn->setChecked          (!setup->allowFanToTurnOff);
    ui->ctrl_fanOnSpeed->setValue               (setup->temperatureF_fanOn);
}

void gui_SoftwareAutoSetup::xferSettings_fromGui(void)
{

}

void gui_SoftwareAutoSetup::drawPlot(void)
{

}
