

//Program using file operations
#include<stdio.h>
#include<stdlib.h>

int main(int argc, char *argv[])
{
    if(argc>2)                         // argc contains argument count. Argument count should be 2 for execution to proceed in this case
    {                                  // the arguments are stored using pointer array *argv[], the contents of which are explained below
        printf("too many arguments. enter exactly one file name.");
        exit(1);
    }
    else if(argc<2)
    {
        printf("too few arguments. enter exactly one file name.");
        exit(2);
    }

    FILE *in, *out;                    // file pointer declaration and initialization
    in = fopen(argv[1],"r");           // argv[0] is always the location of the executable file
                                       // while, argv[1] is the filename of the input file
    out = fopen("output.txt","w");     // the output filename is output.txt

    if(in == NULL)                     // exception case, if file not found
    {
        printf("input file does not exist.\n");
        exit(3);
    }

    int ele, max, min;                 // declaring, initializing variables
    int sum = 0;
    int num = 0;
    float avg;
    char ch;

    fscanf(in, "%d%c", &ele, &ch);     // reading first line just to set defaults for max, min
    max = ele;
    min = ele;
    fseek(in, 0, SEEK_SET);            // make sure file stream pointer is back at the beginning of the file

    while(fscanf(in, "%d%c", &ele, &ch) != EOF)  // traverse lines of the file
    {
        num = num + 1;                 // to get number of elements
        if(ele>max)
            max = ele;                 // code for max and min
        if(ele<min)
            min = ele;
        sum = sum + ele;               // to get sum of elements
    }
    avg = (float)sum / num;            // type casting while calculating average

    fprintf(out, "%d\n%d\n%d\n%d\n%.2f\n", num, min, max, sum, avg); // recording output in output.txt file

    fclose(in);                        // always close files after use
    fclose(out);

    return 0;
}
