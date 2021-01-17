#include <stdio.h>
int main()
{
    int d, m, year;
    printf("Enter date (dd/mm/yy): ");
    scanf("%d/%d/%d", &d, &m, &year);
    if (d % 10 == 1 && d != 11)
        printf("%d st", d);
    else if (d % 10 == 2 && d != 12)
        printf("%d nd", d);
    else if (d % 10 == 3 && d != 13)
        printf("%d rd", d);
    else
        printf("%d th", d);
    return 0;
}
// #include <stdio.h>
// #include <time.h>

// int main()
// {
//     time_t s;
//     struct tm *current_time;

//     s = time(NULL);

//     current_time = localtime(&s);

//     printf("Current year = %d\n", (current_time->tm_year+1900));

//     return 0;
// }