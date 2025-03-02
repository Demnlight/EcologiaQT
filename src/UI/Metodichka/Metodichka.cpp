// secondwindow.cpp
#include "Metodichka.hpp"
#include <QBoxLayout>
#include <QDir>

Metodichka::Metodichka(QWidget *parent, QWidget *_mainWindow) : QWidget(parent), mainWindow(_mainWindow)
{
    this->adjustSize();
    this->setFixedSize(this->size());

    this->setWindowFlags(this->windowFlags() | Qt::MSWindowsFixedSizeDialogHint);
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
