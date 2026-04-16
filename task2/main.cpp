#include <iostream>
#include <vector>
#include <cmath> // математические функции (sqrt)
#include <ctime> // srand(time(0)) для оживления генератора случайных чисел, чтобы они были разными
#include <cstdlib> // функции rand() (генерация случайного числа) и srand() (установка стартовой точки для генератора)
#include <numeric> // функция gcd (нахождение наибольшего общего делителя — НОД)
#include <algorithm> // для сортировки, поиска, обмена. функция swap(a, b)

using namespace std;

typedef unsigned long long ull; // создаем короткое имя для типа данных

// Функция для модульного возведения в степень (a^b % n)
// Используем __int128 для промежуточного умножения, чтобы избежать переполнения
ull power(ull a, ull b, ull n) {
    ull res = 1;
    a %= n;
    while (b > 0) {
        if (b % 2 == 1) res = (__int128)res * a % n;
        a = (__int128)a * a % n;
        b /= 2;
    }
    return res;
}

// Алгоритм Евклида для нахождения НОД
ull gcd(ull a, ull b) {
    while (b) {
        a %= b;
        swap(a, b);
    }
    return a;
}

// 1. Решето Эратосфена для получения простых чисел qi < 500
vector<int> getPrimes(int limit) {
    vector<bool> isPrime(limit + 1, true);
    isPrime[0] = isPrime[1] = false;
    for (int p = 2; p * p <= limit; p++) {
        if (isPrime[p]) {
            for (int i = p * p; i <= limit; i += p)
                isPrime[i] = false;
        }
    }
    vector<int> primes;
    for (int p = 2; p <= limit; p++) {
        if (isPrime[p]) primes.push_back(p);
    }
    return primes;
}

// Процедура тестирования Поклингтона
bool pocklingtonTest(ull n, ull F, const vector<ull>& factors, int t) {
    if (n < 2) return false;
    if (n == 2 || n == 3) return true;

    for (int j = 0; j < t; ++j) {
        // Выбираем случайное 'a' в диапазоне (1, n)
        ull a = 2 + rand() % (n - 3); 
        
        // 1) Условие: a^(n-1) == 1 (mod n)
        if (power(a, n - 1, n) != 1) return false; // power - возведение числа в степень по модулю

        // 2) Условие: НОД(a^((n-1)/qi) - 1, n) == 1 для всех qi
        bool usl2 = true;
        for (ull qi : factors) {
            ull exp = (n - 1) / qi;
            ull val = power(a, exp, n);
            if (gcd(val - 1, n) != 1) {
                usl2 = false;
                break;
            }
        }
        
        if (usl2) return true; 
    }
    return false;
}

int main() {
    srand(time(0));

    int bits;
    cout << "Введите требуемую разрядность (bits): ";
    cin >> bits;

    vector<int> primeTable = getPrimes(500);
    
    // Структуры для хранения результатов таблицы 2
    vector<ull> foundPrimes;
    vector<bool> testResults;
    vector<int> rejectedCounts;

    while (foundPrimes.size() < 10) {
        int rejected = 0;
        bool isprimefound = false;
        ull finaln = 0;
        ull finalF = 0;
        vector<ull> finalfactors;

        while (!isprimefound) {
            // Генерация числа n = RF + 1
            ull F = 1;
            vector<ull> factors;
            
            // Набираем F из случайных простых чисел
            while (F < (1ULL << (bits / 2))) {
                ull q = primeTable[rand() % primeTable.size()];
                F *= q;
                factors.push_back(q);
            }

            // Вычисляем R (случайное четное), n = RF + 1
            ull R = (1ULL << (bits - 1)) / F; 
            if (R % 2 != 0) R++;
            ull n = R * F + 1;

            // Проверка по тесту Поклингтона
            if (pocklingtonTest(n, F, factors, 1)) {
                finaln = n;
                finalF = F;
                finalfactors = factors;
                isprimefound = true;
            } else {
                rejected++;
            }
        }

        // Шаг 6: Дополнительная проверка с параметром t = 2
        bool finalcheck = pocklingtonTest(finaln, finalF, finalfactors, 2);
        
        foundPrimes.push_back(finaln);
        testResults.push_back(finalcheck);
        rejectedCounts.push_back(rejected);
    }

    // Вывод Таблицы
    cout << "\nРезультаты выполнения тестов\n";
    cout << "---------------------------------------------------------------------------------------\n";
    cout << " №\t| ";
    for (int i = 1; i <= 10; ++i) cout << i << "\t| ";
    cout << "\n---------------------------------------------------------------------------------------\n";
    
    cout << "Число\t| ";
    for (ull p : foundPrimes) cout << p << "\t| ";
    cout << "\n---------------------------------------------------------------------------------------\n";
    
    cout << "Тест\t| ";
    for (bool r : testResults) cout << (r ? "true" : "false") << "\t| ";
    cout << "\n---------------------------------------------------------------------------------------\n";
    
    cout << "Rejected| ";
    for (int rej : rejectedCounts) cout << rej << "\t| ";
    cout << "\n---------------------------------------------------------------------------------------\n";

    return 0;
}