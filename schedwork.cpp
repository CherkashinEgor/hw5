

#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
// add or remove necessary headers as you please
#include "schedwork.h"

using namespace std;

// a constant that can be used to indicate an INVALID 
// worker ID if that is useful to your implementation.
// Feel free to not use or delete.
static const Worker_T INVALID_ID = (unsigned int)-1;


// Add prototypes for any helper functions here
bool scheduleHelper(int row, int col, const AvailabilityMatrix& avail, const size_t dailyNeed, const size_t maxShifts, DailySchedule& sched);
bool checkIfValid(const AvailabilityMatrix& avail, const size_t dailyNeed, const size_t maxShifts, DailySchedule& sched, Worker_T id);
// Add your implementation of schedule() and other helper functions here

bool schedule(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed, // d
    const size_t maxShifts, // m
    DailySchedule& sched
)
{
    if(avail.size() == 0U){
        return false;
    }
    sched.clear();
    // Add your code below
    // sched is a NxD matrix

    //Constraints
    //Each person (avail[Day][Worker]) can only work m times
    std::vector<int> workCounter(avail[0].size(), 0);
    for(int i = 0; i < avail.size(); i++){
        vector<Worker_T> temp;
        sched.push_back(temp);
        for(int j = 0; j < dailyNeed; j++){
            sched[i].push_back(INVALID_ID);
        }
    }
    return scheduleHelper(0, 0, avail, dailyNeed, maxShifts, sched);

}

bool scheduleHelper(int row, int col, const AvailabilityMatrix& avail, const size_t dailyNeed, const size_t maxShifts, DailySchedule& sched){
    int n = int(avail.size());
    if(row == n - 1 && col == dailyNeed){
        return true;
    }
    if(col == dailyNeed){
        row += 1;
        col = 0;
    }
    for(Worker_T id = 0; id < Worker_T(int(avail[0].size())); id++){
        sched[row][col] = id;
        bool temp = checkIfValid(avail, dailyNeed, maxShifts, sched, id);
        if(temp){
            bool nxt = scheduleHelper(row, col+1, avail, dailyNeed, maxShifts, sched);
            if(nxt){
                return true;
            }
        }
        sched[row][col] = INVALID_ID;
    }
    return false;
}

bool checkIfValid(const AvailabilityMatrix& avail, const size_t dailyNeed, const size_t maxShifts, DailySchedule& sched, Worker_T id){
    int d = static_cast<int>(dailyNeed);
    int m = static_cast<int>(maxShifts);
    int n = static_cast<int>(avail.size());
    int total_work = 0;
    for(int i = 0; i < n; i++){
        int daily_work = 0;
        for(int j = 0; j < d; j++){
            if(sched[i][j] == id && id != INVALID_ID){
                if(avail[i][int(id)] == 0){
                    return false;
                }
                daily_work += 1;
                total_work += 1;
            }
        }
        if(daily_work > 1){
            return false;
        }
    }
    if(total_work > m){
        return false;
    }
    return true;
}