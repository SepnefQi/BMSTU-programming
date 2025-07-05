package main

import (
	"fmt"
	"math"
)

type Rational struct {
	num int //numerator
	den int //denominator
}

func gcd(a, b int) int {
	a = int(math.Abs(float64(a)))
	b = int(math.Abs(float64(b)))
	for b != 0 {
		a, b = b, a%b
	}
	return a
}

func (n *Rational) norm() {
	g := gcd(n.num, n.den)
	n.num /= g
	n.den /= g
	if n.den < 0 {
		n.num = -n.num
		n.den = -n.den
	}
}

func main() {
	var n int
	fmt.Scan(&n)
	
	m := make([][] Rational, n)
	for i := range m {
		m[i] = make([]Rational, n+1)
		for j := 0; j < n+1; j++ {
			var val int
			fmt.Scan(&val)
			m[i][j] = Rational{num: val, den: 1}
		}
	}
	// 1) Выбор ненулевого элемента в столбце и деление на него всей строки
	// 2) Переставляем строки, чтобы эта стала 1-ой
	// 3) Вычитаем её из всех остальных
	
	for i := 0; i<n; i++ {
		k := i
		for j := i; j<n; j++ { // нашли ненулевое число
			if m[j][i].num != 0 {
				k = j
				break
			}
		}
		if k != i { // сделали строку 1-ой
			m[k], m[i] = m[i], m[k]
		}
		if m[i][i].num == 0 { // если на главной диагонали 0 => нет решений
		  fmt.Print("No solution")
			return
		}

		for j := i+1; j<=n; j++ { // поделили все числа в строке на него, оно стало 1/1
			m[i][j].den *= m[i][i].num
			m[i][j].num *= m[i][i].den
			m[i][j].norm()
		}
		m[i][i].num = 1
		m[i][i].den = 1

		for j := i+1; j<n; j++ { // отнимаем от других строк выбранную
		  ratio := m[j][i]
		  for q := i; q<=n; q++ {
			  mult := Rational {
				  num: ratio.num * m[i][q].num,
				  den: ratio.den * m[i][q].den,
				}
				mult.norm()
				mult2 := Rational {
					num: m[j][q].num * mult.den - mult.num * m[j][q].den,
				  den: m[j][q].den * mult.den,
				}
				m[j][q] = mult2
				m[j][q].norm() 
			}
		}
	}
	
	for i := n - 1; i >= 0; i-- {
		for j := i-1; j >= 0; j-- {
			ratio := m[j][i]
			for q := i; q <= n; q++ {
				mult := Rational{
					num: ratio.num * m[i][q].num,
					den: ratio.den * m[i][q].den,
				}
				mult.norm()

				mult2 := Rational{
					num: m[j][q].num*mult.den - mult.num*m[j][q].den,
					den: m[j][q].den * mult.den,
				}

				m[j][q] = mult2
				m[j][q].norm()
			}
		}
	}
	
	for i := 0; i<n; i++ {
	  m[i][n].norm()
	  fmt.Printf("%d/%d\n", m[i][n].num, m[i][n].den)
	}
}