#include <iostream>
#include <vector>
#include "Library/puzzleState.h"
#include "Library/puzzleSolver.h"

PuzzleState getState(int size);

int main() { 
  int dimension;
  std::cout << "Enter dimension: "; 
  std::cin >> dimension;
  std::cout << "\n\nInput puzzle (Use 0 for cavity):\n\n";
  PuzzleState puzzle = getState(dimension);
  std::cout << "\n\n";
  Puzzle::solveAndPrint(puzzle);
  //
}

PuzzleState getState(int size) { 
  std::vector<std::vector<int>> grid;
  std::pair<int, int> cavity;
  
  for (int i = 0; i < size; i++) {
    std::vector<int> row;
    for (int j = 0; j < size; j++) {
      int tile;
      std::cin >> tile;
      if (tile == 0) {
        cavity.first = i;
        cavity.second = j;
      }
      row.push_back(tile);
    }
    grid.emplace_back(std::move(row));
  }

  PuzzleState puzzle(grid, cavity); 
  return puzzle;
}