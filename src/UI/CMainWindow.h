#ifndef CMAINWINDOW_H
#define CMAINWINDOW_H

#include <memory>

#include <QMainWindow>
#include "FirstPractice/CFirstPractice.hpp"

#include "../App/api.hpp"
#include "Metodichka/CMetodichka.hpp"

class CMainWindow : public QWidget
{
    Q_OBJECT

public:
    CMainWindow(QWidget *parent = nullptr);
    ~CMainWindow();

private:
    FirstPractice* firstPractice = nullptr;
    //FirstPractice* firstPractice = nullptr;
    Metodichka* metodichka = nullptr;
    
    void openFirstPractice();
    void openSecondPractice();
    void openMetodichka();
};

#endif // CMAINWINDOW_H