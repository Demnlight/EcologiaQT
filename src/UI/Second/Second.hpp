#pragma once

#include <QWidget>
#include <QCloseEvent>

#include <QBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QDoubleValidator>

#include <vector>

class SecondPractice : public QWidget
{
    Q_OBJECT

public:
    SecondPractice(QWidget *parent = nullptr, QWidget* _mainWindow = nullptr);
    ~SecondPractice();

private:
    void closeEvent(QCloseEvent *event) override; // Переопределяем closeEvent
    void checkResults();
    QWidget* mainWindow = nullptr;

    std::vector<QLineEdit*> lineEdits;
    std::vector<QLabel*> labels;
};
