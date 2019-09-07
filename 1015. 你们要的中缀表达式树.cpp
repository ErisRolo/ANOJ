/**
* ��������׺���ʽ������ô��ò������ֹһ��ѹ�й����ˣ�����
*       ���ʽ�����������Ȼ������֮����У��ң����ӵĽ�㣬������������ǰ�����ż���
*       �ؼ����ڱ��ʽ��������㣬����������������һ�������ı��ʽ������һ�μ���
*       �����ܸ������Һ��ӵ�ֱֵ�Ӽ��㣬����Ҫ�������������ķ���ֵ���㣬��Ϊ��������������һ�����ʽ����������
*       ��˵ݹ�߽�Ҫ�ɿս���ΪҶ�ӽ��
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
