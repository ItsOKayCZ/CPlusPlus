#ifndef PROMPT_H
#define PROMPT_H

#include <QWidget>

#include <QAbstractButton>
#include <QLineEdit>

#include <QDebug>

namespace Ui {
class Prompt;
}

class Prompt : public QWidget
{
    Q_OBJECT

public:
    explicit Prompt(QWidget *parent = nullptr);
    ~Prompt();

    QString display();

private:
    Ui::Prompt *ui;
};

#endif // PROMPT_H
