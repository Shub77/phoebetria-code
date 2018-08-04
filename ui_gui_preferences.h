/********************************************************************************
** Form generated from reading UI file 'gui_preferences.ui'
**
** Created by: Qt User Interface Compiler version 4.8.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GUI_PREFERENCES_H
#define UI_GUI_PREFERENCES_H

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
#include <QtGui/QGroupBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QListWidget>
#include <QtGui/QSpacerItem>
#include <QtGui/QStackedWidget>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_gui_Preferences
{
public:
    QGridLayout *gridLayout_5;
    QDialogButtonBox *ctrl_actionButtons;
    QGridLayout *gridLayout_2;
    QListWidget *ctrl_preferenceTabList;
    QStackedWidget *ctrl_preferenceTabs;
    QWidget *page_generalSettings;
    QGridLayout *gridLayout_4;
    QLabel *lbl_startupProfile;
    QCheckBox *ctrl_showTooltipOnMinimize;
    QLabel *lbl_shutdownProfile;
    QCheckBox *ctrl_minimizeToTray;
    QCheckBox *ctrl_minimizeOnStart;
    QFrame *line;
    QLabel *lbl_ShowTooltipOnMinimize;
    QCheckBox *ctrl_quitOnClose;
    QLabel *lbl_MinimizeToTray;
    QLabel *lbl_minimizeOnStart;
    QLabel *lbl_quitOnClose;
    QComboBox *ctrl_startupProfile;
    QComboBox *ctrl_shutdownProfile;
    QCheckBox *ctrl_alwaysShowTrayIcon;
    QLabel *lbl_alwaysShowTrayIcon;
    QWidget *page_channelSettings;
    QGridLayout *gridLayout;
    QLabel *lbl_useLogRpmScale;
    QCheckBox *ctrl_useLogRpmScale;
    QSpacerItem *verticalSpacer;
    QGroupBox *groupBox_3;
    QGridLayout *gridLayout_3;
    QLineEdit *ctrl_channel3FanName;
    QLabel *lbl_channel2Name;
    QLineEdit *ctrl_channel1FanName;
    QLineEdit *ctrl_channel5FanName;
    QLineEdit *ctrl_channel2FanName;
    QLineEdit *ctrl_channel4FanName;
    QLabel *lbl_channel3Name;
    QLabel *lbl_channel4Name;
    QLabel *lbl_channel5Name;
    QLabel *lbl_channel1Name;
    QLineEdit *ctrl_channel1TempName;
    QLineEdit *ctrl_channel2TempName;
    QLineEdit *ctrl_channel3TempName;
    QLineEdit *ctrl_channel4TempName;
    QLineEdit *ctrl_channel5TempName;
    QLabel *lbl_channelNameHeader;
    QLabel *lbl_channelTempHeader;
    QWidget *page_appearanceSettings;
    QGridLayout *gridLayout_6;
    QComboBox *ctrl_style;
    QLabel *lbl_selectStyle;
    QLabel *lbl_selectLanguage;
    QSpacerItem *verticalSpacer_2;
    QSpacerItem *verticalSpacer_3;
    QComboBox *ctrl_language;
    QCheckBox *ctrl_showChannelLabels;
    QLabel *lbl_showChannelLabels;

    void setupUi(QDialog *gui_Preferences)
    {
        if (gui_Preferences->objectName().isEmpty())
            gui_Preferences->setObjectName(QString::fromUtf8("gui_Preferences"));
        gui_Preferences->resize(650, 350);
        gui_Preferences->setMinimumSize(QSize(600, 350));
        gui_Preferences->setSizeGripEnabled(true);
        gui_Preferences->setModal(false);
        gridLayout_5 = new QGridLayout(gui_Preferences);
        gridLayout_5->setSpacing(10);
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        gridLayout_5->setContentsMargins(10, 10, 10, 20);
        ctrl_actionButtons = new QDialogButtonBox(gui_Preferences);
        ctrl_actionButtons->setObjectName(QString::fromUtf8("ctrl_actionButtons"));
        ctrl_actionButtons->setMinimumSize(QSize(0, 0));
        ctrl_actionButtons->setOrientation(Qt::Horizontal);
        ctrl_actionButtons->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        gridLayout_5->addWidget(ctrl_actionButtons, 2, 0, 1, 1);

        gridLayout_2 = new QGridLayout();
        gridLayout_2->setSpacing(5);
        gridLayout_2->setContentsMargins(5, 5, 5, 5);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        ctrl_preferenceTabList = new QListWidget(gui_Preferences);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Images/pref_gears.png"), QSize(), QIcon::Normal, QIcon::Off);
        QListWidgetItem *__qlistwidgetitem = new QListWidgetItem(ctrl_preferenceTabList);
        __qlistwidgetitem->setIcon(icon);
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Images/pref_sliders.png"), QSize(), QIcon::Normal, QIcon::Off);
        QListWidgetItem *__qlistwidgetitem1 = new QListWidgetItem(ctrl_preferenceTabList);
        __qlistwidgetitem1->setIcon(icon1);
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/Images/pref_appearance.png"), QSize(), QIcon::Normal, QIcon::Off);
        QListWidgetItem *__qlistwidgetitem2 = new QListWidgetItem(ctrl_preferenceTabList);
        __qlistwidgetitem2->setIcon(icon2);
        ctrl_preferenceTabList->setObjectName(QString::fromUtf8("ctrl_preferenceTabList"));
        ctrl_preferenceTabList->setMinimumSize(QSize(0, 0));
        ctrl_preferenceTabList->setMaximumSize(QSize(200, 16777215));
        ctrl_preferenceTabList->setSizeIncrement(QSize(0, 0));
        QFont font;
        font.setPointSize(10);
        ctrl_preferenceTabList->setFont(font);
        ctrl_preferenceTabList->setIconSize(QSize(40, 35));
        ctrl_preferenceTabList->setSpacing(10);

        gridLayout_2->addWidget(ctrl_preferenceTabList, 0, 0, 1, 1);

        ctrl_preferenceTabs = new QStackedWidget(gui_Preferences);
        ctrl_preferenceTabs->setObjectName(QString::fromUtf8("ctrl_preferenceTabs"));
        ctrl_preferenceTabs->setMinimumSize(QSize(300, 0));
        ctrl_preferenceTabs->setFrameShape(QFrame::WinPanel);
        ctrl_preferenceTabs->setFrameShadow(QFrame::Sunken);
        page_generalSettings = new QWidget();
        page_generalSettings->setObjectName(QString::fromUtf8("page_generalSettings"));
        gridLayout_4 = new QGridLayout(page_generalSettings);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        lbl_startupProfile = new QLabel(page_generalSettings);
        lbl_startupProfile->setObjectName(QString::fromUtf8("lbl_startupProfile"));

        gridLayout_4->addWidget(lbl_startupProfile, 10, 0, 1, 2);

        ctrl_showTooltipOnMinimize = new QCheckBox(page_generalSettings);
        ctrl_showTooltipOnMinimize->setObjectName(QString::fromUtf8("ctrl_showTooltipOnMinimize"));
        ctrl_showTooltipOnMinimize->setEnabled(true);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(ctrl_showTooltipOnMinimize->sizePolicy().hasHeightForWidth());
        ctrl_showTooltipOnMinimize->setSizePolicy(sizePolicy);
        ctrl_showTooltipOnMinimize->setStyleSheet(QString::fromUtf8(""));

        gridLayout_4->addWidget(ctrl_showTooltipOnMinimize, 3, 2, 1, 1);

        lbl_shutdownProfile = new QLabel(page_generalSettings);
        lbl_shutdownProfile->setObjectName(QString::fromUtf8("lbl_shutdownProfile"));

        gridLayout_4->addWidget(lbl_shutdownProfile, 11, 0, 1, 2);

        ctrl_minimizeToTray = new QCheckBox(page_generalSettings);
        ctrl_minimizeToTray->setObjectName(QString::fromUtf8("ctrl_minimizeToTray"));
        sizePolicy.setHeightForWidth(ctrl_minimizeToTray->sizePolicy().hasHeightForWidth());
        ctrl_minimizeToTray->setSizePolicy(sizePolicy);
        ctrl_minimizeToTray->setStyleSheet(QString::fromUtf8(""));

        gridLayout_4->addWidget(ctrl_minimizeToTray, 0, 2, 1, 1);

        ctrl_minimizeOnStart = new QCheckBox(page_generalSettings);
        ctrl_minimizeOnStart->setObjectName(QString::fromUtf8("ctrl_minimizeOnStart"));
        sizePolicy.setHeightForWidth(ctrl_minimizeOnStart->sizePolicy().hasHeightForWidth());
        ctrl_minimizeOnStart->setSizePolicy(sizePolicy);
        ctrl_minimizeOnStart->setStyleSheet(QString::fromUtf8(""));

        gridLayout_4->addWidget(ctrl_minimizeOnStart, 1, 2, 1, 1);

        line = new QFrame(page_generalSettings);
        line->setObjectName(QString::fromUtf8("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        gridLayout_4->addWidget(line, 7, 0, 1, 6);

        lbl_ShowTooltipOnMinimize = new QLabel(page_generalSettings);
        lbl_ShowTooltipOnMinimize->setObjectName(QString::fromUtf8("lbl_ShowTooltipOnMinimize"));
        lbl_ShowTooltipOnMinimize->setEnabled(true);
        lbl_ShowTooltipOnMinimize->setWordWrap(true);

        gridLayout_4->addWidget(lbl_ShowTooltipOnMinimize, 3, 0, 1, 1);

        ctrl_quitOnClose = new QCheckBox(page_generalSettings);
        ctrl_quitOnClose->setObjectName(QString::fromUtf8("ctrl_quitOnClose"));
        sizePolicy.setHeightForWidth(ctrl_quitOnClose->sizePolicy().hasHeightForWidth());
        ctrl_quitOnClose->setSizePolicy(sizePolicy);
        ctrl_quitOnClose->setStyleSheet(QString::fromUtf8(""));

        gridLayout_4->addWidget(ctrl_quitOnClose, 2, 2, 1, 1);

        lbl_MinimizeToTray = new QLabel(page_generalSettings);
        lbl_MinimizeToTray->setObjectName(QString::fromUtf8("lbl_MinimizeToTray"));

        gridLayout_4->addWidget(lbl_MinimizeToTray, 0, 0, 1, 1);

        lbl_minimizeOnStart = new QLabel(page_generalSettings);
        lbl_minimizeOnStart->setObjectName(QString::fromUtf8("lbl_minimizeOnStart"));

        gridLayout_4->addWidget(lbl_minimizeOnStart, 1, 0, 1, 1);

        lbl_quitOnClose = new QLabel(page_generalSettings);
        lbl_quitOnClose->setObjectName(QString::fromUtf8("lbl_quitOnClose"));

        gridLayout_4->addWidget(lbl_quitOnClose, 2, 0, 1, 1);

        ctrl_startupProfile = new QComboBox(page_generalSettings);
        ctrl_startupProfile->setObjectName(QString::fromUtf8("ctrl_startupProfile"));
        ctrl_startupProfile->setStyleSheet(QString::fromUtf8(""));

        gridLayout_4->addWidget(ctrl_startupProfile, 10, 2, 1, 4);

        ctrl_shutdownProfile = new QComboBox(page_generalSettings);
        ctrl_shutdownProfile->setObjectName(QString::fromUtf8("ctrl_shutdownProfile"));
        ctrl_shutdownProfile->setStyleSheet(QString::fromUtf8(""));
        ctrl_shutdownProfile->setEditable(false);

        gridLayout_4->addWidget(ctrl_shutdownProfile, 11, 2, 1, 4);

        ctrl_alwaysShowTrayIcon = new QCheckBox(page_generalSettings);
        ctrl_alwaysShowTrayIcon->setObjectName(QString::fromUtf8("ctrl_alwaysShowTrayIcon"));
        sizePolicy.setHeightForWidth(ctrl_alwaysShowTrayIcon->sizePolicy().hasHeightForWidth());
        ctrl_alwaysShowTrayIcon->setSizePolicy(sizePolicy);

        gridLayout_4->addWidget(ctrl_alwaysShowTrayIcon, 0, 5, 1, 1);

        lbl_alwaysShowTrayIcon = new QLabel(page_generalSettings);
        lbl_alwaysShowTrayIcon->setObjectName(QString::fromUtf8("lbl_alwaysShowTrayIcon"));

        gridLayout_4->addWidget(lbl_alwaysShowTrayIcon, 0, 3, 1, 2);

        ctrl_preferenceTabs->addWidget(page_generalSettings);
        page_channelSettings = new QWidget();
        page_channelSettings->setObjectName(QString::fromUtf8("page_channelSettings"));
        gridLayout = new QGridLayout(page_channelSettings);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        lbl_useLogRpmScale = new QLabel(page_channelSettings);
        lbl_useLogRpmScale->setObjectName(QString::fromUtf8("lbl_useLogRpmScale"));

        gridLayout->addWidget(lbl_useLogRpmScale, 2, 0, 1, 4);

        ctrl_useLogRpmScale = new QCheckBox(page_channelSettings);
        ctrl_useLogRpmScale->setObjectName(QString::fromUtf8("ctrl_useLogRpmScale"));
        ctrl_useLogRpmScale->setStyleSheet(QString::fromUtf8(""));

        gridLayout->addWidget(ctrl_useLogRpmScale, 2, 4, 1, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer, 3, 0, 1, 6);

        groupBox_3 = new QGroupBox(page_channelSettings);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        groupBox_3->setFlat(false);
        gridLayout_3 = new QGridLayout(groupBox_3);
        gridLayout_3->setContentsMargins(5, 5, 5, 5);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        ctrl_channel3FanName = new QLineEdit(groupBox_3);
        ctrl_channel3FanName->setObjectName(QString::fromUtf8("ctrl_channel3FanName"));

        gridLayout_3->addWidget(ctrl_channel3FanName, 3, 1, 1, 1);

        lbl_channel2Name = new QLabel(groupBox_3);
        lbl_channel2Name->setObjectName(QString::fromUtf8("lbl_channel2Name"));

        gridLayout_3->addWidget(lbl_channel2Name, 2, 0, 1, 1);

        ctrl_channel1FanName = new QLineEdit(groupBox_3);
        ctrl_channel1FanName->setObjectName(QString::fromUtf8("ctrl_channel1FanName"));

        gridLayout_3->addWidget(ctrl_channel1FanName, 1, 1, 1, 1);

        ctrl_channel5FanName = new QLineEdit(groupBox_3);
        ctrl_channel5FanName->setObjectName(QString::fromUtf8("ctrl_channel5FanName"));

        gridLayout_3->addWidget(ctrl_channel5FanName, 6, 1, 1, 1);

        ctrl_channel2FanName = new QLineEdit(groupBox_3);
        ctrl_channel2FanName->setObjectName(QString::fromUtf8("ctrl_channel2FanName"));

        gridLayout_3->addWidget(ctrl_channel2FanName, 2, 1, 1, 1);

        ctrl_channel4FanName = new QLineEdit(groupBox_3);
        ctrl_channel4FanName->setObjectName(QString::fromUtf8("ctrl_channel4FanName"));

        gridLayout_3->addWidget(ctrl_channel4FanName, 4, 1, 1, 1);

        lbl_channel3Name = new QLabel(groupBox_3);
        lbl_channel3Name->setObjectName(QString::fromUtf8("lbl_channel3Name"));

        gridLayout_3->addWidget(lbl_channel3Name, 3, 0, 1, 1);

        lbl_channel4Name = new QLabel(groupBox_3);
        lbl_channel4Name->setObjectName(QString::fromUtf8("lbl_channel4Name"));

        gridLayout_3->addWidget(lbl_channel4Name, 4, 0, 1, 1);

        lbl_channel5Name = new QLabel(groupBox_3);
        lbl_channel5Name->setObjectName(QString::fromUtf8("lbl_channel5Name"));

        gridLayout_3->addWidget(lbl_channel5Name, 6, 0, 1, 1);

        lbl_channel1Name = new QLabel(groupBox_3);
        lbl_channel1Name->setObjectName(QString::fromUtf8("lbl_channel1Name"));

        gridLayout_3->addWidget(lbl_channel1Name, 1, 0, 1, 1);

        ctrl_channel1TempName = new QLineEdit(groupBox_3);
        ctrl_channel1TempName->setObjectName(QString::fromUtf8("ctrl_channel1TempName"));

        gridLayout_3->addWidget(ctrl_channel1TempName, 1, 2, 1, 1);

        ctrl_channel2TempName = new QLineEdit(groupBox_3);
        ctrl_channel2TempName->setObjectName(QString::fromUtf8("ctrl_channel2TempName"));

        gridLayout_3->addWidget(ctrl_channel2TempName, 2, 2, 1, 1);

        ctrl_channel3TempName = new QLineEdit(groupBox_3);
        ctrl_channel3TempName->setObjectName(QString::fromUtf8("ctrl_channel3TempName"));

        gridLayout_3->addWidget(ctrl_channel3TempName, 3, 2, 1, 1);

        ctrl_channel4TempName = new QLineEdit(groupBox_3);
        ctrl_channel4TempName->setObjectName(QString::fromUtf8("ctrl_channel4TempName"));

        gridLayout_3->addWidget(ctrl_channel4TempName, 4, 2, 1, 1);

        ctrl_channel5TempName = new QLineEdit(groupBox_3);
        ctrl_channel5TempName->setObjectName(QString::fromUtf8("ctrl_channel5TempName"));

        gridLayout_3->addWidget(ctrl_channel5TempName, 6, 2, 1, 1);

        lbl_channelNameHeader = new QLabel(groupBox_3);
        lbl_channelNameHeader->setObjectName(QString::fromUtf8("lbl_channelNameHeader"));

        gridLayout_3->addWidget(lbl_channelNameHeader, 0, 1, 1, 1);

        lbl_channelTempHeader = new QLabel(groupBox_3);
        lbl_channelTempHeader->setObjectName(QString::fromUtf8("lbl_channelTempHeader"));

        gridLayout_3->addWidget(lbl_channelTempHeader, 0, 2, 1, 1);


        gridLayout->addWidget(groupBox_3, 0, 0, 2, 6);

        ctrl_preferenceTabs->addWidget(page_channelSettings);
        page_appearanceSettings = new QWidget();
        page_appearanceSettings->setObjectName(QString::fromUtf8("page_appearanceSettings"));
        gridLayout_6 = new QGridLayout(page_appearanceSettings);
        gridLayout_6->setObjectName(QString::fromUtf8("gridLayout_6"));
        ctrl_style = new QComboBox(page_appearanceSettings);
        ctrl_style->setObjectName(QString::fromUtf8("ctrl_style"));

        gridLayout_6->addWidget(ctrl_style, 2, 1, 1, 1);

        lbl_selectStyle = new QLabel(page_appearanceSettings);
        lbl_selectStyle->setObjectName(QString::fromUtf8("lbl_selectStyle"));

        gridLayout_6->addWidget(lbl_selectStyle, 2, 0, 1, 1);

        lbl_selectLanguage = new QLabel(page_appearanceSettings);
        lbl_selectLanguage->setObjectName(QString::fromUtf8("lbl_selectLanguage"));

        gridLayout_6->addWidget(lbl_selectLanguage, 3, 0, 1, 1);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_6->addItem(verticalSpacer_2, 5, 0, 1, 1);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_6->addItem(verticalSpacer_3, 0, 0, 1, 1);

        ctrl_language = new QComboBox(page_appearanceSettings);
        ctrl_language->setObjectName(QString::fromUtf8("ctrl_language"));

        gridLayout_6->addWidget(ctrl_language, 3, 1, 1, 1);

        ctrl_showChannelLabels = new QCheckBox(page_appearanceSettings);
        ctrl_showChannelLabels->setObjectName(QString::fromUtf8("ctrl_showChannelLabels"));

        gridLayout_6->addWidget(ctrl_showChannelLabels, 1, 1, 1, 1);

        lbl_showChannelLabels = new QLabel(page_appearanceSettings);
        lbl_showChannelLabels->setObjectName(QString::fromUtf8("lbl_showChannelLabels"));

        gridLayout_6->addWidget(lbl_showChannelLabels, 1, 0, 1, 1);

        ctrl_preferenceTabs->addWidget(page_appearanceSettings);

        gridLayout_2->addWidget(ctrl_preferenceTabs, 0, 1, 1, 2);


        gridLayout_5->addLayout(gridLayout_2, 1, 0, 1, 1);

        QWidget::setTabOrder(ctrl_preferenceTabList, ctrl_minimizeToTray);
        QWidget::setTabOrder(ctrl_minimizeToTray, ctrl_alwaysShowTrayIcon);
        QWidget::setTabOrder(ctrl_alwaysShowTrayIcon, ctrl_minimizeOnStart);
        QWidget::setTabOrder(ctrl_minimizeOnStart, ctrl_quitOnClose);
        QWidget::setTabOrder(ctrl_quitOnClose, ctrl_showTooltipOnMinimize);
        QWidget::setTabOrder(ctrl_showTooltipOnMinimize, ctrl_startupProfile);
        QWidget::setTabOrder(ctrl_startupProfile, ctrl_shutdownProfile);
        QWidget::setTabOrder(ctrl_shutdownProfile, ctrl_channel1FanName);
        QWidget::setTabOrder(ctrl_channel1FanName, ctrl_channel1TempName);
        QWidget::setTabOrder(ctrl_channel1TempName, ctrl_channel2FanName);
        QWidget::setTabOrder(ctrl_channel2FanName, ctrl_channel2TempName);
        QWidget::setTabOrder(ctrl_channel2TempName, ctrl_channel3FanName);
        QWidget::setTabOrder(ctrl_channel3FanName, ctrl_channel3TempName);
        QWidget::setTabOrder(ctrl_channel3TempName, ctrl_channel4FanName);
        QWidget::setTabOrder(ctrl_channel4FanName, ctrl_channel4TempName);
        QWidget::setTabOrder(ctrl_channel4TempName, ctrl_channel5FanName);
        QWidget::setTabOrder(ctrl_channel5FanName, ctrl_channel5TempName);
        QWidget::setTabOrder(ctrl_channel5TempName, ctrl_useLogRpmScale);
        QWidget::setTabOrder(ctrl_useLogRpmScale, ctrl_actionButtons);

        retranslateUi(gui_Preferences);
        QObject::connect(ctrl_actionButtons, SIGNAL(accepted()), gui_Preferences, SLOT(accept()));
        QObject::connect(ctrl_actionButtons, SIGNAL(rejected()), gui_Preferences, SLOT(reject()));

        ctrl_preferenceTabs->setCurrentIndex(2);


        QMetaObject::connectSlotsByName(gui_Preferences);
    } // setupUi

    void retranslateUi(QDialog *gui_Preferences)
    {
        gui_Preferences->setWindowTitle(QApplication::translate("gui_Preferences", "Preferences", 0, QApplication::UnicodeUTF8));

        const bool __sortingEnabled = ctrl_preferenceTabList->isSortingEnabled();
        ctrl_preferenceTabList->setSortingEnabled(false);
        QListWidgetItem *___qlistwidgetitem = ctrl_preferenceTabList->item(0);
        ___qlistwidgetitem->setText(QApplication::translate("gui_Preferences", "General Settings", 0, QApplication::UnicodeUTF8));
        QListWidgetItem *___qlistwidgetitem1 = ctrl_preferenceTabList->item(1);
        ___qlistwidgetitem1->setText(QApplication::translate("gui_Preferences", "Channel Settings", 0, QApplication::UnicodeUTF8));
        QListWidgetItem *___qlistwidgetitem2 = ctrl_preferenceTabList->item(2);
        ___qlistwidgetitem2->setText(QApplication::translate("gui_Preferences", "Appearance", 0, QApplication::UnicodeUTF8));
        ctrl_preferenceTabList->setSortingEnabled(__sortingEnabled);

        lbl_startupProfile->setText(QApplication::translate("gui_Preferences", "Startup Profile", 0, QApplication::UnicodeUTF8));
        ctrl_showTooltipOnMinimize->setText(QString());
        lbl_shutdownProfile->setText(QApplication::translate("gui_Preferences", "Shutdown Profile", 0, QApplication::UnicodeUTF8));
        ctrl_minimizeToTray->setText(QString());
        ctrl_minimizeOnStart->setText(QString());
        lbl_ShowTooltipOnMinimize->setText(QApplication::translate("gui_Preferences", "Show Tooltips while Minimized", 0, QApplication::UnicodeUTF8));
        ctrl_quitOnClose->setText(QString());
        lbl_MinimizeToTray->setText(QApplication::translate("gui_Preferences", "Minimize to Tray", 0, QApplication::UnicodeUTF8));
        lbl_minimizeOnStart->setText(QApplication::translate("gui_Preferences", "Start Minimized", 0, QApplication::UnicodeUTF8));
        lbl_quitOnClose->setText(QApplication::translate("gui_Preferences", "Quit on Close", 0, QApplication::UnicodeUTF8));
        ctrl_alwaysShowTrayIcon->setText(QString());
        lbl_alwaysShowTrayIcon->setText(QApplication::translate("gui_Preferences", "Always Show Tray Icon", 0, QApplication::UnicodeUTF8));
        lbl_useLogRpmScale->setText(QApplication::translate("gui_Preferences", "RPM sliders use logarithmic scale", 0, QApplication::UnicodeUTF8));
        ctrl_useLogRpmScale->setText(QString());
        groupBox_3->setTitle(QString());
        lbl_channel2Name->setText(QApplication::translate("gui_Preferences", "Channel 2", 0, QApplication::UnicodeUTF8));
        lbl_channel3Name->setText(QApplication::translate("gui_Preferences", "Channel 3", 0, QApplication::UnicodeUTF8));
        lbl_channel4Name->setText(QApplication::translate("gui_Preferences", "Channel 4", 0, QApplication::UnicodeUTF8));
        lbl_channel5Name->setText(QApplication::translate("gui_Preferences", "Channel 5", 0, QApplication::UnicodeUTF8));
        lbl_channel1Name->setText(QApplication::translate("gui_Preferences", "Channel 1", 0, QApplication::UnicodeUTF8));
        lbl_channelNameHeader->setText(QApplication::translate("gui_Preferences", "Fan Name", 0, QApplication::UnicodeUTF8));
        lbl_channelTempHeader->setText(QApplication::translate("gui_Preferences", "Temperature Probe", 0, QApplication::UnicodeUTF8));
        lbl_selectStyle->setText(QApplication::translate("gui_Preferences", "Style", 0, QApplication::UnicodeUTF8));
        lbl_selectLanguage->setText(QApplication::translate("gui_Preferences", "Language", 0, QApplication::UnicodeUTF8));
        ctrl_showChannelLabels->setText(QString());
        lbl_showChannelLabels->setText(QApplication::translate("gui_Preferences", "Show Channel Labels", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class gui_Preferences: public Ui_gui_Preferences {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GUI_PREFERENCES_H
