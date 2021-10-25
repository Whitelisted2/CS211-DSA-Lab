
// Program to implement Binary Search Tree
#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>  // for isdigit()
#include<string.h> // for strstr()

// structure for a tree node
struct BSTree{
    struct BSTree *left;
    int data;
    struct BSTree *right;
};

// function to create a node
struct BSTree *create(int item){
  struct BSTree *temp = (struct BSTree *)malloc(sizeof(struct BSTree));
  temp->data = item;
  temp->left = NULL;
  temp->right = NULL;
  return temp;               // returns node (as a structure)
}
struct BSTree *root;

// operations to be performed
void insert();
void search();
void successor();
void predecessor();
struct BSTree* findMin();
struct BSTree* findMax();
void preorder();
void postorder();
void inorder();
void maximum();
void minimum();

// global variables to manage the formatting of output from preorder/postorder/inorder
int size = 0;
int counter = 0;

int main(int argc, char *argv[])
{
    FILE *fp;                          // to empty the output file
    fp = fopen("bst.txt","w");
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
    
    // read input file line-by-line
    FILE *in;
    in = fopen(argv[1], "r");
    char line[20];
    int i;
    while(fgets(line, 20, in) != NULL)
    {
        // if it has the required substring, then do the required function
        // in some cases, we'll need to take a number input
        if(strstr(line, "insert"))
        {
            char *temp = line;
            temp += 7;
            strcpy(line, temp);
            line[strlen(line)-1]='\0';
            
            int val = atoi(line);
            insert(val);
        }
        else if(strstr(line, "search"))
        {
            char *temp = line;
            temp += 7;
            strcpy(line, temp);
            line[strlen(line)-1]='\0';
            
            int val = atoi(line);
            search(val);
        }
        else if(strstr(line, "successor"))
        {
            char *temp = line;
            temp += 10;
            strcpy(line, temp);
            line[strlen(line)-1]='\0';
            
            int val = atoi(line);
            successor(val);
        }
        else if(strstr(line, "predecessor"))
        {
            char *temp = line;
            temp += 12;
            strcpy(line, temp);
            line[strlen(line)-1]='\0';
            
            int val = atoi(line);
            predecessor(val);
        }
        else if(strstr(line, "inorder"))
        {
            counter = 0;
            inorder(root);
            FILE *outin;
            outin = fopen("bst.txt","a+");
            fprintf(outin, "\n");
            fclose(outin);
        }
        else if(strstr(line, "preorder"))
        {
            counter = 0;
            preorder(root);
            FILE *outpre;
            outpre = fopen("bst.txt","a+");
            fprintf(outpre, "\n");
            fclose(outpre);
        }
        else if(strstr(line, "postorder"))
        {
            counter = 0;
            postorder(root);
            FILE *outpost;
            outpost = fopen("bst.txt","a+");
            fprintf(outpost, "\n");
            fclose(outpost);
        }
        else if(strstr(line, "maximum"))
        {
            maximum(root);
            FILE *outmax;
            outmax = fopen("bst.txt","a+");
            fprintf(outmax, "\n");
            fclose(outmax);
        }
        else if(strstr(line, "minimum"))
        {
            minimum(root);
            FILE *outmin;
            outmin = fopen("bst.txt","a+");
            fprintf(outmin, "\n");
            fclose(outmin);
        }
    }
    fclose(in);
    return 0;
}

void insert(int val)
{
    struct BSTree *newnode;
    newnode = create(val);
    if(root == NULL)
    {
        // for empty tree
        root = newnode;
    }
    else{
        struct BSTree *current, *temp;
        current = root;
        while(current != NULL)
        {
            temp = current;
            if(current->data > newnode->data)
            {
                current = current->left;
            }
            else{
                current = current->right;
            }
        }
        if(temp->data > newnode->data)
        {
            temp->left = newnode;
        }
        else{
            temp->right = newnode;
        }
    }
 
    // logging the insertion in output file
    FILE *out;
    out = fopen("bst.txt","a");
    fprintf(out, "%d inserted\n", val);
    size++;
    fclose(out);
}

void search(int val)
{
    struct BSTree *sear;
    sear = root;
    while(sear != NULL)
    {
        if(val == sear->data)
        {
            FILE *out1;
            out1 = fopen("bst.txt", "a");
            fprintf(out1, "%d found\n", val);
            fclose(out1);
            return;
        }
        else if(val < sear->data)
        {
            sear = sear->left;
        }
        else{
            sear = sear->right;
        }
    }
 
    FILE *out2;
    out2 = fopen("bst.txt", "a");
    fprintf(out2, "%d not found\n", val);
    fclose(out2);
}

void preorder(struct BSTree *preordertravel)
{
    if(preordertravel != NULL)
    {
        FILE *out;
        out = fopen("bst.txt","a+");
        counter++;
        // since in the sample file, list of numbers doesn't end with a space
        if(counter == size)
        {
            fprintf(out, "%d", preordertravel->data);
        }
        else{
            fprintf(out, "%d ", preordertravel->data);
        }
        fclose(out);
        
        preorder(preordertravel->left);
        preorder(preordertravel->right);
    }
}

void postorder(struct BSTree *postordertravel)
{
    if(postordertravel != NULL)
    {
        postorder(postordertravel->left);
        postorder(postordertravel->right);
        
        FILE *out;
        out = fopen("bst.txt","a+");
        counter++;
        // since in the sample file, list of numbers doesn't end with a space
        if(counter == size)
        {
            fprintf(out, "%d", postordertravel->data);
        }
        else{
            fprintf(out, "%d ", postordertravel->data);
        }
        fclose(out);
    }
}

void inorder(struct BSTree *inordertravel)
{
    if(inordertravel != NULL)
    {
        inorder(inordertravel->left);
        
        FILE *out;
        out = fopen("bst.txt","a+");
        counter++;
        // since in the sample file, list of numbers doesn't end with a space
        if(counter == size)
        {
            fprintf(out, "%d", inordertravel->data);
        }
        else{
            fprintf(out, "%d ", inordertravel->data);
        }
        fclose(out);
        
        inorder(inordertravel->right);
    }
}

void maximum(struct BSTree *max)
{
    if(root == NULL)
    {
        // empty tree
        return;
    }
    while(max->right != NULL)
    {
        // rightmost element 
        max = max->right;
    }
    FILE *out;
    out = fopen("bst.txt","a");
    fprintf(out, "%d", max->data);
    fclose(out);
}

void minimum(struct BSTree *min)
{
    if(root == NULL)
    {
        // empty tree
        return;
    }
    while(min->left != NULL)
    {
        // leftmost element
        min = min->left;
    }
    FILE *out;
    out = fopen("bst.txt","a");
    fprintf(out, "%d", min->data);
    fclose(out);
}

void successor(int val)
{
    // search for val in BST. If it does not exist, report that in output and return
    struct BSTree *sear;
    int status = 0;             // 0:not found, 1:found
    sear = root;
    while(sear != NULL)
    {
        if(val == sear->data)
        {
            status = 1;                  // in this case, sear contains val
            break;
        }
        else if(val < sear->data)
        {
            sear = sear->left;
        }
        else{
            sear = sear->right;
        }
    }
    if(status == 0)
    {
        // if tree is empty, or element is not present in tree
        FILE *outsear;
        outsear = fopen("bst.txt","a");
        fprintf(outsear, "%d does not exist\n", val);
        fclose(outsear);
        return;
    }
    
    // find max value in BST. if val == max, then val has no successor and return
    struct BSTree *max;
    max = root;
    while(max->right != NULL)
    {
        max = max->right; 
    }
    if(max->data == val)
    {
        FILE *outmax;
        outmax = fopen("bst.txt","a");
        fprintf(outmax, "successor of %d does not exist\n", val);
        fclose(outmax);
        return;
    }
    
    // so, we have effectively ensured that successor exists
    // and, we know it exists for node 'sear' due to the above search
    struct BSTree *curr, *succ;
    curr = root;
    succ = root;
    while(curr->data != sear->data){
        if(curr->data > sear->data){
            succ = curr;
            curr= curr->left;
        }
        else
            curr = curr->right;
    }

    if(curr->right != NULL)
    {
        succ = findMin(curr->right);
    }
    
    FILE *out;
    out = fopen("bst.txt","a");
    fprintf(out, "%d\n", succ->data);
    fclose(out);
    return;
}

struct BSTree* findMin(struct BSTree *test)
{
    while(test->left != NULL)
    {
        test = test->left;
    }
    return test;
}

void predecessor(int val)
{
    // search for val in BST. If it does not exist, report that in output and return
    struct BSTree *sear;
    int status = 0;             // 0:not found, 1:found
    sear = root;
    while(sear != NULL)
    {
        if(val == sear->data)
        {
            status = 1;
            break;
        }
        else if(val < sear->data)
        {
            sear = sear->left;
        }
        else{
            sear = sear->right;
        }
    }
    if(status == 0)
    {
        // if tree is empty, or element is not present in tree
        FILE *outsear;
        outsear = fopen("bst.txt","a");
        fprintf(outsear, "%d does not exist\n", val);
        fclose(outsear);
        return;
    }
    
    // find min value in BST. if val == min, then val has no predecessor and return
    struct BSTree *min;
    min = root;
    while(min->left != NULL)
    {
        min = min->left;
    }
    if(min->data == val)
    {
        FILE *outmax;
        outmax = fopen("bst.txt","a");
        fprintf(outmax, "predecessor of %d does not exist\n", val);
        fclose(outmax);
        return;
    }
    
    // so, we have effectively ensured that predecessor exists
    // and, we know it exists for node 'sear' due to the above search
    struct BSTree *curr, *pred;
    curr = root;
    pred = root;
    while(curr->data != sear->data){
        if(curr->data > sear->data){
            curr= curr->left;
        }
        else{
            pred = curr;
            curr = curr->right;
        }
    }

    if(curr->left != NULL)
    {
        pred = findMax(curr->left);
    }
    
    FILE *out;
    out = fopen("bst.txt","a");
    fprintf(out, "%d\n", pred->data);
    fclose(out);
    return;
}

struct BSTree* findMax(struct BSTree *test)
{
    while(test->right != NULL)
    {
        test = test->right;
    }
    return test;
}