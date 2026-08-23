#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int point;
    int type;   // 1 = start, -1 = end
} Event;

/* Sort by point.
   If points are equal, start (+1) comes before end (-1).
*/
int compare(const void *a, const void *b)
{
    Event *e1 = (Event *)a;
    Event *e2 = (Event *)b;

    if (e1->point != e2->point)
        return e1->point - e2->point;

    return e2->type - e1->type;
}

int main()
{
    int n;

    printf("Enter number of intervals: ");
    scanf("%d", &n);

    Event *events = malloc(2 * n * sizeof(Event));

    if (events == NULL)
    {
        printf("Memory allocation failed.\n");
        return 1;
    }

    printf("\nEnter intervals (left right):\n");

    for (int i = 0; i < n; i++)
    {
        int l, r;

        printf("Interval %d: ", i + 1);
        scanf("%d %d", &l, &r);

        events[2 * i].point = l;
        events[2 * i].type = 1;

        events[2 * i + 1].point = r;
        events[2 * i + 1].type = -1;
    }

    /* Sort all endpoints */
    qsort(events, 2 * n, sizeof(Event), compare);

    int current = 0;
    int maximum = 0;
    int bestPoint = events[0].point;

    /* Sweep from left to right */
    for (int i = 0; i < 2 * n; i++)
    {
        current += events[i].type;

        if (current > maximum)
        {
            maximum = current;
            bestPoint = events[i].point;
        }
    }

    printf("\n----------------------------------\n");
    printf("Point with maximum overlap: %d\n", bestPoint);
    printf("Maximum number of intervals: %d\n", maximum);
    printf("----------------------------------\n");

    free(events);

    return 0;
}