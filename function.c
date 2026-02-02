#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <math.h>
#include <stdbool.h>
#include "Circuit_h"

//lookup table for circuit values for each input combination, have id as index
// typedef struct {
//     int lookup[10000];
// } Lookup;

// Lookup* createLookup() {
//     Lookup* inst = malloc(sizeof(Lookup));
//     for(int i = 0; i < sizeof inst; i++) {
//         inst->lookup[i] = -1;
//     }
// }

int* createCases(int numInputs) {
    //number of inputs
    int size = 1 << numInputs;
    //size array
    size*=numInputs;
    int* combinations = malloc(size*sizeof(int));
    for(int i = 0; i < size/numInputs; i++) {
        for(int j = 0; j < numInputs; j++) {
            combinations[i*numInputs + j] = i >> (numInputs-1-j) & 1;
        }
    }

   return combinations;
}



void createHeader(Node* nodes[], int numStanzas, int* numInputs) {
    int cnt = 0;
    for(int i = 0; i < numStanzas; i++) {
        if(!strcmp(nodes[i]->type, "INPUT")) {
            cnt+=1;
            printf("%d ", nodes[i]->uniqueID);
        }
    }
    *numInputs = cnt;
    printf("| ");
    for(int i = 0; i < numStanzas; i++) {
        if(!strcmp(nodes[i]->type, "OUTPUT")) {
            printf("%d ", nodes[i]->uniqueID);
        }
    }
}


//simulate each case
void simulate(char* content, Node* nodes[], int numStanzas) {
    int numInputs = 0;
    createHeader(nodes, numStanzas, &numInputs);

    int* combinations = createCases(numInputs);
    int numberCombos = 1 << numInputs;
    int combPtr = 0;
    // printf("\n| f1 |\n");
    for(int i = 0; i < numberCombos; i++) {
        //fill in inputs for every permuation
        int f = 0;
        while(combPtr < (i+1)*numInputs) {
            while(strcmp(nodes[f]->type, "INPUT")) {
                f+=1;
            }
            nodes[f]->val = combinations[combPtr];
            f+=1;
            combPtr+=1;
        }
        // printf("\n| f2 |\n");
        //loop through and fill in what you can
        bool someBlank = true;
        while(someBlank) {
            int cnt = 0;
            for(int j = 0; j < numStanzas; j++) {
                if(!strcmp(nodes[j]->type, "INPUT") || nodes[j]->val != -1) continue;
                bool cont = 0;
                for(int k = 0; k < nodes[j]->numInput; k++) {
                    if(nodes[nodes[j]->input[k]]->val == -1) {
                        cont = 1;
                        break;
                    }
                }
                if(cont) continue;
                cnt+=1;
                if(!strcmp(nodes[j]->type, "OUTPUT")) {
                    nodes[j]->val = nodes[nodes[j]->input[0]]->val;
                }
                else if(!strcmp(nodes[j]->type, "NOT")) {
                    nodes[j]->val = nodes[nodes[j]->input[0]]->val == 0 ? 1 : 0;
                }
                else if(!strcmp(nodes[j]->type, "OR")) {
                    bool hasOne = false;
                    for(int k = 0; k < nodes[j]->numInput; k++) {
                        if(nodes[nodes[j]->input[k]]->val == 1) {
                            hasOne = true;
                            break;
                        }
                    }
                    nodes[j]->val = hasOne ? 1 : 0;
                }
                else if(!strcmp(nodes[j]->type, "AND")) {
                    bool allOne = true;
                    for(int k = 0; k < nodes[j]->numInput; k++) {
                        if(nodes[nodes[j]->input[k]]->val == 0) {
                            allOne = false;
                            break;
                        }
                    }
                    nodes[j]->val = allOne ? 1 : 0;
                }
                else if(!strcmp(nodes[j]->type, "XOR")) {
                    int c = 0;
                    for(int k = 0; k < nodes[j]->numInput; k++) {
                        if(nodes[nodes[j]->input[k]]->val == 1) {
                            c++;
                        }
                    }
                    nodes[j]->val = c % 2 == 1 ? 1 : 0;
                }

                // printf("\n| %d |\n", cnt);
                // for(int i = 0; i < numStanzas; i++) {
                //     printNode(nodes[i]);
                // }
            }
            if(cnt == 0) someBlank = false;
        }
        //write out result each round to stdout
        printf("\n");
        for(int i = 0; i < numStanzas; i++) {
            if(!strcmp(nodes[i]->type, "INPUT")) {
                printf("%d ", nodes[i]->val);
            }
        } 
        printf("| ");
        for(int i = 0; i < numStanzas; i++) {
            if(!strcmp(nodes[i]->type, "OUTPUT")) {
                printf("%d ", nodes[i]->val);
            }
        }
        for(int i = 0; i < numStanzas; i++) {
            nodes[i]->val = -1;
        }
        
    }
    //write in all inputs int
}
