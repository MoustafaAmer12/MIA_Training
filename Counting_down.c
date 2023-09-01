/*
 * File_name: Counting_down.c
 * Author: Moustafa Esam
 * Description: Task 1.2
 * Date_created: 13/8
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SLEEP_SEC 1

int main()
{
    int time;
    printf("Enter the countdown.\n");


    // Handle input's type and value from user
    int temp;
    do
    {
        temp = scanf("%d", &time);
        if(!temp || time <= 0)
        {
            printf("Enter a valid time value.\n");
        }
        while(getchar() != '\n');
    }while(!temp || time <= 0);

    // Start the countdown
    while(time > 0)
    {
        printf("%d\n", time--);
        sleep(SLEEP_SEC);
        if(time == 0)
        {
            printf("Blast off to the moon!\n");
        }
    }
    return 0;
}
