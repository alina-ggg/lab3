#include <iostream>
#include <cmath>

using namespace std;

// Функция для сокращения дроби (Нахождение наибольшего общего делителя)
long long getGcd(long long a, long long b) {
    while (b) {
        a %= b;
        swap(a, b);
    }
    return a;
}

int main() {
    int a, b;
    if (!(cin >> a >> b)) return 0;

    // Условие расходимости
    if (b <= 1) {
        cout << "infinity" << endl;
        return 0;
    }

    // Будем накапливать сумму в double для точности
    long double sum = 0;
    for (int n = 1; n <= 500; ++n) {
        long double term = pow((long double)n, a) / pow((long double)b, n);
        if (term < 1e-19) break; // Ряд сходится быстро, этого достаточно
        sum += term;
    }

    // Теперь превратим десятичное число обратно в дробь
    // Используем упрощенный метод подбора знаменателя
    long long bestNum = 0, bestDen = 1;
    long double minerror = 1e-15;

    for (long long den = 1; den <= 10000; ++den) {
        long long num = (long long)round(sum * den);
        if (abs(sum - (long double)num / den) < minerror) {
            bestNum = num;
            bestDen = den;
            break;
        }
    }

    // Сокращаем результат перед выводом
    long long common = getGcd(bestNum, bestDen);
    cout << bestNum / common << "/" << bestDen / common << endl;

    return 0;
}