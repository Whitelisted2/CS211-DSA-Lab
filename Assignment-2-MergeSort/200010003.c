
// Program to perform Merge Sort
// NOTE: THE GIVEN OUTPUT FILES DO NOT END IN NEWLINE CHARACTER, SO THIS HAS BEEN DONE ACCORDINGLY.
#include<stdio.h>
#include<stdlib.h>
void mergesort();
void merge();

int main(int argc, char *argv[])
{
    FILE *tp;                          // emptying contents of output file
    tp = fopen("mergesort.txt","w");
    fclose(tp);
 
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
    
    FILE *in;
    in = fopen(argv[1],"r");          // 2nd element of argument array is the input file name
 
    int temp, ArraySize=0;
    while(fscanf(in, "%d\n", &temp) != EOF)
    {
        ArraySize++;                  // loop to find number of elements to be sorted
    }
    int arr[ArraySize];

    int i = 0;
    fseek(in, 0, SEEK_SET);
    while(fscanf(in, "%d\n", &temp) != EOF)
    {
        arr[i] = temp;               // getting values from input.txt into the array arr[]
        i++;
    }
    fclose(in);
 
    mergesort(arr, 0, ArraySize - 1); // mergesort() is called here
    
    FILE *out;
    out = fopen("mergesort.txt","w");
    for(i = 0; i < ArraySize; i++)
    {
        fprintf(out, "%d", arr[i]);
        if(i < ArraySize - 1)
         fprintf(out, "\n");       // since sample output doesn't end with a newline character
    }
    fclose(out);
 
    return 0;
}

void mergesort(int arr[], int l, int h)
{
    if (l < h)
    {
        int mid = l + (h - l) / 2;  // getting middle index of array without overflow when doing (h+l)
        mergesort(arr, l, mid);
        mergesort(arr, mid + 1, h); // splitting array in two parts and sorting recursively
        merge(arr, l, mid, h);      // merge back once sorted using merge()
    }
}

void merge(int arr[], int l, int mid, int h)
{
    int left_array_size = mid - l + 1; // setting size of subarrays
    int right_array_size = h - mid;
    int LeftArray[left_array_size], RightArray[right_array_size];
 
    int i, j;                          // giving values to the subarray elements
    for (i = 0; i < left_array_size; i++)
        LeftArray[i] = arr[l + i];
    for (j = 0; j < right_array_size; j++)
        RightArray[j] = arr[mid + 1 + j];
    
    i = 0;
    j = 0;
    int k = l;
    
    // while loop makes it easier for the case when there are still elements left in one of the sub-arrays after sorting
    while (i < left_array_size && j < right_array_size)
    {
        if (LeftArray[i] <= RightArray[j])
        {
            arr[k] = LeftArray[i];
            i++;
        }
        else
        {
            arr[k] = RightArray[j];
            j++;
        }
        k++;
    }
    // k may not be equal to h at this point, so leftover elements are just appended on directly, if any
    while (i < left_array_size)
    {
        arr[k] = LeftArray[i];
        i++;
        k++;
    }
    while (j < right_array_size)
    {
        arr[k] = RightArray[j];
        j++;
        k++;
    }
}