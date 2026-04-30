#ifndef SNAKE_H
#define SNAKE_H

#include <deque>
#include <algorithm>
#include "Shared.h"

class Snake
{
public:
    Snake();

    void reset();

    void move(Direction d); // push_front newHead, pop_back tail

    void grow(Direction d); // push_front newHead, no pop_back

    Cell getHead() const;

    const Body &getBody() const;

    bool containsCell(const Cell &c) const; // O(n) linear search

    int length() const;

private:
    Body body_;
    void computeNextHead(Direction d, Cell &out) const;
};

#endif
