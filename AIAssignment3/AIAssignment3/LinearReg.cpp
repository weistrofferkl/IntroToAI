//
//  LinearReg.cpp
//  AIAssignment3
//
//  Created by Kendall Weistroffer on 11/3/16.
//  Copyright © 2016 Kendall Weistroffer. All rights reserved.
//

/*
    Code for the Linear Regression algorithm, after running this algorithm multiple times, this can predict the 
    value of each image in the data set at about 82% accuracy.
 */
#include "LinearReg.hpp"
#include "ReadIn.hpp"
#include <vector>
#include <ioStream>

using namespace std;

class LinearReg{


public:

    float learnR;
    float bias = 0;
    int inputCount;
    uint8_t label;
    
    vector<float> weights = vector<float>(28*28); //each pixel must have its own weight
    vector<image> theImages;

    
    /*
     Constructor for the Linear Regression algorithm, takes in all of the images, the decided learning rate,
     and whatever integer (0-9) we happen to be looking at.
     */
    LinearReg(vector<image> allImages,float learningRate, uint8_t l){
        
        learnR = learningRate;
        theImages = allImages;
        label = l;
        weights.at(0) = 0; //set to be 0 to account for bias, may be unnecessary
        
        //Initilize the weights
        for(int i = 1; i< weights.size(); i++){
            weights.at(i) = (1/weights.size());
        }
        
        //train weights accordingly
        training(theImages);
        
    }
    
    /*
     Take the dot-product of the weights and the pixel value, essentially computing h(x)
     */
    float test(image selectedImage){
        float sum = 0;

            for(int i = 0; i < weights.size() ; i++){
                
               float x = selectedImage.pixel[i];
                sum += weights.at(i)*x;
            }

        return sum+bias; //add the bias to the end result and return
        
    }

    /*
        Update the weights accordingly, using the weight update rule as defined in the assignment
        description
     */
    void training(vector<image> data){
        for(int j = 0; j< data.size(); j++){
            
            float h = test(data.at(j));
            int hOfX = (h >= 0) ? 1 : 0; // threshold function
            
            for(int i = 0; i< weights.size(); i++){
                //applying the update rule to each weight using its current value, the learning rate, h(x) from the test function,
                //and the current pixel value
                weights.at(i) = weights.at(i) + learnR*(((data.at(j).value == label) ? 1:0) - hOfX) * data.at(j).pixel[i];
            
            }
            //update the bias as well according to a similar update rule, as defined in the textbook
            bias = bias + learnR*(((data.at(j).value == label )? 1:0) - hOfX);
        
        }
     
        }
    
};
