#include <stdio.h>

int main()
{
    unsigned short pt[100], n, ps;
    unsigned int la, pa;
    unsigned short pn, off;

    printf("Enter the number of pages: ");
    scanf("%hu", &n);
    printf("Enter the page size (in bytes): ");
    scanf("%hu", &ps);

    printf("Enter the frame number for each page:\n");
    for (unsigned short i = 0; i < n; i++)
    {
        printf("Page %hu -> Frame: ", i);
        scanf("%hu", &pt[i]);
    }

    printf("Enter the logical address: ");
    scanf("%u", &la);

    pn = la / ps;
    off = la % ps;

    if (pn >= n)
    {
        printf("Invalid logical address! Page number out of bounds.\n");
        return 1;
    }

    pa = pt[pn] * ps + off;

    printf("Logical Address: %u (Page: %hu, Offset: %hu)\n", la, pn, off);
    printf("Physical Address: %u\n", pa);

    return 0;
}
