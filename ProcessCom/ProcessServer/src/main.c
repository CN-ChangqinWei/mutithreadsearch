#include "../inc/list.h"
#include <stdio.h>
#include "../inc/Pipe.h"
#include "../inc/Server.h"
//#define SERVER	("SerPipe")

int main(){
	//list test
/*
	Head* phead=malloc(sizeof(Head));
	ListInit(phead);
	int arr[10]={0,1,2,3,4,5,6,7,8,9};
	ListTest(arr,sizeof(arr)/sizeof(int),phead);
	RemoveNode(5,phead);
	RemoveNode(4,phead);
	RemoveNode(0,phead);
	RemoveNode(9,phead);
	ListPrint(phead);
	return 0;
*/
	//Pipe test
/*	CreatePipe(10);
	CreatePipeByName(SERVER);
	RemovePipe(10);
	RemovePipeByName(SERVER);
	return 0;
*/
	//	
	ServerInit();
	ServerRecv();
	return 0;
}
