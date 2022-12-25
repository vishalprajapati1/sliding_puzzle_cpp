#pragma once
#include <vector>

// puzzle class
class PuzzleState {
 using grid = std::vector<std::vector<int>>;
public:
 PuzzleState(grid puzzle, std::pair<int, int> cavity);
 PuzzleState move(int direction);
 PuzzleState(int size);
 void print() const;
 bool validMove(int move);
 bool isSolved();
 int size() const;
 bool operator==(const PuzzleState& state) const;

 struct custom_hash {
  std::size_t operator()(const PuzzleState& p) const;
 };

private:
 grid puzzle_;
 std::pair<int, int> cavity_;
};