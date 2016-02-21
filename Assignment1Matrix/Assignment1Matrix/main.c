//
// CS 125
// Coding Assignment 1
// Avi Saraf & Paul Lisker
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

double** allocateMatrix(int, int);
double randomZeroToOne();
void fillMatrixRandomly(double**, int, int);
void fillMatrixByDistance(double**, double**, int, int);
double distance(double**, int, int, int);

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
        
        
        
        // Printing the coordinate matrix
        
        printf("Printing the coordinate matrix:\n");
        for(int i=0; i< numpoints; i++)
        {
            for(int j=0; j< dimensions; j++)
            {
                printf("[%f], at position[%d][%d]\n", coordinates[i][j], i, j);
            }
        }

    }
    else {
        printf("Ummmm. You done messed up.\n");
    }

    
    // Printing the adjmatrix
    printf("Printing the adj matrix:\n");
    for(int i=0; i< numpoints; i++)
    {
        for(int j=0; j< numpoints; j++)
        {
            printf("[%f], at position[%d][%d]\n", adjmatrix[i][j], i, j);
        }
    }
    

    // insert code here...
    printf("numpoints: %d\n", numpoints);
    printf("numtrials: %d\n", numtrials);
    printf("dimension: %d\n", dimensions);
    return 0;
}

// Allocates memory for an X by Y matrix
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
        }
    }
}

// Filling up a matrix with distance between nodes
void fillMatrixByDistance(double** adjmatrix, double** coordinates, int numpoints, int dimensions) {
    for(int i=0; i< numpoints; i++)
    {
        for(int j=0; j< numpoints; j++)
        {
            adjmatrix[i][j] = distance(coordinates, dimensions, i, j);
        }
    }
}


// creates a random double [0,1]; from http://stackoverflow.com/questions/6218399/how-to-generate-a-random-number-between-0-and-1
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









