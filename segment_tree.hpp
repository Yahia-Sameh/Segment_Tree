#ifndef SEGMENT_TREE_H
#define SEGMENT_TREE_H

#include <iostream>
#include <vector>

using namespace std;

template <typename T> T my_min(T a, T b) { return a < b ? a : b; }

template <typename T> T my_max(T a, T b) { return a > b ? a : b; }

template <typename T> class SegmentTree {
protected:
  vector<T> tree;
  vector<T> lazy;
  int n;
  T identity;

  int left(int idx) { return idx * 2; }
  int right(int idx) { return idx * 2 + 1; }
  int mid(int l, int r) { return l + (r - l) / 2; }

  virtual T combine(T a, T b) = 0;
  virtual void apply_update(T &node_value, T update_value, int range_len) = 0;

  void build(int idx, int l, int r, const vector<T> &arr) {
    if (l == r) {
      tree[idx] = arr[l];
      return;
    }
    int m = mid(l, r);
    build(left(idx), l, m, arr);
    build(right(idx), m + 1, r, arr);
    tree[idx] = combine(tree[left(idx)], tree[right(idx)]);
  }

  void propagate(int idx, int l, int r) {
    if (lazy[idx] != T()) {
      apply_update(tree[idx], lazy[idx], r - l + 1);

      if (l != r) {
        lazy[left(idx)] += lazy[idx];
        lazy[right(idx)] += lazy[idx];
      }

      lazy[idx] = T();
    }
  }

  void update_range(int idx, int l, int r, int ql, int qr, T val) {
    propagate(idx, l, r);

    if (ql > r || qr < l)
      return;

    if (ql <= l && r <= qr) {
      lazy[idx] += val;
      propagate(idx, l, r);
      return;
    }

    int m = mid(l, r);
    update_range(left(idx), l, m, ql, qr, val);
    update_range(right(idx), m + 1, r, ql, qr, val);
    tree[idx] = combine(tree[left(idx)], tree[right(idx)]);
  }

  void update_point(int idx, int l, int r, int pos, T val) {
    propagate(idx, l, r);

    if (l == r) {
      tree[idx] = val;
      return;
    }

    int m = mid(l, r);
    if (pos <= m)
      update_point(left(idx), l, m, pos, val);
    else
      update_point(right(idx), m + 1, r, pos, val);

    propagate(left(idx), l, m);
    propagate(right(idx), m + 1, r);
    tree[idx] = combine(tree[left(idx)], tree[right(idx)]);
  }

  T query_range(int idx, int l, int r, int ql, int qr) {
    propagate(idx, l, r);

    if (ql > r || qr < l)
      return identity;
    if (ql <= l && r <= qr)
      return tree[idx];

    int m = mid(l, r);
    T left_res = query_range(left(idx), l, m, ql, qr);
    T right_res = query_range(right(idx), m + 1, r, ql, qr);

    return combine(left_res, right_res);
  }

public:
  SegmentTree(const vector<T> &arr, T id = T()) : identity(id) {
    n = arr.size();
    if (n == 0) {
      cerr << "Error: Array cannot be empty\n";
      return;
    }

    tree.resize(4 * n, T());
    lazy.resize(4 * n, T());
  }

  T query(int l, int r) {
    if (l < 0 || r >= n || l > r) {
      cerr << "Error: Invalid query range [" << l << ", " << r << "]\n";
      return identity;
    }
    return query_range(1, 0, n - 1, l, r);
  }

  void update(int pos, T val) {
    if (pos < 0 || pos >= n) {
      cerr << "Error: Invalid update position " << pos << "\n";
      return;
    }
    update_point(1, 0, n - 1, pos, val);
  }

  void update(int l, int r, T val) {
    if (l < 0 || r >= n || l > r) {
      cerr << "Error: Invalid update range [" << l << ", " << r << "]\n";
      return;
    }
    update_range(1, 0, n - 1, l, r, val);
  }

  T get(int pos) { return query(pos, pos); }

  int size() const { return n; }

  void print() {
    cout << "Segment Tree (size: " << n << "):\n";
    cout << "Elements: ";
    for (int i = 0; i < n; i++) {
      cout << get(i) << " ";
    }
    cout << "\n";
  }
};

template <typename T> class SumSegmentTree : public SegmentTree<T> {
protected:
  T combine(T a, T b) override { return a + b; }

  void apply_update(T &node_value, T update_value, int range_len) override {
    node_value += update_value * range_len;
  }

public:
  SumSegmentTree(const vector<T> &arr) : SegmentTree<T>(arr, T()) {
    this->build(1, 0, this->n - 1, arr);
  }
};

template <typename T> class MinSegmentTree : public SegmentTree<T> {
protected:
  T combine(T a, T b) override { return my_min(a, b); }

  void apply_update(T &node_value, T update_value, int range_len) override {
    node_value += update_value;
  }

public:
  MinSegmentTree(const vector<T> &arr) : SegmentTree<T>(arr) {

    if (arr.size() > 0) {

      T max_val = arr[0];
      for (const T &val : arr) {
        if (val > max_val)
          max_val = val;
      }

      this->identity = max_val + max_val;
    }
    this->build(1, 0, this->n - 1, arr);
  }
};

template <typename T> class MaxSegmentTree : public SegmentTree<T> {
protected:
  T combine(T a, T b) override { return my_max(a, b); }

  void apply_update(T &node_value, T update_value, int range_len) override {
    node_value += update_value;
  }

public:
  MaxSegmentTree(const vector<T> &arr) : SegmentTree<T>(arr) {

    if (arr.size() > 0) {

      T min_val = arr[0];
      for (const T &val : arr) {
        if (val < min_val)
          min_val = val;
      }

      this->identity = min_val - min_val - min_val;
    }
    this->build(1, 0, this->n - 1, arr);
  }
};

#endif
