//
//  main.cpp
//  124_Programming_1
//
//  Created by Avinash Saraf on 2/17/16.
//  Copyright © 2016 Avinash Saraf. All rights reserved.
//

#include <iostream>
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <cstdlib>
#include <tuple>


struct Adjacency_List_Node
{
    int end;
    struct Adjacency_List_Node* next;
};

struct Adjacency_List
{
    struct Adjacency_List_Node *head;
};

class graph
{
    private:
        int v;
        struct Adjacency_List* list;
    public:
        graph(int v)
        {
            this->v = v; 
            list = new std::tuple <Adjacency_List, float> (Adjacency_List[v], -1);
            for (int i = 0;i < v;++i){
                list[i].head = NULL;
            }
        }
    
        // new node
        Adjacency_List_Node* new_node(int end) {
            Adjacency_List_Node* newnode = new Adjacency_List_Node;
            newnode -> end = end;
            newnode -> next = NULL;
            return newnode;
        }
    
        void new_edge (int start, int end) {
            float x = (rand() / float(RAND_MAX));
            Adjacency_List_Node* newnode = new_node(end);
            newnode->next = list[start].head;
            list[start].head = std::tuple <Adjacency_List_Node, float>  (newnode, x);
            newnode = new_node(start);
            newnode->next = list[end].head;
            list[end].head = newnode;
        }
    
    /*
     * Print the graph
     */
    void printGraph()
    {
        int k;
        for (k = 0; k < v; ++k)
        {
            Adjacency_List_Node* pCrawl = list[k].head;
            std::cout<<"\n Adjacency list of vertex "<<k<<"\n head ";
            while (pCrawl)
            {
                std::cout<<"-> "<<pCrawl->end;
                pCrawl = pCrawl->next;
            }
            std::cout<<std::endl;
        }
    }
    
};

int main()
    {
        srand(time_t(NULL));

        graph gh(5);
        gh.new_edge(1, 2);
        gh.new_edge(1, 3);
        gh.new_edge(1, 4);
        gh.new_edge(2, 3);
        gh.new_edge(3, 4);
        gh.new_edge(0, 1);
        gh.new_edge(0, 4);
        
        // print the adjacency list representation of the above graph
        gh.printGraph();
        
        return 0;
    }

//int[][] gen_graph

// graphs function (takes n, dimension) {
    // dimension = 0:
        // adjacency list: all edge weights are random
    // dimension = 2:
        // adjacency list: edge weight = sqrt(rand_1^2+rand_2^2)
    // dimension = 3:
        // edge weight = cube root(rand_1^2+rand_2^2+rand_3^2)
    // dimension = 3:
        // edge weight = quad root(rand_1^2+rand_2^2+rand_3^2+rand_4^2)

    // create and return adjacency list





//std::cout << "Hello, World!\n";
//float x,y;
//
//x = (rand() / float(RAND_MAX));
//y = (rand() / float(RAND_MAX));
;