/**
* 分析：中缀表达式树，这么看貌似晴神不止一次压中过题了？？？
*       表达式即中序遍历，然后根结点之外的有（右）孩子的结点，遍历左右子树前加括号即可
*       关键在于表达式结果的运算，遍历完右子树后获得一个完整的表达式，进行一次计算
*       但不能根据左右孩子的值直接计算，而是要根据左右子树的返回值计算，因为左右子树可能是一个表达式产生计算结果
*       因此递归边界要由空结点改为叶子结点
**/

#include <bits/stdc++.h>
using namespace std;
const int maxn = 31;

int n,root;
string c,a,b;
bool isRoot[maxn];

struct Node {
	string data;
	int lchild,rchild;
} node[maxn];

double cal(string op,double a,double b) {
	if(op=="+")
		return a+b;
	else if(op=="-")
		return a-b;
	else if(op=="*")
		return a*b;
	else if(op=="/")
		return a/b;
}

string str;
double inorder(int root) {
	int l=node[root].lchild,r=node[root].rchild;
	if(l==-1&&r==-1) {
		str+=node[root].data;
		return stod(node[root].data);
	}
	if(isRoot[root]==false&&r!=-1) {
		str+="(";
		double left=inorder(l);
		str+=node[root].data;
		double right=inorder(r);
		str+=")";
		return cal(node[root].data,left,right);
	} else {
		double left=inorder(l);
		str+=node[root].data;
		double right=inorder(r);
		return cal(node[root].data,left,right);
	}
}

int main() {
	fill(isRoot,isRoot+maxn,true);
	scanf("%d",&n);
	for(int i=0; i<n; i++)
		cin>>node[i].data;
	for(int i=0; i<n; i++) {
		cin>>a>>b;
		if(a=="-")
			node[i].lchild=-1;
		else {
			node[i].lchild=stoi(a);
			isRoot[stoi(a)]=false;
		}
		if(b=="-")
			node[i].rchild=-1;
		else {
			node[i].rchild=stoi(b);
			isRoot[stoi(b)]=false;
		}
	}
	for(int i=0; i<n; i++) {
		if(isRoot[i]) {
			root=i;
			break;
		}
	}
	double ans=inorder(root);
	printf("%s %.2f",str.c_str(),ans);
	return 0;
}
