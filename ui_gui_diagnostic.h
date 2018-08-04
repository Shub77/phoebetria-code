/********************************************************************************
** Form generated from reading UI file 'gui_diagnostic.ui'
**
** Created by: Qt User Interface Compiler version 4.8.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GUI_DIAGNOSTIC_H
#define UI_GUI_DIAGNOSTIC_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QTextBrowser>
#include <QtGui/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_gui_Diagnostic
{
public:
    QVBoxLayout *verticalLayout;
    QTextBrowser *ctrl_diagnosticReport;
    QGridLayout *gridLayout;
    QPushButton *ctrl_saveAsPDF;
    QPushButton *ctrl_close;
    QSpacerItem *horizontalSpacer;

    void setupUi(QDialog *gui_Diagnostic)
    {
        if (gui_Diagnostic->objectName().isEmpty())
            gui_Diagnostic->setObjectName(QString::fromUtf8("gui_Diagnostic"));
        gui_Diagnostic->resize(640, 480);
        gui_Diagnostic->setMinimumSize(QSize(640, 480));
        verticalLayout = new QVBoxLayout(gui_Diagnostic);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        ctrl_diagnosticReport = new QTextBrowser(gui_Diagnostic);
        ctrl_diagnosticReport->setObjectName(QString::fromUtf8("ctrl_diagnosticReport"));

        verticalLayout->addWidget(ctrl_diagnosticReport);

        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        ctrl_saveAsPDF = new QPushButton(gui_Diagnostic);
        ctrl_saveAsPDF->setObjectName(QString::fromUtf8("ctrl_saveAsPDF"));

        gridLayout->addWidget(ctrl_saveAsPDF, 0, 1, 1, 1);

        ctrl_close = new QPushButton(gui_Diagnostic);
        ctrl_close->setObjectName(QString::fromUtf8("ctrl_close"));

        gridLayout->addWidget(ctrl_close, 0, 2, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 0, 0, 1, 1);


        verticalLayout->addLayout(gridLayout);


        retranslateUi(gui_Diagnostic);

        QMetaObject::connectSlotsByName(gui_Diagnostic);
    } // setupUi

    void retranslateUi(QDialog *gui_Diagnostic)
    {
        gui_Diagnostic->setWindowTitle(QApplication::translate("gui_Diagnostic", "Dialog", 0, QApplication::UnicodeUTF8));
        ctrl_saveAsPDF->setText(QApplication::translate("gui_Diagnostic", "Save PDF", 0, QApplication::UnicodeUTF8));
        ctrl_close->setText(QApplication::translate("gui_Diagnostic", "Close", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class gui_Diagnostic: public Ui_gui_Diagnostic {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GUI_DIAGNOSTIC_H
