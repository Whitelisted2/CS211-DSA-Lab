
//Application of Stacks: The Tower of Hanoi Problem
#include<stdio.h>
#include<stdlib.h>
int n = 0;                             // As instructed, maximum size of stack (total no. of disks) is 'n'
void push();                           // Declaration of functions that we shall define after the main() function
int pop();
void toh();

struct stack                           // For our purposes, we form a stack using structures, which consists of:
{
    char name;                         // a name, (which is required during file writing)
    int top;                           // a top, (which denotes topmost element of the stack-array) and
    int* StackArray;                   // (a pointer to) a corresponding array (which is the main part of the stack).
};
struct stack* newstack(char StackName)                               // a function to create and initialize a stack
{
    struct stack* newS = (struct stack*)malloc(sizeof(struct stack));// memory is allocated depending on the size of the structure stack
    newS->name = StackName;
    newS->top = -1;                                                  // top is initialized to -1 for empty stack
    newS->StackArray = (int*)malloc(n * sizeof(int));                // StackArray is also allocated depending on size required
    return newS;                                                     // new stack created is returned
}

int main(int argc, char* argv[])
{
    FILE* fp;                          // to empty the file, it is opened in write mode and closed
    fp = fopen("toh.txt","w");
    fclose(fp);

    if(argc>2)                         // argc contains argument count. Argument count should be 2 for execution to proceed in this case
    {                                  // the arguments are stored using pointer array *argv[]
        printf("too many arguments. enter exactly one number input (for number of disks).");
        exit(1);
    }
    else if(argc<2)
    {
        printf("too few arguments. enter exactly one number input (for number of disks).");
        exit(2);
    }
    n = atoi(argv[1]);                 // n is the total number of disks, which is the second argument of command-line input (argv[1])

    int i;                             // counting variable for later
    struct stack* A = newstack('A');   // creating stacka A, B, C, giving their names as arguments to the newstack() function
    struct stack* B = newstack('B');
    struct stack* C = newstack('C');

    for(i=n; i>0; i--)                 // initially, push disks into A in descending order
    {
        push(i, A);
    }

    toh(n, A, C, B);                   // star of the show, the toh() function

    return 0;
}

// Functions to check if stack is full or empty, which will be called in other functions:
int IsStackFull(struct stack* teststack)
{
    if(teststack->top == n-1)          // if top is n-1, stack is full
        return 1;
    else
        return 0;

}
int IsStackEmpty(struct stack* teststack)
{
    if(teststack->top == -1)           // if top is -1, stack is empty
        return 1;
    else
        return 0;
}

// push, pop, and peek functions:
void push(int ele, struct stack *Receiver)       // pushes ele into stack if stack has a vacancy (i.e. is not full)
{
    FILE* fp;
    fp = fopen("toh.txt","a");                   // file opened in append mode
    if(!IsStackFull(Receiver))                   // pushes if stack is not full
    {
        Receiver->top++;                         // increment top, assign ele to that new top
        Receiver->StackArray[Receiver->top] = ele;
        fprintf(fp, "Push disk %d to Stack %c\n", ele, Receiver->name);        // record the operation in the file toh.txt
    }
    else
    {
        printf("OVERFLOW CASE. STACK IS FULL!!");                              // message displayed if stack is full
    }
    fclose(fp);
}
int pop(struct stack *Donor)                     // pops top element, returns that value
{
    int PopEle = 0;                              // variable to store popped element
    FILE* fp;
    fp = fopen("toh.txt","a");                   // append mode
    if(!IsStackEmpty(Donor))                     // pops if stack is not empty
    {
        PopEle = Donor->StackArray[Donor->top];  // record top element
        Donor->top--;                            // decrement top
        fprintf(fp, "Pop disk %d from Stack %c\n", PopEle, Donor->name);       // record the operation in the file toh.txt
    }
    else
    {
        printf("UNDERFLOW CASE. STACK IS EMPTY!!");                            // message displayed if stack is empty
    }
    fclose(fp);
    return PopEle;                               // returns the popped element
}

//The central function of this entire program:
void toh(int n, struct stack* from_stack, struct stack* dest_stack, struct stack* aux_stack)
{
    if(n == 1)
    {
        push(pop(from_stack), dest_stack);                 // base case
    }
    else
    {
        toh(n-1, from_stack, aux_stack, dest_stack);       // recursion case
        push(pop(from_stack), dest_stack);
        toh(n-1, aux_stack, dest_stack, from_stack);
    }
}