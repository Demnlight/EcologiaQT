// secondwindow.cpp
#include "Second.hpp"
#include "../../App/api.hpp"

SecondPractice::SecondPractice(QWidget *parent, QWidget *_mainWindow) : QWidget(parent), mainWindow(_mainWindow)
{
    lineEdits.reserve(6);

    auto curVariant = &API::Inst().curVariant;
    auto practica = &curVariant->secondPractice;

    QLabel *header = new QLabel("Определение воздействия автотранспорта на компоненты урбанизированных экосистем городских агломераций.");
    QLabel *splitterText = new QLabel("Знак разделитель - запятая.");
    QLabel *resultHeaderText = new QLabel("Результат расчета округлить до пяти знаков после запятой.");

    QString variantStr = "Вариант: " + QString::number(curVariant->numberVariant);
    QLabel *variant = new QLabel(variantStr);

    QFrame *splitHeaderLine = new QFrame();
    splitHeaderLine->setFrameShape(QFrame::HLine);
    splitHeaderLine->setFrameShadow(QFrame::Sunken);

    QLabel *headTask = new QLabel(curVariant->head.c_str());
    QLabel *whatWantFound = new QLabel(practica->whatWantFound.c_str());

    QLabel *dano = new QLabel("Дано: ");

    QHBoxLayout *firstDano = new QHBoxLayout();

    QLabel *C_CO = new QLabel("C<sub>CO</sub>= " + QString::number(practica->C_CO) + " мкг/m<sup>3</sup>");
    QLabel *C_NO2 = new QLabel("C<sub>NO<sup>2</sup></sub>= " + QString::number(practica->C_NO2) + " мкг/m<sup>3</sup>");
    QLabel *C_PM2_5 = new QLabel("C<sub>PM<sup>2.5</sup></sub>= " + QString::number(practica->C_PM2_5) + " мкг/m<sup>3</sup>");

    firstDano->addWidget(C_CO);
    firstDano->addWidget(C_NO2);
    firstDano->addWidget(C_PM2_5);

    QHBoxLayout *secondDano = new QHBoxLayout();

    QLabel *C_PM10 = new QLabel("C<sub>PM<sup>10</sup></sub>= " + QString::number(practica->C_PM10) + " мкг/m<sup>3</sup>");
    QLabel *C_SO2 = new QLabel("C<sub>SO<sup>2</sup></sub>= " + QString::number(practica->C_SO2) + " мкг/m<sup>3</sup>");
    QLabel *C_O3 = new QLabel("C<sub>O<sup>3</sup></sub>= " + QString::number(practica->C_O3) + " мкг/m<sup>3</sup>");

    secondDano->addWidget(C_PM10);
    secondDano->addWidget(C_SO2);
    secondDano->addWidget(C_O3);

    QFrame *splitBottomLine = new QFrame();
    splitBottomLine->setFrameShape(QFrame::HLine);
    splitBottomLine->setFrameShadow(QFrame::Sunken);

    QHBoxLayout *hbox = new QHBoxLayout();
    {
        auto CreateCombo = [](QVBoxLayout *column, const char *labelStr, std::vector<QLineEdit *> &lineEdits) -> void
        {
            QHBoxLayout *comboLayout = new QHBoxLayout();
            QLabel *label = new QLabel(labelStr);
            QLineEdit *input = new QLineEdit();
            QDoubleValidator *validator = new QDoubleValidator();
            input->setValidator(validator);
            comboLayout->addWidget(label);
            comboLayout->addWidget(input);
            column->addLayout(comboLayout);

            lineEdits.push_back(input);
        };

        QVBoxLayout *firstColumn = new QVBoxLayout();
        {
            CreateCombo(firstColumn, "ИЗА= ", lineEdits);
            CreateCombo(firstColumn, "Эф.Сум= ", lineEdits);
            CreateCombo(firstColumn, "СИ= ", lineEdits);
        }

        QVBoxLayout *thirdColumn = new QVBoxLayout();
        {
            QLabel *bestResult = new QLabel("Лучший результат: ");
            QLabel *attemptsCount = new QLabel("Количество попыток: ");

            thirdColumn->addWidget(bestResult);
            thirdColumn->addWidget(attemptsCount);

            this->labels.push_back(bestResult);
            this->labels.push_back(attemptsCount);
        }

        QVBoxLayout *fourColumn = new QVBoxLayout();
        {
            QPushButton *checkResultsB = new QPushButton("Проверить ответы");
            checkResultsB->setMinimumSize(100, 50);
            checkResultsB->setMaximumSize(200, 100);
            fourColumn->addWidget(checkResultsB);

            connect(checkResultsB, &QPushButton::clicked, this, &SecondPractice::checkResults);
        }

        hbox->addLayout(firstColumn);
        hbox->addLayout(thirdColumn);
        hbox->addLayout(fourColumn);
    }

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
    mainLayout->addWidget(splitBottomLine);
    mainLayout->addLayout(hbox);

    // Установка компоновки для виджета
    setLayout(mainLayout);

    this->adjustSize();
    this->setFixedSize(this->size());

    this->setWindowFlags(this->windowFlags() | Qt::MSWindowsFixedSizeDialogHint);
}

SecondPractice::~SecondPractice()
{
}

void SecondPractice::closeEvent(QCloseEvent *event)
{
    this->hide();
    mainWindow->show();
    event->ignore();
}


void SecondPractice::checkResults()
{
    API::answerForSecondPractice UserAnswer;
    UserAnswer.IZA = this->lineEdits[0]->text().toDouble();
    UserAnswer.ES = this->lineEdits[1]->text().toDouble();
    UserAnswer.CU = this->lineEdits[2]->text().toDouble();

    API::Inst().compareAnswerForSecondPractice(UserAnswer);

    auto infoFirst = &API::Inst().info_secondPractice;
    this->labels[0]->setText("Лучший результат: " + QString::number(infoFirst->bestResult) + "%");
    this->labels[1]->setText("Количество попыток: " + QString::number(infoFirst->numberOfRemainingAttempts));
}
