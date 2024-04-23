#include<stdio.h>
#include<stdlib.h>
#include<sys/stat.h>
#include<sys/fcntl.h>
#include<sys/types.h>
#include<unistd.h>
#include<pthread.h>
#include<string.h>
#include<regex.h>
FILE* fd;
int fdw;
char* bufB;
char* bufA;
char* res;
pthread_mutex_t lock;
pthread_cond_t cd1;
pthread_cond_t cd2;
pthread_cond_t cd3;
char str[100]={0};
void * thread_readline(void* arg){
	pthread_mutex_lock(&lock);
	pthread_cond_wait(&cd1,&lock);	
	usleep(100);	
	while(0==feof(fd))
	{	
	pthread_mutex_unlock(&lock);
		printf("A excute\n");
	//	pthread_mutex_unlock(&lock);	
		pthread_mutex_lock(&lock);
		printf("A Lock\n");
		bzero(bufA,1024);
		fgets(bufA,1024,fd);
		printf("awake B\n");
		pthread_cond_signal(&cd2);
		printf("A wait\n");
		pthread_cond_wait(&cd1,&lock);
		usleep(100);
	}
	return 0;
}

void * thread_ensurecontent(void*arg){
	pthread_mutex_lock(&lock);
	pthread_cond_wait(&cd2,&lock);
	regex_t reg;
	//char str[100]={0};
	char regstr[100]={0};
	sprintf(regstr,".*%s.*",str);
	printf("%s\n",regstr);
	int err=regcomp(&reg,regstr,REG_EXTENDED|REG_NEWLINE);
	if(err){
		perror("regcomp");
		exit(0);
	}
	regmatch_t regmatch[3];
	int c;
	while(1){
	pthread_mutex_unlock(&lock);
		printf("B excute\n");
		pthread_mutex_lock(&lock);
		printf("B lcok\n");
		c=regexec(&reg,bufA,1,regmatch,0);
		printf("%s",bufA);	
		printf("B regex excute c=%d\n",c);
		if(0==c){
			printf("str start cating\n");
			//strcat(bufB,bufA);//duan cuo wu
			pthread_cond_signal(&cd3);
			pthread_cond_wait(&cd2,&lock);
			usleep(100);
			printf("str cating\n");
			continue;
		}else if(c==REG_NOMATCH){
			printf("awake A\n");
			pthread_cond_signal(&cd1);
			pthread_cond_wait(&cd2,&lock);
			usleep(100);
		}else{
			perror("regexec");	
			exit(0);	

		}
	}
	return 0;
}

void * thread_writetobuf(void*arg){
	pthread_mutex_lock(&lock);
	pthread_cond_wait(&cd3,&lock);
	while(1){
		pthread_mutex_unlock(&lock);	
		printf("C excute\n");
		pthread_mutex_lock(&lock);
		printf("C lock\n");
		write(fdw,bufA,strlen(bufA));
		lseek(fdw,0,SEEK_END);
		//fwrite(bufA,1,strlen(bufA),fdw);
		printf("C write\n");
		pthread_cond_signal(&cd1);
		pthread_cond_wait(&cd3,&lock);
		//pthread_mutex_unlock(&lock);
	}//free(bufB);
	//free(bufA);
	exit(0);
}

int main(int argc,char* argv[]){

	if(argc!=3){
		printf("too few args!\n");
		return 0;
	}

	if(access(argv[2],R_OK)){
		printf("%s not exist!\n",argv[2]);
		return 0;
	}
	strcpy(str,argv[1]);
	pthread_cond_init(&cd1,0);
	pthread_cond_init(&cd2,0);
	pthread_cond_init(&cd3,0);
	pthread_mutex_init(&lock,0);
	//int fds=open(argv[2],O_RDONLY);
	//int size=lseek(fd,0,SEEK_END);
	//close(fds);
	//char* bufBr=(char*)malloc(size);
	//bufB=bufBr;
	char* bufAr=(char*)malloc(1024);
	bufA=bufAr;
	//memset(bufA,0,1024);
	//memset(bufB,0,size);duan cuo wu
	//FILE* fd;
	fd=fopen(argv[2],"r");
	char filew[100]={0};
	sprintf(filew,"%snew",argv[2]);
	fdw=open(filew,O_WRONLY|O_CREAT|O_TRUNC,0777);
	//fdw=fopen(filew,"w");
	pthread_t tid[3];
	pthread_create(tid,NULL,thread_readline,NULL);
	sleep(0);
	pthread_create(tid+1,NULL,thread_ensurecontent,NULL);
	sleep(0);
	pthread_create(tid+2,NULL,thread_writetobuf,NULL);
	sleep(0);
	//pthread_mutex_unlock(&lock);
	pthread_cond_signal(&cd1);
	//pthread_cond_signal(&cd2);
	//pthread_cond_signal(&cd3);
	while(feof(fd)==0) sleep(1);
	//fclose(fd);
	//fclose(fdw);
	//free(bufBr);
	//free(bufAr);
	exit(0);
}


