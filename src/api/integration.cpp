#include <iostream>
#include <string>
#include <curl/curl.h>
#include <nlohmann/json.hpp>
using json = nlohmann::json;
// used g++ src/api/integration.cpp -I /Users/rayenayari/Desktop/BACHELOR/CSE201/trading-platform-pp/curl -lcurl -lldap -lz && ./a.out 
// We have to put curl_global_init(CURL_GLOBAL_DEFAULT) 
// in the main file 
//Write function to pass to curl 
size_t writefunc(void *ptr, size_t size, size_t nmemb, std::string *s) {
  s->append(static_cast<char *>(ptr), size*nmemb);
  return size*nmemb;
}
int main(){
curl_global_init(CURL_GLOBAL_DEFAULT) ;
CURL *curl = curl_easy_init();   
CURLcode result; 
long httpCode(0);//Initialize the http code to 0, it can't be an int it must be a long int 
struct curl_slist *headers= NULL;
std::string token = "buk0iff48v6r2017bpg0"; // The API token which will be used
std::string data; //Contains the data



if(curl) {
  // Website settings
  curl_easy_setopt(curl, CURLOPT_URL, "https://finnhub.io/api/v1/quote?symbol=AAPL");
  std::string token_header = "X-Finnhub-Token:" + token; // token is our API key 
  // Add the token parameter to the header    
  headers = curl_slist_append(headers, token_header.c_str());     
  curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
  //Follow redirections 
  curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
  // Set the request mode to GET
  curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "GET");
  //Handle the data container 
  curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writefunc);
  curl_easy_setopt(curl,CURLOPT_WRITEDATA,&data);
  //Perform the GET request and store the HTTP code
  result=curl_easy_perform(curl);
  // always cleanup  
  curl_easy_cleanup(curl);
  curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &httpCode);
  // 200 means successful transfer
  if (httpCode==200 && result==CURLE_OK ){ 
      //  contains the requested data
      json j= json::parse(data);
      //Print out the data
      std::cout << j.dump(4) << std::endl;
      std::cout << data << std::endl;
      
  }
}
return 0;
}