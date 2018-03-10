package main

import (
	"fmt"
	"strconv"
	"time"

	"github.com/prasannamahajan/practice-problems/hashtable/hashmap"
)

func insert(h *hashmap.HashMap, starting, elements int) {
	for i := starting; i <= starting+elements-1; i++ {
		//fmt.Printf("cap %d, total %d, inserting %d\n", h.capacity, h.totalNodes, i)
		fmt.Printf("Inserting %d\t", i)
		h.Put(i, strconv.Itoa(i))
		h.Stats()
	}
	h.Print()
}

func getall(h *hashmap.HashMap, starting, elements int) {
	for i := starting; i <= starting+elements-1; i++ {
		v := h.Get(i)
		fmt.Println("get", v)
	}
}

func deleteall(h *hashmap.HashMap, starting, elements int) {
	for i := starting + elements - 1; i >= starting; i-- {
		fmt.Printf("Deleting %d\t", i)
		h.Remove(i)
		h.Stats()
	}
}

func measure(fh func(*hashmap.HashMap, int, int), h *hashmap.HashMap, starting, elements int) {
	start := time.Now()
	fh(h, starting, elements)
	elapsed := time.Since(start)
	fmt.Println("time taken by", fh, "is", elapsed)
}

func help() {
	fmt.Println("Use following commands")
	fmt.Println("p|put <key> <value>")
	fmt.Println("g|get <key>")
	fmt.Println("r|remove <key>")
	fmt.Println("s|show")
	fmt.Println("stats")
}

func main() {
	h := new(hashmap.HashMap)
	h.Init()
	help()
	for {
		var key int
		var command, value string
		fmt.Scanf("%s", &command)
		switch command {
		case "p", "put":
			fmt.Scanf("%d%s", &key, &value)
			h.Put(key, value)
			fmt.Printf("Added [%d:%s]\n", key, value)
		case "r", "remove":
			fmt.Scanf("%d", &key)
			h.Remove(key)
			fmt.Printf("Removed [%d]\n", key)
		case "g", "get":
			fmt.Scanf("%d", &key)
			fmt.Printf("key=%d,value=%s\n", key, h.Get(key))
		case "s", "show":
			h.Print()
		case "stats":
			h.Stats()
		default:
			fmt.Println("Wrong input")
			help()
		}
	}
	/*
		v := 100
		measure(insert, h, 1, v)
		measure(getall, h, 1, v)
		measure(deleteall, h, 1, v)
		h.Print()
		h.Stats()
	*/
}
