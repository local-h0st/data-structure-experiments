package main

import (
	"fmt"
	"math/rand"
	"time"
)

const list_length = 16

func main() {
	rand.Seed(time.Now().Unix())
	random_integer_list := make([]int, 0)
	for i := 0; i < list_length; i++ {
		random_integer_list = append(random_integer_list, rand.Intn(100))
	}
	fmt.Println("original:", random_integer_list)
	fmt.Println()
	// data is well prepared
	dk := list_length / 2
	for dk != 0 {
		ShellSort(&random_integer_list, dk)
		dk = dk / 2
	}
	fmt.Println()
	fmt.Println("final result:", random_integer_list)

}

func ShellSort(list *[]int, dk int) {
	fmt.Println("dk:", dk)
	fmt.Println("before sort:", *list)
	// index from 0 to dk-1 belongs to diffierent groups
	for group_index := 0; group_index < dk; group_index++ {
		// all the elements with index (group_index + i * dk) are in the same group
		ordered := make([]int, 0)
		ordered = append(ordered, (*list)[group_index])
		for i := 1; group_index+i*dk < len(*list); i++ {
			// this loop takes out one elem at a time
			pos := len(ordered) - 1
			for (*list)[group_index+i*dk] < ordered[pos] {
				pos--
				if pos == -1 {
					break
				}
			}
			// should be right after the pos
			// namely at index of pos+1
			rear_part := make([]int, 0)
			rear_part = append([]int{}, ordered[pos+1:]...)
			ordered = append(ordered[:pos+1], (*list)[group_index+i*dk])
			ordered = append(ordered, rear_part...)
		}
		for i := 0; i < len(ordered); i++ {
			(*list)[group_index+i*dk] = ordered[i]
		}
	}
	fmt.Println("after sort:", *list)
}

// ;;;;;;;;;;;;;;;;;;;;
// Author: redh3t
// TimeStamp: 2022/12/8
// 还好，一节课写完不算复杂
// 有个下标越界调试了一会
// ;;;;;;;;;;;;;;;;;;;;
