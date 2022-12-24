#include <unordered_set>
#include <queue>
#include <array>
#include "puzzleState.h"
#include "puzzleGenerator.h"

// namespace Puzzle {
void Puzzle::generateAndPrint(int size, int moves_to_solve) {
  // left 0 right 1 up 2 down 3
  const std::array<int, 4> k_directions = {0, 1, 2, 3};

  PuzzleState solved_puzzle(size);
  int depth = -1;
  std::queue<PuzzleState> q;
  std::unordered_set<PuzzleState, PuzzleState::custom_hash> visited;
  q.push(solved_puzzle);
  visited.insert(solved_puzzle);

  
  PuzzleState current_state = solved_puzzle;
  while (!q.empty() && depth < moves_to_solve) {
    int states_in_level = q.size();
    while (states_in_level-- > 0) {
      current_state = q.front();
      q.pop();
      for (auto direction : k_directions) {
        if (current_state.validMove(direction)) {
          PuzzleState new_state = current_state.move(direction);
          if (visited.find(new_state) == visited.end()) {
            visited.insert(new_state);
            q.push(new_state);
          }
        }
      }
    }
    ++depth;
  }
  current_state.print();
  std::cout << "\nSolveable in " << depth << " moves.";
}
// };
