/*************************************************************************
	> File Name: 1.c
	> Author: fly
	> Mail:fly@163.com 
	> Created Time: 2017年12月02日 星期六 22时20分41秒
 ************************************************************************/

#include<stdio.h>
#include <string>
#include <string>
#include <iostream>
#include <algorithm>
using namespace::std;

int Median3(int A[], int p, int q )
{
    int c = ( p + q ) / 2;
    if( A[p] > A[c] )
        swap<int>(A[p], A[c]);
    if( A[p] > A[q] )
        swap<int>(A[p], A[q]);
    if( A[c] > A[q] )
        swap<int>(A[c], A[q]);
        swap<int>(A[c],A[q-1]);
    return A[q-1];
}

int Partition( int A[], int p, int q )
{
    int key = Median3( A, p, q );
    int i = p;
    int j = q-1;
    while(1)
    {
         while( A[++i] < key ){}
         while( A[--j] > key ){}
         if( i < j )
             swap<int>( A[i], A[j] );
         else
         break;
     }
     swap( A[i], A[q-1] );
     return i;
}

void InsertionSort(int A[], int N)
{
     int tmp;
     int j;
     int p;

     for( p = 1; p < N; p++ )
     {
         tmp = A[p];
         for( j = p; j > 0 && A[j -1] > tmp; j -- )
         A[j] = A[j-1];
         A[j] = tmp;
     }
}

#define cutoff 5
void QuickSort(int A[], int p, int q)
{
    if( p + cutoff <= q )
    {
         int r = Partition(A, p, q);
         QuickSort( A, p, r - 1 );
         QuickSort( A, r + 1, q );
    }
    else
         InsertionSort(A + p, q - p + 1 );
}

int main()
{
    int A[8] = {6,10,13,5,8,3,2,11};
    QuickSort(A,0,7);
    for( int k = 0; k < 8; k++ )
    cout << A[k] << "  ";
    cout << endl;
}
