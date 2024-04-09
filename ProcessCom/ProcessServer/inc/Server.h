#ifndef _SERVER_H
#define _SERVER_H
#define SERVER	("SerPipe")
#include "list.h"
#include "Pipe.h"
extern Head Client_lst;

void ServerInit();

void ServerSendTo(PipeMsg msg);

void ServerDealData(PipeMsg msg);

void ServerRecv();

#endif
