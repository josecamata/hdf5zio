#ifndef BE6A052D_EB4E_48B2_B69D_3C892204ED82
#define BE6A052D_EB4E_48B2_B69D_3C892204ED82

#include <iostream>
#include <math.h>


template <typename T>
void change_places(T *x, T *y){
    T temp = *y;
    *y = *x;
    *x = temp;
}

template <typename T>
void maxHeapify(T *array, int i, int n) 
{
    int l = 2*i + 1;
    int r = 2*i + 2;
    int m = i;

    if(l < n && array[l] > array[m]){
        m = l;
    }

    if(r < n && array[r] > array[m]){
        m = r;
    }

    if(m != i){
        change_places(&array[i], &array[m]);
        maxHeapify(array, m, n);
    }
}

template <typename T>
void buildHeapMax(T *array, int n){
    for(int i = n/2 - 1; i >= 0; i--){
        maxHeapify(array, i, n);
    }
}

template <typename T>
void heapSort(T *array, int n){

    buildHeapMax(array, n);
    
    for (int i = n-1; i > 0; i--)
    {
        change_places(&array[0], &array[i]);
        maxHeapify(array, 0, i);
    }
}
#endif /* BE6A052D_EB4E_48B2_B69D_3C892204ED82 */
