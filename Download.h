//
//  Download.h
//  Project_v1217
//
//  Created by Lu on 2021/12/18.
//

#ifndef Download_h
#define Download_h


#endif /* Download_h */

struct MemoryStruct {
    char* memory;
    size_t size;
};

void* myrealloc(void* ptr, size_t size) {
    if (ptr) return realloc(ptr, size);
    else return malloc(size);
}
int write_data2(void* ptr, size_t size, size_t nmemb, void* data) {
    size_t realsize = size * nmemb;
    struct MemoryStruct* mem = (struct MemoryStruct*)data;
    mem->memory = (char*)myrealloc(mem->memory, mem->size + realsize + 1);
    if (mem->memory) {
        memcpy(&(mem->memory[mem->size]), ptr, realsize);
        mem->size += realsize;
        mem->memory[mem->size] = 0;
    }
    return realsize;
}


void getAdjClose(map<string, string> symbol_date_map, map<string, map<string, double>>& date_price, map<string, double> &IWB_date_map)
{
    //cout << "Retrieving data..." << endl;
    // declaration of an object CURL
    CURL* handle;
    CURLcode result;

    // set up the program environment that libcurl needs
    curl_global_init(CURL_GLOBAL_ALL);

    // curl_easy_init() returns a CURL easy handle
    handle = curl_easy_init();

    // if everything's all right with the easy handle...
    if (handle) {
        string url_common = "https://eodhistoricaldata.com/api/eod/";
        // You must replace this API toekn with yours
        string api_token = "61ad428d1d8d76.46544183";

        /*
        Retrieve IWB as benchmark ONLY ONCE. Date-Price pairs.
        */
        
        symbol_date_map["IWB"] = "2021-01-04";
        struct MemoryStruct IWBdata;
        IWBdata.memory = NULL;
        IWBdata.size = 0;

        string url_request = url_common + "IWB" + ".US?" + "from="
            + "2020-05-01" + "&to=" + "2021-11-30" + "&api_token="
            + api_token + "&period=d";
        curl_easy_setopt(handle, CURLOPT_URL, url_request.c_str());

        //adding a user agent
        curl_easy_setopt(handle, CURLOPT_USERAGENT, "Mozilla/5.0 (Windows NT 10.0; Win64; x64; rv:74.0) Gecko / 20100101 Firefox / 74.0");
        curl_easy_setopt(handle, CURLOPT_SSL_VERIFYPEER, 0);
        curl_easy_setopt(handle, CURLOPT_SSL_VERIFYHOST, 0);


        curl_easy_setopt(handle, CURLOPT_WRITEFUNCTION, write_data2);
        curl_easy_setopt(handle, CURLOPT_WRITEDATA, (void*)&IWBdata);

        // perform, then store the expected code in result
        result = curl_easy_perform(handle);

        if (result != CURLE_OK) {
            // if errors have occured, tell us what is wrong with result
            fprintf(stderr, "curl_easy_perform() failed: %s\n",
                curl_easy_strerror(result));
            return;
        }

        stringstream sIWBData;
        sIWBData.str(IWBdata.memory);
        string sIWBValue, sIWBDate;
        double dIWBValue = 0;
        string IWBline;

        while (getline(sIWBData, IWBline)) {
            size_t found = IWBline.find('-');
            if (found != std::string::npos) {
                //cout << line << endl;
                sIWBDate = IWBline.substr(0, IWBline.find_first_of(','));
                IWBline.erase(IWBline.find_last_of(','));
                sIWBValue = IWBline.substr(IWBline.find_last_of(',') + 1);
                dIWBValue = strtod(sIWBValue.c_str(), NULL);
                IWB_date_map[sIWBDate] = dIWBValue;
                //cout << sDate << " " << std::fixed << setprecision(2) << dValue << endl;
            }
        }

        free(IWBdata.memory);
        IWBdata.size = 0;

        //cout << "IWB data retrieved!!!" << endl;


        /*
        Then retrieve data for tickers
        */
        
        map<string, string>::iterator itr = symbol_date_map.begin();
        for (; itr != symbol_date_map.end(); itr++)
        {
            string symbol = itr->first;
            string date = itr->second;

            cout << symbol << " ";

            string start_date = "2020-05-01";
            string end_date = "2021-11-30";

            struct MemoryStruct data;
            data.memory = NULL;
            data.size = 0;

            string url_request = url_common + symbol + ".US?" + "from="
                + start_date + "&to=" + end_date + "&api_token="
                + api_token + "&period=d";
            curl_easy_setopt(handle, CURLOPT_URL, url_request.c_str());

            //adding a user agent
            curl_easy_setopt(handle, CURLOPT_USERAGENT, "Mozilla/5.0 (Windows NT 10.0; Win64; x64; rv:74.0) Gecko / 20100101 Firefox / 74.0");
            curl_easy_setopt(handle, CURLOPT_SSL_VERIFYPEER, 0);
            curl_easy_setopt(handle, CURLOPT_SSL_VERIFYHOST, 0);


            curl_easy_setopt(handle, CURLOPT_WRITEFUNCTION, write_data2);
            curl_easy_setopt(handle, CURLOPT_WRITEDATA, (void*)&data);

            // perform, then store the expected code in result
            result = curl_easy_perform(handle);

            if (result != CURLE_OK) {
                // if errors have occured, tell us what is wrong with result
                fprintf(stderr, "curl_easy_perform() failed: %s\n",
                    curl_easy_strerror(result));
                return;
            }

            stringstream sData;
            sData.str(data.memory);
            string sValue, sDate;
            double dValue = 0;
            string line;
            //cout << symbol << endl;

            //map<string, double> date_price;
            while (getline(sData, line)) {
                size_t found = line.find('-');
                if (found != std::string::npos) {
                    //cout << line << endl;
                    sDate = line.substr(0, line.find_first_of(','));
                    line.erase(line.find_last_of(','));
                    sValue = line.substr(line.find_last_of(',') + 1);
                    dValue = strtod(sValue.c_str(), NULL);
                    date_price[symbol][sDate]= dValue;
                    //cout << sDate << " " << std::fixed << setprecision(2) << dValue << endl;
                }
            }
            
            //cout << "size: " + adjClose.size() << endl;
            free(data.memory);
            data.size = 0;
        }
    }
    else {
        fprintf(stderr, "Curl init failed!\n");
        return;
    }

    // cleanup since you've used curl_easy_init
    curl_easy_cleanup(handle);

    // release resources acquired by curl_global_init()
    curl_global_cleanup();
}

void get2N_days(map<string, string> symbol_date_map, int N, map<string, Vector>& price_map, map<string, Vector>& benchmark_map, map<string, map<string, double>>& date_price, map<string, double> &IWB_date_map)
{
    
    map<string, string>::iterator symbol_itr = symbol_date_map.begin();
    for (; symbol_itr != symbol_date_map.end(); symbol_itr++)
    {
        string symbol = symbol_itr->first;
        string date = symbol_itr->second;

        map<string, double>::iterator itr = date_price[symbol].find(date);
        // if the date zero is not found, return empty
        if (itr == date_price[symbol].end()) {
            cout << symbol + " day zero is not found!" << endl;
            continue;
        }
        
        for (int i = 0; i < N; i++) {
            //if the symbol doesn't have +N days, return end
            if (itr == date_price[symbol].end()) {
                break;
            }
            itr++;
        }

        map<string, double>::iterator end_itr = itr;
        if (itr != date_price[symbol].end()) {
            end_itr++;
        }

        //reset itr
        itr = date_price[symbol].find(date);
        for (int i = 0; i < N; i++) {
            //if the symbol doesn't have -N days, return begin
            if (itr == date_price[symbol].begin()) {
                break;
            }
            itr--;
        }

        Vector adjClose;
        Vector benchmark;
        while (itr != end_itr) {
            adjClose.push_back(itr->second);
            benchmark.push_back(IWB_date_map[itr->first]);
            itr++;
        }

        price_map[symbol] = adjClose;
        benchmark_map[symbol] = benchmark;

    }
}


