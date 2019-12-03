#include <stdio.h>

int busquedaBinaria(int datos[], int dim, int num);

int
main()
{
    int v[] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17};
    int dim = 17;
    for(int i = 0; i <= 17; i++)
    {
            printf("%d\n", busquedaBinaria(v, dim, i));
    }
    printf("%d\n", busquedaBinaria(v, dim, 19));
}

int
busquedaBinaria(int datos[], int dim, int num)
{
    if(dim == 0)
    {
        return 0;
    }
    if(datos[dim/2] == num)
    {
        return 1;
    }

    if(num < datos[dim/2])
    {
        return busquedaBinaria(datos, dim/2, num);
    }
    return busquedaBinaria(datos + dim/2 + 1, dim/2, num);
}
