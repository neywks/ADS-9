// Copyright 2022 NNTU-CS
#include "tree.h"

#include <vector>

PMTreeNode::~PMTreeNode() {
  for (auto kid : children) {
    delete kid;
  }
}

void PMTree::build(PMTreeNode* node, const std::vector<char>& items) {
  if (items.empty()) return;

  for (char c : items) {
    PMTreeNode* kid = new PMTreeNode(c);
    node->children.push_back(kid);

    std::vector<char> rest;
    for (char x : items) {
      if (x != c) rest.push_back(x);
    }

    build(kid, rest);
  }
}

PMTree::PMTree(const std::vector<char>& chars) {
  for (char c : chars) {
    PMTreeNode* nd = new PMTreeNode(c);
    roots.push_back(nd);

    std::vector<char> rest;
    for (char x : chars) {
      if (x != c) rest.push_back(x);
    }

    build(nd, rest);
  }
}

PMTree::~PMTree() {
  for (auto nd : roots) {
    delete nd;
  }
}

static void collect(PMTreeNode* nd, std::vector<char>* cur,
                    std::vector<std::vector<char>>* out) {
  if (!nd) return;

  cur->push_back(nd->value);

  if (nd->children.empty()) {
    out->push_back(*cur);
  } else {
    for (auto kid : nd->children) {
      collect(kid, cur, out);
    }
  }

  cur->pop_back();
}

std::vector<std::vector<char>> getAllPerms(const PMTree& tree) {
  std::vector<std::vector<char>> res;
  std::vector<char> cur;

  for (auto nd : tree.getRoots()) {
    collect(nd, &cur, &res);
  }

  return res;
}

std::vector<char> getPerm1(PMTree& tree, int n) {
  if (n <= 0) return {};

  auto all = getAllPerms(tree);

  if (static_cast<size_t>(n) > all.size()) return {};

  return all[n - 1];
}

static int countLeaves(PMTreeNode* nd) {
  if (!nd) return 0;
  if (nd->children.empty()) return 1;

  int sum = 0;
  for (auto kid : nd->children) {
    sum += countLeaves(kid);
  }
  return sum;
}

std::vector<char> getPerm2(PMTree& tree, int n) {
  if (n <= 0) return {};

  const auto& rootsList = tree.getRoots();
  if (rootsList.empty()) return {};

  int acc = 0;
  PMTreeNode* cur = nullptr;

  for (auto nd : rootsList) {
    int sz = countLeaves(nd);
    if (acc + sz >= n) {
      cur = nd;
      break;
    }
    acc += sz;
  }

  if (!cur) return {};

  std::vector<char> res;
  int idx = n - acc;

  while (cur) {
    res.push_back(cur->value);

    if (cur->children.empty()) break;

    acc = 0;
    PMTreeNode* next = nullptr;

    for (auto kid : cur->children) {
      int sz = countLeaves(kid);
      if (acc + sz >= idx) {
        next = kid;
        break;
      }
      acc += sz;
    }

    if (!next) return {};

    idx -= acc;
    cur = next;
  }

  return res;
}
