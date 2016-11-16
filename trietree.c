#include <stdio.h>
#include <stdlib.h>

typedef struct node_s node_t;

struct node_s{
    char flag; // 0 无单词到此结尾  1 有单词到此结尾
    char ch;
    int count; //有单词到此结尾次数
    node_t *parent;
    node_t *child;
    node_t *brother;
};

typedef struct {
    node_t *root;
    int wordcount;
} tree_t;

tree_t *createTrieTree() {
    tree_t *tree;
    tree = malloc(sizeof(tree_t));
    tree->wordcount = 0;

    node_t *root;
    root = malloc(sizeof(node_t));
    root->flag = 0;
    root->ch = -1;
    root->count = 0;
    root->parent = NULL;
    root->child = NULL;
    root->brother = NULL;

    tree->root = root;
    return tree;
}

void insert(node_t *node, char *word) {
    char ch;
    ch = *word;

    int wordEnd = 0;
    if (!*(word+1)) {
        wordEnd = 1;
    }

    if (node->child) {
        if (node->child->ch == ch) {
           if (wordEnd) {
               node->child->flag = 1;
               node->child->count ++;
           } else {
               insert(node->child, ++word); 
           }
        } else {
            node_t *curNode;
            int meet = 0;
            curNode = node->child->brother;
            while(curNode) {
                if (curNode->ch == ch) {
                    meet = 1; 
                    if (wordEnd) {
                        curNode->flag = 1;
                        curNode->count++;
                    } else {
                        insert(curNode, ++word);
                    }
                    break;
                } else {
                    if (curNode->brother) {
                        curNode = curNode->brother;
                    } else {
                        
                        node_t *newNode;
                        newNode = malloc(sizeof(node_t));
                        newNode->flag = 0;
                        newNode->count = 0;
                        newNode->child = NULL;
                        newNode->parent = node;
                        newNode->brother = NULL;
                        newNode->ch = ch;

                        curNode->brother = newNode;
                        
                        if (wordEnd) {
                            newNode->flag = 1;
                            newNode->count ++;
                        } else {
                            insert(newNode, ++word);
                        }
                    }
                }
            }
        } 
    } else {
       node_t *newNode;
       newNode = malloc(sizeof(node_t));
       newNode->flag = 0;
       newNode->count = 0;
       newNode->child = NULL;
       newNode->parent = node;
       newNode->ch = ch;
       newNode->brother = NULL;

       node->child = newNode;
       if (wordEnd) {
           newNode->count++;
           newNode->flag = 1;
       } else {
           insert(newNode, ++word);
       }
    }
}

void search(node_t *node, char *word) {

    if (node->ch == -1) {
        search(node->child, word);
    }

    int found = 0;
    char ch;
    ch = *word;

    int wordEnd = 0;
    if (!*(word+1)) {
        wordEnd = 1;
    }

    //自身找，没找到去兄弟找, 没有找到返回失败
    if (node->ch == ch) {
        if(wordEnd) {
            found = 1;
        } else {
            search(node->child, ++word);
        }    
    } else {
        node_t *curNode;
        curNode = node->brother;
        while(curNode) {
            if (curNode->ch == ch) {
                if (wordEnd) {
                    found = 1;
                } else {
                    search(curNode->child, ++word);       
                }
                break;
            } else {
                curNode = curNode->brother;
            }
        }
    }

    if (wordEnd) {
        if (found == 1) {
            printf("found the word\n");
        } else {
            printf("do not found the word\n");
        } 
    }
}

void countWord(node_t *node, char *word) {
    int count = 0;
    int ch;
    ch = *word;
    if (node->ch == -1) {
        countWord(node->child, word);
    }

    int wordEnd = 0;
    if (!*(word+1)) {
        wordEnd = 1;
    }

    if (node->ch == ch) {
        if (wordEnd) {
            count = node->count;
        } else {
            countWord(node->child, ++word);
        }
    } else {
        node_t *curNode;
        curNode = node->brother;
        while(curNode) {
            if (curNode->ch == ch) {
                if (wordEnd) {
                    count = curNode->count;
                } else {
                    countWord(curNode->child, ++word);       
                }
                break;
            } else {
                curNode = curNode->brother;
            }
        }
    }
    
    if (wordEnd) {
        printf("word count:%d\n", count);
    }
}

int main(int argc, char **argv) {
    tree_t *tree;
    tree = createTrieTree();
   
    char *wordlist[] = {
        "ph",
        "php",
        "php",
        "php",
        "php",
        "php",
        NULL
    };

    int i = 0;
    for (i = 0; wordlist[i]; i++) {
        insert(tree->root, wordlist[i]);
    }

    search(tree->root, "php");
    countWord(tree->root, "php");
}
