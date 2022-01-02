//
//  Bootstrap.cpp
//  Project_v1217
//
//  Created by Lu on 2021/12/18.
//

#include "Bootstrap.hpp"
#include<iostream>
#include <stdlib.h>
#include <time.h>
using namespace std;


vector<string> BootStrap::resample(vector<string> vec) {
    //vector<int>index;
    int len = vec.size();
    int index = 0;


    //make sure every time we draw different samples


    vector<string>myvec;
    int count = 0;

    while (count < n_samples) {

        count += 1;
        index = rand() % len;

        myvec.push_back(vec[index]);
        //cout << vec[index] << endl;

    }
    //cout << endl;
    return myvec;
}
