#include"../inc/list.h"


void NodeInit(Node* ptrnode,int value){
	ptrnode->m_Value=value;
	ptrnode->m_pNext=NULL;
}

void ListInit(Head* ptrhead){
	ptrhead->m_Length=0;
	Node*p=malloc(sizeof(Node));
	NodeInit(p,0);
	ptrhead->m_Front=p;
	ptrhead->m_Back=p;
	printf("List init ok\n");
}
void AddNode(Node* ptrnode,Head* ptrhead){

	ptrhead->m_Length++;
	ptrhead->m_Back->m_pNext=ptrnode;
	ptrhead->m_Back=ptrnode;
}

void ClearList(Head* ptrhead){
	Node*p1;
	Node*p2;
	p1=ptrhead->m_Front;
	p2=p1->m_pNext;
	while(p1){
		p1=p2;
		if(p2) p2=p2->m_pNext;
		if(p1) free(p1);
		//p1=p2;
		//if(p2) p2=p2->m_pNext;
	}
	ptrhead->m_Length=0;
	ptrhead->m_Back=ptrhead->m_Front;
}

void RemoveNode(int value,Head* ptrhead){
	Node*p1;
	Node*p2;
	p1=ptrhead->m_Front;
	p2=p1->m_pNext;
	while(p2){
		if(p2->m_Value==value){
			p1->m_pNext=p2->m_pNext;
			if(p1->m_pNext==NULL){
				ptrhead->m_Back=p1;
			}
			ptrhead->m_Length--;
			free(p2);
			return;
		}
		p1=p1->m_pNext;
		p2=p2->m_pNext;
	}
}
void ListTest(int *arr,int length,Head* ptrhead){
	
	for(int i=0;i<length;i++){
		Node*p=malloc(sizeof(Node));
		NodeInit(p,arr[i]);
		AddNode(p,ptrhead);
		
	}
	ListPrint(ptrhead);
	
}

void ListPrint(Head* ptrhead){
	Node* p=ptrhead->m_Front->m_pNext;
	while(p){

		printf("%d ",p->m_Value);
		p=p->m_pNext;
	}
	printf("\n");
}
Node* ListFind(Head* ptrhead,int value){
	Node*p=ptrhead->m_Front->m_pNext;
	while(p){

		if(p->m_Value==value){
			return p;
		}
		p=p->m_pNext;
	}
	return NULL;
}
