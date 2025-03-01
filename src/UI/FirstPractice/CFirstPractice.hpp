// secondwindow.h
#ifndef SECONDWINDOW_H
#define SECONDWINDOW_H

#include <QWidget>
#include <QCloseEvent>

class FirstPractice : public QWidget
{
    Q_OBJECT

public:
    FirstPractice(QWidget *parent = nullptr, QWidget* _mainWindow = nullptr);
    ~FirstPractice();

private:
    void closeEvent(QCloseEvent *event) override; // Переопределяем closeEvent
    QWidget* mainWindow = nullptr;
};

#endif // SECONDWINDOW_H
