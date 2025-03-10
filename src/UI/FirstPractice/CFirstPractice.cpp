// secondwindow.cpp
#include "CFirstPractice.hpp"

#include <QBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include "../../App/api.hpp"

FirstPractice::FirstPractice(QWidget *parent, QWidget *_mainWindow) : QWidget(parent), mainWindow(_mainWindow) {
    
    auto curVariant = &API::Inst().curVariant;
    auto firstPrac = &curVariant->firstPractice;

    QLabel* header = new QLabel("Определение воздействия автотранспорта на компоненты урбанизированных экосистем городских агломераций.");
    QLabel* splitterText = new QLabel("Знак разделитель - запятая.");
    QLabel* resultHeaderText = new QLabel("Результат расчета округлить до четырех знаков после запятой в меньшую сторону.");
    
    QString variantStr = "Вариант: " + QString::number(curVariant->numberVariant);
    QLabel* variant = new QLabel(variantStr);

    // Создаем горизонтальную линию
    QFrame *splitHeaderLine = new QFrame();
    splitHeaderLine->setFrameShape(QFrame::HLine); // Устанавливаем форму линии
    splitHeaderLine->setFrameShadow(QFrame::Sunken); // Устанавливаем тень

    QLabel* headTask = new QLabel (curVariant->head.c_str());
    QLabel* whatWantFound= new QLabel (firstPrac->whatWantFound.c_str());

    QLabel* dano = new QLabel ("Дано: ");

    QHBoxLayout* firstDano = new QHBoxLayout();
    
    QLabel* M_CO = new QLabel ("M<sub>CO</sub>= " + QString::number(firstPrac->M_p_CO) + "г/км");
    QLabel* M_NO2 = new QLabel ("M<sub>NO<sup>2</sup></sub>= " + QString::number(firstPrac->M_p_NO2) + "г/км");
    QLabel* M_PM2_5 = new QLabel ("M<sub>PM<sup>2.5</sup></sub>= " + QString::number(firstPrac->M_p_PM2_5) + "г/км");

    firstDano->addWidget(M_CO);
    firstDano->addWidget(M_NO2);
    firstDano->addWidget(M_PM2_5);

    QHBoxLayout* secondDano = new QHBoxLayout();
    
    QLabel* M_PM10 = new QLabel ("M<sub>PM<sup>10</sup></sub>= " + QString::number(firstPrac->M_p_PM10) + "г/км");
    QLabel* M_SO2 = new QLabel ("M<sub>SO<sup>2</sup></sub>= " + QString::number(firstPrac->M_p_SO2) + "г/км");
    QLabel* M_O3 = new QLabel ("M<sub>O<sup>3</sup></sub>= " + QString::number(firstPrac->M_p_O3) + "г/км");

    secondDano->addWidget(M_PM10);
    secondDano->addWidget(M_SO2);
    secondDano->addWidget(M_O3);

    auto r = API::Inst().get_r(API::typePollutant::PM2_5, firstPrac->V);
    auto V = API::Inst().get_r(API::typePollutant::NO2, firstPrac->V);
    QString koefStr = QString ("Коэффициент учитывающий изменения количества выбрасываемых вредных веществ r<sub>v</sub>= " 
            + QString::number(r)
            + ".\nДля выбросов NO<sup>2</sup>r<sup>v</sup> = "
            + QString::number(V)
            + " (Приложение Б).");
    QLabel* koef = new QLabel(koefStr);
    QLabel* distance = new QLabel("Длина участка: " + QString::number(firstPrac->L));
    QLabel* averageSpeed = new QLabel("Средняя скорость автомобилей: " + QString::number(firstPrac->V));
    QLabel* autoCount = new QLabel("Количество автомобилей: " + QString::number(firstPrac->G));

    QFrame *splitBottomLine = new QFrame();
    splitBottomLine->setFrameShape(QFrame::HLine); // Устанавливаем форму линии
    splitBottomLine->setFrameShadow(QFrame::Sunken); // Устанавливаем тень


    /*QHBoxLayout* firstRow = new QHBoxLayout();
    
    QLabel* buttomM_CO = new QLabel ("M<sub>CO</sub>= ");
    QLabel* buttomM_PM10 = new QLabel ("M<sub>PM<sup>10</sup></sub>= " );
    QLabel* bestResult = new QLabel ("Лучший результат: ");
    QLabel* buttomButtonUpp = new QLabel (" ");

    firstRow->addWidget(buttomM_CO);
    firstRow->addWidget(buttomM_PM10);
    firstRow->addWidget(bestResult);
    firstRow->addWidget(buttomButtonUpp);

    QHBoxLayout* secondRow = new QHBoxLayout();
    
    QLabel* buttomM_NO2 = new QLabel ("M<sub>NO<sup>2</sup></sub>= " );
    QLabel* buttomM_SO2 = new QLabel ("M<sub>SO<sup>2</sup></sub>= ");
    QLabel* numberOfAttempts = new QLabel ("Количество попыток: ");
    QLabel* buttomButtonMiddle = new QLabel (" ");

    secondRow->addWidget(buttomM_NO2);
    secondRow->addWidget(buttomM_SO2);
    secondRow->addWidget(numberOfAttempts);
    secondRow->addWidget(buttomButtonMiddle);


    QHBoxLayout* thirdRow = new QHBoxLayout();
    
    QLabel* buttomM_PM2_5 = new QLabel ("M<sub>PM<sup>2.5</sup></sub>= " );
    QLabel* buttomM_O3 = new QLabel ("M<sub>O<sup>3</sup></sub>= ");
    QLabel* nothing = new QLabel (" ");
    QLabel* buttomButtonButton = new QLabel (" ");

    thirdRow->addWidget(buttomM_PM2_5);
    thirdRow->addWidget(buttomM_O3);
    thirdRow->addWidget(numberOfAttempts);
    thirdRow->addWidget(buttomButtonButton);*/

    QHBoxLayout* hbox = new QHBoxLayout();

    QVBoxLayout* firstColumn = new QVBoxLayout();

    QHBoxLayout* M_CO2_combo = new QHBoxLayout();

    QLabel* buttomM_CO = new QLabel ("M<sub>CO</sub>= ");
    QLineEdit *inputM_CO2 = new QLineEdit();
    M_CO2_combo->addWidget(buttomM_CO);
    M_CO2_combo->addWidget(inputM_CO2);
    firstColumn->addLayout(M_CO2_combo);

    QHBoxLayout* M_NO2_combo = new QHBoxLayout();
    QLabel* buttomM_NO2 = new QLabel ("M<sub>NO<sup>2</sup></sub>= " );
    QLineEdit *inputM_NO2 = new QLineEdit();
    M_NO2_combo->addWidget(buttomM_NO2);
    M_NO2_combo->addWidget(inputM_NO2);
    firstColumn->addLayout(M_NO2_combo);

    QHBoxLayout* M_PM2_5_combo = new QHBoxLayout();
    QLabel* buttomM_PM2_5 = new QLabel ("M<sub>PM<sup>2.5</sup></sub>= " );
    QLineEdit *inputM_PM2_5 = new QLineEdit();
    M_PM2_5_combo->addWidget(buttomM_PM2_5);
    M_PM2_5_combo->addWidget(inputM_PM2_5);
    firstColumn->addLayout(M_PM2_5_combo);

    hbox->addLayout(firstColumn);
    

    // Создание компоновки
    QVBoxLayout *mainLayout = new QVBoxLayout();
    mainLayout->addWidget(header);
    mainLayout->addWidget(splitterText);
    mainLayout->addWidget(resultHeaderText);
    mainLayout->addWidget(splitHeaderLine);
    mainLayout->addWidget(variant);
    mainLayout->addWidget(headTask);
    mainLayout->addWidget(whatWantFound);
    mainLayout->addWidget(dano);
    mainLayout->addLayout(firstDano);
    mainLayout->addLayout(secondDano);
    mainLayout->addWidget(koef);
    mainLayout->addWidget(distance);
    mainLayout->addWidget(averageSpeed);
    mainLayout->addWidget(autoCount);
    mainLayout->addWidget(splitBottomLine);
    mainLayout->addLayout(hbox);
    

    // Установка компоновки для виджета
    setLayout(mainLayout);
}

FirstPractice::~FirstPractice() {
}

void FirstPractice::closeEvent(QCloseEvent *event) {
    this->hide();
    mainWindow->show();
    event->ignore();
}
