#include "mt-collatz.hpp"
#include <iostream>
#include <thread>
#include "pthread.h"
#include <stdio.h>
#include <stdlib.h>

int COUNTER = 2;
int *histogramArray;

void collatz(){
	cout << "Thread ID "<< std::this_thread::get_id() << endl;

	int stoppingTime = 0; // increment every loop in the while loop, put this int into the histogram array
	int num = COUNTER; // this is the number we use for this iteration, always set equal to COUNTER
}

int main(int argc, char **argv){

	thread threadArray[atoi(argv[2])];

	cout << atoi(argv[1]) << endl;
	histogramArray = new int[atoi(argv[1])];

	// init historgram array with 0s
	for(int i = 0; i < atoi(argv[1]); i++){
		histogramArray[i] = 0;
	}

	// create the threads
	for(int i = 0; i < atoi(argv[2]); i++){
		threadArray[i] = thread(collatz);
	}

	//join threads with main thread
	for(int i = 0; i < atoi(argv[2]); i++){
		threadArray[i].join();
	}

	cout << "Finished!" << endl;
	delete[] histogramArray;

	return 0;
}
