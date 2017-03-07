#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<malloc.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<sys/wait.h>
#include<error.h>
#include<stdlib.h>

struct info
{
       char id[6];
       char name[5];
       char sub[5];
} *nameinfo,*cnameinfo;

void idp_fc(); /*write id in parent, fetch details in child*/

int main()
{
       int fd,i,errno,rc;
       FILE *f1;
       char n[10];

       
       fd = open("/home/venkat/test.txt",O_RDWR | O_CREAT | O_EXCL,0777);
       if(fd == -1)
               printf("file not created properly\n");
               
       close(fd);
       
       f1 = fopen("/home/venkat/test.txt","a");
       
       if(f1 == NULL)
       {
               printf("file not opened properly to write\n");
               printf("error rc:%d",errno);
               //exit(0);
       }
       
       nameinfo = (struct info*)malloc(sizeof(struct info));
       
       for(i = 0;i<5;i++)
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
               
       idp_fc();    
       
       
}


void idp_fc()
{
	int rc,r,fd2[2],status,ofset,i;
	char buf[60],rec[2],rbuf[2];
	FILE *fdr;

	cnameinfo = (struct info*)malloc(sizeof(struct info));

	if (pipe(fd2) == -1)
	{
		perror("pipe not created properly\n" );
		exit(1);
	}

	rc = fork();

	if (rc == -1) {
		perror("child 1 not created properly");
		exit(1);
	}
	else if (rc == 0) {
		printf(" i m the child 1 : %d\n",getpid());
		/*Setting child as a read end*/
		close(fd2[1]); 
		read(fd2[0],rbuf,sizeof(rbuf));
                printf("child: fetching the record = %s\n",rbuf);
                
                r = atoi(rbuf);
                printf("child: fetching the record = %d\n",r);
                
		/* Fetch the particular record from the file */
		fdr = fopen("/home/venkat/test.txt","r+");
		if (fdr == NULL) {
			perror("file not opened properly");
			exit(1);
		}
		ofset = 0;
		/*while(feof(fdr))
		{
			memset(cnameinfo,'\0',sizeof(struct info));
			fread(rec,sizeof(struct info),0,fdr);
			memcpy(cnameinfo,rec,sizeof(struct info));
			
			if (strncmp(cnameinfo->id,rbuf,2) == 0) {
				printf("i m the record\n");
			}
			else {
				ofset = fseek(fdr,ofset,sizeof(struct info));
				if (ofset == -1) {
					perror("fseek error");
					exit(1);
				}
			}
		}*/
		printf("the sizeof struct = %d\n",sizeof(struct info));
		for (i=0;i<(r-1);i++) {
		     
		     fseek(fdr,sizeof(struct info),SEEK_CUR);
		     ofset = ftell(fdr);
		     printf("child: ofset = %d\n",ofset);
		}

                r = ftell(fdr);
                printf("child: Current Position = %d\n",r);
                memset(rec,'\0',sizeof(struct info));
                fread(rec,sizeof(struct info),1,fdr);
                printf("the record is rec = %s",rec);
                
		fclose(fdr);

	} 

	else {
		printf("i am the parent : %d\n",getpid());
		/*Setting parent as a write end*/
		close(fd2[0]);
		printf("fetch the record : \n");
		scanf("%s",rec);
		write(fd2[1],rec,sizeof(rec));
		wait(&status);
	}
}


