#ifndef ADVANCED_SEGMENT_TREE_H
#define ADVANCED_SEGMENT_TREE_H

#include <iostream>
#include <vector>

using namespace std;
// Segment Tree with range assignment (set range to value)
template <typename T> class RangeAssignSegmentTree {
private:
  struct Node {
    T value;
    T lazy_assign;
    bool has_lazy;

    Node() : value(T()), lazy_assign(T()), has_lazy(false) {}
  };

  vector<Node> tree;
  int n;

  int left(int idx) { return idx * 2; }
  int right(int idx) { return idx * 2 + 1; }
  int mid(int l, int r) { return l + (r - l) / 2; }

  void build(int idx, int l, int r, const vector<T> &arr) {
    if (l == r) {
      tree[idx].value = arr[l];
      return;
    }
    int m = mid(l, r);
    build(left(idx), l, m, arr);
    build(right(idx), m + 1, r, arr);
    tree[idx].value = tree[left(idx)].value + tree[right(idx)].value;
  }

  void push_assign(int idx, int l, int r) {
    if (tree[idx].has_lazy) {
      T val = tree[idx].lazy_assign;
      tree[idx].value = val * (r - l + 1);

      if (l != r) {
        tree[left(idx)].lazy_assign = val;
        tree[left(idx)].has_lazy = true;
        tree[right(idx)].lazy_assign = val;
        tree[right(idx)].has_lazy = true;
      }

      tree[idx].has_lazy = false;
    }
  }

  void update_assign(int idx, int l, int r, int ql, int qr, T val) {
    push_assign(idx, l, r);

    if (ql > r || qr < l)
      return;

    if (ql <= l && r <= qr) {
      tree[idx].lazy_assign = val;
      tree[idx].has_lazy = true;
      push_assign(idx, l, r);
      return;
    }

    int m = mid(l, r);
    update_assign(left(idx), l, m, ql, qr, val);
    update_assign(right(idx), m + 1, r, ql, qr, val);
    tree[idx].value = tree[left(idx)].value + tree[right(idx)].value;
  }

  T query_sum(int idx, int l, int r, int ql, int qr) {
    push_assign(idx, l, r);

    if (ql > r || qr < l)
      return T();
    if (ql <= l && r <= qr)
      return tree[idx].value;

    int m = mid(l, r);
    return query_sum(left(idx), l, m, ql, qr) +
           query_sum(right(idx), m + 1, r, ql, qr);
  }

public:
  RangeAssignSegmentTree(const vector<T> &arr) {
    n = arr.size();
    if (n == 0) {
      cerr << "Error: Array cannot be empty\n";
      return;
    }
    tree.resize(4 * n);
    build(1, 0, n - 1, arr);
  }

  // Set range [l, r] to value
  void set_range(int l, int r, T val) {
    if (l < 0 || r >= n || l > r) {
      cerr << "Error: Invalid range [" << l << ", " << r << "]\n";
      return;
    }
    update_assign(1, 0, n - 1, l, r, val);
  }

  // Get sum of range [l, r]
  T query(int l, int r) {
    if (l < 0 || r >= n || l > r) {
      cerr << "Error: Invalid query range [" << l << ", " << r << "]\n";
      return T();
    }
    return query_sum(1, 0, n - 1, l, r);
  }

  // Get single element
  T get(int pos) { return query(pos, pos); }

  int size() const { return n; }

  void print() {
    cout << "Array: ";
    for (int i = 0; i < n; i++) {
      cout << get(i) << " ";
    }
    cout << "\n";
  }
};

#endif // ADVANCED_SEGMENT_TREE_H
