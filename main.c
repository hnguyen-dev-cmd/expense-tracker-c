// Expense Tracker in C
#include <stdio.h>
#include <string.h>

typedef struct {
    char description[100];
    float amount;
} Expense;

void delete_expense(Expense expenses[], int *count, float *total) {
    if (*count == 0) {
        printf("🚫 No expenses to delete.\n");
        return;
    }

    printf("\n📋 Expenses:\n");
    for (int i = 0; i < *count; i++) {
        printf("%d. %-20s $%.2f\n", i + 1, expenses[i].description, expenses[i].amount);
    }

    printf("\nWhich expense do you want to delete? (Enter #): ");
    int index;
    if (scanf("%d", &index) != 1 || index < 1 || index > *count) {
        printf("❌ Invalid selection.\n");
        while (getchar() != '\n');
        return;
    }

    index--; // Convert to 0-based index
    printf("✅ Deleted: %s - $%.2f\n", expenses[index].description, expenses[index].amount);

    *total -= expenses[index].amount;

    // Shift all items after index left by one
    for (int i = index; i < *count - 1; i++) {
        expenses[i] = expenses[i + 1];
    }
    (*count)--;

    // Rewrite the file with updated data
    FILE *file = fopen("expenses.txt", "w"); // Overwrite
    if (file == NULL) {
        printf("❌ Error updating file!\n");
        return;
    }
    for (int i = 0; i < *count; i++) {
        fprintf(file, "%-20s $%.2f\n", expenses[i].description, expenses[i].amount);
    }
    fclose(file);
}


int main() {
    Expense expenses[100];  // Array to hold up to 100 expenses
    int count = 0;          // Number of expenses loaded
    char description[100];
    float amount;
    float total = 0.0;

    FILE *file = fopen("expenses.txt", "a+"); // a+ = read + append
    if (file == NULL) {
        printf("❌ Error opening file!\n");
        return 1;
    }
    rewind(file); // Go to start of file

    while (fscanf(file, "%99[^$] $%f\n", expenses[count].description, &expenses[count].amount) == 2) {
        count++;
    }

     printf("📂 Previous Expenses:\n");
     for (int i = 0; i < count; i++) {
         printf("📝 %-20s $%.2f\n", expenses[i].description, expenses[i].amount);
         total += expenses[i].amount;
    }
    printf("💸 Current total before new entries: $%.2f\n\n", total);

    // Input new expenses
    printf("=== Expense Tracker ===\n");
    printf("Type 'exit' as description to quit.\n\n");
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
	while (getchar() != '\n')
		;
        continue;
        }

        printf("Enter amount: $");
        if (scanf("%f", &amount) != 1) {
            printf("Invalid input. Please enter a number.\n");
            while (getchar() != '\n');
            continue;
        }

        total += amount;

        strcpy(expenses[count].description, description);
        expenses[count].amount = amount;
        count++;

        // Save to file
        fprintf(file, "%-20s $%.2f\n", description, amount);
        fflush(file); // ensure it's written

        printf("✅ Added: %-20s $%.2f\n\n", description, amount);

        while (getchar() != '\n');
    }

    fclose(file);

    printf("\n📋 Final Expense List:\n");
    float finalTotal = 0.0;

    for (int i = 0; i < count; i++) {
        printf("🔸 %-20s $%.2f\n", expenses[i].description, expenses[i].amount);
        finalTotal += expenses[i].amount;
    }

    printf("\n📊 Final total: $%.2f\n", finalTotal);

    printf("💾 All expenses saved in 'expenses.txt'\n");

    return 0;
}
