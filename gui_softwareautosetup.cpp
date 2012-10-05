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
    xferSettings_toGui(channel);

    const QList<QPoint> ramp = m_fanCurve.ramp();

    QCPGraph* gr = new QCPGraph(ui->ctrl_plot->xAxis, ui->ctrl_plot->yAxis);
    gr->setScatterStyle(QCP::ssDisc);

    for (int i = 0; i < ramp.count(); ++i)
    {
        gr->addData(ramp.at(i).x(), ramp.at(i).y());
    }
}

void gui_SoftwareAutoSetup::setupAxes(const FanControllerData& fcdata, int channel)
{
    FanControllerIO* fc = &ph_fanControllerIO();
    int minProbeTemp = fc->minProbeTemp(fcdata.isCelcius())-10;
    int maxProbeTemp = fc->maxProbeTemp(fcdata.isCelcius())+10;

    ui->ctrl_plot->xAxis->setRange(minProbeTemp, maxProbeTemp);
    ui->ctrl_plot->yAxis->setRange(0, fcdata.maxRPM(channel) + 100);

    /* TEMP : FIXME */
    ui->ctrl_plot->xAxis->setRange(0, 255);
}

void gui_SoftwareAutoSetup::setupTemperatureCtrlLimits(const FanControllerData&)
{

}

void gui_SoftwareAutoSetup::xferSettings_toGui(int channel)
{
    const FanCurveData* setup = m_fanCurve.setup();

    ui->ctrl_channel->setValue                 (channel);
    ui->ctrl_minRpm->setValue                  (setup->minUsableRpm);
    ui->ctrl_fanOnTemp->setValue               (setup->temperatureF_fanOn);
    ui->ctrl_rampStartTemp->setValue           (setup->temperatureF_rampStart);
    ui->ctrl_rampMidTemp->setValue             (setup->temperatureF_rampMid);
    ui->ctrl_rampEndTemp->setValue             (setup->temperatureF_rampEnd);
    ui->fan_fanToMaxTemp->setValue             (setup->temperatureF_fanToMax);
    ui->ctrl_rampStartSpeed->setValue          (setup->speed_rampStart);
    ui->ctrl_rampMidSpeed->setValue            (setup->speed_rampMid);
    ui->ctrl_rampEndSpeed->setValue            (setup->speed_rampEnd);

    ui->ctrl_isFanConstantSpeed->setChecked    (setup->fixedRpm);
    ui->ctrl_probeAffinity->setValue           (setup->probeAffinity);
    ui->ctrl_isFanAlwaysOn->setChecked         (!setup->allowFanToTurnOff);
    ui->ctrl_fanOnSpeed->setValue              (setup->temperatureF_fanOn);

}

void gui_SoftwareAutoSetup::xferSettings_fromGui(void)
{

}

void gui_SoftwareAutoSetup::drawPlot(void)
{

}
