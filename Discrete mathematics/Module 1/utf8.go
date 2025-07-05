package main

import (
	"fmt"
)

func encode(utf32 []rune) []byte {
	utf8 := make([]byte, 0)
	for _, r := range utf32 {
		if r <= 0b01111111 {
			utf8 = append(utf8, byte(r))
		} else if r <= 0b0000011111111111 {
			utf8 = append(utf8, byte(0b11000000|(r>>6&0b00011111)))
			utf8 = append(utf8, byte(0b10000000|(r&0b00111111)))
		} else if r <= 0b000000001111111111111111 {
			utf8 = append(utf8, byte(0b11100000|(r>>12&0b00001111)))
			utf8 = append(utf8, byte(0b10000000|(r>>6&0b00111111)))
			utf8 = append(utf8, byte(0b10000000|(r&0b00111111)))
		} else if r <= 0b000100001111111111111111 {
			utf8 = append(utf8, byte(0b11110000|(r>>18&0b00000111)))
			utf8 = append(utf8, byte(0b10000000|(r>>12&0b00111111)))
			utf8 = append(utf8, byte(0b10000000|(r>>6&0b00111111)))
			utf8 = append(utf8, byte(0b10000000|(r&0b00111111)))
		}
	}
	return utf8
}


func decode(utf8 []byte) []rune {
	utf32 := make([]rune, 0)
	for i := 0; i < len(utf8); {
		b := utf8[i]
		var r rune
		var size int
		if b < 0b10000000 {
			r = rune(b)
			size = 1
		} else if b >= 0b11000000 && b < 0b11100000 {
			r = rune((rune(b&0b00011111)<<6) | (rune(utf8[i+1]&0b00111111)))
			size = 2
		} else if b >= 0b11100000 && b < 0b11110000 {
			r = rune((rune(b&0b00001111)<<12) | (rune(utf8[i+1]&0b00111111)<<6) | 
			                                    (rune(utf8[i+2]&0b00111111)))
			size = 3
		} else if b >= 0b11110000 && b < 0b11111000 {
			r = rune((rune(b&0b00000111)<<18) | (rune(utf8[i+1]&0b00111111)<<12) | 
			                                    (rune(utf8[i+2]&0b00111111)<<6) | 
			                                    (rune(utf8[i+3]&0b00111111)))
			size = 4
		} else {
			return []rune{}
		}
		utf32 = append(utf32, r)
		i += size
	}
	return utf32
}

func main() {
	text := "Hello, World!"
	s1 := ([]byte)(text)
	s2 := ([]rune)(text)
	k1 := decode(s1)
	k2 := encode(s2)
	for _, x := range k1 {
		fmt.Printf("%c %d\n", x, x)
	} 
	for _, x := range k2 {
		fmt.Printf("%c %d\n", x, x)
	}
}