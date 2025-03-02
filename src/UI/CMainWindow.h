#pragma once
#include <memory>

#include <QMainWindow>
#include "First/First.hpp"
#include "Second/Second.hpp"
#include "Metodichka/Metodichka.hpp"

#include "../App/api.hpp"

class CMainWindow : public QWidget
{
    Q_OBJECT

public:
    CMainWindow(QWidget *parent = nullptr);
    ~CMainWindow();

private:
    FirstPractice* firstPractice = nullptr;
    SecondPractice* secondPractice = nullptr;
    Metodichka* metodichka = nullptr;
    
    void openFirstPractice();
    void openSecondPractice();
    void openMetodichka();
};
