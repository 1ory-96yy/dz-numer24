#include <iostream>
#include <stdexcept>

class Node {
public:
    int data;
    Node* prev;
    Node* next;

    Node(int value) : data(value), prev(nullptr), next(nullptr) {}
};

class DoublyLinkedList {
private:
    Node* head;
    Node* tail;

public:
    DoublyLinkedList() : head(nullptr), tail(nullptr) {}

    ~DoublyLinkedList() {
        Node* current = head;
        while (current) {
            Node* next = current->next;
            delete current;
            current = next;
        }
        head = tail = nullptr;
    }

    bool isEmpty() const {
        return head == nullptr;
    }

    void append(int value) {
        Node* newNode = new Node(value);
        if (isEmpty()) {
            head = tail = newNode;
        }
        else {
            newNode->prev = tail;
            tail->next = newNode;
            tail = newNode;
        }
    }

    void deleteNode(int value) {
        if (isEmpty()) {
            throw std::runtime_error("Cannot delete from empty list");
        }

        Node* current = head;
        while (current) {
            if (current->data == value) {
                if (current->prev) {
                    current->prev->next = current->next;
                }
                if (current->next) {
                    current->next->prev = current->prev;
                }
                if (current == head) {
                    head = current->next;
                }
                if (current == tail) {
                    tail = current->prev;
                }
                delete current;
                return;
            }
            current = current->next;
        }

        throw std::runtime_error("Value not found in the list");
    }

    void printList() const {
        Node* current = head;
        while (current) {
            std::cout << current->data << " ";
            current = current->next;
        }
        std::cout << std::endl;
    }
};

int main() {
    DoublyLinkedList dll;

    try {
        dll.append(1);
        dll.append(2);
        dll.append(3);

        dll.deleteNode(2);
        dll.deleteNode(4);
    }
    catch (const std::runtime_error& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    dll.printList();

    return 0;
}
