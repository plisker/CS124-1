//
// CS 124
// Coding Assignment 1
// Avi Saraf & Paul Lisker
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <stdbool.h>
#include <limits.h>

typedef struct Node {
    int value;
    double weight;
} Node;

typedef struct priorityQ {
    Node* heap;
    int size;
} priorityQ;

typedef struct MSTree {
    int* prev;
    double* dist;
} MSTree;

double** allocateMatrix(int, int);
double randomZeroToOne();
void fillMatrixRandomly(double**, int, int);
void fillMatrixByDistance(double**, double**, int, int);
double distance(double**, int, int, int);
MSTree primsMST(double**, int, int);
void insert(Node, priorityQ*);
void rebuild(Node*, int, int);
Node popMin(priorityQ*);
void initialize(priorityQ*, int);

int main(int argc, const char * argv[]) {
    
    // Grab input
    int numpoints = atoi(argv[2]);
    int numtrials = atoi(argv[3]);
    int dimensions = atoi(argv[4]);
    srand((unsigned)time(NULL));
    double globalAverage = 0;
    
    for (int i = 0; i < numtrials; i++) {
        double** adjmatrix = allocateMatrix(numpoints, numpoints);
        
        if (dimensions == 0) {
            // Use this to fill adj matrix with random edge weights
            fillMatrixRandomly(adjmatrix, numpoints, numpoints);
        }
        else if (dimensions == 2 | dimensions == 3 | dimensions == 4) {
            
            // Create array for coordinates
            double** coordinates = allocateMatrix(numpoints, dimensions);
            
            // Fill array with random [0,1] coordinates
            fillMatrixRandomly(coordinates, numpoints, dimensions);
            
            // Fill adjmatrix with edge weights
            fillMatrixByDistance(adjmatrix, coordinates, numpoints, dimensions);
            
            free(coordinates);
            
        }
        
        // Might be worth adding some error checking earlier in the code so that dimension never gets here.
        else {
            printf("Ummm. You done messed up.\n");
        }
        
        
        // Call Prims MST Algorithm
        MSTree tree = primsMST(adjmatrix, rand()%numpoints, numpoints);
        
        double average = 0;
        
        for (int i = 0; i < numpoints; i++) {
            if(tree.prev[i] >= 0 ) {
                average += adjmatrix[i][tree.prev[i]];
            }
        }
        
        globalAverage += average;

        for (int i = 0; i < numpoints; i++){
            free(adjmatrix[i]);
        }
        free(adjmatrix);
        
    }
    
    // Calculate average of all trials
    globalAverage = (globalAverage / (float) numtrials);
    printf("%f %d %d %d\n", globalAverage, numpoints, numtrials, dimensions);
    return 0;
    
    
}

// Allocates memory for an X by Y matrix using double pointers
double** allocateMatrix(int X, int Y) {
    double** adjmatrix;
    adjmatrix = (double**) malloc(X*sizeof(double*));
    for (int i = 0; i < X; i++)
        adjmatrix[i] = (double*) malloc(Y*sizeof(double));
    return adjmatrix;
}

// Fills up a matrix with random weights [0,1]
void fillMatrixRandomly(double** adjmatrix, int numpoints, int dimensions) {
    for(int i=0; i< numpoints; i++)
    {
        for(int j=0; j< dimensions; j++)
        {
            adjmatrix[i][j] = randomZeroToOne();

        }
    }
}

// Fills up a matrix with distance between nodes
void fillMatrixByDistance(double** adjmatrix, double** coordinates, int numpoints, int dimensions) {
    double max_weight = 2*pow(numpoints, -(1/(double)dimensions));
    for(int i=0; i< numpoints; i++)
    {
        for(int j=(0+i); j< numpoints; j++)
        {
            double dist = distance(coordinates, dimensions, i, j);
            
            if (dist < max_weight) {
            adjmatrix[i][j] = dist;
            adjmatrix[j][i] = adjmatrix[i][j];
            }
            else {
                adjmatrix[i][j] = (double)1;
                adjmatrix[j][i] = (double)1;
            }
        }
        free(coordinates[i]);
    }
}


// Creates a random double [0,1]
double randomZeroToOne()
{
    return (double)rand() / (double)RAND_MAX ;
}

// Distance between coordinates
double distance(double** coordinates, int dimensions, int node1, int node2) {
    
    double sumOfSquares = 0.0;
    for(int i=0; i<dimensions; i++)
    {
        double difference = (coordinates[node1][i] - coordinates[node2][i]);
        sumOfSquares += difference * difference;
    }
    
    double distance = sqrt(sumOfSquares);
    return distance;
}


// Prim's Algorithm
MSTree primsMST(double** graph, int sNode, int numberOfNodes) {
    MSTree tree;
    
    int v,w;
    double dist[numberOfNodes];
    int prev[numberOfNodes];
    bool inMST[numberOfNodes];
    
    priorityQ H;
    initialize(&H, numberOfNodes);
    
    // Starting place
    for (int i = 0; i < numberOfNodes; i++) {
        dist[i] = INFINITY;
        prev[i] = -1;
        inMST[i] = false;
    }
    
    Node s;
    s.value=sNode;
    s.weight=0;
    
    
    dist[sNode] = 0;
    insert(s, &H);
    
    while (H.size != 0) {
        // Find min in heap
        Node popped = popMin(&H);
        v=popped.value;
        
        // Add to MST
        inMST[v] = true;
        
        // Add new nodes to heap
        for (w = 0; w < numberOfNodes; w++) {
            if ((!inMST[w]) && (graph[v][w] != 1) && (graph[v][w] < dist[w])) {
                dist[w] = graph[v][w];
                prev[w] = v;
                popped.value = w;
                popped.weight=dist[w];
                
                insert(popped, &H);
            }
        }
    }
    tree.prev=prev;
    tree.dist=dist;
    return tree;
}

// Initialize heap
void initialize(priorityQ *priorityq, int n) {
    priorityq->size = 0;
    priorityq->heap = (Node*)malloc(sizeof(Node)*(n*(n/4)));
}

// Insert new nodes into heap
void insert(Node node, priorityQ* heap) {
    
    // Update size
    int size = heap->size;
    ++heap->size;
    
    // Create new position
    int newNodePosition;
    Node tempNode;
    newNodePosition = size + 1;
    heap->heap[newNodePosition] = node;
    
    // Find valid position
    while (newNodePosition > 1 && heap->heap[newNodePosition].weight < heap->heap[(newNodePosition)/2].weight) {
        tempNode = heap->heap[newNodePosition];
        heap->heap[newNodePosition] = heap->heap[newNodePosition/2];
        heap->heap[newNodePosition/2] = tempNode;
        newNodePosition = (newNodePosition/2);
    }
}

// Heapify function
void rebuild(Node* heap, int size, int heapIndex) {
    int childIndex;
    Node tempNode;
    while (true) {
        childIndex = heapIndex*2;
        if (childIndex > size) {
            break;
        }
        else {
            // Determine which of the children is greater, for potential swapping
            if (heap[childIndex].weight > heap[childIndex+1].weight) {
                // Adjust index to higher child
                ++childIndex;
            }
        }
        // Swap if needed!
        if (heap[childIndex].weight < heap[heapIndex].weight) {
            tempNode = heap[childIndex];
            heap[childIndex] = heap[heapIndex];
            heap[heapIndex] = tempNode;
            heapIndex = childIndex;
        } else {
            break;
        }
    }
}

// Dequeue
Node popMin(priorityQ* heap) {
    Node minNode = heap->heap[1];
    int size = heap->size;
    
    // Swap head for last node and decrement size
    heap->heap[1] = heap->heap[size];
    --size;
    
    // rebuild the heap!
    rebuild(heap->heap, size, 1);
    
    --heap->size;
    return minNode;
}



