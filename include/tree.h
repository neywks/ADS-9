// Copyright 2022 NNTU-CS
#ifndef INCLUDE_TREE_H_
#define INCLUDE_TREE_H_

#include <vector>

class PMTreeNode {
 public:
  char value;
  std::vector<PMTreeNode*> children;

  explicit PMTreeNode(char val) : value(val) {}
  ~PMTreeNode();
};

class PMTree {
 private:
  std::vector<PMTreeNode*> roots;
  void build(PMTreeNode* node, const std::vector<char>& items);

 public:
  explicit PMTree(const std::vector<char>& elements);
  ~PMTree();
  const std::vector<PMTreeNode*>& getRoots() const { return roots; }
};

std::vector<std::vector<char>> getAllPerms(const PMTree& tree);
std::vector<char> getPerm1(PMTree& tree, int n);
std::vector<char> getPerm2(PMTree& tree, int n);

#endif  // INCLUDE_TREE_H_
