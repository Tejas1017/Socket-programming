//client program
#include"header.h"
int main(){
	int sfd;
	struct sockaddr_in serverId;
    	sfd=socket(AF_INET,SOCK_STREAM,0);
	if(sfd<0){
		perror("socket");
		return 0;
	}
	perror("socket");
	serverId.sin_family=AF_INET;
	serverId.sin_port=htons(3000);
	serverId.sin_addr.s_addr=inet_addr("127.0.0.1");
	int len =sizeof(serverId);
	if(connect(sfd,(struct sockaddr*)&serverId,len)<0){
		perror("connect");
		return 0;
	}
	perror("connect");
	////writing in file ->>
	char speakToServer[100];
	while(1){
		printf("Send your message to server \n");
		scanf("%[^\n]s",speakToServer);
		write(sfd,speakToServer,strlen(speakToServer)+1);
		sleep(1);
		read(sfd,speakToServer,sizeof(speakToServer));
		printf("server is saying: %s",speakToServer);
		if(strcmp(speakToServer,"bye")==0){
			break;
		}
	}
		close(sfd);

}
