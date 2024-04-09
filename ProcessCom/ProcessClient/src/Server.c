#include"Server.h"
#include<string.h>
Head Client_lst;
void ServerInit(){
	CreatePipeByName(SERVER);
	ListInit(&Client_lst);	
}

void ServerSendTo(PipeMsg msg){
	Node*p=ListFind(&Client_lst,msg.aim);
	char PipeName[30]={0};
	sprintf(PipeName,"%dPipe",msg.aim);
	if(!p){
		if(access(PipeName,R_OK))
		{
			printf("Send error Pipe %s not exist\n",PipeName);
			return;
		}
		p=malloc(sizeof(Node));
		NodeInit(p,msg.aim);
		AddNode(p,&Client_lst);
		p->fd=open(PipeName,O_WRONLY);
	}	
	WritePipe(msg,p->fd);	
}

void ServerDealData(PipeMsg msg){
	if(msg.aim==msg.from){
		memset(msg.Content,0,sizeof(msg.Content));
		Node*p=Client_lst.m_Front->m_pNext;
		int* p_data=(int*)msg.Content;
		while(p){
			*p_data=p->m_Value;
			p_data++;
			p=p->m_pNext;
		}
		ServerSendTo(msg);
	}else{
		ServerSendTo(msg);
	}

}
void ServerRecv(){
	pid_t pid=fork();
	if(pid>0){	
	if(access(SERVER,R_OK)){
		printf("Server pipe not exist\n");
		return;
	}
	int fd=open(SERVER,O_RDONLY|O_NONBLOCK);
	int num=0;
	char Buf[1024]={0};
	while(1){
		num=read(fd,Buf,sizeof(PipeMsg));
		if(num>0){
			PipeMsg* p=(PipeMsg*)Buf;
			ServerDealData(*p);
		}		
	}}
	else if(pid==0){
		while(1){
			sleep(1);
			printf("Runing\n");
		}
	}else{
		perror("fork fail");
	}
}

