#include "Table.h"

Table::Table(Tree* a, Tree* b)
    : columnNodes(nullptr), rowNodes(nullptr), valueTable(nullptr)
{
    rowNumber = a->GetNodesNumber();
    columnNumber = b->GetNodesNumber();

    valueTable = new int*[rowNumber];
    for(int i = 0; i < rowNumber; i++)
    {
        valueTable[i] = new int[columnNumber];
        ClearRow(valueTable[i], columnNumber);
    }

    columnNodes = new TreeNode*[columnNumber];
    rowNodes = new TreeNode*[rowNumber];

    rowNodes[a->GetRoot()->GetTag()] = a->GetRoot();
    FillNodesArray(a->GetRoot(), rowNodes);
    columnNodes[b->GetRoot()->GetTag()] = b->GetRoot();
    FillNodesArray(b->GetRoot(), columnNodes);

    FillLeafs(a->GetLeafsNumber(), b->GetLeafsNumber());
    
    FillSons(a->GetLeafsNumber(), b->GetLeafsNumber());

    leafNumber = a->GetLeafsNumber();
}

int Table::GetResult() const
{
    return leafNumber - valueTable[leafNumber][leafNumber];
}

Table::~Table()
{
    for(int i = 0; i < rowNumber; i++)
    {
        delete[] valueTable[i];
    }
    delete[] valueTable;
    delete[] columnNodes;
    delete[] rowNodes;
}
//------------------------------------------------------------------------------
void Table::ClearRow(int* row, int size)
{
    for(int i = 0; i < size; i++)
    {
        row[i] = 0;
    }
}

void Table::FillNodesArray(TreeNode* node, TreeNode** array)
{
    if(node->GetSon() != nullptr)
    {
        array[node->GetSon()->GetTag()] = node->GetSon();
        FillNodesArray(node->GetSon(), array);
    }
    if(node->GetBrother() != nullptr)
    {
        array[node->GetBrother()->GetTag()] = node->GetBrother();
        FillNodesArray(node->GetBrother(), array);
    }

}

void Table::FillLeafs(int aLeafsNumber, int bLeafsNumber) 
{   
    for(int i=0; i<aLeafsNumber; i++)
    {
        if(i >= bLeafsNumber)
        {
            break;
        }
        for (int j = 0; j < bLeafsNumber; j++)
        {
            if(j >= aLeafsNumber)
            {
                break;
            }
            if(i==j)
            {
                valueTable[i][j] = 1;
                FillDescendants(columnNodes[i], i, "row");
                FillDescendants(rowNodes[i], i, "column");
            }
        }
        
    }
}

void Table::FillDescendants(TreeNode* node, int coordinate, std::string dimension)
{
    if(node == nullptr)
    {
        return;
    }
    node = node->GetParent();
    while(node != nullptr)
    {
        if(dimension == "row")
        {
            valueTable[coordinate][node->GetTag()] = 1;
        }
        else if(dimension == "column")
        {
            valueTable[node->GetTag()][coordinate] = 1;
        }
        else 
        {
            throw "Wrong dimension";
        }
        node = node->GetParent();
    }
}

void Table::FillSons(int rowLimit, int columnLimit)
{
    
    for(int j = columnNumber-1; j >= columnLimit; j--)
    {   
        for(int i = rowNumber-1; i >= rowLimit; i--)
        {
            valueTable[i][j] = SumOfConnections(rowNodes[i], columnNodes[j]);
        }
    }
}

int Table::SumOfConnections(TreeNode* rowNode, TreeNode* columnNode)
{
    if(rowNode->GetSon() == nullptr || columnNode->GetSon() == nullptr) std::cout << "LOOL";
    int y = rowNode->CountSons();
    int x = columnNode->CountSons();
    
    TreeNode* rSon = rowNode->GetSon();
    TreeNode* cSon = columnNode->GetSon();

    int** matrix = new int*[y];
    for(int i = 0; i < y; i++)
    {
        matrix[i] = new int[x];
        cSon = columnNode->GetSon();
        for(int j = 0; j < x; j++)
        {
            matrix[i][j] = valueTable[rSon->GetTag()][cSon->GetTag()];
            
            cSon = cSon->GetBrother();
        }

        rSon = rSon->GetBrother();
    }
    
    
    int sum = MaxAssigment(matrix, y, x);

    cSon = columnNode->GetSon();
    for(int j=0; j<x; j++)
    {
        if(valueTable[rowNode->GetTag()][cSon->GetTag()] > sum)
        {
            sum = valueTable[rowNode->GetTag()][cSon->GetTag()];
        }
        cSon = cSon->GetBrother();
    }

    rSon = rowNode->GetSon();
    for(int i=0; i<y; i++)
    {
        if(valueTable[rSon->GetTag()][columnNode->GetTag()] > sum)
        {
            sum = valueTable[rSon->GetTag()][columnNode->GetTag()];
        }
        rSon = rSon->GetBrother();
    }

    for(int i=0; i<y; i++)
    {
        delete[] matrix[i];
    }

    delete[] matrix;

    return sum;
}

int Table::MaxAssigment(int** matrix, int y, int x)
{
    if(y * x == 1) return matrix[0][0];
    else if(y * x < 1) return 0;
    int max = 0;
    
    int** buffor = new int*[y-1];
    for(int i = 0; i < y-1; i++)
    {
        buffor[i] = new int[x-1];
    }
    for(int i = 0; i < y; i++)
    {
        for(int j = 0; j < x; j++)
        {
            if(i == 0 || j == 0)
            {
                int bi = 0;
            
                for(int by = 0; by < y; by++)
                {
                    if(by != i)
                    {
                        int bj = 0;
                        for(int bx = 0; bx < x; bx++)
                        {
                            if(bx != j)
                            {
                                buffor[bi][bj] = matrix[by][bx];
                                bj++;
                            }
                        }
                        bi++;
                    }
                }
                int maxbuffor = MaxAssigment(buffor, y-1, x-1);
                if(maxbuffor + matrix[i][j] > max)
                {
                    max = maxbuffor + matrix[i][j];
                }
            }
        }
    }
    for(int by = 0; by < y-1; by++)
    {
        delete[] buffor[by];
    }
    delete[] buffor;

    return max;
}