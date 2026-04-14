package main

import (
	"fmt"
)

// getWinner определяет победителя: 1 если Павел, 0 если Вика
func getWinner(n int, m int, prefixSums []int64) int {
	var scorePavel int64 = 0
	var scoreVika int64 = 0
	currentPos := 0
	lastMove := -1
	isPavelTurn := true

	for currentPos < n {
		// Используем очень маленькое число для инициализации поиска максимума
		var maxStepSum int64 = -2e18
		chosenCount := 0

		for i := 1; i <= m; i++ {
			// Проверка на выход за границы и ограничение Варианта 2
			if currentPos+i > n {
				break
			}
			if i == lastMove {
				continue
			}

			// Вычисляем сумму за текущий ход
			currentStepSum := prefixSums[currentPos+i] - prefixSums[currentPos]

			// Жадный выбор: ищем максимальную сумму
			if currentStepSum > maxStepSum {
				maxStepSum = currentStepSum
				chosenCount = i
			} else if currentStepSum == maxStepSum && chosenCount == 0 {
				// Если суммы равны, выбираем минимальное количество чисел
				chosenCount = i
			}
		}

		// Защита от тупиковой ситуации (если легальный ход не найден)
		if chosenCount == 0 {
			if lastMove == 1 {
				chosenCount = 2
			} else {
				chosenCount = 1
			}
			if currentPos+chosenCount > n {
				chosenCount = n - currentPos
			}
			maxStepSum = prefixSums[currentPos+chosenCount] - prefixSums[currentPos]
		}

		// Начисление очков
		if isPavelTurn {
			scorePavel += maxStepSum
		} else {
			scoreVika += maxStepSum
		}

		// Смена состояния
		currentPos += chosenCount
		lastMove = chosenCount
		isPavelTurn = !isPavelTurn
	}

	if scorePavel > scoreVika {
		return 1
	}
	return 0
}

func main() {
	var n, m int
	_, err := fmt.Scan(&n, &m)
	if err != nil {
		return
	}

	// Срез для префиксных сумм (аналог vector в C++)
	prefixSums := make([]int64, n+1)
	for i := 0; i < n; i++ {
		var val int64
		fmt.Scan(&val)
		prefixSums[i+1] = prefixSums[i] + val
	}

	fmt.Println(getWinner(n, m, prefixSums))
}
