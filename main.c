// Expense Tracker in C
#include <stdio.h>
#include <string.h>
#include <time.h>

typedef struct {
    char description[100];
    float amount;
    char timestamp[30];
} Expense;

void delete_expense(Expense expenses[], int *count, float *total) {
    if (*count == 0) {
        printf("🚫 No expenses to delete.\n");
        return;
    }

    printf("\n📋 Expenses:\n");
    for (int i = 0; i < *count; i++) {
        printf("%d. %-20s $%.2f [%s]\n", i + 1, expenses[i].description, expenses[i].amount, expenses[i].timestamp);
    }

    printf("\nWhich expense do you want to delete? (Enter #): ");
    int index;
    if (scanf("%d", &index) != 1 || index < 1 || index > *count) {
        printf("❌ Invalid selection.\n");
        while (getchar() != '\n');
        return;
    }

    index--; // Convert to 0-based index

    printf("✅ Deleted: %s - $%.2f [%s]\n", 
        expenses[index].description, 
        expenses[index].amount, 
        expenses[index].timestamp);

    *total -= expenses[index].amount;

    // Shift all items after index left by one
    for (int i = index; i < *count - 1; i++) {
        expenses[i] = expenses[i + 1];
    }
    (*count)--;

    // Rewrite the file with updated expenses
    FILE *file = fopen("expenses.txt", "w");
    if (file == NULL) {
        printf("❌ Error rewriting file!\n");
        return;
    }

    *total = 0.0;
    for (int i = 0; i < *count; i++) {
        fprintf(file, "%-20s $%.2f %s\n", 
            expenses[i].description, 
            expenses[i].amount, 
            expenses[i].timestamp);
        *total += expenses[i].amount;
    }

    fclose(file);
    printf("\n💾 File updated successfully after deletion!\n");
    printf("📊 New total: $%.2f\n", *total);
}

void sortExpenses(Expense expenses[], int count) {
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (expenses[j].amount > expenses[j + 1].amount) {
                Expense temp = expenses[j];
                expenses[j] = expenses[j + 1];
                expenses[j + 1] = temp;
            }
        }
    }
}

int main() {
    Expense expenses[100];
    int count = 0;
    float total = 0.0;
    char description[100];
    float amount;

    FILE *file = fopen("expenses.txt", "a+");
    if (file == NULL) {
        printf("❌ Error opening file!\n");
        return 1;
    }

    rewind(file); // Read from start

    while (fscanf(file, "%99[^$] $%f %[^\n]\n", 
        expenses[count].description, 
        &expenses[count].amount, 
        expenses[count].timestamp) == 3) {
        total += expenses[count].amount;
        count++;
    }

    printf("📂 Previous Expenses:\n");
    for (int i = 0; i < count; i++) {
        printf("📝 %-20s $%.2f [%s]\n", 
            expenses[i].description, 
            expenses[i].amount, 
            expenses[i].timestamp);
    }

    printf("💸 Current total before new entries: $%.2f\n\n", total);

    printf("=== Expense Tracker ===\n");
    printf("Type 'exit' as description to quit.\n");
    printf("Type 'delete' as description to delete an expense.\n\n");

    while (count < 100) {
        printf("Enter description: ");
        fgets(description, sizeof(description), stdin);
        description[strcspn(description, "\n")] = 0;

        if (strcmp(description, "exit") == 0) {
            break;
        }

        if (strcmp(description, "delete") == 0) {
            delete_expense(expenses, &count, &total);
            while (getchar() != '\n');
            continue;
        }

        // Get current time
        time_t now = time(NULL);
        struct tm *t = localtime(&now);
        char currentTime[30];
        strftime(currentTime, sizeof(currentTime), "%Y-%m-%d %I:%M %p", t);

        printf("Enter amount: $");
        if (scanf("%f", &amount) != 1) {
            printf("❌ Invalid input. Please enter a number.\n");
            while (getchar() != '\n');
            continue;
        }

        strcpy(expenses[count].description, description);
        expenses[count].amount = amount;
        strcpy(expenses[count].timestamp, currentTime);

        total += amount;
        count++;

        fprintf(file, "%-20s $%.2f %s\n", description, amount, currentTime);
        fflush(file);

        printf("✅ Added: %-20s $%.2f [%s]\n\n", description, amount, currentTime);

        while (getchar() != '\n');
    }

    fclose(file);

    sortExpenses(expenses, count);

    printf("\n📋 Final Expense List:\n");
    float finalTotal = 0.0;

    for (int i = 0; i < count; i++) {
        printf("🔸 %-20s $%.2f [%s]\n", 
            expenses[i].description, 
            expenses[i].amount, 
            expenses[i].timestamp);
        finalTotal += expenses[i].amount;
    }

    printf("\n📊 Final total: $%.2f\n", finalTotal);
    printf("💾 All expenses saved in 'expenses.txt'\n");

    return 0;
}
