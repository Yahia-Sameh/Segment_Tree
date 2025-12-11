#include "segment_tree.hpp"
#include <iostream>
#include <vector>

bool test_sum_tree() {
  std::cout << "Testing SumSegmentTree... ";

  std::vector<int> arr = {1, 2, 3, 4, 5};
  SumSegmentTree<int> st(arr);

  // Test initial queries
  if (st.query(0, 4) != 15) {
    std::cout << "FAIL: Sum [0,4] should be 15\n";
    return false;
  }

  if (st.query(1, 3) != 9) {
    std::cout << "FAIL: Sum [1,3] should be 9\n";
    return false;
  }

  // Test point update
  st.update(2, 10);
  if (st.query(0, 4) != 22) {
    std::cout << "FAIL: After update, sum should be 22\n";
    return false;
  }

  // Test range update
  st.update(0, 2, 5);
  if (st.get(0) != 6) {
    std::cout << "FAIL: arr[0] should be 6\n";
    return false;
  }

  if (st.get(2) != 15) {
    std::cout << "FAIL: arr[2] should be 15\n";
    return false;
  }

  std::cout << "PASS\n";
  return true;
}

bool test_min_tree() {
  std::cout << "Testing MinSegmentTree... ";

  std::vector<int> arr = {5, 2, 8, 1, 6};
  MinSegmentTree<int> st(arr);

  if (st.query(0, 4) != 1) {
    std::cout << "FAIL: Min should be 1\n";
    return false;
  }

  if (st.query(0, 2) != 2) {
    std::cout << "FAIL: Min [0,2] should be 2\n";
    return false;
  }

  st.update(3, 10);
  if (st.query(0, 4) != 2) {
    std::cout << "FAIL: After update, min should be 2\n";
    return false;
  }

  std::cout << "PASS\n";
  return true;
}

bool test_edge_cases() {
  std::cout << "Testing edge cases... ";

  // Single element
  std::vector<int> arr1 = {42};
  SumSegmentTree<int> st1(arr1);

  if (st1.query(0, 0) != 42) {
    std::cout << "FAIL: Single element test\n";
    return false;
  }

  // Two elements
  std::vector<int> arr2 = {1, 2};
  SumSegmentTree<int> st2(arr2);

  if (st2.query(0, 1) != 3) {
    std::cout << "FAIL: Two elements sum\n";
    return false;
  }

  std::cout << "PASS\n";
  return true;
}

int main() {
  std::cout << "=== Segment Tree Tests ===\n\n";

  bool all_pass = true;

  all_pass = test_sum_tree() && all_pass;
  all_pass = test_min_tree() && all_pass;
  all_pass = test_edge_cases() && all_pass;

  std::cout << "\n=== " << (all_pass ? "All tests PASSED" : "Some tests FAILED")
            << " ===\n";

  return all_pass ? 0 : 1;
}
