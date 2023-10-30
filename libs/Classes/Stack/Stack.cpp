#include "Stack.h"


bool Stack::IsEmpty() {
    return (head == nullptr || tail == nullptr);
}

void Stack::PushEmpty(Node* node) {
    head = node;
    tail = node;
}

void Stack::PushBack(Triple& triple) {
    Node* node = new Node();
    node->triple = triple;
    if (IsEmpty()) {
        PushEmpty(node);
        return;
    }
    node->prev = tail;
    tail->next = node;
    tail = node;
}

Triple Stack::PopBack() {
    if (IsEmpty()) {
        ThrowError("Stack is empty!");
    }
    Triple triple = tail->triple;
    tail = tail->prev;
    if (IsEmpty()) {
        delete head;
        head = nullptr;
        return triple;
    }
    delete tail->next;
    tail->next = nullptr;
    return triple;
}