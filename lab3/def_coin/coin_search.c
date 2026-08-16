#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*
   Print coins and their weights in a section
*/
void printSection(int coins[], int low, int high)
{
    printf("Coins   : ");

    for (int i = low; i <= high; i++)
        printf("%d ", i + 1);

    printf("\nWeights : ");

    for (int i = low; i <= high; i++)
        printf("%d ", coins[i]);

    printf("\n");
}

/*
   Calculate total weight of a group
 */
int totalWeight(int coins[], int low, int high)
{
    int sum = 0;

    for (int i = low; i <= high; i++)
        sum += coins[i];

    return sum;
}

/*
   Simulated balance scale
*/
int balance(int coins[],
            int l1, int r1,
            int l2, int r2)
{
    int sum1 = totalWeight(coins, l1, r1);
    int sum2 = totalWeight(coins, l2, r2);

    printf("\nLEFT  GROUP : ");
    for (int i = l1; i <= r1; i++)
        printf("%d(%d) ", i + 1, coins[i]);

    printf("\nRIGHT GROUP: ");
    for (int i = l2; i <= r2; i++)
        printf("%d(%d) ", i + 1, coins[i]);

    printf("\n");

    printf("\nTotal weight of LEFT  group = %d", sum1);
    printf("\nTotal weight of RIGHT group = %d\n", sum2);

    if (sum1 < sum2)
    {
        printf("Result: LEFT group is LIGHTER.\n");
        return -1;
    }
    else if (sum1 > sum2)
    {
        printf("Result: RIGHT group is LIGHTER.\n");
        return 1;
    }
    else
    {
        printf("Result: BOTH GROUPS ARE EQUAL.\n");
        return 0;
    }
}

/*
   Divide and Conquer Search
*/
int findDefective(int coins[],
                  int low,
                  int high,
                  int *step)
{
    int n = high - low + 1;

    printf("\n");
    printf("====================================================\n");
    printf("STEP %d\n", ++(*step));
    printf("====================================================\n");

    printf("Current section being searched:\n");
    printSection(coins, low, high);

    printf("\nNumber of coins in current section = %d\n", n);

    /*
       One coin remains
    */
    if (n == 1)
    {
        printf("\nOnly coin %d remains.\n", low + 1);
        printf("Weight of coin %d = %d\n",
               low + 1, coins[low]);

        if (coins[low] < 10)
        {
            printf("Coin %d is LIGHTER than 10.\n",
                   low + 1);

            return low;
        }
        else
        {
            printf("Coin %d has weight 10.\n",
                   low + 1);

            printf("Therefore, NO defective coin exists.\n");

            return -1;
        }
    }

    /*
       Two coins remain
    */
    if (n == 2)
    {
        printf("\nOnly two coins remain.\n");

        int result = balance(coins,
                             low, low,
                             high, high);

        if (result == -1)
        {
            return low;
        }
        else if (result == 1)
        {
            return high;
        }
        else
        {
            printf("Both coins have equal weight.\n");
            printf("Therefore, NO defective coin exists here.\n");

            return -1;
        }
    }

    /*
       Divide the section
    */

    int half = n / 2;

    int leftLow = low;
    int leftHigh = low + half - 1;

    int rightLow;
    int rightHigh;

    int extra = -1;

    if (n % 2 == 0)
    {
        /* Equal groups */
        rightLow = leftHigh + 1;
        rightHigh = high;
    }
    else
    {
        /*
           Odd number:
           Leave one coin aside.
        */
        rightLow = high - half + 1;
        rightHigh = high;

        extra = low + half;
    }

    printf("\nDIVIDE:\n");

    printf("Left group : ");
    for (int i = leftLow; i <= leftHigh; i++)
        printf("%d(%d) ", i + 1, coins[i]);

    printf("\nRight group: ");
    for (int i = rightLow; i <= rightHigh; i++)
        printf("%d(%d) ", i + 1, coins[i]);

    if (extra != -1)
        printf("\nExtra coin : %d(%d)",
               extra + 1, coins[extra]);

    printf("\n");

    /*
       Compare two groups
    */

    int result = balance(coins,
                         leftLow, leftHigh,
                         rightLow, rightHigh);

    /*
       LEFT LIGHTER
    */
    if (result == -1)
    {
        printf("\nSearching LEFT group next.\n");

        return findDefective(coins,
                             leftLow,
                             leftHigh,
                             step);
    }

    /*
       RIGHT LIGHTER
    */
    else if (result == 1)
    {
        printf("\nSearching RIGHT group next.\n");

        return findDefective(coins,
                             rightLow,
                             rightHigh,
                             step);
    }

    /*
       GROUPS EQUAL
    */
    else
    {
        /*
           If an extra coin exists, it is the only
           possible defective coin.
        */
        if (extra != -1)
        {
            printf("\nThe two groups are equal.\n");
            printf("Only the extra coin can possibly be defective.\n");

            printf("\nChecking extra coin %d:\n",
                   extra + 1);

            printf("Weight = %d\n", coins[extra]);

            if (coins[extra] < 10)
            {
                printf("Coin %d is lighter than 10.\n",
                       extra + 1);

                return extra;
            }
            else
            {
                printf("Coin %d has weight 10.\n",
                       extra + 1);

                printf("Therefore NO defective coin exists.\n");

                return -1;
            }
        }

        /*
           No extra coin and both groups equal.
           Therefore all coins in this section are
           perfect.
        */
        printf("\nBoth groups have equal weight.\n");
        printf("There is no remaining coin to check.\n");
        printf("Therefore NO defective coin exists in this section.\n");

        return -1;
    }
}

/*
   MAIN
*/
int main()
{
    int n;
    int choice;
    int defectivePosition = -1;
    int defectiveWeight = 10;

    srand(time(NULL));

    printf("====================================================\n");
    printf("          DEFECTIVE COIN SEARCH\n");
    printf("          DIVIDE AND CONQUER\n");
    printf("====================================================\n");

    /*
       Get number of coins
    */
    printf("\nEnter number of coins: ");
    scanf("%d", &n);

    if (n < 2)
    {
        printf("At least 2 coins are required.\n");
        return 0;
    }

    int *coins = (int *) malloc(n * sizeof(int));

    if (coins == NULL)
    {
        printf("Memory allocation failed.\n");
        return 1;
    }

    /*
       Normal coin weight = 10
    */
    for (int i = 0; i < n; i++)
        coins[i] = 10;

    printf("\nWeight of every normal coin = 10\n");

    /*
       Select defective coin
    */

    printf("\nHow do you want to select the defective coin?\n");
    printf("1. Choose position manually\n");
    printf("2. Generate position randomly\n");
    printf("3. No defective coin\n");

    printf("\nEnter choice: ");
    scanf("%d", &choice);

    /*
       MANUAL POSITION
    */
    if (choice == 1)
    {
        printf("\nEnter defective coin position (1-%d): ",
               n);
        scanf("%d", &defectivePosition);

        if (defectivePosition < 1 ||
            defectivePosition > n)
        {
            printf("Invalid position.\n");
            free(coins);
            return 1;
        }

        defectivePosition--;

        /* Ask for defective weight */
        do
        {
            printf("Enter weight of defective coin (<= 10): ");
            scanf("%d", &defectiveWeight);

            if (defectiveWeight > 10 || defectiveWeight < 0)
                printf("Invalid weight! Weight must be <= 10.\n");

        } while (defectiveWeight > 10 ||
                 defectiveWeight < 0);

        coins[defectivePosition] = defectiveWeight;
    }

    /*
       RANDOM POSITION
    */
    else if (choice == 2)
    {
        defectivePosition = rand() % n;

        printf("\nRandom defective position = %d\n",
               defectivePosition + 1);

        do
        {
            printf("Enter weight of defective coin (<= 10): ");
            scanf("%d", &defectiveWeight);

            if (defectiveWeight > 10 || defectiveWeight < 0)
                printf("Invalid weight! Weight must be <= 10.\n");

        } while (defectiveWeight > 10 ||
                 defectiveWeight < 0);

        coins[defectivePosition] = defectiveWeight;
    }

    /*
       NO DEFECTIVE COIN
    */
    else if (choice == 3)
    {
        defectivePosition = -1;
        defectiveWeight = 10;

        printf("\nAll coins have weight 10.\n");
        printf("There is NO defective coin.\n");
    }

    else
    {
        printf("Invalid choice.\n");
        free(coins);
        return 1;
    }

    /*
       Display initial arrangement
    */
    printf("\n====================================================\n");
    printf("INITIAL COIN ARRANGEMENT\n");
    printf("====================================================\n");

    printf("Coin positions: ");

    for (int i = 0; i < n; i++)
        printf("%d ", i + 1);

    printf("\nWeights       : ");

    for (int i = 0; i < n; i++)
        printf("%d ", coins[i]);

    printf("\n");

    /*
       This is only for verification of the simulation.
       The searching algorithm itself does not use it.
    */
    if (defectivePosition != -1)
    {
        printf("\n[For verification] Actual defective coin = %d\n",
               defectivePosition + 1);

        printf("[For verification] Its weight = %d\n",
               defectiveWeight);
    }

    /*
       Start searching
    */

    printf("\n\nStarting Divide and Conquer Search...\n");

    int step = 0;

    int result = findDefective(coins,
                               0,
                               n - 1,
                               &step);

    /*
       Final result
    */

    printf("\n\n====================================================\n");
    printf("                  FINAL RESULT\n");
    printf("====================================================\n");

    if (result == -1)
    {
        printf("No defective coin found.\n");
        if (defectivePosition == -1)
            printf("VERIFIED: All coins have weight 10.\n");
        else
            printf("ERROR: Defective coin was at position %d.\n",
                   defectivePosition + 1);
    }
    else
    {
        printf("Defective coin found at position: %d\n",
               result + 1);

        printf("Weight of defective coin: %d\n",
               coins[result]);

        if (result == defectivePosition)
            printf("VERIFIED: Correct defective coin found!\n");
        else
            printf("ERROR: Incorrect result.\n");
    }

    printf("\nTotal search steps = %d\n", step);

    free(coins);

    return 0;
}