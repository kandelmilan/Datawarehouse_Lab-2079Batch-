// WAP IN C TO DESCRIBE THE WORKFLOW OF APRIORI ALGORITHM.
// DESCRIPTION:- 1.DEFINATION AND EXAMPLE 2.FLOWCHART +PSEUDOCODE
// CODE , O/P
// DISCUSSION
// RESULT AND CONCLUSION

// wap to achieve the apriori algorithm using below algorithm and pseudo code with proper output flow
// Step-by-Step Algorithm
//  Scan the database and find all frequent 1-itemsets → L1
//  Set k = 2
//  While L(k−1) is not empty:
//  Generate candidate itemsets Ck from L(k−1)
//  Scan database to count support of each candidate in Ck
//  Remove candidates with support < min_sup
//  Remaining itemsets form Lk
//  Increment k
//  Union all Lk to get the final frequent itemsets

// PSEUDO CODE
//  Apriori(D, min_sup)

// Input:
//     D → Transaction database
//     min_sup → Minimum support threshold

// Output:
//     L → Set of all frequent itemsets

// Begin
//     L1 = find_frequent_1_itemsets(D, min_sup)
//     k = 2

//     While L(k-1) ≠ ∅ do
//         Ck = apriori_gen(L(k-1))   // Generate candidate k-itemsets
//         For each transaction t in D do
//             For each candidate c in Ck do
//                 If c ⊆ t then
//                     count[c] = count[c] + 1
//         End For

//         Lk = { c ∈ Ck | count[c] ≥ min_sup }
//         k = k + 1
//     End While

//     Return L = ⋃ Lk
// End

// CANDIDATE GENERATION FUNCTION
// apriori_gen(L(k-1))

// Input:
//     L(k-1) → Frequent (k-1)-itemsets

// Output:
//     Ck → Candidate k-itemsets

// Begin
//     Ck = ∅
//     For each itemset l1 in L(k-1) do
//         For each itemset l2 in L(k-1) do
//             If first (k-2) items of l1 = first (k-2) items of l2 then
//                 c = l1 ∪ l2
//                 If all (k-1)-subsets of c are in L(k-1) then
//                     Add c to Ck
//     Return Ck
// End

// for (int i = prevStart; i < prevStart + prevCount; i++) {
//             for (int j = i + 1; j < prevStart + prevCount; j++) {

//                 int candidate[MAX_I];
//                 int valid = 1;

//                 for (int x = 0; x < k - 2; x++) {
//                     if (L[i][x] != L[j][x])
//                         valid = 0;
//                 }

//                 if (!valid) continue;

//                 for (int x = 0; x < k - 1; x++)
//                     candidate[x] = L[i][x];

//                 candidate[k - 1] = L[j][k - 2];

//                 int count = 0;

//                 for (int t = 0; t < T; t++) {
//                     if (isSubset(candidate, k, D[t]))
//                         count++;
//                 }

//                 printItemset(candidate,k);
//                 printf(" support=%d\n", count);

//                 if (count >= min_sup) {
//                     for (int x = 0; x < k; x++)
//                         newL[newCount][x] = candidate[x];
//                     newSize[newCount] = k;
//                     newCount++;
//                 }
//             }
//         }

//         if (newCount == 0)
//             break;

//         printf("\n=== L%d Frequent Itemsets ===\n", k);
//         for (int i = 0; i < newCount; i++) {
//             printItemset(newL[i],k);
//             printf("\n");
//         }

//         for (int i = 0; i < newCount; i++) {
//             for (int j = 0; j < k; j++)
//                 L[Lcount][j] = newL[i][j];
//             Lsize[Lcount] = k;
//             Lcount++;
//         }

//         prevStart = Lcount - newCount;
//         prevCount = newCount;
//         k++;
//     }

//     printf("\n=== Final Frequent Itemsets ===\n");
//     for (int i = 0; i < Lcount; i++) {
//         printItemset(L[i], Lsize[i]);
//         printf("\n");
//     }

//     return 0;
// }

// OUTPUT MUST BE LIKE :
// Enter number of transactions: 4
// Enter number of items: 3
// Enter minimum support count: 2

// Transaction data:
// 1 1 0
// 1 1 1
// 1 0 1
// 0 1 1


#include <stdio.h>

int main()
{

    int T, I, min_sup;
    int D[10][10];

    int L[50][10];  // stores all frequent itemsets
    int Lsize[50];  // size of each itemset
    int Lcount = 0; // total frequent itemsets

    printf("Enter number of transactions: ");
    scanf("%d", &T);

    printf("Enter number of items: ");
    scanf("%d", &I);

    printf("Enter minimum support count: ");
    scanf("%d", &min_sup);

    printf("\nEnter transaction data:\n");
    for (int i = 0; i < T; i++)
    {
        for (int j = 0; j < I; j++)
        {
            scanf("%d", &D[i][j]);
        }
    }

    /* --------- L1 Generation --------- */
    printf("\nL1 Frequent Itemsets:\n");

    for (int i = 0; i < I; i++)
    {
        int count = 0;

        for (int t = 0; t < T; t++)
        {
            if (D[t][i] == 1)
                count++;
        }

        if (count >= min_sup)
        {
            L[Lcount][0] = i;
            Lsize[Lcount] = 1;
            printf("{%d} support=%d\n", i + 1, count);
            Lcount++;
        }
    }

    int k = 2;
    int start = 0;
    int prevCount = Lcount;

    /* --------- L2 Generation --------- */
    if (prevCount > 1)
    {

        printf("\nL2 Frequent Itemsets:\n");

        for (int i = 0; i < prevCount; i++)
        {
            for (int j = i + 1; j < prevCount; j++)
            {

                int item1 = L[start + i][0];
                int item2 = L[start + j][0];
                int count = 0;

                for (int t = 0; t < T; t++)
                {
                    if (D[t][item1] == 1 && D[t][item2] == 1)
                        count++;
                }

                if (count >= min_sup)
                {
                    L[Lcount][0] = item1;
                    L[Lcount][1] = item2;
                    Lsize[Lcount] = 2;
                    printf("{%d %d} support=%d\n",
                           item1 + 1, item2 + 1, count);
                    Lcount++;
                }
            }
        }
    }

    /* --------- Final Output --------- */
    printf("\nFinal Frequent Itemsets:\n");
    for (int i = 0; i < Lcount; i++)
    {
        printf("{ ");
        for (int j = 0; j < Lsize[i]; j++)
            printf("%d ", L[i][j] + 1);
        printf("}\n");
    }

    return 0;
}
