package main

func qssort(n int,
	less func(i, j int) bool,
	swap func(i, j int)) {

	type Interval struct {
		low  int
		high int
	}

	stack := make([]Interval, 0, n)

	stack = append(stack, Interval{0, n - 1})

	for len(stack) > 0 {
		nowinterval := stack[len(stack)-1]
		stack = stack[:len(stack)-1]

		low := nowinterval.low
		high := nowinterval.high

		if low < high {
			pivot := low

			i := low + 1
			j := high

			for {
				for i <= high && !less(pivot, i) {
					i++
				}

				for j >= low+1 && !less(j, pivot) {
					j--
				}

				if i >= j {
					break
				}

				swap(i, j)

				i++
				j--
			}

			swap(pivot, j)

			stack = append(stack, Interval{low, j - 1})
			stack = append(stack, Interval{j + 1, high})
		}
	}
}

func main() {

}