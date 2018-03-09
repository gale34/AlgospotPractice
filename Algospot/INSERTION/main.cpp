#include <iostream>
#include <vector>
#include <cstdio>
#include <cstdlib>

using namespace std;

typedef int KeyType;


struct Node {
    KeyType key;

    int priority, sizeNode;
    Node *left, *right;
    Node(const KeyType& key2) : key(key2), priority(rand()), sizeNode(1), left(NULL), right(NULL) {}

    void setLeft(Node* nextLeft)
    {
        left = nextLeft;
        calcSize();
    }
    void setRight(Node* nextRight)
    {
        right = nextRight;
        calcSize();
    }
    void calcSize()
    {
        sizeNode = 1;
        if(left)
            sizeNode += left->sizeNode;
        if(right)
            sizeNode += right->sizeNode;
    }
};

typedef pair<Node*, Node*> NodePair;

NodePair split(Node* root, KeyType key) {
    if(root == NULL)
        return NodePair(NULL,NULL);

    if(root->key < key)
    {
        NodePair rs = split(root->right, key);
        root->setRight(rs.first);
        return NodePair(root, rs.second);
    }

    NodePair ls = split(root->left, key);
    root->setLeft(ls.second);
    return NodePair(ls.first, root);
}

Node* insertNode(Node* root, Node* node)
{
    if(root == NULL)
        return node;

    if(root->priority < node->priority)
    {
        NodePair splitted = split(root, node->key);
        node->setLeft(splitted.first);
        node->setRight(splitted.second);
        return node;
    }
    else if(node->key < root->key)
        root->setLeft(insertNode(root->left,node));
    else
        root->setRight(insertNode(root->right,node));
    return root;
}

Node* mergeNode(Node* a, Node* b)
{
    if(a == NULL)
        return b;
    if(b == NULL)
        return a;
    if(a->priority < b->priority)
    {
        b->setLeft(mergeNode(a,b->left));
        return b;
    }
    a->setRight(mergeNode(a->right,b));
    return a;
}

Node* eraseNode(Node* root, KeyType key)
{
    if(root == NULL)
        return root;

    if(root->key == key)
    {
        Node* ret = mergeNode(root->left, root->right);
        delete root;
        return ret;
    }

    if(key < root->key)
        root->setLeft(eraseNode(root->left,key));
    else
        root->setRight(eraseNode(root->right,key));
    return root;
}

Node* kth(Node* root, int k)
{
    int leftSize = 0;
    if(root->left != NULL)
        leftSize = root->left->sizeNode;
    if(k <= leftSize)
        return kth(root->left, k);
    if(k == leftSize + 1)
        return root;

    return kth(root->right, k - leftSize - 1);
}

int countLessThan(Node* root, KeyType key)
{
    if(root == NULL)
        return 0;

    if(root->key >= key)
        return countLessThan(root->left, key);

    int ls = (root->left ? root->left->sizeNode : 0);
    return ls + 1 + countLessThan(root->right, key);
}
int main()
{
    int c,n;
    freopen("input.txt","r",stdin);

    cin >> c;

    for(int i = 0; i < c; i++)
    {
        vector<int> movement;

        cin >> n;

        for(int j = 0; j < n; j++)
        {
            int temp = 0;
            cin >> temp;

            movement.push_back(temp);
        }
    }


    cout << "Hello world!" << endl;
    return 0;
}
