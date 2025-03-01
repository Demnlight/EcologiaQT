#pragma once
#include <algorithm>
#include <string>
#include <unordered_map>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QFile>
#include <QDebug>
#include <QRandomGenerator>

class API {

    API() {}

   public:

    static API& Inst()
    {
        static API inst;
        return inst;
    }

    std::string fileName = "Variants.json";
    std::string filePath = "Variant/";
    int accuracy = 4;

    struct practice_first {
        std::string whatWantFound{};  // Что нужно найти (пояснение для человека)
        double M_p_PM2_5{};           // Пробеговый выброс загрязняющего вещества (г/км)
        double M_p_PM10{};            // Пробеговый выброс загрязняющего вещества (г/км)
        double M_p_NO2{};             // Пробеговый выброс загрязняющего вещества (г/км)
        double M_p_O3{};              // Пробеговый выброс загрязняющего вещества (г/км)
        double M_p_SO2{};             // Пробеговый выброс загрязняющего вещества (г/км)
        double M_p_CO{};              // Пробеговый выброс загрязняющего вещества (г/км)
        double L{};                   // Длина участка (км)
        double V{};                   // Средняя скорость движения (км/ч)
        double G{};                   // Число проезжающего автотранспорта (за 20мин)
    };

    struct practice_second {
        std::string whatWantFound{};  // Что нужно найти (пояснение для человека)
        double C_PM2_5{};             // Фактическая концентрация вредного вещества в воздухе (мкГ/м^3)
        double C_PM10{};              // Фактическая концентрация вредного вещества в воздухе (мкГ/м^3)
        double C_NO2{};               // Фактическая концентрация вредного вещества в воздухе (мкГ/м^3)
        double C_O3{};                // Фактическая концентрация вредного вещества в воздухе (мкГ/м^3)
        double C_SO2{};               // Фактическая концентрация вредного вещества в воздухе (мкГ/м^3)
        double C_CO{};                // Фактическая концентрация вредного вещества в воздухе (мкГ/м^3)
    };

    struct Variant {
        int numberVariant{};               // Номер варианта для отображения на экране
        std::string head{};                // Текст-пояснение для человека
        practice_first firstPractice{};    // Информация для первой практики
        practice_second secondPractice{};  // Информация для второй практики
    };

    struct answerForFirstPractice {
        std::string M_L_PM2_5;  // Выброс загрязняющего вещества движущимся автотранспортным потоком (г/с)
        std::string M_L_PM10;   // Выброс загрязняющего вещества движущимся автотранспортным потоком (г/с)
        std::string M_L_NO2;    // Выброс загрязняющего вещества движущимся автотранспортным потоком (г/с)
        std::string M_L_O3;     // Выброс загрязняющего вещества движущимся автотранспортным потоком (г/с)
        std::string M_L_SO2;    // Выброс загрязняющего вещества движущимся автотранспортным потоком (г/с)
        std::string M_L_CO;     // Выброс загрязняющего вещества движущимся автотранспортным потоком (г/с)
    };

    struct answerForSecondPractice {
        std::string IZA;  // Индекс Загрязнения атмосферы (ИЗА) (безразмерный)
        std::string CU;   // Стандартный Индекс (СИ) (безразмерный)
        std::string ES;   // Эффект Суммации (безразмерный)
    };

    struct informationForUser {
        informationForUser() {
            message = "";
            numberOfRemainingAttempts = 3;
            bestResult = 0;
        }
        std::string message;            // Сообщение, которое должно быть отображено с помощью "MessageBox.Show()"
        int numberOfRemainingAttempts;  // Количество попыток, которые остались у пользователя
        int bestResult;                 // Наилучший результат пользователя (в процентах)
    };

    enum typePollutant {
        PM2_5,
        PM10,
        NO2,
        O3,
        SO2,
        CO
    };

    static double get_r(typePollutant pollutant, double V) {
        if (pollutant == typePollutant::NO2)
            return 1.0;

        std::unordered_map<double, double> r =
            {
                {10, 1.35},
                {15, 1.28},
                {20, 1.2},
                {25, 1.1},
                {30, 1},
                {35, 0.88},
                {40, 0.75},
                {45, 0.63},
                {50, 0.5},
                {60, 0.3},
                {75, 0.45},
                {80, 0.5},
                {100, 0.65},
            };

        return r[V];
    }

    static double get_PDK_cc(typePollutant pollutant) {
        std::unordered_map<typePollutant, double> PDK_cc =
            {
                {typePollutant::PM2_5, 0.035},
                {typePollutant::PM10, 0.06},
                {typePollutant::NO2, 0.1},
                {typePollutant::O3, 0.1},
                {typePollutant::SO2, 0.05},
                {typePollutant::CO, 3},
            };

        return PDK_cc[pollutant];
    }

    static double get_PDK_mp(typePollutant pollutant) {
        std::unordered_map<typePollutant, double> PDK_mp =
            {
                {typePollutant::PM2_5, 0.3},
                {typePollutant::PM10, 0.16},
                {typePollutant::NO2, 0.2},
                {typePollutant::O3, 0.16},
                {typePollutant::SO2, 0.5},
                {typePollutant::CO, 5},
            };

        return PDK_mp[pollutant];
    }

    static double get_k(typePollutant pollutant) {
        // Класс опасности вещества
        std::unordered_map<typePollutant, double> k =
            {
                {typePollutant::PM2_5, 1},
                {typePollutant::PM10, 1},
                {typePollutant::NO2, 3},
                {typePollutant::O3, 1},
                {typePollutant::SO2, 3},
                {typePollutant::CO, 4},
            };

        return k[pollutant];
    }

    informationForUser info_firstPractice = informationForUser();
    informationForUser info_secondPractice = informationForUser();
    Variant curVariant = Variant();

    static answerForFirstPractice calculateAnswerForFirstPractice(Variant variant) {
        answerForFirstPractice answer = answerForFirstPractice();

        // Расчет по формулам
        double M_L_PM2_5 = (variant.firstPractice.L / 1200.0) * variant.firstPractice.M_p_PM2_5 * variant.firstPractice.G * get_r(typePollutant::PM2_5, variant.firstPractice.V);
        double M_L_PM10 = (variant.firstPractice.L / 1200.0) * variant.firstPractice.M_p_PM10 * variant.firstPractice.G * get_r(typePollutant::PM10, variant.firstPractice.V);
        double M_L_NO2 = (variant.firstPractice.L / 1200.0) * variant.firstPractice.M_p_NO2 * variant.firstPractice.G * get_r(typePollutant::NO2, variant.firstPractice.V);
        double M_L_O3 = (variant.firstPractice.L / 1200.0) * variant.firstPractice.M_p_O3 * variant.firstPractice.G * get_r(typePollutant::O3, variant.firstPractice.V);
        double M_L_SO2 = (variant.firstPractice.L / 1200.0) * variant.firstPractice.M_p_SO2 * variant.firstPractice.G * get_r(typePollutant::SO2, variant.firstPractice.V);
        double M_L_CO = (variant.firstPractice.L / 1200.0) * variant.firstPractice.M_p_CO * variant.firstPractice.G * get_r(typePollutant::CO, variant.firstPractice.V);

        // Перевод в string
        answer.M_L_PM2_5 = std::to_string(M_L_PM2_5);
        answer.M_L_PM10 = std::to_string(M_L_PM10);
        answer.M_L_NO2 = std::to_string(M_L_NO2);
        answer.M_L_O3 = std::to_string(M_L_O3);
        answer.M_L_SO2 = std::to_string(M_L_SO2);
        answer.M_L_CO = std::to_string(M_L_CO);

        return answer;
    }

    void compareAnswerForFirstPractice(answerForFirstPractice userAnswer) {
        if (info_firstPractice.numberOfRemainingAttempts <= 0) {
            info_firstPractice.message = "У вас больше не осталось попыток для прохождения практики.";
            return;
        }
        info_firstPractice.numberOfRemainingAttempts--;
        info_firstPractice.message = "";

        answerForFirstPractice rightAnswer = calculateAnswerForFirstPractice(curVariant);

        int currentResult = 0;

        currentResult += (rightAnswer.M_L_PM2_5 == userAnswer.M_L_PM2_5) ? 1 : 0;
        currentResult += (rightAnswer.M_L_PM10 == userAnswer.M_L_PM10) ? 1 : 0;
        currentResult += (rightAnswer.M_L_NO2 == userAnswer.M_L_NO2) ? 1 : 0;
        currentResult += (rightAnswer.M_L_O3 == userAnswer.M_L_O3) ? 1 : 0;
        currentResult += (rightAnswer.M_L_SO2 == userAnswer.M_L_SO2) ? 1 : 0;
        currentResult += (rightAnswer.M_L_CO == userAnswer.M_L_CO) ? 1 : 0;

        currentResult = (int)((currentResult / 6.0) * 100.0);

        if (currentResult > info_firstPractice.bestResult)
            info_firstPractice.bestResult = currentResult;

        info_firstPractice.message = "Ваш текущий результат:" + std::to_string(currentResult) + "%\nВаш наилучший результат: " + std::to_string(info_firstPractice.bestResult) + "%\nКоличество оставшихся попыток: " + std::to_string(info_firstPractice.numberOfRemainingAttempts);
    }

    static answerForSecondPractice calculateAnswerForSecondPractice(Variant variant) {
        answerForSecondPractice answer = answerForSecondPractice();

        // Расчет по формулам
        // Делим на 1000 т.к. нужно перевести микрограммы в миллиграммы
        double IZA =
            pow((variant.secondPractice.C_PM2_5 / 1000) / get_PDK_cc(typePollutant::PM2_5), get_k(typePollutant::PM2_5)) +
            pow((variant.secondPractice.C_PM10 / 1000) / get_PDK_cc(typePollutant::PM10), get_k(typePollutant::PM10)) +
            pow((variant.secondPractice.C_NO2 / 1000) / get_PDK_cc(typePollutant::NO2), get_k(typePollutant::NO2)) +
            pow((variant.secondPractice.C_O3 / 1000) / get_PDK_cc(typePollutant::O3), get_k(typePollutant::O3)) +
            pow((variant.secondPractice.C_SO2 / 1000) / get_PDK_cc(typePollutant::SO2), get_k(typePollutant::SO2)) +
            pow((variant.secondPractice.C_CO / 1000) / get_PDK_cc(typePollutant::CO), get_k(typePollutant::CO));

        // Расчет по формулам
        // Делим на 1000 т.к. нужно перевести микрограммы в миллиграммы
        double CU =
            ((variant.secondPractice.C_PM2_5 / 1000) / get_PDK_mp(typePollutant::PM2_5)) +
            ((variant.secondPractice.C_PM10 / 1000) / get_PDK_mp(typePollutant::PM10)) +
            ((variant.secondPractice.C_NO2 / 1000) / get_PDK_mp(typePollutant::NO2)) +
            ((variant.secondPractice.C_O3 / 1000) / get_PDK_mp(typePollutant::O3)) +
            ((variant.secondPractice.C_SO2 / 1000) / get_PDK_mp(typePollutant::SO2)) +
            ((variant.secondPractice.C_CO / 1000) / get_PDK_mp(typePollutant::CO));

        // Расчет по формулам
        // Делим на 1000 т.к. нужно перевести микрограммы в миллиграммы
        double tempES = 0, ES = 0;
        tempES = (variant.secondPractice.C_PM2_5 / 1000) / get_PDK_cc(typePollutant::PM2_5);
        ES += tempES <= 1 ? tempES : 0;
        tempES = (variant.secondPractice.C_PM10 / 1000) / get_PDK_cc(typePollutant::PM10);
        ES += tempES <= 1 ? tempES : 0;
        tempES = (variant.secondPractice.C_NO2 / 1000) / get_PDK_cc(typePollutant::NO2);
        ES += tempES <= 1 ? tempES : 0;
        tempES = (variant.secondPractice.C_O3 / 1000) / get_PDK_cc(typePollutant::O3);
        ES += tempES <= 1 ? tempES : 0;
        tempES = (variant.secondPractice.C_SO2 / 1000) / get_PDK_cc(typePollutant::SO2);
        ES += tempES <= 1 ? tempES : 0;
        tempES = (variant.secondPractice.C_CO / 1000) / get_PDK_cc(typePollutant::CO);
        ES += tempES <= 1 ? tempES : 0;

        // Перевод в string
        answer.IZA = std::to_string(IZA);
        answer.CU = std::to_string(CU);
        answer.ES = std::to_string(ES);

        return answer;
    }

    void compareAnswerForSecondPractice(answerForSecondPractice userAnswer) {
        if (info_secondPractice.numberOfRemainingAttempts <= 0) {
            info_secondPractice.message = "У вас больше не осталось попыток для прохождения практики.";
            return;
        }
        info_secondPractice.numberOfRemainingAttempts--;
        info_secondPractice.message = "";

        answerForSecondPractice rightAnswer = calculateAnswerForSecondPractice(curVariant);

        int currentResult = 0;

        currentResult += (rightAnswer.IZA == userAnswer.IZA) ? 1 : 0;
        currentResult += (rightAnswer.CU == userAnswer.CU) ? 1 : 0;
        currentResult += (rightAnswer.ES == userAnswer.ES) ? 1 : 0;

        currentResult = (int)((currentResult / 3.0) * 100.0);

        if (currentResult > info_secondPractice.bestResult)
            info_secondPractice.bestResult = currentResult;

        info_firstPractice.message = "Ваш текущий результат:" + std::to_string(currentResult) + "%\nВаш наилучший результат: " + std::to_string(info_secondPractice.bestResult) + "%\nКоличество оставшихся попыток: " + std::to_string(info_secondPractice.numberOfRemainingAttempts);
    }

    Variant jsonToVariant (QJsonObject& jsonObj)
    {
        Variant var{};

        var.numberVariant = jsonObj["numberVariant"].toInt();
        var.head = jsonObj["head"].toString().toStdString();

        practice_first first{};

        QJsonObject firstPrac = jsonObj["firstPractice"].toObject();
        first.whatWantFound = firstPrac["whatWantFound"].toString().toStdString();
        first.M_p_PM2_5 = firstPrac["M_p_PM2_5"].toDouble();
        first.M_p_PM10 = firstPrac["M_p_PM10"].toDouble();
        first.M_p_NO2 = firstPrac["M_p_NO2"].toDouble();
        first.M_p_O3 = firstPrac["M_p_O3"].toDouble();
        first.M_p_SO2 = firstPrac["M_p_SO2"].toDouble();
        first.M_p_CO = firstPrac["M_p_CO"].toDouble();
        first.L = firstPrac["L"].toDouble();
        first.V = firstPrac["V"].toDouble();
        first.G = firstPrac["G"].toDouble();
        var.firstPractice = first;

        practice_second second{};
        QJsonObject secondPrac = jsonObj["secondPractice"].toObject();
        second.whatWantFound = secondPrac["whatWantFound"].toString().toStdString();
        second.C_PM2_5 = secondPrac["C_PM2_5"].toDouble();
        second.C_PM10 = secondPrac["C_PM10"].toDouble();
        second.C_NO2 = secondPrac["C_NO2"].toDouble();
        second.C_O3 = secondPrac["C_O3"].toDouble();
        second.C_SO2 = secondPrac["C_SO2"].toDouble();
        second.C_CO = secondPrac["C_CO"].toDouble();
        var.secondPractice = second;

        return var;
    }

    Variant getRandomVariant ()
    {
        Variant var{};

        // Открываем файл
        QFile file(std::string(filePath + fileName).c_str());
        if (!file.open(QIODevice::ReadOnly)) {
            qDebug() << "Не удалось открыть файл:" << file.errorString();
            return var;
        }

        // Читаем содержимое файла
        QByteArray jsonData = file.readAll();
        file.close(); // Закрываем файл после чтения

        // Парсинг JSON
        QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonData);

        if (jsonDoc.isNull()) {
            qDebug() << "Ошибка парсинга JSON";
            return var;
        }

        QJsonArray variants = jsonDoc.array();

        auto variant = variants.at(QRandomGenerator::global()->bounded(0, variants.count() - 1)).toObject();
        var = jsonToVariant(variant);
        return var;
    }
};
