#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include <curl/curl.h>

int main(int argc, char *argv[])
{
  if(argc!= 4){
printf("Insert ip, port,number_of_packets");
printf("Example: main_curl 8000 10");

  }
  CURL *curl;
  CURLcode res;
  struct curl_slist *headers = NULL;
  int number_of_packets = atoi(argv[3]);
  printf("Number packets  %d",number_of_packets);

  char url[100];
  char path[]="/nudm-sdm/v2/imsi-460020301001001?dataset-names=AM,SMF_SEL";
  strcpy(url, "https://");
  strcat(url,argv[1]);
  strcat(url,":");
  strcat(url,argv[2]);
  strcat(url,path);
  printf("Url  %s\n",  url);

  long window_size_increment = 65535; // Set the window size increment to maximum size, 2^31-1

  // Initialize the libcurl library
  curl_global_init(CURL_GLOBAL_ALL);

  // Create a new curl handle
  curl = curl_easy_init();
  if (curl) {
    // Set the URL to send the request to
    curl_easy_setopt(curl, CURLOPT_URL, url);
    curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
    //disable ssl certificate validation
  curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
  curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);
    // Add a custom header to the request to send the window size increment
    char header[128];
    sprintf(header, "Window-Size-Increment: %ld", window_size_increment);
    headers = curl_slist_append(headers, header);
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

    // Set the HTTP/2 version to use
    curl_easy_setopt(curl, CURLOPT_HTTP_VERSION, CURL_HTTP_VERSION_2_0);
    for(int i=0;i<number_of_packets;i++){
          res = curl_easy_perform(curl);
          if (res != CURLE_OK) {
             fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
       }
    }
    // Perform the request
      

    // Cleanup
    curl_slist_free_all(headers);
    curl_easy_cleanup(curl);
  }

  // Cleanup the libcurl library
  curl_global_cleanup();

  return 0;
}
