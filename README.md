# TradingPlatform++
TradingPlatform++, as the name suggests, is a fully featured stock trading platform built in C++.

## Features we provide:
1. Give the user the ability to create many portfolios where each portfolio has some stocks to trade and its own performance assessment.
2. Display the line chart and candle chart of any stock that Finnhub provides along with a vertical tracer to show the closing price.
3. Display each company's specific news under its graph.
4. Allow the user to buy and sell stocks with different order types and display his performance accordingly.
5. Show the Market news in a specific tab for more detailed info about the markets.
6. Display the plot of some strategies that we researched in the Strategy tab to allow the user to understand them.
7. Show the signals of whether we should buy or sell according to these strategies and the sentiment analysis of the news.

## Team Members:
1. Mehdi Makni (Project Leader)
2. Mira Hajar
3. Ayari Rayen
4. Guruprerana Shabadi (GUI Team Leader and Git Master)
5. Maxime Lamy
6. Maayane Attias
7. Mamoune Mouchtaki
8. Alban Puech (Trello Leader)
9. Khanh Nguyen
10. Vishrut Malik
11. Frederic Marcel Tchouli
12. Vinh Nguyen (Research Team Leader)

We have been organized mainly into these subgroups:

### API Team

1. Mehdi Makni
2. Rayen Ayari

### GUI Team

1. Guruprerana Shabadi 
2. Khanh Nguyen
3. Maxime Lamy
4. Mamoune Mouchtaki

### Research Team

1. Vinh Nguyen 
2. Frederic Marcel Tchouli
3. Vishrut Malik
4. Alban Puech
5. Mira Hajar
6. Maayane Attias

# Instructions for Ubuntu and macOS:

## Installing cURL

In order to call the API Finnhub, we use [libcurl](https://curl.se/libcurl/).
Run the following commands on the terminal:

### Ubuntu
```
sudo apt install curl
```

### macOS
```
brew install curl
```

## Building guide

If you have already downloaded Qt Creator then open the project in Qt Creator run it.

Otherwise you can follow these steps.

### Ubuntu

Run the following commands on the terminal:
```
sudo apt-get install build-essential
sudo apt-get install qt5-default
```

### macOS

Run the following commands on the terminal:
```
brew qt5-default
```

Now you need to run this script that you can find in `scripts\build.sh`:
```
rm -rf build
mkdir build
cd build
qmake ../src/trading-platform-pp.pro
make -j8
```
