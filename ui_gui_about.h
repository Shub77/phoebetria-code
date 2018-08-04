/********************************************************************************
** Form generated from reading UI file 'gui_about.ui'
**
** Created by: Qt User Interface Compiler version 4.8.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GUI_ABOUT_H
#define UI_GUI_ABOUT_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QFrame>
#include <QtGui/QGraphicsView>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QTabWidget>
#include <QtGui/QTextBrowser>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_gui_About
{
public:
    QVBoxLayout *verticalLayout_2;
    QTabWidget *tabWidget;
    QWidget *tab;
    QVBoxLayout *verticalLayout_6;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout_4;
    QGraphicsView *graphicsView;
    QSpacerItem *verticalSpacer;
    QSpacerItem *horizontalSpacer;
    QVBoxLayout *verticalLayout_3;
    QLabel *label;
    QLabel *ctrl_version;
    QLabel *ctrl_build;
    QLabel *ctrl_qtVersion;
    QSpacerItem *verticalSpacer_2;
    QFrame *line;
    QVBoxLayout *verticalLayout_5;
    QLabel *label_3;
    QLabel *ctrl_build_2;
    QTextBrowser *textBrowser_acknowledgement;
    QLabel *label_5;
    QWidget *tab_2;
    QVBoxLayout *verticalLayout;
    QTextBrowser *textBrowser;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *ctrl_aboutClose;
    QSpacerItem *horizontalSpacer_2;

    void setupUi(QDialog *gui_About)
    {
        if (gui_About->objectName().isEmpty())
            gui_About->setObjectName(QString::fromUtf8("gui_About"));
        gui_About->setWindowModality(Qt::WindowModal);
        gui_About->resize(430, 456);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Images/phoebetria_icon_16.png"), QSize(), QIcon::Normal, QIcon::Off);
        gui_About->setWindowIcon(icon);
        verticalLayout_2 = new QVBoxLayout(gui_About);
        verticalLayout_2->setSpacing(5);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(-1, 12, -1, 12);
        tabWidget = new QTabWidget(gui_About);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        verticalLayout_6 = new QVBoxLayout(tab);
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        graphicsView = new QGraphicsView(tab);
        graphicsView->setObjectName(QString::fromUtf8("graphicsView"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(graphicsView->sizePolicy().hasHeightForWidth());
        graphicsView->setSizePolicy(sizePolicy);
        graphicsView->setMinimumSize(QSize(64, 64));
        graphicsView->setMaximumSize(QSize(64, 64));
        graphicsView->setStyleSheet(QString::fromUtf8("background-image: url(:/Images/icons/64x64/phoebetria.png);"));
        graphicsView->setFrameShape(QFrame::NoFrame);
        graphicsView->setFrameShadow(QFrame::Sunken);
        graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

        verticalLayout_4->addWidget(graphicsView);

        verticalSpacer = new QSpacerItem(20, 13, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_4->addItem(verticalSpacer);


        horizontalLayout->addLayout(verticalLayout_4);

        horizontalSpacer = new QSpacerItem(13, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        label = new QLabel(tab);
        label->setObjectName(QString::fromUtf8("label"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy1);
        label->setMinimumSize(QSize(0, 0));
        QFont font;
        font.setPointSize(14);
        label->setFont(font);
        label->setText(QString::fromUtf8("Phoebetria"));

        verticalLayout_3->addWidget(label);

        ctrl_version = new QLabel(tab);
        ctrl_version->setObjectName(QString::fromUtf8("ctrl_version"));
        sizePolicy1.setHeightForWidth(ctrl_version->sizePolicy().hasHeightForWidth());
        ctrl_version->setSizePolicy(sizePolicy1);
        ctrl_version->setMinimumSize(QSize(0, 0));
        QFont font1;
        font1.setPointSize(9);
        ctrl_version->setFont(font1);
        ctrl_version->setText(QString::fromUtf8("Version 0.0"));

        verticalLayout_3->addWidget(ctrl_version);

        ctrl_build = new QLabel(tab);
        ctrl_build->setObjectName(QString::fromUtf8("ctrl_build"));
        sizePolicy1.setHeightForWidth(ctrl_build->sizePolicy().hasHeightForWidth());
        ctrl_build->setSizePolicy(sizePolicy1);
        ctrl_build->setMinimumSize(QSize(0, 0));
        ctrl_build->setText(QString::fromUtf8("Build:"));

        verticalLayout_3->addWidget(ctrl_build);

        ctrl_qtVersion = new QLabel(tab);
        ctrl_qtVersion->setObjectName(QString::fromUtf8("ctrl_qtVersion"));
        ctrl_qtVersion->setText(QString::fromUtf8("Qt Version:"));

        verticalLayout_3->addWidget(ctrl_qtVersion);


        horizontalLayout->addLayout(verticalLayout_3);


        verticalLayout_6->addLayout(horizontalLayout);

        verticalSpacer_2 = new QSpacerItem(20, 10, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_6->addItem(verticalSpacer_2);

        line = new QFrame(tab);
        line->setObjectName(QString::fromUtf8("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        verticalLayout_6->addWidget(line);

        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setSpacing(5);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        label_3 = new QLabel(tab);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        sizePolicy1.setHeightForWidth(label_3->sizePolicy().hasHeightForWidth());
        label_3->setSizePolicy(sizePolicy1);
        QFont font2;
        font2.setFamily(QString::fromUtf8("MS Shell Dlg 2"));
        font2.setPointSize(9);
        label_3->setFont(font2);
        label_3->setText(QString::fromUtf8("Controller software for the BitFenix Recon fan controller."));
        label_3->setAlignment(Qt::AlignHCenter|Qt::AlignTop);

        verticalLayout_5->addWidget(label_3);

        ctrl_build_2 = new QLabel(tab);
        ctrl_build_2->setObjectName(QString::fromUtf8("ctrl_build_2"));
        ctrl_build_2->setText(QString::fromUtf8("\302\251 Copyright 2012"));
        ctrl_build_2->setAlignment(Qt::AlignCenter);

        verticalLayout_5->addWidget(ctrl_build_2);

        textBrowser_acknowledgement = new QTextBrowser(tab);
        textBrowser_acknowledgement->setObjectName(QString::fromUtf8("textBrowser_acknowledgement"));
        textBrowser_acknowledgement->setReadOnly(true);
        textBrowser_acknowledgement->setHtml(QString::fromUtf8("<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p></body></html>"));
        textBrowser_acknowledgement->setSource(QUrl(QString::fromUtf8("qrc:/html/Acknowledgments")));

        verticalLayout_5->addWidget(textBrowser_acknowledgement);

        label_5 = new QLabel(tab);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::MinimumExpanding);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(label_5->sizePolicy().hasHeightForWidth());
        label_5->setSizePolicy(sizePolicy2);
        label_5->setMinimumSize(QSize(0, 0));
        QPalette palette;
        QBrush brush(QColor(70, 70, 70, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Text, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Text, brush);
        QBrush brush1(QColor(120, 120, 120, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Disabled, QPalette::Text, brush1);
        label_5->setPalette(palette);
        label_5->setScaledContents(false);
        label_5->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_5->setWordWrap(true);

        verticalLayout_5->addWidget(label_5);


        verticalLayout_6->addLayout(verticalLayout_5);

        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QString::fromUtf8("tab_2"));
        verticalLayout = new QVBoxLayout(tab_2);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        textBrowser = new QTextBrowser(tab_2);
        textBrowser->setObjectName(QString::fromUtf8("textBrowser"));
#ifndef QT_NO_ACCESSIBILITY
        textBrowser->setAccessibleName(QString::fromUtf8(""));
#endif // QT_NO_ACCESSIBILITY
#ifndef QT_NO_ACCESSIBILITY
        textBrowser->setAccessibleDescription(QString::fromUtf8(""));
#endif // QT_NO_ACCESSIBILITY
        textBrowser->setHtml(QString::fromUtf8("<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p></body></html>"));
        textBrowser->setSource(QUrl(QString::fromUtf8("qrc:/html/GPL3_Brief")));

        verticalLayout->addWidget(textBrowser);

        tabWidget->addTab(tab_2, QString());

        verticalLayout_2->addWidget(tabWidget);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_3);

        ctrl_aboutClose = new QPushButton(gui_About);
        ctrl_aboutClose->setObjectName(QString::fromUtf8("ctrl_aboutClose"));
        ctrl_aboutClose->setStyleSheet(QString::fromUtf8("QPushButton {\n"
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

        horizontalLayout_2->addWidget(ctrl_aboutClose);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);


        verticalLayout_2->addLayout(horizontalLayout_2);


        retranslateUi(gui_About);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(gui_About);
    } // setupUi

    void retranslateUi(QDialog *gui_About)
    {
        gui_About->setWindowTitle(QApplication::translate("gui_About", "About Phoebetria", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_ACCESSIBILITY
        label->setAccessibleName(QString());
#endif // QT_NO_ACCESSIBILITY
#ifndef QT_NO_ACCESSIBILITY
        label->setAccessibleDescription(QString());
#endif // QT_NO_ACCESSIBILITY
#ifndef QT_NO_ACCESSIBILITY
        ctrl_version->setAccessibleName(QString());
#endif // QT_NO_ACCESSIBILITY
#ifndef QT_NO_ACCESSIBILITY
        ctrl_build->setAccessibleName(QString());
#endif // QT_NO_ACCESSIBILITY
#ifndef QT_NO_ACCESSIBILITY
        ctrl_qtVersion->setAccessibleName(QString());
#endif // QT_NO_ACCESSIBILITY
#ifndef QT_NO_ACCESSIBILITY
        label_3->setAccessibleName(QString());
#endif // QT_NO_ACCESSIBILITY
#ifndef QT_NO_ACCESSIBILITY
        ctrl_build_2->setAccessibleName(QString());
#endif // QT_NO_ACCESSIBILITY
#ifndef QT_NO_ACCESSIBILITY
        ctrl_build_2->setAccessibleDescription(QString());
#endif // QT_NO_ACCESSIBILITY
#ifndef QT_NO_ACCESSIBILITY
        textBrowser_acknowledgement->setAccessibleName(QString());
#endif // QT_NO_ACCESSIBILITY
#ifndef QT_NO_ACCESSIBILITY
        textBrowser_acknowledgement->setAccessibleDescription(QString());
#endif // QT_NO_ACCESSIBILITY
        label_5->setText(QApplication::translate("gui_About", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:8pt;\"><small>This program is </span><small><span style=\" font-size:8pt; font-weight:600;\">not</span></small><small><span style=\" font-size:8pt;\"> official BitFenix\302\256 software. BitFenix\302\256 is in no way associated or affiliated with this program.</small></span></p></body></html>", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("gui_About", "About", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("gui_About", "License", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        ctrl_aboutClose->setToolTip(QApplication::translate("gui_About", "Close", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        ctrl_aboutClose->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class gui_About: public Ui_gui_About {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GUI_ABOUT_H
