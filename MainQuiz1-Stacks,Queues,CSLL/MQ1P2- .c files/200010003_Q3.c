
//Program to implement Queue using Linked List implementation of Stack
#include<stdio.h>
#include<stdlib.h>

// Functions that are associated with linked list implementation of stack
int pop(); // i.e. delete_beg()
void push(); // i.e. insert_beg()

// Functions (operations on stacks) to be defined in terms of the above
void queue_peek();
void queue_dequeue();
void queue_enqueue();
void queue_isEmpty();
void queue_isFull();
void traverse();
// [Note: In a queue, generally only head element can be read, traditionally we can't traverse through a queue without dequeueing.]

// node structure and default parameter settings
struct node{
    int data;
    struct node *next;
};
struct node *top1 = NULL; // we will use two stacks
struct node *top2 = NULL;

// global variable to record size of stack
int queueSize = 0;
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
    printf("\nBefore you begin, enter an upper bound for size of Queue. (max size)");
    printf("\nThis is due to the nature of Queue as a data structure, it needs a MAX value. (default setting = 10)");
    printf("\n Enter a value:\t");
    scanf("%d", &MAX);
    while(1)
    {
        printf("\n\n_____________________________________________________________");
        printf("\nMenu for Queue (using Stack) with Linked List Implementation");
        printf("\n_____________________________________________________________");
        printf("\n 1. Peek (read the head element)");
        printf("\n 2. Dequeue (extract the head element)");
        printf("\n 3. Enqueue (add a new element on tail end)");
        printf("\n 4. IsEmpty (check if queue is empty)");
        printf("\n 5. IsFull (check if queue is full)");
        printf("\n 6. View Queue (not traditionally an option)");
        printf("\n 7. Exit");
        printf("\n [Note: In a queue, generally only head element can be read, traditionally we can't traverse through a queue without dequeueing.]");
        printf("\nEnter your choice:");
        scanf("%d", &ch);
        switch(ch)
        {
            case 1:
                queue_peek();
                break;
            case 2:
                queue_dequeue();
                break;
            case 3:
                queue_enqueue();
                break;
            case 4:
                queue_isEmpty();
                break;
            case 5:
                queue_isFull();
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

void push(int num, struct node *newnode)
{
    if(num == 1)                  // we will take num = 1 to push into stack having top1
    {
        if(top1 == NULL)
        {
            top1 = newnode;
        }
        else{
            newnode->next = top1;
            top1 = newnode;
        }
    }
    else if(num == 2)             // we will take num = 2 to push into stack having top2
    {
        if(top2 == NULL)
        {
            top2 = newnode;
        }
        else{
            newnode->next = top2;
            top2 = newnode;
        }
    }
}

int pop(int num)
{
    if(num == 1)
    {
        if(top1 == NULL)
        {
            printf("\nUnderflow case. Empty stack.");
            printf("\n this part of the function should ideally never be used in this program!");
            exit(2);
        }
        else{
            struct node *del;
             int deldata;
             del = top1;              // set del to top1, get its data into a variable, change top1, then free del.
             deldata = del->data;
             top1 = top1->next;
             free(del);
             return deldata;          // return the "popped" value.
        }
    }
    else if(num == 2)
    {
        if(top2 == NULL)
        {
            printf("\nUnderflow case. Empty stack.");
            printf("\n this part of the function should ideally never be used in this program!");
            exit(3);
        }
        else{
            struct node *del;
             int deldata;
             del = top2;              // set del to top2, get its data into a variable, change top2, then free del.
             deldata = del->data;
             top2 = top2->next;
             free(del);
             return deldata;          // return the "popped" value.
        }
    }
}

void queue_peek()                     // this function will only be used for stack corresponding to top1
{
    // in this implementation, since we will have oldest element stored at head (as you will see in queue_enqueue()), it is the front/head.
    if(top1 == NULL)
    {
        printf("\nEmpty Queue. Nothing to peek at.");
    }
    else{
        // read data of head element (top of stack1) without popping it!
        printf("\nHead element is: %d", top1->data);
    }
}

void queue_enqueue()
{
    // to enqueue an element, we will pop all elements from stack1 to stack2, push it into stack2, then pop all elements from stack2 to stack1
    if(queueSize == MAX)                 // if stackSize has reached the max limit
    {
        printf("\nOVERFLOW CASE! QUEUE IS FULL! enqueue is not possible at this moment.");
        return;
    }
    struct node *newnode, *temp;
    int num, i;
    printf("\nEnter Data:");
    scanf("%d", &num);
    newnode = create(num);
    for(i = 0; i < queueSize; i++)
    {
        temp = create(pop(1));            // temporary node to store popped values from stack1
        push(2, temp);                    // so they can be pushed into stack2
    }
    push(2, newnode);                     // push new element into stack2
    for(i = 0; i < queueSize+1; i++)
    {
        temp = create(pop(2));            // temporary node to store popped values from stack2
        push(1, temp);                    // so they can be pushed into stack1
    }
    queueSize++;                          // increment queueSize
    printf("\n%d has been successfully enqueued into the Queue.", num);
}

void queue_dequeue()
{
    // to pop an element, just show top value, change the top (of stack1) and free del.
    if(queueSize == 0)
    {
        printf("\nUNDERFLOW CASE! QUEUE IS EMPTY! dequeue is not possible at this moment.");
        return;
    }
    struct node *del;
    del = top1;
    if(queueSize == 1)                // if queue has 1 element
    {
        printf("\n%d has been popped successfully", del->data);
        top1 = NULL;
        free(del);
        queueSize--;
        return;
    }
    top1 = top1->next;               // shift top, display del->data, then free del
    printf("\n%d has been popped successfully", del->data);
    free(del);
    queueSize--;
}

void queue_isEmpty()
{
    if(queueSize == 0)
    {
        printf("\nQueue is empty!!!");
    }
    else
    {
        printf("\nQueue is not empty!");
    }
}

void queue_isFull()
{
    if(queueSize == MAX)
    {
        printf("\nQueue is full!!!");
    }
    else
    {
        printf("\nQueue is not full!");
    }
}

void traverse()
{
    if(queueSize == 0)
    {
        printf("\nThe queue is empty, nowhere to traverse!");
        return;
    }
    struct node *temp;
    temp = top1;
    printf("\nElements of queue (front to rear): ");
    while(temp->next != NULL){
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("%d", temp->data); // to get the last element value as well
}