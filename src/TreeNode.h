#pragma once

class TreeNode
{
private:
    int tag;
    TreeNode* parent;
    TreeNode* brother;
    TreeNode* son;
public:
    TreeNode();
    TreeNode(int tag);
    ~TreeNode();
    int GetTag() const;    
    TreeNode* GetParent() const;
    TreeNode* GetBrother() const;
    TreeNode* GetSon() const;
    void SetTag(int value);
    void SetParent(TreeNode* node);
    void SetBrother(TreeNode* node); 
    void SetSon(TreeNode* node);
    bool IsLeaf() const; 
    int CountSons() const;
};
