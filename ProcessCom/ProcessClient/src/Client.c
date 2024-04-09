#include"../inc/Client.h"
#include"../inc/Server.h"
#include<string.h>
Head Process_lst;
int fd_Server;
int fd_Read;
void ClientInit(){
	char pipename[30]={0};
	sprintf(pipename,"%dPipe",getpid());
	CreatePipe(getpid());
	ListInit(&Process_lst);
	if(access(SERVER,R_OK)){
		printf("ServerPipe not exist\n");
		return;
	}
	fd_Server=open(SERVER,O_WRONLY);
	printf("ServerPipe open\n");
	if(access(pipename,R_OK)){
		printf("%s not exist\n",pipename);
		return;
	}
	fd_Read=open(pipename,O_RDONLY|FNONBLOCK);
	printf("RecvPipe Open\n");
}

void ClientDeal(PipeMsg msg){
	if(msg.aim==msg.from){
		int* p=(int*)msg.Content;
		ClearList(&Process_lst);
		while(*p){
			Node* pnode=malloc(sizeof(Node));
			NodeInit(pnode,*p);
			AddNode(pnode,&Process_lst);
			p++;	
		}		
	}else{
		printf("Process%d:%s\n",msg.from,msg.Content);
	}
}

void ClientSend(int aim,char* content){
	if(access(SERVER,R_OK)){
		printf("ServerPipe not exsit\n");
		return;	
	}
	PipeMsg msg;
	msg.aim=aim;
	msg.from=getpid();
	strcpy(msg.Content,content);
	WritePipe(msg,fd_Server);
		
}

void ClientRecv(){
	int num;
	char Buf[1024]={0};
	Node* p=Process_lst.m_Front->m_pNext;
	while(1){
		num=read(fd_Read,Buf,sizeof(PipeMsg));
		if(num>0){
			ClientDeal(*(PipeMsg*)Buf);
		}	
		if(p){
			ClientSend(p->m_Value,"test");
			p=p->m_pNext;
		}else{ 
			ClientSend((int)getpid(),"test");
			p=Process_lst.m_Front->m_pNext;
		}
		sleep(1);
	}
}
