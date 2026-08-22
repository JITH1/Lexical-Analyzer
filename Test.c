#include<stdio.h>

#define MAX 100
#define SUM(a,b) 

int main()
{
    int n ;

    scanf("%d",&n);

    int arr[n];

    printf("\nEnter the array elements : \n");
    for(int i = 0 ; i<n ; i++)
    scanf("%d",&arr[i]);

    int start = 0 , end = n-1 ;

    while(start<end)
    {
        while(arr[start]%2==0 && start<end)
        start++;

        while(arr[end]%2!=0 && start<end)
        end--;

        if(start<end)
        {
            int temp = arr[start];
            arr[start] = arr[end];
            arr[end] = temp ;
        }
    }

    printf("\nAfter Swap : \n");

    for(int i = 0 ; i<n ; i++)
    printf("%d ",arr[i]);

    return 0;

}