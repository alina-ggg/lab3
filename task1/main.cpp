#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

// Функция для вычисления значения Y в зависимости от X
double calculateY(double x) {
    if (x >= -5.0 && x <= -3.0) {
        return sqrt(4.0 - pow(x + 3.0, 2));
    } 
    else if (x > -3.0 && x <= -2.0) {
        return -x - 1.0;
    } 
    else if (x > -2.0 && x <= -1.0) {
        return sqrt(1.0 - pow(x + 2.0, 2));
    } 
    else if (x > -1.0 && x <= 1.0) {
        return -0.5 * x - 0.5;
    } 
    else if (x > 1.0 && x <= 2.0) {
        return -1.0 - sqrt(1.0 - pow(x - 2.0, 2));
    } 
    else if (x > 2.0 && x <= 3.0) {
        return -x;
    } 
    else if (x > 3.0 && x <= 5.0) {
        return -3.0 + sqrt(4.0 - pow(x - 5.0, 2));
    } 
    else {
        // Если X выходит за пределы графика
        return NAN; 
    }
}

int main() {
    // Исходные данные для полного покрытия графика
    double x_start = -5.0;
    double x_end = 5.0;
    double dx = 0.5;

    // Вывод шапки таблицы
    cout << "---------------------------" << endl;
    cout << "|" << setw(8) << "X" << " |" << setw(12) << "Y" << " |" << endl;
    cout << "---------------------------" << endl;

    // Цикл вычисления и вывода значений
    // + dx/10.0 используется для компенсации погрешности чисел с плавающей точкой
    for (double x = x_start; x <= x_end + dx / 10.0; x += dx) {
        double y = calculateY(x);
        
        cout << "|" << setw(8) << fixed << setprecision(2) << x << " |";
        
        if (isnan(y)) {
            cout << setw(12) << "N/A" << " |" << endl;
        } else {
            cout << setw(12) << fixed << setprecision(4) << y << " |" << endl;
        }
    }
    cout << "---------------------------" << endl;

    return 0;
}