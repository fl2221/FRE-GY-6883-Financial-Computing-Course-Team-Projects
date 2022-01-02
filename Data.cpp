//
//  Data.cpp
//  Project_v1217
//
//  Created by Lu on 2021/12/18.
//

#include "Data.hpp"
#include<iostream>
#include "curl/curl.h"
#include <map>
#include"calculation.hpp"

using namespace std;

void Data::populateEarningVector(vector<string>& symbols, vector<string>& anndate, vector<string>& prdend, vector<string>& est, vector<string>& rpt, vector<string>& sur_prise, vector<string>& sur_pct)
{
    ifstream fin;
    fin.open(cEarningAnnounceFile, ios::in);
    string line, symbol, date, end, estimate, report, surprise, pct;
    while (!fin.eof())
    {
        //fin >> line;
        getline(fin, line);
        stringstream sin(line);
        getline(sin, symbol, ',');
        getline(sin, date, ',');
        getline(sin, end, ',');
        getline(sin, estimate, ',');
        getline(sin, report, ',');
        getline(sin, surprise, ',');
        getline(sin, pct);
        symbols.push_back(symbol);
        anndate.push_back(date);
        prdend.push_back(end);
        est.push_back(estimate);
        rpt.push_back(report);
        sur_prise.push_back(surprise);
        sur_pct.push_back(pct);
    }
}

void Data::Split(vector<string>& title, vector<string>& miss, vector<string>& meet, vector<string>& beat)
{
    cout << "Total number of tickers for bootstrapping: " + to_string(title.size()) << endl;
    
    int msize = title.size() / 3;
    copy(title.begin(), title.begin() + msize, back_inserter(miss));
    copy(title.begin() + msize, title.begin() + 2*msize, back_inserter(meet));
    copy(title.begin() + 2*msize, title.begin() +title.size(), back_inserter(beat));
}

void Data::populateSymbolVector(vector<string>& symbols)
{
    ifstream fin;
    fin.open(cIWB1000SymbolFile, ios::in);
    string line, name, symbol;
    while (!fin.eof()) {
        getline(fin, line);
        stringstream sin(line);
        getline(sin, symbol, ',');
        getline(sin, name);
        symbols.push_back(symbol);
    }
}
