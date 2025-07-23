// Expense Tracker in C
#include <stdio.h>
#include <string.h>

typedef struct {
    char description[100];
    float amount;
} Expense;

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

    while (1) {
        printf("Enter description: ");
        fgets(description, sizeof(description), stdin);
        description[strcspn(description, "\n")] = 0;

        if (strcmp(description, "exit") == 0) {
            break;
        }

        printf("Enter amount: $");
        if (scanf("%f", &amount) != 1) {
            printf("Invalid input. Please enter a number.\n");
            while (getchar() != '\n');
            continue;
        }

        total += amount;

        // Save to file
        fprintf(file, "%-20s $%.2f\n", description, amount);
        fflush(file); // ensure it's written

        printf("✅ Added: %-20s $%.2f\n\n", description, amount);

        while (getchar() != '\n');
    }

    fclose(file);

    printf("\n📊 Total spent: $%.2f\n", total);
    printf("💾 All expenses saved in 'expenses.txt'\n");

    return 0;
}
