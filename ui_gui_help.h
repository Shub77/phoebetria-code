/********************************************************************************
** Form generated from reading UI file 'gui_help.ui'
**
** Created by: Qt User Interface Compiler version 4.8.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GUI_HELP_H
#define UI_GUI_HELP_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QStackedWidget>
#include <QtGui/QTextBrowser>
#include <QtGui/QTreeWidget>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_gui_Help
{
public:
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *ctrl_close;
    QTreeWidget *ctrl_helpList;
    QStackedWidget *ctrl_helpBrowser;
    QWidget *page_Start;
    QVBoxLayout *verticalLayout;
    QLineEdit *lbl_Start;
    QTextBrowser *html_Start;
    QWidget *page_About;
    QVBoxLayout *verticalLayout_2;
    QLineEdit *lbl_About;
    QTextBrowser *html_About;
    QWidget *page_Diagnostic;
    QVBoxLayout *verticalLayout_10;
    QLineEdit *lbl_Diagnostic;
    QTextBrowser *html_Diagnostic;
    QWidget *page_Main;
    QVBoxLayout *verticalLayout_9;
    QLineEdit *lbl_Main;
    QTextBrowser *html_Main;
    QWidget *page_Profile;
    QVBoxLayout *verticalLayout_8;
    QLineEdit *lbl_Profile;
    QTextBrowser *html_Profile;
    QWidget *page_SoftwareAuto;
    QVBoxLayout *verticalLayout_7;
    QLineEdit *lbl_SoftwareAuto;
    QTextBrowser *html_SoftwareAuto;
    QWidget *page_Preferences;
    QVBoxLayout *verticalLayout_6;
    QLineEdit *lbl_Preferences;
    QTextBrowser *htmlPreferences;
    QWidget *page_Appearance;
    QVBoxLayout *verticalLayout_5;
    QLineEdit *lbl_Appearance;
    QTextBrowser *html_Appearance;
    QWidget *page_Channel;
    QVBoxLayout *verticalLayout_4;
    QLineEdit *lineEdit;
    QTextBrowser *html_Channel;
    QWidget *page_General;
    QVBoxLayout *verticalLayout_3;
    QLineEdit *lineEdit_2;
    QTextBrowser *html_General;

    void setupUi(QDialog *gui_Help)
    {
        if (gui_Help->objectName().isEmpty())
            gui_Help->setObjectName(QString::fromUtf8("gui_Help"));
        gui_Help->resize(1024, 512);
        gui_Help->setMinimumSize(QSize(1024, 512));
        gridLayout = new QGridLayout(gui_Help);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        ctrl_close = new QPushButton(gui_Help);
        ctrl_close->setObjectName(QString::fromUtf8("ctrl_close"));

        horizontalLayout->addWidget(ctrl_close);


        gridLayout->addLayout(horizontalLayout, 1, 0, 1, 3);

        ctrl_helpList = new QTreeWidget(gui_Help);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem();
        __qtreewidgetitem->setText(1, QString::fromUtf8("Page"));
        ctrl_helpList->setHeaderItem(__qtreewidgetitem);
        QTreeWidgetItem *__qtreewidgetitem1 = new QTreeWidgetItem(ctrl_helpList);
        QTreeWidgetItem *__qtreewidgetitem2 = new QTreeWidgetItem(__qtreewidgetitem1);
        __qtreewidgetitem2->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
        new QTreeWidgetItem(__qtreewidgetitem1);
        new QTreeWidgetItem(__qtreewidgetitem1);
        new QTreeWidgetItem(__qtreewidgetitem1);
        new QTreeWidgetItem(__qtreewidgetitem1);
        QTreeWidgetItem *__qtreewidgetitem3 = new QTreeWidgetItem(ctrl_helpList);
        new QTreeWidgetItem(__qtreewidgetitem3);
        new QTreeWidgetItem(__qtreewidgetitem3);
        new QTreeWidgetItem(__qtreewidgetitem3);
        ctrl_helpList->setObjectName(QString::fromUtf8("ctrl_helpList"));
        ctrl_helpList->setMaximumSize(QSize(200, 16777215));
        ctrl_helpList->setAutoExpandDelay(0);
        ctrl_helpList->setItemsExpandable(true);

        gridLayout->addWidget(ctrl_helpList, 0, 0, 1, 1);

        ctrl_helpBrowser = new QStackedWidget(gui_Help);
        ctrl_helpBrowser->setObjectName(QString::fromUtf8("ctrl_helpBrowser"));
        QFont font;
        font.setPointSize(18);
        ctrl_helpBrowser->setFont(font);
        page_Start = new QWidget();
        page_Start->setObjectName(QString::fromUtf8("page_Start"));
        verticalLayout = new QVBoxLayout(page_Start);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        lbl_Start = new QLineEdit(page_Start);
        lbl_Start->setObjectName(QString::fromUtf8("lbl_Start"));
        lbl_Start->setReadOnly(true);

        verticalLayout->addWidget(lbl_Start);

        html_Start = new QTextBrowser(page_Start);
        html_Start->setObjectName(QString::fromUtf8("html_Start"));
        html_Start->setSource(QUrl(QString::fromUtf8("qrc:/help/window_into.html")));
        html_Start->setOpenLinks(false);

        verticalLayout->addWidget(html_Start);

        ctrl_helpBrowser->addWidget(page_Start);
        page_About = new QWidget();
        page_About->setObjectName(QString::fromUtf8("page_About"));
        verticalLayout_2 = new QVBoxLayout(page_About);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        lbl_About = new QLineEdit(page_About);
        lbl_About->setObjectName(QString::fromUtf8("lbl_About"));
        lbl_About->setReadOnly(true);

        verticalLayout_2->addWidget(lbl_About);

        html_About = new QTextBrowser(page_About);
        html_About->setObjectName(QString::fromUtf8("html_About"));
        html_About->setSource(QUrl(QString::fromUtf8("qrc:/help/window_about.html")));

        verticalLayout_2->addWidget(html_About);

        ctrl_helpBrowser->addWidget(page_About);
        page_Diagnostic = new QWidget();
        page_Diagnostic->setObjectName(QString::fromUtf8("page_Diagnostic"));
        verticalLayout_10 = new QVBoxLayout(page_Diagnostic);
        verticalLayout_10->setObjectName(QString::fromUtf8("verticalLayout_10"));
        lbl_Diagnostic = new QLineEdit(page_Diagnostic);
        lbl_Diagnostic->setObjectName(QString::fromUtf8("lbl_Diagnostic"));
        lbl_Diagnostic->setReadOnly(true);

        verticalLayout_10->addWidget(lbl_Diagnostic);

        html_Diagnostic = new QTextBrowser(page_Diagnostic);
        html_Diagnostic->setObjectName(QString::fromUtf8("html_Diagnostic"));
        html_Diagnostic->setSource(QUrl(QString::fromUtf8("qrc:/help/window_diagnostic.html")));

        verticalLayout_10->addWidget(html_Diagnostic);

        ctrl_helpBrowser->addWidget(page_Diagnostic);
        page_Main = new QWidget();
        page_Main->setObjectName(QString::fromUtf8("page_Main"));
        verticalLayout_9 = new QVBoxLayout(page_Main);
        verticalLayout_9->setObjectName(QString::fromUtf8("verticalLayout_9"));
        lbl_Main = new QLineEdit(page_Main);
        lbl_Main->setObjectName(QString::fromUtf8("lbl_Main"));
        lbl_Main->setReadOnly(true);

        verticalLayout_9->addWidget(lbl_Main);

        html_Main = new QTextBrowser(page_Main);
        html_Main->setObjectName(QString::fromUtf8("html_Main"));
        html_Main->setSource(QUrl(QString::fromUtf8("qrc:/help/window_main.html")));

        verticalLayout_9->addWidget(html_Main);

        ctrl_helpBrowser->addWidget(page_Main);
        page_Profile = new QWidget();
        page_Profile->setObjectName(QString::fromUtf8("page_Profile"));
        verticalLayout_8 = new QVBoxLayout(page_Profile);
        verticalLayout_8->setObjectName(QString::fromUtf8("verticalLayout_8"));
        lbl_Profile = new QLineEdit(page_Profile);
        lbl_Profile->setObjectName(QString::fromUtf8("lbl_Profile"));
        lbl_Profile->setReadOnly(true);

        verticalLayout_8->addWidget(lbl_Profile);

        html_Profile = new QTextBrowser(page_Profile);
        html_Profile->setObjectName(QString::fromUtf8("html_Profile"));
        html_Profile->setSource(QUrl(QString::fromUtf8("qrc:/help/window_profile.html")));

        verticalLayout_8->addWidget(html_Profile);

        ctrl_helpBrowser->addWidget(page_Profile);
        page_SoftwareAuto = new QWidget();
        page_SoftwareAuto->setObjectName(QString::fromUtf8("page_SoftwareAuto"));
        verticalLayout_7 = new QVBoxLayout(page_SoftwareAuto);
        verticalLayout_7->setObjectName(QString::fromUtf8("verticalLayout_7"));
        lbl_SoftwareAuto = new QLineEdit(page_SoftwareAuto);
        lbl_SoftwareAuto->setObjectName(QString::fromUtf8("lbl_SoftwareAuto"));
        lbl_SoftwareAuto->setReadOnly(true);

        verticalLayout_7->addWidget(lbl_SoftwareAuto);

        html_SoftwareAuto = new QTextBrowser(page_SoftwareAuto);
        html_SoftwareAuto->setObjectName(QString::fromUtf8("html_SoftwareAuto"));
        html_SoftwareAuto->setSource(QUrl(QString::fromUtf8("qrc:/help/window_softwareauto.html")));

        verticalLayout_7->addWidget(html_SoftwareAuto);

        ctrl_helpBrowser->addWidget(page_SoftwareAuto);
        page_Preferences = new QWidget();
        page_Preferences->setObjectName(QString::fromUtf8("page_Preferences"));
        verticalLayout_6 = new QVBoxLayout(page_Preferences);
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        lbl_Preferences = new QLineEdit(page_Preferences);
        lbl_Preferences->setObjectName(QString::fromUtf8("lbl_Preferences"));
        lbl_Preferences->setReadOnly(true);

        verticalLayout_6->addWidget(lbl_Preferences);

        htmlPreferences = new QTextBrowser(page_Preferences);
        htmlPreferences->setObjectName(QString::fromUtf8("htmlPreferences"));
        htmlPreferences->setSource(QUrl(QString::fromUtf8("qrc:/help/preferences_intro.html")));

        verticalLayout_6->addWidget(htmlPreferences);

        ctrl_helpBrowser->addWidget(page_Preferences);
        page_Appearance = new QWidget();
        page_Appearance->setObjectName(QString::fromUtf8("page_Appearance"));
        verticalLayout_5 = new QVBoxLayout(page_Appearance);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        lbl_Appearance = new QLineEdit(page_Appearance);
        lbl_Appearance->setObjectName(QString::fromUtf8("lbl_Appearance"));
        lbl_Appearance->setReadOnly(true);

        verticalLayout_5->addWidget(lbl_Appearance);

        html_Appearance = new QTextBrowser(page_Appearance);
        html_Appearance->setObjectName(QString::fromUtf8("html_Appearance"));
        html_Appearance->setSource(QUrl(QString::fromUtf8("qrc:/help/preferences_appearance.html")));

        verticalLayout_5->addWidget(html_Appearance);

        ctrl_helpBrowser->addWidget(page_Appearance);
        page_Channel = new QWidget();
        page_Channel->setObjectName(QString::fromUtf8("page_Channel"));
        verticalLayout_4 = new QVBoxLayout(page_Channel);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        lineEdit = new QLineEdit(page_Channel);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));

        verticalLayout_4->addWidget(lineEdit);

        html_Channel = new QTextBrowser(page_Channel);
        html_Channel->setObjectName(QString::fromUtf8("html_Channel"));
        html_Channel->setSource(QUrl(QString::fromUtf8("qrc:/help/preferences_channel.html")));

        verticalLayout_4->addWidget(html_Channel);

        ctrl_helpBrowser->addWidget(page_Channel);
        page_General = new QWidget();
        page_General->setObjectName(QString::fromUtf8("page_General"));
        verticalLayout_3 = new QVBoxLayout(page_General);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        lineEdit_2 = new QLineEdit(page_General);
        lineEdit_2->setObjectName(QString::fromUtf8("lineEdit_2"));

        verticalLayout_3->addWidget(lineEdit_2);

        html_General = new QTextBrowser(page_General);
        html_General->setObjectName(QString::fromUtf8("html_General"));
        html_General->setFrameShape(QFrame::NoFrame);
        html_General->setFrameShadow(QFrame::Plain);
        html_General->setLineWidth(2);
        html_General->setSource(QUrl(QString::fromUtf8("qrc:/help/preferences_general.html")));

        verticalLayout_3->addWidget(html_General);

        ctrl_helpBrowser->addWidget(page_General);

        gridLayout->addWidget(ctrl_helpBrowser, 0, 1, 1, 1);


        retranslateUi(gui_Help);

        ctrl_helpBrowser->setCurrentIndex(9);


        QMetaObject::connectSlotsByName(gui_Help);
    } // setupUi

    void retranslateUi(QDialog *gui_Help)
    {
        gui_Help->setWindowTitle(QApplication::translate("gui_Help", "Phoebetria Help", 0, QApplication::UnicodeUTF8));
        ctrl_close->setText(QApplication::translate("gui_Help", "Close", 0, QApplication::UnicodeUTF8));
        QTreeWidgetItem *___qtreewidgetitem = ctrl_helpList->headerItem();
        ___qtreewidgetitem->setText(0, QApplication::translate("gui_Help", "Help", 0, QApplication::UnicodeUTF8));

        const bool __sortingEnabled = ctrl_helpList->isSortingEnabled();
        ctrl_helpList->setSortingEnabled(false);
        QTreeWidgetItem *___qtreewidgetitem1 = ctrl_helpList->topLevelItem(0);
        ___qtreewidgetitem1->setText(1, QApplication::translate("gui_Help", "0", 0, QApplication::UnicodeUTF8));
        ___qtreewidgetitem1->setText(0, QApplication::translate("gui_Help", "General", 0, QApplication::UnicodeUTF8));
        QTreeWidgetItem *___qtreewidgetitem2 = ___qtreewidgetitem1->child(0);
        ___qtreewidgetitem2->setText(1, QApplication::translate("gui_Help", "1", 0, QApplication::UnicodeUTF8));
        ___qtreewidgetitem2->setText(0, QApplication::translate("gui_Help", "About", 0, QApplication::UnicodeUTF8));
        QTreeWidgetItem *___qtreewidgetitem3 = ___qtreewidgetitem1->child(1);
        ___qtreewidgetitem3->setText(1, QApplication::translate("gui_Help", "2", 0, QApplication::UnicodeUTF8));
        ___qtreewidgetitem3->setText(0, QApplication::translate("gui_Help", "Diagnostic", 0, QApplication::UnicodeUTF8));
        QTreeWidgetItem *___qtreewidgetitem4 = ___qtreewidgetitem1->child(2);
        ___qtreewidgetitem4->setText(1, QApplication::translate("gui_Help", "3", 0, QApplication::UnicodeUTF8));
        ___qtreewidgetitem4->setText(0, QApplication::translate("gui_Help", "Main", 0, QApplication::UnicodeUTF8));
        QTreeWidgetItem *___qtreewidgetitem5 = ___qtreewidgetitem1->child(3);
        ___qtreewidgetitem5->setText(1, QApplication::translate("gui_Help", "4", 0, QApplication::UnicodeUTF8));
        ___qtreewidgetitem5->setText(0, QApplication::translate("gui_Help", "Profile", 0, QApplication::UnicodeUTF8));
        QTreeWidgetItem *___qtreewidgetitem6 = ___qtreewidgetitem1->child(4);
        ___qtreewidgetitem6->setText(1, QApplication::translate("gui_Help", "5", 0, QApplication::UnicodeUTF8));
        ___qtreewidgetitem6->setText(0, QApplication::translate("gui_Help", "Software Auto", 0, QApplication::UnicodeUTF8));
        QTreeWidgetItem *___qtreewidgetitem7 = ctrl_helpList->topLevelItem(1);
        ___qtreewidgetitem7->setText(1, QApplication::translate("gui_Help", "6", 0, QApplication::UnicodeUTF8));
        ___qtreewidgetitem7->setText(0, QApplication::translate("gui_Help", "Preferences", 0, QApplication::UnicodeUTF8));
        QTreeWidgetItem *___qtreewidgetitem8 = ___qtreewidgetitem7->child(0);
        ___qtreewidgetitem8->setText(1, QApplication::translate("gui_Help", "7", 0, QApplication::UnicodeUTF8));
        ___qtreewidgetitem8->setText(0, QApplication::translate("gui_Help", "Appearance", 0, QApplication::UnicodeUTF8));
        QTreeWidgetItem *___qtreewidgetitem9 = ___qtreewidgetitem7->child(1);
        ___qtreewidgetitem9->setText(1, QApplication::translate("gui_Help", "8", 0, QApplication::UnicodeUTF8));
        ___qtreewidgetitem9->setText(0, QApplication::translate("gui_Help", "Channels", 0, QApplication::UnicodeUTF8));
        QTreeWidgetItem *___qtreewidgetitem10 = ___qtreewidgetitem7->child(2);
        ___qtreewidgetitem10->setText(1, QApplication::translate("gui_Help", "9", 0, QApplication::UnicodeUTF8));
        ___qtreewidgetitem10->setText(0, QApplication::translate("gui_Help", "General", 0, QApplication::UnicodeUTF8));
        ctrl_helpList->setSortingEnabled(__sortingEnabled);

        lbl_Start->setText(QApplication::translate("gui_Help", "Phoebetria Help", 0, QApplication::UnicodeUTF8));
        lbl_About->setText(QApplication::translate("gui_Help", "About Window", 0, QApplication::UnicodeUTF8));
        lbl_Diagnostic->setText(QApplication::translate("gui_Help", "Diagnostic Window", 0, QApplication::UnicodeUTF8));
        lbl_Main->setText(QApplication::translate("gui_Help", "Main Window", 0, QApplication::UnicodeUTF8));
        lbl_Profile->setText(QApplication::translate("gui_Help", "Profile Window", 0, QApplication::UnicodeUTF8));
        lbl_SoftwareAuto->setText(QApplication::translate("gui_Help", "Software Auto Configuration", 0, QApplication::UnicodeUTF8));
        lbl_Preferences->setText(QApplication::translate("gui_Help", "Phoebetria Preferences", 0, QApplication::UnicodeUTF8));
        lbl_Appearance->setText(QApplication::translate("gui_Help", "Appearance Preferences", 0, QApplication::UnicodeUTF8));
        lineEdit->setText(QApplication::translate("gui_Help", "Channel Preferences", 0, QApplication::UnicodeUTF8));
        lineEdit_2->setText(QApplication::translate("gui_Help", "General Preferences", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class gui_Help: public Ui_gui_Help {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GUI_HELP_H
