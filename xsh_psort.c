/******************************************************************************************************************************
  AUTHORS: GIRISH SRINIVAS
******************************************************************************************************************************
*/
#include <xinu.h>
#include <stdio.h>
#include <stdlib.h>

/*******************************************************************************************************************************
   bsort() prototype which take 4 parameter which are:
   1. an integer pointer to an array.
   2. an integer variable which holds the size of the array.
   3. a character pointer which is used to store the name of the process.
   4. a semaphore variable.
********************************************************************************************************************************
*/
void bsort(int *, int, char *, sid32);

//shell cmd psort.
shellcmd xsh_psort(int32 argc, char *argv[])
{
    int N;          //size of the array.
    int SEED;       //value of seed for srand().
    int *a, *b;     //array pointers.
    int i;          // loop variable.
    sid32 s = semcreate(1); //semaphore variable.

   // long start1, end1, start2, end2;
    //long *timevar;
    
    //condition to check if the user enter correct number of cmd line arguments.
    if(argc == 3)
    {
        N = atoi(argv[1]);
        SEED = atoi(argv[2]);
        *a = (int *)getmem(N * 4);
        *b = (int *)getmem(N * 4);
    }
    else
    {
        printf("\nInsufficient arguments passed to the program...!\n");
        return -1;
    }

    //prints the size of the array.
    printf("\nThe size of the array is: %d\n", N);

    srand(SEED);                    //takes the seed and assigns to variable and send to rand().

    //generates the random number using rand().
    for(i = 0; i < N; i++)
    {
        a[i] = rand();          //places the random numbers in first array.
        b[i] = a[i];            //copies the contents of first array into second array.
    }

    //start1 = gettime(timevar);
    resume(create(bsort, 1024, 80, "Bsort_1", 4, a, N, "Bsort_1", s));  //creates a process "Bsort_1".
    //end1 = gettime(timevar);

    sleep(3);       //sleep() is used to synchronize the process execution.
    
    //start2 = gettime(timevar);
    resume(create(bsort, 1024, 10, "Bsort_2", 4, a, N, "Bosrt_2", s));  //creates a process "Bsort_2".
    //end2 = gettime(timevar);

    sleep(3);       //sleep() is used to synchronize the process execution.

    //printf("Time elapsed for process Bsort_1 is: %d sec\n",(end1-start1));
    //printf("Time elapsed for process Bsort_2 is: %d sec\n",(end2-start2));
    printf("\npsort() method terminated!!!...\n");
    kill(getpid());     //terminates psort() method.
}


/********************************************************************************************************************************
  Bubble sort function definition which sorts the content of the array in ascending order.
  It takes 4 parameters, which are:
  1. an integer pointer variable which points to an array.
  2. an integer variable which holds the value of size of the array.
  3. a character pointer variable which holds the name of the process.
  4. a semaphore variable.
*********************************************************************************************************************************
*/
void bsort(int *a, int n, char *name, sid32 s)
{
    int i, j;
    int temp;
    int x1, x2;

    for(i = 0; i < (n - 1); i++)
    {
        for(j = 0; j < (n - 1 - i); j++)
        {
            wait(s);        //wait() system call is executed on semaphor variable 's'.
            x1 = a[j];      //the first value in the array is read and stored in 'x1'.
            signal(s);      //signal() system call is executed on semaphore variable 's'.

            wait(s);        
            x2 = a[j + 1];  //the second value in the array is read and stored in 'x2'.
            signal(s);
            
            //comparision of 2 values.
            if(x1 > x2)
            {
                temp = x1;      //swapping of variables takes place.
                x1 = x2;
                x2 = temp;

                wait(s);
                a[j] = x1;      //the swapped values are stored back into the array.
                signal(s);

                wait(s);
                a[j + 1] = x2;  //the swapped values are stored back into the array.
                signal(s);

            }
        }
    }
    
    //prints the sorted array for a particular process.
    printf("\nThe sorted array for process ID: %d with name: %s\n", getpid(), name);
    for(i = 0; i < n; i++)
        printf("%d\n", a[i]);

    //terminates the process.
    printf("\nbsort() method for process id: %d with name %s is terminated!!!...\n", getpid(), name);
    kill(getpid());
}
