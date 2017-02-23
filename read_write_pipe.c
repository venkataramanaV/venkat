#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<malloc.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<sys/wait.h>

struct info
{
       char id[6];
       char name[5];
       char sub[5];
} *nameinfo,*cnameinfo;

void rp_cw();

int main()
{
       int fd,i,errno,rc;
       FILE *f1;
       char n[10];

       
       fd = open("/home/venkat/venkat/test.txt",O_RDWR | O_CREAT | O_EXCL,0777);
       if(fd == -1)
               printf("file not created properly\n");
               
       close(fd);
       
       f1 = fopen("/home/venkat/venkat/test.txt","a");
       
       if(f1 == NULL)
       {
               printf("file not opened properly to write\n");
               printf("error rc:%d",errno);
               //exit(0);
       }
       
       nameinfo = (struct info*)malloc(sizeof(struct info));
       
       for(i = 0;i<2;i++)
       {       
               memset(nameinfo,'\0',sizeof(struct info));
               memset(n,'\0',10);
               printf("get the id:\n");
               scanf("%s",n);
               memmove(nameinfo->id,n,sizeof(n));
               
               memset(n,'\0',10);
               printf("get the name:\n");
               scanf("%s",n);
               memmove(nameinfo->name,n,sizeof(n));
               
               memset(n,'\0',10);
               printf("get the sub:\n");
               scanf("%s",n);
               memmove(nameinfo->sub,n,sizeof(n));
               
               rc = fwrite(nameinfo,sizeof(struct info),1,f1);
               
               if (rc == 0)               
                       printf("file write err \n");
               
               
       }
       rc = fclose(f1);
       
       free(nameinfo);
               
       if(rc != 0)
               printf("file write close err \n");
               
       rp_cw();    
       
       
}

void rp_cw()
{
       int filedes[2];
       int errno,status;
       char *buf;
       FILE *fp;
       FILE *fw;
       
       nameinfo = (struct info*)malloc(sizeof(struct info));
       cnameinfo = (struct info*)malloc(sizeof(struct info));
       buf = (char *)malloc(sizeof(struct info));
       
       pipe(filedes);
       
       if(fork() == 0)
       {
               /* i m the child 
                  i have to get write the details
                  fetched from my parent */
                  
               if(close(filedes[1]) == -1)
                       printf("child: err in closing read end des = %d\n",errno);

               sleep(5);
 
               if (read(filedes[0], buf, sizeof(struct info)) != sizeof(struct info))
                       printf("child: err in reading in fd[1] = %d\n",errno); 
                       
               memcpy(cnameinfo,buf,sizeof(struct info));
                                     
               printf("child: %s %s %s \n",cnameinfo->id,cnameinfo->name,cnameinfo->sub);
       
       }
       else 
       {
               /* i am the parent
                  i have to give the read input
                  to my chile */
                  
               if(close(filedes[0]) == -1)
                       printf("Parent: err in closing write end des = %d\n",errno);
                       
               fp = fopen("/home/venkat/venkat/test.txt","r+");
               
               if (fp == NULL)
                       printf("Parent: err in opening a file to read = %d ",errno);
                       
               if (fread(buf,sizeof(struct info),1,fp) == -1)
                       printf("Parent: err in reading a file = %d\n ",errno);

               memcpy(nameinfo,buf,sizeof(struct info));
               printf("Parent: %s %s %s\n",nameinfo->id,nameinfo->name,nameinfo->sub);                       
               
               if (write(filedes[1], buf, sizeof(struct info)) != sizeof(struct info))
                       printf("Parent: err in witing in fd[1] = %d\n",errno);               
                       
               printf("Parent: %s %s %s\n",nameinfo->id,nameinfo->name,nameinfo->sub); 
                       
               wait(&status);

       }
}
