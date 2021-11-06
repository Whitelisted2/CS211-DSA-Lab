
//Program to implement Stack using Linked List implementation of Queue
#include<stdio.h>
#include<stdlib.h>

// Functions that are associated with linked list implementation of queue
int dequeue(); // i.e. delete_beg()
void enqueue(); // i.e. insert_end()

// Functions (operations on stacks) to be defined in terms of the above
void stack_peek();
void stack_pop();
void stack_push();
void stack_isEmpty();
void stack_isFull();
void traverse();
// [Note: In a stack, generally only top element can be read, traditionally we can't traverse through a stack without popping.]

// node structure and default parameter settings
struct node{
    int data;
    struct node *next;
};
struct node *head = NULL;
struct node *tail = NULL;

// global variable to record size of stack
int stackSize = 0;
int MAX = 10;        // to store max stack size
int deldata;

// function to create a new node
struct node* create(int num)
{
    struct node *newnode = (struct node*)malloc(sizeof(struct node));
    if(newnode == NULL)
    {
        printf("\nInsufficient memory space.");
        exit(1);
    }
    newnode->data = num;
    //printf("\nEnter Data:");
    //scanf("%d", &newnode->data);
    newnode->next = NULL;
    return newnode;
}

int main()
{
    int ch, n;
    printf("\nBefore you begin, enter an upper bound for size of Stack. (max size)");
    printf("\nThis is due to the nature of Stack as a data structure, it needs a MAX value. (default setting = 10)");
    printf("\n Enter a value:\t");
    scanf("%d", &MAX);
    while(1)
    {
        printf("\n\n_____________________________________________________________");
        printf("\nMenu for Stack (using Queue) with Linked List Implementation");
        printf("\n_____________________________________________________________");
        printf("\n 1. Peek (read the top element)");
        printf("\n 2. Pop (extract the top element)");
        printf("\n 3. Push (add a new element on top)");
        printf("\n 4. IsEmpty (check if stack is empty)");
        printf("\n 5. IsFull (check if stack is full)");
        printf("\n 6. View Stack (not traditionally an option)");
        printf("\n 7. Exit");
        printf("\n [Note: In a stack, usually only top element can be read; traditionally we can't traverse through a stack without popping.]");
        printf("\nEnter your choice:");
        scanf("%d", &ch);
        switch(ch)
        {
            case 1:
                stack_peek();
                break;
            case 2:
                stack_pop();
                break;
            case 3:
                stack_push();
                break;
            case 4:
                stack_isEmpty();
                break;
            case 5:
                stack_isFull();
                break;
            case 6:
                traverse();
                break;
            case 7:
                exit(0);
            default: 
                printf("\nInvalid input. try again.");
        }
    }
    return 0;
}

void enqueue(struct node* newnode)                   // basically, insert_end() for a singly linked list
{
    //struct node *newnode;
    //newnode = create();
    if(head == NULL)             // if queue is empty
    {
        head = newnode;
        tail = newnode;
    }
    else{
         tail-> next = newnode; // else, make tail point to new node, change tail
         tail = newnode;
    }
}

int dequeue()                   // basically, delete_beg() for a singly linked list
{
    if(head == NULL)             // if queue is empty (verification measure, though the stack handling will manage this)
    {
        printf("\nUnderflow case. Empty queue.");
        printf("\n this part of the function should ideally never be used in this program!");
        exit(1);
    }
    else{
        struct node *del;
        int deldata;
        del = head;              // set del to head, get its data into a variable, change head, then free del.
        deldata = del->data;
        head = head->next;
        free(del);
        return deldata;          // return the "dequeued" value.
    }
}

void stack_peek()
{
    // in this implementation, since we will have latest element stored at head (as you will see in stack_push()), it is the top.
    if(head == NULL)
    {
        printf("\nEmpty Stack. Nothing to peek at.");
    }
    else{
        // read data of top element (head) without popping it!
        printf("\nTop element is: %d", head->data);
    }
}

void stack_push()
{
    // to push an element, we will enqueue it into queue, then dequeue and enqueue all pre-existing nodes
    if(stackSize == MAX)                 // if stackSize has reached the max limit
    {
        printf("\nOVERFLOW CASE! STACK IS FULL! push is not possible at this moment.");
        return;
    }
    struct node *newnode, *temp;
    int num;
    printf("\nEnter Data:");
    scanf("%d", &num);
    newnode = create(num);
    enqueue(newnode);                     // enqueue newnode
    int i = 0;
    for(i = 0; i < stackSize; i++)
    {
        temp = create(dequeue());         // temporary node to store dequeued values
        enqueue(temp);                    // so they can be enqueued back into the queue.
    }
    stackSize++;
    printf("\n%d has been successfully pushed into the Stack.", num);
}

void stack_pop()
{
    // to pop an element, just show head value, change the head and free del.
    if(stackSize == 0)
    {
        printf("\nUNDERFLOW CASE! STACK IS EMPTY! pop is not possible at this moment.");
        return;
    }
    struct node *del;
    del = head;
    if(stackSize == 1)                // if stack has 1 element
    {
        printf("\n%d has been popped successfully", del->data);
        head = NULL;
        free(del);
        stackSize--;
        return;
    }
    head = head->next;               // shift head, display del->data, then free del
    printf("\n%d has been popped successfully", del->data);
    free(del);
    stackSize--;
}

void stack_isEmpty()
{
    if(stackSize == 0)
    {
        printf("\nStack is empty!!!");
    }
    else
    {
        printf("\nStack is not empty!");
    }
}

void stack_isFull()
{
    if(stackSize == MAX)
    {
        printf("\nStack is full!!!");
    }
    else
    {
        printf("\nStack is not full!");
    }
}

void traverse()
{
    if(stackSize == 0)
    {
        printf("\nThe stack is empty, nowhere to traverse!");
        return;
    }
    struct node *temp;
    temp = head;
    printf("\nElements of stack (top first): ");
    while(temp->next != NULL){
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("%d", temp->data); // to get the last element value as well
}