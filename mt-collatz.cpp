#include <iostream>
#include <thread>
#include "pthread.h"
#include <stdio.h>
#include <stdlib.h>
#include <mutex>

using namespace std;

int COUNTER = 2;
int numInArray = 1;
int MAXNUMBER;
int *histogramArray;
mutex mtxLocker;

void runCollatz(int collatzRange, int threadNum){
	//cout << "Thread ID "<< threadNum << endl;
	//cout << collatzRange << endl;

	int stoppingTime = 0; // increment every loop in the while loop, put this int into the histogram array
	int num = COUNTER; // this is the number we use for this iteration, always set equal to COUNTER

	while(1){
		mtxLocker.lock();
		if(COUNTER > collatzRange){
			mtxLocker.unlock();
			break;
		}
		num = COUNTER++;
		mtxLocker.unlock();
	
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

		//cout << num << endl;
		histogramArray[numInArray++] = stoppingTime;

	}
}

int main(int argc, char **argv){

	thread threadArray[atoi(argv[2])];

	cout << atoi(argv[1]) << endl;
	MAXNUMBER = atoi(argv[1]);
	histogramArray = new int[atoi(argv[1])];

	// init historgram array with 0s
	for(int i = 0; i < atoi(argv[1]); i++){
		histogramArray[i] = 0;
	}

	// create the threads
	for(int i = 0; i < atoi(argv[2]); i++){
		threadArray[i] = thread(runCollatz, atoi(argv[1]), i);
	}

	/*for(int i = 0; i < MAXNUMBER; i++){
		cout << histogramArray[i] << ", ";
	}
	cout << endl;*/

	//join threads with main thread
	for(int i = 0; i < atoi(argv[2]); i++){
		threadArray[i].join();
	}

	cout << histogramArray[0] << ", ";

	for(int i = 1; i < MAXNUMBER; i++){
		if(histogramArray[i] == 0){
			;
		}else{
			cout << histogramArray[i] << ", ";
		}
	}
	cout << endl << endl << MAXNUMBER << endl;

	cout << "Finished!" << endl;
	delete[] histogramArray;

	return 0;
}
