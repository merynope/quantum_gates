#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_DATABASE_SIZE 100

// Function to apply the Pauli X operation to a qubit
void pauliX(int *qubit) {
    // Implement the Pauli X operation logic here
    *qubit = (*qubit == 0) ? 1 : 0;
}

// Function to apply the Pauli Y operation to a qubit
void pauliY(int *qubit) {
    printf("You selected Pauli Y operation.\n");
    // Implement the Pauli Y operation logic here
    *qubit = -(*qubit);
}

// Function to apply the Pauli Z operation to a qubit
void pauliZ(int *qubit) {
    printf("You selected Pauli Z operation.\n");
    // Implement the Pauli Z operation logic here
    *qubit = -(*qubit);
}

// Function to simulate the oracle that marks the target item
int oracle(int target, int guess) {
    return (guess == target) ? 1 : -1;
}

// Function to apply the Grover diffusion operator
void diffusion(int *array, int n) {
    int i;
    int sum = 0;

    for (i = 0; i < n; i++) {
        array[i] = -array[i];
        sum += array[i];
    }

    for (i = 0; i < n; i++) {
        array[i] = 2 * sum - array[i];
    }
}

// Function to perform Grover's algorithm
int groversAlgorithm(int *database, int database_size, int target) {
    int i, guess, count;

    // Perform Grover iterations (approx. sqrt(N) iterations)
    for (count = 0; count < 3; count++) {
        // Oracle phase (mark the target)
        for (i = 0; i < database_size; i++) {
            database[i] *= oracle(target, i);
        }

        // Apply the diffusion operator
        diffusion(database, database_size);
    }

    // Measure the result (maximum amplitude corresponds to the target)
    for (i = 0, guess = 0; i < database_size; i++) {
        if (database[i] > database[guess]) {
            guess = i;
        }
    }

    return guess;
}

int main() {
    int choice;
    int qubit = 0; // Initialize the qubit to |0>
    printf("\n\n");
    do {
        printf("ENTER THE OPERATION TO BE PERFORMED AS PER MENU\n");
        printf("1. PAULI X\n");
        printf("2. PAULI Y\n");
        printf("3. PAULI Z\n");
        printf("4. RANDOM NUMBER GENERATOR\n");
        printf("5. GROVER'S ALGORITHM\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Pauli X Gate Simulation\n");
                printf("Initial qubit state: |%d>\n", qubit);
                pauliX(&qubit);
                printf("Pauli X gate applied. New qubit state: |%d>\n", qubit);
                break;
            case 2:
                printf("Pauli Y Gate Simulation\n");
                printf("Initial qubit state: |%d>\n", qubit);
                pauliY(&qubit);
                printf("Pauli Y gate applied. New qubit state: |%d>\n", qubit);
                break;
            case 3:
                printf("Pauli Z Gate Simulation\n");
                printf("Initial qubit state: |%d>\n", qubit);
                pauliZ(&qubit);
                printf("Pauli Z gate applied. New qubit state: |%d>\n", qubit);
                break;
            case 4:
                srand(time(NULL)); // Seed the random number generator with the current time
                printf("Quantum Random Number Generator using Hadamard Gate\n");
                // Apply Hadamard transformation: |0> -> (|0> + |1>)/sqrt(2), |1> -> (|0> - |1>)/sqrt(2)
                int random_bit = rand() % 2; // Generate a random bit (0 or 1)
                if (random_bit == 0) {
                    // Map |0> to (|0> + |1>)/sqrt(2)
                    qubit = qubit + 1;
                } else {
                    // Map |1> to (|0> - |1>)/sqrt(2)
                    qubit = qubit - 1;
                }
                printf("Random bit generated: %d\n", (qubit + 1) / 2);
                break;
            case 5:
                printf("You selected Grover's Algorithm.\n");
                int database[MAX_DATABASE_SIZE];
                int database_size, target, i;

                // Prompt the user for the size of the database
                printf("Enter the size of the database: ");
                scanf("%d", &database_size);

                // Prompt the user to populate the database
                printf("Enter %d elements for the database:\n", database_size);
                for (i = 0; i < database_size; i++) {
                    scanf("%d", &database[i]);
                }

                // Prompt the user for the target item to search
                printf("Enter the target item to search for: ");
                scanf("%d", &target);

                // Perform Grover's algorithm
                int result = groversAlgorithm(database, database_size, target);

                // Display the result
                printf("Target item %d found at index %d.\n", target, result);
                break;
            
            case 0:
                printf("Exiting the program. Goodbye!\n");
                break;
            default:
                printf("Invalid choice. Please select a valid option.\n");
        }
    } while (choice != 0);

    return 0;
}
