#pragma once

#include <QWidget>
#include <QCloseEvent>

#include <QBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QDoubleValidator>

#include <vector>

class FirstPractice : public QWidget
{
    Q_OBJECT

public:
    FirstPractice(QWidget *parent = nullptr, QWidget* _mainWindow = nullptr);
    ~FirstPractice();

private:
    void closeEvent(QCloseEvent *event) override; // Переопределяем closeEvent
    void checkResults();
    QWidget* mainWindow = nullptr;

    std::vector<QLineEdit*> lineEdits;
    std::vector<QLabel*> labels;
    
};
