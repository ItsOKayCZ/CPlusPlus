/********************************************************************************
** Form generated from reading UI file 'settings.ui'
**
** Created by: Qt User Interface Compiler version 5.13.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETTINGS_H
#define UI_SETTINGS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Settings
{
public:
    QDialogButtonBox *buttons;
    QWidget *formLayoutWidget;
    QFormLayout *formLayout;
    QLabel *hostnameLabel;
    QLineEdit *hostnameInput;
    QLabel *cookieLabel;
    QLineEdit *cookieInput;
    QLabel *label;

    void setupUi(QDialog *Settings)
    {
        if (Settings->objectName().isEmpty())
            Settings->setObjectName(QString::fromUtf8("Settings"));
        Settings->setEnabled(true);
        Settings->resize(370, 140);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(Settings->sizePolicy().hasHeightForWidth());
        Settings->setSizePolicy(sizePolicy);
        Settings->setMinimumSize(QSize(370, 140));
        Settings->setMaximumSize(QSize(370, 140));
        Settings->setCursor(QCursor(Qt::ArrowCursor));
        buttons = new QDialogButtonBox(Settings);
        buttons->setObjectName(QString::fromUtf8("buttons"));
        buttons->setGeometry(QRect(190, 100, 171, 32));
        buttons->setOrientation(Qt::Horizontal);
        buttons->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        formLayoutWidget = new QWidget(Settings);
        formLayoutWidget->setObjectName(QString::fromUtf8("formLayoutWidget"));
        formLayoutWidget->setGeometry(QRect(10, 40, 351, 52));
        formLayout = new QFormLayout(formLayoutWidget);
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        formLayout->setContentsMargins(0, 0, 0, 0);
        hostnameLabel = new QLabel(formLayoutWidget);
        hostnameLabel->setObjectName(QString::fromUtf8("hostnameLabel"));

        formLayout->setWidget(0, QFormLayout::LabelRole, hostnameLabel);

        hostnameInput = new QLineEdit(formLayoutWidget);
        hostnameInput->setObjectName(QString::fromUtf8("hostnameInput"));

        formLayout->setWidget(0, QFormLayout::FieldRole, hostnameInput);

        cookieLabel = new QLabel(formLayoutWidget);
        cookieLabel->setObjectName(QString::fromUtf8("cookieLabel"));

        formLayout->setWidget(1, QFormLayout::LabelRole, cookieLabel);

        cookieInput = new QLineEdit(formLayoutWidget);
        cookieInput->setObjectName(QString::fromUtf8("cookieInput"));

        formLayout->setWidget(1, QFormLayout::FieldRole, cookieInput);

        label = new QLabel(Settings);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(10, 10, 361, 21));
        label->setTextFormat(Qt::AutoText);
        label->setWordWrap(true);

        retranslateUi(Settings);
        QObject::connect(buttons, SIGNAL(accepted()), Settings, SLOT(accept()));
        QObject::connect(buttons, SIGNAL(rejected()), Settings, SLOT(reject()));

        QMetaObject::connectSlotsByName(Settings);
    } // setupUi

    void retranslateUi(QDialog *Settings)
    {
        Settings->setWindowTitle(QCoreApplication::translate("Settings", "Enter the server configuration", nullptr));
        hostnameLabel->setText(QCoreApplication::translate("Settings", "Hostname:", nullptr));
        cookieLabel->setText(QCoreApplication::translate("Settings", "Password:", nullptr));
        label->setText(QCoreApplication::translate("Settings", "You can set the hostname and the cookie for the server", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Settings: public Ui_Settings {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETTINGS_H
