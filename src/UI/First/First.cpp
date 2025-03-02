// secondwindow.cpp
#include "First.hpp"
#include "../../App/api.hpp"

FirstPractice::FirstPractice(QWidget *parent, QWidget *_mainWindow) : QWidget(parent), mainWindow(_mainWindow)
{
    lineEdits.reserve(6);

    auto curVariant = &API::Inst().curVariant;
    auto firstPrac = &curVariant->firstPractice;

    QLabel *header = new QLabel("Определение воздействия автотранспорта на компоненты урбанизированных экосистем городских агломераций.");
    QLabel *splitterText = new QLabel("Знак разделитель - запятая.");
    QLabel *resultHeaderText = new QLabel("Результат расчета округлить до пяти знаков после запятой.");

    QString variantStr = "Вариант: " + QString::number(curVariant->numberVariant);
    QLabel *variant = new QLabel(variantStr);

    // Создаем горизонтальную линию
    QFrame *splitHeaderLine = new QFrame();
    splitHeaderLine->setFrameShape(QFrame::HLine);   // Устанавливаем форму линии
    splitHeaderLine->setFrameShadow(QFrame::Sunken); // Устанавливаем тень

    QLabel *headTask = new QLabel(curVariant->head.c_str());
    QLabel *whatWantFound = new QLabel(firstPrac->whatWantFound.c_str());

    QLabel *dano = new QLabel("Дано: ");

    QHBoxLayout *firstDano = new QHBoxLayout();

    QLabel *M_CO = new QLabel("M<sub>CO</sub>= " + QString::number(firstPrac->M_p_CO) + "г/км");
    QLabel *M_NO2 = new QLabel("M<sub>NO<sup>2</sup></sub>= " + QString::number(firstPrac->M_p_NO2) + "г/км");
    QLabel *M_PM2_5 = new QLabel("M<sub>PM<sup>2.5</sup></sub>= " + QString::number(firstPrac->M_p_PM2_5) + "г/км");

    firstDano->addWidget(M_CO);
    firstDano->addWidget(M_NO2);
    firstDano->addWidget(M_PM2_5);

    QHBoxLayout *secondDano = new QHBoxLayout();

    QLabel *M_PM10 = new QLabel("M<sub>PM<sup>10</sup></sub>= " + QString::number(firstPrac->M_p_PM10) + "г/км");
    QLabel *M_SO2 = new QLabel("M<sub>SO<sup>2</sup></sub>= " + QString::number(firstPrac->M_p_SO2) + "г/км");
    QLabel *M_O3 = new QLabel("M<sub>O<sup>3</sup></sub>= " + QString::number(firstPrac->M_p_O3) + "г/км");

    secondDano->addWidget(M_PM10);
    secondDano->addWidget(M_SO2);
    secondDano->addWidget(M_O3);

    auto r = API::Inst().get_r(API::typePollutant::PM2_5, firstPrac->V);
    auto V = API::Inst().get_r(API::typePollutant::NO2, firstPrac->V);
    QString koefStr = QString("Коэффициент учитывающий изменения количества выбрасываемых вредных веществ r<sub>v</sub>= " + QString::number(r) + ".\nДля выбросов NO<sup>2</sup>r<sup>v</sup> = " + QString::number(V) + " (Приложение Б).");
    QLabel *koef = new QLabel(koefStr);
    QLabel *distance = new QLabel("Длина участка: " + QString::number(firstPrac->L) + "км");
    QLabel *averageSpeed = new QLabel("Средняя скорость автомобилей: " + QString::number(firstPrac->V) + "км/ч");
    QLabel *autoCount = new QLabel("Количество автомобилей: " + QString::number(firstPrac->G));

    QFrame *splitBottomLine = new QFrame();
    splitBottomLine->setFrameShape(QFrame::HLine);   // Устанавливаем форму линии
    splitBottomLine->setFrameShadow(QFrame::Sunken); // Устанавливаем тень

    QHBoxLayout *hbox = new QHBoxLayout();
    {
        auto CreateCombo = [](QVBoxLayout *column, const char *labelStr, std::vector<QLineEdit *> &lineEdits) -> void
        {
            QHBoxLayout *comboLayout = new QHBoxLayout();
            QLabel *label = new QLabel(labelStr);
            QLineEdit *input = new QLineEdit();
            QDoubleValidator *validator = new QDoubleValidator();
            input->setValidator(validator);

            QLabel *subLabel = new QLabel("Г/С");
            comboLayout->addWidget(label);
            comboLayout->addWidget(input);
            comboLayout->addWidget(subLabel);
            column->addLayout(comboLayout);

            lineEdits.push_back(input);
        };

        QVBoxLayout *firstColumn = new QVBoxLayout();
        {
            CreateCombo(firstColumn, "M<sub>CO</sub>= ", lineEdits);
            CreateCombo(firstColumn, "M<sub>NO<sup>2</sup></sub>= ", lineEdits);
            CreateCombo(firstColumn, "M<sub>PM<sup>2.5</sup></sub>= ", lineEdits);
        }

        QVBoxLayout *secondColumn = new QVBoxLayout();
        {
            CreateCombo(secondColumn, "M<sub>PM<sup>10</sup></sub>= ", lineEdits);
            CreateCombo(secondColumn, "M<sub>SO<sup>2</sup></sub>= ", lineEdits);
            CreateCombo(secondColumn, "M<sub>O<sup>3</sup></sub>= ", lineEdits);
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

            connect(checkResultsB, &QPushButton::clicked, this, &FirstPractice::checkResults);
        }

        hbox->addLayout(firstColumn);
        hbox->addLayout(secondColumn);
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
    mainLayout->addWidget(koef);
    mainLayout->addWidget(distance);
    mainLayout->addWidget(averageSpeed);
    mainLayout->addWidget(autoCount);
    mainLayout->addWidget(splitBottomLine);
    mainLayout->addLayout(hbox);

    // Установка компоновки для виджета
    setLayout(mainLayout);

    this->adjustSize();
    this->setFixedSize(this->size());

    this->setWindowFlags(this->windowFlags() | Qt::MSWindowsFixedSizeDialogHint);
}

FirstPractice::~FirstPractice()
{
}

void FirstPractice::closeEvent(QCloseEvent *event)
{
    this->hide();
    mainWindow->show();
    event->ignore();
}


void FirstPractice::checkResults()
{
    API::answerForFirstPractice UserAnswer;
    UserAnswer.M_L_PM2_5 = this->lineEdits[2]->text().toDouble();
    UserAnswer.M_L_PM10 = this->lineEdits[3]->text().toDouble();
    UserAnswer.M_L_NO2 = this->lineEdits[1]->text().toDouble();
    UserAnswer.M_L_O3 = this->lineEdits[5]->text().toDouble();
    UserAnswer.M_L_SO2 = this->lineEdits[4]->text().toDouble();
    UserAnswer.M_L_CO = this->lineEdits[0]->text().toDouble();
    API::Inst().compareAnswerForFirstPractice(UserAnswer);

    auto infoFirst = &API::Inst().info_firstPractice;
    this->labels[0]->setText("Лучший результат: " + QString::number(infoFirst->bestResult) + "%");
    this->labels[1]->setText("Количество попыток: " + QString::number(infoFirst->numberOfRemainingAttempts));
}
