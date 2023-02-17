package main

import "fmt"

func main() {
	array := []int{4, 1, 6, 5, 7, 2, 3}
	printArr(array)
	//fmt.Println(QuickSort(0, 6, array))
	//fmt.Println(QuickSort(0, 2, array))
	doQuickSort(0, len(array)-1, array)
	printArr(array)
}

func QuickSort(start, end int, arr []int) int {
	var direction bool = true // true means right
	var elem int = arr[start]
	var crntPos int = start
	arr[start] = 0
	start++
	for start <= end {
		if direction == true {
			if arr[end] < elem {
				arr[crntPos] = arr[end]
				crntPos = end
				arr[crntPos] = 0
				end--
				direction = !direction
			} else {
				end--
			}
		} else {
			if arr[start] > elem {
				arr[crntPos] = arr[start]
				crntPos = start
				arr[crntPos] = 0
				start++
				direction = !direction
			} else {
				start++
			}
		}
	}
	arr[crntPos] = elem
	return crntPos
}

func printArr(arr []int) {
	fmt.Println("order of array :")
	for _, v := range arr {
		fmt.Print(v)
	}
	fmt.Println()
}

func doQuickSort(start, end int, arr []int) {
	i := QuickSort(start, end, arr)
	fmt.Println(i)
	if start <= i-1 {
		doQuickSort(start, i-1, arr)
	}
	if end >= i+1 {
		doQuickSort(i+1, end, arr)
	}

}

// 快排 fiki教我的方法
