#include <iostream>
using namespace std;

//function prototype
int coins(int amount);

/***************************************
* main()
***************************************/
int main()
{
    int cents, n;

    // Get user input

    cout << "Enter an amount in cents: ";
    cin >> cents;

    // Call recursive function

    n = coins(cents);
    cout << endl;

    // Output results

    cout << n << " coins" << endl;

    return 0;
}

//function definition
int coins(int sum)
{
    int total_coins = 0;
    int coinvalues[] = { 25,10,5,1 };
    int i = 0;

    //base case - user enters a value equal to zero or less than zero
    if (sum <= 0)
    {
        //return
        return 0;
    }
    else
    {
        //check if sum is more than a quarter
        if (sum >= coinvalues[i])
        {
            cout << coinvalues[i] << " ";

            //now, subtract that amount from the coins left
            sum -= coinvalues[i];
            //check if the changed amount in this case is equal to one of the coin values (sum will now be zero)
            if (sum == 0)
            {
                total_coins += 1; //that was the last coin
                return total_coins; // return total coins
            }

            //if the sum does not equal zero
            //check if the modulo is equal to the coin value - if it is not, count another coin
            else
            {
                total_coins = 1 + coins(sum);
            }
        }

        //check if sum is more than a dime
        else if (sum >= coinvalues[i+1])
        {
            cout << coinvalues[i+1] << " ";
            //now, subtract that amount from the coins left
            sum -= coinvalues[i+1];
            //check if the changed amount in this case is equal to one of the coin values (sum will now be zero)
            if (sum == 0)
            {
                total_coins += 1; //that was the last coin
                return total_coins; // return total coins
            }
            //if the sum does not equal zero
            //check if the modulo is equal to the coin value - if it is not, count another coin
            else
            {
                total_coins = 1 + coins(sum);
            }
        }

        //check if sum is more than a nickel
        else if (sum >= coinvalues[i+2])
        {
            cout << coinvalues[i+2] << " ";

            //now, subtract that amount from the coins left
            sum -= coinvalues[i+2];


            //check if the changed amount in this case is equal to one of the coin values (sum will now be zero)
            if (sum == 0)
            {
                total_coins += 1; //that was the last coin
                return total_coins; // return total coins
            }

            //if the sum does not equal zero
            //check if the modulo is equal to the coin value - if it is not, count another coin
            else
            {
                total_coins = 1 + coins(sum);

            }
        }

        //check if sum is more than a penny 
        else
        {
            cout << coinvalues[i+3] << " ";

            //now, subtract that amount from the coins left
            sum -= coinvalues[i+3];
            //check if the changed amount in this case is equal to one of the coin values (sum will now be zero)
            if (sum == 0)
            {
                total_coins += 1; //that was the last coin
                return total_coins; // return total coins
            }

            //if the sum does not equal zero
            //check if the modulo is equal to the coin value - if it is not, count another coin
            else
            {
                total_coins = 1 + coins(sum);
            }
        }
    }
    return total_coins;
}