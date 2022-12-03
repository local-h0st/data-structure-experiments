package main

import (
	"fmt"
)

func main() {
	graph := []Vertix{
		Vertix{"V0", 0, []int{1, 2}, 0},
		Vertix{"V1", 1, []int{3}, 0},
		Vertix{"V2", 2, []int{3, 5}, 0},
		Vertix{"V3", 3, []int{}, 0},
		Vertix{"V4", 4, []int{3}, 0},
		Vertix{"V5", 5, []int{}, 0},
	}
	Topo(graph)
}

type Vertix struct {
	Data             string
	Current_index    int
	Next_indexs_list []int // 出边表
	Indegree         int
}

func SetIndegree(vlist *[]Vertix) {
	// first clear
	for i := 0; i < len((*vlist)); i++ {
		(*vlist)[i].Indegree = 0
	}
	// then set
	for i := 0; i < len(*vlist); i++ {
		if len((*vlist)[i].Next_indexs_list) != 0 {
			// visit every elem whose out table is not empty
			for _, index := range (*vlist)[i].Next_indexs_list {
				var real_index int
				for (*vlist)[real_index].Current_index != index && real_index < len(*vlist) {
					real_index++
				}
				(*vlist)[real_index].Indegree++
			}
		}
	}
	// I would rather use this func rather to maintain out-degree table
}

func ExamCurrent(vlist []Vertix) {
	fmt.Println("examing...")
	for _, v := range vlist {
		fmt.Println(v)
	}
	fmt.Println("exam ended.")
}

func Topo(aovGraph []Vertix) {
	graphCopy := make([]Vertix, 0)
	for _, v := range aovGraph {
		graphCopy = append(graphCopy, v)
	}
	step_count := 0
	for step_count < 10 {
		invalid_flag := true
		step_count++
		fmt.Println("step", step_count, "are as follow:")
		SetIndegree(&graphCopy) // to sum the indegree of every vertix
		tmp := make([]Vertix, 0)
		for i := 0; i < len(graphCopy); i++ {
			if graphCopy[i].Indegree == 0 {
				fmt.Println(graphCopy[i])
				invalid_flag = false
			} else {
				tmp = append(tmp, graphCopy[i])
			}
		}
		graphCopy = make([]Vertix, 0)
		for _, v := range tmp {
			graphCopy = append(graphCopy, v)
		}
		if invalid_flag {
			panic("has circles.")
		}
		if len(graphCopy) == 0 {
			break
		}
	}
}

// ;;;;;;;;;;;;;;;;;;;;;;;;;;;;
// Author: redh3t
// TimeStamp: 2022/12/3 23:56
// 电脑重装了，现在电脑上没有gcc了
// 就拿自己服务器上的golang写了
// 过程还行，调小bug调了好一会
// ;;;;;;;;;;;;;;;;;;;;;;;;;;;
