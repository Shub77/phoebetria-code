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

    FanControllerIO* fc = &ph_fanControllerIO();
    int minProbeTemp = fc->minProbeTemp(fcdata.isCelcius())-10;
    int maxProbeTemp = fc->maxProbeTemp(fcdata.isCelcius())+10;

    ui->widget->xAxis->setRange(minProbeTemp, maxProbeTemp);
    ui->widget->yAxis->setRange(0, fcdata.maxRPM(channel) + 100);

    ui->widget->xAxis->setRange(0, 255);

    const QList<QPoint> ramp = m_fanCurve.ramp();

    QCPGraph* gr = new QCPGraph(ui->widget->xAxis, ui->widget->yAxis);
    gr->setScatterStyle(QCP::ssDisc);

    for (int i = 0; i < ramp.count(); ++i)
    {
        gr->addData(ramp.at(i).x(), ramp.at(i).y());
    }
}
