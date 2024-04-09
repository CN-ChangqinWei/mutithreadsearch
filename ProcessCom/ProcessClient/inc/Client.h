#ifndef _CLIENT_H
#define _CLIENT_H
#include"Pipe.h"
#include"list.h"
extern Head Process_lst;

void ClientInit();

void ClientDeal(PipeMsg msg);

void ClientSend(int aim,char* content);

void ClientRecv();

#endif
