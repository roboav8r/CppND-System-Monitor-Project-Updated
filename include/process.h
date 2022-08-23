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
  std::string Command();                   // TODO: See src/process.cpp
  float CpuUtilization();                  // TODO: See src/process.cpp
  std::string Ram();                       // TODO: See src/process.cpp
  long int UpTime();
  bool operator<(Process const& a) const;  // TODO: See src/process.cpp

  Process(int); // Constructor with PID as input

 private:
  int pid_;
};

#endif