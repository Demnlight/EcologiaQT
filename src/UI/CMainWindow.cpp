#include "CMainWindow.h"

#include <QBoxLayout>
#include <QPushButton>


CMainWindow::CMainWindow(QWidget *parent) : QWidget(parent)
{
    firstPractice = new FirstPractice(parent, this);
    metodichka = new Metodichka(parent, this);
    
    QVBoxLayout *layout = new QVBoxLayout;

    // Создаем три кнопки
    QPushButton *button1 = new QPushButton("Методическое пособие");
    QPushButton *button2 = new QPushButton("Практика 1");
    QPushButton *button3 = new QPushButton("Практика 2");

    // Добавляем кнопки в layout
    layout->addWidget(button1);
    layout->addWidget(button2);
    layout->addWidget(button3);

    // Устанавливаем layout в главное окно
    this->setLayout(layout);

    connect(button1, &QPushButton::clicked, this, &CMainWindow::openMetodichka);
    connect(button2, &QPushButton::clicked, this, &CMainWindow::openFirstPractice);
}

CMainWindow::~CMainWindow()
{
}

void CMainWindow::openFirstPractice()
{
    firstPractice->show();
    this->hide();
}

void CMainWindow::openSecondPractice()
{
    firstPractice->show();
    this->hide();
}

void CMainWindow::openMetodichka()
{
    metodichka->show();
    this->hide();
}

