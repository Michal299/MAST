#include <iostream>
#include "TreeNode.h"
#include "Tree.h"
#include "Table.h"

using namespace std;

int main()
{
    int n;
    cin >> n;
    string* newicks = new string[n];
    for(int i = 0; i < n; i++)
    {   
        cin >> newicks[i];
    }
    
    for(int i = 0; i < n; i++)
    {
        for(int j = i + 1; j < n; j++)
        {
            Tree a(newicks[i]);
            Tree b(newicks[j]);
            Table table(&a, &b);
            cout << table.GetResult() << endl;
        }
    }
    
    delete[] newicks;
}
