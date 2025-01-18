//  g++ -std=c++17 main.cpp Random1.cpp -o monte_carlo_simple
#include "Random1.h"
#include <iostream>
#include <cmath>
using namespace std;
// This function implements the Simple Monte Carlo simulation for pricing a European call option.
// The Monte Carlo method simulates multiple possible future price paths for the underlying asset
// and calculates the average payoff at expiry, discounted back to the present value.

double SimpleMonteCarlo1(double Expiry,
                         double Strike,
                         double Spot,
                         double Vol,
                         double r,
                         unsigned long NumberOfPaths){
    // Calculate variance, root variance, and Ito correction term based on the input volatility and expiry.
    double variance = Vol*Vol*Expiry;
    double rootVariance = sqrt(variance);
    double itoCorrection = -0.5*variance;
    // Calculate the adjusted starting spot price considering the interest rate and Ito correction.
    double movedSpot = Spot*exp(r*Expiry +itoCorrection);
    
    double thisSpot;
    double runningSum=0;
    // Loop through each path to simulate the future price of the asset.
    for (unsigned long i=0; i < NumberOfPaths; i++){
        // Generate a random Gaussian value for the simulation.
        double thisGaussian = GetOneGaussianByBoxMuller();
        // Calculate the spot price at expiry using the Gaussian random variable.
        thisSpot = movedSpot*exp( rootVariance*thisGaussian);
        // Calculate the payoff for a call option (spot price - strike price).
        double thisPayoff = thisSpot - Strike;
        // If the payoff is negative, set it to zero (European call option payoff).
        thisPayoff = thisPayoff >0 ? thisPayoff : 0;
        // Accumulate the sum of all payoffs.
        runningSum += thisPayoff;
    }
    // Calculate the average payoff by dividing the total by the number of paths.
    double mean = runningSum / NumberOfPaths;
    // Discount the average payoff to the present value.
    mean *= exp(-r*Expiry);
    // Return the calculated price of the option.
    return mean;
}

int main(){
    // Declare variables to store the input values for the option.
    double Expiry;
    double Strike;
    double Spot;
    double Vol;
    double r;
    unsigned long NumberOfPaths;
    // Prompt the user for the required input parameters.
    cout << "\nEnter expiry\n";
    cin >> Expiry;
    cout << "\nEnter strike\n";
    cin >> Strike;
    cout << "\nEnter spot\n";
    cin >> Spot;
    cout << "\nEnter vol\n";
    cin >> Vol;
    cout << "\nr\n";
    cin >> r;
    cout << "\nNumber of paths\n";
    cin >> NumberOfPaths;
    // Call the SimpleMonteCarlo1 function to calculate the option price.
    double result = SimpleMonteCarlo1(  Expiry,
                                        Strike,
                                        Spot,
                                        Vol,
                                        r,
                                        NumberOfPaths);
    
    // Output the calculated price of the option.
    cout <<"the price is " << result << "\n";
    // Wait for user input before exiting (typically used to pause the program).
    double tmp;
    cin >> tmp;
    return 0;
}
