#include "processor.h"

// Define default constructor
// Processor::Processor(){
//     // Construct the processor object with CPU utilization data (needed to compute time differential)
//     this->last_util_ = LinuxParser::CpuUtilization();
// }

// Use initializer list in constructor to prevent "%n in writable segment detected" error!
Processor::Processor() : last_util_{LinuxParser::CpuUtilization()} {
}

// Return the aggregate CPU utilization
float Processor::Utilization() { 

    // Compute previous CPU usage data
    // See: https://stackoverflow.com/questions/23367857/accurate-calculation-of-cpu-usage-given-in-percentage-in-linux
    long int prev_idle = LinuxParser::IdleJiffies(this->last_util_);
    long int prev_total = LinuxParser::Jiffies(this->last_util_);

    // Compute & store current CPU usage
    this->last_util_ = LinuxParser::CpuUtilization();
    long int idle = LinuxParser::IdleJiffies(this->last_util_);
    long int total = LinuxParser::Jiffies(this->last_util_);

    // Compute differential CPU usage
    long int delta_total = total - prev_total;
    long int delta_idle = idle - prev_idle;

    // Use ternary operator to avoid divide-by-zero condition
    float cpu_pct = (delta_total != 0) ? ((float)delta_total - (float)delta_idle)/(float)delta_total : ((float)total - (float)idle)/(float)total ;

    return cpu_pct;
}