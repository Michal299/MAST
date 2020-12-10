#include "TreeNode.h"

TreeNode::TreeNode()
    : tag(0), parent(nullptr), brother(nullptr), son(nullptr)
{

}

TreeNode::TreeNode(int tag)
    : tag(tag), parent(nullptr), brother(nullptr), son(nullptr)
{

}

TreeNode::~TreeNode()
{
    tag=0;
}

int TreeNode::GetTag() const
{
    return tag;
}

TreeNode* TreeNode::GetParent() const
{
    return parent;
}

TreeNode* TreeNode::GetBrother() const
{
    return brother;
}

TreeNode* TreeNode::GetSon() const
{
    return son;
}

void TreeNode::SetTag(int value)
{
    this->tag = value;
}

void TreeNode::SetParent(TreeNode* node)
{
    parent = node;
}

void TreeNode::SetBrother(TreeNode* node)
{
    brother = node;
}

void TreeNode::SetSon(TreeNode* node)
{
    son = node;
}

bool TreeNode::IsLeaf() const
{
    if(son == nullptr)
    {
        return true;
    }
    else
    {
        return false;
    }
    
}

int TreeNode::CountSons() const
{
    int number = 0;
    TreeNode* child = son;
    while(child != nullptr)
    {
        number++;
        child = child->GetBrother();
    }
    return number;
}