//
//  main.cpp
//  Final project v1216
//
//  Created by Lu on 2021/12/16.
//

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <locale>
#include <iomanip>
#include <fstream>
#include <map>
#include <algorithm>
#include "curl/curl.h"
#include "Bootstrap.hpp"
#include"calculation.hpp"
#include "Vector.hpp"
#include "Data.hpp"
#include "Download.h"


using namespace std;


void pop_bs_vec(BootStrap bs, vector<vector<string>>& popvec, vector<string>original_vec, int times) {
    for (int i = 0; i < times; i++) {
        vector<string> sample = bs.resample(original_vec);
        popvec.push_back(sample);
    }
}

void plot_caar(vector<vector<Vector>> calculation_results) {
    int dataSize = calculation_results[0][1].size();
    int N = (dataSize >> 1) + 1;
    FILE* gnuplotPipe, * tempDataFile;
    const char* tempDataFileName1 = "Beat";
    const char* tempDataFileName2 = "Meet";
    const char* tempDataFileName3 = "Miss";
    double x, y, x2, y2, x3, y3;
    int i;

    gnuplotPipe = _popen("C:\\PROGRA~1\\gnuplot\\bin\\gnuplot.exe","w");
    if (gnuplotPipe) {
        fprintf(gnuplotPipe, "plot \"%s\" with lines, \"%s\" with lines, \"%s\" with lines\n", tempDataFileName1, tempDataFileName2, tempDataFileName3);
        fflush(gnuplotPipe);
        tempDataFile = fopen(tempDataFileName1, "w");
        for (i = 0; i < dataSize; i++) {
            x = i - N;
            y = calculation_results[0][1][i];
            fprintf(tempDataFile, "%lf %lf\n", x, y);
        }
        fclose(tempDataFile);

        tempDataFile = fopen(tempDataFileName2, "w");
        for (i = 0; i < dataSize; i++) {
            x2 = i - N;
            y2 = calculation_results[1][1][i];
            fprintf(tempDataFile, "%lf %lf\n", x2, y2);
        }
        fclose(tempDataFile);

        tempDataFile = fopen(tempDataFileName3, "w");
        for (i = 0; i < dataSize; i++) {
            x3 = i - N;
            y3 = calculation_results[2][1][i];
            fprintf(tempDataFile, "%lf %lf\n", x3, y3);
        }
        fclose(tempDataFile);

        fprintf(gnuplotPipe, "set term wxt\n");
        fprintf(gnuplotPipe, "set grid\n");
        fprintf(gnuplotPipe, "set xlabel 'N - Number of days'\n");
        fprintf(gnuplotPipe, "set ylabel 'CAAR'\n");
        fprintf(gnuplotPipe, "set title 'CAAR of all groups'\n");
        fprintf(gnuplotPipe, "set key left top\n");
        fprintf(gnuplotPipe, "set key width '10'\n");
        

        printf("press enter to continue...");
        system("pause");
        remove(tempDataFileName1);
        remove(tempDataFileName2);
        remove(tempDataFileName3);
        fprintf(gnuplotPipe, "exit \n");
    }
    else {
        printf("gnuplot not found...");
    }

}
void showmenu()
{
    cout << "----------Menu--------------" << endl;
    cout << "1. Enter N." << endl
        << "2. Pull information for one stock." << endl
        << "3. Show AAR, AAR-SD, CAAR and CAAR-STD for one group." << endl
        << "4. Show the gnuplot graph with CAAR for all 3 groups." << endl
        << "5. Exit menu." << endl << endl;
    cout << endl;

}

int main()
{
    srand(time(NULL));
    int N = 0;
    Data data;
    vector<string> symbolList;
    data.populateSymbolVector(symbolList);

    //read earnings csv
    vector<string> ticker;
    vector<string> announce_date;
    vector<string> prd_end;
    vector<string> estimate;
    vector<string> report_earn;
    vector<string> surprise;
    vector<string> surprise_pct;
    vector<string> MissEst_group;
    vector<string> MeetEst_group;
    vector<string> BeatEst_group;
    
   
    data.populateEarningVector(ticker, announce_date, prd_end, estimate, report_earn, surprise, surprise_pct);

    map<string, string> ticker_date_map; // a map that contains tickers and corresponding day zeros
    for (int i = 0; i < (int)ticker.size(); i++) {
        //use intersection of symbolList and ticker
        if (find(symbolList.begin(), symbolList.end(), ticker[i]) != symbolList.end() && ticker[i] != "") {
            ticker_date_map[ticker[i]] = announce_date[i];
        }
    }


    //price_map: ticker and vector of price pair
    //benchmark_map: ticker and vector of benchmark price pair
    map<string, Vector> price_map, benchmark_map;
    map<string, double> IWB_date_map;
    map<string, map<string, double>> date_price;
    getAdjClose(ticker_date_map, date_price, IWB_date_map);
    
    vector<string> curSymbols;
    map<string, Vector>::iterator itr;
    

    vector<string> valid_symbol;
    map<string, Vector> ARtable;
    string curSymbol;
    Vector stockReturn;
    Vector benchmarkReturn;
    vector<string> sort_vec;
    

    //Bootstrap
    BootStrap bootstrap;


    vector<vector<string>>BeatEstvec;
    vector<vector<string>>MeetEstEstvec;
    vector<vector<string>>MissEstEstvec;

    int resample_time = 40;
    //int num_samples = 80;

    vector<Vector> BE_cal;
    vector<Vector> Me_cal;
    vector<Vector> Mi_cal;

    //calculate average average AAR,CAAR,AAR_STD,CAAR_STD
    calculation cal_be;
    vector<vector<Vector>> calcualtion_results;
    
    //menu
    //display items
    
    //get operator
    int oper=0;
    string stock_ticker;
    string group;
    int ticker_index=0;
    Vector daily_return;
    Vector cum_daily_return;
    int group_selection;
    int group_name;

    vector<string>::iterator itr1;
    
    while (oper != 5) {
        if (N == 0) {
            oper = 1;
        }
        else {
            showmenu();
            cout << "Please select an option." << endl;
            cin >> oper;
        }
        switch (oper)
        {
        default:
            cout << "Please enter a valid choice." << endl;
            break;
        case 1:
            cout << endl << "Please enter N (N>=60):" << endl;
            //int N;
            cin >> N;
            if (N < 60) {
                cout << "Invalid N,automatically set to N=60." << endl;
                N = 60;
            }
            curSymbols.clear();
            valid_symbol.clear();
            ARtable.clear();
            stockReturn.clear();
            benchmarkReturn.clear();
            BeatEstvec.clear();
            MeetEstEstvec.clear();
            MissEstEstvec.clear();
            BE_cal.clear();
            Me_cal.clear();
            Mi_cal.clear();
            calcualtion_results.clear();
            MissEst_group.clear();
            MeetEst_group.clear();
            BeatEst_group.clear();
            sort_vec.clear();
            get2N_days(ticker_date_map, N, price_map, benchmark_map, date_price, IWB_date_map);
            itr = price_map.begin();
            while (itr != price_map.end()) {
                curSymbols.push_back(itr->first);
                itr++;
            }
            //Check and erase stocks with less than 2N+1 days of data
            //If valid, put symbol into valid_symbol and caluclate returns & AR
            for (int i = 0; i < (int)curSymbols.size(); i++) {
                curSymbol = curSymbols[i];
                if ((int)price_map[curSymbol].size() < 2 * N + 1) {
                    cout << curSymbol + " days less than 2N + 1! Actual: " + to_string(price_map[curSymbol].size()) << endl;
                    price_map.erase(curSymbol);
                    benchmark_map.erase(curSymbol);
                }
                else {
                    valid_symbol.push_back(curSymbol);
                    stockReturn = calculateReturn(price_map[curSymbol]);
                    benchmarkReturn = calculateReturn(benchmark_map[curSymbol]);
                    ARtable[curSymbol] = stockReturn - benchmarkReturn;
                }
            }

            /*vector<string> sort_vec;*/
            for (int i = 0; i < (int)ticker.size(); i++) {
                for (int j = 0; j < (int)valid_symbol.size(); j++) {
                    if (ticker[i] == valid_symbol[j]) {
                        sort_vec.push_back(ticker[i]);
                    }
                }
            }

            //Split Valid Symbols into three groups
            data.Split(sort_vec, MissEst_group, MeetEst_group, BeatEst_group);
            //cout << to_string(MissEst_group.size()) << endl;
            //cout << to_string(MeetEst_group.size()) << endl;
            //cout << to_string(BeatEst_group.size()) << endl;
            
            //resample data of three groups
            pop_bs_vec(bootstrap, BeatEstvec, BeatEst_group, resample_time);
            pop_bs_vec(bootstrap, MeetEstEstvec, MeetEst_group, resample_time);
            pop_bs_vec(bootstrap, MissEstEstvec, MissEst_group, resample_time);
            
            BE_cal = cal_be.calculate_all(BeatEstvec, 80, 2 * N, resample_time, ARtable);
            
            Me_cal = cal_be.calculate_all(MeetEstEstvec, 80, 2 * N, resample_time, ARtable);

            Mi_cal = cal_be.calculate_all(MissEstEstvec, 80, 2 * N, resample_time, ARtable);
            //cout << Mi_cal.size() << endl;
            
            calcualtion_results.push_back(BE_cal);
            calcualtion_results.push_back(Me_cal);
            calcualtion_results.push_back(Mi_cal);
            /*calcualtion_results[0] = BE_cal;
            calcualtion_results[1] = Me_cal;
            calcualtion_results[2] = Mi_cal;*/

            break;
        
        
        case 2:
            cout << "Please enter stock ticker:" << endl;
            cin >> stock_ticker;
            
            
            itr1 = find(ticker.begin(), ticker.end(), stock_ticker);
            if (itr1 != ticker.cend())
            {
                ticker_index=(int)distance(ticker.begin(), itr1);

                if (find(MissEst_group.begin(), MissEst_group.end(), stock_ticker) != MissEst_group.end() && stock_ticker != "") { group = "MISS ESTIMATE"; }
                else if (find(MeetEst_group.begin(), MeetEst_group.end(), stock_ticker) != MeetEst_group.end() && stock_ticker != "") { group = "MEET ESTIMATE"; }
                else if (find(BeatEst_group.begin(), BeatEst_group.end(), stock_ticker) != BeatEst_group.end() && stock_ticker != "") { group = "BEAT ESTIMATE"; }
                //else 

                daily_return = calculateReturn(price_map[stock_ticker]);
                cum_daily_return = calculateCumReturn(daily_return);
                cout << "Ticker: " << stock_ticker << endl
                    << "Group: " << group << endl
                    << "Announce Date: " << announce_date[ticker_index] << endl
                    << "Period End: " << prd_end[ticker_index] << endl
                    << "EPS Esitmate: " << estimate[ticker_index] << endl
                    << "EPS Actual: " << report_earn[ticker_index] << endl
                    << "EPS Surprise: " << surprise[ticker_index] << endl
                    << "EPS Surprise Percent: " << surprise_pct[ticker_index] << endl
                    << endl;
                cout << "Daily Prices: " << price_map[stock_ticker] << endl
                    << "Cumulative Daily Returns: " << cum_daily_return << endl << endl;
            }
            else
            {
                cout << "Please enter a valid ticker. " << endl;
            }
                
            break;
            
       
        case 3:
            cout << "Please enter the group selection: " << endl
                << "1. Beat Estimate Group" << endl
                << "2. Meet Estimate Group" << endl
                << "3. Miss Estimate Group" << endl
                << "4. Go back to the previous menu" << endl;
            
            cin >> group_selection;
            
            if (group_selection == 1) group_name = 0;
            else if (group_selection == 2) group_name = 1;
            else if (group_selection == 3) group_name = 2;
            else if (group_selection == 4) break;
            else{
                cout << "Please enter a valid choice." << endl;
                break;
            }
            
            cout << "AAR: " << calcualtion_results[group_name][0] << endl
                << "CAAR: " << calcualtion_results[group_name][1] << endl
                << "AAR_STD: " << calcualtion_results[group_name][2] << endl
                << "CAAR_STD: " << calcualtion_results[group_name][3] << endl << endl;

            break;
        
        case 4:
            
            cout << "Plotting CAAR with Gnuplot..." << endl;
            plot_caar(calcualtion_results);
            break;
            

        case 5:
            
            break;
            

       
        }
        


    }
    return 0;
}

