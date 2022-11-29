#include "pch.h"
#include <unordered_set>
#include <queue>
#include <stack>
#include <vector>
#include <unordered_map>
#include "Library/puzzleState.h"
#include "Library/puzzleSolver.h"
#include "Library/puzzleGenerator.h"

TEST(GoogleTest, google_test_working) {
  EXPECT_EQ(1, 1);
  EXPECT_TRUE(true);
}

TEST(Constructors, grid_and_cavity) { 
  PuzzleState p({{1, 2}, {3, 0}}, {1, 1});
  ASSERT_TRUE(p.isSolved());
  ASSERT_EQ(p.size(), 2);
}

TEST(Constructors, solved_puzzle_by_size) {
  PuzzleState p(3);
  ASSERT_TRUE(p.isSolved());
  ASSERT_EQ(p.size(), 3);
}

TEST(Print, printing_puzzle) {
  std::string expected_output = "\n\n1 2 3 \n4 5 6 \n7 8   \n";
  PuzzleState p(3);
  testing::internal::CaptureStdout();
  p.print();
  std::string output = testing::internal::GetCapturedStdout();
  ASSERT_EQ(output, expected_output);
 //
}

// TODO: write test cases for all moves
TEST(Move_validator, validator) { 
  PuzzleState ps = PuzzleState(6);
  // 0 left 1 right 2 up 3 down
  ASSERT_FALSE(ps.validMove(0));
  ASSERT_TRUE (ps.validMove(1));
  ASSERT_FALSE(ps.validMove(2));
  ASSERT_TRUE (ps.validMove(3));
}

TEST(MoveGenerator, test) {
  std::string expected_output_left_move = "\n\n1 2 3 \n4 5 6 \n7   8 \n";
  std::string expected_output_down_move = "\n\n1 2 3 \n4 5   \n7 8 6 \n";

  PuzzleState p (3);
  PuzzleState p_left = p.move(/*direction=*/1);  // move left, ensure move exists
  PuzzleState p_down = p.move(/*direction=*/3);  // move down, ensure move exists

  testing::internal::CaptureStdout();
  p_left.print();
  std::string left_output = testing::internal::GetCapturedStdout();
  testing::internal::CaptureStdout();
  p_down.print();
  std::string down_output = testing::internal::GetCapturedStdout();

  ASSERT_TRUE(left_output == expected_output_left_move);
  ASSERT_TRUE(down_output == expected_output_down_move);
}

TEST(HashImplementation, creating_unordered_set) { 
  PuzzleState p = PuzzleState(3);
  std::unordered_set<PuzzleState, PuzzleState::custom_hash> set;
  set.insert(p);
  ASSERT_TRUE(set.find(p) != set.end());
  p = p.move(/*direction=*/1); // move left, ensure move exists
  ASSERT_FALSE(set.find(p) != set.end());
}

TEST(EqaulityOperator, comparing_puzzle_states) { 
  PuzzleState p = PuzzleState(2); 
  PuzzleState q = PuzzleState({{1, 2}, {3, 0}}, {1, 1});
  ASSERT_TRUE(p == q);
  PuzzleState moved = p.move(/*direction=*/1);  // move left, ensure move exists
  ASSERT_TRUE(!(moved == p));
}

TEST(Member_function_isSolved, state_is_solved) {
  PuzzleState p(3);
  ASSERT_TRUE(p.isSolved());
}

TEST(Member_function_isSolved, state_is_unsolved) { 
  PuzzleState p(3);
  p = p.move(/*direction=*/1);  // move left, ensure move exists
  ASSERT_FALSE(p.isSolved());
}

TEST(Member_function_puzzle_size, testing) {
  PuzzleState p(10); 
  ASSERT_EQ(p.size(), 10);
}

TEST(Generate, solveable_in_asked_moves) {
  std::string expected_output =
      "\n\n3   \n2 1 \n\nSolveable in 5 moves.";
  testing::internal::CaptureStdout();
  // every valid confugration of a 2 by 2 puzzle is solveable in atmost 6 moves
  Puzzle::generateAndPrint(/*size=*/2, /*moves_to_solve=*/5);
  std::string output = testing::internal::GetCapturedStdout();
  ASSERT_EQ(output, expected_output);
}

TEST(Generate, unsolveable_in_asked_moves) {
  std::string expected_output = "\n\n6 4 7 \n8 5   \n3 2 1 \n\nSolveable in 31 moves.";
  testing::internal::CaptureStdout();
  // every valid confugration of a 3 by 3 puzzle is solveable in atmost 31 moves
  Puzzle::generateAndPrint(/*size=*/3, /*moves_to_solve=*/300);
  std::string output = testing::internal::GetCapturedStdout();
  ASSERT_EQ(output, expected_output);
}

TEST(Solve, solveable_puzzle) {
  std::string expected_output =
       "Step # 0\n\n1 2 \n  3 \nStep # 1\n\n1 2 \n3   \n";
  PuzzleState unsolved({{1, 2}, {0, 3}}, {1, 0});
  testing::internal::CaptureStdout();
  Puzzle::solveAndPrint(unsolved);
  std::string output = testing::internal::GetCapturedStdout();
  ASSERT_EQ(output, expected_output);
}

TEST(Solve, unsolveable_puzzle) {
  std::string expected_output =
      "\n\nUnsolveable\n\n";
  PuzzleState unsolved({{3, 2}, {1, 0}}, {1, 1});
  testing::internal::CaptureStdout();
  Puzzle::solveAndPrint(unsolved);
  std::string output = testing::internal::GetCapturedStdout();
  ASSERT_EQ(output, expected_output);
}

// useful functions [STARTS]

/*
  size_t pos; // helps identifies line break in console output
  while ((pos = output.find('\n')) != std::string::npos) {
    output[pos] = '*';
  }
*/

// useful functions [END]





// dumped code

//TEST(Solve, example_one) { 
//  //PuzzleState unsolved({{1, 2}, {0, 3}}, {1, 0});
//  PuzzleState unsolved({{0, 3}, {2, 1}}, {0, 0});
//  PuzzleState solved = PuzzleState(2);
//  std::queue<PuzzleState> q;
////  // puzzle ,  parent of puzzle
//  std::unordered_map<PuzzleState, PuzzleState, PuzzleState::custom_hash> visited;
//  q.push(unsolved);
//  visited.insert({unsolved, unsolved});
//  bool isSolved = false;
//  //PuzzleState current_state = unsolved;
//  //if (visited.find(unsolved) != visited.end()) std::cout << "true";
//  //
//  while (!q.empty()) {
//  //  // idea use move vector
//    const int k_left = 0, k_right = 1, k_up = 2, k_down = 3;
//    PuzzleState current_state = q.front();
//    q.pop();
//    /*std::cout << "\nmove\n";
//    current_state.print();
//    std::cout << "\nmove\n";*/
//    if (current_state == solved) {
//      isSolved = true;
//      break;
//    }
//
//    if (current_state.validMove(k_left)) {
//      PuzzleState new_state = current_state.move(k_left);
//      if (visited.find(new_state) == visited.end()) {
//        visited.insert({new_state, current_state});
//        q.push(new_state);
//      }
//    }
//    if (current_state.validMove(k_right)) {
//      PuzzleState new_state = current_state.move(k_right);
//      if (visited.find(new_state) == visited.end()) {
//        visited.insert({new_state, current_state});
//        q.push(new_state);
//      }
//    }
//    if (current_state.validMove(k_up)) {
//      PuzzleState new_state = current_state.move(k_up);
//      if (visited.find(new_state) == visited.end()) {
//        visited.insert({new_state, current_state});
//        q.push(new_state);
//      }
//    }
//    if (current_state.validMove(k_down)) {
//      PuzzleState new_state = current_state.move(k_down);
//      if (visited.find(new_state) == visited.end()) {
//        visited.insert({new_state, current_state});
//        q.push(new_state);
//      }
//    }
//  }
//
//
//  // refractor this code
//  if (!isSolved) std::cout << "Unsolveable";
// // return;
//
//
//  /*for (auto it : visited) {
//    std::cout << "\nstart";
//    it.first.print();
//    std::cout << "\nmaps";
//    it.second.print();
//  }*/
//
//  std::vector<PuzzleState> steps;
//  //// backtrack
//  PuzzleState current_state = solved;
//  while (!(current_state == unsolved)) {
//    steps.push_back(current_state);
//    auto it = visited.find(current_state);
//    if (it == visited.end()) break;
//    current_state = it->second;
//  }
//  steps.push_back(unsolved);
//  std::reverse(steps.begin(), steps.end());
//  
//  //// print
//  int step = 0;
//  for (auto state : steps) {
//    std::cout << "Step # " << (step++);
//    state.print();
//  }
//
//
//  // dummy
//}
 //TEST(implementation, test) {
 // PuzzleState solved_puzzle = PuzzleState(2);
 // int max_moves = 16;
 // int depth = -1;


 // PuzzleState current_state = solved_puzzle;
 // while (!q.empty() && depth < max_moves) {
 //   const int k_left = 0, k_right = 1, k_up = 2, k_down = 3;
 //   int states_in_level = q.size();
 //   //std::cout << "level " << d << "\n\n";
 //   while (states_in_level-- > 0) {
 //     current_state = q.front();
 //     //current_state.print();
 //     q.pop();

 //     if (current_state.validMove(k_left)) {
 //       PuzzleState new_state = current_state.move(k_left);
 //       if (visited.find(new_state) == visited.end()) {
 //         visited.insert(new_state);
 //         q.push(new_state);
 //       }
 //     }
 //     if (current_state.validMove(k_right)) {
 //       PuzzleState new_state = current_state.move(k_right);
 //       if (visited.find(new_state) == visited.end()) {
 //         //new_state->print();
 //         visited.insert(new_state);
 //         q.push(new_state);
 //       }
 //     }
 //     if (current_state.validMove(k_up)) {
 //       PuzzleState new_state = current_state.move(k_up);
 //       if (visited.find(new_state) == visited.end()) {
 //         visited.insert(new_state);
 //         q.push(new_state);
 //       }
 //     }
 //     if (current_state.validMove(k_down)) {
 //       PuzzleState new_state = current_state.move(k_down);
 //       if (visited.find(new_state) == visited.end()) {
 //         visited.insert(new_state);
 //         q.push(new_state);
 //       }
 //     }
 //   }
 //   ++depth;
 // }
// while (!s.empty() && max_d > 0) {
//  PuzzleState current_state = s.top(); s.pop();
//  steps.push_back(current_state);
//  if (current_state.validMove(k_left)) {
//    PuzzleState new_state = current_state.move(k_left);
//    if (visited.find(new_state) == visited.end()) {
//      visited.insert(new_state);
//      //q.push(new_state);
//    }
//  }
//}
// }

 // current_state.print();
 // std::cout << "\nSolveable in " << depth << " moves.";
 //}
 //TEST(Solving, test_one) {
   // use depth limited dfs
 //  const int k_left = 0, k_right = 1, k_up = 2, k_down = 3;
   //PuzzleState solved_puzzle = PuzzleState(2);
   //PuzzleState unsolved_puzzle = PuzzleState({{0, 1}, {3, 2}}, {0, 0});
   //std::stack<PuzzleState> s;
   //std::unordered_set<PuzzleState, PuzzleState::custom_hash> visited;
   //s.push(unsolved_puzzle);
   //visited.insert(unsolved_puzzle);
   //int max_d = 10;
 // std::queue<PuzzleState> q;
 // std::unordered_set<PuzzleState, PuzzleState::custom_hash> visited;
 // q.push(solved_puzzle);
 // visited.insert(solved_puzzle);

// TEST(implementation) {
//  PuzzleState* solved_puzzle = new PuzzleState(2);
//  int moves = 4;
//
//  int d = 0;
//
//  std::queue<PuzzleState*> q;
//  std::unordered_set<PuzzleState*> visited;
//  q.push(solved_puzzle);
//  visited.insert(solved_puzzle);
//
//  PuzzleState* current_state = nullptr;
//  while (!q.empty() && d < moves) {
//    const int k_left = 0, k_right = 1, k_up = 2, k_down = 3;
//    int states_in_level = q.size();
//    std::cout << "hi\n\n";
//    while (states_in_level-- > 0) {
//      current_state = q.front();
//      current_state->print();
//      q.pop();
//
//      if (current_state->validMove(k_left)) {
//        PuzzleState* new_state = current_state->move(k_left);
//        if (visited.find(new_state) == visited.end()) {
//          visited.insert(new_state);
//          q.push(new_state);
//        }
//      }
//      if (current_state->validMove(k_right)) {
//        PuzzleState* new_state = current_state->move(k_right);
//        if (visited.find(new_state) == visited.end()) {
//          //new_state->print();
//          visited.insert(new_state);
//          q.push(new_state);
//        }
//      }
//      if (current_state->validMove(k_up)) {
//        PuzzleState* new_state = current_state->move(k_up);
//        if (visited.find(new_state) == visited.end()) {
//          visited.insert(new_state);
//          q.push(new_state);
//        }
//      }
//      if (current_state->validMove(k_down)) {
//        PuzzleState* new_state = current_state->move(k_down);
//        if (visited.find(new_state) == visited.end()) {
//          visited.insert(new_state);
//          q.push(new_state);
//        }
//      }
//    }
//    if (!q.empty()) ++d;
//  }
//
//  if (current_state != nullptr)
//   current_state->print();
//}