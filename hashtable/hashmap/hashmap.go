package hashmap

import (
	"fmt"
)

const (
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

	for _, listHead := range *oldBuckets {
		curr := listHead
		for curr != nil {
			h.addPair(curr.key, curr.value)
			curr = curr.nextNode
		}
	}
}

func (h *HashMap) Put(key int, value string) {
	h.resize()
	if h.addPair(key, value) == true {
		h.totalNodes++
	}
}

func (h *HashMap) addPair(key int, value string) bool {
	node := &Node{
		key:   key,
		value: value,
	}
	index := h.hash(key)
	head := &(*h.buckets)[index]
	return h.addToList(head, node)
}

func (h *HashMap) addToList(head **Node, node *Node) bool {
	if *head == nil {
		*head = node
		return true
	}
	curr := *head
	for {
		if curr.key == node.key {
			// Update the value if key already exist
			curr.value = node.value
			return false
		}
		if curr.nextNode == nil {
			break
		}
		curr = curr.nextNode
	}
	curr.nextNode = node
	return true
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
	index := h.hash(key)
	head := &(*h.buckets)[index]
	if h.removeFromList(head, key) == true {
		h.totalNodes--
		h.resize()
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

func (h *HashMap) Stats() {
	fmt.Printf("Size %d\t", h.size)
	fmt.Printf("Capacity %d\t", h.capacity)
	fmt.Printf("TotalNodes %d\t", h.totalNodes)
	loadFactor := float64(h.totalNodes) / float64(h.capacity)
	fmt.Printf("Loadfactor %.2f\n", loadFactor)
}
