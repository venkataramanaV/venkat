#include <stdio.h>
/*
HOURGLASS SUM
find the max value of subarray with the format
a b c       b c d
  d           e
e f g       f g h    so on for 6x6 matrix
*/

main()
{
	int n=0;
	int r=0;
	int k=0,l=0;
	int sum,max=0;
	int i,j;

	int a[6][6] = {1,1,1,0,0,0,
                       0,1,0,0,0,0,
                       1,1,1,0,0,0,
                       0,0,2,4,4,0,
                       0,0,0,2,0,0,
                       0,0,1,2,4,0       
                      };

/*	for(i=0;i<6;i++)
	{
		   for(j=0;j<6;j++)
		   {       
				   //printf("update the array index a[%d][%d]\n",i,j);
				   scanf("%d",&a[i][j]);
		   }
	}
*/
	for(i=0;i<6;i++)
	{
		   for(j=0;j<6;j++)
		   {
				  printf("%d ",a[i][j]);
		   }              
		   printf("\n");
	}
              
       
        for(i=0;i<6;++i)
	{        
               for(j=0;j<6;++j)
               {
                       if(((j+2) < 6) && ((i+2) < 6))
                       {
                               printf("%d %d %d\n",a[i][j],a[i][j+1],a[i][j+2]);
                               printf("  %d   \n",a[i+1][j+1]);
                               printf("%d %d %d\n",a[i+2][j],a[i+2][j+1],a[i+2][j+2]); 
                                                             
                               sum = a[i][j] + a[i][j+1] + a[i][j+2] +
                                               a[i+1][j+1] +
                                     a[i+2][j] + a[i+2][j+1] + a[i+2][j+2];
                               printf("sum = %d\n",sum);
                               printf("\n");
                                              
                       }
                       if(sum > max)
                               max = sum;
               }
        }
        printf("max sum: %d\n",max);


}
/*
while(l<4)
{
       for(i=n;i<(n+3);i++)
       {
               while(k<4)
              {       
                      for(j=r;j<(r+3);j++)
                     {
                          sum[k]=a[i][j];
                     }
                      k++;
                     r++;
               }
              r=k=0;
              n++;
       }
       l++;
}       
*/
