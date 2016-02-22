//
// CS 125
// Coding Assignment 1
// Avi Saraf & Paul Lisker
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <stdbool.h>

double** allocateMatrix(int, int);
double randomZeroToOne();
void fillMatrixRandomly(double**, int, int);
void fillMatrixByDistance(double**, double**, int, int);
double distance(double**, int, int, int);
int* findMin(int*, bool*);
void primsMST(double**, int);

int main(int argc, const char * argv[]) {
    
    int numpoints = atoi(argv[2]);
    int numtrials = atoi(argv[3]);
    int dimensions = atoi(argv[4]);
    srand((unsigned)time(NULL));
    
    double** adjmatrix = allocateMatrix(numpoints, numpoints);
    
    if (dimensions == 0) {
        // Use this to fill adj matrix with random edge weights
        fillMatrixRandomly(adjmatrix, numpoints, numpoints);
    }
    else if (dimensions == 2| dimensions == 3 | dimensions ==4) {
        // Create array for coordinates
        double** coordinates = allocateMatrix(numpoints, dimensions);

        // Fill array with random [0,1] coordinates
        fillMatrixRandomly(coordinates, numpoints, dimensions);
        
        // Fill adjmatrix with edge weights
        fillMatrixByDistance(adjmatrix, coordinates, numpoints, dimensions);
        
        #warning Figure out if I free it here
        /*for (int i = 0; i < numpoints; i++){
            free(coordinates[i]);
        }*/
        free(coordinates);
        
        // Printing the coordinate matrix
        /*
        printf("Printing the coordinate matrix:\n");
        for(int i=0; i< numpoints; i++)
        {
            for(int j=0; j< dimensions; j++)
            {
                printf("[%f], at position[%d][%d]\n", coordinates[i][j], i, j);
            }
        }*/

    }
    
    // Might be worth adding some error checking earlier in the code so that dimension never gets here.
    else {
        printf("Ummmm. You done messed up.\n");
    }

    
    // Printing the adjmatrix
    /*
    printf("Printing the adj matrix:\n");
    for(int i=0; i< numpoints; i++)
    {
        for(int j=0; j< numpoints; j++)
        {
            printf("[%f], at position[%d][%d]\n", adjmatrix[i][j], i, j);
        }
    }
    */
    
    
    // Call Prims MST Algorithm -- Avi ADDED THIS LINE
    primsMST(adjmatrix, numpoints);
    
    
    
    #warning Figure out if I free it here
    for (int i = 0; i < numpoints; i++){
        free(adjmatrix[i]);
    }
    free(adjmatrix);
    
    printf("Success! Here are some stats:\n");
    printf("Number of nodes: %d\n", numpoints);
    printf("Trials: %d\n", numtrials);
    printf("Dimensions: %d\n", dimensions);
    

    return 0;
    
    
}

// Allocates memory for an X by Y matrix
// Inspiration... http://pleasemakeanote.blogspot.com/2008/06/2d-arrays-in-c-using-malloc.html
// We might have to change this or cite the webstie above
double** allocateMatrix(int X, int Y) {
    double** adjmatrix;
    adjmatrix = (double**) malloc(X*sizeof(double*));
    for (int i = 0; i < X; i++)
        adjmatrix[i] = (double*) malloc(Y*sizeof(double));
    return adjmatrix;
}

// Filling up a matrix with random weights [0,1]
void fillMatrixRandomly(double** adjmatrix, int numpoints, int dimensions) {
    for(int i=0; i< numpoints; i++)
    {
        for(int j=0; j< dimensions; j++)
        {
            adjmatrix[i][j] = randomZeroToOne();
            //printf("[%f] coordinate, at node [%d], axis [%d]\n", adjmatrix[i][j], i, j);

        }
        
        // This code can be removed later
        printf("Finished the coordinates of node %d\n", i);
        
    }
}

// Filling up a matrix with distance between nodes
void fillMatrixByDistance(double** adjmatrix, double** coordinates, int numpoints, int dimensions) {
    for(int i=0; i< numpoints; i++)
    {
        for(int j=(0+i); j< numpoints; j++)
        {
            double dist = distance(coordinates, dimensions, i, j);
            
            #warning k(n) function should go here instead of Magic Number
            if (dist < 0.2) {
            adjmatrix[i][j] = dist;
            adjmatrix[j][i] = adjmatrix[i][j];
            }
            //printf("[%f] edge weight, at position[%d][%d]\n", adjmatrix[i][j], i, j);
        }
        
        // This code can be removed later
        //if(i%100==0) {
        printf("Finished the edge weights of node %d\n", i);
        //}
        
        #warning Figure out if I free it here
        free(coordinates[i]);
    }
}


// creates a random double [0,1]; from http://stackoverflow.com/questions/6218399/how-to-generate-a-random-number-between-0-and-1
// WE MIGHT HAVE TO REDO THIS SO THAT IT'S OUR OWN CODE, or MAYBE CITE IT?
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

// Implement Prims (THIS IS WHERE AVI STARTED)


// Priority queue via heap
int* findMin(int verts[], bool inMST[]) {
    return &verts[0];
}

// Prim's Algorithm...
#warning Should it really be void? Shouldn't it return a pointer to the MST so that the average tree size be calculated?
void primsMST(double** adjmatrix, int n) {
    
    // This statement isn't printing.. so have I really called the function?
    printf("Started Prim's!\n");
    
    int parent[n];
    int key[n];
    bool inMST[n];
    
    for (int i = 0; i < n; i++) {
        key[i] = 2;
        inMST[i] = false;
    }
    
    key[0] = 0;
    parent[0] = -1;
    
    
    // I think something is going wrong in this loop with larger n... Maybe I'm not using pointers right?
    for (int k = 0; k < n-1; k++){
        int* minpath = findMin(key, inMST);
        
        inMST[*minpath] = true;
        
        for (int j = 0; j < n; j++) {
            // need to add removed edges condition by checking if edge exists
            if ((inMST[j] == false) & (adjmatrix[k][j] < key[j])) {
                parent[j] = k;
                key[j] = adjmatrix[k][j];
            }
        }
    }
    printf("Prim's algorithm has executed!\n");
               
}



typedef struct Node {
#warning More might be needed in this struct
    int value;
} Node;

typedef struct priorityQ {
    Node* minHeap;
    int size;
} priorityQ;


#warning Functions needed: InitializeHeap; Insert; Rebuild; removeMin; Enqueue (maybe within Insert); Dequeue (maybe within removeMin)

////////// COPIED FROM ELSEWHERE AS REFERENCE, DELETE DELETE DELETE
typedef struct heapData {
    //dummy
} heapData;

typedef struct heapNode {
    int value;
    heapData data;               //dummy
} heapNode;

typedef struct PQ {
    heapNode* heap;
    int size;
} PQ;

void insert(heapNode aNode, heapNode* heap, int size) {
    int idx;
    heapNode tmp;
    idx = size + 1;
    heap[idx] = aNode;
    while (heap[idx].value < heap[idx/2].value && idx > 1) {
        tmp = heap[idx];
        heap[idx] = heap[idx/2];
        heap[idx/2] = tmp;
        idx /= 2;
    }
}

void shiftdown(heapNode* heap, int size, int idx) {
    int cidx;        //index for child
    heapNode tmp;
    for (;;) {
        cidx = idx*2;
        if (cidx > size) {
            break;   //it has no child
        }
        if (cidx < size) {
            if (heap[cidx].value > heap[cidx+1].value) {
                ++cidx;
            }
        }
        //swap if necessary
        if (heap[cidx].value < heap[idx].value) {
            tmp = heap[cidx];
            heap[cidx] = heap[idx];
            heap[idx] = tmp;
            idx = cidx;
        } else {
            break;
        }
    }
}

heapNode removeMin(heapNode* heap, int size) {
    int cidx;
    heapNode rv = heap[1];
    //printf("%d:%d:%d\n", size, heap[1].value, heap[size].value);
    heap[1] = heap[size];
    --size;
    shiftdown(heap, size, 1);
    return rv;
}
void enqueue(heapNode node, PQ *q) {
    insert(node, q->heap, q->size);
    ++q->size;
}

heapNode dequeue(PQ *q) {
    heapNode rv = removeMin(q->heap, q->size);
    --q->size;
    return rv;
}

void initQueue(PQ *q, int n) {
    q->size = 0;
    q->heap = (heapNode*)malloc(sizeof(heapNode)*(n+1));
}

int mmain(int argc, char **argv) {
    int n;
    int i;
    PQ q;
    heapNode hn;
    n = atoi(argv[1]);
    initQueue(&q, n);
    srand(time(NULL));
    for (i = 0; i < n; ++i) {
        hn.value = rand()%10000;
        printf("enqueue node with value: %d\n", hn.value);
        enqueue(hn, &q);
    }
    printf("\ndequeue all values:\n");
    for (i = 0; i < n; ++i) {
        hn = dequeue(&q);
        printf("dequeued node with value: %d, queue size after removal: %d\n", hn.value, q.size);
    }
}








