#include<stdio.h>

main()
{
       int num,len=0,rem=0,n=0,i;
       char str[10];
       
       printf("get the number num \n");
       scanf("%d",&num);
       
       n = num;
       while (n != 0)
       {
               len++;
               n = n/10;               
       }
       
       for(i=0;i<len;i++)
       {
               rem = num%10;
               num=num/10;
               str[len - (i+1)] = rem + '0';               
               printf("str[i] = %c", str[i]);
       }
       str[len] = '\0';
       printf("number : %s \n",str);
}      
