#include <bits/stdc++.h>
using namespace std;
const int maxn = 1025;

bool isBST = true, isMAX = true, isMIN = true;
vector<int> bst;

struct node {
    int k, v;
    int lchild, rchild;
} Node[maxn];

void inorder(int root) {
    if(root == -1)
        return;
    inorder(Node[root].lchild);
    bst.push_back(Node[root].k);
    inorder(Node[root].rchild);
}

void ismax(int root) {
    if(Node[root].lchild == -1 && Node[root].rchild == -1)
        return;
    if(Node[root].lchild != -1) {
        if(Node[Node[root].lchild].v < Node[root].v) {
            ismax(Node[root].lchild);
        } else {
            isMAX = false;
            return;
        }
    }
    if(Node[root].rchild != -1) {
        if(Node[Node[root].rchild].v < Node[root].v) {
            ismax(Node[root].rchild);
        } else {
            isMAX = false;
            return;
        }
    }
}

void ismin(int root) {
    if(Node[root].lchild == -1 && Node[root].rchild == -1)
        return;
    if(Node[root].lchild != -1) {
        if(Node[Node[root].lchild].v > Node[root].v) {
            ismin(Node[root].lchild);
        } else {
            isMIN = false;
            return;
        }
    }
    if(Node[root].rchild != -1) {
        if(Node[Node[root].rchild].v > Node[root].v) {
            ismin(Node[root].rchild);
        } else {
            isMIN = false;
            return;
        }
    }
}

int main() {
    int n, root, l, r;
    scanf("%d", &n);
    int h[n + 1];
    fill(h, h + n + 1, 0);
    for(int i = 1; i <= n; i++)
        scanf("%d", &Node[i].k);
    for(int i = 1; i <= n; i++)
        scanf("%d", &Node[i].v);
    for(int i = 1; i <= n; i++) {
        scanf("%d%d", &l, &r);
        Node[i].lchild = l, Node[i].rchild = r;
        h[l] = 1, h[r] = 1;
    }
    for(int i = 1; i <= n; i++ ) {
        if(h[i] != 1)
            root = i;
    }
    inorder(root);
    ismax(root);
    ismin(root);
    for(int i = 0; i < bst.size() - 1; i++) {
        if(bst[i + 1] < bst[i]) {
            isBST = false;
            break;
        }
    }
    if(isBST && isMAX)
        printf("YES\nMAX HEAP");
    if(isBST && isMIN)
        printf("YES\nMIN HEAP");
    if((isBST == false && isMAX == true) || (isBST == false && isMIN == true))
        printf("NO\nNOT BST");
    if((isBST == true && isMAX == false) && (isBST == true && isMIN == false))
        printf("NO\nNOT HEAP");
    if((isBST == false && isMAX == false) && (isBST == false && isMIN == false))
        printf("NO\nNOT BST AND NOT HEAP");
    return 0;
}
