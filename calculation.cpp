//
//  calculation.cpp
//  Project_v1217
//
//  Created by Lu on 2021/12/18.
//

#include "calculation.hpp"
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
#include <cmath>
using namespace std;

vector<Vector> calculation::getAR(int n, vector<vector<string>>vec, int num_samples, map<string, Vector> ARtable)
{
    map<string, Vector>::iterator mitr;

    vector<vector<double>>new_vec;
    for (int i = 0; i < num_samples; i++) {

        mitr = ARtable.find(vec[n][i]);
        if (mitr != ARtable.end()) {
            new_vec.push_back(mitr->second);
        }
        else {
            cout << "not found: ";
            cout << vec[n][i] << endl;
        }

    }
 
    return new_vec;
}

vector<double> calculation::getAAR(vector<vector<double>>ar, int num_dates, int num_samples) {

    vector<double>AAR;
    for (int i = 0; i < num_dates; i++) {
        double sum = 0;
        for (int n = 0; n < num_samples; n++) {
            sum += ar[n][i];
        }
        double avg = sum / num_samples;
        AAR.push_back(avg);
    }
    return AAR;
}

Vector calculation::getCAAR(Vector aar, int num_dates)
{
    Vector CAAR;
    double caar = 0.0;
    for (int i = 0; i < num_dates; i++) {
        caar += aar[i];
        CAAR.push_back(caar);
    }
    return CAAR;
}
Vector calculation::cal_avg(vector<Vector> pop, int num_dates, int resample_times) {
    Vector AVG;
    double res = 0.0;
    for (int i = 0; i < num_dates; i++) {
        for (int j = 0; j < resample_times; j++) {
            res += pop[j][i];
        }
        res = res / resample_times;
        AVG.push_back(res);
    }
    return AVG;
}

Vector calculation::cal_std(vector<Vector> pop, Vector avg, int num_dates, int resample_times) {
    Vector STD;
    double res = 0.0;
    double mean = 0.0;
    for (int i = 0; i < num_dates; i++) {
        mean = avg[i];
        for (int j = 0; j < resample_times; j++) {
            res += pow((pop[j][i] - mean), 2);
        }
        res = sqrt(res / resample_times);
        STD.push_back(res);
    }
    return STD;

}

vector<Vector> calculation::calculate_all(vector<vector<string>>vec, int num_samples, int num_dates, int resample_times, map<string, Vector>ARtable) {
    vector<Vector> result;
    vector<Vector> AAR_pop;
    vector<Vector>CAAR_pop;
    Vector AVG_AAR;
    Vector AVG_CAAR;
    Vector STD_AAR;
    Vector STD_CAAR;

    for (int n = 0; n < resample_times; n++) {
        vector<Vector> AR = getAR(n,vec, num_samples, ARtable);
        Vector AAR = getAAR(AR, num_dates, num_samples);
        Vector CAAR = getCAAR(AAR, num_dates);
        
        AAR_pop.push_back(AAR);
        CAAR_pop.push_back(CAAR);
    }
    AVG_AAR = cal_avg(AAR_pop, num_dates, resample_times);
    AVG_CAAR = cal_avg(CAAR_pop, num_dates, resample_times);
    STD_AAR = cal_std(AAR_pop, AVG_AAR, num_dates, resample_times);
    STD_CAAR = cal_std(CAAR_pop, AVG_CAAR, num_dates, resample_times);
    
    result.push_back(AVG_AAR);
    result.push_back(AVG_CAAR);
    result.push_back(STD_AAR);
    result.push_back(STD_CAAR);
    //cout << result.size()<<endl;
    //cout << result[0].size() << endl;

    return result;
}
