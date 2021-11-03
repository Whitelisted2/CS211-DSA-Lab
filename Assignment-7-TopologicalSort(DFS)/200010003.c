

// PROGRAM FOR DEPTH FIRST SEARCH ON A DIRECTED ACYCLIC GRAPH
#include<stdio.h>
#include<stdlib.h>
#define MAX 10000

void push();
int pop();
void dfs();

int m, n;
int time = 0;
int color[MAX], discover[MAX], finished[MAX];

struct vertex{                 // for vertex of graph
    int data;
    struct vertex *next;
};
struct vertex *allvert[MAX];

struct stack{                  // for stack top
    int data;
    struct stack *next;
};
struct stack *top_s = NULL;      // initialize stack top

struct stack* create(int num)  // create function for enqueueing process
{
    struct stack *newnode = (struct stack*)malloc(sizeof(struct stack));
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
    fp = fopen("ts.txt","w");
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
    
    int i;
    for(i = 0; i < n; i++)
    {
        color[i] = 0;                 // 0 for white, 1 for grey, 2 for black
        discover[i] = -1;
        allvert[i] = NULL;
        finished[i] = -1;
    }
 
    while(fscanf(infile, "%d %d\n", &v1, &v2) != EOF)
    {
        struct vertex *newnode = malloc(sizeof(struct vertex));
        if(newnode != NULL)                   // check if memory is available
        {
            newnode->data = v2;
        }
        else{
           printf("\nMemory Insufficient!");
           exit(4);
        }
        newnode->next = allvert[v1];
        allvert[v1] = newnode;
    }
    fclose(infile);
    
    for(i = 0; i < n; i++)                          // for vertices 0 to n-1
    {
        if(color[i] == 0)                           // if unvisited,
        {
            dfs(i);                                 // then dfs
        }
    }
    
    FILE *outfile;
    outfile = fopen("ts.txt", "a+");
    while(top_s !=  NULL)
    {
        fprintf(outfile, "%d\n", pop());
    }
    fclose(outfile);
    return 0;
}

void dfs(int i)
{
    time++;
    discover[i] = time;
    color[i] = 1;
    struct vertex *traversal;
    traversal = allvert[i];
    
    while(traversal != NULL)
    {
        if(color[traversal->data] == 0)
        {
            dfs(traversal->data);
        }
        traversal = traversal->next;
    }
    
    color[i] = 2;
    time++;
    finished[i] = time;
    push(i);
}

void push(int num) // insert_beg()
{
    struct stack *newnode;
    newnode = create(num);
    if(top_s == NULL)
    {
        top_s = newnode;
    }
    else{
        newnode->next = top_s;
        top_s = newnode;
    }
}

int pop() // delete_beg()
{
    if(top_s == NULL)
    {
        printf("\nUnderflow case. Empty stack.");
        printf("\n this part of the function should ideally never be used in this program!");
        exit(2);
    }
    else{
        struct stack *del;
        int deldata;
        del = top_s;             // set del to top1, get its data into a variable, change top1, then free del.
        deldata = del->data;
        top_s = top_s->next;
        free(del);
        return deldata;          // return the "popped" value.
    }
}