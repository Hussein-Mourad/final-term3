#include <stdio.h>

int main()
{
    char str[20];
    int i;
    printf("Enter a number: ");
    scanf("%d\n", &i);
    printf("Enter a string: ");
    scanf("%[^\n]%*c", str);
    printf("%d\n", i);
    printf("%s\n", str);
}