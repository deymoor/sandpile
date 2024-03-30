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
    node->next = tail;
    tail->prev = node;
    tail = node;
}

Triple Stack::PopBack() {
    if (IsEmpty()) {
        ThrowError("Stack is empty!");
    }
    Triple triple = tail->triple;
    tail = tail->next;
    if (IsEmpty()) {
        delete head;
        head = nullptr;
        return triple;
    }
    delete tail->prev;
    tail->prev = nullptr;
    return triple;
}