// WAP IN C TO IMPLEMENT SUPPORT VECTOR MACHINE (LINEAR SVM)

#include <stdio.h>

#define LEARNING_RATE 0.1
#define EPOCHS 100

int main()
{
    // Training Data (2 features, binary class: -1 and 1)
    float X[4][2] = {
        {2, 3},
        {1, 1},
        {-2, -1},
        {-3, -2}};

    int Y[4] = {1, 1, -1, -1};

    float w[2] = {0, 0};
    float b = 0;

    int i, j, epoch;

    // Training
    for (epoch = 0; epoch < EPOCHS; epoch++)
    {
        for (i = 0; i < 4; i++)
        {
            float linear_output = 0;

            for (j = 0; j < 2; j++)
                linear_output += w[j] * X[i][j];

            linear_output += b;

            if (Y[i] * linear_output < 1)
            {
                for (j = 0; j < 2; j++)
                    w[j] += LEARNING_RATE * Y[i] * X[i][j];

                b += LEARNING_RATE * Y[i];
            }
        }
    }

    // Testing Sample
    float test[2] = {3, 2};
    float result = w[0] * test[0] + w[1] * test[1] + b;

    if (result >= 0)
        printf("Predicted Class: 1\n");
    else
        printf("Predicted Class: -1\n");

    return 0;
}

// Objectives (Any Two)
// To understand the concept of supervised learning using Support Vector Machine.
// To implement Linear SVM using gradient-based weight update in C.

// Theory (Short Paragraph)
/*Support Vector Machine (SVM) is a supervised machine learning algorithm used
for classification and regression tasks. In linear SVM, the objective is to find the
optimal hyperplane that separates two classes with maximum margin.
The algorithm updates weights and bias using hinge loss when the classification condition is violated.
It works efficiently for linearly separable binary classification problems.
*/

// Algorithm (Linear SVM)
// Start
// Initialize weights (w) and bias (b) to 0
// For each epoch
// For each training sample
// Compute linear output: w.x + b
// If Y * (w.x + b) < 1
// Update weights
// Update bias
// Repeat for given epochs
// Test new sample
// Predict class based on sign of output
// Stop

// Pseudo code
// BEGIN
// 1. Initialize weight vector w = 0
// 2. Initialize bias b = 0
// 3. Set learning_rate and number_of_epochs
// 4. For epoch = 1 to number_of_epochs
//        For each training sample (Xi, Yi)
//            Compute linear_output = w.Xi + b
//            If Yi * linear_output < 1
//                 w = w + learning_rate * Yi * Xi
//                 b = b + learning_rate * Yi
//            End If
//        End For
//    End For
// 5. Input test sample
// 6. Compute result = w.test + b
// 7. If result >= 0
//        Predict class = 1
//    Else
//        Predict class = -1
// END