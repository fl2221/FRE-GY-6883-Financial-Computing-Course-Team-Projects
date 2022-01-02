# FRE-GY-6883-Financial-Computing-Course-Team-Projects
Evaluate the impact of quarterly earnings report on stock price movement

Programming Requirements: 

  • Use liburl to retrieve historical price data from eodhistoricaldata.com: A function retrieves the adjusted close prices for selected Russell 1000 stocks and IWB (Russell 1000 ETF used as market benchmark) into memory.
  
  • Create a set of classes such as class for stock to handle EPS (earnings per share) estimate and price information.
  
  • Use member functions or independent functions for all calculation. Overload a few arithmetic operators for vector/matrix.
  
  • The stocks and their corresponding price information for each group should be stored in a STL map, with stock symbol as its keys.
  
  • The expected AAR, AAR STD, and expected CAAR and CAAR STD for 3 groups are presented in a matrix. The row of the matrix is the group#, matrix columns are for AAR, AAR-STD, CAAR, CAAR-STD
  
  • Use gnuplot to show the CAAR from all 3 groups in one graph.
  
  
Program functions:

  • Retrieve historical price data for all selected stocks. Parse the retrieved data for dates and adjusted closing prices.
    
  • Calculate AAR, AAR-STD, CAAR, CAAR-STD for each group
    
  • Populate the stock maps and AAR/CAAR matrix.
    
  • Show the gnuplot graph with CAAR for all 3 groups.
  
    
Program menu of 5 options:

  • Enter N to retrieve 2N+1 days of historical price data for all stocks (you need to validate user input to make sure N >= 60).
    
  • Pull information for one stock from one group:
      ▪ Daily Prices
      ▪ Cumulative Daily Returns
      ▪ The group the stock belongs to
      ▪ Earning Announcement Date, Period Ending, Estimated, Reported Earnings, Surprise and Surprise %.
  • Show AAR, AAR-STD, CAAR and CAAR-STD for one group.
  • Show the gnuplot graph with CAAR for all 3 groups. 
  • Exit your program.

![image](https://user-images.githubusercontent.com/90628693/147866095-9c0773f4-3b73-4dc6-a2fc-bedebbb96965.png)

