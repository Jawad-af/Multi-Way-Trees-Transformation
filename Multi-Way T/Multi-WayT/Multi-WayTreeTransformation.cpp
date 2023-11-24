#include <stdio.h>
#include <stdlib.h>

#define MAX_NUM_NODES 10
#define NUM_CHILDREN 5

typedef struct Node {
    int value;
    int children[NUM_CHILDREN];
}treeNode;

treeNode* treeRep[MAX_NUM_NODES];

treeNode* newNode(int value) {
    treeNode* n = (treeNode*)malloc(sizeof(treeNode));
    n->value = 0;
    int i = 1;
    while (i < NUM_CHILDREN) {
        n->children[i] = 0;
        i++;
    }
    return n;
}

treeNode* TransformationPR_MWT(int array[], int size) {
    int i = 1;
    while (i < size) {
        treeRep[i] = newNode(i);
        i++;
    }
    treeNode* root = NULL;
    i = 1;
    while (i < size) {
        if (array[i] == -1) {
            treeRep[i]->value = i;
            root = treeRep[i];
        }
        else {
            if (treeRep[array[i]]->value == 0) {
                treeRep[array[i]]->value = array[i];
                treeRep[array[i]]->children[1] = i;
            }
            else {
                int j = 2;
                while (treeRep[array[i]]->children[j] != 0)
                    j++;
                treeRep[array[i]]->children[j] = i;
            }
        }
        i++;
    }

    return root;
}

typedef struct MWtreeRep {
    int value;
    MWtreeRep* child;
    MWtreeRep* sibling;
}MWtreeRep;

MWtreeRep* treeRep3;

MWtreeRep* TransformationMWT_BI(int index) {
    if (index == 0) return NULL;

    MWtreeRep* current = (MWtreeRep*)malloc(sizeof(MWtreeRep));
    current->value = treeRep[index]->value;
    current->child = NULL;
    current->sibling = NULL;

    MWtreeRep* previous = NULL;
    int i = 1;
    while (i < MAX_NUM_NODES && treeRep[index]->children[i] != 0) {
        int childIndex = treeRep[index]->children[i];
        MWtreeRep* newChild = TransformationMWT_BI(childIndex);
        if (i == 1) {
            current->child = newChild;
            current->child->value = treeRep[index]->children[i];
        }
        else
            previous->sibling = newChild;

        previous = newChild;
        previous->value = treeRep[index]->children[i];
        i++;
    }

    return current;
}

void prettyPrintR1(int array[], int size, int index, int level) {
    int i = 0;
    while (i < level) {
        printf("   ");
        i++;
    }
    printf("%d\n", index);
    i = 1;
    while (i < size) {
        if (array[i] == index)
            prettyPrintR1(array, size, i, level + 1);
        i++;
    }
}

void prettyPrintR2(treeNode* root, int level) {
    if (!root) return;
    if (root->value != 0) {
        int i = 0;
        while (i < level) {
            printf("    ");
            i++;
        }
        printf("%d\n", root->value);
    }

    int j = 1;
    while (j < MAX_NUM_NODES && root->children[j]) {
        prettyPrintR2(treeRep[root->children[j]], level + 1);
        j++;
    }

    if (level >= 0 && root->children[1] != 0) {
        int i = 1;
        while (i < MAX_NUM_NODES && root->children[i] != 0) {
            if (treeRep[root->children[i]]->value == 0) {
                int j = 0;
                while (j < level + 1) {
                    printf("   ");
                    j++;
                }
                printf("%d\n", root->children[i]);
            }
            i++;
        }
    }
}

void prettyPrintR3(MWtreeRep* root, int level) {
    if (!root) return;
    int i = 0;
    while (i < level) {
        printf("  ");
        i++;
    }
    printf("%d\n", root->value);
    prettyPrintR3(root->child, level + 1);
    prettyPrintR3(root->sibling, level);
}

int main() {
    int array[] = { 0, 2, 7, 5, 2, 7, 7, -1, 5, 2 };
    prettyPrintR1(array, MAX_NUM_NODES, 7, 0);
    printf("\n");

    printf("PR_MWT trans: \n\n");
    treeNode* root = TransformationPR_MWT(array, MAX_NUM_NODES);
    prettyPrintR2(root, 0);
    printf("\n");

    printf("MWT_BI trans: \n\n");
    MWtreeRep* rootR3 = TransformationMWT_BI(root->value);
    prettyPrintR3(rootR3, 0);

    return 0;
}
