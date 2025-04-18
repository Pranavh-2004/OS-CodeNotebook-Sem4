#include <stdio.h>

#define MAX_SEGMENTS 100

typedef struct
{
    unsigned short base;
    unsigned short limit;
} Segment;

int main()
{
    Segment st[MAX_SEGMENTS];
    unsigned short n;
    unsigned int la, pa;
    unsigned short sn;
    unsigned int off;

    printf("Enter the number of segments: ");
    scanf("%hu", &n);

    printf("Enter base and limit for each segment:\n");
    for (unsigned short i = 0; i < n; i++)
    {
        printf("Segment %hu -> Base: ", i);
        scanf("%hu", &st[i].base);
        printf("Segment %hu -> Limit: ", i);
        scanf("%hu", &st[i].limit);
    }

    printf("Enter the logical address (Segment Number and Offset): ");
    scanf("%hu %u", &sn, &off);

    if (sn >= n || off >= st[sn].limit)
    {
        printf("Invalid logical address! Segment number out of bounds or offset exceeds limit.\n");
        return 1;
    }

    pa = st[sn].base + off;

    printf("Logical Address: Segment %hu, Offset %hu\n", sn, off);
    printf("Physical Address: %u\n", pa);

    return 0;
}
