/*
 * File_name: Task_Manager.c
 * Author: Moustafa Esam
 * Description: Task 1.3
 * Date_created: 14/8
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define SLEEP_SEC 2
#define MAX_SIZE 101
#define MAX_STRING 32

/**
  * print_menu: prints the task manager menu with the valid options
  * Return: void
  */
void print_menu();

/**
  * add_task - adds a task to the list given its description
  * Return: void
  */
void add_task();

/**
  * view_tasks - views the tasks list each with
  * its ID and Description consecuetively.
  * Return: void
  */
void view_tasks();

/**
  * remove_task - removes a task from the list given its ID
  * Return: void
  */
void remove_task();

/**
  * complete_task - marks a task as completed given its ID
  * Return: void
  */
void complete_task();

/**
  * view_table - views the list of tasks in a tabular format
  * with 2 columns indicating the task ID and Description
  * Return: void
  */
void view_table();

// Global Variables
int taskID[MAX_SIZE] = {0};
char task[MAX_SIZE][MAX_STRING];
bool complete[MAX_SIZE] = {false};
int count = 1;

int main()
{
    int option;
    print_menu();
    do
    {
        printf("Select an option: ");
        while(!scanf("%d", &option))
        {
            printf("Enter a valid option: ");
            while(getchar() != '\n');
        }
        switch(option)
        {
        // Add a Task
        case 1:
            add_task();
            break;

        // View Task List either completed or current
        case 2:
            view_tasks();
            break;

        // REmove a Task from the list
        case 3:
            remove_task();
            break;

        // Mark a task as completed
        case 4:
            complete_task();
            break;

        // Tabular Format
        case 5:
            view_table();
            break;
        // Exit the program
        case 6:
            printf("Exiting Minions Task Manager. Have a great day!\n");
            exit(0);

        // Any other input
        default:
            printf("This option is not in the list, Enter another one.");
        }
        printf("\n");
    }while(true);
    return 0;
}

void print_menu()
{
    printf("Minions Task Manager\n");
    printf("1.Add Task\n");
    printf("2.View Tasks\n");
    printf("3.Remove Task\n");
    printf("4.Mark Task\n");
    printf("5.View Tasks in Tabular Format\n");
    printf("6.Exit\n\n");
}

void add_task()
{
    printf("Enter task description: ");
    while(getchar() != '\n');
    scanf("%[^\n]%*c", task[count]);
    taskID[count] = count;
    count++;
    printf("Task added successfully!\n");
}

void view_tasks()
{
    int val;
    printf("Enter 1 to view current tasks or 2 to view completed tasks: ");
    while(!scanf("%d", &val) || (val > 1 & val < 0))
    {
        printf("Enter 1 or 2: ");
        while(getchar() != '\n');
    }
    if(val == 1)
    {
        printf("Current Tasks:\n");
        for(int i = 1; i < count;i++)
        {
            if(taskID[i] != 0 && !complete[i])
            {
                printf("Task ID: %d\nDescription: %s\n\n", taskID[i], task[i]);
            }
        }
    }
    else
    {
        printf("Completed Tasks:\n");
        for(int i = 1; i < count;i++)
        {
            if(taskID[i] != 0 && complete[i])
            {
                printf("Task ID: %d\nDescription: %s\n\n", taskID[i], task[i]);
            }
        }
    }
}

void remove_task()
{
    int ID;
    printf("Enter task ID to remove or 0 to exit: ");
    while(!scanf("%d", &ID) || ID >= count)
    {
        printf("Enter a valid Task ID: ");
        while(getchar() != '\n');
    }
    if(ID == 0)
    {
        printf("Returning to main menu...\n");
    }
    else
    {
        while(ID < count-1)
        {
            taskID[ID] = taskID[ID+1] - 1;
            strcpy(task[ID],task[ID+1]);
            complete[ID] = complete[ID+1];
            ID++;
        }
        taskID[count] = 0;
        strcpy(task[count],"");
        complete[count] = false;
        count--;
        printf("Task removed successfully!\n");
    }
}

void complete_task()
{
    int num;
    printf("Enter task ID to mark as complete or 0 to exit: ");
    while(!scanf("%d", &num) || num >= count)
    {
        printf("Enter a valid Task ID: ");
        while(getchar() != '\n');
    }
    if(num == 0)
    {
        printf("Returning to main menu...\n");
    }
    else
    {
        complete[num] = true;
        printf("Well done, Task %d completed!\n", num);
    }
}

void view_table()
{
    printf("TaskID\t\t%-30s\n", "Description");
    for(int i = 1; i < count; i++)
    {
        printf("%-6d\t\t%-30s\n", taskID[i], task[i]);
    }
}
