#ifndef STOCK_H
#define STOCK_H

#include <string>
#include <QJsonObject>
#include <QJsonArray>
#include <QMap>
#include <QVector>
#include "api/api.h"

class Stock {
 private:
  std::string symbol;
  QJsonObject dataByDay;
  qint64 latestTimeStampByDay;
  qint64 latestTimeStampByMinute;
  QMap<std::string, QVector<double>> dataByMinute;
  QJsonArray stockNews;
  QJsonObject sentimentData;
  API *api;

 public:
  Stock(std::string);
  ~Stock();

  std::string getSymbol();
  qint64 getLatestTimestampByDay();
  qint64 getLatestTimestampByMinute();
  QJsonObject getDataByDay();
  QJsonArray getNews();
  QMap<std::string, QVector<double>> getDataByMinute();
  QMap<std::string, double> getDataByMinute(int idx);
  int getDataByMinuteSize();
  QJsonObject getSentimentData();
  void updateDataByDay();
  //We do not return the update data by day because it only updates once a day so we do not have a problem with graphing.
  //And it is mainly used by Strategy class to give their predictions.
  void updateDataByMinute();
  //We return here the updated data so that the GUI team could add only the new data points and not all the data we have.
  void updateNews();
  void updateSentimentData();
};

#endif // STOCK_H

/*
Sample Output of dataByDay for apple stock:
Test run on 07/12/2020 14:43:05 (CET) (Monday) with resolution "D" that is one day and interval current time and going back one month.
Notice that the first data point we get t=1604880000 corresponds to 11/09/2020
It is the case because the API does not return data points when it is weekend or holidays. In short when the market is close.
{
"c":[116.31999969482,115.9700012207,119.48999786377,119.20999908447,119.26000213623,120.30000305176,119.38999938965,118.0299987793,118.63999938965,117.33999633789,113.84999847412,115.16999816895,116.0299987793,116.58999633789,119.05000305176,122.7200012207,123.08000183105,122.94000244141,122.25],
"h":[121.98000335693,117.58000183105,119.58999633789,120.51999664307,119.67169952393,120.98999786377,120.66999816895,119.81999969482,118.94999694824,118.76999664307,117.58999633789,115.84999847412,116.75,117.48999786377,120.9700012207,123.46929931641,123.37000274658,123.76999664307,122.86080169678],
"l":[116.12000274658,114.13999938965,116.51000213623,118.58000183105,117.87000274658,118.16999816895,118.98999786377,118,116.83999633789,117.29000091553,113.76000213623,112.58999633789,115.23000335693,116.2200012207,116.80999755859,120.01000213623,120.91999816895,122.23999786377,121.51999664307],
"o":[120.5,115.56999969482,117.16999816895,119.55000305176,119.44000244141,118.93000030518,119.51000213623,118.61000061035,117.33000183105,118.63999938965,117.20999908447,113.95999908447,115.62999725342,116.56999969482,116.9700012207,121.01000213623,122.15000152588,123.51000213623,122.59999847412],
"s":"ok",
"t":[1604880000,1604966400,1605052800,1605139200,1605225600,1605484800,1605571200,1605657600,1605744000,1605830400,1606089600,1606176000,1606262400,1606435200,1606694400,1606780800,1606867200,1606953600,1607040000],
"v":[154515312,138023392,112294952,103350672,81689000,91183016,74270976,76322112,74112976,73604000,127959320,113874216,76499232,46691000,167204992,125922000,89004192,78967632,78260000]
}


From Finnhub webpage:
o
List of open prices for returned candles.
h
List of high prices for returned candles.
l
List of low prices for returned candles.
c
List of close prices for returned candles.
v
List of volume data for returned candles.
t
List of timestamp for returned candles.
s
Status of the response. This field can either be ok or no_data.
*/


/*
Sample Output of stockNews for apple stock:
Test run on 08/12/2020 13:07 (CET) (Tuesday) and 2 hours worth of data:
[{"category":"company","datetime":1607418000,"headline":"Apple preps next Mac chips with aim to outclass highest-end PCs","id":61651699,"image":"https://apicms.thestar.com.my/uploads/images/2020/12/07/964780.jpg","related":"AAPL","source":"https://www.thestar.com.my","summary":"Apple Inc is planning a series of new Mac processors for introduction as early as 2021 that are aimed at outperforming Intel Corp’s fastest.","url":"https://www.thestar.com.my/tech/tech-news/2020/12/08/apple-preps-next-mac-chips-with-aim-to-outclass-highest-end-pcs"},{"category":"company","datetime":1607405756,"headline":"Will Apple ‘surprise’ consumers with a new product announcement today?","id":61651736,"image":"https://images.indianexpress.com/2020/12/AirPods-Studio.jpg","related":"AAPL","source":"https://indianexpress.com","summary":"Apple is rumoured to announce a new mysterious product on Tuesday.  Will it be AirPods Studio or AirTags or an updated Apple TV streaming box?","url":"https://indianexpress.com/article/technology/tech-news-technology/will-apple-surprise-consumers-with-a-new-hardware-product-announcement-december-8-2020-7096079/"},{"category":"company","datetime":1607400178,"headline":"Apple Music now accessible on Google smart speakers and displays","id":61651760,"image":"https://images.indianexpress.com/2020/12/Apple-music.jpg","related":"AAPL","source":"https://indianexpress.com","summary":"To play music from Apple Music, you first need to link your Apple Music account in the Google Home app.","url":"https://indianexpress.com/article/technology/tech-news-technology/apple-music-now-accessible-on-google-smart-speakers-and-displays/"},{"category":"company","datetime":1607399640,"headline":"Report: Apple Developing Mac Chips That Will Be Faster Than Intel's Top-Line Products | The Motley Fool","id":61651882,"image":"https://g.foolcdn.com/editorial/images/604022/cpu-being-inserted-by-a-hand.jpg","related":"AAPL","source":"https://www.fool.com","summary":"The company apparently wants to beat its departing business partner at its own game.","url":"https://www.fool.com/investing/2020/12/07/report-apple-developing-mac-chips-that-will-be-fas/"},{"category":"company","datetime":1607396850,"headline":"Apple MacBooks Could Have Its New 32-Core ARM-Based","id":61651638,"image":"https://1734811051.rsc.cdn77.org/data/images/full/376742/apple-tests-new-chip-models-for-its-macbooks-it-is-reportedly-working-on-a-32-core-processor.jpg","related":"AAPL","source":"https://www.techtimes.com","summary":"Apple is also planning to launch a new half-sized Mac Pro by 2022.","url":"https://www.techtimes.com/articles/254804/20201207/apples-alleged-new-32-core-arm-based-processor-appear-macbooks.htm"},{"category":"company","datetime":1607389597,"headline":"Concept imagines new Apple Watch Series 7 with flat edges - 9to5Mac","id":61650871,"image":"https://i2.wp.com/9to5mac.com/wp-content/uploads/sites/6/2020/12/Apple-Watch-Series-7-concept.jpg?resize=1200%2C628\u0026quality=82\u0026strip=all\u0026ssl=1","related":"AAPL","source":"https://9to5mac.com","summary":"After the 2018 iPad Pro, Apple introduced all the new iPhone 12 models with flat edges that resemble its classic products, such as the first generation iPad and the iPhone 5. But what about Apple Watch? While there’s no evidence that Apple will redesign its smartwatch anytime soon, designer Wilson Nicklaus has created a concept […]","url":"https://9to5mac.com/2020/12/07/concept-imagines-new-apple-watch-series-7-with-flat-edges/"},{"category":"company","datetime":1607386560,"headline":"Will Tesla Do Another Stock Split in 2021?","id":61652039,"image":"https://www.nasdaq.com/sites/acquia.prod/files/2019-05/0902-Q19%20Total%20Markets%20photos%20and%20gif_CC8.jpg?781689970","related":"AAPL","source":"Nasdaq","summary":"2020 has been an amazing year for Tesla (NASDAQ: TSLA) shareholders. The electric-auto maker's stock price started the year at $418 per share, and on Dec. 7, it fetched more than $625 per share. That would be pretty impressive even if it weren't for the 5-for-1 stock split that T","url":"https://www.nasdaq.com/articles/will-tesla-do-another-stock-split-in-2021-2020-12-08"},{"category":"company","datetime":1607385600,"headline":"Mobile Value-added Services (VAS) Market to Grow by $ 342.50 Billion amid Recession | Includes Impact of COVID-19 and Business Continuity Plan for the New Normal | Technavio","id":61651630,"image":"https://mms.businesswire.com/media/20201207005755/en/844785/23/IRTNTR44646.jpg","related":"AAPL","source":"businesswire","summary":"The Mobile Value-added Services (VAS) Market will grow by USD 342.50 bn during 2020-2024","url":"https://www.businesswire.com/news/home/20201207005755/en/4881450/Mobile-Value-added-Services-VAS-Market-to-Grow-by-342.50-Billion-amid-Recession-Includes-Impact-of-COVID-19-and-Business-Continuity-Plan-for-the-New-Normal-Technavio"},{"category":"company","datetime":1607385600,"headline":"Mobile Value-added Services (VAS) Market to Grow by $ 342.50 Billion amid Recession | Includes Impact of COVID-19 and Business Continuity Plan for the New Normal | Technavio","id":61651629,"image":"https://mms.businesswire.com/media/20201207005755/en/844785/23/IRTNTR44646.jpg","related":"AAPL","source":"businesswire","summary":"The Mobile Value-added Services (VAS) Market will grow by USD 342.50 bn during 2020-2024","url":"https://www.businesswire.com/news/home/20201207005755/en/4881429/Mobile-Value-added-Services-VAS-Market-to-Grow-by-342.50-Billion-amid-Recession-Includes-Impact-of-COVID-19-and-Business-Continuity-Plan-for-the-New-Normal-Technavio"},{"category":"company","datetime":1607385600,"headline":"Mobile Value-added Services (VAS) Market to Grow by $ 342.50 Billion amid Recession | Includes Impact of COVID-19 and Business Continuity Plan for the New Normal | Technavio","id":61651621,"image":"https://mms.businesswire.com/media/20201207005755/en/844785/23/IRTNTR44646.jpg","related":"AAPL","source":"businesswire","summary":"The Mobile Value-added Services (VAS) Market will grow by USD 342.50 bn during 2020-2024","url":"https://www.businesswire.com/news/home/20201207005755/en/Mobile-Value-added-Services-VAS-Market-to-Grow-by-342.50-Billion-amid-Recession-Includes-Impact-of-COVID-19-and-Business-Continuity-Plan-for-the-New-Normal-Technavio"}]
*/
