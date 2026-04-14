#include <iostream>
#include <vector>

using namespace std;

// Функция для определения победителя (возвращает 1, если победил Павел, и 0, если Вика)
int getWinner(int n, int m, const vector<long long>& prefixSums) {
    long long scorePavel = 0;
    long long scoreVika = 0;
    int currentPos = 0;
    int lastMove = -1; // Количество чисел, взятых на предыдущем ходу
    bool isPavelTurn = true;

    while (currentPos < n) {
        long long maxStepSum = -2e18; // Минимально возможное значение для поиска максимума
        int chosenCount = 0;

        // Игрок выбирает i чисел (от 1 до m)
        for (int i = 1; i <= m; i++) {
            // Нельзя выйти за пределы последовательности
            if (currentPos + i > n) break;
            
            // Вариант 2: нельзя брать столько же, сколько взял противник только что
            if (i == lastMove) continue;

            // Считаем сумму за этот ход через префиксные суммы
            long long currentStepSum = prefixSums[currentPos + i] - prefixSums[currentPos];

            // Жадная стратегия: ищем максимальную сумму
            if (currentStepSum > maxStepSum) {
                maxStepSum = currentStepSum;
                chosenCount = i;
            } 
            // Если суммы одинаковы, выбираем минимальное количество чисел
            else if (currentStepSum == maxStepSum && chosenCount == 0) {
                chosenCount = i;
            }
        }

        // Если из-за ограничений хода нет, берем минимум (защита от зацикливания)
        if (chosenCount == 0) {
            chosenCount = (lastMove == 1) ? 2 : 1;
            if (currentPos + chosenCount > n) chosenCount = n - currentPos;
            maxStepSum = prefixSums[currentPos + chosenCount] - prefixSums[currentPos];
        }

        // Прибавляем очки текущему игроку
        if (isPavelTurn) {
            scorePavel += maxStepSum;
        } else {
            scoreVika += maxStepSum;
        }

        // Обновляем позицию в массиве и передаем ход
        currentPos += chosenCount;
        lastMove = chosenCount;
        isPavelTurn = !isPavelTurn;
    }

    // Возвращаем результат сравнения счетов
    if (scorePavel > scoreVika) return 1;
    else return 0;
}

int main() {
    int n, m;
    if (!(cin >> n >> m)) return 0;

    // Используем префиксные суммы для быстрого нахождения суммы на отрезке
    vector<long long> prefixSums(n + 1, 0);
    for (int i = 0; i < n; i++) {
        long long val;
        cin >> val;
        prefixSums[i + 1] = prefixSums[i] + val;
    }

    // Вызываем функцию и выводим результат
    cout << getWinner(n, m, prefixSums) << endl;

    return 0;
}