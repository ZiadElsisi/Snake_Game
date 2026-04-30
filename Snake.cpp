#include "Snake.h"

using namespace std;

Snake::Snake()
{
    reset();
}

void Snake::reset()
{

    body_.clear();

    int start_x = GRID_WIDTH / 2;
    int start_y = GRID_HEIGHT / 2;

    body_.push_back({start_x, start_y});

    body_.push_back({start_x - 1, start_y});
    body_.push_back({start_x - 2, start_y});
}

void Snake::computeNextHead(Direction d, Cell &out) const
{

    Cell currentHead = body_.front();
    out = currentHead;

    switch (d)
    {
    case Direction::UP:
        out.y--;
        break;
    case Direction::DOWN:
        out.y++;
        break;
    case Direction::LEFT:
        out.x--;
        break;
    case Direction::RIGHT:
        out.x++;
        break;
    }
}

void Snake::grow(Direction d)
{

    Cell nextHead;

    computeNextHead(d, nextHead);

    body_.push_front(nextHead);
}

Cell Snake::getHead() const
{
    return body_.front();
}

const Body &Snake::getBody() const
{
    return body_;
}

bool Snake::containsCell(const Cell &c) const
{

    for (const auto &segment : body_)
    {

        if (segment.x == c.x && segment.y == c.y)
        {

            return true;
        }
    }

    return false;
}

int Snake::length() const
{
    return static_cast<int>(body_.size());
}