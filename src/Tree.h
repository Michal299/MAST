#pragma once
#include "TreeNode.h"
#include <iostream>
#include <string>

class Tree
{
private:
    TreeNode* root;
    int nodesNumber;
    int leafsNumber;
    void RepairTags(TreeNode* node);
public:
    Tree(std::string newick);
    void DeleteSubtree(TreeNode* node);
    int GetNodesNumber() const;
    int GetLeafsNumber() const;
    TreeNode* GetRoot() const;
    ~Tree();
};
