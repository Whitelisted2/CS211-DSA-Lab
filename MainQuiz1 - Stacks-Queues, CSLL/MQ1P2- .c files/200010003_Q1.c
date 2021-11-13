
//Program to implement Circular Singly Linked List (CLL) and its operations
#include<stdio.h>
#include<stdlib.h>

// list of function declarations
void insert_begin();
void insert_end();
void insert_pos();
void delete_begin();
void delete_end();
void delete_pos();
void display();

// node structure, and some default parameter settings
struct node {
    int data;
    struct node* next;
};
struct node* head = NULL;

// global variable to record size of CLL
int listSize = 0;

// function to create a new node
struct node* create()
{
    struct node *newnode = (struct node*)malloc(sizeof(struct node));
    if(newnode == NULL)
    {
        printf("\nInsufficient memory space.");
        exit(1);
    }
    printf("\nEnter Data:");
    scanf("%d", &newnode->data);
    newnode->next = NULL;
    return newnode;
}

int main()
{
    int ch, n;
    while(1)
    {
        printf("\n\n_____________________________________________");
        printf("\nMenu for Circular Linked List");
        printf("\n_____________________________________________");
        printf("\n 1. Insert a node at the beginning ");
        printf("\n 2. Insert a node at the end");
        printf("\n 3. Insert a node at the given position");
        printf("\n 4. Delete a node from the beginning");
        printf("\n 5. Delete a node from the end");
        printf("\n 6. Delete a node from the given position");
        printf("\n 7. Display the list");
        printf("\n 8. Exit");
        printf("\nEnter your choice:");
        scanf("%d", &ch);
        switch(ch)
        {
            case 1:
                insert_begin();
                break;
            case 2:
                insert_end();
                break;
            case 3:
                insert_pos();
                break;
            case 4:
                delete_begin();
                break;
            case 5:
                delete_end();
                break;
            case 6:
                delete_pos();
                break;
            case 7:
                display();
                break;
            case 8:
                exit(0);
            default:
                printf("\nInvalid input. try again.");
        }
    }
    return 0;
}

void insert_begin()
{
    struct node *newnode, *tail;
    newnode = create();
    if(head == NULL)               // if CLL is empty
    {
        head = newnode;
        newnode->next = head;
    }
    else
    {
        tail = head;
        while(tail->next != head)  // get element just before head in CLL (i.e. tail)
        {
            tail = tail->next;
        }
        tail->next = newnode;      // place newnode after tail and before (old) head, then set it as new head 
        newnode->next = head;
        head = newnode;
    }
    listSize++;                    // increment listSize
    return;
}

void insert_end()
{
    struct node *newnode, *tail;
    newnode = create();
    if(head == NULL)               // if CLL is empty
    {
        head = newnode;
        newnode->next = head;
    }
    else
    {
        tail = head;
        while(tail->next != head)  // get element just before head in CLL (i.e. tail)
        {
            tail = tail->next;
        }
        tail->next = newnode;      // place newnode after (old) tail and before head
        newnode->next = head;
    }
    listSize++;                    // increment listSize
    return;
}

void insert_pos()
{
    struct node *newnode, *position;
    newnode = create();
    position = head;
    int i = 0;
    int pos;
    printf("\nEnter position to insert at (i.e. the index it should have after insertion):");
    scanf("%d", &pos);
    if(pos > 0 && pos < listSize)            // check if position lies within valid "middle" bounds
    {
        while(i < pos-1)                     // if yes, traverse upto one element prior
        {
            position = position-> next;
            i++;
        }
        newnode->next = position->next;      // set newnode->next to position->next, then make position->next as newnode
        position->next = newnode;
        listSize++;                          // increment listSize
    }
    else
    {
        struct node *tail;
        if(pos == 0)                         // if user wants to insert at beginning, reuse (most of) the code from insert_beg()
        {
            if(head == NULL)
            {
                head = newnode;
                newnode->next = head;
            }
            else
            {
                tail = head;
                while(tail->next != head)
                {
                    tail = tail->next;
                }
                tail->next = newnode;
                newnode->next = head;
                head = newnode;
            }
            listSize++;
        }
        else if(pos == listSize)             // if user wants to insert at end, reuse (most of) the code from insert_end()
        {
            tail = head;
            while(tail->next != head)
            {
                tail = tail->next;
            }
            tail->next = newnode;
            newnode->next = head;
            listSize++;
        }
        else                                 // if none of the above, then position must be invalid
        {
            printf("\nInvalid position for the existing circular linked list.");
        }
    }
    return;
}

void delete_begin()
{
    if(head == NULL)                        // if CLL is empty
    {
        printf("\nThe List is EMPTY!\n");
    }
    else
    {
        struct node *del;
        del = head;
        if(head->next == head)              // if CLL has one node
        {
            head = NULL;
            printf("\nData of deleted element = %d", del->data);
            free(del);
            listSize--;
        }
        else
        {
            struct node *tail;
            tail = head;
            while(tail->next != head)       // get element just before head in CLL (i.e. tail)
            {
                tail = tail->next;
            }
            head = head->next;              // change head, then make tail point to new head
            tail->next = head;
            printf("\nData of deleted element = %d", del->data);
            free(del);
            listSize--;
        }
    }
    return;
}

void delete_end()
{
    if(head == NULL)                        // if CLL is empty
    {
        printf("\nThe List is EMPTY!\n");
    }
    else
    {
        struct node *del;
        del = head;
        if(head->next == head)              // if CLL has one node
        {
            head = NULL;
            printf("\nData of deleted element = %d", del->data);
            free(del);
            listSize--;
        }
        else
        {
            struct node *delprev;
            delprev = head;
            del = del->next;
            while(del->next != head)       // get element just before head in CLL (i.e. tail), and also element just before tail
            {
                delprev = delprev->next;
                del = del->next;
            }
            delprev->next = head;          // change delprev->next to head, free old tail.
            printf("\nData of deleted element = %d", del->data);
            free(del);
            listSize--;
        }
    }
    return;
}

void delete_pos()
{
    if(head == NULL || listSize == 0)      // if CLL is empty 
    {
        printf("\nThe List is EMPTY!\n");
    }
    else
    {
        int i = 0;
        int pos;
        printf("\nEnter position of element to be deleted (i.e. its index):");
        scanf("%d", &pos);
        if(pos >= 0 && pos < listSize)     // check if position lies within valid bounds 
        {
            struct node *del, *delprev;
            del = head->next;
            delprev = head;
            while(i < pos-1)               // traverse upto the required position, while also traversing delprev upto the previous element
            {
                delprev = delprev->next;
                del = del->next;   
            }
            delprev->next = del->next;     // change delprev->next, then free del 
            printf("\nData of deleted element = %d", del->data);
            free(del);
            listSize--;
        }
        else                               // if not within bounds, must be an invalid position
        {
            printf("\nInvalid position for the existing circular linked list.");
        }
    }
    return;
}

void display()
{
    struct node *temp;
    temp = head;
    printf("\nNumber of elements: %d", listSize);
    if(head == NULL)                       // if CLL is empty
    {
        printf("\nLIST IS EMPTY!!");
    }
    else
    {
        printf("\nThe data of the elements of the Circular Singly Linked List are: ");
        while(temp->next!=head)            // traverse through all elements while printing
        {
            printf("\t%d", temp->data);
            temp = temp->next;
        }
        printf("\t%d", temp->data);        // also make sure to print the last element (tail)
    }
    return;
}