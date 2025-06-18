#include <stdio.h>

// Function to add numbers to the file
void add_numbers_to_file() {
    FILE *file = fopen("numbers.txt", "w"); // Open in write mode
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    int num;
    printf("Enter numbers to add to the file (-1 to stop):\n");
    while (1) {
        scanf("%d", &num);
        if (num == -1) break;
        fprintf(file, "%d ", num);
    }

    fclose(file);
    printf("Numbers added to the file successfully.\n");
}

// Function to read and print numbers from the file
void read_numbers_from_file() {
    FILE *file = fopen("numbers.txt", "r"); // Open in read mode
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    int num[100];
    int i = 0;
    while (i < 100 && fscanf(file, "%d", &num[i]) == 1) {
        i++;
    }

    fclose(file);

    printf("Numbers in the file:\n");
    for (int j = 0; j < i; j++) {
        printf("%d ", num[j]);
    }
    printf("\n");
}

int main() {
    int choice;
    while (1) {
        printf("1. Add numbers to file\n");
        printf("2. Read numbers from file\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                add_numbers_to_file();
                break;
            case 2:
                read_numbers_from_file();
                break;
            case 3:
                return 0;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}