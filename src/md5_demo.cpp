#include <stdio.h>
#include "md5.h"

int main()
{
    int j,k;
    char *msg = "Not my code";
    ui *d = md5(msg, strlen(msg));
    WBunion u;

    printf("0x");
    for (j=0; j<4; j++)
    {
        u.w = d[j];
        for (k=0; k<4; k++)
        {
            printf("%02x", u.b[k]);
        }
    }
    printf("\n");

    return 0;
}
