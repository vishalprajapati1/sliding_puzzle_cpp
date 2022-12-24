#include "puzzleState.h"
#include <vector>
#include <iostream>

// puzzle class
class PuzzleState {
 using grid = std::vector<std::vector<int>>;
public:
 PuzzleState(grid puzzle, std::pair<int, int> cavity) {
   for (int i = 0; i < puzzle.size(); i++) {
     std::vector<int> row;
     for (int j = 0; j < puzzle.size(); j++) {
       row.push_back(puzzle[i][j]);
     }
     this->puzzle_.emplace_back(std::move(row));
   }
   this->cavity_ = cavity;
 }

  PuzzleState move(int direction) {
   // generates a new puzzle
   PuzzleState state = PuzzleState(this->puzzle_, this->cavity_);
   int &cavity_x = state.cavity_.first, &cavity_y = state.cavity_.second;
   if (direction == 0) {
     std::swap(state.puzzle_[cavity_x][cavity_y],
               state.puzzle_[cavity_x][cavity_y + 1]);
     ++cavity_y;
   }
   if (direction == 1) {
     std::swap(state.puzzle_[cavity_x][cavity_y],
               state.puzzle_[cavity_x][cavity_y - 1]);
     --cavity_y;
   }
   if (direction == 2) {  // up
     std::swap(state.puzzle_[cavity_x][cavity_y],
               state.puzzle_[cavity_x + 1][cavity_y]);
     ++cavity_x;
   }
   if (direction == 3) {  // down
     std::swap(state.puzzle_[cavity_x][cavity_y],
               state.puzzle_[cavity_x - 1][cavity_y]);
     --cavity_x;
   }

   return state;
 }

 PuzzleState(int size) { 
   // generates a solved puzzle of size n
   int current_tile = 1;
   for (int i = 0; i < size; i++) {
     std::vector<int> row;
     for (int j = 0; j < size; j++) {
       row.push_back(current_tile++);
     }
     puzzle_.emplace_back(std::move(row));
   }
   puzzle_.back().back() = 0;
   cavity_.first = size - 1, cavity_.second = size - 1;
 }

 void print() const { 
   std::cout << "\n\n";
   for (auto& row : puzzle_) {
     for (auto tile : row) {
       if (tile != 0)
         std::cout << tile << ' ';
       else
         std::cout << "  ";
     }
     std::cout << '\n';
   }
 }

 bool validMove(int move) {
   // 0 for left, 1 for right, 2 for up, 3 for down
   int cavity_x = cavity_.first;
   int cavity_y = cavity_.second;
   if (move == 0) {
     if (cavity_y < puzzle_.size() - 1) return true;
   }

   if (move == 1) {
     if (cavity_y > 0) return true;
   }

   if (move == 2) {
     if (cavity_x < puzzle_.size() - 1) return true;
   }

   if (move == 3) {
     if (cavity_x > 0) return true;
   }

   return false;
 }
 bool isSolved() { 
   if (puzzle_.back().back() != 0) return false;
   int expected_tile = 1;
   for (int i = 0; i < puzzle_.size(); i++) {
     for (int j = 0; j < puzzle_.size(); j++) {
       if (i == puzzle_.size() - 1 && j == puzzle_.size() - 1) continue;
       if (puzzle_[i][j] != expected_tile) return false;
       ++expected_tile;
     }
   }

   return true;
 }

 int size() const { return puzzle_.size(); }

 bool operator==(const PuzzleState& state) const {
   for (int i = 0; i < this->puzzle_.size(); i++) {
     for (int j = 0; j < this->puzzle_.size(); j++) {
       if (this->puzzle_[i][j] != state.puzzle_[i][j]) return false;
     }
   }
   return true;
 }

 struct custom_hash {

 std::size_t operator()(const PuzzleState& p) const {
   // https://stackoverflow.com/a/2595226 <- About combining hash value
   std::size_t hash = 0;
   std::hash<int> hasher;
   for (auto& row : p.puzzle_) {
     for (auto tile : row) {
       hash ^= hasher(tile) + 0x9e3779b9 + (hash << 6) + (hash >> 2);
     }
   }
   return hash;
  }
 };

private:
 grid puzzle_;
 std::pair<int, int> cavity_;
};
