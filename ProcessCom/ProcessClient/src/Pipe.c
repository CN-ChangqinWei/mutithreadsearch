#include"../inc/Pipe.h"

char CreatePipe(int value){
	char PipeName[30]={0};
	sprintf(PipeName,"%dPipe",value);
	if(!access(PipeName,R_OK)){
		printf("Pipe existed!\n");
		return 1;
	}
	printf("Pipe %s create succeed\n",PipeName);
	mkfifo(PipeName,0644);
	return 0;
}

char CreatePipeByName(char* name){
	if(!access(name,R_OK)){
		printf("Pipe existed!\n");
		return 1;
	}
	printf("Pipe %s create succeed\n",name);
	mkfifo(name,0644);
	return 0;
	
}

void RemovePipe(int value){
	char PipeName[30]={0};
	sprintf(PipeName,"%dPipe",value);
	if(access(PipeName,R_OK)){
		printf("Pipe %s not existed\n",PipeName);
		return;
	}
	printf("Pipe %s removed\n",PipeName);
	unlink(PipeName);
}
void RemovePipeByName(char* name){

	if(access(name,R_OK)){
		printf("Pipe %s not existed\n",name);
		return;
	}
	printf("Pipe %s removed\n",name);
	unlink(name);

}
void WritePipe(PipeMsg msg,int fd){
	lseek(fd,0,SEEK_SET);
	char* buf=(char*)&msg;
	write(fd,buf,sizeof(msg));	
}

void ReadPipe(char* buf,int fd){
	lseek(fd,0,SEEK_SET);
	read(fd,buf,sizeof(PipeMsg));

}
