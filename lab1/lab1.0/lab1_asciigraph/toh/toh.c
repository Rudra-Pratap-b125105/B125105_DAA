#include <stdio.h>

#define MAX_DISKS 10
#define HEIGHT 20

int main()
{
    int moves[MAX_DISKS + 1];
    int maxMoves = (1 << MAX_DISKS) - 1;

    for (int i = 1; i <= MAX_DISKS; i++)
        moves[i] = (1 << i) - 1;

    printf("\nTower of Hanoi\n");
    printf("\n");

    for (int row = HEIGHT; row >= 0; row--)
    {
        int level = (maxMoves * row) / HEIGHT;

        printf("%4d |", level);

        for (int col = 1; col <= MAX_DISKS; col++)
        {
            if (moves[col] >= level &&
                moves[col] < level + maxMoves / HEIGHT)
                printf("   *");
            else
                printf("    ");
        }

        printf("\n");
    }

    printf("     +-------------------------------------------->\n");
    printf("       ");

    for (int i = 1; i <= MAX_DISKS; i++)
        printf("%4d", i);

    printf("\n");
    printf("             Number of Disks\n\n");
    printf("Moves:\n");
    for (int i = 1; i <= MAX_DISKS; i++)
        printf("n = %2d   Moves = %4d\n", i, moves[i]);

    return 0;
}