
#include<stdio.h>
#include<stdlib.h>
void add_to_ll();
void find_dist();
void enqueue();
int dequeue();

int m, n;

struct vertex{
    int data;
    char color;
    int dist;
    int pred;
    struct vertex *next;
};
struct vertex *allvert[2000];     // create array of pointers for the multiple linked lists

struct queue{
    int data;
    struct queue *next;
};
struct queue *head_grey = NULL;
struct queue *tail = NULL;

struct queue* create(int num)
{
    struct queue *newnode = (struct queue*)malloc(sizeof(struct queue));
    if(newnode == NULL)
    {
        printf("\nInsufficient memory space.");
        exit(1);
    }
    newnode->data = num;
    newnode->next = NULL;
    return newnode;
}

int main()
{
    FILE *fp;                          // to empty the output file
    fp = fopen("sd.txt","w");
    fclose(fp);
 
    // if(argc>2)                         // argc contains argument count. Argument count should be 2 for execution to proceed in this case
    // {                                  // the arguments are stored using pointer array *argv[] 
    //     printf("too many arguments. enter exactly one file name.");
    //     exit(1);
    // }
    // else if(argc<2)
    // {
    //     printf("too few arguments. enter exactly one file name.");
    //     exit(2);
    // }
 
    FILE *infile;
    infile = fopen("input1.graph", "r");
    if(infile == NULL)
    {
        printf("input file does not exist\n");
        exit(3);
    }
    
    fscanf(infile, "%d %d\n", &n, &m); // n is number of vertices and m is number of edges (number of lines to read in the file after first line)
    printf("\n 1st : %d  , %d ", n,m);
    //int i;
    // for(i=0; i<2000; i++)
    // {
    //     allvert[i] = NULL;
    // }
    printf("uh");
    printf("\n Second");
    //while(1) // every other line has two vertices to connect (undirected)
   //{
  //if ( fscanf(infile, "%d %d\n", &v1, &v2) == EOF ) { printf("OOOOOOOOOOOOO"); exit(0); }
  // add_to_ll(v1, v2); // add v2 to adjacency list of v1
  // add_to_ll(v2, v1); // add v1 to adjacency list of v2
  // printf("\n InSide Loop : %d  , %d ", v1,v2);
  //}
   printf("llllllllllllllllllllllllllllld ");
   fclose(infile);
  printf("llllllllllllllllllllllllllllld is last num");
    printf("d is last num");
    // graph should be ready via linked list representation!
    // we need to find distance of vertices from 0 now
    //find_dist();
    printf("hmmm");
    FILE *out;                          // to empty the output file
    out = fopen("sd.txt","a+");
    for(i = 0; i < n; i++)
    {
        fprintf(out, "%d\n", allvert[i]->dist);
    }
    fclose(out);
 
    return 0;
}

void find_dist()
{
    // we will find distance of all vertices from 0, and put it as information in its "dist" variable
    allvert[0]->color = 'g';
    allvert[0]->dist = 0;
    allvert[0]->pred = -1;
    enqueue(0);
    
    while(head_grey != NULL)
    {
        int u = dequeue();
        struct vertex *temp;
        temp = allvert[u];
        while(temp != NULL)
        {
            if(temp->color == 'w')
            {
                temp->color = 'g';
                temp->dist = allvert[u]->dist + 1;
                temp->pred = u;
                enqueue(u);
            }
            temp = temp->next;
        }
        allvert[u]->color = 'b';
    }
    
}

int dequeue()                        // basically, delete_beg() for a singly linked list
{
    if(head_grey == NULL)            // if queue is empty (verification measure, though the stack handling will manage this)
    {
        printf("\nUnderflow case. Empty queue.");
        printf("\n this part of the function should ideally never be used in this program!");
        exit(5);
    }
    else{
        struct queue *del;
        int deldata;
        del = head_grey;             // set del to head, get its data into a variable, change head, then free del.
        deldata = del->data;
        head_grey = head_grey->next;
        free(del);
        return deldata;              // return the "dequeued" value.
    }
}

void enqueue(int num)                // basically, insert_end() for a singly linked list
{
    struct queue *newnode;
    newnode = create(num);
    if(head_grey == NULL)            // if queue is empty
    {
        head_grey = newnode;
        tail = newnode;
    }
    else{
         tail->next = newnode;       // else, make tail point to new node, change tail
         tail = newnode;
    }
}

void add_to_ll(int from_vert, int to_vert)
{
    // for a moment, think about this as a hash table, since insertion procedure is very similar!!!
    struct vertex *newnode = malloc(sizeof(struct vertex));
    if(newnode != NULL)                          // check if memory is available
    {
        newnode->data = to_vert;                 // copy to_vert to data of the node
        newnode->color = 'w';                    // initially all vertices are white
        newnode->next = NULL;                    // initialise newnode->next to be NULL
        newnode->pred = -1;
    }
    else{
        printf("\nMemory Insufficient!");
        exit(4);
    }
    struct vertex *head;
    head = allvert[from_vert];
    if(head == NULL)                            // "no-collision" case
    {
        head = newnode;
    }
    else{                                       // "collision case"; insert at beginning of linked list
        newnode->next = head;
        head = newnode;
    }
    
}