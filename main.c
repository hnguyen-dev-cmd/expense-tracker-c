// Expense Tracker in C
#include <stdio.h>

#define MAX_EXPENSES 100

struct Expense {
    char description[100];
    float amount;
};

int main() {
    struct Expense expenses[MAX_EXPENSES];
    int count = 0;

    char desc[100];
    float amt;

    printf("Enter expense description: ");
    fgets(desc, sizeof(desc), stdin);

    printf("Enter amount: $");
    scanf("%f", &amt);

    // Store the expense
    snprintf(expenses[count].description, sizeof(expenses[count].description), "%s", desc);
    expenses[count].amount = amt;
    count++;

    printf("✅ Expense added: %s - $%.2f\n", expenses[0].description, expenses[0].amount);

    return 0;
}
