package main

import (
    "fmt"
)

type Node struct {
    value int
    next *Node
    down *Node
}

func insertNext(prenode *Node, value int) {
    node := &Node{value, nil, nil} 
    prenode.next = node
}

func main() {
    numList := []int{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}
    var head = Node{0, nil, nil}
    
    var curNode *Node
    curNode = &head
    for _, num := range(numList) {
        insertNext(curNode, num)
        curNode = curNode.next
    }
    
    curNode = &head
    for {
        if curNode.next != nil {
            fmt.Println(curNode.value)
            curNode = curNode.next
        } else {
            fmt.Println(curNode.value)
            break
        }
    }
}
