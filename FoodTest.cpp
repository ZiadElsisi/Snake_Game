// #include "Food.h"
// #include "SpecialFood.h"
// #include <cassert>
// #include <iostream>
// #include <set>
//
// void testFoodNeverSpawnsOnSnakeBody() {
//     std::cout << "Test: Food never spawns on a given body... ";
//
//     Food food;  // Create a Food instance to test
//     Body snakeBody;
//     snakeBody.push_back({5, 5});
//     snakeBody.push_back({5, 6});
//     snakeBody.push_back({5, 7});
//
//     int gridW = 10;
//     int gridH = 10;
//
//     // Respawn multiple times and verify position is never in snakeBody
//     for (int i = 0; i < 10; ++i) {
//         food.respawn(snakeBody, gridW, gridH);
//
//         assert(food.isActive() == true);
//
//         Cell pos = food.getPosition();
//         bool foundInBody = false;
//         for (const auto& segment : snakeBody) {
//             if (segment == pos) {
//                 foundInBody = true;
//                 break;
//             }
//         }
//         assert(foundInBody == false);
//     }
//
//     std::cout << "PASSED\n";
// }
//
// void testSpecialFoodDeactivatesAfterLifetime() {
//     std::cout << "Test: SpecialFood deactivates after lifetime expires... ";
//
//     SpecialFood specialFood;
//     Body emptyBody;
//     int gridW = 10;
//     int gridH = 10;
//
//     // Spawn special food
//     specialFood.spawn(emptyBody, gridW, gridH);
//     assert(specialFood.isActive() == true);
//     assert(specialFood.getRemainingTime() == SpecialFood::LIFETIME);
//
//     // Tick halfway through lifetime
//     specialFood.tick(SpecialFood::LIFETIME / 2.0f);
//     assert(specialFood.isActive() == true);
//     float remainingAfterHalf = specialFood.getRemainingTime();
//     assert(remainingAfterHalf > 0.0f);
//     assert(remainingAfterHalf < SpecialFood::LIFETIME);
//
//     // Tick remaining time (plus a bit more to ensure deactivation)
//     specialFood.tick(remainingAfterHalf + 0.1f);
//     assert(specialFood.isActive() == false);
//     assert(specialFood.getRemainingTime() <= 0.0f);
//
//     std::cout << "PASSED\n";
// }
//
// void testRespawnWorksOnEmptyBody() {
//     std::cout << "Test: respawn() works on empty body... ";
//
//     Food food;
//     Body emptyBody;
//     int gridW = 20;
//     int gridH = 20;
//
//     // Should be able to respawn multiple times on empty body
//     for (int i = 0; i < 5; ++i) {
//         food.respawn(emptyBody, gridW, gridH);
//
//         assert(food.isActive() == true);
//
//         Cell pos = food.getPosition();
//         assert(pos.first >= 0 && pos.first < gridW);
//         assert(pos.second >= 0 && pos.second < gridH);
//     }
//
//     std::cout << "PASSED\n";
// }
//
// void testFoodInitialization() {
//     std::cout << "Test: Food initialization... ";
//
//     Food food;
//     assert(food.isActive() == false);
//
//     Cell pos = food.getPosition();
//     assert(pos.first == 0 && pos.second == 0);
//
//     std::cout << "PASSED\n";
// }
//
// void testSpecialFoodInitialization() {
//     std::cout << "Test: SpecialFood initialization... ";
//
//     SpecialFood specialFood;
//     assert(specialFood.isActive() == false);
//     assert(specialFood.getRemainingTime() == 0.0f);
//     assert(SpecialFood::POINTS == 2);
//     assert(SpecialFood::LIFETIME == 5.0f);
//
//     Cell pos = specialFood.getPosition();
//     assert(pos.first == 0 && pos.second == 0);
//
//     std::cout << "PASSED\n";
// }
//
// void testSpecialFoodDeactivateMethod() {
//     std::cout << "Test: SpecialFood deactivate() method... ";
//
//     SpecialFood specialFood;
//     Body emptyBody;
//     int gridW = 10;
//     int gridH = 10;
//
//     specialFood.spawn(emptyBody, gridW, gridH);
//     assert(specialFood.isActive() == true);
//
//     specialFood.deactivate();
//     assert(specialFood.isActive() == false);
//     assert(specialFood.getRemainingTime() == 0.0f);
//
//     std::cout << "PASSED\n";
// }
//
// void testFoodPositionsAreDifferent() {
//     std::cout << "Test: Food respawns in different positions... ";
//
//     Food food;
//     Body emptyBody;
//     int gridW = 20;
//     int gridH = 20;
//
//     std::set<Cell> positions;
//
//     // Spawn 50 times and collect positions
//     for (int i = 0; i < 50; ++i) {
//         food.respawn(emptyBody, gridW, gridH);
//         positions.insert(food.getPosition());
//     }
//
//     // With 50 spawns on a 20x20 grid, we should have multiple different positions
//     // (probability of all same position is astronomically low)
//     assert(positions.size() > 1);
//
//     std::cout << "PASSED\n";
// }
//
// int main() {
//     std::cout << "========== Food Tests ==========\n";
//
//     try {
//         testFoodInitialization();
//         testSpecialFoodInitialization();
//         testRespawnWorksOnEmptyBody();
//         testFoodNeverSpawnsOnSnakeBody();
//         testSpecialFoodDeactivatesAfterLifetime();
//         testSpecialFoodDeactivateMethod();
//         testFoodPositionsAreDifferent();
//
//         std::cout << "\n========== ALL TESTS PASSED ==========\n";
//         return 0;
//     } catch (const std::exception& e) {
//         std::cerr << "Test failed with exception: " << e.what() << "\n";
//         return 1;
//     }
// }
