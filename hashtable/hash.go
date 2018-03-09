package main

import (
	"fmt"
	"strconv"
	"time"
)

const (
	EMPTY             = -1
	INITIAL_SIZE      = 2
	MIN_LOAD_FACTOR   = 0.10
	MAX_LOAD_FACTOR   = 0.75
	MAX_NODES_IN_LIST = 5
)

type Node struct {
	key      int
	value    string
	nextNode *Node
}

type HashMap struct {
	buckets    *[]*Node
	size       int
	totalNodes int
	capacity   int
}

func (h *HashMap) Init() {
	h.size = INITIAL_SIZE
	v := make([]*Node, h.size)
	h.buckets = &v
	h.capacity = h.size * MAX_NODES_IN_LIST
}

func (h *HashMap) hash(key int) int {
	return key % h.size
}

func (h *HashMap) resize() {
	loadFactor := float64(h.totalNodes) / float64(h.capacity)
	if MIN_LOAD_FACTOR < loadFactor && loadFactor < MAX_LOAD_FACTOR {
		return
	}
	if loadFactor <= MIN_LOAD_FACTOR {
		if h.size == INITIAL_SIZE {
			return
		}
		fmt.Println("Min loadfactor reached", loadFactor)
		h.size /= 2
	} else {
		fmt.Println("Max loadfactor reached", loadFactor)
		h.size *= 2
	}
	v := make([]*Node, h.size)
	oldBuckets := h.buckets
	h.buckets = &v
	h.capacity = h.size * MAX_NODES_IN_LIST
	fmt.Printf("Changing size = %d, capacity = %d, nodes = %d\n", h.size, h.capacity, h.totalNodes)

	for _, bucket := range *oldBuckets {
		curr := bucket.nextNode
		for curr != nil {
			h.Put(curr.key, curr.value)
			curr = curr.nextNode
		}
	}
	h.totalNodes /= 2
}

func (h *HashMap) Put(key int, value string) {
	h.resize()
	node := &Node{
		key:   key,
		value: value,
	}
	index := h.hash(key)
	head := &(*h.buckets)[index]
	h.addToList(head, node)
	h.totalNodes += 1
}

func (h *HashMap) addToList(head **Node, node *Node) {
	if *head == nil {
		*head = node
		return
	}
	node.nextNode = *head
	*head = node
}

func (h *HashMap) removeFromList(head **Node, key int) bool {
	if *head == nil {
		return false
	}
	if (*head).key == key {
		*head = (*head).nextNode
		return true
	}
	prev := *head
	curr := (*head).nextNode
	for curr != nil {
		if curr.key == key {
			prev.nextNode = curr.nextNode
			return true
		}
		curr = curr.nextNode
	}
	return false
}

func (h *HashMap) Get(key int) string {
	index := h.hash(key)
	curr := (*h.buckets)[index]
	for curr != nil {
		if curr.key == key {
			return curr.value
		}
		curr = curr.nextNode
	}
	return ""
}

func (h *HashMap) Remove(key int) {
	h.resize()
	index := h.hash(key)
	head := &(*h.buckets)[index]
	if h.removeFromList(head, key) == true {
		h.totalNodes--
	}
}

func (h *HashMap) Print() {
	for i, bucket := range *h.buckets {
		fmt.Print(i, "[")
		curr := bucket
		for curr != nil {
			fmt.Print(curr.key, ":", curr.value, " ")
			curr = curr.nextNode
		}
		fmt.Println("]")
	}
}

func insert(h *HashMap, starting, elements int) {
	for i := starting; i <= starting+elements; i++ {
		//fmt.Printf("cap %d, total %d, inserting %d\n", h.capacity, h.totalNodes, i)
		h.Put(i, strconv.Itoa(i))
	}
}

func getall(h *HashMap, starting, elements int) {
	for i := starting; i <= starting+elements; i++ {
		h.Get(i)
		//fmt.Println("get", v)
	}
}

func deleteall(h *HashMap, starting, elements int) {
	for i := starting + elements; i >= starting; i-- {
		h.Remove(i)
	}
}

func measure(fh func(*HashMap, int, int), h *HashMap, starting, elements int) {
	start := time.Now()
	fh(h, starting, elements)
	elapsed := time.Since(start)
	fmt.Println("time taken by", fh, "is", elapsed)
}

func main() {
	h := new(HashMap)
	h.Init()
	h.Put(1, "prasanna")
	h.Put(9, "mahajan")
	h.Print()
	fmt.Println("key stored at 9 ==> ", h.Get(9))
	h.Remove(1)
	fmt.Println("After deleting key at 9")
	h.Print()
	h.Put(9, "mahajan")
	h.Remove(1)
	fmt.Println("After deleting key at 1")
	h.Print()
	//v := 20
	//measure(insert, h, 1, v)
	//measure(getall, h, 1, v)
	//measure(deleteall, h, 1, v)
	//h.Print()
}
