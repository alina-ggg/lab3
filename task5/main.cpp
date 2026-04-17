#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>

using namespace std;

// Структура для хранения точки данных
struct DataPoint {
    double time;
    double temp;
};

int main() {

    double Tk, Tsr, r, maxTime, dt;

    // 1. Ввод необходимых параметров
    cout << "=== Моделирование остывания кофе ===" << endl;
    cout << "Введите начальную температуру кофе (Tk): ";
    cin >> Tk;
    cout << "Введите температуру окружающей среды (Tsr): ";
    cin >> Tsr;
    cout << "Введите коэффициент остывания (r): ";
    cin >> r;
    cout << "Введите максимальное время наблюдения (мин): ";
    cin >> maxTime;
    cout << "Введите шаг измерения времени (dt): ";
    cin >> dt;

    vector<DataPoint> measurements;

    // 2. Функция моделирования (циклический расчет)
    cout << "\nТаблица зависимости температуры от времени:" << endl;
    cout << "---------------------------" << endl;
    cout << "| Время (мин) | Темп. (C) |" << endl;
    cout << "---------------------------" << endl;

    for (double t = 0; t <= maxTime; t += dt) {
        // Вычисление температуры по закону Ньютона
        double currentTemp = Tsr + (Tk - Tsr) * exp(-r * t);
        
        measurements.push_back({t, currentTemp});

        // Вывод строки таблицы
        cout << "| " << setw(11) << fixed << setprecision(1) << t 
             << " | " << setw(9) << currentTemp << " |" << endl;
    }
    cout << "---------------------------" << endl;
    
    return 0;
}