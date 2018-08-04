/********************************************************************************
** Form generated from reading UI file 'gui_softwareautosetup.ui'
**
** Created by: Qt User Interface Compiler version 4.8.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GUI_SOFTWAREAUTOSETUP_H
#define UI_GUI_SOFTWAREAUTOSETUP_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QComboBox>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QFrame>
#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QSpacerItem>
#include <QtGui/QSpinBox>
#include <QtGui/QTabWidget>
#include <QtGui/QTextBrowser>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>
#include "qcustomplot.h"

QT_BEGIN_NAMESPACE

class Ui_gui_SoftwareAutoSetup
{
public:
    QVBoxLayout *verticalLayout;
    QCustomPlot *ctrl_plot;
    QFrame *line;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_10;
    QComboBox *ctrl_channel;
    QLineEdit *ctrl_channelName;
    QTabWidget *tabWidget;
    QWidget *tab;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_2;
    QGridLayout *gridLayout_2;
    QLabel *label_probeAffinity;
    QLabel *label_11;
    QLabel *label_12;
    QSpinBox *ctrl_rampMidSpeed;
    QLabel *label_13;
    QLabel *label_14;
    QSpinBox *ctrl_rampEndSpeed;
    QSpinBox *ctrl_fanOnTemp;
    QSpinBox *ctrl_rampStartTemp;
    QSpinBox *fan_fanToMaxTemp;
    QLabel *label_15;
    QLabel *label_16;
    QSpinBox *ctrl_rampStartSpeed;
    QLabel *label_17;
    QSpinBox *ctrl_rampEndTemp;
    QLabel *label_18;
    QSpinBox *ctrl_rampMidTemp;
    QSpinBox *ctrl_minRpm;
    QCheckBox *ctrl_isFanConstantSpeed;
    QSpinBox *ctrl_probeAffinity;
    QCheckBox *ctrl_isFanAlwaysOn;
    QSpinBox *ctrl_fanOnSpeed;
    QSpacerItem *verticalSpacer;
    QWidget *tab_2;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout;
    QLabel *label_19;
    QSpinBox *ctrl_hysteresisUp;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_20;
    QSpinBox *ctrl_hysteresisDown;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_21;
    QSpinBox *ctrl_hysteresisFanOff;
    QTextBrowser *ctrl_explanation;
    QSpacerItem *verticalSpacer_2;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *gui_SoftwareAutoSetup)
    {
        if (gui_SoftwareAutoSetup->objectName().isEmpty())
            gui_SoftwareAutoSetup->setObjectName(QString::fromUtf8("gui_SoftwareAutoSetup"));
        gui_SoftwareAutoSetup->resize(518, 564);
        gui_SoftwareAutoSetup->setSizeGripEnabled(true);
        gui_SoftwareAutoSetup->setModal(false);
        verticalLayout = new QVBoxLayout(gui_SoftwareAutoSetup);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        ctrl_plot = new QCustomPlot(gui_SoftwareAutoSetup);
        ctrl_plot->setObjectName(QString::fromUtf8("ctrl_plot"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(ctrl_plot->sizePolicy().hasHeightForWidth());
        ctrl_plot->setSizePolicy(sizePolicy);
        ctrl_plot->setMinimumSize(QSize(500, 250));
        ctrl_plot->setStyleSheet(QString::fromUtf8(""));

        verticalLayout->addWidget(ctrl_plot);

        line = new QFrame(gui_SoftwareAutoSetup);
        line->setObjectName(QString::fromUtf8("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        verticalLayout->addWidget(line);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        label_10 = new QLabel(gui_SoftwareAutoSetup);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_5->addWidget(label_10);

        ctrl_channel = new QComboBox(gui_SoftwareAutoSetup);
        ctrl_channel->setObjectName(QString::fromUtf8("ctrl_channel"));

        horizontalLayout_5->addWidget(ctrl_channel);

        ctrl_channelName = new QLineEdit(gui_SoftwareAutoSetup);
        ctrl_channelName->setObjectName(QString::fromUtf8("ctrl_channelName"));
        ctrl_channelName->setStyleSheet(QString::fromUtf8("background:transparent"));
        ctrl_channelName->setFrame(false);
        ctrl_channelName->setReadOnly(true);

        horizontalLayout_5->addWidget(ctrl_channelName);


        verticalLayout->addLayout(horizontalLayout_5);

        tabWidget = new QTabWidget(gui_SoftwareAutoSetup);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        verticalLayout_2 = new QVBoxLayout(tab);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        gridLayout_2 = new QGridLayout();
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        label_probeAffinity = new QLabel(tab);
        label_probeAffinity->setObjectName(QString::fromUtf8("label_probeAffinity"));
        label_probeAffinity->setEnabled(true);
        label_probeAffinity->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_2->addWidget(label_probeAffinity, 1, 2, 1, 1);

        label_11 = new QLabel(tab);
        label_11->setObjectName(QString::fromUtf8("label_11"));
        QFont font;
        font.setBold(true);
        font.setWeight(75);
        label_11->setFont(font);

        gridLayout_2->addWidget(label_11, 2, 2, 1, 1);

        label_12 = new QLabel(tab);
        label_12->setObjectName(QString::fromUtf8("label_12"));
        label_12->setFont(font);

        gridLayout_2->addWidget(label_12, 2, 1, 1, 1);

        ctrl_rampMidSpeed = new QSpinBox(tab);
        ctrl_rampMidSpeed->setObjectName(QString::fromUtf8("ctrl_rampMidSpeed"));
        ctrl_rampMidSpeed->setMaximum(65500);
        ctrl_rampMidSpeed->setSingleStep(100);

        gridLayout_2->addWidget(ctrl_rampMidSpeed, 5, 2, 1, 1);

        label_13 = new QLabel(tab);
        label_13->setObjectName(QString::fromUtf8("label_13"));
        label_13->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_2->addWidget(label_13, 4, 0, 1, 1);

        label_14 = new QLabel(tab);
        label_14->setObjectName(QString::fromUtf8("label_14"));
        label_14->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_2->addWidget(label_14, 5, 0, 1, 1);

        ctrl_rampEndSpeed = new QSpinBox(tab);
        ctrl_rampEndSpeed->setObjectName(QString::fromUtf8("ctrl_rampEndSpeed"));
        ctrl_rampEndSpeed->setMaximum(65500);
        ctrl_rampEndSpeed->setSingleStep(100);

        gridLayout_2->addWidget(ctrl_rampEndSpeed, 6, 2, 1, 1);

        ctrl_fanOnTemp = new QSpinBox(tab);
        ctrl_fanOnTemp->setObjectName(QString::fromUtf8("ctrl_fanOnTemp"));
        ctrl_fanOnTemp->setEnabled(false);
        ctrl_fanOnTemp->setMaximum(255);
        ctrl_fanOnTemp->setSingleStep(1);

        gridLayout_2->addWidget(ctrl_fanOnTemp, 3, 1, 1, 1);

        ctrl_rampStartTemp = new QSpinBox(tab);
        ctrl_rampStartTemp->setObjectName(QString::fromUtf8("ctrl_rampStartTemp"));
        ctrl_rampStartTemp->setMaximum(255);
        ctrl_rampStartTemp->setSingleStep(1);

        gridLayout_2->addWidget(ctrl_rampStartTemp, 4, 1, 1, 1);

        fan_fanToMaxTemp = new QSpinBox(tab);
        fan_fanToMaxTemp->setObjectName(QString::fromUtf8("fan_fanToMaxTemp"));
        fan_fanToMaxTemp->setMinimumSize(QSize(120, 0));
        fan_fanToMaxTemp->setMaximum(255);
        fan_fanToMaxTemp->setSingleStep(1);

        gridLayout_2->addWidget(fan_fanToMaxTemp, 7, 1, 1, 1);

        label_15 = new QLabel(tab);
        label_15->setObjectName(QString::fromUtf8("label_15"));
        label_15->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_2->addWidget(label_15, 6, 0, 1, 1);

        label_16 = new QLabel(tab);
        label_16->setObjectName(QString::fromUtf8("label_16"));
        label_16->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_2->addWidget(label_16, 7, 0, 1, 1);

        ctrl_rampStartSpeed = new QSpinBox(tab);
        ctrl_rampStartSpeed->setObjectName(QString::fromUtf8("ctrl_rampStartSpeed"));
        ctrl_rampStartSpeed->setMaximum(65500);
        ctrl_rampStartSpeed->setSingleStep(100);

        gridLayout_2->addWidget(ctrl_rampStartSpeed, 4, 2, 1, 1);

        label_17 = new QLabel(tab);
        label_17->setObjectName(QString::fromUtf8("label_17"));
        label_17->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_2->addWidget(label_17, 1, 0, 1, 1);

        ctrl_rampEndTemp = new QSpinBox(tab);
        ctrl_rampEndTemp->setObjectName(QString::fromUtf8("ctrl_rampEndTemp"));
        ctrl_rampEndTemp->setMaximum(255);
        ctrl_rampEndTemp->setSingleStep(1);

        gridLayout_2->addWidget(ctrl_rampEndTemp, 6, 1, 1, 1);

        label_18 = new QLabel(tab);
        label_18->setObjectName(QString::fromUtf8("label_18"));
        label_18->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_2->addWidget(label_18, 3, 0, 1, 1);

        ctrl_rampMidTemp = new QSpinBox(tab);
        ctrl_rampMidTemp->setObjectName(QString::fromUtf8("ctrl_rampMidTemp"));
        ctrl_rampMidTemp->setMaximum(255);
        ctrl_rampMidTemp->setSingleStep(1);

        gridLayout_2->addWidget(ctrl_rampMidTemp, 5, 1, 1, 1);

        ctrl_minRpm = new QSpinBox(tab);
        ctrl_minRpm->setObjectName(QString::fromUtf8("ctrl_minRpm"));
        ctrl_minRpm->setMaximum(65500);
        ctrl_minRpm->setSingleStep(100);

        gridLayout_2->addWidget(ctrl_minRpm, 1, 1, 1, 1);

        ctrl_isFanConstantSpeed = new QCheckBox(tab);
        ctrl_isFanConstantSpeed->setObjectName(QString::fromUtf8("ctrl_isFanConstantSpeed"));
        ctrl_isFanConstantSpeed->setEnabled(false);

        gridLayout_2->addWidget(ctrl_isFanConstantSpeed, 4, 3, 1, 1);

        ctrl_probeAffinity = new QSpinBox(tab);
        ctrl_probeAffinity->setObjectName(QString::fromUtf8("ctrl_probeAffinity"));
        ctrl_probeAffinity->setEnabled(true);
        ctrl_probeAffinity->setMinimum(1);
        ctrl_probeAffinity->setMaximum(5);

        gridLayout_2->addWidget(ctrl_probeAffinity, 1, 3, 1, 1);

        ctrl_isFanAlwaysOn = new QCheckBox(tab);
        ctrl_isFanAlwaysOn->setObjectName(QString::fromUtf8("ctrl_isFanAlwaysOn"));
        ctrl_isFanAlwaysOn->setChecked(true);

        gridLayout_2->addWidget(ctrl_isFanAlwaysOn, 3, 3, 1, 1);

        ctrl_fanOnSpeed = new QSpinBox(tab);
        ctrl_fanOnSpeed->setObjectName(QString::fromUtf8("ctrl_fanOnSpeed"));
        ctrl_fanOnSpeed->setEnabled(false);
        ctrl_fanOnSpeed->setMaximum(65500);
        ctrl_fanOnSpeed->setSingleStep(100);

        gridLayout_2->addWidget(ctrl_fanOnSpeed, 3, 2, 1, 1);


        horizontalLayout_2->addLayout(gridLayout_2);


        verticalLayout_2->addLayout(horizontalLayout_2);

        verticalSpacer = new QSpacerItem(20, 14, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer);

        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QString::fromUtf8("tab_2"));
        verticalLayout_3 = new QVBoxLayout(tab_2);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label_19 = new QLabel(tab_2);
        label_19->setObjectName(QString::fromUtf8("label_19"));

        horizontalLayout->addWidget(label_19);

        ctrl_hysteresisUp = new QSpinBox(tab_2);
        ctrl_hysteresisUp->setObjectName(QString::fromUtf8("ctrl_hysteresisUp"));
        ctrl_hysteresisUp->setMaximum(10);

        horizontalLayout->addWidget(ctrl_hysteresisUp);


        verticalLayout_3->addLayout(horizontalLayout);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label_20 = new QLabel(tab_2);
        label_20->setObjectName(QString::fromUtf8("label_20"));

        horizontalLayout_3->addWidget(label_20);

        ctrl_hysteresisDown = new QSpinBox(tab_2);
        ctrl_hysteresisDown->setObjectName(QString::fromUtf8("ctrl_hysteresisDown"));
        ctrl_hysteresisDown->setMaximum(10);

        horizontalLayout_3->addWidget(ctrl_hysteresisDown);


        verticalLayout_3->addLayout(horizontalLayout_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        label_21 = new QLabel(tab_2);
        label_21->setObjectName(QString::fromUtf8("label_21"));

        horizontalLayout_4->addWidget(label_21);

        ctrl_hysteresisFanOff = new QSpinBox(tab_2);
        ctrl_hysteresisFanOff->setObjectName(QString::fromUtf8("ctrl_hysteresisFanOff"));
        ctrl_hysteresisFanOff->setMaximum(10);

        horizontalLayout_4->addWidget(ctrl_hysteresisFanOff);


        verticalLayout_3->addLayout(horizontalLayout_4);

        ctrl_explanation = new QTextBrowser(tab_2);
        ctrl_explanation->setObjectName(QString::fromUtf8("ctrl_explanation"));

        verticalLayout_3->addWidget(ctrl_explanation);

        verticalSpacer_2 = new QSpacerItem(20, 27, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_3->addItem(verticalSpacer_2);

        tabWidget->addTab(tab_2, QString());

        verticalLayout->addWidget(tabWidget);

        buttonBox = new QDialogButtonBox(gui_SoftwareAutoSetup);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout->addWidget(buttonBox);

        QWidget::setTabOrder(buttonBox, ctrl_channel);
        QWidget::setTabOrder(ctrl_channel, ctrl_channelName);
        QWidget::setTabOrder(ctrl_channelName, ctrl_minRpm);
        QWidget::setTabOrder(ctrl_minRpm, ctrl_probeAffinity);
        QWidget::setTabOrder(ctrl_probeAffinity, ctrl_fanOnTemp);
        QWidget::setTabOrder(ctrl_fanOnTemp, ctrl_rampStartTemp);
        QWidget::setTabOrder(ctrl_rampStartTemp, ctrl_rampMidTemp);
        QWidget::setTabOrder(ctrl_rampMidTemp, ctrl_rampEndTemp);
        QWidget::setTabOrder(ctrl_rampEndTemp, fan_fanToMaxTemp);
        QWidget::setTabOrder(fan_fanToMaxTemp, ctrl_fanOnSpeed);
        QWidget::setTabOrder(ctrl_fanOnSpeed, ctrl_rampStartSpeed);
        QWidget::setTabOrder(ctrl_rampStartSpeed, ctrl_rampMidSpeed);
        QWidget::setTabOrder(ctrl_rampMidSpeed, ctrl_rampEndSpeed);
        QWidget::setTabOrder(ctrl_rampEndSpeed, ctrl_isFanAlwaysOn);
        QWidget::setTabOrder(ctrl_isFanAlwaysOn, ctrl_isFanConstantSpeed);
        QWidget::setTabOrder(ctrl_isFanConstantSpeed, tabWidget);
        QWidget::setTabOrder(tabWidget, ctrl_hysteresisUp);
        QWidget::setTabOrder(ctrl_hysteresisUp, ctrl_hysteresisDown);
        QWidget::setTabOrder(ctrl_hysteresisDown, ctrl_hysteresisFanOff);
        QWidget::setTabOrder(ctrl_hysteresisFanOff, ctrl_explanation);

        retranslateUi(gui_SoftwareAutoSetup);
        QObject::connect(buttonBox, SIGNAL(accepted()), gui_SoftwareAutoSetup, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), gui_SoftwareAutoSetup, SLOT(reject()));

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(gui_SoftwareAutoSetup);
    } // setupUi

    void retranslateUi(QDialog *gui_SoftwareAutoSetup)
    {
        gui_SoftwareAutoSetup->setWindowTitle(QApplication::translate("gui_SoftwareAutoSetup", "Software Auto Setup", 0, QApplication::UnicodeUTF8));
        label_10->setText(QApplication::translate("gui_SoftwareAutoSetup", "Channel", 0, QApplication::UnicodeUTF8));
        ctrl_channelName->setText(QString());
        label_probeAffinity->setText(QApplication::translate("gui_SoftwareAutoSetup", "Probe affinity", 0, QApplication::UnicodeUTF8));
        label_11->setText(QApplication::translate("gui_SoftwareAutoSetup", "Speeds", 0, QApplication::UnicodeUTF8));
        label_12->setText(QApplication::translate("gui_SoftwareAutoSetup", "Temperatures", 0, QApplication::UnicodeUTF8));
        label_13->setText(QApplication::translate("gui_SoftwareAutoSetup", "Ramp start", 0, QApplication::UnicodeUTF8));
        label_14->setText(QApplication::translate("gui_SoftwareAutoSetup", "Ramp mid", 0, QApplication::UnicodeUTF8));
        label_15->setText(QApplication::translate("gui_SoftwareAutoSetup", "Ramp end", 0, QApplication::UnicodeUTF8));
        label_16->setText(QApplication::translate("gui_SoftwareAutoSetup", "Fan to max RPM", 0, QApplication::UnicodeUTF8));
        label_17->setText(QApplication::translate("gui_SoftwareAutoSetup", "Minimum settable RPM", 0, QApplication::UnicodeUTF8));
        label_18->setText(QApplication::translate("gui_SoftwareAutoSetup", "Turn fan on at", 0, QApplication::UnicodeUTF8));
        ctrl_isFanConstantSpeed->setText(QApplication::translate("gui_SoftwareAutoSetup", "Constant speed", 0, QApplication::UnicodeUTF8));
        ctrl_isFanAlwaysOn->setText(QApplication::translate("gui_SoftwareAutoSetup", "Always on", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("gui_SoftwareAutoSetup", "Channel Settings", 0, QApplication::UnicodeUTF8));
        label_19->setText(QApplication::translate("gui_SoftwareAutoSetup", "Hysterisis Up", 0, QApplication::UnicodeUTF8));
        label_20->setText(QApplication::translate("gui_SoftwareAutoSetup", "Hysterisis Down", 0, QApplication::UnicodeUTF8));
        label_21->setText(QApplication::translate("gui_SoftwareAutoSetup", "Hysterisis Fan Off", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("gui_SoftwareAutoSetup", "Advanced", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class gui_SoftwareAutoSetup: public Ui_gui_SoftwareAutoSetup {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GUI_SOFTWAREAUTOSETUP_H
