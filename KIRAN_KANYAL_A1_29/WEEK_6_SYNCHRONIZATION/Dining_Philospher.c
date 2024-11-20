#include <stdio.h>

// Arrays to represent philosophers and chopstick status
int p[5];  // Philosopher states: 0 = Thinking, 1 = Eating
int ch[5]; // Chopstick states: 0 = Free, 1 = In use

// Function to release chopsticks (signal)
void signal(int y) {
    int right = (y + 1) % 5;
    p[y] = 0;        // Philosopher stops eating
    ch[y] = 0;       // Left chopstick is released
    ch[right] = 0;   // Right chopstick is released
}

// Function to acquire chopsticks (wait)
void wait(int y) {
    int right = (y + 1) % 5;

    // Check if both chopsticks are free
    if (ch[y] == 0 && ch[right] == 0) {
        p[y] = 1;       // Philosopher starts eating
        ch[y] = 1;      // Mark left chopstick as in use
        ch[right] = 1;  // Mark right chopstick as in use
    } else if (p[y] == 1) {
        // Philosopher is already eating
        int w;
        printf("Do you want philosopher %d to stop eating? (1 for Yes, 0 for No): ", y);
        scanf("%d", &w);
        if (w == 1) {
            signal(y); // Release chopsticks
        }
    } else {
        // Chopsticks are busy, philosopher has to wait
        printf("Chopsticks %d and %d are busy.\n", y, right);
        printf("Philosopher %d has to wait.\n", y);
    }
}

int main() {
    int u; // Continue flag

    // Initialize philosophers and chopsticks
    for (int i = 0; i < 5; i++) {
        p[i] = 0;  // All philosophers start thinking
        ch[i] = 0; // All chopsticks are free
    }

    do {
        // Print the current state of philosophers
        for (int i = 0; i < 5; i++) {
            if (p[i] == 0) {
                printf("Philosopher %d: Thinking\n", i);
            } else {
                printf("Philosopher %d: Eating\n", i);
            }
        }

        int s;
        printf("Which philosopher wants to eat? (Enter 0-4): ");
        scanf("%d", &s);
        if (s >= 0 && s < 5) {
            wait(s); // Attempt to make the selected philosopher eat
        } else {
            printf("Invalid input. Please enter a number between 0 and 4.\n");
        }

        printf("\nDo you want to continue? (1 for Yes, 0 for No): ");
        scanf("%d", &u);
    } while (u == 1);

    return 0;
}
