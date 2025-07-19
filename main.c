// Expense Tracker in C
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_DESC 100

int main() {
    float amount, total = 0.0;
    char description[MAX_DESC];

    printf("=== Expense Tracker ===\n");
    printf("Type 'exit' as description to quit.\n");

    while (1) {
        printf("\nEnter description: ");
        fgets(description, MAX_DESC, stdin);
        description[strcspn(description, "\n")] = 0; // Remove newline

        if (strcmp(description, "exit") == 0) {
            break;
        }

        printf("Enter amount: $");
        if (scanf("%f", &amount) != 1) {
            printf("Invalid input. Please enter a number.\n");
            while (getchar() != '\n'); // Clear input buffer
            continue;
        }

        total += amount;
        printf("✅ Added: %-20s $%.2f\n", description, amount);
        while (getchar() != '\n'); // Clear input buffer
    }

    printf("\n📊 Total spent: $%.2f\n", total);
    return 0;
}

