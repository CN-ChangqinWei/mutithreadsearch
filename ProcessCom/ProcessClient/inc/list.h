#ifndef _LIST_H
#define _LIST_H
#include<stdlib.h>
#include<stdio.h>
typedef struct node{
	int m_Value;
	int fd;
	struct node* m_pNext;

}Node;

typedef struct head{
	int m_Length;
	Node* m_Front;
	Node* m_Back;

}Head;

void NodeInit(Node* ptrnode,int value);

void ListInit(Head* ptrhead);

void AddNode(Node* ptrnode,Head* ptrhead);

void ClearList(Head* ptrhead);

void RemoveNode(int value,Head* ptrhead);

void ListTest(int *arr,int length,Head* ptrhead);

void ListPrint(Head* ptrhead);

Node* ListFind(Head* ptrhead,int value);

#endif

