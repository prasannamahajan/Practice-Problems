package main

import (
	"fmt"
	"strconv"
	"time"

	"github.com/prasannamahajan/practice-problems/hashtable/hashmap"
)

func insert(h *hashmap.HashMap, starting, elements int) {
	for i := starting; i <= starting+elements; i++ {
		//fmt.Printf("cap %d, total %d, inserting %d\n", h.capacity, h.totalNodes, i)
		h.Stats()
		fmt.Printf("Inserting %d\t", i)
		h.Put(i, strconv.Itoa(i))
	}
}

func getall(h *hashmap.HashMap, starting, elements int) {
	for i := starting; i <= starting+elements; i++ {
		v := h.Get(i)
		fmt.Println("get", v)
	}
}

func deleteall(h *hashmap.HashMap, starting, elements int) {
	for i := starting + elements; i >= starting; i-- {
		h.Stats()
		fmt.Printf("Deleting %d\t", i)
		h.Remove(i)
	}
}

func measure(fh func(*hashmap.HashMap, int, int), h *hashmap.HashMap, starting, elements int) {
	start := time.Now()
	fh(h, starting, elements)
	elapsed := time.Since(start)
	fmt.Println("time taken by", fh, "is", elapsed)
}

func main() {
	h := new(hashmap.HashMap)
	h.Init()
	/*
		for {
			var k int
			var c, v string
			fmt.Scanf("%s", &c)
			if c == "a" {
				fmt.Scanf("%d%s", &k, &v)
				h.Put(k, v)
				h.Print()
			} else if c == "d" {
				fmt.Scanf("%d", &k)
				h.Remove(k)
			} else if c == "g" {
				fmt.Scanf("%d", &k)
				fmt.Println("pair", k, ":", h.Get(k))
			} else {
				h.Print()
			}
		}
	*/
	v := 99
	measure(insert, h, 1, v)
	/*
		measure(getall, h, 1, v)
	*/
	measure(deleteall, h, 1, v)
	h.Print()
}
