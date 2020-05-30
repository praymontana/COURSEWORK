#include <stdio.h>

#ifndef FUNC_H_INCLUDED
#define FUNC_H_INCLUDED

///Prototypes of structures (for both lists) and functions for sublist

///The structure describing the information field of a sublist item
typedef struct T
{
    char *model;            ///Pointer to the first element of the string storing the name of the smartphone model
    char *cpu;              ///Pointer to the first element of the string storing the processor name
    float RAM;              ///The amount of RAM (in GB)
    float cost;             ///Price (in thousand rubles)
    int camera;             ///Camera resolution (in megapixels)
    int ROM;                ///The amount of ROM of the device (in GB)
    int year;               ///Smartphone launch year
}phone;

///The structure describing the list item
typedef struct e
{
    int ID;                 ///Individual List ID
    phone *content;         ///Pointer to the information field of a list item
    struct e *next;         ///Pointer to the next list item
    struct e *prev;         ///Pointer to the previous list item
}node;

///The structure describing the "head" of the list
typedef struct h
{
    int cnt;                ///The number of structures in the list
    node *first;            ///Pointer to the first item in the list
    node *last;             ///Pointer to the last item in the list
}head;

///The structure describing the list item
typedef struct b
{
    int ID;                 ///Individual List ID
    char *brand;            ///Pointer to the first element of the string storing the brand of the smartphone
    head *start;            ///Pointer to the "head" of the list linking the models of one brand
    struct b *next;         ///Pointer to the next list item
    struct b *prev;         ///Pointer to the previous list item
}branch;

///The structure describing the "head" of the main list
typedef struct N
{
    int cnt;                ///The number of structures in the list
    int schet0;             ///ID counter of this list
    branch *first;          ///Pointer to the first item in the list
    branch *last;           ///Pointer to the last item in the list
}nach;

///Function to initialize an array of flags
int *init(int col);

///Function that checks the entered number for correctness
float check(float left, float znach, float right, char *str);

///Help function
void help();

///----------------------------------------------------
///Some functions for the main list

///Function that returns field name brand
char* brand_out(branch *b);

///Function that creates the "head" of the main list
nach *create_nach();

///Feunction that adds a new brand to the file cabinet
void create_branch(nach *n, char *str, head *h);

///Function that checks if a given brand is in the file cabinet (1 - yes, 0 - no)
branch *finder(nach *h, char *str);

///Function that displays all the elements of the main list and reads the user's choice
branch *choose_branch(nach *n);

///Function that copies the original card file to the working one
void copy_kart(nach *n1, nach *n2);

///Function that displays a list item header
void print_nach(char *str);

///Function that displays all brands in a file cabinet
void all_out(nach *h);

///Function that removes all models of a certain brand
void del_branch(nach *n, int id);

///Function that swaps the elements of the main list
void swap_b(branch *b1, branch *b2);

///Function sorting items in the main list
void sort_brand(nach *n, char* (*function)(branch*), int flag);

///Function sorting everything else
void sort_all(nach *n, char* (*function)(node*), int (*funcname)(node*), float (*func)(node*), int flag);

///Function searching for the main list item
void search_brand(nach *n, char* str, char* (*function)(branch*));

///Search function throughout the file cabinet
void search_all(nach *n, char *str, float l1, float l2, char* (*function)(node*), int (*funcname)(node*), float (*func)(node*));

///Function that writes the result to a txt file
void write(nach *n, FILE *ph);

///Function that writes the result to a csv file
void write_csv(nach *n, FILE *ph);

///Function that cleans the entire file cabinet
nach *clear_kart(nach *n);

///----------------------------------------------------
///Functions for the main list

///Function that causes a delay and screen clearing
void delay();

///Function that returns the model field name
char* model_out(node *p);

///Function that returns the CPU field name
char* cpu_out(node *p);

///Function that returns the RAM field name
float RAM_out(node *p);

///Function that returns the cost field name
float cost_out(node *p);

///Function that returns the camera field name
int camera_out(node *p);

///Function that returns the ROM field name
int ROM_out(node *p);

///Function that returns the year field name
int year_out(node *p);

///Function returning user selection
float choose();

///Keyboard Read Function
char* input_line();

///Function that displays all the items in the sublist and reads the user's choice
int choose_elem(head *h, char *str);

///Structure Fill Function
phone* str_fill();

///Function that prints the list
void str_out(head *h);

///The function that displays the "header" to display the file cabinet
void print_header();

///Function that clears the information field of a list item
void clear_inf(phone *n);

///Function of cleansing structure
void clear_str(head *h);

///Function that frees memory from a two-dimensional array of strings
void clear(char** data1, int schet);

///Function separating a string by a delimiter character
char **split(char *data0, char sep);

///Function filling a structure from a file
void file_fill(nach *h, char *data, char sep, int schet);

///Function that creates the "head" of the list
head *create_head();

///Function that creates the list item
void create_elem(head* h, int k, phone *ks);

///Function that swaps information content of list items
void swap(node *f, node *s);

///A function that sorts an array of structures by fields in the sublist
void sort_ost(head *h, int (*func_sort)(node*), float (*func_s)(node*), int flag_sort);

///A function that sorts an array of structures by name field
void sort_name(head *h1, char* (*func_sot)(node*), int flag_sot);

///Function looking for values ​​by numeric fields
void search_ost(nach *N, head *h, float f1, float f2, int (*funcname)(node*), float (*func)(node*), int bi);

///String Comparison Function
int sravn(char *s1, char *s2);

///Function looking for values ​​in a string field
void search_name(nach *N, head *h, char* str, char* (*funct)(node*), int bi);

///Function that removes a list item
void del_node(nach *N, head *h, int bi, int id);

///Function that copies the contents of structures
void copy(phone *first, phone *second);

///List Copy Function
void copy_str(head *h1, head *h2);

///Function that adds an item after any
void insert_after(head *h, int id, int k);

///Function that adds an item before any
void insert_before(head *h, int id, int k);

///Field Correction Function
void correct(branch *b, int id);

#endif // FUNC_H_INCLUDED
