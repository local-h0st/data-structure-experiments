package main

import (
	"fmt"
)

func main() {
	var heap Heap
	heap.init([]int{10, 16, 3, 14, 9, 7, 1, 8, 2, 4})
	heap.printHeap() // 输出原始序列
	heap.build()
	heap.printHeap() // 输出建堆完成后的序列
	heap.heapSort()
	heap.printHeap() // 输出堆排序后的序列，有序，单增
}

type Heap struct {
	arr []int
}

func (heap *Heap) sortOnce(num int) {
	// 表示前num个元素排成堆

}

func (heap Heap) getLeftKid(index int) (i, v int) {
	if 2*index > heap.arr[0] {
		return -1, -1
	} else {
		return 2 * index, heap.arr[2*index]
	}
}
func (heap Heap) getRightKid(index int) (i, v int) {
	if 2*index+1 > heap.arr[0] {
		return -1, -1
	} else {
		return 2*index + 1, heap.arr[2*index+1]
	}
}
func (heap *Heap) init(array []int) {
	// 堆从下标1开始，下表0存储堆的元素个数
	// 仍然是无序的
	heap.arr = make([]int, 0)
	heap.arr = append(heap.arr, len(array))
	for _, v := range array {
		heap.arr = append(heap.arr, v)
	}
}
func (heap Heap) printHeap() {
	fmt.Println("total elements :", heap.arr[0])
	fmt.Println(heap.arr[1:])
}
func (heap *Heap) maintain(index int) {
	//前提是该节点左右子树均是大顶堆
	for {
		value := heap.arr[index]
		l_index, l_value := heap.getLeftKid(index)
		r_index, r_value := heap.getRightKid(index)
		if l_index == -1 {
			// 左子树不存在，右子树一定也不存在，因此是叶子节点
			return
		} else if r_index == -1 {
			// 左子树存在，右子树不存在
			if value >= l_value {
				// 已经是大顶堆不需要维护
				return
			} else {
				// 交换
				heap.arr[index], heap.arr[l_index] = l_value, value
				index = l_index // 只有index是for外的变量
			}
		} else {
			// 均存在
			if value >= l_value && value >= r_value {
				// 已经是大顶堆不需要维护
				return
			} else if value < l_value && value < r_value {
				// 比两边都小
				if l_value > r_value {
					// l>r>crnt 和l换
					heap.arr[index], heap.arr[l_index] = l_value, value
					index = l_index
				} else {
					// 和r换
					heap.arr[index], heap.arr[r_index] = r_value, value
					index = r_index
				}
			} else if value < l_value && value >= r_value {
				// r<=vrnt<l 和l换
				heap.arr[index], heap.arr[l_index] = l_value, value
				index = l_index
			} else {
				// l<crnt<=r 和r换
				heap.arr[index], heap.arr[r_index] = r_value, value
				index = r_index
			}
		}
	}
}
func (heap *Heap) build() {
	for i := heap.arr[0]; i > 0; i-- {
		heap.maintain(i)
	}
}
func (heap *Heap) heapSort() {
	heap.build()
	total := heap.arr[0] // 循环中利用0号位置存储的有效元素个数来影响getLR函数的效果，实现排除掉最末尾已经排序好的数字的效果
	for pos := total; pos > 0; pos-- {
		heap.arr[pos], heap.arr[1] = heap.arr[1], heap.arr[pos]
		heap.arr[0]--
		heap.maintain(1)
	}
	heap.arr[0] = total
}
