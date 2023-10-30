#pragma once
#include "../../utils/utils.h"
#include <iostream>


struct Triple {
    uint64_t elem = 0;
    uint16_t x = 0;
    uint16_t y = 0;
};

struct Node {
    Triple triple;
    Node* next;
    Node* prev;

    Node() {
        next = nullptr;
        prev = nullptr;
    }
};

struct Stack {
    Node* head;
    Node* tail;

    Stack() {
        head = nullptr;
        tail = nullptr;
    }

    ~Stack() {
        while (!this->IsEmpty()) {
            tail = tail->prev;
            if (IsEmpty()) {
                delete head;
                head = nullptr;
            } else {
                delete tail->next;
                tail->next = nullptr;
            }
        }
    }

    bool IsEmpty();

    void PushEmpty(Node* node);

    void PushBack(Triple& triple);

    Triple PopBack();
};
