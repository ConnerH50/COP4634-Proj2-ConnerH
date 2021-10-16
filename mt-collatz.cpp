#include <iostream>
#include <thread>
#include "pthread.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <mutex>

using namespace std;

int COUNTER = 2;
int numInArray = 1;
int MAXNUMBER;
int histogramArray[1000];
bool NOLOCK = false;
mutex mtxLocker;

void runCollatz(int collatzRange, long long threadNum){

	int stoppingTime = 0; // increment every loop in the while loop, put this int into the histogram array
	long long num = COUNTER; // this is the number we use for this iteration, always set equal to COUNTER

	while(1){
		if(NOLOCK == true){
			if(COUNTER >= collatzRange){
				break;
			}
			num = COUNTER++;
		}else{		
			mtxLocker.lock();
			if(COUNTER >= collatzRange){
				mtxLocker.unlock();
				break;
			}
			num = COUNTER++;
			mtxLocker.unlock();
		}
	
		stoppingTime = 0;	

		while(num > 1){
			stoppingTime++;
			if(num % 2 == 0){ //if even
				num = num / 2;
			}else{ //if odd
				num = (3 * num) + 1;
			}
		}
		
		if(NOLOCK == true){
			histogramArray[stoppingTime]++;
		}else{
			mtxLocker.lock();
			histogramArray[stoppingTime]++;
			mtxLocker.unlock();
		}

	}
}

int main(int argc, char **argv){

	struct timespec start, stop;

	if(argv[3] != NULL){
		if(strcmp(argv[3], "-nolock") == 0){
			NOLOCK = true;
		}
	}

	thread threadArray[atoi(argv[2])];
	MAXNUMBER = atoi(argv[1]);

	for(int i = 0; i < 1000; i++){
		histogramArray[i] = 0;
	}

	clock_gettime(CLOCK_REALTIME, &start);

	// create the threads
	for(int i = 0; i < atoi(argv[2]); i++){
		threadArray[i] = thread(runCollatz, atoi(argv[1]), i);
	}

	//join threads with main thread
	for(int i = 0; i < atoi(argv[2]); i++){
		threadArray[i].join();
	}

	//print out stoppingtime frequency
	cout << 0 << "," << histogramArray[0] << endl;
	for(int i = 1; i < 1000; i++){
		cout << i << "," << histogramArray[i] << endl;
	}

	clock_gettime(CLOCK_REALTIME, &stop);
	double time = (stop.tv_sec - start.tv_sec) + (stop.tv_nsec - start.tv_nsec) / 100000000.0;
	cerr << argv[1] << "," << argv[2] << "," << time << endl;

	return 0;
}
