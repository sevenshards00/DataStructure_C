/*
* 비선형 자료구조 - 연결 리스트 기반 이진 트리
* 파일명: BinaryTree.c
* 파일 버전: 0.2
* 작성자: Sevenshards
* 작성 일자: 2023-11-23
* 이전 버전 작성 일자: 2023-11-23
* 버전 내용: 전위, 중위 순회 추가 및 순회 시 할 일을 결정할 수 있도록 함수 포인터 사용.
* 이전 버전 내용: 중위 순회 기능까지 포함한 이진 트리 구현.
*/
// 저자의 표현을 빌리자면, 이진 트리를 구현"할 수 있는 도구"를 만드는 과정이다.
// 어디다 갖다 쓸 것인가는 나중에 생각하자.
#include <stdio.h>
#include <stdlib.h>
#include "BinaryTree.h"

// 노드의 생성 및 데이터 저장과 조회
BTreeNode* MakeBTreeNode(void) // 이진 트리의 노드 생성
{
	BTreeNode* node = (BTreeNode*)malloc(sizeof(BTreeNode));
	node->left = NULL;
	node->right = NULL;
	return node;
}

BTData GetData(BTreeNode* bt) // 이진 트리 노드의 데이터를 반환 (Getter)
{
	return bt->data;
}

void SetData(BTreeNode* bt, BTData data) // 이진 트리 노드에 데이터를 저장 (Setter)
{
	bt->data = data;
}

BTreeNode* GetLeftSubTree(BTreeNode* bt) // 왼쪽 서브 트리의 주소 값(왼쪽 서브 트리의 루트 노드)을 반환
{
	return bt->left;
}
BTreeNode* GetRightSubTree(BTreeNode* bt) // 오른쪽 서브 트리의 주소 값(오른쪽 서브 트리의 루트 노드)을 반환
{
	return bt->right;
}

// 노드의 연결
void MakeLeftSubTree(BTreeNode* main, BTreeNode* sub) // 매개변수 sub로 전달된 트리 또는 노드를 매개변수 main의 왼쪽 서브트리로 연결
{
	if (main->left != NULL) // 이미 왼쪽에 연결된 트리나 노드가 있다면
		free(main->left); // 할당된 메모리를 해제한다.
	
	main->left = sub; // 그리고 새로 왼쪽에 연결한다.
}

void MakeRightSubTree(BTreeNode* main, BTreeNode* sub) // 매개 변수 sub로 전달된 트리 또는 노드를 매개변수 main의 오른쪽 서브트리로 연결
{
	if (main->right != NULL) // 이미 오른쪽에 연결된 트리나 노드가 있다면
		free(main->right); // 할당된 메모리를 해제한다.

	main->right = sub; // 그리고 새로 오른쪽에 연결한다.
}

// 순회 (재귀를 이용하여 구현한다!)
// 중위 순회 1)왼쪽 서브 트리 -> 2)루트 노드 -> 3)오른쪽 서브 트리
void InorderTraversal(BTreeNode* bt, VisitFuncPtr action)
{
	if (bt == NULL) // 만약 공집합 노드(NULL)이라면? 재귀의 탈출 조건이 된다.
		return;

	InorderTraversal(bt->left, action); // 1) 왼쪽 서브 트리를 순회
	action(bt->data); // 2) 루트 노드를 방문
	InorderTraversal(bt->right, action); // 3) 오른쪽 서브 트리를 순회
}
// 전위 순회 1)루트 노드 -> 2)왼쪽 서브 트리 -> 3)오른쪽 서브 트리
void PreorderTraversal(BTreeNode* bt, VisitFuncPtr action)
{
	if (bt == NULL) // 만약 공집합 노드(NULL)이라면? 재귀의 탈출 조건이 된다.
		return;

	action(bt->data); // 1) 루트 노드를 방문
	PreorderTraversal(bt->left, action); // 2) 왼쪽 서브 트리를 순회
	PreorderTraversal(bt->right, action); // 3) 오른쪽 서브 트리를 순회
}
// 후위 순회 1)왼쪽 서브 트리 -> 2)오른쪽 서브트리 -> 3)루트 노드
void PostorderTraversal(BTreeNode* bt, VisitFuncPtr action)
{
	if (bt == NULL) // 만약 공집합 노드(NULL)이라면? 재귀의 탈출 조건이 된다.
		return;

	PostorderTraversal(bt->left, action); // 1) 왼쪽 서브 트리를 순회
	PostorderTraversal(bt->right, action); // 2) 오른쪽 서브 트리를 순회
	action(bt->data); // 3) 루트 노드를 방문
}

// 트리의 모든 노드 삭제
void DeleteTree(BTreeNode* bt)
{
	if (bt == NULL) // 공집합 노드(NULL)이라면 재귀 탈출.
		return;

	// 후위 순회를 통해 왼쪽, 그리고 오른쪽, 마지막으로 루트 노드를 비우는 형태로 진행.
	DeleteTree(bt->left);
	DeleteTree(bt->right);

	printf("delete tree node data: %d\n", bt->data);
	free(bt);
}