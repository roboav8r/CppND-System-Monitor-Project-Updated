#include <string>

#include "format.h"

using std::string;

// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
string Format::ElapsedTime(long seconds) { 
    int hrs = int( (seconds - seconds%3600) / 3600);
    int mins = int( (seconds - hrs*3600 - seconds%60) / 60);
    int secs = int( seconds - hrs*3600 - mins*60 );

    string hr_string = (hrs>=10) ? std::to_string(hrs) : '0' + std::to_string(hrs);
    string min_string = (mins>=10) ? std::to_string(mins) : '0' + std::to_string(mins);
    string sec_string = (secs>=10) ? std::to_string(secs) : '0' + std::to_string(secs);

    return hr_string + ":" + min_string + ":" + sec_string; 
}