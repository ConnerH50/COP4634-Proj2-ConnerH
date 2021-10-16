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
//int *histogramArray;
int histogramArray[1000];
bool NOLOCK = false;
mutex mtxLocker;

void runCollatz(int collatzRange, int threadNum){

	int stoppingTime = 0; // increment every loop in the while loop, put this int into the histogram array
	int num = COUNTER; // this is the number we use for this iteration, always set equal to COUNTER

	while(1){
		if(NOLOCK == false){
			//cout << "NOLOCK enabled" << endl;

			if(COUNTER > collatzRange){
				break;
			}
			num = COUNTER++;
		}else{		
			mtxLocker.lock();
			if(COUNTER > collatzRange){
				mtxLocker.unlock();
				break;
			}
			num = COUNTER++;
			mtxLocker.unlock();
		}
	
		stoppingTime = 0;	

		while(num > 1){
			stoppingTime++;
			//cout << num << ", ";

			if(num % 2 == 0){ //if even
				num = num / 2;
			}else{ //if odd
				num = (3 * num) + 1;
			}
		}
		
		if(NOLOCK == false){
			histogramArray[stoppingTime]++;
		}else{
			mtxLocker.lock();
			histogramArray[stoppingTime]++;
			mtxLocker.unlock();
		}

	}
}

int main(int argc, char **argv){

	if(argv[3] != NULL){
		if(strcmp(argv[3], "-nolock") == 0){
			NOLOCK = true;
			cout << "NOLOCK enabled" << endl;
		}
	}

	thread threadArray[atoi(argv[2])];

	cout << atoi(argv[1]) << endl;
	MAXNUMBER = atoi(argv[1]);
	//histogramArray = new int[atoi(argv[1])];

	// init historgram array with 0s
	for(int i = 0; i < atoi(argv[1]); i++){
		//histogramArray[i] = 0;
	}

	for(int i = 0; i < 1000; i++){
		histogramArray[i] = 0;
	}

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
		if(histogramArray[i] == 0){
			;
		}
		else{
			cout << i << "," << histogramArray[i] << endl;
		}
	}

	/*cout << histogramArray[0] << ", ";

	for(int i = 1; i < MAXNUMBER; i++){
		if(histogramArray[i] == 0){
			;
		}else{
			cout << i << "," << histogramArray[i] << endl;
		}
	}
	*/

	cout << "Finished!" << endl;
	//delete[] histogramArray;

	return 0;
}
