#pragma once
#include "Tree.h"

class Table
{
private:
    TreeNode** columnNodes;
    TreeNode** rowNodes;
    int** valueTable;
    int columnNumber;
    int rowNumber;
    int leafNumber;
    void ClearRow(int* row, int size);
    void FillNodesArray(TreeNode* node, TreeNode** array);
    void FillLeafs(int aLeafsNumber, int bLeafsNumber);
    void FillDescendants(TreeNode* node, int coordinate, std::string dimension);
    void FillSons(int rowLimit, int columnLimit);
    int SumOfConnections(TreeNode* rowNode, TreeNode* columnNode);
    int MaxAssigment(int** matrix, int y, int x);
public:
    Table(Tree* a, Tree* b);
    int GetResult() const;
    ~Table();
};