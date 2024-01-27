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
    fprintf(file, "%d, %s, %d\n", user->id, user->name, user->age);

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

void findUser(FILE *file, int id) {
    rewind(file);

    struct User user;
    int found = 0;
    while (fscanf(file, "%d, %49[^,], %d\n", &user.id, user.name, &user.age) == 3){
        if (user.id == id){
            printf("User found:\n");
            printf("ID: %d, Name: %s, Age: %d\n\n", user.id, user.name, user.age);
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("User with ID %d not found.\n\n", id);

    }
}

void updateUser(FILE *file, int id, const struct User *newUser) {
    rewind(file);

    FILE *temp = fopen("temp.txt", "a+");
    if (temp == NULL) {
        perror("Error creating temporary file");
        exit(EXIT_FAILURE);
    }

    struct User user;
    while (fscanf(file, "%d, %49[^,], %d\n", &user.id, user.name, &user.age) == 3) {
        if (user.id == id) {
            fprintf(temp, "%d, %s, %d\n", newUser->id, newUser->name, newUser->age);

        }

        else {
            fprintf(temp, "%d, %s, %d\n", user.id, user.name, user.age);
        }
    }

    fclose(file);
    fclose(temp);

    remove("users.txt");
    rename("temp.txt","users.txt");

    printf("User update successfully!!!\n\n");
}

void deleteUser(FILE *file, int id){
    rewind(file);

    FILE *temp = fopen("temp.txt", "a+");
    if(temp == NULL) {
        perror("Error creating temporary file");
        exit(EXIT_FAILURE);
    }

    struct User user;
    int delete = 0;
    while (fscanf(file, "%d, %49[^,], %d\n", &user.id, user.name, &user.age) == 3){
        if (user.id == id){
            delete = 1;
        }
        else {
            fprintf(temp, "%d, %s, %d\n", user.id, user.name, user.age);

        }
    }

    fclose(file);
    fclose(temp);

    remove("users.txt");
    rename("temp.txt", "users.txt");

    if(delete) {
        printf("User deleted succefully!\n\n");
    }
    else {
        printf("User with ID %d not found.\n\n", id);
    }
}


