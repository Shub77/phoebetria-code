/********************************************************************************
** Form generated from reading UI file 'gui_profiles.ui'
**
** Created by: Qt User Interface Compiler version 4.8.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GUI_PROFILES_H
#define UI_GUI_PROFILES_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QListWidget>
#include <QtGui/QPlainTextEdit>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QSplitter>
#include <QtGui/QTextBrowser>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_gui_Profiles
{
public:
    QGridLayout *gridLayout;
    QSplitter *splitter;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout_3;
    QVBoxLayout *verticalLayout_3;
    QLabel *lbl_profileList;
    QListWidget *ctrl_profileList;
    QVBoxLayout *verticalLayout_4;
    QVBoxLayout *verticalLayout;
    QLabel *lbl_profileName;
    QLineEdit *ctrl_profileName;
    QVBoxLayout *verticalLayout_2;
    QLabel *lbl_profileDescription_2;
    QPlainTextEdit *ctrl_profileDescription;
    QWidget *layoutWidget_2;
    QVBoxLayout *verticalLayout_5;
    QLabel *lbl_profileDescription;
    QTextBrowser *ctrl_profilePreview;
    QHBoxLayout *horizontalLayout;
    QPushButton *ctrl_LoadProfile;
    QPushButton *ctrl_SaveProfile;
    QPushButton *ctrl_EraseProfile;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer;
    QPushButton *ctrl_profileClose;
    QSpacerItem *horizontalSpacer_2;

    void setupUi(QDialog *gui_Profiles)
    {
        if (gui_Profiles->objectName().isEmpty())
            gui_Profiles->setObjectName(QString::fromUtf8("gui_Profiles"));
        gui_Profiles->setWindowModality(Qt::WindowModal);
        gui_Profiles->resize(452, 501);
        gui_Profiles->setMinimumSize(QSize(400, 300));
        gui_Profiles->setSizeGripEnabled(true);
        gridLayout = new QGridLayout(gui_Profiles);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        splitter = new QSplitter(gui_Profiles);
        splitter->setObjectName(QString::fromUtf8("splitter"));
        splitter->setFrameShape(QFrame::NoFrame);
        splitter->setOrientation(Qt::Vertical);
        splitter->setOpaqueResize(true);
        splitter->setChildrenCollapsible(false);
        layoutWidget = new QWidget(splitter);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        horizontalLayout_3 = new QHBoxLayout(layoutWidget);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        lbl_profileList = new QLabel(layoutWidget);
        lbl_profileList->setObjectName(QString::fromUtf8("lbl_profileList"));

        verticalLayout_3->addWidget(lbl_profileList);

        ctrl_profileList = new QListWidget(layoutWidget);
        ctrl_profileList->setObjectName(QString::fromUtf8("ctrl_profileList"));
        ctrl_profileList->setSortingEnabled(true);

        verticalLayout_3->addWidget(ctrl_profileList);


        horizontalLayout_3->addLayout(verticalLayout_3);

        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        lbl_profileName = new QLabel(layoutWidget);
        lbl_profileName->setObjectName(QString::fromUtf8("lbl_profileName"));

        verticalLayout->addWidget(lbl_profileName);

        ctrl_profileName = new QLineEdit(layoutWidget);
        ctrl_profileName->setObjectName(QString::fromUtf8("ctrl_profileName"));

        verticalLayout->addWidget(ctrl_profileName);


        verticalLayout_4->addLayout(verticalLayout);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        lbl_profileDescription_2 = new QLabel(layoutWidget);
        lbl_profileDescription_2->setObjectName(QString::fromUtf8("lbl_profileDescription_2"));

        verticalLayout_2->addWidget(lbl_profileDescription_2);

        ctrl_profileDescription = new QPlainTextEdit(layoutWidget);
        ctrl_profileDescription->setObjectName(QString::fromUtf8("ctrl_profileDescription"));

        verticalLayout_2->addWidget(ctrl_profileDescription);


        verticalLayout_4->addLayout(verticalLayout_2);


        horizontalLayout_3->addLayout(verticalLayout_4);

        splitter->addWidget(layoutWidget);
        layoutWidget_2 = new QWidget(splitter);
        layoutWidget_2->setObjectName(QString::fromUtf8("layoutWidget_2"));
        verticalLayout_5 = new QVBoxLayout(layoutWidget_2);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        verticalLayout_5->setContentsMargins(0, 0, 0, 0);
        lbl_profileDescription = new QLabel(layoutWidget_2);
        lbl_profileDescription->setObjectName(QString::fromUtf8("lbl_profileDescription"));

        verticalLayout_5->addWidget(lbl_profileDescription);

        ctrl_profilePreview = new QTextBrowser(layoutWidget_2);
        ctrl_profilePreview->setObjectName(QString::fromUtf8("ctrl_profilePreview"));

        verticalLayout_5->addWidget(ctrl_profilePreview);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        ctrl_LoadProfile = new QPushButton(layoutWidget_2);
        ctrl_LoadProfile->setObjectName(QString::fromUtf8("ctrl_LoadProfile"));
        ctrl_LoadProfile->setMaximumSize(QSize(80, 16777215));

        horizontalLayout->addWidget(ctrl_LoadProfile);

        ctrl_SaveProfile = new QPushButton(layoutWidget_2);
        ctrl_SaveProfile->setObjectName(QString::fromUtf8("ctrl_SaveProfile"));
        ctrl_SaveProfile->setMaximumSize(QSize(80, 16777215));

        horizontalLayout->addWidget(ctrl_SaveProfile);

        ctrl_EraseProfile = new QPushButton(layoutWidget_2);
        ctrl_EraseProfile->setObjectName(QString::fromUtf8("ctrl_EraseProfile"));
        ctrl_EraseProfile->setMaximumSize(QSize(80, 16777215));

        horizontalLayout->addWidget(ctrl_EraseProfile);


        verticalLayout_5->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        ctrl_profileClose = new QPushButton(layoutWidget_2);
        ctrl_profileClose->setObjectName(QString::fromUtf8("ctrl_profileClose"));
        ctrl_profileClose->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	border: none;\n"
"	margin: 0px;\n"
"    padding: 0px;\n"
"	image: url(:/Images/icon_close.png)\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"	border: none;\n"
"	margin: 0px;\n"
"    padding: 0px;\n"
"	image: url(:/Images/icon_close_lite.png)\n"
"}\n"
"\n"
"QPushButton:disabled {\n"
"	border: none;\n"
"	margin: 0px;\n"
"    padding: 0px;\n"
"	image: url(:/Images/icon_close_lite.png)\n"
"}"));

        horizontalLayout_2->addWidget(ctrl_profileClose);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);


        verticalLayout_5->addLayout(horizontalLayout_2);

        splitter->addWidget(layoutWidget_2);

        gridLayout->addWidget(splitter, 0, 0, 1, 1);

        QWidget::setTabOrder(ctrl_profileList, ctrl_profileName);
        QWidget::setTabOrder(ctrl_profileName, ctrl_profileDescription);
        QWidget::setTabOrder(ctrl_profileDescription, ctrl_profilePreview);
        QWidget::setTabOrder(ctrl_profilePreview, ctrl_LoadProfile);
        QWidget::setTabOrder(ctrl_LoadProfile, ctrl_SaveProfile);
        QWidget::setTabOrder(ctrl_SaveProfile, ctrl_EraseProfile);
        QWidget::setTabOrder(ctrl_EraseProfile, ctrl_profileClose);

        retranslateUi(gui_Profiles);

        QMetaObject::connectSlotsByName(gui_Profiles);
    } // setupUi

    void retranslateUi(QDialog *gui_Profiles)
    {
        gui_Profiles->setWindowTitle(QApplication::translate("gui_Profiles", "Profile", 0, QApplication::UnicodeUTF8));
        lbl_profileList->setText(QApplication::translate("gui_Profiles", "Profile", 0, QApplication::UnicodeUTF8));
        lbl_profileName->setText(QApplication::translate("gui_Profiles", "Name", 0, QApplication::UnicodeUTF8));
        lbl_profileDescription_2->setText(QApplication::translate("gui_Profiles", "Description", 0, QApplication::UnicodeUTF8));
        lbl_profileDescription->setText(QApplication::translate("gui_Profiles", "Preview", 0, QApplication::UnicodeUTF8));
        ctrl_LoadProfile->setText(QApplication::translate("gui_Profiles", "Load", 0, QApplication::UnicodeUTF8));
        ctrl_SaveProfile->setText(QApplication::translate("gui_Profiles", "Save", 0, QApplication::UnicodeUTF8));
        ctrl_EraseProfile->setText(QApplication::translate("gui_Profiles", "Delete", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        ctrl_profileClose->setToolTip(QApplication::translate("gui_Profiles", "Close", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        ctrl_profileClose->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class gui_Profiles: public Ui_gui_Profiles {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GUI_PROFILES_H
