//
//  LogReg.cpp
//  AIAssignment3
//
//  Created by Kendall Weistroffer on 11/10/16.
//  Copyright © 2016 Kendall Weistroffer. All rights reserved.
//

/*
 Code for the Logistical Regression algorithm, after running this algorithm multiple times, this can predict the
 value of each image in the data set at about 91% accuracy.
 */

#include "LogReg.hpp"
#include "ReadIn.hpp"
#include <vector>
#include <ioStream>
#include <cmath>

using namespace std;

class LogReg{
    
    
public:
    
    float learnR;
    float bias = 0;
    int inputCount;
    vector<float> weights = vector<float>(28*28); //each pixel must have its own weight
    vector<image> theImages;
    uint8_t label;
    
    /*
     Constructor for the Linear Regression algorithm, takes in all of the images, the decided learning rate,
     and whatever integer (0-9) we happen to be looking at.
     */
    LogReg(vector<image> allImages,float learningRate, uint8_t l){
        
        learnR = learningRate;
        theImages = allImages;
        label = l;
        
        weights.at(0) = 0; //once again, not sure if this was necessary or not
        
        //Initilize the weights
        for(int i = 1; i< weights.size(); i++){
            weights.at(i) = (1/weights.size());
        }
        //train weights accordingly
        training(theImages);
        
    }
    
    /*
      Take the dot-product of the weights and the pixel value, will be used in the logistical hypothesis function: 1 / (1 + e^(-w*x))
     */
    float test(image selectedImage){

        float dotPro = 0;
        
        for(int i = 0 ; i< weights.size(); i++){
            float x = selectedImage.pixel[i];
            dotPro += (x*weights.at(i));
            
        }
        return dotPro;
    }

    /*
     Update the weights accordingly, since we are only doing a single layer, we can use the same weight update
     function as defined in the assignment description (as discussed in Thayne's office hours on 11/11/2016)
     
     */
    void training(vector<image> data){
        //train on the training data 20 times
        for (int k = 0; k < 20; k++) {
            for(int j = 0; j< data.size(); j++){
                
                float h = test(data.at(j)); //compute the dotProduct
                float hOfX = (1 / (1 + exp(-h))); //compute the rest of the hypothesis function: 1 / (1 + e^(-w*x))
                
                for(int i = 0; i< weights.size(); i++){
                    //applying the update rule to each weight using its current value, the learning rate, h(x) from the test function,
                    //and the current pixel value
                    weights.at(i) = weights.at(i) + learnR*(((data.at(j).value == label) ? 1:0) - hOfX) * data.at(j).pixel[i];
                }
                //update the bias as well according to a similar update rule, as defined in the textbook
                bias = bias + learnR*(((data.at(j).value == label )? 1:0) - hOfX);
            }
            
        }
    }
    
    
    
    
    
};

