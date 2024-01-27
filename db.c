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

void addUser(FILE *file, const struct User *user) {
    printf(file, "%d, %s, %d\n", user->id, user->name, user->age);

}

void listUsers(FILE *file) {
    rewind(file);

    struct User user;
    printf("List of Users:\n");
    while (fscanf(file, "%d, %49[^,], %d\n", &user.id, user.name, &user.age) == 3){
        printf("ID: %d, Name: %s, Age: %d\n", user.id, user.name, user.age);
    }
    printf("\n");
}

