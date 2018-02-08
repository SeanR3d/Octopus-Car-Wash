//Sean Reddington
//*made around Fall 2016*
//Run results will update in carWash.txt
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include "queueType.h" // header file which includes both linkedListType and QueueType classes

int averageWait(int& total, int& washed);
bool closeQueue(int& open, int& min, int& carsLeft, int& washTime);

int main() {

	ofstream outFile;
	outFile.open("carWash.txt");

	int  timeForWash, minute, timeEnteredQueue, carsWashed, totalQueueMin, timeLeftOnCar;
	float probOfArrival;
	queueType carQueue;
	int timeOpen = 600; //hours of operation for a day
	int carsInQueue = 0;

	cout << "Enter time to wash one car: ";
	cin >> timeForWash;
	cout << "Enter probability of arrival in any minute: ";
	cin >> probOfArrival;

	carsWashed = 0;
	timeEnteredQueue = 0;
	totalQueueMin = 0;
	timeLeftOnCar = 0; 
	srand(time(0));

		//Carwash begins
		for (minute = 1; minute <= timeOpen; ++minute) {

			if (!closeQueue(timeOpen, minute, carsInQueue, timeForWash)) {//closes entry to car wash to prevent cars getting stuck after hours
				if (rand() % 100 <= probOfArrival) {
					carQueue.addQueue(minute);
					carsInQueue++;
				}
			}

			if ((timeLeftOnCar == 0) && !carQueue.isEmptyQueue()) {
				timeEnteredQueue = carQueue.front();
				carQueue.deleteQueue();
				totalQueueMin = totalQueueMin + (minute - timeEnteredQueue);
				++carsWashed;
				carsInQueue--;
				timeLeftOnCar = timeForWash;
			}
			if (timeLeftOnCar != 0)
				--timeLeftOnCar;
		}
	
	//outputs results to carWash.txt
	outFile << "For a wash time of " << timeForWash 
			<< " minutes and probability rate of " << static_cast<int> (probOfArrival) << "%: " << endl;

					outFile << "\tCars washed: " << carsWashed << endl;
					outFile << setiosflags(ios::fixed | ios::showpoint);
					outFile << "\tAverage wait in queue: " << setprecision(2)
							<< float(averageWait(totalQueueMin, carsWashed)) << " minutes" << endl;
					outFile << "\tCars left waiting in line for eternity: " << carsInQueue << endl;


	outFile.close();
	return 0;
}

int averageWait(int& total, int& washed) {

	if (washed == 0)
		return total;

	return total / washed;
}

bool closeQueue(int& open, int& min, int& carsLeft, int& washTime) {
	int timeLeft = open - min;

		if ((carsLeft * washTime) <= (timeLeft - washTime))
			return false;
}