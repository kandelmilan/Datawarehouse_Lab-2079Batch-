// WAP IN C TO IMPLEMENT BAYESIAN CLASSIFICATION (NAIVE BAYES)

#include <stdio.h>

#define MAX_SAMPLES 100
#define MAX_FEATURES 10
#define MAX_CLASSES 5
#define MAX_VALUES 5

// Global arrays
int data[MAX_SAMPLES][MAX_FEATURES];
int class_label[MAX_SAMPLES];

int class_count[MAX_CLASSES];
int value_count[MAX_FEATURES][MAX_VALUES][MAX_CLASSES];

float prior[MAX_CLASSES];
float cond_prob[MAX_FEATURES][MAX_VALUES][MAX_CLASSES];

// -------- TRAIN FUNCTION --------
void train_naive_bayes(int total_samples, int total_features, int total_classes)
{
    int i, f, v, c;

    for (c = 0; c < total_classes; c++)
        class_count[c] = 0;

    for (f = 0; f < total_features; f++)
        for (v = 0; v < MAX_VALUES; v++)
            for (c = 0; c < total_classes; c++)
                value_count[f][v][c] = 0;

    // Count class occurrences
    for (i = 0; i < total_samples; i++)
    {
        c = class_label[i];
        class_count[c]++;
    }

    // Count feature occurrences
    for (i = 0; i < total_samples; i++)
    {
        c = class_label[i];
        for (f = 0; f < total_features; f++)
        {
            v = data[i][f];
            value_count[f][v][c]++;
        }
    }

    // Compute Prior
    for (c = 0; c < total_classes; c++)
        prior[c] = (float)class_count[c] / total_samples;

    // Compute Conditional Probabilities (Laplace Smoothing)
    for (f = 0; f < total_features; f++)
        for (v = 0; v < MAX_VALUES; v++)
            for (c = 0; c < total_classes; c++)
                cond_prob[f][v][c] =
                    (float)(value_count[f][v][c] + 1) /
                    (class_count[c] + MAX_VALUES);
}

// -------- PREDICT FUNCTION --------
int predict(int sample[], int total_features, int total_classes)
{
    float posterior[MAX_CLASSES];
    int c, f, v;

    // Compute posterior for each class
    for (c = 0; c < total_classes; c++)
    {
        posterior[c] = prior[c];

        for (f = 0; f < total_features; f++)
        {
            v = sample[f];
            posterior[c] *= cond_prob[f][v][c];
        }
    }

    // Find class with maximum posterior
    int max_class = 0;
    float max_value = posterior[0];

    for (c = 1; c < total_classes; c++)
    {
        if (posterior[c] > max_value)
        {
            max_value = posterior[c];
            max_class = c;
        }
    }

    return max_class;
}

// -------- MAIN FUNCTION --------
int main()
{
    int total_samples = 4;
    int total_features = 2;
    int total_classes = 2;

    data[0][0] = 0;
    data[0][1] = 0;
    class_label[0] = 0;
    data[1][0] = 0;
    data[1][1] = 1;
    class_label[1] = 1;
    data[2][0] = 1;
    data[2][1] = 0;
    class_label[2] = 1;
    data[3][0] = 1;
    data[3][1] = 1;
    class_label[3] = 1;

    train_naive_bayes(total_samples, total_features, total_classes);

    printf("Prior Probabilities:\n");
    for (int c = 0; c < total_classes; c++)
        printf("Class %d: %f\n", c, prior[c]);

    // Test Sample
    int sample[2] = {1, 0};
    int result = predict(sample, total_features, total_classes);

    printf("\nPredicted Class for sample {1,0}: %d\n", result);

    return 0;
}