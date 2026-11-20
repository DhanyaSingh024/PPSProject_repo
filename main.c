#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define FILE_NAME "items.txt"

struct Item {
    int id;
    char type[10];
    char name[50];
    char category[30];
    char location[50];
    char status[15];
};

void addItem(void) {
    struct Item item;
    FILE *fp;
    int choice;

    printf("\n1. Lost item\n2. Found item\nChoose report type: ");
    scanf("%d", &choice);

    if (choice != 1 && choice != 2) {
        printf("Invalid choice.\n");
        return;
    }

    item.id = 1;
    fp = fopen(FILE_NAME, "a+");
    if (fp == NULL) {
        printf("Unable to open file.\n");
        return;
    }

    rewind(fp);
    {
        struct Item oldItem;
        while (fscanf(fp, "%d|%9[^|]|%49[^|]|%29[^|]|%49[^|]|%14[^\n]\n",
                      &oldItem.id, oldItem.type, oldItem.name,
                      oldItem.category, oldItem.location, oldItem.status) == 6) {
            if (oldItem.id >= item.id)
                item.id = oldItem.id + 1;
        }
    }

    strcpy(item.type, choice == 1 ? "LOST" : "FOUND");
    strcpy(item.status, "OPEN");

    printf("Item name (use underscores instead of spaces): ");
    scanf("%49s", item.name);

    printf("Category (e.g. book, bottle, keys): ");
    scanf("%29s", item.category);

    printf("Location (use underscores instead of spaces): ");
    scanf("%49s", item.location);

    fprintf(fp, "%d|%s|%s|%s|%s|%s\n",
            item.id, item.type, item.name, item.category,
            item.location, item.status);
    fclose(fp);

    printf("\nReport saved! Your item ID is %d.\n", item.id);
}

void viewItems(void) {
    struct Item item;
    FILE *fp = fopen(FILE_NAME, "r");
    int found = 0;

    if (fp == NULL) {
        printf("\nNo reports available yet.\n");
        return;
    }

    printf("\n--------------- CAMPUS ITEM REPORTS ---------------\n");
    while (fscanf(fp, "%d|%9[^|]|%49[^|]|%29[^|]|%49[^|]|%14[^\n]\n",
                  &item.id, item.type, item.name, item.category,
                  item.location, item.status) == 6) {
        printf("\nID: %d | Type: %s | Status: %s\n",
               item.id, item.type, item.status);
        printf("Item: %s | Category: %s | Location: %s\n",
               item.name, item.category, item.location);
        found = 1;
    }

    if (!found)
        printf("No reports available yet.\n");

    fclose(fp);
}

void searchItem(void) {
    struct Item item;
    char searchName[50];
    FILE *fp = fopen(FILE_NAME, "r");
    int found = 0;

    if (fp == NULL) {
        printf("\nNo reports available yet.\n");
        return;
    }

    printf("\nEnter item name to search (use underscores): ");
    scanf("%49s", searchName);

    while (fscanf(fp, "%d|%9[^|]|%49[^|]|%29[^|]|%49[^|]|%14[^\n]\n",
                  &item.id, item.type, item.name, item.category,
                  item.location, item.status) == 6) {
        if (strcmp(searchName, item.name) == 0) {
            printf("\nMatch found!\n");
            printf("ID: %d | Type: %s | Status: %s\n",
                   item.id, item.type, item.status);
            printf("Category: %s | Location: %s\n",
                   item.category, item.location);
            found = 1;
        }
    }

    if (!found)
        printf("No matching item found.\n");

    fclose(fp);
}

void markResolved(void) {
    struct Item item;
    FILE *fp = fopen(FILE_NAME, "r");
    FILE *temp = fopen("temp.txt", "w");
    int targetID, found = 0;

    if (fp == NULL || temp == NULL) {
        printf("\nUnable to open records.\n");
        if (fp != NULL) fclose(fp);
        if (temp != NULL) fclose(temp);
        return;
    }

    printf("\nEnter item ID to mark as returned/resolved: ");
    scanf("%d", &targetID);

    while (fscanf(fp, "%d|%9[^|]|%49[^|]|%29[^|]|%49[^|]|%14[^\n]\n",
                  &item.id, item.type, item.name, item.category,
                  item.location, item.status) == 6) {
        if (item.id == targetID) {
            strcpy(item.status, "RESOLVED");
            found = 1;
        }

        fprintf(temp, "%d|%s|%s|%s|%s|%s\n",
                item.id, item.type, item.name, item.category,
                item.location, item.status);
    }

    fclose(fp);
    fclose(temp);

    remove(FILE_NAME);
    rename("temp.txt", FILE_NAME);

    if (found)
        printf("Item marked as resolved.\n");
    else
        printf("No item found with that ID.\n");
}

int main(void) {
    int choice;

    do {
        printf("\n======= CAMPUS LOST & FOUND SYSTEM =======\n");
        printf("1. Report Lost/Found Item\n");
        printf("2. View All Reports\n");
        printf("3. Search for an Item\n");
        printf("4. Mark Item as Resolved\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addItem(); break;
            case 2: viewItems(); break;
            case 3: searchItem(); break;
            case 4: markResolved(); break;
            case 5: printf("\nThank you for using the system!\n"); break;
            default: printf("\nInvalid choice. Try again.\n");
        }
    } while (choice != 5);

    return 0;
}
