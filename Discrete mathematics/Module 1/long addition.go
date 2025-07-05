package main

func add(a, b []int32, p int) []int32 {
	maxLen := len(a)
	if len(b) > maxLen {
		maxLen = len(b)
	}

	result := make([]int32, maxLen+1)
	carry := int32(0)

	for i := 0; i < maxLen; i++ {
		digitA := int32(0)
		if i < len(a) {
			digitA = a[i]
		}
		digitB := int32(0)
		if i < len(b) {
			digitB = b[i]
		}

		sum := digitA + digitB + carry
		result[i] = sum % int32(p)
		carry = sum / int32(p)
	}

	result[maxLen] = carry

	if result[maxLen] == 0 {
		result = result[:maxLen]
	}

	return result
}

func main() {
	p := 2
	a := []int32{1, 2, 3}
	b := []int32{4, 5, 6}
	sum := add(a, b, p)
	for _, digit := range sum {
		print(digit, " ")
	}
}