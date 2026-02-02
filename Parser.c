#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <stdbool.h>
#include "Circuit_h"


//when reading in store in lines that contain input and output and iterate over them twice, first identifying number of elements than reading in the elements
Node* createNode(char* type, int uniqueId, int numInput, int numOutput, char* inp, char* out) {
    Node* inst = malloc(sizeof(Node));
    inst->type = type;
    inst->uniqueID = uniqueId;
    inst->numInput = numInput;
    inst->numOutput = numOutput;
    inst->input = malloc(sizeof(int)*numInput);
    inst->output = malloc(sizeof(int)*numOutput);
    inst->val = -1;
    //sets comma seperated numbers to arrays
    for(int i = 0; i < numInput; i++) {
        if(*inp == ',') inp++;
        inst->input[i] = *inp++-'0';
    }
    for(int i = 0; i < numOutput; i++) {
        if(*out == ',') out++;
        inst->output[i] = *out++-'0';
    }
    
    return inst;
}

//call on { so you can find number stanzas
int numInstances(char* input, char c) {
    int ct = 0;
    while(*input) {
        if(*input == c) ct++;
        input++;
    }
    return ct;
}

//call on to find in how many characters new line
int lenVar(char* s) {
    int n = 0;
    while(*s++!='\n') n+=1;
    return n;
}

void printNode(Node* node) {
    printf("---------------------------------------------\n");
    printf("the type is %s\n", node->type);
    printf("the uniqueID is %d\n", node->uniqueID);
    // printf("the number of inputs this node takes is %d\n", node->numInput);
    // printf("the number of nodes this node outputs to is %d\n", node->numOutput);
    // printf("the inputs are: ");
    printf("[");
    for(int i = 0; i < node->numInput; i++) {
        printf("%d, ",node->input[i]);
    }
    printf("]\n");
    // printf("the outputs are: ");
    // printf("[");
    // for(int i = 0; i < node->numOutput; i++) {
    //     printf("%d, ",node->output[i]);
    // }
    // printf("]\n");
    printf("the current val is: %d\n", node->val);
    printf("---------------------------------------------");
}

int main(int argc, char* args[]) {
    char* fileName = args[1];
    FILE *fp = fopen(fileName, "r");
    //size of content in fp
    struct stat st;
    stat(fileName, &st);
    char* content = malloc(st.st_size+1);
    //read and verify all read
    int bytesRead = fread(content, 1, st.st_size, fp);
    if(bytesRead != st.st_size) {
        printf("Bad read");
        return 1;
    }
    content[bytesRead] = '\0';

    int numStanzas = numInstances(content, '{')-1;

    //initalize array to contain pointers to all node objects
    Node* nodes[numStanzas];
    

    // printf("number of stanzas is %d\n", numStanzas);
    //printf("the content is\n%s\n", content);
    char* set = content;
    for(int i = 0; i < numStanzas; i++) {
        //-------Type
        char* res = strstr(set,"Type=");
        res+=5;
        char* ptr = res;
        int lenV = lenVar(ptr);

        char* type = malloc(lenV+1);
        strncpy(type, res, lenV);
        type[lenV] = '\0';
        // printf("%s\n", type);

        //-------UniqueID
        res = strstr(set,"UniqueID=");
        res+=9;
        ptr = res;
        lenV = lenVar(ptr);

        char* ID = malloc(lenV+1);
        strncpy(ID, res, lenV);
        ID[lenV] = '\0';
        //
        int id = ID[0]-'0'; 
        // printf("%s\n", ID);

        //-------Input
        res = strstr(set,"Input=");
        res+=6;
        ptr = res;
        lenV = lenVar(ptr);

        char* inp = malloc(lenV+1);
        strncpy(inp, res, lenV);
        inp[lenV] = '\0';
        // printf("%s\n", inp);

        int numInput = numInstances(inp, ',');

        //-------Output
        res = strstr(set,"Output=");
        res+=7;
        ptr = res;
        lenV = lenVar(ptr);

        char* out = malloc(lenV+1);
        strncpy(out, res, lenV);
        out[lenV] = '\0';
        // printf("%s\n", out);
        set = res;

        int numOutput = numInstances(out, ',');
        
        //create Node and put it in Nodes array
        Node* n = createNode(type, id, numInput, numOutput, inp, out);
        nodes[i] = n;
    }

    for(int i = 0; i < numStanzas; i++) {
        //printNode(nodes[i]);
        //printf("-- %d | %d --",i, numStanzas);
    }
    simulate(content, nodes, numStanzas);

    // char* res = strstr(content,"UniqueID=");
    // res+=9;
    // char* ptr = res;

    // char* type = malloc(10);
    // strncpy(type, res, 9);
    // printf("%s", type);



    // char* res = strstr(content,"Input=");
    // res+=6;
    // char* ptr = res;

    // char* type = malloc(10);
    // strncpy(type, res, 9);
    // printf("%s", type);


    // char* res = strstr(content,"Output=");
    // res+=7;
    // char* ptr = res;

    // char* type = malloc(10);
    // strncpy(type, res, 9);
    // printf("%s", type);
    // return 0;
}
//strstr()

// strchr()

//strpbrk

