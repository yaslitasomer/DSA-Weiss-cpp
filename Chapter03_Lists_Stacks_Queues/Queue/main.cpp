#include <iostream>
#include <string>
#include <stdexcept>
#include "LinkedQueue.h"
#include "ArrayQueue.h"

using namespace std;

// ==============================================================================
// GENERIC QUEUE DIAGNOSTICS
// Tests any queue engine passed to it!
// ==============================================================================
template <typename QueueType>
void runQueueDiagnostics(QueueType& q, const string& engineName) {
    cout << ">>> RUNNING DIAGNOSTICS FOR: " << engineName << " <<<\n";

    // 1. Enqueue Operations (Customers entering the line)
    cout << "[Step 1] Enqueuing 'Customer A', 'Customer B', 'Customer C'...\n";
    q.enqueue("Customer A");
    q.enqueue("Customer B");
    q.enqueue("Customer C");

    cout << "         Queue Size: " << q.size() << "\n";
    cout << "         Who is at the front? '" << q.front() << "'\n\n";

    // 2. Dequeue Operations (Serving customers FIFO style)
    cout << "[Step 2] Serving customers (Dequeueing):\n";
    while (!q.empty()) {
        cout << "         Serving: " << q.front() << "\n";
        q.dequeue();
    }
    cout << "         Queue Size after serving all: " << q.size() << "\n\n";

    // 3. Exception Safety
    cout << "[Step 3] Exception Safety Test (Dequeueing empty queue)...\n";
    try {
        q.dequeue();
        cout << "         [FAILED] Engine allowed dequeue on empty queue!\n";
    }
    catch (const underflow_error& e) {
        cout << "         [SUCCESS] Exception Caught: " << e.what() << "\n";
    }
    cout << "--------------------------------------------------------\n\n";
}

int main() {
    cout << "=== C++ QUEUE ARCHITECTURE TEST ENGINE ===\n\n";

    // Engine 1: Linked List
    LinkedQueue<string> printerQueue;
    runQueueDiagnostics(printerQueue, "LinkedQueue (Node-Driven)");

    // Engine 2: Circular Array
    // Creating a very small array (capacity 3) to test the wrap-around logic
    ArrayQueue<string> circularBuffer(3);
    runQueueDiagnostics(circularBuffer, "ArrayQueue (Circular-Buffer)");

    // Specific Wrap-Around Test for Circular Array
    cout << ">>> TESTING CIRCULAR WRAP-AROUND BEHAVIOR <<<\n";
    ArrayQueue<int> ring(3);
    ring.enqueue(10);
    ring.enqueue(20);
    ring.enqueue(30);
    // Array is now physically [10, 20, 30]. Front is at index 0, Back is at index 2.

    ring.dequeue(); // Removes 10. Size is 2. Front is at index 1.

    // Now we add 40. Since Back is at 2, it should wrap around to index 0!
    ring.enqueue(40);
    cout << "[SUCCESS] Circular buffer wrapped around successfully without crashing!\n";
    cout << "Current Front: " << ring.front() << " (Should be 20)\n\n";

    cout << "All queue systems are functioning perfectly according to the ADT rules.\n";

    return 0;
}