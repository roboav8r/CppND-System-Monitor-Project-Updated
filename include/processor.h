#ifndef PROCESSOR_H
#define PROCESSOR_H

#include "linux_parser.h"

class Processor {
 public:
  Processor();
  float Utilization();

 private:
  std::vector<std::string> last_util_; 
};

#endif