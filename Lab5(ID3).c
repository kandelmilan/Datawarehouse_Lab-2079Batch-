// WAP IN C TO IMPLEMENT ID3 ALGORITHM FOR DECISION TREE

#include <stdio.h>
#include <math.h>

#define MAX 10

// Function to calculate entropy
float entropy(int pos, int neg)
{
    float p, n, ent = 0.0;

    if (pos == 0 || neg == 0)
        return 0.0;

    p = (float)pos / (pos + neg);
    n = (float)neg / (pos + neg);

    ent = -p * log2(p) - n * log2(n);
    return ent;
}

int main()
{
    int attributes, i;
    int totalPos, totalNeg;

    printf("Enter total positive examples: ");
    scanf("%d", &totalPos);

    printf("Enter total negative examples: ");
    scanf("%d", &totalNeg);

    float totalEntropy = entropy(totalPos, totalNeg);
    printf("\nTotal Entropy = %.4f\n", totalEntropy);

    printf("\nEnter number of attributes: ");
    scanf("%d", &attributes);

    float bestGain = -1;
    int bestAttribute = -1;

    for (i = 0; i < attributes; i++)
    {
        int values, j;
        printf("\nEnter number of values for Attribute %d: ", i + 1);
        scanf("%d", &values);

        int pos[MAX], neg[MAX];
        float weightedEntropy = 0.0;

        for (j = 0; j < values; j++)
        {
            printf("Value %d - Positive examples: ", j + 1);
            scanf("%d", &pos[j]);

            printf("Value %d - Negative examples: ", j + 1);
            scanf("%d", &neg[j]);

            int subsetTotal = pos[j] + neg[j];
            float subsetEntropy = entropy(pos[j], neg[j]);

            weightedEntropy += ((float)subsetTotal /
                                (totalPos + totalNeg)) *
                               subsetEntropy;
        }

        float infoGain = totalEntropy - weightedEntropy;

        printf("Information Gain of Attribute %d = %.4f\n", i + 1, infoGain);

        if (infoGain > bestGain)
        {
            bestGain = infoGain;
            bestAttribute = i + 1;
        }
    }

    printf("\nBest Attribute (Root Node) = Attribute %d\n", bestAttribute);
    printf("Maximum Information Gain = %.4f\n", bestGain);

    printf("\nFurther recursive splitting follows the same ID3 process.\n");

    return 0;
}

/*
Objectives:
1. To understand the working principle of the ID3 decision tree algorithm.
2. To implement entropy and information gain calculations to select the best attribute.

Theory:
ID3 (Iterative Dichotomiser 3) is a supervised machine learning algorithm
used for classification problems. It constructs a decision tree by selecting
the attribute that provides the highest information gain at each step. The
core concept behind ID3 is entropy, which measures the impurity or disorder
in a dataset.

Information Gain is calculated by subtracting the weighted entropy of subsets
from the total entropy of the dataset. The attribute with the maximum
information gain is chosen as the root node. The dataset is then recursively
partitioned until all examples in a node belong to the same class or no
attributes remain.

Algorithm:
1. Start
2. Input total positive and negative examples
3. Calculate total entropy
4. For each attribute:
      a. Calculate entropy for each value
      b. Compute weighted entropy
      c. Calculate information gain
5. Select attribute with maximum information gain
6. Repeat recursively for subsets
7. Stop when node becomes pure
8. End

Pseudo Code:
BEGIN
    Input total positive and negative examples
    Compute total entropy

    FOR each attribute
        Input number of values
        FOR each value
            Input positive and negative examples
            Compute entropy of subset
            Compute weighted entropy
        END FOR
        Compute information gain
    END FOR

    Select attribute with maximum information gain
END
*/

// OUTPUT
/*
kandelmilan@192 DatawareHouseandDataMining % ./ID3
Enter total positive examples: 9
Enter total negative examples: 5

Total Entropy = 0.9403

Enter number of attributes: 2

Enter number of values for Attribute 1: 2
Value 1 - Positive examples: 6
Value 1 - Negative examples: 2
Value 2 - Positive examples: 3
Value 2 - Negative examples: 3
Information Gain of Attribute 1 = 0.0481

Enter number of values for Attribute 2: 2
Value 1 - Positive examples: 7
Value 1 - Negative examples: 1
Value 2 - Positive examples: 2
Value 2 - Negative examples: 4
Information Gain of Attribute 2 = 0.2361

Best Attribute (Root Node) = Attribute 2
Maximum Information Gain = 0.2361

Further recursive splitting follows the same ID3 process.

*/