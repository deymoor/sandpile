#include "Stack.h"

bool Stack::IsEmpty() {
    return (this->head == nullptr || this->tail == nullptr);
}

void Stack::PushEmpty(Node* node) {
    this->head = node;
    this->tail = node;
}

void Stack::PushBack(Triple* triple_temp) {
    Node* node = new Node();
    auto triple = new Triple();
    triple->x = triple_temp->x;
    triple->y = triple_temp->y;
    triple->elem = triple_temp->elem;
    node->triple = triple;
    if (IsEmpty()) {
        PushEmpty(node);
        return;
    }
    node->prev = this->tail;
    this->tail->next = node;
    this->tail = node;
}

Triple* Stack::PopBack() {
    if (IsEmpty()) {
        ThrowError("Stack is empty!");
    }
    auto triple = new Triple();
    triple->x = this->tail->triple->x;
    triple->y = this->tail->triple->y;
    triple->elem = this->tail->triple->elem;
    this->tail = this->tail->prev;
    if (IsEmpty()) {
        delete this->head;
        this->head = nullptr;
        return triple;
    }
    delete this->tail->next;
    this->tail->next = nullptr;
    return triple;
}