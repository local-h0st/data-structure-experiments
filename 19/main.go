package main

import (
	"fmt"
	"math/rand"
	"time"
)

const list_length = 16

func main() {
	rand.Seed(time.Now().Unix())
	random_integer_list := make([]int, list_length)
	for i := 0; i < list_length; i++ {
		random_integer_list[i] = rand.Intn(100)
	}
	fmt.Println("random list generated", random_integer_list)
	// 开始排序
	tmp := make([]int, list_length)
	var first, final int
	tmp[first] = random_integer_list[0]
	for _, value := range random_integer_list[1:] {
		if value < tmp[first] {
			first = mod(first-1, list_length)
			tmp[first] = value
		} else if value > tmp[final] {
			final = mod(final+1, list_length)
			tmp[final] = value
		} else {
			var i int
			for ; value < tmp[mod(final-i, list_length)]; i++ {
				tmp[mod(final-i+1, list_length)] = tmp[mod(final-i, list_length)]
			}
			tmp[mod(final-i+1, list_length)] = value
			final = mod(final+1, list_length)
		}
	}
	fmt.Println("tmp list after sorting", tmp)
	fmt.Println("first & final", first, final)
	sorted_list := make([]int, list_length)
	for i := first; mod(i, list_length) != final; i++ {
		sorted_list[i-first] = tmp[mod(i, list_length)]
	}
	sorted_list[list_length-1] = tmp[final]
	fmt.Println("copied to sorted list", sorted_list)
}

func mod(n, m int) int {
	result := n % m
	if result < 0 {
		result += m
	}
	return result
}

// ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
// Author: redh3t
// TimeStamp: 2022/12/6 16:32
// 一节课不到的时间写完了，写起来还算简单
// 其实golang的slice具有相比c++的天然优势
// slice长度可扩展，不需要采用循环的方式
// 但为了和c++保持近似我还是选择循环数组
// ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
