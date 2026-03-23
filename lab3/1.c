#include <stdio.h> 
#include <locale.h> 


int main()
{
    setlocale(LC_ALL, "Russian");
    int a, b, c;
    printf("¬ведите кол-во машин:"); 
    scanf_s("%d", &b);
    printf("¬ведите цену за одну машину:"); 
    scanf_s("%d", &a);
    c = a * b;
    printf("ќбща€ выручка составл€ет:%d", c);
    return 0; 
}
