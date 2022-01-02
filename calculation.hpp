//
//  calculation.hpp
//  Project_v1217
//
//  Created by Lu on 2021/12/18.
//

#ifndef calculation_hpp
#define calculation_hpp

#include <stdio.h>

#endif /* calculation_hpp */

#pragma once
#include <stdio.h>
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <locale>
#include <iomanip>
#include <fstream>
#include <map>
#include <algorithm>
#include"Vector.hpp"
using namespace std;
class calculation {
private:
    int num_samples;
    int num_dates;
    int resample_times;
    map<string, Vector>ARtable;

    //vector<Vector>result;

public:
    calculation():num_samples(80){};
    ~calculation(){}
    


    //According to bootstrap samples, find  corresponding AR in ARtable
    vector<Vector> getAR(int n, vector<vector<string>>vec, int num_samples, map<string, Vector> ARtable);

    //compute AAR for all days
    Vector getAAR(vector<Vector>vec, int num_dates, int num_samples);

    Vector getCAAR(Vector aar, int num_dates);

    Vector cal_avg(vector<Vector>pop, int num_dates, int resample_times);

    Vector cal_std(vector<Vector>pop, Vector avg, int num_dates, int resample_times);
    vector<Vector> calculate_all(vector<vector<string>>vec, int num_samples, int num_dates, int resample_times, map<string, Vector>ARtable);
};








