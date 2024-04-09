#ifndef _PIPE_H
#define _PIPE_H
#include<sys/stat.h>
#include<sys/types.h>
#include<sys/fcntl.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
typedef struct msg{
	int aim;
	int from;
	char Content[100];
}PipeMsg;

char CreatePipe(int value);

char CreatePipeByName(char* name);

void RemovePipe(int value);

void RemovePipeByName(char* name);

void WritePipe(PipeMsg msg,int fd);

void ReadPipe(char* buf,int fd);



#endif
