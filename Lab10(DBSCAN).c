// WAP IN C TO IMPLEMENT DBSCAN ALGORITHM (2D POINTS)

#include <stdio.h>
#include <math.h>

#define MAX 100

// Structure for a point
typedef struct
{
    double x, y;
    int visited;
    int cluster;
} Point;

Point points[MAX];
int n;
double eps;
int MinPts;

// Function to calculate Euclidean Distance
double distance(Point a, Point b)
{
    return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
}

// Find neighbors of a point
int regionQuery(int index, int neighbors[])
{
    int count = 0;
    for (int i = 0; i < n; i++)
    {
        if (distance(points[index], points[i]) <= eps)
        {
            neighbors[count++] = i;
        }
    }
    return count;
}

// Expand cluster
void expandCluster(int index, int clusterId)
{
    int neighbors[MAX];
    int neighborCount = regionQuery(index, neighbors);

    points[index].cluster = clusterId;

    for (int i = 0; i < neighborCount; i++)
    {
        int neighborIndex = neighbors[i];

        if (!points[neighborIndex].visited)
        {
            points[neighborIndex].visited = 1;

            int newNeighbors[MAX];
            int newCount = regionQuery(neighborIndex, newNeighbors);

            if (newCount >= MinPts)
            {
                for (int j = 0; j < newCount; j++)
                {
                    neighbors[neighborCount++] = newNeighbors[j];
                }
            }
        }

        if (points[neighborIndex].cluster == 0)
        {
            points[neighborIndex].cluster = clusterId;
        }
    }
}

int main()
{
    int clusterId = 0;

    printf("Enter number of points: ");
    scanf("%d", &n);

    printf("Enter eps value: ");
    scanf("%lf", &eps);

    printf("Enter MinPts value: ");
    scanf("%d", &MinPts);

    printf("Enter x and y coordinates:\n");
    for (int i = 0; i < n; i++)
    {
        scanf("%lf %lf", &points[i].x, &points[i].y);
        points[i].visited = 0;
        points[i].cluster = 0;
    }

    for (int i = 0; i < n; i++)
    {
        if (!points[i].visited)
        {
            points[i].visited = 1;

            int neighbors[MAX];
            int neighborCount = regionQuery(i, neighbors);

            if (neighborCount < MinPts)
            {
                points[i].cluster = -1; // Noise
            }
            else
            {
                clusterId++;
                expandCluster(i, clusterId);
            }
        }
    }

    printf("\nDBSCAN Clustering Result:\n");
    for (int i = 0; i < n; i++)
    {
        if (points[i].cluster == -1)
            printf("Point (%.2lf, %.2lf) -> Noise\n", points[i].x, points[i].y);
        else
            printf("Point (%.2lf, %.2lf) -> Cluster %d\n",
                   points[i].x, points[i].y, points[i].cluster);
    }

    return 0;
}

// OBJECTIVES
// To understand density-based clustering.
// To implement DBSCAN algorithm.
// To identify clusters and noise points.
// To analyze effect of ε and MinPts.

// DBSCAN Algorithm
// HEORY

// DBSCAN (Density-Based Spatial Clustering of Applications with Noise)
//  is a density-based clustering algorithm used to group data points into clusters based on density.
// It forms clusters where points are closely packed together and marks points in low-density regions as noise (outliers).

// Key Concepts
//  Eps (ε) → Radius that defines neighborhood distance
//  MinPts → Minimum number of points required to form a dense region

// Types of Points
//  Core Point
//  A point having at least MinPts points within distance ε.
//  Border Point
//  A point that has fewer than MinPts neighbors but lies within ε of a core point.
//  Noise Point
//  A point that is neither core nor border.

// Working Principle
// DBSCAN starts with an arbitrary point.
// If it has enough neighbors → form a cluster.
// Expand cluster by checking density-connected neighbors.
// Points that do not belong to any cluster are labeled as noise.

// Advantages
//  Detects clusters of arbitrary shape
//  Handles noise automatically
//  No need to specify number of clusters

// Disadvantages
// Sensitive to ε and MinPts values
// Not ideal when densities vary significantly

// PSEUDO CODE
//  START
//  INPUT dataset
//  SET cluster_id = 0
//  FOR each point P in dataset
//      IF P is not visited
//          Mark P as visited
//          Find neighbors of P within distance ε
//          IF neighbors < MinPts
//              Mark P as Noise
//          ELSE
//              cluster_id = cluster_id + 1
//              Expand Cluster(P, neighbors, cluster_id)
//          END IF
//      END IF
//  END FOR
//  STOP
//  FUNCTION Expand Cluster(P, neighbors, cluster_id)
//      Assign P to cluster_id
//      FOR each neighbor N
//          IF N not visited
//              Mark N as visited
//              Find neighbors of N
//              IF neighbors >= MinPts
//                  Add new neighbors to neighbor list
//              END IF
//          END IF
//          IF N not yet member of any cluster
//              Assign N to cluster_id
//          END IF
//      END FOR
//  END FUNCTION

// OUTPUT
//  kandelmilan@kandels-MacBook-Air DatawareHouseandDataMining % ./dbscan
//  Enter number of points: 8
//  Enter eps value: 2
//  Enter MinPts value: 2
//  Enter x and y coordinates:
//  2 10
//  2 5
//  8 4
//  5 8
//  7 5
//  6 4
//  1 2
//  4 9

// DBSCAN Clustering Result:
// Point (2.00, 10.00) -> Noise
// Point (2.00, 5.00) -> Noise
// Point (8.00, 4.00) -> Cluster 1
// Point (5.00, 8.00) -> Cluster 2
// Point (7.00, 5.00) -> Cluster 1
// Point (6.00, 4.00) -> Cluster 1
// Point (1.00, 2.00) -> Noise
// Point (4.00, 9.00) -> Cluster 2