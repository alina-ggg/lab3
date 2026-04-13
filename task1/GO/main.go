package main

import (
	"fmt"
	"math"
)

func calculateY(x float64) float64 {
	if x >= -5.0 && x <= -3.0 {
		return math.Sqrt(4.0 - math.Pow(x+3.0, 2))
	} else if x > -3.0 && x <= -2.0 {
		return -x - 1.0
	} else if x > -2.0 && x <= -1.0 {
		return math.Sqrt(1.0 - math.Pow(x+2.0, 2))
	} else if x > -1.0 && x <= 1.0 {
		return -0.5*x - 0.5
	} else if x > 1.0 && x <= 2.0 {
		return -1.0 - math.Sqrt(1.0-math.Pow(x-2.0, 2))
	} else if x > 2.0 && x <= 3.0 {
		return -x
	} else if x > 3.0 && x <= 5.0 {
		return -3.0 + math.Sqrt(4.0-math.Pow(x-5.0, 2))
	} else {
		return math.NaN()
	}
}

func main() {
	xStart := -5.0
	xEnd := 5.0
	dx := 0.5

	fmt.Println("-------------------------")
	// % — сигнализирует о начале команды
	// s — сокращение от string (строка). Говорит, что мы вставляем текст.
	fmt.Printf("|%8s |%12s |\n", "X", "Y")
	fmt.Println("-------------------------")

	for x := xStart; x <= xEnd+dx/10.0; x += dx {
		y := calculateY(x)

		// %8.2f означает ширину 8 символов и 2 знака после запятой
		fmt.Printf("|%8.2f |", x)

		if math.IsNaN(y) {
			fmt.Printf("%12s |\n", "N/A")
		} else {
			fmt.Printf("%12.4f |\n", y)
		}
	}
	fmt.Println("-------------------------")
}
