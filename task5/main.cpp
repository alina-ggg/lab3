#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>

using namespace std;

struct DataPoint {
    double x; // Время
    double y; // Температура
};

// Функция cafe - рассчитывает координаты графика
void cafe(double Tk, double Tsr, double r, double maxTime, double dt, vector<DataPoint>& data) {
    for (double t = 0; t <= maxTime; t += dt) {
        double currentTemp = Tsr + (Tk - Tsr) * exp(-r * t);
        data.push_back({t, currentTemp});
    }
}

// Функция aprox - рассчитывает коэффициенты аппроксимирующей прямой y = ax + b
void aprox(const vector<DataPoint>& data, double& a, double& b) {
    int n = data.size();
    double sumX = 0, sumY = 0, sumXY = 0, sumX2 = 0;

    for (const auto& p : data) {
        sumX += p.x;
        sumY += p.y;
        sumXY += p.x * p.y;
        sumX2 += p.x * p.x;
    }

    // Формулы из блока aprox на схеме
    a = (n * sumXY - sumX * sumY) / (n * sumX2 - sumX * sumX);
    b = (sumY - a * sumX) / n;
}

// Функция korrel - рассчитывает коэффициент корреляции r
double korrel(const vector<DataPoint>& data) {
    int n = data.size();
    double sumX = 0, sumY = 0;
    for (const auto& p : data) {
        sumX += p.x;
        sumY += p.y;
    }
    double meanX = sumX / n;
    double meanY = sumY / n;

    double numerator = 0;
    double denX = 0;
    double denY = 0;

    for (const auto& p : data) {
        numerator += (p.x - meanX) * (p.y - meanY);
        denX += pow(p.x - meanX, 2);
        denY += pow(p.y - meanY, 2);
    }

    return numerator / sqrt(denX * denY);
}

int main() {
    double Tk, Tsr, r_coeff, maxTime, dt;

    cout << "Введите Tk, Tsr, r, maxTime, dt: ";
    cin >> Tk >> Tsr >> r_coeff >> maxTime >> dt;

    vector<DataPoint> measurements;

    // Вызов функций согласно блок-схеме
    cafe(Tk, Tsr, r_coeff, maxTime, dt, measurements);

    double a, b;
    aprox(measurements, a, b);

    double r_corr = korrel(measurements);

    // Вывод таблицы
    cout << "\nТаблица зависимости температуры от времени:" << endl;
    cout << "-------------------------------" << endl;
    // Задаем ширину для заголовков (12 символов для времени, 12 для температуры)
    cout << "| " << setw(12) << left << "Время (мин)" 
         << " | " << setw(12) << left << "Темп. (C)" << " |" << endl;
    cout << "-------------------------------" << endl;

    for (const auto& p : measurements) {
        // setw(12) гарантирует, что каждое число займет ровно 12 позиций
        cout << "| " << setw(12) << left << fixed << setprecision(2) << p.x 
             << " | " << setw(12) << left << fixed << setprecision(2) << p.y << " |" << endl;
    }
    cout << "-------------------------------" << endl;

    // Вывод параметров (последний блок схемы)
    cout << "\n=== Результаты анализа ===" << endl;
    cout << "Уравнение прямой: y = " << fixed << setprecision(4) << a << " * x + " << b << endl;
    cout << "Коэффициент корреляции: " << r_corr << endl;
    cout << "Коэффициент детерминации (R^2): " << pow(r_corr, 2) << endl;
    return 0;
}