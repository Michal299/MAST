#include "Tree.h"

Tree::Tree(std::string newick)
    : root(new TreeNode(0)), nodesNumber(1), leafsNumber(0)
{
    TreeNode* current = root;
    int tag=-1;

    for (size_t i = 0; i < newick.length(); i++)
    {
        char element = newick[i];
        if(element == '(')
        {
            TreeNode* node = new TreeNode(tag);
            node->SetParent(current);

            current->SetSon(node);
            
            tag--;
            current = node;
            nodesNumber++;
        }
        else if (element == ')')
        {
            current = current->GetParent();
        }
        else if(element == ',')
        {
            TreeNode* node = new TreeNode(tag);
            node->SetParent(current->GetParent());

            current->SetBrother(node);
            tag--;
            current = node;
            nodesNumber++;
        }
        else if(element >= '0' && element <= '9')
        {
            int j = i;
            for(j; j < newick.length(); j++)
            {
                if(newick[j] < '0' || newick[j] > '9')
                {
                    break;
                }
            }
            int newTag = atoi(newick.substr(i,j-i).c_str());
            i = j - 1;
            current->SetTag(newTag);
            leafsNumber++;
            tag++;
        }
        else if(element == ';')
        {
            break;
        }
    }
    RepairTags(root);
}

void Tree::DeleteSubtree(TreeNode* node)
{
    if(node != nullptr)
    {
        while(node->GetSon() != nullptr)
        {
            TreeNode* son = node->GetSon();
            node->SetSon(son->GetBrother());
            DeleteSubtree(son);
        }
        delete node;
        nodesNumber--;
    }
}

int Tree::GetNodesNumber() const 
{
    return nodesNumber;
}

int Tree::GetLeafsNumber() const
{
    return leafsNumber;
}

TreeNode* Tree::GetRoot() const
{
    return root;
}

Tree::~Tree()
{
    DeleteSubtree(root);
}

//------------------------------------------------------------------------------

void Tree::RepairTags(TreeNode* node)
{
    if(node != nullptr)
    {
        if(!node->IsLeaf())
        {
            node->SetTag(node->GetTag() * (-1) + leafsNumber);
            RepairTags(node->GetSon());
        }
        else
        {
            node->SetTag(node->GetTag() - 1);
        }
        
        RepairTags(node->GetBrother());
    }
}