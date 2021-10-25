
// PROGRAM FOR BREADTH FIRST SEARCH ON AN UNDIRECTED GRAPH
#include<stdio.h>
#include<stdlib.h>

void find_dist();
void enqueue();
int dequeue();

int m, n;

struct vertex{                 // for vertex of graph
    int data;
    struct vertex *next;
};

struct queue{                  // for queue node
    int data;
    struct queue *next;
};
struct queue *head_q = NULL;   // initialize queue head, tail
struct queue *tail_q = NULL;

struct queue* create(int num)  // create function for enqueueing process
{
    struct queue *newnode = (struct queue*)malloc(sizeof(struct queue));
    if(newnode == NULL)
    {
        printf("\nInsufficient memory space.");
        exit(6);
    }
    newnode->data = num;
    newnode->next = NULL;
    return newnode;
}

int main(int argc, char *argv[])
{
    FILE *fp;                          // to empty the output file
    fp = fopen("sd.txt","w");
    fclose(fp);
 
    if(argc>2)                         // argc contains argument count. Argument count should be 2 for execution to proceed in this case
    {                                  // the arguments are stored using pointer array *argv[] 
        printf("too many arguments. enter exactly one file name.");
        exit(1);
    }
    else if(argc<2)
    {
        printf("too few arguments. enter exactly one file name.");
        exit(2);
    }
    
    FILE *infile;
    infile = fopen(argv[1], "r");
    if(infile == NULL)
    {
        printf("input file does not exist\n");
        exit(3);
    }
    
    int v1, v2;
    fscanf(infile, "%d %d\n", &n, &m); // n is number of vertices and m is number of edges (number of lines to read in the file after first line)
    
    struct vertex *allvert[n];
    int color[n];
    int dist[n];
    for(int i = 0; i < n; i++)
    {
        color[i] = 0;                 // 0 for white, 1 for grey, 2 for black
        dist[i] = -1;
        allvert[i] = NULL;
    } 
    
    while(fscanf(infile, "%d %d\n", &v1, &v2) != EOF)
    {
        struct vertex *newnode1 = malloc(sizeof(struct vertex));
        struct vertex *newnode2 = malloc(sizeof(struct vertex));
        if(newnode1 != NULL && newnode2 != NULL)                   // check if memory is available
        {
            newnode1->data = v1;
            newnode2->data = v2;
        }
        else{
           printf("\nMemory Insufficient!");
           exit(4);
        }
        newnode2->next = allvert[v1];                // append v2 to adjacency list of v1
        allvert[v1] = newnode2;
        newnode1->next = allvert[v2];                // and vice versa
        allvert[v2] = newnode1;
    }
    fclose(infile);
    
    color[0] = 1;                                    // values assuming 0 is source node
    dist[0] = 0;
    enqueue(0);
    
    while(head_q != NULL)                            // the main part of the BFS Algorithm
    {
        int k = dequeue();                           // dequeue from queue and traverse through that element's adjacency list
        struct vertex *traversal;
        traversal = allvert[k];
        while(traversal != NULL)
        {
            if(color[traversal->data] == 0)          // if a node is unvisited, then now change its color to grey
            {
                color[traversal->data] = 1;
                dist[traversal->data] = dist[k] + 1; // also update its distance to be one greater than that of dequeued element
                enqueue(traversal->data);            // enqueue the now-grey element into queue
            }
            traversal = traversal->next;
        }
        color[k] = 2;                                // once all neighbours of k are visited, change color of k to black
    }
    
    FILE *outfile;
    outfile = fopen("sd.txt", "a+");
    for(int i = 0; i < n; i++)
    {
        fprintf(outfile, "%d\n", dist[i]);          // output file contains distances of all nodes from source 
    }
    fclose(outfile);
    return 0;
}

int dequeue()                        // basically, delete_beg() for a singly linked list
{
    if(head_q == NULL)              // if queue is empty (verification measure, though the stack handling will manage this)
    {
        printf("\nUnderflow case. Empty queue.");
        printf("\n this part of the function should ideally never be used in this program!");
        exit(5);
    }
    else{
        struct queue *del;
        int deldata;
        del = head_q;               // set del to head, get its data into a variable, change head, then free del.
        deldata = del->data;
        head_q = head_q->next;
        free(del);
        return deldata;             // return the "dequeued" value.
    }
}

void enqueue(int num)               // basically, insert_end() for a singly linked list
{
    struct queue *newnode;
    newnode = create(num);
    if(head_q == NULL)              // if queue is empty
    {
        head_q = newnode;
        tail_q = newnode;
    }
    else{
         tail_q->next = newnode;    // else, make tail point to new node, change tail
         tail_q = newnode;
    }
}