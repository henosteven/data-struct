package main

import (
    "fmt"
)

type Node struct {
    value int
    next *Node
    down *Node
}

type SkipList struct {
    topNode *Node
}

func main() {
    var numList = []int{1, 2, 3, 4, 5, 6, 7, 8, 9}    
    var topNode *Node = &Node{1, nil, nil}
    
    curNode := topNode
    for _, num := range(numList) {
        newNode := &Node{num, nil, nil}
        curNode.next = newNode
        curNode = newNode
    }

    reNode := topNode
    for {
        fmt.Println(reNode.value)
        if reNode.next == nil {
            break;
        }
        reNode = reNode.next
    }

    fmt.Println("========")

    /* 构建第二层 */
    var newTopNode *Node = &Node{1, nil, nil}
    newTopNode.down = topNode

    re2Node := topNode
    cur2Node := newTopNode
    for {
        if re2Node.value % 4 == 0 {
            cNewNode := &Node{re2Node.value, nil, nil}
            cNewNode.down = re2Node
            cur2Node.next = cNewNode
            cur2Node = cNewNode
        }
        if re2Node.next == nil {
            break;
        }
        re2Node = re2Node.next
    }


    re5Node := newTopNode
    for {
        fmt.Println(re5Node.value)
            if re5Node.next == nil {
                break;
            }
        re5Node = re5Node.next
    }

   fmt.Println("===========")

   /* 试试搜索 */
   cur3Node := newTopNode
   pre3Node := newTopNode

   i := 0;
   for {
        i = i + 1
        
        if cur3Node == nil {
            fmt.Println("not found");
            break
        }

        if cur3Node.value == 9 {
            fmt.Println("found the value ", i)
            break;
        }

        if cur3Node.value < 9 {
            fmt.Println("meet")
            if cur3Node.next == nil {
                pre3Node = cur3Node.down
                cur3Node = cur3Node.down.next
            } else {
                pre3Node = cur3Node
                cur3Node = cur3Node.next
            }
        } else {
            cur3Node = pre3Node.down
            pre3Node = cur3Node
        }
   } 
}
