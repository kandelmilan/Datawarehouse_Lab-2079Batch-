// WAP IN C TO IMPLEMENT K-MEANS++ USING MANHATTAN DISTANCE

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

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
    float centroid[10][FEATURES];
    int cluster[MAX];
    float dist[MAX];

    srand(time(NULL));

    printf("Enter number of data points: ");
    scanf("%d", &n);

    printf("Enter number of clusters: ");
    scanf("%d", &k);

    printf("Enter data points:\n");
    for (int i = 0; i < n; i++)
        for (int j = 0; j < FEATURES; j++)
            scanf("%f", &Data[i][j]);

    // Step 1: Randomly select first centroid
    int first = rand() % n;
    for (int j = 0; j < FEATURES; j++)
        centroid[0][j] = Data[first][j];

    // Step 2: Select remaining centroids (K-Means++)
    for (int c = 1; c < k; c++)
    {
        float sum = 0;

        for (int i = 0; i < n; i++)
        {
            float minDist = 9999;

            for (int j = 0; j < c; j++)
            {
                float d = manhattan(Data[i], centroid[j]);
                if (d < minDist)
                    minDist = d;
            }

            dist[i] = minDist * minDist; // squared distance
            sum += dist[i];
        }

        float r = ((float)rand() / RAND_MAX) * sum;
        float cumulative = 0;

        for (int i = 0; i < n; i++)
        {
            cumulative += dist[i];
            if (cumulative >= r)
            {
                for (int j = 0; j < FEATURES; j++)
                    centroid[c][j] = Data[i][j];
                break;
            }
        }
    }

    // Standard K-Means iterations
    for (int iter = 0; iter < 5; iter++)
    {
        // Assign clusters
        for (int i = 0; i < n; i++)
        {
            float minDist = 9999;

            for (int j = 0; j < k; j++)
            {
                float d = manhattan(Data[i], centroid[j]);
                if (d < minDist)
                {
                    minDist = d;
                    cluster[i] = j;
                }
            }
        }

        // Update centroids
        for (int j = 0; j < k; j++)
        {
            float sum[FEATURES] = {0};
            int count = 0;

            for (int i = 0; i < n; i++)
            {
                if (cluster[i] == j)
                {
                    for (int f = 0; f < FEATURES; f++)
                        sum[f] += Data[i][f];
                    count++;
                }
            }

            if (count > 0)
                for (int f = 0; f < FEATURES; f++)
                    centroid[j][f] = sum[f] / count;
        }
    }

    printf("\nFinal Clusters:\n");
    for (int i = 0; i < n; i++)
    {
        printf("Point (");
        for (int j = 0; j < FEATURES; j++)
            printf("%.2f ", Data[i][j]);
        printf(") -> Cluster %d\n", cluster[i]);
    }

    return 0;
}

// Objectives (Any Two)
// To implement K-Means++ clustering using Manhattan distance.
// To understand centroid initialization improvement over standard K-Means.

// Theory (Short Paragraph)
/*K-Means++ improves the centroid initialization of traditional K-Means by selecting
initial centroids based on probability proportional to squared distance from existing centroids.
In this implementation, Manhattan distance is used instead of Euclidean distance.
Manhattan distance calculates the absolute difference between feature values,
making it suitable for grid-based and high-dimensional data.*/

// Manhattan Distance formula:
// D=∣x1−x2∣+∣y1−y2∣

// Algorithm
// Start
// Input n and k
// Input dataset into Data[n][features]
// Randomly select first centroid
// Select remaining centroids using probability method
// Assign points using Manhattan distance
// Recalculate centroids
// Repeat until convergence
// Stop

// pseudo Code
//  BEGIN
//  1. Input dataset Data[n][f]
//  2. Input number of clusters k
//  3. Randomly choose first centroid
//  4. For each remaining centroid
//         Compute Manhattan distance from nearest centroid
//         Select next centroid based on squared distance probability
//     End For
//  5. Repeat
//         Assign each point to nearest centroid
//         Update centroids by mean calculation
//     Until convergence
//  6. Display clusters
//  END

// output
// kandelmilan@kandels-MacBook-Air DatawareHouseandDataMining % ./K-means++Alg
// Enter number of data points: 8
// Enter number of clusters: 3
// Enter data points (x y):
// 2 10
// 2 5
// 8 4
// 5 8
// 7 5
// 6 4
// 3 2
// 4 6

// Final Clusters:
// Point (2.00, 10.00) -> Cluster 2
// Point (2.00, 5.00) -> Cluster 2
// Point (8.00, 4.00) -> Cluster 1
// Point (5.00, 8.00) -> Cluster 2
// Point (7.00, 5.00) -> Cluster 1
// Point (6.00, 4.00) -> Cluster 1
// Point (3.00, 2.00) -> Cluster 0
// Point (4.00, 6.00) -> Cluster 2