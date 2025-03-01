// secondwindow.cpp
#include "CMetodichka.hpp"
#include <QBoxLayout>
#include <QDir>
#include <QPainter>

#include <QPdfDocument>
#include <QGraphicsScene>

Metodichka::Metodichka(QWidget *parent, QWidget* _mainWindow) : QWidget(parent), mainWindow(_mainWindow)
{

}

Metodichka::~Metodichka()
{
}

void Metodichka::closeEvent(QCloseEvent *event)
{
    this->hide();
    mainWindow->show();
    event->ignore();
}
