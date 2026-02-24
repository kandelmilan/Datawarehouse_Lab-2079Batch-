#include <stdio.h>
#include <stdlib.h>

#define MAX_ITEMS 10
#define MAX_TRANSACTIONS 10

int main() {

    /* 
    QUESTION:
    WAP IN C TO DESCRIBE THE WORKFLOW OF FP-GROWTH ALGORITHM.

    DESCRIPTION:
    1. DEFINITION:
       FP-Growth is an algorithm for mining frequent itemsets 
       without generating candidate itemsets explicitly.

    2. EXAMPLE:
       Input → Transaction database + Minimum Support
       Output → Frequent Itemsets

    3. CODE + OUTPUT FLOW
    4. DISCUSSION
    5. RESULT AND CONCLUSION


    ALGORITHM (Step-by-Step):
    1. Scan database and find frequency of each item (L1)
    2. Discard items not meeting minimum support
    3. Order items in descending frequency
    4. Build FP-tree:
       - Start with root
       - Insert each transaction in order
       - Increment counts for existing nodes
       - Create new nodes when needed
    5. Mine frequent patterns recursively


    PSEUDO-CODE:

    FP-Growth(D, min_sup)
    Begin
        L1 = find_frequent_1_itemsets(D, min_sup)
        sort L1 descending
        Build FP-tree
        Recursively mine frequent itemsets
    End
    */

    struct FPNode {
        int item;
        int count;
        struct FPNode* parent;
        struct FPNode* children[MAX_ITEMS];
        int childCount;
    };

    int T, I, min_sup;
    int D[MAX_TRANSACTIONS][MAX_ITEMS];

    printf("Enter number of transactions: ");
    scanf("%d",&T);

    printf("Enter number of items: ");
    scanf("%d",&I);

    printf("Enter minimum support count: ");
    scanf("%d",&min_sup);

    printf("\nEnter transaction data (0/1 for each item):\n");
    for(int i=0;i<T;i++)
        for(int j=0;j<I;j++)
            scanf("%d",&D[i][j]);

    // Create root node
    struct FPNode* root = (struct FPNode*) malloc(sizeof(struct FPNode));
    root->item = -1;
    root->count = 0;
    root->parent = NULL;
    root->childCount = 0;
    for(int i=0;i<MAX_ITEMS;i++)
        root->children[i] = NULL;

    // Insert transactions into FP-tree
    for(int t=0;t<T;t++){
        struct FPNode* current = root;
        for(int i=0;i<I;i++){
            if(D[t][i] == 1){
                int found = 0;

                // Check if child exists
                for(int j=0;j<current->childCount;j++){
                    if(current->children[j]->item == i){
                        current->children[j]->count++;
                        current = current->children[j];
                        found = 1;
                        break;
                    }
                }

                // Create new node if not found
                if(!found){
                    struct FPNode* newNode = 
                        (struct FPNode*) malloc(sizeof(struct FPNode));
                    newNode->item = i;
                    newNode->count = 1;
                    newNode->parent = current;
                    newNode->childCount = 0;
                    for(int k=0;k<MAX_ITEMS;k++)
                        newNode->children[k] = NULL;

                    current->children[current->childCount++] = newNode;
                    current = newNode;
                }
            }
        }
    }

    // Print FP-tree (Preorder Traversal using stack simulation)
    printf("\nFP-Tree Structure:\n");

    struct FPNode* stack[100];
    int depth[100];
    int top = -1;

    stack[++top] = root;
    depth[top] = 0;

    while(top >= 0){
        struct FPNode* node = stack[top];
        int d = depth[top];
        top--;

        if(node->item != -1)
            printf("%*sItem %d Count %d\n", d*2,"", node->item+1, node->count);

        for(int i=node->childCount-1;i>=0;i--){
            stack[++top] = node->children[i];
            depth[top] = d+1;
        }
    }

    return 0;
}