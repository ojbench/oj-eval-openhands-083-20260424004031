
#include <iostream>
using namespace std;

// Node structure for singly circular linked list
struct Node {
    int value;
    Node* next;
    
    Node(int val) : value(val), next(nullptr) {}
};

class CircularLinkedList {
private:
    Node* head;
    Node* tail;
    int size;
    
public:
    CircularLinkedList() : head(nullptr), tail(nullptr), size(0) {}
    
    ~CircularLinkedList() {
        // Clean up all nodes to prevent memory leaks
        if (head == nullptr) return;
        
        Node* current = head;
        Node* nextNode;
        
        // Break the circular link first
        tail->next = nullptr;
        
        // Delete all nodes
        while (current != nullptr) {
            nextNode = current->next;
            delete current;
            current = nextNode;
        }
    }
    
    // Add a node to the end of the circular list
    void addNode(int value) {
        Node* newNode = new Node(value);
        
        if (head == nullptr) {
            // First node
            head = newNode;
            tail = newNode;
            newNode->next = newNode; // Points to itself
        } else {
            // Add to the end
            tail->next = newNode;
            newNode->next = head;
            tail = newNode;
        }
        size++;
    }
    
    // Remove the m-th node starting from current head position
    // Returns the value of the removed node
    int removeMthNode(int m) {
        if (head == nullptr || size == 0) {
            return -1; // Empty list
        }
        
        if (size == 1) {
            // Only one node left
            int value = head->value;
            delete head;
            head = nullptr;
            tail = nullptr;
            size = 0;
            return value;
        }
        
        // Find the (m-1)-th node (node before the one to be removed)
        // We start counting from head, so we need to move (m-2) steps from head
        Node* prev = head;
        for (int i = 1; i < m - 1; i++) {
            prev = prev->next;
        }
        
        // Node to be removed
        Node* toRemove = prev->next;
        int value = toRemove->value;
        
        // Remove the node
        prev->next = toRemove->next;
        
        // Update head or tail if necessary
        if (toRemove == head) {
            head = toRemove->next;
        }
        if (toRemove == tail) {
            tail = prev;
        }
        
        // The next round should start from the node after the removed one
        head = toRemove->next;
        
        delete toRemove;
        size--;
        
        return value;
    }
    
    // Get current head value
    int getHeadValue() const {
        return (head != nullptr) ? head->value : -1;
    }
    
    // Get current size
    int getSize() const {
        return size;
    }
    
    // Check if list is empty
    bool isEmpty() const {
        return size == 0;
    }
};

int main() {
    int n, m;
    cin >> n >> m;
    
    // Create circular linked list with n nodes
    CircularLinkedList list;
    
    // Add nodes 1 to n
    for (int i = 1; i <= n; i++) {
        list.addNode(i);
    }
    
    // Simulate Josephus Ring elimination
    while (!list.isEmpty()) {
        int removedValue = list.removeMthNode(m);
        cout << removedValue << endl;
    }
    
    return 0;
}
