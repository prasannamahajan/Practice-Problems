package main

import (
	"fmt"
)

const (
	EMPTY        = -1
	INITIAL_SIZE = 8
)

type Node struct {
	key      int
	value    string
	nextNode *Node
}

type Bucket struct {
	nextNode *Node
}

type HashMap struct {
	buckets *[]Bucket
	size    int
}

func (h *HashMap) Init() {
	h.size = INITIAL_SIZE
	v := make([]Bucket, h.size)
	h.buckets = &v
}

func (h *HashMap) hash(key int) int {
	return key % h.size
}

func (h *HashMap) Put(key int, value string) {
	node := &Node{
		key:   key,
		value: value,
	}
	index := h.hash(key)
	if (*h.buckets)[index].nextNode == nil {
		(*h.buckets)[index].nextNode = node
		return
	}
	curr := (*h.buckets)[index].nextNode
	node.nextNode = curr
	(*h.buckets)[index].nextNode = node
}

func (h *HashMap) Get(key int) string {
	index := h.hash(key)
	curr := (*h.buckets)[index].nextNode
	for curr != nil {
		if curr.key == key {
			return curr.value
		}
	}
	return ""
}

func (h *HashMap) Remove(key int) {
	index := h.hash(key)
	curr := (*h.buckets)[index].nextNode
	if curr != nil {
		if curr.key == key {
			nextNode := curr.nextNode
			(*h.buckets)[index].nextNode = nextNode
			return
		}
	} else {
		return
	}
	prev := (*h.buckets)[index].nextNode
	curr = curr.nextNode
	for curr != nil {
		if curr.key == key {
			prev.nextNode = curr.nextNode
			return
		}
	}
}

func (h *HashMap) Print() {
	for i, bucket := range *h.buckets {
		fmt.Print(i, "[")
		curr := bucket.nextNode
		for curr != nil {
			fmt.Print(curr.key, ":", curr.value, " ")
			curr = curr.nextNode
		}
		fmt.Println("]")
	}
}

func main() {
	h := new(HashMap)
	h.Init()
	h.Put(1, "prasanna")
	h.Put(9, "mahajan")
	h.Print()
	fmt.Println("key stored at 9 ==> ", h.Get(9))
	h.Remove(9)
	fmt.Println("After deleting key at 9")
	h.Print()
	h.Put(9, "mahajan")
	h.Remove(1)
	fmt.Println("After deleting key at 1")
	h.Print()
}
