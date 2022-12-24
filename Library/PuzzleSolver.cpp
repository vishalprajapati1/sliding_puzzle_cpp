#include "puzzleState.h"
#include "puzzleSolver.h"
#include <array>
#include <algorithm>
#include <unordered_map>
#include <queue>

// namespace Puzzle {
void Puzzle::solveAndPrint(PuzzleState unsolved) {
  // left 0 right 1 up 2 down 3
  const std::array<int, 4> k_directions = {0, 1, 2, 3};

  PuzzleState solved = PuzzleState(unsolved.size());
  std::queue<PuzzleState> q;
  // puzzle ,  parent of puzzle
  std::unordered_map<PuzzleState, PuzzleState, PuzzleState::custom_hash>
      visited;
  q.push(unsolved);
  visited.insert({unsolved, unsolved});
  bool isSolved = false;

  while (!q.empty()) {
    PuzzleState current_state = q.front();
    q.pop();
    if (current_state == solved) {
      isSolved = true;
      break;
    }

    for (auto direction : k_directions) {
      if (current_state.validMove(direction)) {
        PuzzleState new_state = current_state.move(direction);
        if (visited.find(new_state) == visited.end()) {
          visited.insert({new_state, current_state});
          q.push(new_state);
        }
      }
    }
  }
  if (!isSolved) {
    std::cout << "\n\nUnsolveable\n\n";
    return;
  }

  // backtrack
  std::vector<PuzzleState> steps;
  PuzzleState current_state = solved;
  while (!(current_state == unsolved)) {
    steps.push_back(current_state);
    auto it = visited.find(current_state);
    if (it == visited.end()) break;
    current_state = it->second;
  }
  steps.push_back(unsolved);
  std::reverse(steps.begin(), steps.end());

  int step = 0;
  for (auto state : steps) {
    std::cout << "Step # " << (step++);
    state.print();
  }
}
// };  // namespace Puzzle
