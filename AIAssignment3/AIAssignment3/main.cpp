//
//  main.cpp
//  AIAssignment3
//
//  Created by Kendall Weistroffer on 11/2/16.
//  Copyright © 2016 Kendall Weistroffer. All rights reserved.
//

 /*
  This assignment performs linear and logistical regression on the data from the MNIST data set, taking in 784 inputs and
  determining the value of each data image in the data set. 
  
  LinearReg.cpp : Code for the Linear Regression algorithm
  LogReg.cpp    : Code for the Logistical Regression algorithm
  ReadIn.cpp    : Code used to read in the MNIST data set, given by Nathan
  ReadIn.hpp    : Header file for reading in the data, given by Nathan
 */

#include <iostream>
#include "ReadIn.hpp"
#include "ReadIn.cpp"
#include "LinearReg.cpp"
#include "LogReg.cpp"
#include <vector>
#include <string>


int main(int argc, const char * argv[]) {
    
    /*
     Basically setting up and reading in our data:
     */
    ReadIn reader;
    std::vector<image> data = std::vector<image>();
    std::vector<image> testData = std::vector<image>();
    std::vector<LinearReg> possLabels = std::vector<LinearReg>();
    std::vector<LogReg> possLabelsLog = std::vector<LogReg>();

    
    char *imageTrain = "train-images-idx3-ubyte";
    char *labelsTrain = "train-labels-idx1-ubyte";
    
    char *imageTest = "t10k-images-idx3-ubyte";
    char *labelsTest = "t10k-labels-idx1-ubyte";

    float LR = .1; //learning rate
 
    reader.LoadData(data, imageTrain, labelsTrain );
    reader.LoadData(testData,imageTest,labelsTest);
    
/*  
  This commented out code was used to visualize the input data, as it would print out the numbers/drawings
  that we are using to train/test the regressions.
 
 
    int counter = 0;
    for(int k = 0 ; k < 1; k++){
        cout<< "EXPECTED VALUE LABEL: " << (int)data.at(k).value << endl;
        for(int i = 0; i < 28; i++){
            for(int j = 0; j< 28; j++){
                counter ++;
                float pixel = (float) data.at(k).get(j,i);
            
                if(pixel > (85*2)){
                    cout << " ";
                }
                else if(pixel > 85){
                    cout << "*";
                }
                else{
                    cout << "#";
                }
        
                if(counter == 28){
                    cout << endl;
                    counter = 0;
                }
          
            }
    
        }
        cout<< endl << endl << endl;
    }
   */
    
    //LINEAR REGRESSION PART OF ASSIGNMENT:
    
    
    //Train the linear regression for each integer 0-9
    for(int i = 0; i < 10; i++){
        possLabels.push_back(LinearReg(data, LR, i));
    
    }
    
    int correctCounter = 0; //Used to keep account of how many times the drawings are correctly identified
    
    //run the linear regression using the test data
    for(int j = 0; j < testData.size(); j++){
        
        
        //used to get the determined value of each integer, where integers that have a higher number are more likely
        //to be the correct number as determined by linear regression algo.
        float deterVal = possLabels.at(0).test(testData.at(j));
        int lab = 0; //used to hold the highest ranked number (0-9)
        
        //loop through the possible integers
        for(int k = 1; k< 10; k++){
            
           //ensures that we are setting lab to be the integer with the highest rank value
            if(deterVal < possLabels.at(k).test(testData.at(j))){
                deterVal = possLabels.at(k).test(testData.at(j));
                lab = k;
            }
    
        }
        //if we have correctly determined the value of the image, increment the correctCounter
        if(lab == testData.at(j).value){
            correctCounter++;
        }
    
    }
    
    std::cout<< std::endl<< "Correct: " << correctCounter << std::endl;
    std::cout<< "Size: " << testData.size() <<std::endl;
    std::cout << "Percentage Linear Regression: " << (float)correctCounter/testData.size() *100<<"%"<< std::endl<< std:: endl;
    
    //LOGISTICAL REGRESSION EXTRA CREDIT:
    
    
    LR = .00000001; //set very low to make sure that we get as close as possible to the global minima
    
    //similar to in linear regression train on each integer 0-9
    for(int i = 0; i < 10; i++){
        possLabelsLog.push_back(LogReg(data, LR, i));
        
    }
    
    int correctCounter2 = 0; //used to keep track of how many times we are correct in determining the value of a picture
    
    //Run the logistical regression algo. on the test data
    for(int j = 0; j < testData.size(); j++){
        
        //used to get the determined value of each integer, where integers that have a higher number are more likely
        //to be the correct number as determined by logistical regression algo.
        float deterVal = possLabelsLog.at(0).test(testData.at(j));
        int lab = 0; //used to hold the highest ranked number (0-9)
        
        
        //loop through the possible integers
        for(int k = 1; k< 10; k++){

            //ensures that we are setting lab to be the integer with the highest rank value
            if(deterVal < possLabelsLog.at(k).test(testData.at(j))){
                
                deterVal = possLabelsLog.at(k).test(testData.at(j));
                lab = k;
            }
            
        }
        //if we have correctly determined the value of the image, increment the correctCounter2
        if(lab == testData.at(j).value){
            correctCounter2++;
        }
        
    }
    
    std::cout<< "Correct: " << correctCounter2 << std::endl;
    std::cout<< "Size: " << testData.size() <<std::endl;
    std::cout << "Percentage Log Regression: " << (float)correctCounter2/testData.size()*100<<"%" << std::endl;

 
    return 0;
}
