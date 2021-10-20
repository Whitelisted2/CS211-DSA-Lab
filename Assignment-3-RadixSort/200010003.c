
// Program to perform Radix Sort
// NOTE: THE GIVEN OUTPUT FILES DO NOT END IN NEWLINE CHARACTER, SO THIS HAS BEEN DONE ACCORDINGLY.
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
void RadixSort();
void CountingSort();

int main(int argc, char *argv[])
{
    FILE *fp;                          // to empty the output file
    fp = fopen("radix.txt","w");
    fclose(fp);
 
    if(argc>3)                             // argc contains argument count. Argument count should be 2 for execution to proceed in this case
    {                                      // the arguments are stored using pointer array *argv[] 
        printf("too many arguments. enter one file name, AND number of digits of largest number in file.");
        exit(1);
    }
    else if(argc<3)
    {
        printf("too few arguments. enter exactly one file name, AND number of digits of largest number in file");
        exit(2);
    }
    
    FILE *in;
    in = fopen(argv[1],"r");                // first argument is the name of input file with .txt extension
    int d = atoi(argv[2]);                  // second argument is number of digits of max number in the file.
    int size = 0;
    int temp;
    while(fscanf(in, "%d\n", &temp) != EOF) // deduce size of number set to be sorted
    {
        size++;
    }
    if(size == 0)
    {
        printf("EMPTY FILE !! CAUTION! THIS MAY LEAD TO ERRORS!");
        exit(4);
    }
    int A[size];
    
    int i = 0;
    fseek(in, 0, SEEK_SET);                 // ensure that file stream pointer is at beginning.
    while(fscanf(in, "%d\n", &temp) != EOF) // store the numbers of the file in an array, A[size]
    {
        A[i] = temp;
        i++;
    }
    fclose(in);
 
    RadixSort(A, d, size);                  // calls RadixSort(), which does operations on array A[] to sort it using radix sort
 
    FILE *out;
    out = fopen("radix.txt","w");
    for(i = 0; i < size-1; i++)             // write the sorted array elements into output file
    {
        fprintf(out, "%d\n", A[i]);
    }
    fprintf(out, "%d", A[size-1]);          // since last element doesn't have \n at the end, we enter it in separately
    fclose(out);
 
    return 0;
}

void RadixSort(int A[], int d, int size)
{
    int i;
    int num_ofdigits = 0;
    int num = 1;
    int max = A[0];
    for (i = 1; i < size; i++)    // to get max-number from the file. seems like a better practice
    {
        if (A[i] > max)
        {
            max = A[i];
        }
    }
    while(max/num > 0)            // get number of digits of the aforementioned max-number
    {
        num *= 10;
        num_ofdigits++;
    }
    if(num_ofdigits != d)         // check if it corresponds to the entered argv[2]
    {
        printf("ENTERED NO. OF DIGITS OF MAX NUMBER (argv[2]) IS INCORRECT. BE CAREFUL AS IT MAY CAUSE ERRORS.");
        // exit(5); // commented out since we can just give the message that argv[2] was wrong and still carry on using the value we found 
    }
    int p; // using p variable for more simplicity, and less use of the pow() function
    for(p = 1; max/p > 0; p*=10)
    {
        CountingSort(A, p, size); // conducting CountingSort() one digit at a time, from Ones place (LSD) towards MSD
    }
}

void CountingSort(int A[], int p, int size)
{
    int i;
    int dc[10];                  // initialize digit count array with zeroes
    for(i = 0; i < 10; i++)
    {
        dc[i] = 0;
    }
    
    int ds[size];               // get values for digit separation array (i.e. getting digit in place p)
    for(i = 0; i < size; i++)
    {
        ds[i] = (A[i]/p)%10;    // get the digit in 'p'th place
    }
    
    for(i = 0; i < size; i++)   // get values for the digit count array (i.e. frequency of each digit)
    {
        dc[ds[i]]++;
    }
    
    for(i = 1; i < 10; i++)     // make the digit count array cumulative
    {
        dc[i] += dc[i-1];
    }
    
    int ax[size];               // put elements into a new array arranged by the considered place
    for(i = size-1; i >= 0; i--)
    {
        ax[dc[ds[i]]-1] = A[i];
        dc[ds[i]]--;
    }
    
    for(i = 0; i<size; i++)     // reassign these sorted values to original array A[] before going back to next CountingSort() or main function
    {
        A[i] = ax[i];
    }
}