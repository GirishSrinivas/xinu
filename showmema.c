/* showmema.c */
/*----------------------------------------------------------------------------
  Authors: Girish Srinivas
 *----------------------------------------------------------------------------
 */

#include <xinu.h>
#include <stdio.h>

int bss_var = 0;
int common_var;
int data_var = 100;

void showmema(void)
{
    printf("Inside showmema.c\n\n");
    printf("Starting address of text is: %x\n", showmema);  //Starting address of text segment
    printf("Ending address of text is: %x\n", (showmema-4)); //ending address of text segment
    printf("Starting address of data is: %x\n", &data_var); //Starding address of data segment
    printf("Ending address of data is: %x\n", (&data_var - 4)); //ending addres of data segment
    printf("Starting address of COMMON(bss-un_init) is: %x\n", &common_var);
    printf("Startind address of bss(Zero_init) is: %x\n", &bss_var); //Starting address of bss segment
    printf("Ending address of bss is: %x\n",(&bss_var - 4)); //ending address of bss segment
}

