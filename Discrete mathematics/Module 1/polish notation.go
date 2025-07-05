package main

import (
	"fmt"
	"strconv"
	"bufio"
  "os"
)

func eval(op string, a, b int) int {
	switch op {
	case "+":
		return a + b
	case "-":
		return a - b
	case "*":
		return a * b
	default:
	  return 0
	}
}

// удаление пробелов
func parse(s string) []string {
	var tokens []string
	for _, r := range s {
		switch r {
		case ' ', '(':
			if r == '(' {
				tokens = append(tokens, "(")
			}
		case ')':
			tokens = append(tokens, ")")
		case '+', '-', '*':
			tokens = append(tokens, string(r))
		default:
			tokens = append(tokens, string(r))
		}
	}

	return tokens
}

func calculate(tokens []string) int {
	stack := make([]string, 0)

	for _, token := range tokens {
		switch token {
		case "(":
			continue
		case ")":
			bs := stack[len(stack)-1]
			stack = stack[:len(stack)-1]
			as := stack[len(stack)-1]
			stack = stack[:len(stack)-1]
			op := stack[len(stack)-1]
			stack = stack[:len(stack)-1]

			a, _ := strconv.Atoi(as)
			b, _ := strconv.Atoi(bs)

			result := eval(op, a, b)
			stack = append(stack, strconv.Itoa(result))

		case "+", "-", "*":
			stack = append(stack, token)
		default:
			stack = append(stack, token)
		}
	}

	res, _ := strconv.Atoi(stack[0])

	return res
}

func main() {
	scanner := bufio.NewScanner(os.Stdin)
	scanner.Scan()
	dano := scanner.Text()

	fmt.Print(calculate(parse(dano)))
}