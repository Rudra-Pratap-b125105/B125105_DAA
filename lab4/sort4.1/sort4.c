#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int time;      // Time in minutes
    int type;      // +1 = entry, -1 = exit
} Event;

// Convert HH:MM into minutes 
int timeToMinutes(int hour, int minute)
{
    return hour * 60 + minute;
}

// Convert minutes back to HH:MM 
void printTime(int time)
{
    printf("%02d:%02d", time / 60, time % 60);
}

// Compare events by time 
int compare(const void *a, const void *b)
{
    Event *e1 = (Event *)a;
    Event *e2 = (Event *)b;

    return e1->time - e2->time;
}

int main()
{
    int n;

    printf("Enter number of people: ");
    scanf("%d", &n);

    Event *events = malloc(2 * n * sizeof(Event));

    if (events == NULL)
    {
        printf("Memory allocation failed.\n");
        return 1;
    }

    printf("\nEnter entry and exit time for each person (HH:MM):\n");

    for (int i = 0; i < n; i++)
    {
        int eh, em;
        int xh, xm;

        printf("Person %d: ", i + 1);

        scanf("%d:%d %d:%d", &eh, &em, &xh, &xm);

        events[2 * i].time = timeToMinutes(eh, em);
        events[2 * i].type = +1;

        events[2 * i + 1].time = timeToMinutes(xh, xm);
        events[2 * i + 1].type = -1;
    }

    // Sort all entry and exit events 
    qsort(events, 2 * n, sizeof(Event), compare);

    int current = 0;
    int maximum = 0;
    int maxTime = 0;

    // Scan the sorted events 
    for (int i = 0; i < 2 * n; i++)
    {
        current += events[i].type;

        if (current > maximum)
        {
            maximum = current;
            maxTime = events[i].time;
        }
    }

    printf("\n----------------------------------\n");

    printf("Maximum people present: %d\n", maximum);

    printf("Time when maximum occurred: ");
    printTime(maxTime);

    printf("\n----------------------------------\n");

    free(events);

    return 0;
}