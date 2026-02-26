// WAP IN C TO IMPLEMENT ID3 ALGORITHM FOR DECISION TREE

// CODE IN PROGRESS - NOT COMPLETED 

#include <stdio.h>
#include <string.h>
#include <math.h>

#define MAX 100

// Function to calculate entropy
float entropy(int positive, int negative)
{
    float p = (float)positive / (positive + negative);
    float n = (float)negative / (positive + negative);
    float ent = 0.0;

    if (p > 0)
        ent -= p * log2(p);
    if (n > 0)
        ent -= n * log2(n);

    return ent;
}

int main()
{
    int n, i;
    int positive[MAX], negative[MAX];
    int totalPositive = 0, totalNegative = 0;

    printf("Enter number of training examples: ");
    scanf("%d", &n);

    printf("Enter number of positive and negative examples for each attribute:\n");
    for (i = 0; i < n; i++)
    {
        printf("Example %d - Positive: ", i);
        scanf("%d", &positive[i]);
        printf("Example %d - Negative: ", i);
        scanf("%d", &negative[i]);

        totalPositive += positive[i];
        totalNegative += negative[i];
    }

    float totalEntropy = entropy(totalPositive, totalNegative);
    printf("\nTotal Entropy of the dataset: %.4f\n", totalEntropy);

    // Further steps would include choosing attributes with max information gain
    // and recursively building the decision tree (not fully implemented here)
    printf("Decision tree building steps follow ID3 recursive method.\n");

    return 0;
}

// Objectives (Any Two)
// To understand the concept of the ID3 decision tree algorithm.
// To implement ID3 algorithm for building a decision tree using entropy and information gain.

// Theory (Short Paragraph)
/*
ID3 (Iterative Dichotomiser 3) is a decision tree algorithm used for classification tasks
in machine learning. It builds a tree by selecting the attribute that maximizes information
gain at each node. Information gain is calculated based on the entropy of the dataset, 
which measures the disorder or impurity. The algorithm recursively partitions the data 
based on attributes until all examples in a node belong to the same class or no attributes
are left. ID3 handles categorical attributes and forms a clear tree structure for decision-making.
*/

// Algorithm (ID3)
// Start
// Input training dataset
// Calculate entropy of the dataset
// For each attribute:
//      Calculate information gain
// Select attribute with maximum information gain as root
// Partition dataset based on selected attribute
// Recursively repeat steps for each partition until all nodes are pure or no attributes left
// Stop

// Pseudo Code
// BEGIN
// 1. Input dataset
// 2. Calculate entropy of target attribute
// 3. For each attribute
//      Calculate information gain
// 4. Select attribute with max gain as decision node
// 5. Partition dataset based on attribute values
// 6. Recursively build subtrees for each partition
// 7. Stop when all examples in node belong to same class
// END

// OUTPUT (Sample):
// Enter number of training examples: 3
// Enter number of positive and negative examples for each attribute:
// Example 0 - Positive: 3
// Example 0 - Negative: 2
// Example 1 - Positive: 2
// Example 1 - Negative: 2
// Example 2 - Positive: 3
// Example 2 - Negative: 1

// Total Entropy of the dataset: 0.9852
// Decision tree building steps follow ID3 recursive method.