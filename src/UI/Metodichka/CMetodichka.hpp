// secondwindow.h
#ifndef METODICHKA_H
#define METODICHKA_H

#include <QWidget>
#include <QCloseEvent>
#include <QMainWindow>



class Metodichka : public QWidget
{
    Q_OBJECT

public:
    Metodichka(QWidget *parent = nullptr, QWidget* _mainWindow = nullptr);
    ~Metodichka();

private:
    void closeEvent(QCloseEvent *event) override; // Переопределяем closeEvent
    QWidget* mainWindow = nullptr;
};



#endif // METODICHKA_H
