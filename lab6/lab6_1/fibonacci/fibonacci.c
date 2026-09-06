#include <stdio.h>

int main(){
    int n, i;
    int dp[100];

    printf("Enter n: ");
    scanf("%d", &n);

    if (n == 0){
        printf("The 0th Fibonacci number is 0\n");
        return 0;
    }

    dp[0] = 0;
    dp[1] = 1;

    for (i = 2; i <= n; i++){
        dp[i] = dp[i - 1] + dp[i - 2];
        printf("%d\n", dp[i]);
    }

    printf("The %dth Fibonacci number is %d\n", n, dp[n]);

    return 0;
}