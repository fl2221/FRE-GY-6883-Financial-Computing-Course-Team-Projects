//
//  Data.hpp
//  Project_v1217
//
//  Created by Lu on 2021/12/18.
//

#ifndef Data_hpp
#define Data_hpp

#include <stdio.h>

#endif /* Data_hpp */
#pragma once
#include<iostream>
#include<cmath>
#include<vector>
#include <sstream>
#include <locale>
#include <iomanip>
#include <fstream>
#include "curl/curl.h"
#include <map>
#include"calculation.hpp"

using namespace std;


class Data
{
private:
    const char* cIWB1000SymbolFile = "Russell_1000_component_stocks.csv";
    const char* cEarningAnnounceFile = "EarningsAnnouncements.csv";
public:
    void populateEarningVector(vector<string>& symbols, vector<string>& anndate, vector<string>& prdend, vector<string>& est, vector<string>& rpt, vector<string>& sur_prise, vector<string>& sur_pct);
    void Split(vector<string>& title, vector<string>& miss, vector<string>& meet, vector<string>& beat);
    void populateSymbolVector(vector<string>& symbols);
};

/*
class getAdj: public Download
{
public:
    
};
}
*/
