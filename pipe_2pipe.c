#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<sys/wait.h>
#include<sys/stat.h>
int main()
{
	int fd1[2],fd2[2];
	int rc,rc2;
	char buf_c[1024];
	char buf_cc[1024];
	int status;
	if (pipe(fd1) == -1)
	{
		perror("pipe 1 not created properly");
		exit(1);
	}
	
	rc = fork();
	
	if (rc == -1)
	{
		perror("child 1 not created properly");
		exit(1);
	} 
	else if (rc == 0)
	{
		printf("i am the child\n");
		/*make this child process to read from fd1[0]*/
		
		close(fd1[1]);
//		dup2(fd1[0],0);
		
//		memset(buf_c,'\0',1024);

//		if (read(fd1[0],buf_c,1024) == -1)
//		{
//			perror("read err in child\n");
//			exit(1);
//		}
		
//		printf("buf_c : %s\n",buf_c);

		if (pipe(fd2) == -1)
		{
			perror("pipe 2 not created properly");
			exit(1);
		}

		rc2 = fork();
		if (rc2 == -1)
		{
			perror("child creation err");
			exit(1);
		}
		else if (rc2 == 0)
		{
			printf("i am the child's child\n");
			close(fd2[1]);
			//memset(buf_cc,'\0',1024);
			
			//read(fd2[0],buf_cc,1024);
			dup2(fd1[0],0);
			dup2(fd2[1],1);
			//read(0,buf_cc,1024);
			
			//printf("buf_cc : %s\n",buf_cc);
			execl("/usr/bin/wc","wc",NULL);
			printf("exec error\n");
			exit(1);

		}
		else
		{
			wait(&status);
			printf("i am the main child\n");
			close(fd2[0]);
			//write(fd2[1],buf_c,1024);
		
		}
	}
	else
	{
		printf("i am the parent\n");
		/*make this parent process to write in fd1[1]*/

		close(fd1[0]);
		dup2(fd1[1],1);
		execlp("ls","ls","-l","/home/venkat",NULL);
		printf("exec error\n");
		exit(1);
		
	}
	
}
