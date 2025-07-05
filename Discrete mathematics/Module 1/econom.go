package main

import (
	"bufio"
	"os"
	"fmt"
)

func econom(s string) int {
	if len(s)==0 {
		return 0
	}
	memo := make(map[string]int)
	return econom2(s, memo)
}

func econom2(s string, memo map[string]int) int {
	if _, ok := memo[s]; ok {
		return 0
	}

	if len(s) == 1 {
		return 0
	}

	if len(s) > 0 && s[0] == '(' {
		o1, o2 := split(s[2:len(s)-1])
		memo[s] = 1

		res := 1 + econom2(o1, memo) + econom2(o2, memo)
		return res
	}

	return 0
}

func split(s string) (string, string) {
	if len(s) == 0 {
		return "", ""
	}
	balance := 0
	sp := -1
	for i := 0; i < len(s); i++ {
		if s[i] == '(' {
			balance++
		} else if s[i] == ')' {
			balance--
		}
		if balance == 0 {
			sp = i + 1
      break
    }
	}
	if sp > 0 {
		return s[:sp], s[sp:]
	}
	return s, ""
}

func main() {
	in := bufio.NewScanner(os.Stdin)
	in.Scan()
	fmt.Println(econom(in.Text()))
}