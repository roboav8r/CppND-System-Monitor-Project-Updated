#include <unistd.h>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>

#include "process.h"

using std::string;
using std::to_string;
using std::vector;

// Constructor with PID as input
Process::Process(int pid){
    pid_ = pid;
    last_stat_ = Stat();
    util_ = CpuUtilization();
};

// Return this process's ID
int Process::Pid() { return pid_; }

// TODO: Return this process's CPU utilization
inline float Process::CpuUtilization() { 

    vector<string> current_stat = Stat();
    long int utime = stoi(current_stat[13]);
    long int stime = stoi(current_stat[14]);
    long int cutime = stoi(current_stat[15]);
    long int cstime = stoi(current_stat[16]);

    float cpu_time = ((float)utime + (float)stime + (float)cutime + (float)cstime) / (float)sysconf(_SC_CLK_TCK);
  
    this->util_ = cpu_time/(float)this->UpTime();
    
    return this->util_;
}

// Return the command that generated this process
string Process::Command() { 
    return LinuxParser::Command(pid_);
}

// Return this process's memory utilization
string Process::Ram() { 
    return LinuxParser::Ram(pid_);
}

// Return the user (name) that generated this process
string Process::User() { 
    return LinuxParser::User(pid_);
}

// Return the age of this process (in seconds)
long int Process::UpTime() {
    return LinuxParser::UpTime(pid_);
}

// TODO: Overload the "less than" comparison operator for Process objects
// REMOVE: [[maybe_unused]] once you define the function
bool Process::operator<(Process const& a) const { 
    return this->util_ > a.util_;
}

// Helper function to get stat info
std::vector<std::string> Process::Stat()
{
  string line;

  std::ifstream stream(LinuxParser::kProcDirectory + std::to_string(this->pid_) + LinuxParser::kStatFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);

    // Convert line to string vector per https://knowledge.udacity.com/questions/49126
    std::istream_iterator<string> beg(linestream), end; 
    vector<string> values(beg, end);

    return values;
  }

}
