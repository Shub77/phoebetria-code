/********************************************************************************
** Form generated from reading UI file 'gui_mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 4.8.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GUI_MAINWINDOW_H
#define UI_GUI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QFrame>
#include <QtGui/QGraphicsView>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QMainWindow>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QSlider>
#include <QtGui/QSpacerItem>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_gui_MainWindow
{
public:
    QAction *actionAbout;
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout_9;
    QHBoxLayout *horizontalLayout_12;
    QGraphicsView *ctrl_logoAndStatus;
    QVBoxLayout *verticalLayout_7;
    QGroupBox *groupBox;
    QHBoxLayout *horizontalLayout_8;
    QVBoxLayout *verticalLayout_11;
    QLabel *lbl_activeProfile;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButton_2;
    QPushButton *pushButton;
    QPushButton *ctrl_syncGui;
    QVBoxLayout *verticalLayout_6;
    QFrame *frame_3;
    QHBoxLayout *horizontalLayout_18;
    QPushButton *ctrl_tempScaleToggleBtn;
    QPushButton *ctrl_isAudibleAlarmBtn;
    QFrame *frame_2;
    QHBoxLayout *horizontalLayout_19;
    QPushButton *ctrl_isManualBtn;
    QPushButton *ctrl_ModifyProfile;
    QFrame *frame;
    QHBoxLayout *horizontalLayout;
    QPushButton *ctrl_isSoftwareControlBtn;
    QPushButton *ctrl_configSoftwareAutoBtn;
    QHBoxLayout *horizontalLayout_17;
    QGroupBox *groupBox_channel1;
    QVBoxLayout *verticalLayout;
    QVBoxLayout *layout_probe1Temp;
    QLineEdit *ctrl_probe1Temp;
    QHBoxLayout *layout_channel1targetspeedSlider;
    QSlider *ctrl_channel1speedSlider;
    QSpacerItem *verticalSpacer_3;
    QPushButton *ctrl_channel1speed;
    QVBoxLayout *layout_channel1Select;
    QPushButton *ctrl_channel1Select;
    QPushButton *ctrl_channel1AlarmTemp;
    QGroupBox *groupBox_channel2;
    QVBoxLayout *verticalLayout_4;
    QVBoxLayout *layout_probe2Temp;
    QLineEdit *ctrl_probe2Temp;
    QHBoxLayout *horizontalLayout_11;
    QSlider *ctrl_channel2speedSlider;
    QSpacerItem *verticalSpacer_6;
    QPushButton *ctrl_channel2speed;
    QVBoxLayout *layout_channel2Select;
    QPushButton *ctrl_channel2Select;
    QPushButton *ctrl_channel2AlarmTemp;
    QGroupBox *groupBox_channel3;
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *layout_probe3Temp;
    QLineEdit *ctrl_probe3Temp;
    QHBoxLayout *horizontalLayout_5;
    QSlider *ctrl_channel3speedSlider;
    QSpacerItem *verticalSpacer_4;
    QPushButton *ctrl_channel3speed;
    QVBoxLayout *layout_channel3Select;
    QPushButton *ctrl_channel3Select;
    QPushButton *ctrl_channel3AlarmTemp;
    QGroupBox *groupBox_channel4;
    QVBoxLayout *verticalLayout_5;
    QVBoxLayout *layout_probe4Temp;
    QLineEdit *ctrl_probe4Temp;
    QHBoxLayout *horizontalLayout_14;
    QSlider *ctrl_channel4speedSlider;
    QSpacerItem *verticalSpacer_7;
    QPushButton *ctrl_channel4speed;
    QVBoxLayout *layout_channel4Select;
    QPushButton *ctrl_channel4Select;
    QPushButton *ctrl_channel4AlarmTemp;
    QGroupBox *groupBox_channel5;
    QVBoxLayout *verticalLayout_3;
    QVBoxLayout *layout_probe5Temp;
    QLineEdit *ctrl_probe5Temp;
    QHBoxLayout *horizontalLayout_30;
    QSlider *ctrl_channel5speedSlider;
    QSpacerItem *verticalSpacer_5;
    QPushButton *ctrl_channel5speed;
    QVBoxLayout *layout_channel5Select;
    QPushButton *ctrl_channel5Select;
    QPushButton *ctrl_channel5AlarmTemp;
    QMenuBar *menuBar;

    void setupUi(QMainWindow *gui_MainWindow)
    {
        if (gui_MainWindow->objectName().isEmpty())
            gui_MainWindow->setObjectName(QString::fromUtf8("gui_MainWindow"));
        gui_MainWindow->resize(455, 512);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(gui_MainWindow->sizePolicy().hasHeightForWidth());
        gui_MainWindow->setSizePolicy(sizePolicy);
        gui_MainWindow->setMinimumSize(QSize(0, 0));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Images/phoebetria_icon_16.png"), QSize(), QIcon::Normal, QIcon::Off);
        gui_MainWindow->setWindowIcon(icon);
        gui_MainWindow->setUnifiedTitleAndToolBarOnMac(false);
        actionAbout = new QAction(gui_MainWindow);
        actionAbout->setObjectName(QString::fromUtf8("actionAbout"));
        actionAbout->setMenuRole(QAction::AboutRole);
        centralWidget = new QWidget(gui_MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        verticalLayout_9 = new QVBoxLayout(centralWidget);
        verticalLayout_9->setSpacing(6);
        verticalLayout_9->setContentsMargins(11, 11, 11, 11);
        verticalLayout_9->setObjectName(QString::fromUtf8("verticalLayout_9"));
        horizontalLayout_12 = new QHBoxLayout();
        horizontalLayout_12->setSpacing(2);
        horizontalLayout_12->setContentsMargins(2, 2, 2, 2);
        horizontalLayout_12->setObjectName(QString::fromUtf8("horizontalLayout_12"));
        ctrl_logoAndStatus = new QGraphicsView(centralWidget);
        ctrl_logoAndStatus->setObjectName(QString::fromUtf8("ctrl_logoAndStatus"));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(ctrl_logoAndStatus->sizePolicy().hasHeightForWidth());
        ctrl_logoAndStatus->setSizePolicy(sizePolicy1);
        ctrl_logoAndStatus->setMinimumSize(QSize(128, 128));
        ctrl_logoAndStatus->setMaximumSize(QSize(128, 128));
        ctrl_logoAndStatus->setStyleSheet(QString::fromUtf8("background-image: url(:/Images/icons/128x128/phoebetria.png);"));
        ctrl_logoAndStatus->setFrameShape(QFrame::NoFrame);
        ctrl_logoAndStatus->setFrameShadow(QFrame::Sunken);
        ctrl_logoAndStatus->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        ctrl_logoAndStatus->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        ctrl_logoAndStatus->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);

        horizontalLayout_12->addWidget(ctrl_logoAndStatus);

        verticalLayout_7 = new QVBoxLayout();
        verticalLayout_7->setSpacing(6);
        verticalLayout_7->setObjectName(QString::fromUtf8("verticalLayout_7"));
        groupBox = new QGroupBox(centralWidget);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setAutoFillBackground(false);
        horizontalLayout_8 = new QHBoxLayout(groupBox);
        horizontalLayout_8->setSpacing(6);
        horizontalLayout_8->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
        verticalLayout_11 = new QVBoxLayout();
        verticalLayout_11->setSpacing(0);
        verticalLayout_11->setObjectName(QString::fromUtf8("verticalLayout_11"));
        lbl_activeProfile = new QLabel(groupBox);
        lbl_activeProfile->setObjectName(QString::fromUtf8("lbl_activeProfile"));
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(lbl_activeProfile->sizePolicy().hasHeightForWidth());
        lbl_activeProfile->setSizePolicy(sizePolicy2);
        lbl_activeProfile->setAutoFillBackground(true);
        lbl_activeProfile->setFrameShape(QFrame::StyledPanel);
        lbl_activeProfile->setFrameShadow(QFrame::Raised);
        lbl_activeProfile->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);
        lbl_activeProfile->setWordWrap(true);

        verticalLayout_11->addWidget(lbl_activeProfile);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        verticalLayout_11->addItem(horizontalSpacer);

        pushButton_2 = new QPushButton(groupBox);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));

        verticalLayout_11->addWidget(pushButton_2);

        pushButton = new QPushButton(groupBox);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        verticalLayout_11->addWidget(pushButton);

        ctrl_syncGui = new QPushButton(groupBox);
        ctrl_syncGui->setObjectName(QString::fromUtf8("ctrl_syncGui"));

        verticalLayout_11->addWidget(ctrl_syncGui);


        horizontalLayout_8->addLayout(verticalLayout_11);

        verticalLayout_6 = new QVBoxLayout();
        verticalLayout_6->setSpacing(5);
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        frame_3 = new QFrame(groupBox);
        frame_3->setObjectName(QString::fromUtf8("frame_3"));
        frame_3->setFrameShape(QFrame::Panel);
        frame_3->setFrameShadow(QFrame::Sunken);
        frame_3->setLineWidth(1);
        horizontalLayout_18 = new QHBoxLayout(frame_3);
        horizontalLayout_18->setSpacing(20);
        horizontalLayout_18->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_18->setObjectName(QString::fromUtf8("horizontalLayout_18"));
        horizontalLayout_18->setContentsMargins(10, 0, 10, 0);
        ctrl_tempScaleToggleBtn = new QPushButton(frame_3);
        ctrl_tempScaleToggleBtn->setObjectName(QString::fromUtf8("ctrl_tempScaleToggleBtn"));
        ctrl_tempScaleToggleBtn->setMaximumSize(QSize(20, 20));
        ctrl_tempScaleToggleBtn->setStyleSheet(QString::fromUtf8(""));
        ctrl_tempScaleToggleBtn->setText(QString::fromUtf8(""));
        ctrl_tempScaleToggleBtn->setIconSize(QSize(24, 24));
        ctrl_tempScaleToggleBtn->setCheckable(true);
        ctrl_tempScaleToggleBtn->setChecked(true);
        ctrl_tempScaleToggleBtn->setFlat(false);

        horizontalLayout_18->addWidget(ctrl_tempScaleToggleBtn);

        ctrl_isAudibleAlarmBtn = new QPushButton(frame_3);
        ctrl_isAudibleAlarmBtn->setObjectName(QString::fromUtf8("ctrl_isAudibleAlarmBtn"));
        ctrl_isAudibleAlarmBtn->setMaximumSize(QSize(20, 20));
        ctrl_isAudibleAlarmBtn->setStyleSheet(QString::fromUtf8(""));
        ctrl_isAudibleAlarmBtn->setText(QString::fromUtf8(""));
        ctrl_isAudibleAlarmBtn->setIconSize(QSize(24, 24));
        ctrl_isAudibleAlarmBtn->setCheckable(true);

        horizontalLayout_18->addWidget(ctrl_isAudibleAlarmBtn);


        verticalLayout_6->addWidget(frame_3);

        frame_2 = new QFrame(groupBox);
        frame_2->setObjectName(QString::fromUtf8("frame_2"));
        frame_2->setFrameShape(QFrame::Panel);
        frame_2->setFrameShadow(QFrame::Sunken);
        frame_2->setLineWidth(1);
        horizontalLayout_19 = new QHBoxLayout(frame_2);
        horizontalLayout_19->setSpacing(20);
        horizontalLayout_19->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_19->setObjectName(QString::fromUtf8("horizontalLayout_19"));
        horizontalLayout_19->setContentsMargins(10, 0, 10, 0);
        ctrl_isManualBtn = new QPushButton(frame_2);
        ctrl_isManualBtn->setObjectName(QString::fromUtf8("ctrl_isManualBtn"));
        ctrl_isManualBtn->setMaximumSize(QSize(20, 20));
        ctrl_isManualBtn->setStyleSheet(QString::fromUtf8(""));
        ctrl_isManualBtn->setIconSize(QSize(24, 24));
        ctrl_isManualBtn->setCheckable(true);
        ctrl_isManualBtn->setChecked(false);
        ctrl_isManualBtn->setFlat(false);

        horizontalLayout_19->addWidget(ctrl_isManualBtn);

        ctrl_ModifyProfile = new QPushButton(frame_2);
        ctrl_ModifyProfile->setObjectName(QString::fromUtf8("ctrl_ModifyProfile"));
        ctrl_ModifyProfile->setMaximumSize(QSize(20, 20));
        ctrl_ModifyProfile->setStyleSheet(QString::fromUtf8(""));
        ctrl_ModifyProfile->setText(QString::fromUtf8(""));
        ctrl_ModifyProfile->setIconSize(QSize(24, 24));

        horizontalLayout_19->addWidget(ctrl_ModifyProfile);


        verticalLayout_6->addWidget(frame_2);

        frame = new QFrame(groupBox);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setFrameShape(QFrame::Panel);
        frame->setFrameShadow(QFrame::Sunken);
        frame->setLineWidth(1);
        horizontalLayout = new QHBoxLayout(frame);
        horizontalLayout->setSpacing(20);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(10, 0, 10, 0);
        ctrl_isSoftwareControlBtn = new QPushButton(frame);
        ctrl_isSoftwareControlBtn->setObjectName(QString::fromUtf8("ctrl_isSoftwareControlBtn"));
        ctrl_isSoftwareControlBtn->setMaximumSize(QSize(20, 20));
        ctrl_isSoftwareControlBtn->setStyleSheet(QString::fromUtf8(""));
        ctrl_isSoftwareControlBtn->setIconSize(QSize(24, 24));
        ctrl_isSoftwareControlBtn->setCheckable(true);

        horizontalLayout->addWidget(ctrl_isSoftwareControlBtn);

        ctrl_configSoftwareAutoBtn = new QPushButton(frame);
        ctrl_configSoftwareAutoBtn->setObjectName(QString::fromUtf8("ctrl_configSoftwareAutoBtn"));
        ctrl_configSoftwareAutoBtn->setEnabled(false);
        ctrl_configSoftwareAutoBtn->setMaximumSize(QSize(20, 20));
        ctrl_configSoftwareAutoBtn->setStyleSheet(QString::fromUtf8(""));
        ctrl_configSoftwareAutoBtn->setIconSize(QSize(24, 24));

        horizontalLayout->addWidget(ctrl_configSoftwareAutoBtn);


        verticalLayout_6->addWidget(frame);


        horizontalLayout_8->addLayout(verticalLayout_6);


        verticalLayout_7->addWidget(groupBox);


        horizontalLayout_12->addLayout(verticalLayout_7);


        verticalLayout_9->addLayout(horizontalLayout_12);

        horizontalLayout_17 = new QHBoxLayout();
        horizontalLayout_17->setSpacing(2);
        horizontalLayout_17->setContentsMargins(2, 2, 2, 2);
        horizontalLayout_17->setObjectName(QString::fromUtf8("horizontalLayout_17"));
        groupBox_channel1 = new QGroupBox(centralWidget);
        groupBox_channel1->setObjectName(QString::fromUtf8("groupBox_channel1"));
        QSizePolicy sizePolicy3(QSizePolicy::Preferred, QSizePolicy::MinimumExpanding);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(groupBox_channel1->sizePolicy().hasHeightForWidth());
        groupBox_channel1->setSizePolicy(sizePolicy3);
        groupBox_channel1->setMinimumSize(QSize(80, 290));
        groupBox_channel1->setAutoFillBackground(true);
        groupBox_channel1->setStyleSheet(QString::fromUtf8(""));
        verticalLayout = new QVBoxLayout(groupBox_channel1);
        verticalLayout->setSpacing(-1);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        layout_probe1Temp = new QVBoxLayout();
        layout_probe1Temp->setSpacing(-1);
        layout_probe1Temp->setObjectName(QString::fromUtf8("layout_probe1Temp"));
        layout_probe1Temp->setContentsMargins(-1, 0, -1, -1);
        ctrl_probe1Temp = new QLineEdit(groupBox_channel1);
        ctrl_probe1Temp->setObjectName(QString::fromUtf8("ctrl_probe1Temp"));
        ctrl_probe1Temp->setEnabled(false);
        QSizePolicy sizePolicy4(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(ctrl_probe1Temp->sizePolicy().hasHeightForWidth());
        ctrl_probe1Temp->setSizePolicy(sizePolicy4);
        ctrl_probe1Temp->setMinimumSize(QSize(0, 0));
        ctrl_probe1Temp->setAlignment(Qt::AlignCenter);
        ctrl_probe1Temp->setReadOnly(true);

        layout_probe1Temp->addWidget(ctrl_probe1Temp);


        verticalLayout->addLayout(layout_probe1Temp);

        layout_channel1targetspeedSlider = new QHBoxLayout();
        layout_channel1targetspeedSlider->setSpacing(6);
        layout_channel1targetspeedSlider->setObjectName(QString::fromUtf8("layout_channel1targetspeedSlider"));
        ctrl_channel1speedSlider = new QSlider(groupBox_channel1);
        ctrl_channel1speedSlider->setObjectName(QString::fromUtf8("ctrl_channel1speedSlider"));
        ctrl_channel1speedSlider->setEnabled(false);
        sizePolicy.setHeightForWidth(ctrl_channel1speedSlider->sizePolicy().hasHeightForWidth());
        ctrl_channel1speedSlider->setSizePolicy(sizePolicy);
        ctrl_channel1speedSlider->setMinimumSize(QSize(0, 80));
        ctrl_channel1speedSlider->setStyleSheet(QString::fromUtf8("	QSlider::groove:vertical {\n"
"     	border: 1px solid #bbb;\n"
"     	background: darkBlue;\n"
"     	width: 20px;\n"
"     	border-radius: 4px;\n"
" 	}\n"
"\n"
" 	QSlider::handle:vertical {\n"
"		background-color: qlineargradient(spread:pad, x1:1, y1:1.1, x2:1, y2:0, stop:0 #000, stop:1 #FFF);\n"
" 		height:15px;\n"
" 		margin:-6px;\n"
" 		border:1px solid #777;\n"
"		border-radius:4px;\n"
" 	}\n"
"\n"
" 	QSlider::add-page:vertical {\n"
"	 	background: qlineargradient(x0: 1, y0: 1, x2: 0, y2: 1, stop: 0 #69c, stop: 1 #026);\n"
"	 	background: qlineargradient(x0: 1, y0: 1, x2: 0, y2: 1, stop: 0 #026, stop: 1 #69c);\n"
"	 	border: 1px solid #777;\n"
"	 	border-radius: 4px;\n"
" 	}\n"
"\n"
" 	QSlider::sub-page:vertical {\n"
"	 	background: qlineargradient(x0: 1, y0: 1, x2: 0, y2: 1, stop: 0 #026, stop: 1 #69c);\n"
"	 	background: qlineargradient(x0: 1, y0: 1, x2: 0, y2: 1, stop: 0 #69c, stop: 1 #026);\n"
"     	border: 1px solid #777;\n"
"	 	border-radius: 4px;\n"
" 	}"));
        ctrl_channel1speedSlider->setMaximum(100);
        ctrl_channel1speedSlider->setOrientation(Qt::Vertical);
        ctrl_channel1speedSlider->setInvertedAppearance(false);
        ctrl_channel1speedSlider->setInvertedControls(false);
        ctrl_channel1speedSlider->setTickPosition(QSlider::TicksAbove);

        layout_channel1targetspeedSlider->addWidget(ctrl_channel1speedSlider);


        verticalLayout->addLayout(layout_channel1targetspeedSlider);

        verticalSpacer_3 = new QSpacerItem(20, 2, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout->addItem(verticalSpacer_3);

        ctrl_channel1speed = new QPushButton(groupBox_channel1);
        ctrl_channel1speed->setObjectName(QString::fromUtf8("ctrl_channel1speed"));

        verticalLayout->addWidget(ctrl_channel1speed);

        layout_channel1Select = new QVBoxLayout();
        layout_channel1Select->setSpacing(-1);
        layout_channel1Select->setObjectName(QString::fromUtf8("layout_channel1Select"));
        layout_channel1Select->setContentsMargins(-1, 0, -1, -1);
        ctrl_channel1Select = new QPushButton(groupBox_channel1);
        ctrl_channel1Select->setObjectName(QString::fromUtf8("ctrl_channel1Select"));
        ctrl_channel1Select->setMinimumSize(QSize(0, 0));
        ctrl_channel1Select->setMaximumSize(QSize(16777215, 16777215));
        ctrl_channel1Select->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	background-color: rgba(230, 230, 230, 0%);\n"
"	border: none;\n"
"	margin: 0px;\n"
"    padding: 0px;\n"
"	font-size: 20px;\n"
"	font-weight: bold;\n"
"	color: white;\n"
"	image: url(:/Images/icon_channels_lite_blue.png)\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"	background-color: rgba(230, 230, 230, 0%);\n"
"	border: none;\n"
"	margin: 0px;\n"
"    padding: 0px;\n"
"	font-size: 20px;\n"
"	font-weight: bold;\n"
"	color: grey;\n"
"	image: url(:/Images/icon_channels_lite_blue.png)\n"
"}"));
        ctrl_channel1Select->setIconSize(QSize(50, 30));
        ctrl_channel1Select->setFlat(false);

        layout_channel1Select->addWidget(ctrl_channel1Select);


        verticalLayout->addLayout(layout_channel1Select);

        ctrl_channel1AlarmTemp = new QPushButton(groupBox_channel1);
        ctrl_channel1AlarmTemp->setObjectName(QString::fromUtf8("ctrl_channel1AlarmTemp"));
        QSizePolicy sizePolicy5(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy5.setHorizontalStretch(51);
        sizePolicy5.setVerticalStretch(0);
        sizePolicy5.setHeightForWidth(ctrl_channel1AlarmTemp->sizePolicy().hasHeightForWidth());
        ctrl_channel1AlarmTemp->setSizePolicy(sizePolicy5);
        ctrl_channel1AlarmTemp->setMinimumSize(QSize(51, 0));

        verticalLayout->addWidget(ctrl_channel1AlarmTemp);


        horizontalLayout_17->addWidget(groupBox_channel1);

        groupBox_channel2 = new QGroupBox(centralWidget);
        groupBox_channel2->setObjectName(QString::fromUtf8("groupBox_channel2"));
        sizePolicy3.setHeightForWidth(groupBox_channel2->sizePolicy().hasHeightForWidth());
        groupBox_channel2->setSizePolicy(sizePolicy3);
        groupBox_channel2->setMinimumSize(QSize(80, 290));
        groupBox_channel2->setAutoFillBackground(true);
        verticalLayout_4 = new QVBoxLayout(groupBox_channel2);
        verticalLayout_4->setSpacing(-1);
        verticalLayout_4->setContentsMargins(11, 11, 11, 11);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        layout_probe2Temp = new QVBoxLayout();
        layout_probe2Temp->setSpacing(-1);
        layout_probe2Temp->setObjectName(QString::fromUtf8("layout_probe2Temp"));
        layout_probe2Temp->setContentsMargins(-1, 0, -1, -1);
        ctrl_probe2Temp = new QLineEdit(groupBox_channel2);
        ctrl_probe2Temp->setObjectName(QString::fromUtf8("ctrl_probe2Temp"));
        ctrl_probe2Temp->setEnabled(false);
        ctrl_probe2Temp->setAlignment(Qt::AlignCenter);
        ctrl_probe2Temp->setReadOnly(true);

        layout_probe2Temp->addWidget(ctrl_probe2Temp);


        verticalLayout_4->addLayout(layout_probe2Temp);

        horizontalLayout_11 = new QHBoxLayout();
        horizontalLayout_11->setSpacing(6);
        horizontalLayout_11->setObjectName(QString::fromUtf8("horizontalLayout_11"));
        ctrl_channel2speedSlider = new QSlider(groupBox_channel2);
        ctrl_channel2speedSlider->setObjectName(QString::fromUtf8("ctrl_channel2speedSlider"));
        ctrl_channel2speedSlider->setEnabled(false);
        sizePolicy.setHeightForWidth(ctrl_channel2speedSlider->sizePolicy().hasHeightForWidth());
        ctrl_channel2speedSlider->setSizePolicy(sizePolicy);
        ctrl_channel2speedSlider->setMinimumSize(QSize(0, 80));
        ctrl_channel2speedSlider->setStyleSheet(QString::fromUtf8("	QSlider::groove:vertical {\n"
"     	border: 1px solid #bbb;\n"
"     	background: darkBlue;\n"
"     	width: 20px;\n"
"     	border-radius: 4px;\n"
" 	}\n"
"\n"
" 	QSlider::handle:vertical {\n"
"		background-color: qlineargradient(spread:pad, x1:1, y1:1.1, x2:1, y2:0, stop:0 #000, stop:1 #FFF);\n"
" 		height:15px;\n"
" 		margin:-6px;\n"
" 		border:1px solid #777;\n"
"		border-radius:4px;\n"
" 	}\n"
"\n"
" 	QSlider::add-page:vertical {\n"
"	 	background: qlineargradient(x0: 1, y0: 1, x2: 0, y2: 1, stop: 0 #69c, stop: 1 #026);\n"
"	 	background: qlineargradient(x0: 1, y0: 1, x2: 0, y2: 1, stop: 0 #026, stop: 1 #69c);\n"
"	 	border: 1px solid #777;\n"
"	 	border-radius: 4px;\n"
" 	}\n"
"\n"
" 	QSlider::sub-page:vertical {\n"
"	 	background: qlineargradient(x0: 1, y0: 1, x2: 0, y2: 1, stop: 0 #026, stop: 1 #69c);\n"
"	 	background: qlineargradient(x0: 1, y0: 1, x2: 0, y2: 1, stop: 0 #69c, stop: 1 #026);\n"
"     	border: 1px solid #777;\n"
"	 	border-radius: 4px;\n"
" 	}"));
        ctrl_channel2speedSlider->setMaximum(100);
        ctrl_channel2speedSlider->setOrientation(Qt::Vertical);
        ctrl_channel2speedSlider->setInvertedAppearance(false);
        ctrl_channel2speedSlider->setInvertedControls(false);
        ctrl_channel2speedSlider->setTickPosition(QSlider::TicksAbove);

        horizontalLayout_11->addWidget(ctrl_channel2speedSlider);


        verticalLayout_4->addLayout(horizontalLayout_11);

        verticalSpacer_6 = new QSpacerItem(20, 2, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_4->addItem(verticalSpacer_6);

        ctrl_channel2speed = new QPushButton(groupBox_channel2);
        ctrl_channel2speed->setObjectName(QString::fromUtf8("ctrl_channel2speed"));

        verticalLayout_4->addWidget(ctrl_channel2speed);

        layout_channel2Select = new QVBoxLayout();
        layout_channel2Select->setSpacing(-1);
        layout_channel2Select->setObjectName(QString::fromUtf8("layout_channel2Select"));
        layout_channel2Select->setContentsMargins(-1, 0, -1, -1);
        ctrl_channel2Select = new QPushButton(groupBox_channel2);
        ctrl_channel2Select->setObjectName(QString::fromUtf8("ctrl_channel2Select"));
        ctrl_channel2Select->setMinimumSize(QSize(0, 0));
        ctrl_channel2Select->setMaximumSize(QSize(16777215, 16777215));
        ctrl_channel2Select->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	background-color: rgba(230, 230, 230, 0%);\n"
"	border: none;\n"
"	margin: 0px;\n"
"    padding: 0px;\n"
"	font-size: 20px;\n"
"	font-weight: bold;\n"
"	color: white;\n"
"	image: url(:/Images/icon_channels_lite_blue.png)\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"	background-color: rgba(230, 230, 230, 0%);\n"
"	border: none;\n"
"	margin: 0px;\n"
"    padding: 0px;\n"
"	font-size: 20px;\n"
"	font-weight: bold;\n"
"	color: grey;\n"
"	image: url(:/Images/icon_channels_lite_blue.png)\n"
"}"));
        ctrl_channel2Select->setIconSize(QSize(50, 30));
        ctrl_channel2Select->setFlat(false);

        layout_channel2Select->addWidget(ctrl_channel2Select);


        verticalLayout_4->addLayout(layout_channel2Select);

        ctrl_channel2AlarmTemp = new QPushButton(groupBox_channel2);
        ctrl_channel2AlarmTemp->setObjectName(QString::fromUtf8("ctrl_channel2AlarmTemp"));
        sizePolicy5.setHeightForWidth(ctrl_channel2AlarmTemp->sizePolicy().hasHeightForWidth());
        ctrl_channel2AlarmTemp->setSizePolicy(sizePolicy5);
        ctrl_channel2AlarmTemp->setMinimumSize(QSize(51, 0));

        verticalLayout_4->addWidget(ctrl_channel2AlarmTemp);


        horizontalLayout_17->addWidget(groupBox_channel2);

        groupBox_channel3 = new QGroupBox(centralWidget);
        groupBox_channel3->setObjectName(QString::fromUtf8("groupBox_channel3"));
        sizePolicy3.setHeightForWidth(groupBox_channel3->sizePolicy().hasHeightForWidth());
        groupBox_channel3->setSizePolicy(sizePolicy3);
        groupBox_channel3->setMinimumSize(QSize(80, 290));
        groupBox_channel3->setAutoFillBackground(true);
        verticalLayout_2 = new QVBoxLayout(groupBox_channel3);
        verticalLayout_2->setSpacing(-1);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        layout_probe3Temp = new QVBoxLayout();
        layout_probe3Temp->setSpacing(-1);
        layout_probe3Temp->setObjectName(QString::fromUtf8("layout_probe3Temp"));
        layout_probe3Temp->setContentsMargins(-1, 0, -1, -1);
        ctrl_probe3Temp = new QLineEdit(groupBox_channel3);
        ctrl_probe3Temp->setObjectName(QString::fromUtf8("ctrl_probe3Temp"));
        ctrl_probe3Temp->setEnabled(false);
        ctrl_probe3Temp->setAlignment(Qt::AlignCenter);
        ctrl_probe3Temp->setReadOnly(true);

        layout_probe3Temp->addWidget(ctrl_probe3Temp);


        verticalLayout_2->addLayout(layout_probe3Temp);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        ctrl_channel3speedSlider = new QSlider(groupBox_channel3);
        ctrl_channel3speedSlider->setObjectName(QString::fromUtf8("ctrl_channel3speedSlider"));
        ctrl_channel3speedSlider->setEnabled(false);
        sizePolicy.setHeightForWidth(ctrl_channel3speedSlider->sizePolicy().hasHeightForWidth());
        ctrl_channel3speedSlider->setSizePolicy(sizePolicy);
        ctrl_channel3speedSlider->setMinimumSize(QSize(0, 80));
        ctrl_channel3speedSlider->setStyleSheet(QString::fromUtf8("	QSlider::groove:vertical {\n"
"     	border: 1px solid #bbb;\n"
"     	background: darkBlue;\n"
"     	width: 20px;\n"
"     	border-radius: 4px;\n"
" 	}\n"
"\n"
" 	QSlider::handle:vertical {\n"
"		background-color: qlineargradient(spread:pad, x1:1, y1:1.1, x2:1, y2:0, stop:0 #000, stop:1 #FFF);\n"
" 		height:15px;\n"
" 		margin:-6px;\n"
" 		border:1px solid #777;\n"
"		border-radius:4px;\n"
" 	}\n"
"\n"
" 	QSlider::add-page:vertical {\n"
"	 	background: qlineargradient(x0: 1, y0: 1, x2: 0, y2: 1, stop: 0 #69c, stop: 1 #026);\n"
"	 	background: qlineargradient(x0: 1, y0: 1, x2: 0, y2: 1, stop: 0 #026, stop: 1 #69c);\n"
"	 	border: 1px solid #777;\n"
"	 	border-radius: 4px;\n"
" 	}\n"
"\n"
" 	QSlider::sub-page:vertical {\n"
"	 	background: qlineargradient(x0: 1, y0: 1, x2: 0, y2: 1, stop: 0 #026, stop: 1 #69c);\n"
"	 	background: qlineargradient(x0: 1, y0: 1, x2: 0, y2: 1, stop: 0 #69c, stop: 1 #026);\n"
"     	border: 1px solid #777;\n"
"	 	border-radius: 4px;\n"
" 	}"));
        ctrl_channel3speedSlider->setMaximum(100);
        ctrl_channel3speedSlider->setOrientation(Qt::Vertical);
        ctrl_channel3speedSlider->setInvertedAppearance(false);
        ctrl_channel3speedSlider->setInvertedControls(false);
        ctrl_channel3speedSlider->setTickPosition(QSlider::TicksAbove);

        horizontalLayout_5->addWidget(ctrl_channel3speedSlider);


        verticalLayout_2->addLayout(horizontalLayout_5);

        verticalSpacer_4 = new QSpacerItem(20, 2, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_2->addItem(verticalSpacer_4);

        ctrl_channel3speed = new QPushButton(groupBox_channel3);
        ctrl_channel3speed->setObjectName(QString::fromUtf8("ctrl_channel3speed"));

        verticalLayout_2->addWidget(ctrl_channel3speed);

        layout_channel3Select = new QVBoxLayout();
        layout_channel3Select->setSpacing(-1);
        layout_channel3Select->setObjectName(QString::fromUtf8("layout_channel3Select"));
        layout_channel3Select->setContentsMargins(-1, 0, -1, -1);
        ctrl_channel3Select = new QPushButton(groupBox_channel3);
        ctrl_channel3Select->setObjectName(QString::fromUtf8("ctrl_channel3Select"));
        ctrl_channel3Select->setMinimumSize(QSize(0, 0));
        ctrl_channel3Select->setMaximumSize(QSize(16777215, 16777215));
        ctrl_channel3Select->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	background-color: rgba(230, 230, 230, 0%);\n"
"	border: none;\n"
"	margin: 0px;\n"
"    padding: 0px;\n"
"	font-size: 20px;\n"
"	font-weight: bold;\n"
"	color: white;\n"
"	image: url(:/Images/icon_channels_lite_blue.png)\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"	background-color: rgba(230, 230, 230, 0%);\n"
"	border: none;\n"
"	margin: 0px;\n"
"    padding: 0px;\n"
"	font-size: 20px;\n"
"	font-weight: bold;\n"
"	color: grey;\n"
"	image: url(:/Images/icon_channels_lite_blue.png)\n"
"}"));
        ctrl_channel3Select->setIconSize(QSize(50, 30));
        ctrl_channel3Select->setFlat(false);

        layout_channel3Select->addWidget(ctrl_channel3Select);


        verticalLayout_2->addLayout(layout_channel3Select);

        ctrl_channel3AlarmTemp = new QPushButton(groupBox_channel3);
        ctrl_channel3AlarmTemp->setObjectName(QString::fromUtf8("ctrl_channel3AlarmTemp"));
        sizePolicy5.setHeightForWidth(ctrl_channel3AlarmTemp->sizePolicy().hasHeightForWidth());
        ctrl_channel3AlarmTemp->setSizePolicy(sizePolicy5);
        ctrl_channel3AlarmTemp->setMinimumSize(QSize(51, 0));

        verticalLayout_2->addWidget(ctrl_channel3AlarmTemp);


        horizontalLayout_17->addWidget(groupBox_channel3);

        groupBox_channel4 = new QGroupBox(centralWidget);
        groupBox_channel4->setObjectName(QString::fromUtf8("groupBox_channel4"));
        sizePolicy3.setHeightForWidth(groupBox_channel4->sizePolicy().hasHeightForWidth());
        groupBox_channel4->setSizePolicy(sizePolicy3);
        groupBox_channel4->setMinimumSize(QSize(80, 290));
        groupBox_channel4->setAutoFillBackground(true);
        verticalLayout_5 = new QVBoxLayout(groupBox_channel4);
        verticalLayout_5->setSpacing(-1);
        verticalLayout_5->setContentsMargins(11, 11, 11, 11);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        layout_probe4Temp = new QVBoxLayout();
        layout_probe4Temp->setSpacing(-1);
        layout_probe4Temp->setObjectName(QString::fromUtf8("layout_probe4Temp"));
        layout_probe4Temp->setContentsMargins(-1, 0, -1, -1);
        ctrl_probe4Temp = new QLineEdit(groupBox_channel4);
        ctrl_probe4Temp->setObjectName(QString::fromUtf8("ctrl_probe4Temp"));
        ctrl_probe4Temp->setEnabled(false);
        ctrl_probe4Temp->setAlignment(Qt::AlignCenter);
        ctrl_probe4Temp->setReadOnly(true);

        layout_probe4Temp->addWidget(ctrl_probe4Temp);


        verticalLayout_5->addLayout(layout_probe4Temp);

        horizontalLayout_14 = new QHBoxLayout();
        horizontalLayout_14->setSpacing(6);
        horizontalLayout_14->setObjectName(QString::fromUtf8("horizontalLayout_14"));
        ctrl_channel4speedSlider = new QSlider(groupBox_channel4);
        ctrl_channel4speedSlider->setObjectName(QString::fromUtf8("ctrl_channel4speedSlider"));
        ctrl_channel4speedSlider->setEnabled(false);
        sizePolicy.setHeightForWidth(ctrl_channel4speedSlider->sizePolicy().hasHeightForWidth());
        ctrl_channel4speedSlider->setSizePolicy(sizePolicy);
        ctrl_channel4speedSlider->setMinimumSize(QSize(0, 80));
        ctrl_channel4speedSlider->setStyleSheet(QString::fromUtf8("	QSlider::groove:vertical {\n"
"     	border: 1px solid #bbb;\n"
"     	background: darkBlue;\n"
"     	width: 20px;\n"
"     	border-radius: 4px;\n"
" 	}\n"
"\n"
" 	QSlider::handle:vertical {\n"
"		background-color: qlineargradient(spread:pad, x1:1, y1:1.1, x2:1, y2:0, stop:0 #000, stop:1 #FFF);\n"
" 		height:15px;\n"
" 		margin:-6px;\n"
" 		border:1px solid #777;\n"
"		border-radius:4px;\n"
" 	}\n"
"\n"
" 	QSlider::add-page:vertical {\n"
"	 	background: qlineargradient(x0: 1, y0: 1, x2: 0, y2: 1, stop: 0 #69c, stop: 1 #026);\n"
"	 	background: qlineargradient(x0: 1, y0: 1, x2: 0, y2: 1, stop: 0 #026, stop: 1 #69c);\n"
"	 	border: 1px solid #777;\n"
"	 	border-radius: 4px;\n"
" 	}\n"
"\n"
" 	QSlider::sub-page:vertical {\n"
"	 	background: qlineargradient(x0: 1, y0: 1, x2: 0, y2: 1, stop: 0 #026, stop: 1 #69c);\n"
"	 	background: qlineargradient(x0: 1, y0: 1, x2: 0, y2: 1, stop: 0 #69c, stop: 1 #026);\n"
"     	border: 1px solid #777;\n"
"	 	border-radius: 4px;\n"
" 	}"));
        ctrl_channel4speedSlider->setMaximum(100);
        ctrl_channel4speedSlider->setOrientation(Qt::Vertical);
        ctrl_channel4speedSlider->setInvertedAppearance(false);
        ctrl_channel4speedSlider->setInvertedControls(false);
        ctrl_channel4speedSlider->setTickPosition(QSlider::TicksAbove);

        horizontalLayout_14->addWidget(ctrl_channel4speedSlider);


        verticalLayout_5->addLayout(horizontalLayout_14);

        verticalSpacer_7 = new QSpacerItem(20, 2, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_5->addItem(verticalSpacer_7);

        ctrl_channel4speed = new QPushButton(groupBox_channel4);
        ctrl_channel4speed->setObjectName(QString::fromUtf8("ctrl_channel4speed"));

        verticalLayout_5->addWidget(ctrl_channel4speed);

        layout_channel4Select = new QVBoxLayout();
        layout_channel4Select->setSpacing(-1);
        layout_channel4Select->setObjectName(QString::fromUtf8("layout_channel4Select"));
        layout_channel4Select->setContentsMargins(-1, 0, -1, -1);
        ctrl_channel4Select = new QPushButton(groupBox_channel4);
        ctrl_channel4Select->setObjectName(QString::fromUtf8("ctrl_channel4Select"));
        ctrl_channel4Select->setMinimumSize(QSize(0, 0));
        ctrl_channel4Select->setMaximumSize(QSize(16777215, 16777215));
        ctrl_channel4Select->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	background-color: rgba(230, 230, 230, 0%);\n"
"	border: none;\n"
"	margin: 0px;\n"
"    padding: 0px;\n"
"	font-size: 20px;\n"
"	font-weight: bold;\n"
"	color: white;\n"
"	image: url(:/Images/icon_channels_lite_blue.png)\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"	background-color: rgba(230, 230, 230, 0%);\n"
"	border: none;\n"
"	margin: 0px;\n"
"    padding: 0px;\n"
"	font-size: 20px;\n"
"	font-weight: bold;\n"
"	color: grey;\n"
"	image: url(:/Images/icon_channels_lite_blue.png)\n"
"}"));
        ctrl_channel4Select->setIconSize(QSize(50, 30));
        ctrl_channel4Select->setFlat(false);

        layout_channel4Select->addWidget(ctrl_channel4Select);


        verticalLayout_5->addLayout(layout_channel4Select);

        ctrl_channel4AlarmTemp = new QPushButton(groupBox_channel4);
        ctrl_channel4AlarmTemp->setObjectName(QString::fromUtf8("ctrl_channel4AlarmTemp"));
        sizePolicy5.setHeightForWidth(ctrl_channel4AlarmTemp->sizePolicy().hasHeightForWidth());
        ctrl_channel4AlarmTemp->setSizePolicy(sizePolicy5);
        ctrl_channel4AlarmTemp->setMinimumSize(QSize(51, 0));

        verticalLayout_5->addWidget(ctrl_channel4AlarmTemp);


        horizontalLayout_17->addWidget(groupBox_channel4);

        groupBox_channel5 = new QGroupBox(centralWidget);
        groupBox_channel5->setObjectName(QString::fromUtf8("groupBox_channel5"));
        sizePolicy3.setHeightForWidth(groupBox_channel5->sizePolicy().hasHeightForWidth());
        groupBox_channel5->setSizePolicy(sizePolicy3);
        groupBox_channel5->setMinimumSize(QSize(80, 290));
        groupBox_channel5->setAutoFillBackground(true);
        verticalLayout_3 = new QVBoxLayout(groupBox_channel5);
        verticalLayout_3->setSpacing(-1);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        layout_probe5Temp = new QVBoxLayout();
        layout_probe5Temp->setSpacing(-1);
        layout_probe5Temp->setObjectName(QString::fromUtf8("layout_probe5Temp"));
        layout_probe5Temp->setContentsMargins(-1, 0, -1, -1);
        ctrl_probe5Temp = new QLineEdit(groupBox_channel5);
        ctrl_probe5Temp->setObjectName(QString::fromUtf8("ctrl_probe5Temp"));
        ctrl_probe5Temp->setEnabled(false);
        ctrl_probe5Temp->setAlignment(Qt::AlignCenter);
        ctrl_probe5Temp->setReadOnly(true);

        layout_probe5Temp->addWidget(ctrl_probe5Temp);


        verticalLayout_3->addLayout(layout_probe5Temp);

        horizontalLayout_30 = new QHBoxLayout();
        horizontalLayout_30->setSpacing(6);
        horizontalLayout_30->setObjectName(QString::fromUtf8("horizontalLayout_30"));
        ctrl_channel5speedSlider = new QSlider(groupBox_channel5);
        ctrl_channel5speedSlider->setObjectName(QString::fromUtf8("ctrl_channel5speedSlider"));
        ctrl_channel5speedSlider->setEnabled(false);
        sizePolicy.setHeightForWidth(ctrl_channel5speedSlider->sizePolicy().hasHeightForWidth());
        ctrl_channel5speedSlider->setSizePolicy(sizePolicy);
        ctrl_channel5speedSlider->setMinimumSize(QSize(0, 80));
        ctrl_channel5speedSlider->setStyleSheet(QString::fromUtf8("	QSlider::groove:vertical {\n"
"     	border: 1px solid #bbb;\n"
"     	background: darkBlue;\n"
"     	width: 20px;\n"
"     	border-radius: 4px;\n"
" 	}\n"
"\n"
" 	QSlider::handle:vertical {\n"
"		background-color: qlineargradient(spread:pad, x1:1, y1:1.1, x2:1, y2:0, stop:0 #000, stop:1 #FFF);\n"
" 		height:15px;\n"
" 		margin:-6px;\n"
" 		border:1px solid #777;\n"
"		border-radius:4px;\n"
" 	}\n"
"\n"
" 	QSlider::add-page:vertical {\n"
"	 	background: qlineargradient(x0: 1, y0: 1, x2: 0, y2: 1, stop: 0 #69c, stop: 1 #026);\n"
"	 	background: qlineargradient(x0: 1, y0: 1, x2: 0, y2: 1, stop: 0 #026, stop: 1 #69c);\n"
"	 	border: 1px solid #777;\n"
"	 	border-radius: 4px;\n"
" 	}\n"
"\n"
" 	QSlider::sub-page:vertical {\n"
"	 	background: qlineargradient(x0: 1, y0: 1, x2: 0, y2: 1, stop: 0 #026, stop: 1 #69c);\n"
"	 	background: qlineargradient(x0: 1, y0: 1, x2: 0, y2: 1, stop: 0 #69c, stop: 1 #026);\n"
"     	border: 1px solid #777;\n"
"	 	border-radius: 4px;\n"
" 	}"));
        ctrl_channel5speedSlider->setMaximum(100);
        ctrl_channel5speedSlider->setOrientation(Qt::Vertical);
        ctrl_channel5speedSlider->setInvertedAppearance(false);
        ctrl_channel5speedSlider->setInvertedControls(false);
        ctrl_channel5speedSlider->setTickPosition(QSlider::TicksAbove);

        horizontalLayout_30->addWidget(ctrl_channel5speedSlider);


        verticalLayout_3->addLayout(horizontalLayout_30);

        verticalSpacer_5 = new QSpacerItem(20, 2, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_3->addItem(verticalSpacer_5);

        ctrl_channel5speed = new QPushButton(groupBox_channel5);
        ctrl_channel5speed->setObjectName(QString::fromUtf8("ctrl_channel5speed"));

        verticalLayout_3->addWidget(ctrl_channel5speed);

        layout_channel5Select = new QVBoxLayout();
        layout_channel5Select->setSpacing(-1);
        layout_channel5Select->setObjectName(QString::fromUtf8("layout_channel5Select"));
        layout_channel5Select->setContentsMargins(-1, 0, -1, -1);
        ctrl_channel5Select = new QPushButton(groupBox_channel5);
        ctrl_channel5Select->setObjectName(QString::fromUtf8("ctrl_channel5Select"));
        ctrl_channel5Select->setMinimumSize(QSize(0, 0));
        ctrl_channel5Select->setMaximumSize(QSize(16777215, 16777215));
        QFont font;
        font.setBold(true);
        font.setWeight(75);
        ctrl_channel5Select->setFont(font);
        ctrl_channel5Select->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	background-color: rgba(230, 230, 230, 0%);\n"
"	border: none;\n"
"	margin: 0px;\n"
"    padding: 0px;\n"
"	font-size: 20px;\n"
"	font-weight: bold;\n"
"	color: white;\n"
"	image: url(:/Images/icon_channels_lite_blue.png)\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"	background-color: rgba(230, 230, 230, 0%);\n"
"	border: none;\n"
"	margin: 0px;\n"
"    padding: 0px;\n"
"	font-size: 20px;\n"
"	font-weight: bold;\n"
"	color: grey;\n"
"	image: url(:/Images/icon_channels_lite_blue.png)\n"
"}"));
        ctrl_channel5Select->setIconSize(QSize(50, 30));
        ctrl_channel5Select->setFlat(false);

        layout_channel5Select->addWidget(ctrl_channel5Select);


        verticalLayout_3->addLayout(layout_channel5Select);

        ctrl_channel5AlarmTemp = new QPushButton(groupBox_channel5);
        ctrl_channel5AlarmTemp->setObjectName(QString::fromUtf8("ctrl_channel5AlarmTemp"));
        sizePolicy5.setHeightForWidth(ctrl_channel5AlarmTemp->sizePolicy().hasHeightForWidth());
        ctrl_channel5AlarmTemp->setSizePolicy(sizePolicy5);
        ctrl_channel5AlarmTemp->setMinimumSize(QSize(51, 0));

        verticalLayout_3->addWidget(ctrl_channel5AlarmTemp);


        horizontalLayout_17->addWidget(groupBox_channel5);


        verticalLayout_9->addLayout(horizontalLayout_17);

        gui_MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(gui_MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 455, 22));
        gui_MainWindow->setMenuBar(menuBar);
        QWidget::setTabOrder(ctrl_logoAndStatus, pushButton);
        QWidget::setTabOrder(pushButton, ctrl_syncGui);
        QWidget::setTabOrder(ctrl_syncGui, ctrl_tempScaleToggleBtn);
        QWidget::setTabOrder(ctrl_tempScaleToggleBtn, ctrl_isAudibleAlarmBtn);
        QWidget::setTabOrder(ctrl_isAudibleAlarmBtn, ctrl_isManualBtn);
        QWidget::setTabOrder(ctrl_isManualBtn, ctrl_ModifyProfile);
        QWidget::setTabOrder(ctrl_ModifyProfile, ctrl_isSoftwareControlBtn);
        QWidget::setTabOrder(ctrl_isSoftwareControlBtn, ctrl_configSoftwareAutoBtn);
        QWidget::setTabOrder(ctrl_configSoftwareAutoBtn, ctrl_probe1Temp);
        QWidget::setTabOrder(ctrl_probe1Temp, ctrl_channel1speedSlider);
        QWidget::setTabOrder(ctrl_channel1speedSlider, ctrl_channel1speed);
        QWidget::setTabOrder(ctrl_channel1speed, ctrl_channel1Select);
        QWidget::setTabOrder(ctrl_channel1Select, ctrl_channel1AlarmTemp);
        QWidget::setTabOrder(ctrl_channel1AlarmTemp, ctrl_probe2Temp);
        QWidget::setTabOrder(ctrl_probe2Temp, ctrl_channel2speedSlider);
        QWidget::setTabOrder(ctrl_channel2speedSlider, ctrl_channel2speed);
        QWidget::setTabOrder(ctrl_channel2speed, ctrl_channel2Select);
        QWidget::setTabOrder(ctrl_channel2Select, ctrl_channel2AlarmTemp);
        QWidget::setTabOrder(ctrl_channel2AlarmTemp, ctrl_probe3Temp);
        QWidget::setTabOrder(ctrl_probe3Temp, ctrl_channel3speedSlider);
        QWidget::setTabOrder(ctrl_channel3speedSlider, ctrl_channel3speed);
        QWidget::setTabOrder(ctrl_channel3speed, ctrl_channel3Select);
        QWidget::setTabOrder(ctrl_channel3Select, ctrl_channel3AlarmTemp);
        QWidget::setTabOrder(ctrl_channel3AlarmTemp, ctrl_probe4Temp);
        QWidget::setTabOrder(ctrl_probe4Temp, ctrl_channel4speedSlider);
        QWidget::setTabOrder(ctrl_channel4speedSlider, ctrl_channel4speed);
        QWidget::setTabOrder(ctrl_channel4speed, ctrl_channel4Select);
        QWidget::setTabOrder(ctrl_channel4Select, ctrl_channel4AlarmTemp);
        QWidget::setTabOrder(ctrl_channel4AlarmTemp, ctrl_probe5Temp);
        QWidget::setTabOrder(ctrl_probe5Temp, ctrl_channel5speedSlider);
        QWidget::setTabOrder(ctrl_channel5speedSlider, ctrl_channel5speed);
        QWidget::setTabOrder(ctrl_channel5speed, ctrl_channel5Select);
        QWidget::setTabOrder(ctrl_channel5Select, ctrl_channel5AlarmTemp);

        retranslateUi(gui_MainWindow);

        QMetaObject::connectSlotsByName(gui_MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *gui_MainWindow)
    {
        gui_MainWindow->setWindowTitle(QApplication::translate("gui_MainWindow", "Phoebetria - BitFenix Recon Fan Controller", 0, QApplication::UnicodeUTF8));
        actionAbout->setText(QApplication::translate("gui_MainWindow", "About", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QString());
        lbl_activeProfile->setText(QApplication::translate("gui_MainWindow", "Profile: ", 0, QApplication::UnicodeUTF8));
        pushButton_2->setText(QApplication::translate("gui_MainWindow", "Reset FanControllerData", 0, QApplication::UnicodeUTF8));
        pushButton->setText(QApplication::translate("gui_MainWindow", "Basic Diagnostics", 0, QApplication::UnicodeUTF8));
        ctrl_syncGui->setText(QApplication::translate("gui_MainWindow", "Sync UI", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        ctrl_tempScaleToggleBtn->setToolTip(QApplication::translate("gui_MainWindow", "Toggle temperature scale", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        ctrl_isAudibleAlarmBtn->setToolTip(QApplication::translate("gui_MainWindow", "Toggle alarm", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        ctrl_isManualBtn->setToolTip(QApplication::translate("gui_MainWindow", "Toggle profile state", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        ctrl_isManualBtn->setText(QString());
#ifndef QT_NO_TOOLTIP
        ctrl_ModifyProfile->setToolTip(QApplication::translate("gui_MainWindow", "Manage profiles", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        ctrl_isSoftwareControlBtn->setToolTip(QApplication::translate("gui_MainWindow", "Toggle software profile state", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        ctrl_isSoftwareControlBtn->setText(QString());
#ifndef QT_NO_TOOLTIP
        ctrl_configSoftwareAutoBtn->setToolTip(QApplication::translate("gui_MainWindow", "Configure Software Auto (Ramps)", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        ctrl_configSoftwareAutoBtn->setText(QString());
        groupBox_channel1->setTitle(QString());
#ifndef QT_NO_TOOLTIP
        ctrl_probe1Temp->setToolTip(QApplication::translate("gui_MainWindow", "Temperature", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        ctrl_channel1speed->setText(QString());
        ctrl_channel1Select->setText(QApplication::translate("gui_MainWindow", "1", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        ctrl_channel1AlarmTemp->setToolTip(QApplication::translate("gui_MainWindow", "Alarm Temperature", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        ctrl_channel1AlarmTemp->setText(QString());
        groupBox_channel2->setTitle(QString());
#ifndef QT_NO_TOOLTIP
        ctrl_probe2Temp->setToolTip(QApplication::translate("gui_MainWindow", "Temperature", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        ctrl_channel2speed->setText(QString());
        ctrl_channel2Select->setText(QApplication::translate("gui_MainWindow", "2", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        ctrl_channel2AlarmTemp->setToolTip(QApplication::translate("gui_MainWindow", "Alarm Temperature", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        ctrl_channel2AlarmTemp->setText(QString());
        groupBox_channel3->setTitle(QString());
#ifndef QT_NO_TOOLTIP
        ctrl_probe3Temp->setToolTip(QApplication::translate("gui_MainWindow", "Temperature", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        ctrl_channel3speed->setText(QString());
        ctrl_channel3Select->setText(QApplication::translate("gui_MainWindow", "3", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        ctrl_channel3AlarmTemp->setToolTip(QApplication::translate("gui_MainWindow", "Alarm Temperature", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        ctrl_channel3AlarmTemp->setText(QString());
        groupBox_channel4->setTitle(QString());
#ifndef QT_NO_TOOLTIP
        ctrl_probe4Temp->setToolTip(QApplication::translate("gui_MainWindow", "Temperature", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        ctrl_channel4speed->setText(QString());
        ctrl_channel4Select->setText(QApplication::translate("gui_MainWindow", "4", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        ctrl_channel4AlarmTemp->setToolTip(QApplication::translate("gui_MainWindow", "Alarm Temperature", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        ctrl_channel4AlarmTemp->setText(QString());
        groupBox_channel5->setTitle(QString());
#ifndef QT_NO_TOOLTIP
        ctrl_probe5Temp->setToolTip(QApplication::translate("gui_MainWindow", "Temperature", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        ctrl_channel5speed->setText(QString());
        ctrl_channel5Select->setText(QApplication::translate("gui_MainWindow", "5", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        ctrl_channel5AlarmTemp->setToolTip(QApplication::translate("gui_MainWindow", "Alarm Temperature", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        ctrl_channel5AlarmTemp->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class gui_MainWindow: public Ui_gui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GUI_MAINWINDOW_H
