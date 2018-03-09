#include <iostream>
#include <vector>
#include <cstdio>
#include <cstring>

using namespace std;

void getPostorder(vector<int>& preorder, vector<int>& inorder,
                  vector<int>& postorder, int preStart, int preEnd,
                  int inStart, int inEnd);
int main()
{
    //freopen("input.txt","r",stdin);

    int c;

    cin >> c;

    for(int i = 0; i < c; i++)
    {
        int n;
        cin >> n;

        vector<int> preorder;
        vector<int> inorder;
        vector<int> postorder;

        for(int j = 0; j < n; j++)
        {
            int number;
            cin >> number;

            preorder.push_back(number);
        }
        for(int j = 0; j < n; j++)
        {
            int number;
            cin >> number;

            inorder.push_back(number);
        }

        getPostorder(preorder,inorder,postorder,0,n,0,n);

        for(int j = 0; j < n; j++)
            cout << postorder[j] << " ";
        cout << endl;

    }
    return 0;
}

void getPostorder(vector<int>& preorder, vector<int>& inorder,
                  vector<int>& postorder, int preStart, int preEnd,
                  int inStart, int inEnd)
{
    if(preEnd == preStart || inEnd == inStart)
        return ;
    if(preEnd - preStart == 1)
    {
        postorder.push_back(preorder[preStart]);
        return ;
    }

    int cnt = 0;

    for(cnt = inStart; cnt < inEnd; cnt++)
    {
        if(inorder[cnt] == preorder[preStart])
            break;
    }
    getPostorder(preorder,inorder,postorder,preStart+1,preStart+1+(cnt-inStart),inStart,cnt);//LEFT CHILD
    getPostorder(preorder,inorder,postorder,preStart+1+(cnt-inStart),preEnd,cnt+1,inEnd);//RIGHT CHILD
    postorder.push_back(preorder[preStart]);

    return;
}
