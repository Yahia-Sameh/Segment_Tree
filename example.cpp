#include "segment_tree.hpp"
#include <iostream>
#include <vector>

using namespace std;

int main() {
  cout << "=== Simple Segment Tree Example ===\n\n";
  vector<int> arr = {1, 3, 5, 7, 9, 11};

  // Sum Segment Tree
  SumSegmentTree<int> sum_tree(arr);
  cout << "Original array: ";
  for (int i = 0; i < sum_tree.size(); i++) {
    cout << sum_tree.get(i) << " ";
  }
  cout << "\n\n";

  cout << "Sum queries:\n";
  cout << "Sum [0, 2] = " << sum_tree.query(0, 2) << "\n";
  cout << "Sum [2, 5] = " << sum_tree.query(2, 5) << "\n";
  cout << "Sum [1, 4] = " << sum_tree.query(1, 4) << "\n";

  cout << "\nUpdating element at index 2 from " << sum_tree.get(2);
  sum_tree.update(2, 10);
  cout << " to " << sum_tree.get(2) << "\n";
  cout << "New sum [0, 2] = " << sum_tree.query(0, 2) << "\n";

  cout << "\nAdding 5 to range [1, 4]\n";
  sum_tree.update(1, 4, 5);
  cout << "Array after range update:\n";
  for (int i = 0; i < sum_tree.size(); i++) {
    cout << "arr[" << i << "] = " << sum_tree.get(i) << "\n";
  }
  cout << "Final sum [0, 5] = " << sum_tree.query(0, 5) << "\n\n";

  // Min Segment Tree
  MinSegmentTree<int> min_tree(arr);
  cout << "Min queries:\n";
  cout << "Min [0, 2] = " << min_tree.query(0, 2) << "\n";
  cout << "Min [2, 5] = " << min_tree.query(2, 5) << "\n";
  cout << "Min [1, 4] = " << min_tree.query(1, 4) << "\n";
  min_tree.update(3, 0);
  cout << "After updating index 3 to 0, Min [0, 5] = " << min_tree.query(0, 5)
       << "\n\n";

  // Max Segment Tree
  MaxSegmentTree<int> max_tree(arr);
  cout << "Max queries:\n";
  cout << "Max [0, 2] = " << max_tree.query(0, 2) << "\n";
  cout << "Max [2, 5] = " << max_tree.query(2, 5) << "\n";
  cout << "Max [1, 4] = " << max_tree.query(1, 4) << "\n";
  max_tree.update(4, 100);
  cout << "After updating index 4 to 100, Max [0, 5] = " << max_tree.query(0, 5)
       << "\n";

  return 0;
}
