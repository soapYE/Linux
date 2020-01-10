#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <stdlib.h>
#include <sys/un.h>
#include <pthread.h>
#include <arpa/inet.h>
 
int sockfd,newfd;
void *read_socket();
 
int main()
{
    int ret;
    pthread_t read_tid,write_tid;
    struct sockaddr_in server_addr;
    server_addr.sin_family=AF_INET;			    // ������ΪIPV4
    server_addr.sin_addr.s_addr=INADDR_ANY;		// �󶨵� INADDR_ANY ��ַ
    server_addr.sin_port=htons(5678);			// ע��˿�ת��
    sockfd=socket(AF_INET,SOCK_STREAM,0);
    if (sockfd<0)
    {
        exit(1);								// ����socket��������socket����������
    }
    ret=bind(sockfd,(struct sockaddr *)(&server_addr),sizeof(server_addr));
    perror("server");
    if (ret<0)
    {
        exit(2);								// ����bind�������׽������ַ����
    }
    ret=listen(sockfd,4);
    if (ret<0)
    {
        exit(3);								// ����listen��������
    }
	printf("�ȴ��ͻ������ӣ�\n");
    newfd=accept(sockfd,NULL,NULL);			
    if (newfd<0)
    {
        exit(4);								// ��������ʧ�ܣ�
    }
    printf("��������ͻ��˽������ӳɹ���\n");
    
    // ����һ���̣߳������socket��ȡ����
    pthread_create(&read_tid,NULL,read_socket,NULL);
    while(1)
    {
        sleep(10000);
    }
}
 
// ��socket��ȡ����
void *read_socket()
{
    int recv_num,recv_num_total=0;
    char recv_buf[50];
    while (1)
    {
        memset(recv_buf,0,sizeof(recv_buf));		// ���һ��recv_buf������
        recv_num=recv(newfd,recv_buf,26,0);
        if (recv_num<0)
            printf("�������˽���ʧ�ܣ�\n");
        else if(recv_num>0)
        {
            recv_num_total+=recv_num;
            printf("�������ˣ����ý��ճɹ�������Ϊ��%s\n���յ�%d���ֽڵ����ݡ�\n",recv_buf,recv_num_total);
            sync();
        }
        else
        {
            printf("����������ͻ��˵��������ж�\n");
			printf("�ȴ��ͻ������ӣ�\n");
            newfd=accept(sockfd,NULL,NULL);
        }
        sleep(1);
    }
} 
