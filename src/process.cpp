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
};

// Return this process's ID
int Process::Pid() { return pid_; }

// TODO: Return this process's CPU utilization
float Process::CpuUtilization() { 

  // string up_time_sec, idle_time_sec;
  string line;
  float cpu_util;
  
  std::ifstream stream(LinuxParser::kProcDirectory + std::to_string(this->pid_) + LinuxParser::kStatFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);

    // Convert line to string vector per https://knowledge.udacity.com/questions/49126
    std::istream_iterator<string> beg(linestream), end; 
    vector<string> values(beg, end);

    cpu_util = ((stoi(values[13]) + stoi(values[14]) + stoi(values[15]) + stoi(values[16])) / sysconf(_SC_CLK_TCK));
  }

  //this->util_ = cpu_util/this->UpTime();

  return this->pid_/1000 ;
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
    return this->pid_ > a.pid_;
}