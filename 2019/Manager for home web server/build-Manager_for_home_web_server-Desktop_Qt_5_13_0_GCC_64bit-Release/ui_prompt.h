/********************************************************************************
** Form generated from reading UI file 'prompt.ui'
**
** Created by: Qt User Interface Compiler version 5.13.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PROMPT_H
#define UI_PROMPT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Prompt
{
public:
    QDialogButtonBox *buttons;
    QLineEdit *inputField;

    void setupUi(QWidget *Prompt)
    {
        if (Prompt->objectName().isEmpty())
            Prompt->setObjectName(QString::fromUtf8("Prompt"));
        Prompt->resize(400, 73);
        buttons = new QDialogButtonBox(Prompt);
        buttons->setObjectName(QString::fromUtf8("buttons"));
        buttons->setGeometry(QRect(220, 40, 166, 24));
        buttons->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        inputField = new QLineEdit(Prompt);
        inputField->setObjectName(QString::fromUtf8("inputField"));
        inputField->setGeometry(QRect(10, 10, 381, 22));

        retranslateUi(Prompt);

        QMetaObject::connectSlotsByName(Prompt);
    } // setupUi

    void retranslateUi(QWidget *Prompt)
    {
        Prompt->setWindowTitle(QCoreApplication::translate("Prompt", "Enter folder name", nullptr));
        inputField->setPlaceholderText(QCoreApplication::translate("Prompt", "Enter folder name", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Prompt: public Ui_Prompt {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PROMPT_H
