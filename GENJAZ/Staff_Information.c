#include <stdio.h>
#include <stdlib.h>
#define MAX_LINE_LENGTH 256
#define STAFF_FILE_PATH "staff.txt"
#pragma warning (disable:4996)

//Structure
typedef struct {
    char id[7];
    char name[20];
    char password[20];
    char position[30];
    char salary[10];
    char contact[15];
    char gender[10];
    int login;
} staff;

//Main Function
//Main Function
int staffInformationModule()
{
    staff s;
    char login_id[7], login_password[20], key[10];
    int choice;
    int found = 0;

    FILE* fp = fopen("staff.txt", "r");
    if (fp == NULL) {
        printf("Failed to open file\n");
        return 1;
    }

    //Login Surface
    while (!found) {
        printf("*****LOGIN*******\n");
        printf("Enter ID       : ");
        scanf("%s", login_id);
        printf("Enter password : ");
        scanf("%s", login_password);
        printf("*****************\n");

        fseek(fp, 0, SEEK_SET);
        while (fscanf(fp, "%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%d|\n", &s.id, &s.name, &s.password, &s.position, &s.salary, &s.contact, &s.gender, &s.login) != EOF) {
            if (strcmp(s.id, login_id) == 0 && strcmp(s.password, login_password) == 0) {
                found = 1;
                s.login++; // increase login time
                fseek(fp, sizeof(staff), SEEK_CUR); // move back to the beginning of the current record
                fprintf(fp, "%s|%s|%s|%s|%s|%s|%s|%d|\n", s.id, s.name, s.password, s.position, s.salary, s.contact, s.gender, s.login); // write the updated record
                fflush(fp); // flush the buffer to ensure changes are written to disk
                break;
            }
        }

        if (!found) {
            printf("Staff ID or password error!\n");
        }
    }


    // Update login time
    s.login++;
    fseek(fp, -(long)sizeof(staff), SEEK_CUR);
    fprintf(fp, "%s|%s|%s|%s|%s|%s|%s|%d|\n", s.id, s.name, s.password, s.position, s.salary, s.contact, s.gender, s.login);

    fclose(fp);

    //Home Page
    do {

    if (found)
    {
        int stop = 0;

        printf("*********Home Page*********\n");
        printf("1. My Details\n");
        printf("2. Staff Details Search\n");
        printf("3. Change My Password\n");
        printf("4. Exit\n");

        printf("\nEnter your choice :");
        scanf("%d", &choice);

        printf("***************************\n");

        switch (choice)
        {
        case 1:
            printf("********************************\n");
            printf("ID             : %s\n", s.id);
            printf("Name           : %s\n", s.name);
            printf("Gender         : %s\n", s.gender);
            printf("Position       : %s\n", s.position);
            printf("Contact Number : %s\n", s.contact);
            printf("Login Times    : %d\n", s.login);
            printf("********************************\n");
            system("pause");
            break;

        case 2:
            staffSearch();
            break;
        case 3:
            changePass(s.id);
            break;
        case 4: stop = 1;
            return 0;
        }
    }

    else {
        printf("Staff ID or password error!\n");
    }

    } while (choice != 4);
}

//Search
int staffSearch()
{
    staff s;
    char login_id[7], login_password[20], key[10];
    int choice;
    int found = 0;

    printf("Enter the staff ID to search for: ");
    scanf("%s", key);


    FILE* fp = fopen("staff.txt", "r");
    if (fp == NULL) {
        printf("Failed to open file\n");
        return 1;
    }

    while (fscanf(fp, "%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%d|\n", &s.id, &s.name, &s.password, &s.position, &s.salary, &s.contact, &s.gender, &s.login) != EOF) {
        if (strcmp(s.id, key) == 0) {
            found = 1;
            printf("ID             : %s\n", s.id);
            printf("Name           : %s\n", s.name);
            printf("Gender         : %s\n", s.gender);
            printf("Position       : %s\n", s.position);
            printf("Contact Number : %s\n", s.contact);
            break;
        }
    }

    if (!found) {
        printf("No staff member found with ID %s.", key);
    }

    fclose(fp);
}


//Reset Password
int changePass(char* id) {
    staff s;
    char old_password[20], new_password[20];
    int found = 0;
    FILE* fp, * temp_fp;

    fp = fopen(STAFF_FILE_PATH, "r");
    temp_fp = fopen("temp.txt", "w");

    if (fp == NULL || temp_fp == NULL) {
        printf("Failed to open file\n");
        return;
    }

    while (fscanf(fp, "%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]%s\n", s.id, s.name, s.password, s.position, s.salary, s.contact, s.gender) != EOF) {
        if (strcmp(s.id, id) == 0) {
            printf("Enter your old password: ");
            scanf("%s", old_password);
            if (strcmp(old_password, s.password) == 0) {
                printf("Enter your new password: ");
                scanf("%s", new_password);
                strcpy(s.password, new_password);
                found = 1;
            }
            else {
                printf("Old password incorrect\n");
            }
        }
        fprintf(temp_fp, "%s|%s|%s|%s|%s|%s|%s\n", s.id, s.name, s.password, s.position, s.salary, s.contact, s.gender);
    }

    if (found) {
        fclose(fp);
        fclose(temp_fp);

        remove(STAFF_FILE_PATH);
        rename("temp.txt", STAFF_FILE_PATH);

        printf("Password changed successfully.\n");

        main();
    }
    else {
        printf("No staff member found with ID %s.\n", id);

        fclose(fp);
        fclose(temp_fp);
        remove("temp.txt");
    }
    return 0;
}

