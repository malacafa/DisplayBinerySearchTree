#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<windows.h>

typedef int element;		// ���� Ž�� Ʈ�� element�� �ڷ����� char�� ����

typedef struct treeNode {
	int key;				// ������ �ʵ�
	struct treeNode* left;	// ���� ���� Ʈ�� ��ũ �ʵ�
	struct treeNode* right;	// ������ ���� Ʈ�� ��ũ �ʵ�
} treeNode;

void gotoxy(int x, int y)
{
 COORD Cur;
 Cur.X=x;
 Cur.Y=y;
 SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),Cur);
}
// ���� Ž�� Ʈ������ Ű���� x�� ����� ��ġ�� Ž���ϴ� ����
treeNode* searchBST(treeNode* root, int x) {
	treeNode* p;
	p = root;
	while (p != NULL) {
		if (x < p->key) p = p->left;
		else if (x == p->key) return p;
		else p = p->right;
	}
	printf("\n ã�� Ű�� �����ϴ�!");
	return p;
}

// ������ p�� ����Ű�� ���� ���Ͽ� ��� x�� �����ϴ� ����
treeNode* insertNode(treeNode *p, int x) {
	treeNode *newNode;
	if (p == NULL) {
		newNode = (treeNode*)malloc(sizeof(treeNode));
		newNode->key = x;
		newNode->left = NULL;
		newNode->right = NULL;
		return newNode;
	}
	else if (x < p->key)  p->left = insertNode(p->left, x);
	else if (x > p->key)  p->right = insertNode(p->right, x);
	else  printf("\n �̹� ���� Ű�� �ֽ��ϴ�! \n");

	return p;
}

treeNode* temp =NULL;//������ 1�϶� ����� ������ ��� ���� temp ����
 
// ��Ʈ ������ Ž���Ͽ� Ű���� ���� ��带 ã�� �����ϴ� ����
int deleteNode(treeNode *root, element key) {
	
	treeNode *parent, *p, *succ, *succ_parent;
	treeNode *child;
	parent = NULL;
	p = root;
	
	while ((p != NULL) && (p->key != key)) {  // ������ ����� ��ġ Ž��
		parent = p;
		if (key < p->key) p = p->left;
		else p = p->right;
	}

	// ������ ��尡 ���� ���
	if (p == NULL) {
		printf("\n ã�� Ű�� ���� Ʈ���� �����ϴ�!!");
		return 0;
	}

	// ������ ��尡 �ܸ� ����� ���
	if ((p->left == NULL) && (p->right == NULL)) {
		if (parent != NULL) {
			if (parent->left == p) parent->left = NULL;
			else parent->right = NULL;
		}
		else
		{
			free(root);
			return 1;	
		}
	}

	// ������ ��尡 �ڽ� ��带 �� �� ���� ���
	else if ((p->left == NULL) || (p->right == NULL)) {
		if (p->left != NULL) child = p->left;
		else child = p->right;

		if (parent != NULL) {
			if (parent->left == p) parent->left = child;
			else parent->right = child;
		}
		else temp = child; // ������ 1�� ��� temp�� ������ �ش�. 
	}

	// ������ ��尡 �ڽ� ��带 �� �� ���� ���
	else {
		succ_parent = p;
		succ = p->left;
		while (succ->right != NULL) { // ���� ���� Ʈ������ �İ��� ã��
			succ_parent = succ;
			succ = succ->right;
		}
		if (succ_parent->left == succ)  succ_parent->left = succ->left;
		else succ_parent->right = succ->left;
		p->key = succ->key;
		p = succ;
	}
	free(p);
	return 0;
}

void delallNode(treeNode* root) // ������ȸ �ϸ鼭 ���������ش�. 
{
	if(root){
		delallNode(root->left);
		delallNode(root->right);
		free(root);
	}
}

treeNode* delAllNode(treeNode* root) // ������ȸ �ϸ鼭 ������Ű�� delallNode�� �����Ű�� key���� ���� ���ο� ��带 ����� ��ȯ�Ѵ�. 
{
	delallNode(root);
	treeNode* temp = malloc(sizeof(treeNode));
	temp->left=NULL;
	temp->right=NULL;
	return temp;
}

// ���� Ž�� Ʈ���� ���� ��ȸ�ϸ鼭 ����ϴ� ����
void displayInorder(treeNode* root){
	if (root) {
		displayInorder(root->left);
		printf("%d_", root->key);
		displayInorder(root->right);	
	}
}

int f(int n) // 2�� n���� ���Ͽ� return �Ѵ�. 
{
	if(n==1)
		return 1;
	return 2*f(n-1);
}

void print(treeNode * root,int x,int y,int lvl) //Ʈ���� ��ȸ�Ѵ�. �ڽ��� 2�� (����-n) �ϋ� 2�� (����-n-1��) ��ŭ ���ϰ� ���鼭 �¿��带 ����Ѵ�. 
{
	if(root)
	{
		gotoxy(x,10+y*2);
		printf("%d",root->key,y,f(lvl+1-y));
		gotoxy(x-f(lvl+1-y)+2,12+y*2);
		if(root->right!=NULL||root->left!=NULL)	
		for(int i=0;i<=2*f(lvl+1-y)-2;i++)
			printf("_");
		print(root->left,x-f(lvl+1-y),y+1,lvl);
		print(root->right,x+f(lvl+1-y),y+1,lvl);
	}
}

int getLevel(treeNode* root) // Ž���ϸ鼭 �ִ� ������ ���ؼ� return �Ѵ�. 
{
    if (root == NULL) return 0;

    int llvl = getLevel(root->left);
    int rlvl = getLevel(root->right);

    if (llvl > rlvl) return llvl + 1;
    else return rlvl + 1;
}

void printTree(treeNode * root) // tree�� ���̸� ���ϰ� ���̿� ���� ����ϴ� print �Լ��� ȣ���Ѵ�. 
{
	int lvl=getLevel(root);
	print(root,f(lvl+1),1,lvl);
}

void printEmpty(treeNode * root) // tree��ŭ�� ������ ����Ѵ�. 
{
	int lvl=getLevel(root);
	for(int i=0;i<1+lvl*2+1;i++)
	{
		for(int j=0;j<4*f(lvl);j++)
			printf(" ");
		printf("\n");
	}
}

void menu() {
	printf("\n*---------------------------*");
	printf("\n\t1 : Ʈ�� ���");
	printf("\n\t2 : Ʈ�� ���� ���");
	printf("\n\t3 : ���� ����");
	printf("\n\t4 : ���� ����");
	printf("\n\t5 : ���� �˻�");
	printf("\n\t6 : ��ü ����");
	printf("\n\t7 : ����"); 
	printf("\n*---------------------------*");
	printf("\n�޴��Է� >> ");
}

int main() {
	
	treeNode* root = NULL;
	treeNode* foundedNode = NULL;
	char choice;
	int key;
	int n=0;
	// [�׸� 7-38]�� ���� �ʱ� ���� Ž�� Ʈ���� �����ϰ� 
	// ��� G�� ��Ʈ ��� ������ root�� ����
	root=insertNode(root,32);
    insertNode(root,16);   insertNode(root,48);
    insertNode(root,8);      insertNode(root,24);   insertNode(root,40);    insertNode(root,56);
    insertNode(root,4);      insertNode(root,12);    insertNode(root,20);    insertNode(root,28);    insertNode(root,36);   insertNode(root,44);   insertNode(root,52);    insertNode(root,60);
    insertNode(root,2);     insertNode(root,6);      insertNode(root,10);    insertNode(root,14);    insertNode(root,18);    insertNode(root,22);   insertNode(root,26);    insertNode(root,30);
    insertNode(root,34);    insertNode(root,38);   insertNode(root,42);    insertNode(root,46);    insertNode(root,50);    insertNode(root,54);   insertNode(root,58);    insertNode(root,62);
    insertNode(root,1);      insertNode(root,3);      insertNode(root,5);      insertNode(root,7);      insertNode(root,9);      insertNode(root,11);   insertNode(root,13);    insertNode(root,15);
    insertNode(root,17);      insertNode(root,19);   insertNode(root,21);   insertNode(root,23);   insertNode(root,25);   insertNode(root,27);   insertNode(root,29);    insertNode(root,31);
    insertNode(root,33);    insertNode(root,35);   insertNode(root,37);   insertNode(root,39);   insertNode(root,41);   insertNode(root,43);   insertNode(root,45);    insertNode(root,47);
    insertNode(root,49);    insertNode(root,51);   insertNode(root,53);   insertNode(root,55);   insertNode(root,57);   insertNode(root,59);   insertNode(root,61);    insertNode(root,63);

	while (1) {
		printf("\n�ƹ� Ű�� ������ ���");
		getch();
		system("cls");
		
		menu();
		scanf(" %c", &choice);

		switch (choice - '0') {
		case 1:	printf("\t[���� Ʈ�� ���]  ");
			if(n==1) // n �� 1 �� ���� key ���� ���ǵ��� ���� root node �Ѱ� �ۿ� ���� ��츦 �ǹ��Ѵ�. 
				printf("Empty tree");
			
			else
				displayInorder(root);	

			printf("\n");
			break;

		case 3:	printf("������ ���ڸ� �Է��ϼ��� : ");
			if(n!=1) 
				printTree(root);
			gotoxy(27,11);
			scanf(" %d", &key);
			if(n!=1)
				printEmpty(root);
			if(n==1){// n �� 1 �� ��� �̹� ���ǵ� ���� root ��忡 key ���� �����Ѵ�. 
				root->key=key;
				n=0;
			}
			else
				insertNode(root, key);
			printTree(root);
			break;

		case 4:	printf("������ ���ڸ� �Է��ϼ��� : ");
			printTree(root);
			gotoxy(27,11);
			scanf(" %d", &key);
			printEmpty(root);
			int t=deleteNode(root, key);
			if(t==1)// ������ ������ ����� 1 �� return �ǰ�, �̶� ���ο� ���� ��带 �����.  
			{
				root=malloc(sizeof(treeNode));
				root->right=NULL;
				root->left=NULL;
				n=1;
			}
			else if(temp!=NULL) // root �� ������ 1�� ��� ����� ������ ������ ���� ������ temp ���. 
			{
				root=temp;
				temp=NULL;
			}
			if(n!=1)
				printTree(root);
			break;

		case 5: printf("ã�� ���ڸ� �Է��ϼ��� : ");
			scanf(" %d", &key);
			foundedNode = searchBST(root, key);
			if (foundedNode != NULL)
				printf("\n %d�� ã�ҽ��ϴ�! \n", foundedNode->key);
			else  printf("\n ���ڸ� ã�� ���߽��ϴ�. \n");
			break;

		case 6: 
			printf("�� �������");
			root = delAllNode(root);
			n=1;
			break; 
		
		case 7: 	return 0;
		
		case 2:
			if(n==1) // n �� 1 �� ���� key ���� ���ǵ��� ���� root node �Ѱ� �ۿ� ���� ��츦 �ǹ��Ѵ�. 
				printf("<<<<<<<<<<<Empty tree>>>>>>>>>>");
			else
				printTree(root);
			break;
			
		default: printf("���� �޴��Դϴ�. �޴��� �ٽ� �����ϼ���! \n");
			break;
		}
	}
}
