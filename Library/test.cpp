#include <gtest/gtest.h>
#include <unordered_set>
#include <queue>
#include <stack>
#include <vector>
#include <unordered_map>
#include "puzzleState.h"
#include "puzzleSolver.h"
#include "puzzleGenerator.h"

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