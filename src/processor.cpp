#include "processor.h"

// Define default constructor
Processor::Processor(){
    // Construct the processor object with CPU utilization data (needed to compute time differential)
    this->last_util_ = LinuxParser::CpuUtilization();
}

// Return the aggregate CPU utilization
float Processor::Utilization() { 

    // Compute previous CPU usage data
    // See: https://stackoverflow.com/questions/23367857/accurate-calculation-of-cpu-usage-given-in-percentage-in-linux
    long int prev_idle = LinuxParser::IdleJiffies(this->last_util_);
    long int prev_total = LinuxParser::Jiffies(this->last_util_);

    std::vector<std::string> current_util = LinuxParser::CpuUtilization();
    this->last_util_ = current_util; // store current utilization for next iteration

    long int idle = LinuxParser::IdleJiffies(current_util);
    long int total = LinuxParser::Jiffies(current_util);

    long int delta_total = total - prev_total;
    long int delta_idle = idle - prev_idle;

    float cpu_pct = ((float)delta_total - (float)delta_idle)/(float)delta_total;

    return cpu_pct;
}