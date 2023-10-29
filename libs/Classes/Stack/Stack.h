#pragma once
#include "../../utils/utils.h"
#include <iostream>


struct Triple {
    uint64_t elem = 0;
    uint16_t x = 0;
    uint16_t y = 0;
};

struct Node {
    Triple* triple = nullptr;
    Node* next = nullptr;
    Node* prev = nullptr;

    ~Node() {
        delete this->triple;
    }
};

struct Stack {
    Node* head = nullptr;
    Node* tail = nullptr;

    ~Stack() {
        while (!this->IsEmpty()) {
            this->tail = this->tail->prev;
            if (IsEmpty()) {
                delete this->head;
                this->head = nullptr;
            } else {
                delete this->tail->next;
                this->tail->next = nullptr;
            }
        }
    }

    bool IsEmpty();

    void PushEmpty(Node* node);

    void PushBack(Triple* triple_temp);

    Triple* PopBack();
};
