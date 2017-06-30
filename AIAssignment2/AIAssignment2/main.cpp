//
//  main.cpp
//  AIAssignment2
//  Created by Kendall Weistroffer on 10/26/16.
//  Copyright © 2016 Kendall Weistroffer. All rights reserved.
//
//  This assignment uses MCMC with Gibbs sampling to solve for the probabilty
//  of rain given that the sprinkler was on last night based on the given network diagram
//  This algorithm is based on the psudocode provided in Stuart Russell and Peter Norvig's
//  Artificial Intelligence text book, found on pgs. 536-537. For the work showing how the probabilities were
//  computed for rain and cloudy being true, please see the attached work sheet along with the assignment's
//  submission. The probabilities for wetGrass were determined based on the table included in the assignment.

#include <iostream>

//Global variables:
//Counter counts the times that rain is true
//The boolean variables are used to track whether or not a specific event is true, or has occured.
//The sprinkler variable is always set to true based on the scope of this particular problem.
int counter = 0;
bool cloudy = false;
bool sprinkler = true;
bool rain = false;
bool wetGrass = false;

/*
    The cloudyMethod sets the boolean variable 'cloudy' to true or false based on the value of rain (T/F) and 
    a precomputed probability of cloudy being true based on the value of rain. Using Bayes, I found that cloudy
    has a probability of (4/9) of being true given that rain is true, and a probability of (1/21) of being true 
    given that rain is false. It is important to remember that the value of sprinkler is always set for true for
    these probabilities.
 */
void cloudyMethod(){
    
    if(rain && rand()%9 < 4){
        cloudy = true;
    }
    else if (!rain && rand()%21 <1){
        cloudy  = true;
    }
    else{
        cloudy = false;
    }
}
/*
    The rainMethod sets the boolean variable 'rain' to true or false based on the value of cloudy (T/F),
    wetGrass (T/F) and a precomputed probability of rain being true based on the value of cloudy & wetGrass.
    Using Bayes, I found that rain has a probability of (22/27) of being true given that cloudy & wetGrass 
    are true,a probability of (11/51) of being true given that cloudy is false and wetGrass is true, a probability
    of (2/7) of being true given that cloudy is true and wetGrass is false, and a probability of (1/41) of being
    true given that cloudy & wetGrass are false.
 */
void rainMethod(){
    
    if(cloudy && wetGrass && rand()%27 < 22){
        rain  = true;
    }
    else if (!cloudy && wetGrass && rand()%51 < 11){
        rain  = true;
    }
    else if(cloudy && !wetGrass && rand()%7 < 2){
        rain = true;
    }
    else if(!cloudy && !wetGrass && rand()%41 < 1){
        rain = true;
    }
    else {
        rain = false;

    }
}

/*
    The wetGrassMethod sets the boolean variable 'wetGrass' to true or false based on the value of rain (T/F) and
    a precomputed probability of wetGrass being true based on the value of rain. Using the probided probability 
    table that was given in the assignment description, wetGrass has a probability of (99/100) of being true given
    that rain is true, and a probability of (90/100 or 9/10) of being true given that rain is false. Similar to the
    cloudyMethod computations, these probabilities assume that sprinkler is set to true based on the assignment
    problem description.
*/
void wetGrassMethod(){
    if(rain && rand()%100< 99){
        wetGrass = true;
    }
    else if (!rain && rand()%10<9){
        wetGrass  = true;
    }
    else{
        wetGrass = false;
    }
}

int main(int argc, const char * argv[]) {
    
    //Number of trials that we will run, I set this to be a high number to get a clearer picture
    //of the probability of (Rain|Sprinkler = True)
    int numTrials = 1000000000;

    //Gibbs Sampling requires that the values be randomly assigned prior to the trials
    //Since the boolean values are initially set to false, there is an equal chance (50%)
    //of these variables being either true or false.
    
    if((random()%2) == 1){
        cloudy = true;
    }
    if((random()%2) == 1){
        rain = true;
    }
    if((random()%2) == 1){
        wetGrass = true;
    }
    

    
    for(int x = 0 ; x < numTrials; x++){
        
        //Gibbs then randomly samples a value for one of the non-evidence variables,
        //which here is the values of cloudy, rain, and wetGrass, which is done
        //using their respective method.
        int r = rand()%3;
        
        if(r == 0){
            cloudyMethod();
        }
        if(r == 1){
            rainMethod();
        }
        if(r==2){
            wetGrassMethod();
        }
        
        //After randomly sampling a non-evidence variable, we check to see if rainy is
        //true or not. If it is, we increment the counter by one to ensure that we compute
        //the correct probability of (Rain | Sprinkler = True).
        if(rain == true){
            counter++;
        }
        
    }

    
    // Here, we print out the number of trials, and the number of times that rain ended up being true,
    // plus the overall probability of (Rain | Sprinkler = True).
    std::cout << "Number of Trials: " << numTrials<< std::endl;
    std::cout << "Rains: " << counter << std::endl;
    std::cout << "Probability of (Rain|Sprinkler = True): " << (float)counter/(float)numTrials << std::endl;

    
    return 0;
}


