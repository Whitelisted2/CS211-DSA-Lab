
// PROGRAM TO IMPLEMENT DIJKSTRA ALGORITHM USING MIN-PRIORITY QUEUE
#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
#define MAX 1000000     // note: lots of comments initially, marginally less within functions

void insert_into_pq();  // several functions to make minheap management easier!
void heapify_up();      // to be used when inserting
void heapify_down();    // to be used when extracting
int parent();           // to return index of priority-parent of some node k
int leftc();            // to return index of priority-leftchild of some node k
int rightc();           // to return index of priority-right-child of some node k
int extract_min();      // to extract min element of priority queue + re-adjust it

int distance[MAX];      // distances of points from the source node
int heapsize;           // size of heap; global variable
int priority[MAX];      // array where index = priority; value = vertex
int exist[MAX];         // if vertex exists in input file at all or not

struct vertex{                 // for vertex of graph, or rather a member of adj.list
    int data;
    int weight;
    struct vertex *next;
};
struct vertex *allvert[MAX];


int main(int argc, char *argv[])
{
    FILE *fp;                          // to empty the output file
    fp = fopen("dijkstra.txt","w");
    fclose(fp);
 
    if(argc>3)                         // argc contains argument count. Argument count should be 3 for execution to proceed in this case
    {                                  // the arguments are stored using pointer array *argv[] 
        printf("too many arguments. enter exactly one file name and source vertex.");
        exit(1);
    }
    else if(argc<3)
    {
        printf("too few arguments. enter exactly one file name and source vertex.");
        exit(2);
    }
 
    int source = atoi(argv[2]);               // get source
    
    FILE *infile;
    infile = fopen(argv[1], "r");
    if(infile == NULL)
    {
        printf("input file does not exist\n");
        exit(3);
    }
    
    int i;
    for(i = 0; i < MAX; i++)                  // set initial values of all global arrays
    {
        exist[i] = 0;
        distance[i] = INT_MAX;
        allvert[i] = NULL;
        priority[i] = -1;
    }
    priority[0] = INT_MAX;                    // for our purposes, we begin priority minheap at index 1
    
    // To initialize single source
    distance[source] = 0;                     // set distance of source node to 0
    

    int u, v, w;
    while(fscanf(infile, "%d %d %d\n", &u, &v, &w) != EOF)
    {
        struct vertex *newnode = malloc(sizeof(struct vertex));
        if(newnode != NULL)                   // check if memory is available
        {
            newnode->data = v;
            newnode->weight = w;
        }
        else{
           printf("\nMemory Insufficient!");
           exit(4);
        }
        newnode->next = allvert[u];           // append newnode v at beginning of adjacency list of u
        allvert[u] = newnode;
        if(exist[u] == 0)                     // if one of the vertices hasn't been encountered yet,
        {                                     // then make its exist[] value 1, and insert into PriotityQueue
            exist[u] = 1;
            insert_into_pq(u);
        }
        if(exist[v] == 0)
        {
            exist[v] = 1;
            insert_into_pq(v);
        }
    }
    fclose(infile);
  
    while(heapsize > 0)                   // main part: core of Dijkstra Algorithm
    {
        u = extract_min();                // get min element of priority queue
        if(distance[u] == INT_MAX)
        {
            continue;                     // this 'continue' won't occur unless vertex is disconnected from source node
        }
        struct vertex *temp;
        temp = allvert[u];
        while(temp != NULL)               // relax all edges from u, by going through its adj list
        {
            v = temp->data;
            if(distance[v] > (distance[u] + temp->weight))
            {
                distance[v] = distance[u] + temp->weight; // If there's a faster path to v,
                for(i = 0;; i++)                          // look for priority index of v
                {
                    if(priority[i] == v)
                    {
                        break;
                    }
                }
                heapify_up(i);                            // re-heapify-up, based on its new shortest-distance
            }
            temp = temp->next;
        }
    }
 
    FILE *outfile;
    outfile = fopen("dijkstra.txt", "a+");
    for(i = 0; i < MAX; i++)
    {
        if(exist[i] == 1)                                // if vertex exists, print to file
        {
            if(distance[i] == INT_MAX)
            {
                fprintf(outfile, "%d -1\n", i);
            }
            else{
                fprintf(outfile, "%d %d\n", i, distance[i]);
            }
        }
    }
    fclose(outfile);
    return 0;
}

void insert_into_pq(int vert) // increments heap size and takes value of vertex (data)
{
    priority[++heapsize] = vert;
    heapify_up(heapsize);     // heapify-up to ensure it is still min-heap 
}

void heapify_up(int c)
{
    int temp, par; 
    while((c > 1) && (distance[priority[c]] < distance[priority[parent(c)]]))
    {                                   // if distance of a priority-parent is more than that of its child,
        par = parent(c);                // then exchange priorities.
        temp = priority[c];
        priority[c] = priority[par];
        priority[par] = temp;
        c = par;
    }                                   // until you reach root node (index 1) or satisfy minheap condition
}

int extract_min()
{
    int min = priority[1];             // get element with most priority (least distance)
    priority[1] = priority[heapsize];  // place last node at root, then re-heapify-down from root (1)
    priority[heapsize] = INT_MAX;
    heapsize--;
    heapify_down(1);
    return min;
}

void heapify_down(int i)
{
    int min = i;
    int lc = leftc(i);
    if((lc <= heapsize) && (distance[priority[lc]] < distance[priority[min]])) // check if left child is smaller than the node itself
    {
        min = lc;
    }
    int rc = rightc(i);
    if((rc <= heapsize) && (distance[priority[rc]] < distance[priority[min]])) // if right child is smaller than left child, swap with right child
    {
        min = rc;
    }
    
    if(min != i) // if there is balancing to be done (i.e. any child's distance < parent's distance)
    {
        int temp = priority[i];
        priority[i] = priority[min];
        priority[min] = temp;
        heapify_down(min);     // recursively exchange with min-child until heap is level-wise sorted
    }
}

int parent(int c)          // parent of node k is at floor(k/2). can be type-casted.
{
    int par = (int)c/2;
    return par;
}
int leftc(int k)           // left child of a node k is at 2k
{
    int c = (2 * k);
    return c;
}
int rightc(int k)          // right child of a node k is at 2k + 1
{
    int c = (2 * k) + 1;
    return c;
}