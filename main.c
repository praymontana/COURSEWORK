#include "my_lib.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <errno.h>

int main()
{
    nach *start=NULL,           ///Address of the "head" of the original main list
        *worker=NULL;           ///Address of the "head" of the working main list
    FILE *ph=NULL;              ///Address of the file containing the source data
    branch *bra=NULL;           ///Address of the main list item for displaying the brands of the main list
    char *data=NULL,            ///Address of the first element of the line, from the ph file
        sep;                    ///Separator character
    float f1,                   ///Variable of the left border of the search
        f2;                     ///Variable of the right border of the search
    int *menu=NULL,             ///Address of the first element of the flag array for displaying menu items
        *search=NULL,           ///Address of the first flag element for complex search queries
        ans,                    ///User's choice
        k,                      ///User's choice to delete list item
        schet,                  ///Variable to hold last ID
        flag,                   ///Flag responsible for sorting in a specific order
        count;                  ///Entry Counter

    setlocale(LC_ALL, "RUS");
    count=0;
    schet=0;
    ///Initializing Menu Flags
    menu=init(4);

    if (menu)
    {
        do
        {
            puts("Menu:");
            puts("1 - Entering a file cabinet from a file or manually");
            if (menu[0])
            {
                puts("2 - Output the entered sequence");
                puts("3 - Copy the source file to the working one");
                if (menu[1])
                {
                    puts("4 - Enter desired action");
                    if (menu[2])
                        puts("5 - Output result");
                }

            }
            puts("6 - Help output");
            puts("7 - Program shutdown");
            ans=(int)choose();
            system("cls");
            switch(ans)
            {
                ///--------------------------------------------------------
                case(1):
                    do
                    {
                        puts("Submenu:");
                        puts("1) - Entering structures from a file");
                        puts("2) - Entering Structures from the Keyboard");
                        puts("3) - Return to the main menu");
                        ans=(int)choose();
                        system("cls");
                        switch(ans)
                        {
                            ///--------------------------------------------
                            case(1):
                                ///Freeing memory from a file cabinet, if one exists
                                if (start)
                                    start=clear_kart(start);

                                ///Creating a file cabinet again
                                count=0;
                                start=create_nach();
                                ph=fopen("data.csv", "r");
                                if (ph)
                                {
                                    sep=';';
                                    data=(char*)malloc(80*sizeof(char));
                                    if (data)
                                    {
                                        while(fgets(data, 80, ph)!=NULL)
                                        {
                                            ///Reading data from a file and filling structures
                                            if (data[0]!='\n')
                                            {
                                                count++;
                                                schet++;
                                                file_fill(start, data, sep, schet);
                                            }
                                        }
                                        free(data);
                                        fclose(ph);

                                        if(!count)
                                        {
                                            start=clear_kart(start);
                                            puts("The file is empty");
                                            delay();
                                        }
                                        else
                                        {
                                            puts("Data entry completed successfully!");
                                            delay();
                                        }
                                    }
                                    else
                                    {
                                        puts("Memory Allocation Error");
                                        fclose(ph);
                                        delay();
                                    }
                                }
                                else
                                {
                                    perror("An error has occurred: ");
                                    delay();
                                }
                                break;
                            ///--------------------------------------------
                            case(2):
                                ///If the list is not empty, then the program suggests adding a file cabinet
                                if (start)
                                {
                                    puts("Do you want to complement the current list? (0)");
                                    puts("You can rewrite your list, just tap another key.");
                                    ans=(int)choose();
                                    if (ans!=0)
                                        count=0;
                                }
                                else
                                    count=0;

                                do
                                {
                                    count++;
                                    schet++;
                                    ///The smartphone brand was introduced separately in order to find out if this brand is already on the list.
                                    puts("Enter smartphone data:");
                                    printf("Enter phone brand - ");
                                    data=input_line();
                                    if (data)
                                    {
                                        ///Depending on the conditions, there is either the creation or addition of a list
                                        ///If a file exists and there are elements in it
                                        if ((count!=1)&&(start))
                                        {
                                            bra=finder(start, data);
                                            if (bra)            ///If a brand exists, a new model is written to it
                                                create_elem(bra->start, schet, NULL);
                                            else
                                            {
                                                ///If a brand is missing, a new master list item is created that identifies that brand.
                                                create_branch(start, data, NULL);
                                                start->last->start=create_head();
                                                create_elem(start->last->start, schet, NULL);
                                            }
                                        }
                                        else if(start==NULL)
                                        {
                                            ///If there is no file cabinet, it is created
                                            start=create_nach();
                                            create_branch(start, data, NULL);
                                            start->last->start=create_head();
                                            create_elem(start->last->start, schet, NULL);
                                        }
                                        else
                                        {
                                            ///If there are no elements in the list or the user wants to rewrite the card index, the existing one is deleted and recreated
                                            clear_kart(start);
                                            start=create_nach();
                                            create_branch(start, data, NULL);
                                            start->last->start=create_head();
                                            create_elem(start->last->start, schet, NULL);
                                        }
                                        free(data);
                                        data=NULL;
                                        puts("Do you want to introduce more structures? (1)");
                                        ans=(int)choose();
                                    }
                                }while(ans==1);
                                puts("\nEntering structures completed!");
                                delay();
                                break;
                            ///--------------------------------------------
                            case(3):
                                system("cls");
                                break;
                            ///--------------------------------------------
                            default:
                                puts("The entered value is invalid. Try again");
                                delay();
                        }
                    }while(ans!=3);

                    ///If the user has created a card file, the working card file is cleared and information is copied from the main card file to the working one.
                    if (start)
                    {
                        if (worker)
                            clear_kart(worker);

                        worker=create_nach();
                        copy_kart(start, worker);
                        ///Flags Initialization
                        menu[0]=1;
                        menu[1]=1;
                        menu[2]=0;
                        menu[3]=1;
                        free(search);
                        search=NULL;
                    }
                    ans=1;
                    break;
                ///--------------------------------------------------------
                case(2):
                    if (menu[0])
                    {
                        puts("Entered sequence of structures:");
                        all_out(start);
                    }
                    break;
                ///--------------------------------------------------------
                case(3):
                    ///If the user has created a card file, the working card file is cleared and information is copied from the main card file to the working one.
                    if (menu[0])
                    {
                        if (worker)
                            clear_kart(worker);

                        worker=create_nach();
                        copy_kart(start, worker);
                        ///Flags Initialization
                        menu[1]=1;
                        menu[2]=0;
                        menu[3]=1;
                        free(search);
                        search=NULL;
                        puts("File cabinet copied successfully");
                        delay();
                    }
                    break;
                ///--------------------------------------------------------
                case(4):
                    ///If a working file exists, then possible actions with it are displayed.
                    if (menu[1])
                    {
                        do
                        {
                            if (worker->cnt==0)
                                menu[3]=0;

                            puts("Select the desired action to be performed with the working file cabinet");
                            if (menu[3])
                            {
                                puts("1 - Brand removal");
                                puts("2 - Model removal");
                                puts("3 - Sorting");
                                puts("4 - Search");
                            }
                            puts("5 - Add item");
                            if (menu[3])
                                puts("6 - Model Characteristic Adjustment");
                            puts("7 - Exit to the main menu");
                            ans=(int)choose();
                            system("cls");
                            switch(ans)
                            {
                                ///---------------------------------
                                case(1):
                                    ///The working file cabinet is not empty; the main list item for deletion is selected
                                    if (menu[3])
                                    {
                                        bra=choose_branch(worker);

                                        if(bra)
                                        {
                                            del_branch(worker, bra->ID);
                                            menu[2]=1;
                                            puts("Item deleted successfully");
                                            delay();

                                        }
                                        else
                                        {
                                            puts("Error allocating memory");
                                            system("pause");
                                        }
                                    }
                                    break;
                                ///---------------------------------
                                case(2):
                                    ///The working file cabinet is not empty; the main list item for deletion is selected
                                    if (menu[3])
                                    {
                                        bra=choose_branch(worker);

                                        if (bra)
                                        {
                                            ///If the choose_branch function returned non-NULL, then the item is selected from the list selected in the previous step and deleted
                                            k=choose_elem(bra->start, bra->brand);
                                            del_node(worker, bra->start, bra->ID, k);
                                            ///Menu flag initialization
                                            menu[2]=1;
                                            puts("Item deleted successfully");
                                            delay();
                                        }
                                        else
                                        {
                                            puts("Error allocating memory");
                                            system("pause");
                                        }
                                    }
                                    break;
                                ///---------------------------------
                                case(3):
                                    ///If the worklist is not empty, then fields are displayed by which you can sort the file cabinet
                                    if (menu[3])
                                    {
                                        do
                                        {
                                            puts("By what field do you want to sort the file cabinet?");
                                            puts("1 - Brand");
                                            puts("2 - Model");
                                            puts("3 - CPU");
                                            puts("4 - RAM");
                                            puts("5 - ROM");
                                            puts("6 - Camera resolution");
                                            puts("7 - Launch year");
                                            puts("8 - Cost");
                                            puts("9 - Return to the previous submenu.");
                                            ans=(int)choose();
                                            switch(ans)
                                            {
                                                ///-------------------------
                                                case(1):
                                                    printf("Select a sort option (1 - in alphabetical order, 2 - in reverse alphabetical order) - ");
                                                    flag=(int)choose();
                                                    flag=(int)check(1, flag, 2, "Select a sort option (1 - in alphabetical order, 2 - in reverse alphabetical order) - ");
                                                    sort_brand(worker, brand_out, flag);
                                                    puts("Sort completed successfully!");
                                                    delay();
                                                    menu[2]=1;
                                                    break;
                                                ///-------------------------
                                                case(2):
                                                    printf("Select a sort option (1 - in alphabetical order, 2 - in reverse alphabetical order) - ");
                                                    flag=(int)choose();
                                                    flag=(int)check(1, flag, 2, "Select a sort option (1 - in alphabetical order, 2 - in reverse alphabetical order) - ");
                                                    sort_all(worker, model_out, NULL, NULL, flag);
                                                    puts("Sort completed successfully!");
                                                    delay();
                                                    menu[2]=1;
                                                    break;
                                                ///-------------------------
                                                case(3):
                                                    printf("Select a sort option (1 - in alphabetical order, 2 - in reverse alphabetical order) - ");
                                                    flag=(int)choose();
                                                    flag=(int)check(1, flag, 2, "Select a sort option (1 - in alphabetical order, 2 - in reverse alphabetical order) - ");
                                                    sort_all(worker, cpu_out, NULL, NULL, flag);
                                                    puts("Sort completed successfully!");
                                                    delay();
                                                    menu[2]=1;
                                                    break;
                                                ///-------------------------
                                                case(4):
                                                    printf("Select a sort option (1 - ascending, 2 - descending) - ");
                                                    flag=(int)choose();
                                                    flag=(int)check(1, flag, 2, "Select a sorting option (1 - ascending, 2 - descending) - ");
                                                    sort_all(worker, NULL, NULL, RAM_out, flag);
                                                    puts("Sort completed successfully!");
                                                    delay();
                                                    menu[2]=1;
                                                    break;
                                                ///-------------------------
                                                case(5):
                                                    printf("Select a sorting option (1 - ascending, 2 - descending) - ");
                                                    flag=(int)choose();
                                                    flag=(int)check(1, flag, 2, "Select a sorting option (1 - ascending, 2 - descending) - ");
                                                    sort_all(worker, NULL, ROM_out, NULL, flag);
                                                    puts("Sort completed successfully!");
                                                    delay();
                                                    menu[2]=1;
                                                    break;
                                                ///-------------------------
                                                case(6):
                                                    printf("Select a sorting option (1 - ascending, 2 - descending) - ");
                                                    flag=(int)choose();
                                                    flag=(int)check(1, flag, 2, "Select a sorting option (1 - ascending, 2 - descending) - ");
                                                    sort_all(worker, NULL, camera_out, NULL, flag);
                                                    puts("Sort completed successfully!");
                                                    delay();
                                                    menu[2]=1;
                                                    break;
                                                ///-------------------------
                                                case(7):
                                                    printf("Select a sorting option (1 - ascending, 2 - descending) - ");
                                                    flag=(int)choose();
                                                    flag=(int)check(1, flag, 2, "Select a sorting option (1 - ascending, 2 - descending) - ");
                                                    sort_all(worker, NULL, year_out, NULL, flag);
                                                    puts("Sort completed successfully!");
                                                    delay();
                                                    menu[2]=1;
                                                    break;
                                                ///-------------------------
                                                case(8):
                                                    printf("Select a sorting option (1 - ascending, 2 - descending) - ");
                                                    flag=(int)choose();
                                                    flag=(int)check(1, flag, 2, "Select a sorting option (1 - ascending, 2 - descending) -  ");
                                                    sort_all(worker, NULL, NULL, cost_out, flag);
                                                    puts("Sort completed successfully!");
                                                    delay();
                                                    menu[2]=1;
                                                    break;
                                                ///-------------------------
                                                case(9):
                                                    system("cls");
                                                    break;
                                                ///-------------------------
                                                default:
                                                    puts("Incorrect entry, try again");
                                                    delay();
                                            }
                                        }while(ans!=9);
                                        ans=3;
                                    }
                                    break;
                                ///---------------------------------
                                case(4):
                                    ///If the card file is not empty, then the fields for the search are offered (after selecting the field the next time it is not displayed)
                                    if (menu[3])
                                    {
                                        if (!search)
                                            search=init(8);

                                        do
                                        {
                                            puts("You can create complex search queries. To do this, select the required fields sequentially.\n");
                                            puts("Select a field to search:");
                                            if (!search[0])
                                                puts("1 - Brand");
                                            if (!search[1])
                                                puts("2 - Model");
                                            if (!search[2])
                                                puts("3 - CPU");
                                            if (!search[3])
                                                puts("4 - RAM");
                                            if (!search[4])
                                                puts("5 - ROM");
                                            if (!search[5])
                                                puts("6 - Camera resolution");
                                            if (!search[6])
                                                puts("7 - Launch year");
                                            if (!search[7])
                                                puts("8 - Cost");
                                            puts("9 - Return to the previous submenu.");
                                            ans=(int)choose(ans);
                                            system("cls");
                                            switch(ans)
                                            {
                                                ///-------------------------
                                                case(1):
                                                    if (!search[0])
                                                    {
                                                        menu[2]=1;
                                                        search[0]=1;
                                                        printf("Enter the desired name - ");
                                                        data=input_line();
                                                        search_brand(worker, data, brand_out);
                                                        puts("Search completed successfully!");
                                                        delay();
                                                        free(data);
                                                        data=NULL;
                                                    }
                                                    break;
                                                ///-------------------------
                                                case(2):
                                                    if (!search[1])
                                                    {
                                                        menu[2]=1;
                                                        search[1]=1;
                                                        printf("Enter the desired name - ");
                                                        data=input_line();
                                                        search_all(worker, data, 0, 0, model_out, NULL, NULL);
                                                        puts("Search completed successfully!");
                                                        delay();
                                                        free(data);
                                                        data=NULL;
                                                    }
                                                    break;
                                                ///-------------------------
                                                case(3):
                                                    if (!search[2])
                                                    {
                                                        menu[2]=1;
                                                        search[2]=1;
                                                        printf("Enter the desired name - ");
                                                        data=input_line();
                                                        search_all(worker, data, 0, 0, cpu_out, NULL, NULL);
                                                        puts("Search completed successfully!");
                                                        delay();
                                                        free(data);
                                                        data=NULL;
                                                    }
                                                    break;
                                                ///-------------------------
                                                case(4):
                                                    if (!search[3])
                                                    {
                                                        menu[2]=1;
                                                        search[3]=1;
                                                        puts("Enter the boundaries of the desired RAM amount (in GB). The range of values ​​is from 0.5 to 12:");
                                                        printf("Enter the first value - ");
                                                        f1=choose();
                                                        f1=check(0.5, f1, 12, "Enter the first value - ");
                                                        printf("Enter the second value - ");
                                                        f2=choose();
                                                        f2=check(0.5, f2, 12, "Enter the second value - ");
                                                        search_all(worker, NULL, f1, f2, NULL, NULL, RAM_out);
                                                        puts("Search completed successfully!");
                                                        delay();
                                                        free(data);
                                                        data=NULL;
                                                    }
                                                    break;
                                                ///-------------------------
                                                case(5):
                                                    if (!search[4])
                                                    {
                                                        menu[2]=1;
                                                        search[4]=1;
                                                        puts("Enter the boundaries of the desired ROM amount (in GB). The range of values ​​is from 2 to 1024:");
                                                        printf("Enter the first value - ");
                                                        f1=choose();
                                                        f1=check(2, f1, 1024, "Enter the first value - ");
                                                        printf("Enter the second value - ");
                                                        f2=choose();
                                                        f2=check(2, f2, 1024, "Enter the second value - ");
                                                        search_all(worker, NULL, f1, f2, NULL, ROM_out, NULL);
                                                        puts("Search completed successfully!");
                                                        delay();
                                                        free(data);
                                                        data=NULL;
                                                    }
                                                    break;
                                                ///-------------------------
                                                case(6):
                                                    if (!search[5])
                                                    {
                                                        menu[2]=1;
                                                        search[5]=1;
                                                        puts("Enter the boundaries of the desired resolution of camera (in megapixels). The range of values ​​is from 2 to 108:");
                                                        printf("Enter the first value - ");
                                                        f1=choose();
                                                        f1=check(2, f1, 108, "Enter the first value - ");
                                                        printf("Enter the second value - ");
                                                        f2=choose();
                                                        f2=check(2, f2, 108, "Enter the second value - ");
                                                        search_all(worker, NULL, f1, f2, NULL, camera_out, NULL);
                                                        puts("Search completed successfully!");
                                                        delay();
                                                        free(data);
                                                        data=NULL;
                                                    }
                                                    break;
                                                ///-------------------------
                                                case(7):
                                                    if (!search[6])
                                                    {
                                                        menu[2]=1;
                                                        search[6]=1;
                                                        puts("Enter the boundaries of the desired years of release. The range of values ​​from 2007 to 2020:");
                                                        printf("Enter the first value - ");
                                                        f1=choose();
                                                        f1=check(2007, f1, 2020, "Enter the first value - ");
                                                        printf("Enter the second value - ");
                                                        f2=choose();
                                                        f2=check(2007, f2, 2020, "Enter the second value - ");
                                                        search_all(worker, NULL, f1, f2, NULL, year_out, NULL);
                                                        puts("Search completed successfully!");
                                                        delay();
                                                        free(data);
                                                        data=NULL;
                                                    }
                                                    break;
                                                ///-------------------------
                                                case(8):
                                                    if (!search[7])
                                                    {
                                                        menu[2]=1;
                                                        search[7]=1;
                                                        puts("Enter the boundaries of the desired value (in thousand rubles). The range of values ​​is from 1 to 500:");
                                                        printf("Enter the first value - ");
                                                        f1=choose();
                                                        f1=check(1, f1, 500, "Enter the first value - ");
                                                        printf("Enter the second value - ");
                                                        f2=choose();
                                                        f2=check(1, f2, 500, "Enter the second value - ");
                                                        search_all(worker, NULL, f1, f2, NULL, NULL, cost_out);
                                                        puts("Search completed successfully!");
                                                        delay();
                                                        free(data);
                                                        data=NULL;
                                                    }
                                                    break;
                                                ///-------------------------
                                                case(9):
                                                    system("cls");
                                                    break;
                                                ///-------------------------
                                                default:
                                                    puts("Incorrect entry, try again");
                                            }
                                        }while(ans!=9);
                                        ans=4;
                                    }
                                    break;
                                ///---------------------------------
                                case(5):
                                    ///You can always add an item if the head of the working file cabinet exists.
                                    do
                                    {
                                        puts("Select the desired action:");
                                        puts("1 - Add a smartphone to a new brand");
                                        puts("2 - Add a smartphone to an existing brand");
                                        puts("3 - Return to previous submenu.");
                                        ans=(int)choose();
                                        system("cls");
                                        switch(ans)
                                        {
                                            ///---------------------
                                            case(1):
                                                puts("Enter smartphone data:");
                                                printf("Enter phone brand - ");
                                                data=input_line();
                                                ///Search for an entered brand
                                                bra=finder(worker, data);
                                                if (!bra)
                                                {
                                                    ///If the brand does not exist, then it is created
                                                    menu[2]=1;
                                                    create_branch(worker, data, NULL);
                                                    free(data);
                                                    data=NULL;
                                                    create_elem(worker->last->start, schet, NULL);
                                                    schet++;
                                                    puts("Item successfully added.");
                                                    delay();
                                                    break;
                                                }
                                                else
                                                {
                                                    ///If the brand exists, there is a redirect to case 2
                                                    free(data);
                                                    data=NULL;
                                                    puts("You have entered an existing brand. Redirecting");
                                                    delay();
                                                }
                                            ///---------------------
                                            case(2):
                                                do
                                                {
                                                    ///If we go directly to case 2, then the user must choose which brand to add the model to.
                                                    if (!bra)
                                                        bra=choose_branch(worker);

                                                    system("cls");
                                                    printf("Choose where you want to add the model from the brand %s\n", bra->brand);
                                                    puts("1 - Add item to end of sublist");
                                                    puts("2 - Add item to top of sublist");
                                                    puts("3 - Add item after specific sublist item");
                                                    puts("4 - Add an item before a specific sublist item");
                                                    puts("5 - Return to previous submenu.");
                                                    ans=(int)choose();
                                                    system("cls");
                                                    switch(ans)
                                                    {
                                                        ///---------------------
                                                        case(1):
                                                            menu[2]=1;
                                                            puts("Enter the remaining data:");
                                                            insert_after(bra->start, bra->start->last->ID, schet);
                                                            schet++;
                                                            puts("Item added successfully.");
                                                            delay();
                                                            break;
                                                        ///---------------------
                                                        case(2):
                                                            menu[2]=1;
                                                            puts("Enter the remaining data:");
                                                            insert_before(bra->start, bra->start->first->ID, schet);
                                                            schet++;
                                                            puts("Item added successfully.");
                                                            delay();
                                                            break;
                                                        ///---------------------
                                                        case(3):
                                                            ///If the user wants to add an element after a certain one, then he selects this element
                                                            k=choose_elem(bra->start, bra->brand);
                                                            if (k)
                                                            {
                                                                ///Происходит добавление
                                                                system("cls");
                                                                puts("Enter the remaining data:");
                                                                insert_after(bra->start, k, schet);
                                                                schet++;
                                                                menu[2]=1;
                                                                puts("Item added successfully.");
                                                                delay();
                                                            }
                                                            else
                                                            {
                                                                puts("Memory Allocation Error");
                                                                delay();
                                                            }
                                                            break;
                                                        ///---------------------
                                                        case(4):
                                                            ///If the user wants to add an element before a certain one, then he selects this element
                                                            k=choose_elem(bra->start, bra->brand);
                                                            if (k)
                                                            {
                                                                system("cls");
                                                                puts("Enter the remaining data:");
                                                                insert_before(bra->start, k, schet);
                                                                schet++;
                                                                menu[2]=1;
                                                                puts("Item added successfully.");
                                                                delay();
                                                            }
                                                            else
                                                            {
                                                                puts("Memory Allocation Error");
                                                                delay();
                                                            }
                                                            break;
                                                        ///---------------------
                                                        case(5):
                                                            system("cls");
                                                            break;
                                                        ///---------------------
                                                        default:
                                                            puts("Incorrect entry, try again");
                                                            delay();
                                                    }
                                                }while(ans!=5);
                                                ans=2;
                                                break;
                                            ///---------------------
                                            case(3):
                                                system("cls");
                                                break;
                                            ///---------------------
                                            default:
                                                puts("Incorrect entry, try again");
                                                delay();
                                        }
                                    }while(ans!=3);
                                    ans=5;
                                    break;
                                ///---------------------------------
                                case(6):
                                    ///If the list is not empty, then the brand is selected, and then the model for which you need to adjust the data
                                    ///If the user chooses to adjust the brand, the corresponding field of the main list changes
                                    if (menu[3])
                                    {
                                        bra=choose_branch(worker);

                                        if (bra)
                                        {
                                            k=choose_elem(bra->start, bra->brand);
                                            system("cls");
                                            correct(bra, k);
                                            menu[2]=1;
                                        }
                                        else
                                        {
                                            puts("Memory Allocation Error");
                                            delay();
                                        }
                                    }
                                ///---------------------------------
                                case(7):
                                    system("cls");
                                    break;
                                ///---------------------------------
                                default:
                                    puts("Incorrect entry, try again");
                                    delay();
                            }
                        }while(ans!=7);
                        ans=4;
                    }
                    break;
                ///--------------------------------------------------------
                case(5):
                    ///If an action was taken with a working card file and it is not empty, then it is displayed either in a file or on the screen
                    if (menu[2])
                    {
                        if(menu[3])
                        {
                            do
                            {
                                puts("How do you want to display the result?");
                                puts("1 - Display result on screen");
                                puts("2 - Output the result to a file");
                                puts("3 - Return to menu");
                                ans=(int)choose();
                                system("cls");
                                switch(ans)
                                {
                                    ///---------------------------------------
                                    case(1):
                                        puts("The result generated on request:");
                                        all_out(worker);
                                        break;
                                    ///---------------------------------------
                                    case(2):
                                        do
                                        {
                                            puts("Select the file in which the result will be written:");
                                            puts("1 - Write to TXT file");
                                            puts("2 - Write to CSV file");
                                            puts("3 - Return to the submenu");
                                            ans=(int)choose();
                                            system("cls");
                                            switch(ans)
                                            {
                                                ///---------------------------
                                                case(1):
                                                    puts("Writing to res.txt");
                                                    ph=fopen("res.txt", "w");
                                                    if (ph)
                                                    {
                                                        ///Writing to res.txt
                                                        write(worker, ph);
                                                        fclose(ph);
                                                    }
                                                    else
                                                    {
                                                        perror("An error has occurred : ");
                                                        delay();
                                                    }
                                                    break;
                                                ///---------------------------
                                                case(2):
                                                    puts("Writing to res.csv");
                                                    ph=fopen("res.csv", "w");
                                                    if (ph)
                                                    {
                                                        ///Writing to res.csv
                                                        write_csv(worker, ph);
                                                        fclose(ph);
                                                    }
                                                    else
                                                    {
                                                        perror("An error has occurred : ");
                                                        delay();
                                                    }
                                                    break;
                                                ///---------------------------
                                                case(3):
                                                    system("cls");
                                                    break;
                                                ///---------------------------
                                                default:
                                                    puts("Invalid value. Try again");
                                                    delay();
                                            }
                                        }while(ans!=3);
                                        ans=3;
                                        break;
                                    ///---------------------------------------
                                    case(3):
                                        system("cls");
                                        break;
                                    ///---------------------------------------
                                    default:
                                        puts("Invalid value. Try again");
                                        delay();
                                }
                            }while(ans!=3);
                        }
                        else
                        {
                            puts("Work array is empty");
                            delay();
                        }
                    }
                    break;
                ///--------------------------------------------------------
                case(6):
                    ///Conclusion of the help on the program
                    help();
                    break;
                ///--------------------------------------------------------
                case(7):
                    ///Freeing memory from under structures
                    if (start)
                        start=clear_kart(start);

                    if (worker)
                        worker=clear_kart(worker);

                    if (search)
                        free(search);

                    free(menu);

                    puts("Program shutdown");
                    delay();
                    break;
                ///--------------------------------------------------------
                default:
                    puts("Incorrect entry, try again");
                    delay();
            }
        }while(ans!=7);
    }
    else
    {
        puts("Incorrect entry, try again");
        delay();
    }

    return 0;
}
