#include <iostream>
#include "Library/puzzleGenerator.h"

int main() { 
  int dimension, moves;
  std::cout << "Enter dimension: ";
  std::cin >> dimension;
  std::cout << "\n# moves to solve generated puzzle: ";
  std::cin >> moves;

  Puzzle::generateAndPrint(dimension, moves);
}