#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<windows.h>

typedef int element;		// 이진 탐색 트리 element의 자료형을 char로 정의

typedef struct treeNode {
	int key;				// 데이터 필드
	struct treeNode* left;	// 왼쪽 서브 트리 링크 필드
	struct treeNode* right;	// 오른쪽 서브 트리 링크 필드
} treeNode;

void gotoxy(int x, int y)
{
 COORD Cur;
 Cur.X=x;
 Cur.Y=y;
 SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),Cur);
}
// 이진 탐색 트리에서 키값이 x인 노드의 위치를 탐색하는 연산
treeNode* searchBST(treeNode* root, int x) {
	treeNode* p;
	p = root;
	while (p != NULL) {
		if (x < p->key) p = p->left;
		else if (x == p->key) return p;
		else p = p->right;
	}
	printf("\n 찾는 키가 없습니다!");
	return p;
}

// 포인터 p가 가리키는 노드와 비교하여 노드 x를 삽입하는 연산
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
	else  printf("\n 이미 같은 키가 있습니다! \n");

	return p;
}

treeNode* temp =NULL;//차수가 1일때 생기는 에러를 잡기 위한 temp 변수
 
// 루트 노드부터 탐색하여 키값과 같은 노드를 찾아 삭제하는 연산
int deleteNode(treeNode *root, element key) {
	
	treeNode *parent, *p, *succ, *succ_parent;
	treeNode *child;
	parent = NULL;
	p = root;
	
	while ((p != NULL) && (p->key != key)) {  // 삭제할 노드의 위치 탐색
		parent = p;
		if (key < p->key) p = p->left;
		else p = p->right;
	}

	// 삭제할 노드가 없는 경우
	if (p == NULL) {
		printf("\n 찾는 키가 이진 트리에 없습니다!!");
		return 0;
	}

	// 삭제할 노드가 단말 노드인 경우
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

	// 삭제할 노드가 자식 노드를 한 개 가진 경우
	else if ((p->left == NULL) || (p->right == NULL)) {
		if (p->left != NULL) child = p->left;
		else child = p->right;

		if (parent != NULL) {
			if (parent->left == p) parent->left = child;
			else parent->right = child;
		}
		else temp = child; // 차수가 1인 경우 temp에 대입해 준다. 
	}

	// 삭제할 노드가 자식 노드를 두 개 가진 경우
	else {
		succ_parent = p;
		succ = p->left;
		while (succ->right != NULL) { // 왼쪽 서브 트리에서 후계자 찾기
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

void delallNode(treeNode* root) // 후위순회 하면서 삭제시켜준다. 
{
	if(root){
		delallNode(root->left);
		delallNode(root->right);
		free(root);
	}
}

treeNode* delAllNode(treeNode* root) // 후위순회 하면서 삭제시키는 delallNode를 실행시키고 key값이 없는 새로운 노드를 만들어 반환한다. 
{
	delallNode(root);
	treeNode* temp = malloc(sizeof(treeNode));
	temp->left=NULL;
	temp->right=NULL;
	return temp;
}

// 이진 탐색 트리를 중위 순회하면서 출력하는 연산
void displayInorder(treeNode* root){
	if (root) {
		displayInorder(root->left);
		printf("%d_", root->key);
		displayInorder(root->right);	
	}
}

int f(int n) // 2의 n승을 구하여 return 한다. 
{
	if(n==1)
		return 1;
	return 2*f(n-1);
}

void print(treeNode * root,int x,int y,int lvl) //트리를 순회한다. 자신이 2의 (높이-n) 일떄 2의 (높이-n-1승) 만큼 더하고 빼면서 좌우노드를 출력한다. 
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

int getLevel(treeNode* root) // 탐색하면서 최대 층수를 구해서 return 한다. 
{
    if (root == NULL) return 0;

    int llvl = getLevel(root->left);
    int rlvl = getLevel(root->right);

    if (llvl > rlvl) return llvl + 1;
    else return rlvl + 1;
}

void printTree(treeNode * root) // tree의 높이를 구하고 높이에 따라 출력하는 print 함수를 호출한다. 
{
	int lvl=getLevel(root);
	print(root,f(lvl+1),1,lvl);
}

void printEmpty(treeNode * root) // tree만큼의 공백을 출력한다. 
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
	printf("\n\t1 : 트리 출력");
	printf("\n\t2 : 트리 구조 출력");
	printf("\n\t3 : 문자 삽입");
	printf("\n\t4 : 문자 삭제");
	printf("\n\t5 : 문자 검색");
	printf("\n\t6 : 전체 삭제");
	printf("\n\t7 : 종료"); 
	printf("\n*---------------------------*");
	printf("\n메뉴입력 >> ");
}

int main() {
	
	treeNode* root = NULL;
	treeNode* foundedNode = NULL;
	char choice;
	int key;
	int n=0;
	// [그림 7-38]과 같은 초기 이진 탐색 트리를 구성하고 
	// 노드 G를 루트 노드 포인터 root로 지정
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
		printf("\n아무 키나 눌러서 계속");
		getch();
		system("cls");
		
		menu();
		scanf(" %c", &choice);

		switch (choice - '0') {
		case 1:	printf("\t[이진 트리 출력]  ");
			if(n==1) // n 이 1 인 경우는 key 값이 정의되지 않은 root node 한개 밖에 없는 경우를 의미한다. 
				printf("Empty tree");
			
			else
				displayInorder(root);	

			printf("\n");
			break;

		case 3:	printf("삽입할 문자를 입력하세요 : ");
			if(n!=1) 
				printTree(root);
			gotoxy(27,11);
			scanf(" %d", &key);
			if(n!=1)
				printEmpty(root);
			if(n==1){// n 이 1 인 경우 이미 정의된 단일 root 노드에 key 값만 대입한다. 
				root->key=key;
				n=0;
			}
			else
				insertNode(root, key);
			printTree(root);
			break;

		case 4:	printf("삭제할 문자를 입력하세요 : ");
			printTree(root);
			gotoxy(27,11);
			scanf(" %d", &key);
			printEmpty(root);
			int t=deleteNode(root, key);
			if(t==1)// 마지막 노드까지 지우면 1 이 return 되고, 이때 새로운 공백 노드를 만든다.  
			{
				root=malloc(sizeof(treeNode));
				root->right=NULL;
				root->left=NULL;
				n=1;
			}
			else if(temp!=NULL) // root 의 차수가 1일 경우 생기는 에러를 잡을때 전역 포인터 temp 사용. 
			{
				root=temp;
				temp=NULL;
			}
			if(n!=1)
				printTree(root);
			break;

		case 5: printf("찾을 문자를 입력하세요 : ");
			scanf(" %d", &key);
			foundedNode = searchBST(root, key);
			if (foundedNode != NULL)
				printf("\n %d를 찾았습니다! \n", foundedNode->key);
			else  printf("\n 숫자를 찾지 못했습니다. \n");
			break;

		case 6: 
			printf("다 지웠어요");
			root = delAllNode(root);
			n=1;
			break; 
		
		case 7: 	return 0;
		
		case 2:
			if(n==1) // n 이 1 인 경우는 key 값이 정의되지 않은 root node 한개 밖에 없는 경우를 의미한다. 
				printf("<<<<<<<<<<<Empty tree>>>>>>>>>>");
			else
				printTree(root);
			break;
			
		default: printf("없는 메뉴입니다. 메뉴를 다시 선택하세요! \n");
			break;
		}
	}
}
