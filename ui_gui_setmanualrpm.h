/********************************************************************************
** Form generated from reading UI file 'gui_setmanualrpm.ui'
**
** Created by: Qt User Interface Compiler version 4.8.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GUI_SETMANUALRPM_H
#define UI_GUI_SETMANUALRPM_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QFormLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QSpinBox>

QT_BEGIN_NAMESPACE

class Ui_gui_setManualRpm
{
public:
    QFormLayout *formLayout;
    QLabel *ctrl_title;
    QLabel *label;
    QSpinBox *ctrl_manualRpm;
    QCheckBox *ctrl_useMaxRpm;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *gui_setManualRpm)
    {
        if (gui_setManualRpm->objectName().isEmpty())
            gui_setManualRpm->setObjectName(QString::fromUtf8("gui_setManualRpm"));
        gui_setManualRpm->resize(317, 136);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Images/icons/32x32/phoebetria.png"), QSize(), QIcon::Normal, QIcon::Off);
        gui_setManualRpm->setWindowIcon(icon);
        gui_setManualRpm->setSizeGripEnabled(true);
        formLayout = new QFormLayout(gui_setManualRpm);
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        ctrl_title = new QLabel(gui_setManualRpm);
        ctrl_title->setObjectName(QString::fromUtf8("ctrl_title"));

        formLayout->setWidget(0, QFormLayout::SpanningRole, ctrl_title);

        label = new QLabel(gui_setManualRpm);
        label->setObjectName(QString::fromUtf8("label"));

        formLayout->setWidget(1, QFormLayout::LabelRole, label);

        ctrl_manualRpm = new QSpinBox(gui_setManualRpm);
        ctrl_manualRpm->setObjectName(QString::fromUtf8("ctrl_manualRpm"));
        QSizePolicy sizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(ctrl_manualRpm->sizePolicy().hasHeightForWidth());
        ctrl_manualRpm->setSizePolicy(sizePolicy);
        ctrl_manualRpm->setMinimumSize(QSize(100, 0));
        ctrl_manualRpm->setMaximum(65535);
        ctrl_manualRpm->setSingleStep(100);

        formLayout->setWidget(1, QFormLayout::FieldRole, ctrl_manualRpm);

        ctrl_useMaxRpm = new QCheckBox(gui_setManualRpm);
        ctrl_useMaxRpm->setObjectName(QString::fromUtf8("ctrl_useMaxRpm"));

        formLayout->setWidget(2, QFormLayout::SpanningRole, ctrl_useMaxRpm);

        buttonBox = new QDialogButtonBox(gui_setManualRpm);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        formLayout->setWidget(3, QFormLayout::SpanningRole, buttonBox);


        retranslateUi(gui_setManualRpm);
        QObject::connect(buttonBox, SIGNAL(accepted()), gui_setManualRpm, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), gui_setManualRpm, SLOT(reject()));

        QMetaObject::connectSlotsByName(gui_setManualRpm);
    } // setupUi

    void retranslateUi(QDialog *gui_setManualRpm)
    {
        gui_setManualRpm->setWindowTitle(QApplication::translate("gui_setManualRpm", "Set Manual RPM", 0, QApplication::UnicodeUTF8));
        ctrl_title->setText(QApplication::translate("gui_setManualRpm", "TextLabel", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("gui_setManualRpm", "Manual RPM", 0, QApplication::UnicodeUTF8));
        ctrl_useMaxRpm->setText(QApplication::translate("gui_setManualRpm", "Use maximum possible", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class gui_setManualRpm: public Ui_gui_setManualRpm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GUI_SETMANUALRPM_H
