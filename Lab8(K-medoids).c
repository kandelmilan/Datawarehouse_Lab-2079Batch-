// WAP IN C TO IMPLEMENT K-MEDOIDS (PAM) USING MANHATTAN DISTANCE

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX 100
#define FEATURES 2

// Manhattan Distance Function
float manhattan(float a[], float b[])
{
    float sum = 0;
    for (int i = 0; i < FEATURES; i++)
        sum += fabs(a[i] - b[i]);
    return sum;
}

int main()
{
    int n, k;
    float Data[MAX][FEATURES];
    int medoid[10];
    int cluster[MAX];

    printf("Enter number of data points: ");
    scanf("%d", &n);

    printf("Enter number of clusters: ");
    scanf("%d", &k);

    printf("Enter data points:\n");
    for (int i = 0; i < n; i++)
        for (int j = 0; j < FEATURES; j++)
            scanf("%f", &Data[i][j]);

    // Initialize first k points as medoids
    for (int i = 0; i < k; i++)
        medoid[i] = i;

    int changed;
    do
    {
        changed = 0;

        // Assign clusters
        for (int i = 0; i < n; i++)
        {
            float minDist = 9999;
            for (int j = 0; j < k; j++)
            {
                float d = manhattan(Data[i], Data[medoid[j]]);
                if (d < minDist)
                {
                    minDist = d;
                    cluster[i] = j;
                }
            }
        }

        // Try swapping medoids
        for (int i = 0; i < n; i++)
        {
            int isMedoid = 0;
            for (int m = 0; m < k; m++)
                if (medoid[m] == i)
                    isMedoid = 1;

            if (!isMedoid)
            {
                for (int m = 0; m < k; m++)
                {
                    int oldMedoid = medoid[m];
                    medoid[m] = i;

                    float totalCost = 0;
                    for (int p = 0; p < n; p++)
                    {
                        float minDist = 9999;
                        for (int q = 0; q < k; q++)
                        {
                            float d = manhattan(Data[p], Data[medoid[q]]);
                            if (d < minDist)
                                minDist = d;
                        }
                        totalCost += minDist;
                    }

                    // Compute old cost
                    medoid[m] = oldMedoid;
                    float oldCost = 0;
                    for (int p = 0; p < n; p++)
                    {
                        float minDist = 9999;
                        for (int q = 0; q < k; q++)
                        {
                            float d = manhattan(Data[p], Data[medoid[q]]);
                            if (d < minDist)
                                minDist = d;
                        }
                        oldCost += minDist;
                    }

                    if (totalCost < oldCost)
                    {
                        medoid[m] = i;
                        changed = 1;
                    }
                }
            }
        }

    } while (changed);

    printf("\nFinal Medoids:\n");
    for (int i = 0; i < k; i++)
    {
        printf("Medoid %d: (", i);
        for (int j = 0; j < FEATURES; j++)
            printf("%.2f ", Data[medoid[i]][j]);
        printf(")\n");
    }

    printf("\nCluster Assignment:\n");
    for (int i = 0; i < n; i++)
        printf("Point %d -> Cluster %d\n", i, cluster[i]);

    return 0;
}

// Objectives (Any Two)
// To implement K-Medoids clustering using Manhattan distance.
// To understand the difference between centroid-based and medoid-based clustering.

// Theory (Short Paragraph)

/*K-Medoids is a clustering algorithm similar to
 K-Means but instead of using the mean as the center,  it selects actual data points as cluster centers called medoids.
 It is more robust to noise and outliers.
  The algorithm works by minimizing the total Manhattan distance between points and their assigned medoid.
   The PAM (Partitioning Around Medoids) technique is commonly used for K-Medoids implementation.

// Manhattan Distance Formula:*/
// D=∣x1−x2∣+∣y1−y2∣

// Algorithm (K-Medoids – PAM)
// Start
// Input dataset
// Select first k points as medoids
// Assign each point to nearest medoid
// For each non-medoid point:
// Swap with medoid
// Compute total clustering cost
// Keep swap if cost reduces
// Repeat until no change
// Stop

// Pseudo Code
// BEGIN
// 1. Input Data[n][f]
// 2. Select first k points as medoids
// 3. Repeat
//        Assign each point to nearest medoid
//        For each non-medoid point
//             For each medoid
//                  Swap and compute total cost
//                  If cost reduces
//                       Update medoid
//             End For
//        End For
//    Until no change
// 4. Display final medoids and clusters
// END

//gcc k-medoidsAlg.c -o k-medoidsAlg 

// OUTPUT:
// kandelmilan@kandels-MacBook-Air DatawareHouseandDataMining % ./k-medoidsAlg 
// Enter number of data points: 10
// Enter number of clusters: 2
// Enter data points:
// 2 3
// 5 7
// 8 3
// 3 5 
// 7 2
// 6 8
// 1 4
// 4 6
// 9 5
// 3 4

// Final Medoids:
// Medoid 0: (3.00 5.00 )
// Medoid 1: (8.00 3.00 )

// Cluster Assignment:
// Point 0 -> Cluster 0
// Point 1 -> Cluster 0
// Point 2 -> Cluster 1
// Point 3 -> Cluster 0
// Point 4 -> Cluster 1
// Point 5 -> Cluster 0
// Point 6 -> Cluster 0
// Point 7 -> Cluster 0
// Point 8 -> Cluster 1
// Point 9 -> Cluster 0