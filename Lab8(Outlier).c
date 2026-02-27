#include <stdio.h>
#include <math.h>

int main()
{
    int n, i;
    float data[100], sum = 0, mean, std = 0;

    printf("Enter number of elements: ");
    scanf("%d", &n);

    printf("Enter the elements:\n");
    for (i = 0; i < n; i++)
    {
        scanf("%f", &data[i]);
        sum += data[i];
    }
    mean = sum / n;
    for (i = 0; i < n; i++)
    {
        std += pow(data[i] - mean, 2);
    }
    std = sqrt(std / n);

    printf("\nMean = %.2f\n", mean);
    printf("Standard Deviation = %.2f\n", std);

    printf("\nOutliers are:\n");
    for (i = 0; i < n; i++)
    {
        if (data[i] < mean - 2 * std || data[i] > mean + 2 * std)
        {
            printf("%.2f\n", data[i]);
        }
    }

    return 0;
}

// OUTPUT :
//  kandelmilan@kandels-MacBook-Air DatawareHouseandDataMining % ./outlier
//  Enter number of elements: 6
//  Enter the elements:
//  1 2 3 4 5 100

// Mean = 19.17
// Standard Deviation = 36.17

// Outliers are:
// 100.00

// OUTLIER DETECTION USING Z-SCORE METHOD

// PSEUDO CODE
//  START
//  INPUT number of data points n
//  IF n <= 1
//      PRINT "At least 2 data points required"
//      STOP
//  END IF
//  DECLARE array data[n]
//  SET sum = 0
//  FOR each data value
//      INPUT value
//      ADD value to sum
//  END FOR
//  COMPUTE mean = sum / n
//  SET sd = 0
//  FOR each data value
//      sd = sd + (value - mean)^2
//  END FOR
//  COMPUTE sd = sqrt(sd / (n - 1))
//  IF sd == 0
//      PRINT "No Outliers (All values same)"
//      STOP
//  END IF
//  SET found = FALSE
//  FOR each data value
//      COMPUTE z = (value - mean) / sd
//      IF |z| >= 3
//          PRINT value as Outlier
//          SET found = TRUE
//      END IF
//  END FOR
//  IF found == FALSE
//      PRINT "No Outliers Found"
//  END IF
//  STOP