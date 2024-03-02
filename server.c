//server side
#include"header.h"
int main(){
	int sfd;
	int len;
    	sfd=socket(AF_INET,SOCK_STREAM,0);//Af_inet stand for ipv4 protocal and sock_stream is tcp communation
    	if(sfd<0){
		perror("socket file");
		return 0; 
	}
	perror("socket");
	/******************bind********************/
	/*struct sockAddr {
	 *	sa_famly sa_family;
	 *	char sa_data[14];
	 * }*/
	//above is geniric structure whenever we are going for ipv4 we need to select ipv4 structure
	//
	struct sockaddr_in serverId,clientId;
	serverId.sin_family=AF_INET;
	serverId.sin_port=htons(3000);//below 1024 are reversed
	//sin_port requried in fromat of network byte  that why htons 
	serverId.sin_addr.s_addr=inet_addr("0.0.0.0");//setting server ip which is loop back
	len =sizeof(serverId);
	if(bind(sfd,(struct sockaddr*)&serverId,len)<0){
		perror("bind");
		return 0;
	}
	perror("bind");
	/***************listen*******************************/
	if(listen(sfd,10)<0)
	{
		perror("listen");
		return 0 ;
	}
	perror("listen");
	/*********accept*********************************/

	int nsfd =accept(sfd,(struct sockaddr*)&clientId,&len);
	if(nsfd<0){
		perror("accept");
	}
	perror("accept");
	printf("client port id %d\n",clientId.sin_port);
	printf("client ip address is %s\n",inet_ntoa(clientId.sin_addr));
   /*
    listen();
    accept();
    read();
    write();
    */	
	char client[100];
	while(1){
		read(nsfd,client,sizeof(client));
		 if(strcmp(client,"bye")==0){
			                         break;
						                 }
		printf("client is saying->> %s \n",client);
   		printf("speak to client :\n");
		scanf("%[^\n]s",client);
		write(nsfd,client,strlen(client)+1);
		sleep(1);
		}
		close(nsfd);
    		close(sfd);
    
}
