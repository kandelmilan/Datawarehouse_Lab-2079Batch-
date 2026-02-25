// WAP to implement K-Means Clustering using Euclidean Distance

#include <stdio.h>
#include <math.h>

#define MAX 100

int main()
{
    int n, k, i, j, cluster[MAX], iteration = 0;
    float x[MAX], y[MAX];
    float centroid_x[10], centroid_y[10];
    float old_centroid_x[10], old_centroid_y[10];
    float distance, min;

    printf("Enter number of data points: ");
    scanf("%d", &n);

    printf("Enter number of clusters: ");
    scanf("%d", &k);

    printf("Enter data points (x y):\n");
    for (i = 0; i < n; i++)
    {
        scanf("%f %f", &x[i], &y[i]);
    }

    // Initialize centroids (first k points)
    for (i = 0; i < k; i++)
    {
        centroid_x[i] = x[i];
        centroid_y[i] = y[i];
    }

    do
    {
        for (i = 0; i < k; i++)
        {
            old_centroid_x[i] = centroid_x[i];
            old_centroid_y[i] = centroid_y[i];
        }

        // Assign clusters
        for (i = 0; i < n; i++)
        {
            min = 9999;
            for (j = 0; j < k; j++)
            {
                distance = sqrt(pow(x[i] - centroid_x[j], 2) + pow(y[i] - centroid_y[j], 2));
                if (distance < min)
                {
                    min = distance;
                    cluster[i] = j;
                }
            }
        }

        // Recalculate centroids
        for (i = 0; i < k; i++)
        {
            float sum_x = 0, sum_y = 0;
            int count = 0;

            for (j = 0; j < n; j++)
            {
                if (cluster[j] == i)
                {
                    sum_x += x[j];
                    sum_y += y[j];
                    count++;
                }
            }

            if (count != 0)
            {
                centroid_x[i] = sum_x / count;
                centroid_y[i] = sum_y / count;
            }
        }

        iteration++;

    } while (iteration < 10);

    printf("\nFinal Clusters:\n");
    for (i = 0; i < n; i++)
    {
        printf("Point (%.2f, %.2f) -> Cluster %d\n", x[i], y[i], cluster[i]);
    }

    return 0;
}

// Objectives (Any Two)
// To understand the concept of unsupervised learning using K-Means clustering.
// To implement the K-Means algorithm using Euclidean distance formula.

//  Theory (Short Paragraph)
/*
K-Means is an unsupervised machine learning algorithm used to partition data into K clusters based on similarity.
 The algorithm works by selecting K initial centroids and assigning each data point to the nearest
centroid using Euclidean distance. After assignment, new centroids are calculated by taking the
mean of the clustered points. This process repeats until the centroids no longer change.
*/

// Algorithm (K-Means Using Euclidean Distance)
// Start
// Input number of data points (n)
// Input number of clusters (k)
// Initialize k centroids
// For each data point:
// Calculate Euclidean distance from each centroid
// Assign point to nearest centroid
// Recalculate centroids (mean of cluster points)
// Repeat steps 5–6 until centroids do not change
// Stop

// Pseudo Code
// BEGIN

// 1. Input n (number of data points)
// 2. Input k (number of clusters)
// 3. For i = 1 to n
//        Read data point (x[i], y[i])
//    End For
// 4. Initialize first k data points as centroids
//        centroid_x[j] = x[j]
//        centroid_y[j] = y[j]
// 5. Repeat until convergence (or fixed number of iterations)
//        a. For each data point i = 1 to n
//               Set min_distance = very large value
//               For each centroid j = 1 to k
//                      Compute Euclidean distance:
//                      distance = sqrt((x[i] - centroid_x[j])²
//                                      + (y[i] - centroid_y[j])²)
//                      If distance < min_distance
//                             min_distance = distance
//                             Assign cluster[i] = j
//                      End If
//               End For
//          End For
//        b. For each cluster j = 1 to k
//               Compute new centroid:
//               centroid_x[j] = mean of x values of points in cluster j
//               centroid_y[j] = mean of y values of points in cluster j
//          End For
// 6. Until centroids do not change
// 7. Display final clusters and centroids
// END

// OUTPUT
// kandelmilan@kandels-MacBook-Air DatawareHouseandDataMining % ./K-meansAlgorithm
// Enter number of data points: 7
// Enter number of clusters: 2
// Enter data points (x y):
// 20 500
// 40 1000
// 30 800
// 18 300
// 28 1200
// 35 1400
// 45 1800

// Final Clusters:
// Point (20.00, 500.00) -> Cluster 0
// Point (40.00, 1000.00) -> Cluster 1
// Point (30.00, 800.00) -> Cluster 0
// Point (18.00, 300.00) -> Cluster 0
// Point (28.00, 1200.00) -> Cluster 1
// Point (35.00, 1400.00) -> Cluster 1
// Point (45.00, 1800.00) -> Cluster 1