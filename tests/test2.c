#include <stdio.h>
int main()
{
    char str[20];
    printf("Enter a string: ");
    scanf("%[^\n]%*c", str);
    printf("%s\n", str);

    return 0;
}