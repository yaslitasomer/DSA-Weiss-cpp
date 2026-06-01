/*
    The Josephus Problem : 3.6
*/

#include <iostream>
#include "../Queue/ArrayQueue.h"

using namespace std;

// ==============================================================================
// ALGORITHM: THE JOSEPHUS PROBLEM (Queue-based Simulation)
// ==============================================================================
// N: Total number of people (numbered 1 to N)
// M: Number of passes before elimination
// ==============================================================================
int playJosephus(int N, int M) {
    // Edge case safety
    if (N <= 0) return 0;

    ArrayQueue<int> circle;

    // Populate the circle
    for (int i = 1; i <= N; i++) {
        circle.enqueue(i);
    }

    int playersRemaining = N;

    // RUN THE SIMULATION
    cout << "   -> Game Starts! (N = " << N << ", M = " << M << ")\n";

    while (playersRemaining > 1) {
        // PASS THE POTATO 'M' TIMES
        for (int i = 0; i < M; i++) {
            // Take the person at the front and move them to the back
            int personWithPotato = circle.front();
            circle.dequeue();
            circle.enqueue(personWithPotato);
        }

        // THE ELIMINATION
        // After M passes, the person currently at the front holds the potato.
        // We dequeue them, they are OUT
        int eliminatedPerson = circle.front();
        circle.dequeue();
        playersRemaining--;

        cout << "   [ELIMINATED] Player " << eliminatedPerson << " is out! (" << playersRemaining << " left)\n";
    }

    // THE WINNER
    return circle.front();
}

int main() {
    cout << "=== JOSEPHUS PROBLEM DIAGNOSTICS ===\n\n";

    // Scenario 1: M = 0 (Eliminate every immediate next person)
    cout << ">>> SCENARIO 1: N = 5, M = 0 <<<\n";
    int winner1 = playJosephus(5, 0);
    cout << ">>> WINNER: Player " << winner1 << " takes the crown! <<<\n\n";
    cout << "--------------------------------------------------------\n\n";

    // Scenario 2: M = 1 (The classic jump elimination)
    cout << ">>> SCENARIO 2: N = 5, M = 1 <<<\n";
    int winner2 = playJosephus(5, 1);
    cout << ">>> WINNER: Player " << winner2 << " takes the crown! <<<\n\n";
    cout << "--------------------------------------------------------\n\n";

    return 0;
}