#include<stdio.h>
int gcd(int j_a,int j_b)
{
    if (j_a == 0)
    {
        return j_b;
    }
    else if (j_b == 0)
    {
        return j_a;
    }
    /* If a and b both are same */
    else if (j_a == j_b)
    {
        return j_a;
    }
    /* If a is greater than b */
    else if (j_a > j_b)
    {
        return gcd(j_a-j_b, j_b);
    }
    else
    {
        return gcd(j_a, j_b-j_a);
    } 
}
int main()
{
    for (int j_i=1;j_i<=20;j_i++)
    {
        for(int j_j=1;j_j<=20;j_j++)
        {
            for(int j_k=1;j_k<=20;j_k++)
            {
                for(int j_m=1;j_m<=20;j_m++)
                {
                    int j_a,j_b,j_c,j_d;

                    /* To find common denomenator */

                    int j_lcm1=(j_i*j_j)/gcd(j_i,j_j);
                    int j_lcm2=(j_lcm1*j_k)/gcd(j_k,j_lcm1);
                    int j_lcm3=(j_lcm2*j_m)/gcd(j_m,j_lcm2);
                    int j_commonDenominator = j_lcm3;
                    
                    j_a=j_commonDenominator/j_i;
                    j_b=j_commonDenominator/j_j;
                    j_c=j_commonDenominator/j_k;
                    j_d=j_commonDenominator/j_m;

                    if(j_a+j_b+j_c+j_d==j_commonDenominator && j_i<=j_j && j_j<=j_k && j_k<=j_m)
                    {
                        printf("%d %d %d %d \n",j_i,j_j,j_k,j_m);
                    }
                }
            }
        }
    }
    return 0;
}