
// PROGRAM TO IMPLEMENT BELLMAN-FORD ALGORITHM
#include<stdio.h>
#include<stdlib.h>
#include<limits.h> // for INT_MAX, INT_MIN
#define MAX 10000
void set_reachable();

int distance[MAX], pred[MAX];

int m, n;

struct vertex{                 // for vertex of graph
    int data;
    int weight;
    struct vertex *next;
};
struct vertex *allvert[MAX];

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
    
    fscanf(infile, "%d %d\n", &n, &m); // n is number of vertices and m is number of edges (number of lines to read in the file after first line)
    
    int i, j;
    int in_neg_cycle[n];
    for(i = 0; i < n; i++)                    // initialize dist, pred and allvert (array of linked list pointers)
    {
        distance[i] = INT_MAX;
        pred[i] = -1;
        allvert[i] = NULL;
        in_neg_cycle[i] = 1;  // 1: not in a neg cycle; -1: in a neg cycle
    }
    
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
    }
    fclose(infile);
    
    int source = 0;
    distance[source] = 0;                     // assuming 0 is the source node
    
    for(i = 1; i < n; i++)                    // main bellman ford algorithm
    {
        for(j = 0; j < n; j++)
        {
            if(distance[j] == INT_MAX)        // if a node hasn't been visited yet, 
            {                                 // there's no point in relaxing its out-edges
                continue;
            }
            u = j;
            struct vertex *temp;
            temp = allvert[j];
            while(temp != NULL)               // relax all edges from u, by going through its adj list
            {
                v = temp->data;
                if(distance[v] > (distance[u] + temp->weight))
                {
                    distance[v] = distance[u] + temp->weight;
                    pred[v] = u;
                }
                temp = temp->next;
            }
        }
    }
 
    for(j = 0; j < n; j++)                    // If still updations are possible,
    {
        if(distance[j] == INT_MAX)            // (If still unreached, leave alone)
        {
            continue;
        }
        u = j;
        struct vertex *temp;
        temp = allvert[j];
        while(temp != NULL)                   // then it is part of a negative cycle
        {
            v = temp->data;
            if(distance[v] > (distance[u] + temp->weight))
            {
                in_neg_cycle[u] = -1;   
            }
            temp = temp->next;
        }
    }
    
    for(i = 0; i < n; i++)
    {
        if(in_neg_cycle[i] == -1)
        {
            // if a node is part of a negative cycle,
            // then all nodes reachable from there will also be at distance -inf
            // do a kind of breadth first traversal
            set_reachable(i, distance, allvert);
        }
    }

    FILE *outfile;
    outfile = fopen("sd.txt", "a+");
    for(i = 0; i < n; i++)
    {
        fprintf(outfile, "%d ", i);
        if(i == source) // source is always at 0 distance
        {
            fprintf(outfile, "0\n");
        }
        else if(distance[i] == INT_MIN)
        {
            fprintf(outfile, "-inf\n");
        }
        else if(distance[i] == INT_MAX)
        {
            fprintf(outfile, "+inf\n");
        }
        else{
            fprintf(outfile, "%d\n", distance[i]);
        }
    }
    fclose(outfile);
    return 0;
}

void set_reachable(int i, int distance[], struct vertex **head)
{
    if(distance[i] == INT_MIN) // if visited, return
    {
        return;
    }
    distance[i] = INT_MIN;     // mark that it is visited
    struct vertex *temp;
    temp = head[i];
    while(temp != NULL)        // any vertices that are reachable from it will also be -inf
    {
        if(distance[temp->data] != INT_MIN)
        {
            set_reachable(temp->data, distance, head); // recursion, like BFS
        }
        temp = temp->next;
    }
}