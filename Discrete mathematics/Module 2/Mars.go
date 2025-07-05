package main

import (
	"fmt"
	"bufio"
	"os"
)

func main() {
	var n int
	bufin := bufio.NewReader(os.Stdin)
	fmt.Fscan(bufin, &n)
	
	d := make([][]string, n)
	for i := 0; i<n; i++ {
		d[i] = make([]string, n)
		for j := 0; j<n; j++ {
			fmt.Fscan(bufin, &d[i][j])
		}
	}
	
	best_group1 := []int {}
	have_solution := n+1
	
	//вариант решения 1: перебор абсолютно всех возможных решений, которых 2^n-1
	for i:=0; i<(1<<n); i++ {
		group1 := []int {}
		group2 := []int {}
		for j:=0; j<n; j++ {
			if (i>>j) & 1 == 1 { //определит войдёт ли человек с номером j+1 в 1-ую группу или нет
				group1 = append(group1, j+1)
			} else {
				group2 = append(group2, j+1)
			}
		}
		// i=2 => 4 способа 1<<2 = 100 = 4
		// 1) i=0 gr1() gr2(1,2)
		// 2) i=1 gr1(1) gr2(2)
		// 3) i=2 gr1(2) gr2(1)
		// 4) i=3 gr1(1,2) gr2()
		
		// теперь проверка: возможно ли сделать такие группы, нет ли "+"
		correct := 1
		for cor11:=0; cor11<len(group1); cor11++ {
			for cor12:=cor11+1; cor12<len(group1); cor12++ {
				if d[group1[cor11]-1][group1[cor12]-1] == "+" {
					correct = 0
					break
				}
			}
			if correct==0 {
				break
			}
		}
		if correct==0 {
			continue
		}
		for cor21:=0; cor21<len(group2); cor21++ {
			for cor22:=cor21+1; cor22<len(group2); cor22++ {
				if d[group2[cor21]-1][group2[cor22]-1] == "+" {
					correct = 0
					break
				}
			}
			if correct==0 {
				break
			}
		}
		if correct==0 {
			continue
		}
		
		size_diff := abs(len(group1) - len(group2))
		if size_diff < have_solution {
			have_solution = size_diff
			if len(group1) <= len(group2) {
				best_group1 = group1
			} else {
				best_group1 = group2
			}
		} else if size_diff == have_solution {
			maybe_best := []int {}
			if len(group1) <= len(group2) {
				maybe_best = group1
			} else {
				maybe_best = group2
			}

			if len(maybe_best) == 0 && len(best_group1) > 0 {
				continue
			}
			if len(best_group1) == 0 && len(maybe_best) > 0 {
				best_group1 = maybe_best
				continue
			}

			best := 0

			for j:=0; j<len(maybe_best); j++ {
				if maybe_best[j]<best_group1[j] {
					best = 1
					break
				}
				if maybe_best[j]>best_group1[j] {
					break
				}
			}
			
			if best==1 {
				best_group1 = maybe_best
			}
		}
	}
	
	if have_solution == n+1 {
		fmt.Print("No solution")
	} else {
		for i := 0; i < len(best_group1); i++ {
			fmt.Printf("%d ", best_group1[i])
		}
	}
}

func abs (n int) int {
	if n<0 {
		return -n
	}
	return n
}