#ifndef PROCESS_H
#define PROCESS_H

#include <string>

#include "linux_parser.h"
/*
Basic class for Process representation
It contains relevant attributes as shown below
*/
class Process {
 public:
  int Pid();
  std::string User();
  std::string Command();
  float CpuUtilization();                  // TODO: See src/process.cpp
  std::string Ram();
  long int UpTime();
  bool operator<(Process const& a) const;  // TODO: See src/process.cpp
  std::vector<std::string> Stat(); // Helper function to get stat info

  Process(int); // Constructor with PID as input

 private:
  int pid_;
  std::vector<std::string> last_stat_;
  float util_;
};

#endif