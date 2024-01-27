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

int main(){
    setlocale(LC_ALL,"en_US");

    FILE *file = fopen("users.txt","a+");

    if(file == NULL){
        perror("Error opening users file");
        return EXIT_FAILURE;
    }

    int choice;
    do {
        printf("1. Add User\n");
        printf("2. List Users\n");
        printf("3. Find User by ID\n");
        printf("4. Update User by ID\n");
        printf("5. Delete User by ID\n");
        printf("0. Exit\n");

        printf("Choose an option:");
        scanf("%d", &choice);

        struct User user;
        int id;

        switch (choice) {

            case 1:
            printf("Enter user ID:");
            scanf("%d", &user.id);
            printf("Enter user name:");
            scanf("%s", user.name);
            printf("Enter user age:");
            scanf("%d", &user.age);
            addUser(file, &user);
            break;

            case 2:
                listUsers(file);
                break;
            
            case 3:
                printf("Enter user ID to find: ");
                scanf("%d", &id);
                findUser(file, id);
                break;
           
            case 4:
                printf("Enter user ID to update: ");
                scanf("%d", &id);
                printf("Enter new user ID: ");
                scanf("%d", &user.id);
                printf("Enter new user name: ");
                scanf("%s", user.name);
                printf("Enter new user age: ");
                scanf("%d", &user.age);

                updateUser(file, id, &user);
                break;
           
            case 5:
                printf("Enter user ID to delete: ");
                scanf("%d", &id);
                deleteUser(file, id);
                break;
         
            case 0:
                printf("Exiting program.\n");
                break;
           
            default:
                printf("Invalid option. Please try again.\n");
        }
    }
    while (choice !=0);
    fclose(file);
    return 0;
}


