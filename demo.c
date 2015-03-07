#include <common.h>
#include <stdio.h>
#include <stdlib.h>
#include "rbtree.h"
typedef struct{
    int data;
    struct rb_node rb;
}rand_node_t;

int node_cmp(rand_node_t *src,rand_node_t *dst)
{
    return dst->data - src->data;
}

void node_insert(rand_node_t *node,struct rb_root *root)
{
    struct rb_node **link = &root->rb_node; 
    struct rb_node *parent = NULL;
    rand_node_t *p;
    while(*link)
    {
        p = container_of(*link,rand_node_t,rb);
        parent = *link;
        if(node_cmp(p,node) > 0)
            link = &(*link)->rb_right;
        else
            link = &(*link)->rb_left;
    }
    rb_link_node(&node->rb,parent,link);
    rb_insert_color(&node->rb,root);
}

int main()
{
    struct rb_root root = RB_ROOT;
    struct rb_node *link = NULL;
    char ch;
    rand_node_t *node = NULL;
    while(1)
    {
        ch = getchar();
        switch(ch)
        {
            case 'a':
                node = (rand_node_t *)malloc(sizeof(rand_node_t)); 
                node->data = rand() % 100;
                node_insert(node,&root);
                break;
            case 'd':
                link = rb_first(&root);
                rb_erase(link,&root);
                break;
            case 'p':
                link = rb_first(&root);
                while(link)
                {
                    node = container_of(link,rand_node_t,rb);
                    printf("%d\n",node->data);
                    link = rb_next(link);
                }
                break;
            case 'q':
                return 0;
        }
    }
    return 0;
}
