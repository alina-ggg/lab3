package main

import (
	"fmt"
	"math"
)

// getGcd находит наибольший общий делитель (алгоритм Евклида)
func getGcd(a, b int64) int64 {
	for b != 0 {
		a %= b
		a, b = b, a
	}
	return a
}

func main() {
	var a, b int
	// Считываем входные данные
	_, err := fmt.Scan(&a, &b)
	if err != nil {
		return
	}

	// Условие расходимости: если основание b <= 1, сумма стремится к бесконечности
	if b <= 1 {
		fmt.Println("infinity")
		return
	}

	// Накапливаем сумму ряда
	var sum float64
	for n := 1.0; n <= 500; n++ {
		term := math.Pow(n, float64(a)) / math.Pow(float64(b), n)
		if term < 1e-19 {
			break
		}
		sum += term
	}

	// Поиск подходящей дроби методом перебора знаменателя
	var bestNum, bestDen int64
	minError := 1e-15

	for den := int64(1); den <= 10000; den++ {
		// round в Go возвращает float64, приводим к int64
		num := int64(math.Round(sum * float64(den)))
		if math.Abs(sum-float64(num)/float64(den)) < minError {
			bestNum = num
			bestDen = den
			break
		}
	}

	// Сокращаем дробь через НОД и выводим результат
	common := getGcd(bestNum, bestDen)
	if bestDen != 0 {
		fmt.Printf("%d/%d\n", bestNum/common, bestDen/common)
	}
}
