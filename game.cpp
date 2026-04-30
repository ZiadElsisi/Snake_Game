#include "Game.h"

// ── Constructor ───────────────────────────────────────────────────────────────
Game::Game()
    : currentDir_(Direction::RIGHT)
    , pendingDir_(Direction::RIGHT)
    , state_(GameState::MENU)
    , score_(0)
    , highScore_(0)
    , ticksSinceSpecial_(0)
{
    reset();
}

// ── Reset ─────────────────────────────────────────────────────────────────────
void Game::reset()
{
    snake_       = Snake();
    food_        = Food();
    specialFood_ = SpecialFood();
    level_       = LevelManager();
    obstacles_.clear();
    obstacles_         = level_.getObstacles();
    currentDir_        = Direction::RIGHT;
    pendingDir_        = Direction::RIGHT;
    dirBuffer_.clear();
    score_             = 0;
    ticksSinceSpecial_ = 0;
    state_             = GameState::PLAYING;
    food_.respawn(snake_.getBody(), Constants::GRID_WIDTH, Constants::GRID_HEIGHT);
}

// ── Accessors ─────────────────────────────────────────────────────────────────
GameState                Game::getState()           const { return state_; }
const Body&              Game::getSnakeBody()        const { return snake_.getBody(); }
Cell                     Game::getFoodPos()          const { return food_.getPosition(); }
bool                     Game::specialFoodActive()   const { return specialFood_.isActive(); }
Cell                     Game::getSpecialFoodPos()   const { return specialFood_.getPosition(); }
float                    Game::getSpecialFoodTime()  const { return specialFood_.getTimeLeft(); }
int                      Game::getScore()            const { return score_; }
int                      Game::getLevel()            const { return level_.getLevel(); }
const std::vector<Cell>& Game::getObstacles()        const { return obstacles_; }
int                      Game::getHighScore()        const { return highScore_; }
void                     Game::setHighScore(int hs)        { highScore_ = hs; }
void                     Game::setState(GameState s)       { state_ = s; }

// ── Direction input ───────────────────────────────────────────────────────────
void Game::setDirection(Direction d)
{
    Direction last = dirBuffer_.empty() ? currentDir_ : dirBuffer_.back();
    if (!validateDirection(d, last)) return;
    if (dirBuffer_.size() < 2)
        dirBuffer_.push_back(d);
}

bool Game::validateDirection(Direction next, Direction current)
{
    if (next == Direction::UP    && current == Direction::DOWN)  return false;
    if (next == Direction::DOWN  && current == Direction::UP)    return false;
    if (next == Direction::LEFT  && current == Direction::RIGHT) return false;
    if (next == Direction::RIGHT && current == Direction::LEFT)  return false;
    return true;
}

// ── Update (one game tick) ────────────────────────────────────────────────────
void Game::update()
{
    if (state_ != GameState::PLAYING) return;

    // 1. Pop next direction from buffer
    if (!dirBuffer_.empty()) {
        currentDir_ = dirBuffer_.front();
        dirBuffer_.pop_front();
    }

    // 2. Compute next head
    Cell head = snake_.getHead();
    if      (currentDir_ == Direction::UP)    head.second -= 1;
    else if (currentDir_ == Direction::DOWN)  head.second += 1;
    else if (currentDir_ == Direction::LEFT)  head.first  -= 1;
    else if (currentDir_ == Direction::RIGHT) head.first  += 1;

    // 3. Boundary collision
    if (head.first  < 0 || head.first  >= Constants::GRID_WIDTH  ||
        head.second < 0 || head.second >= Constants::GRID_HEIGHT)
    {
        state_ = GameState::GAME_OVER;
        if (score_ > highScore_) highScore_ = score_;
        return;
    }

    // 4. Obstacle collision
    for (const Cell& obs : obstacles_) {
        if (head == obs) {
            state_ = GameState::GAME_OVER;
            if (score_ > highScore_) highScore_ = score_;
            return;
        }
    }

    // 5. Self-collision (containsCell checks entire body incl. head,
    //    but head hasn't moved yet so current head == old head position,
    //    which is safe — only a true overlap with body segments matters)
    if (snake_.containsCell(head)) {
        state_ = GameState::GAME_OVER;
        if (score_ > highScore_) highScore_ = score_;
        return;
    }

    // 6. Special food
    if (specialFood_.isActive() && head == specialFood_.getPosition()) {
        score_ += 2;
        snake_.grow(currentDir_);
        specialFood_.deactivate();
    }
    // 7. Normal food
    else if (head == food_.getPosition()) {
        score_ += 1;
        snake_.grow(currentDir_);
        food_.respawn(snake_.getBody(), Constants::GRID_WIDTH, Constants::GRID_HEIGHT);
        bool levelChanged = level_.update(score_);
        if (levelChanged)
            obstacles_ = level_.getObstacles();
    }
    // 8. Normal move
    else {
        snake_.move(currentDir_);
    }

    // 9. Tick special food timer
    specialFood_.tick();

    // 10. Spawn special food every 10 ticks
    ++ticksSinceSpecial_;
    if (!specialFood_.isActive() && ticksSinceSpecial_ >= 10) {
        specialFood_.spawn(snake_.getBody(), Constants::GRID_WIDTH, Constants::GRID_HEIGHT);
        ticksSinceSpecial_ = 0;
    }
}
