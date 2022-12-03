package main

import "fmt"

const inf = 9999

func main() {
	graph := Graph{
		[]Vert{
			Vert{"vert 0", 0},
			Vert{"vert 1", 1},
			Vert{"vert 2", 2},
			Vert{"vert 3", 3},
			Vert{"vert 4", 4},
		},
		[]Edge{
			Edge{1, 0, 1},
			Edge{3, 0, 2},
			Edge{5, 0, 3},
			Edge{1, 1, 2},
			Edge{2, 1, 3},
			Edge{2, 2, 4},
			// new add
			Edge{1, 1, 4},
		},
	}
	Dij(graph, 0)
}

type Edge struct {
	Weight int
	From   int
	To     int
}

type Vert struct {
	Data  string
	Index int
}

type Graph struct {
	Vs []Vert
	Es []Edge
}

func (g *Graph) GetEdgesStartFromVert(index int) []Edge {
	result := make([]Edge, 0)
	for _, e := range g.Es {
		if e.From == index {
			result = append(result, e)
		}
	}
	return result
}

func MoveVert(index int, S *[]int, V *[]int) bool {
	for i, v := range *V {
		if v == index {
			*S = append(*S, index)
			*V = append((*V)[:i], (*V)[i+1:]...)
			return true
		}
	}
	return false
}

func HasElem(s []int, elem int) bool {
	for _, v := range s {
		if v == elem {
			return true
		}
	}
	return false
}

func FindShortest(info map[int]struct{ length, pre_index int }, V []int) (shortest_i, shortest_length int) {
	shortest_length = inf
	for i, v := range info {
		if v.length < shortest_length && HasElem(V, i) {
			shortest_length = v.length
			shortest_i = i
		}
	}
	return
}

func UpdateInfo(info *map[int]struct{ length, pre_index int }, index int, V []int, graph Graph) {
	edges := graph.GetEdgesStartFromVert(index)
	for _, e := range edges {
		if (*info)[index].length+e.Weight < (*info)[e.To].length {
			(*info)[e.To] = struct {
				length    int
				pre_index int
			}{
				(*info)[index].length + e.Weight,
				index,
			}
		}
	}
}

func Dij(graph Graph, origin int) {
	S := make([]int, 0)
	V := make([]int, 0)
	info := make(
		map[int]struct {
			length    int
			pre_index int
		},
		len(graph.Vs),
	) // info代表源到index的长度
	for _, v := range graph.Vs {
		V = append(V, v.Index)
	} // V准备完毕
	for _, v := range graph.Vs {
		info[v.Index] = struct {
			length    int
			pre_index int
		}{inf, -1}
	} // map初始化完成

	// 开始
	info[origin] = struct {
		length    int
		pre_index int
	}{0, -1}
	for len(S) < len(graph.Vs) {
		// fmt.Println("##########")
		// for i := 0; i < len(graph.Vs); i++ {
		// 	fmt.Println(i, info[i])
		// }
		// fmt.Println("#")
		next_index, _ := FindShortest(info, V)
		fmt.Println(next_index)
		MoveVert(next_index, &S, &V)
		UpdateInfo(&info, next_index, V, graph)
	}
	fmt.Println(info)
}

// ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
// Author: redh3t
// Timestamp: 2022/12/4 3:42
// 蛮离谱的，脑子写的时候比较混乱，
// 步骤分不开，后来查阅了资料
// 思路才清楚了
// 中间还有一次不小心死循环了
// 我服务器直接崩了，强制关机才恢复
// 困QaQ
// ;;;;;;;;;;;;;;;;;;;;;;;;;;;;
