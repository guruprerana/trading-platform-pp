# Event-Driven Backtest Environment for Algorithms in C++

Large project that will most likely take the entire summer, if not longer. Along the way I plan to pick up C++ as it is the fastest language for event-driven backtesting and is a great tool to have mastery of. 

Using my own C+ Yahoo Finance interface to download historical EOD data in .csv file format, which will then be used for backtesting. In the future, I will modify the data handler to integrate with the Bloomberg API on the Bloomberg Terminal in my school's library, which will also necessitate porting the program over to Windows, although that won't be much of a hassle.

Runs an event-driven loop that continuously checks an Event queue for market data updates, strategy-specific signals, orders, and fill events. Passes the market data updates through the given strategy which calculates the signals to send to the execution handler which then sends orders and finally updates the portfolio with the information of the fill. For visualization, I use GNUPlot and Qt: the former for graphing the equity curve and holdings information, and the latter for displaying performance statistics and setting various backtest environment variables, i.e. start date, end date, and initial capital. A screenshot of the interface:

<img src="./screenshot1.png" alt="Screenshot of interface"/>

It is split into several windows because I prefer using GNUplot for realtime updates to the graph rather than going to great lengths to set up multithreading in Qt for a single window application.

## Installation
### Prerequisites
* Boost
* GNU Plot
* CURL
* Qt5Widgets 
* GSL

### Ubuntu
```
sudo apt update
sudo apt upgrade
sudo snap install cmake
sudo apt install libboost-all-dev libcurl4-openssl-dev libgsl-dev gnuplot qt5-default
cmake .
make
./algotester
```

## Test your strategy
Implement your strategy in a `.cpp` file in the folder `Strategies/`, with the same structure with the `mainstrategy.cpp` (especially the `MainStrategy` class). For testing, you can paste your code in the `mainstrategy.cpp` and run `make` again to run the backtesting.

However, do not push the modified `mainstrategy.cpp` file.

The benchmark represents the buy/hold strategy (just buy at the beginning and hold till the end) with S&P500 (symbol `SPY`).