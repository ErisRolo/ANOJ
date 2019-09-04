/**
* 分析：层序中序建树
**/

#include <bits/stdc++.h>
using namespace std;
const int maxn = 31;

int n, temp, root;
vector<int> layer;
int in[maxn];

struct Node {
    int data, lchild, rchild;
} node[maxn];

int idx = 0;
int create(vector<int> layer, int inl, int inr) {
    if(layer.size() == 0)
        return -1;
    int root = idx++;
    node[root].data = layer[0];
    int k;
    for(k = inl; k <= inr; k++) {
        if(in[k] == layer[0])
            break;
    }
    vector<int> left, right;
    for(int i = 1; i < layer.size(); i++) {
        bool isleft = false;
        for(int j = inl; j < k; j++) {
            if(in[j] == layer[i]) {
                isleft = true;
                break;
            }
        }
        if(isleft)
            left.push_back(layer[i]);
        else
            right.push_back(layer[i]);
    }
    node[root].lchild = create(left, inl, k - 1);
    node[root].rchild = create(right, k + 1, inr);
    return root;
}

int n1 = 0;
void preorder(int root) {
    if(root == -1)
        return;
    printf("%d", node[root].data);
    n1++;
    if(n1 != n)
        printf(" ");
    else
        printf("\n");
    preorder(node[root].lchild);
    preorder(node[root].rchild);
}

int n2 = 0;
void postorder(int root) {
    if(root == -1)
        return;
    postorder(node[root].lchild);
    postorder(node[root].rchild);
    printf("%d", node[root].data);
    n2++;
    if(n2 != n)
        printf(" ");
    else
        printf("\n");
}

int main() {
    scanf("%d", &n);
    for(int i = 0; i < n; i++) {
        scanf("%d", &temp);
        layer.push_back(temp);
    }
    for(int i = 0; i < n; i++)
        scanf("%d", &in[i]);
    root = create(layer, 0, n - 1);
    preorder(root);
    postorder(root);
    return 0;
}
