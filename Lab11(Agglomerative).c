// WAP IN C TO IMPLEMENT AGGLOMERATIVE HIERARCHICAL CLUSTERING
// METHOD: SINGLE LINKAGE (Minimum Distance)

#include <stdio.h>
#include <math.h>

#define MAX 100

double data[MAX][2]; // Store 2D points
int cluster[MAX];    // Cluster id of each point
int n, k;

// Euclidean Distance
double distance(int i, int j)
{
    return sqrt(pow(data[i][0] - data[j][0], 2) +
                pow(data[i][1] - data[j][1], 2));
}

int main()
{
    printf("Enter number of points: ");
    scanf("%d", &n);

    printf("Enter desired number of clusters (k): ");
    scanf("%d", &k);

    printf("Enter x and y coordinates:\n");
    for (int i = 0; i < n; i++)
    {
        scanf("%lf %lf", &data[i][0], &data[i][1]);
        cluster[i] = i; // Initially each point is its own cluster
    }

    int currentClusters = n;

    while (currentClusters > k)
    {
        double minDist = 99999;
        int c1 = -1, c2 = -1;

        // Find closest pair of clusters
        for (int i = 0; i < n; i++)
        {
            for (int j = i + 1; j < n; j++)
            {
                if (cluster[i] != cluster[j])
                {
                    double dist = distance(i, j);
                    if (dist < minDist)
                    {
                        minDist = dist;
                        c1 = cluster[i];
                        c2 = cluster[j];
                    }
                }
            }
        }

        // Merge cluster c2 into c1
        for (int i = 0; i < n; i++)
        {
            if (cluster[i] == c2)
            {
                cluster[i] = c1;
            }
        }

        currentClusters--;
    }

    printf("\nAgglomerative Clustering Result:\n");
    for (int i = 0; i < n; i++)
    {
        printf("Point (%.2lf, %.2lf) -> Cluster %d\n",
               data[i][0], data[i][1], cluster[i]);
    }

    return 0;
}

// OBJECTIVES
// To implement the Agglomerative Hierarchical Clustering algorithm using a bottom-up merging approach.
// To group data points into a specified number of clusters based on minimum distance criteria.

// THEORY
// Agglomerative Hierarchical Clustering is a bottom-up clustering technique in which each data point initially
// starts as its own individual cluster. The algorithm repeatedly merges the
//  two closest clusters based on a chosen distance measure (such as Euclidean distance)
//   until a desired number of clusters is formed. This process creates a hierarchy of clusters,
//    which can be represented using a dendrogram.

// In this method, different linkage criteria can be used to measure the
//  distance between clusters, such as single linkage (minimum distance),
//  complete linkage (maximum distance), or average linkage. Agglomerative
//   clustering does not require initial cluster centers and is useful for identifying nested group
//    structures in data. However, it can be computationally expensive for large datasets.

// PSEUDO CODE
//  START
//  INPUT number of points n
//  INPUT desired number of clusters k
//  FOR each point i from 0 to n-1
//      INPUT x and y coordinates of point i
//      SET cluster[i] = i   // initially each point is its own cluster
//  END FOR
//  SET currentClusters = n
//  WHILE currentClusters > k
//      SET minDist = infinity
//      SET c1 = -1, c2 = -1
//      // Find the closest pair of clusters
//      FOR i = 0 to n-1
//          FOR j = i+1 to n-1
//              IF cluster[i] != cluster[j] THEN
//                  COMPUTE distance between point i and point j
//                  IF distance < minDist THEN
//                      minDist = distance
//                      c1 = cluster[i]
//                      c2 = cluster[j]
//                  END IF
//              END IF
//          END FOR
//      END FOR
//      // Merge cluster c2 into cluster c1
//      FOR i = 0 to n-1
//          IF cluster[i] == c2 THEN
//              cluster[i] = c1
//          END IF
//      END FOR
//      DECREMENT currentClusters by 1
//  END WHILE
//  // Print the clusters
//  FOR i = 0 to n-1
//      PRINT point[i] coordinates and cluster[i]
//  END FOR
//  STOP

// OUTPUT
//  kandelmilan@kandels-MacBook-Air DatawareHouseandDataMining % ./Agglomerative
//  Enter number of points: 6
//  Enter desired number of clusters (k): 2
//  Enter x and y coordinates:
//  1 1
//  1.5 1.5
//  5 5
//  3 4
//  4 4
//  3 3.5

// Agglomerative Clustering Result:
// Point (1.00, 1.00) -> Cluster 0
// Point (1.50, 1.50) -> Cluster 0
// Point (5.00, 5.00) -> Cluster 2
// Point (3.00, 4.00) -> Cluster 2
// Point (4.00, 4.00) -> Cluster 2
// Point (3.00, 3.50) -> Cluster 2