#ifndef PROMPT_H
#define PROMPT_H

#include <QWidget>

#include <QAbstractButton>

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

    void display();

private slots:
    void on_buttonBox_clicked(QAbstractButton *button);

private:
    Ui::Prompt *ui;
};

#endif // PROMPT_H
