#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

#define MAX_NAME_SIZE 50
#define FILE_SIZE 1000

struct User
{
    int id;
    char name[MAX_NAME_SIZE];
    int age;
};

