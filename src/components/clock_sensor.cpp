/**
 * @file clock_sensor.cpp
 * @brief An example to emulate a sensor to measure simulation elapsed time
 */

#include "clock_sensor.hpp"

#include <library/initialize/initialize_file_access.hpp>

ClockSensor::ClockSensor(const int prescaler, ClockGenerator* clock_generator, const SimulationTime& simulation_time, const double bias_s)
    : Component(prescaler, clock_generator), simulation_time_(simulation_time), bias_s_(bias_s), time_output_s_(0.0) {}

void ClockSensor::MainRoutine(const int time_count) {
  UNUSED(time_count);
  time_output_s_ = simulation_time_.GetElapsedTime_s() + bias_s_;
}

std::string ClockSensor::GetLogHeader() const {
  std::string str_tmp = "";
  std::string section = "clock_sensor_";
  str_tmp += WriteScalar(section + "observed_time", "sec");

  return str_tmp;
}

std::string ClockSensor::GetLogValue() const {
  std::string str_tmp = "";

  str_tmp += WriteScalar(time_output_s_);

  return str_tmp;
}

ClockSensor InitClockSensor(ClockGenerator* clock_generator, const SimulationTime& simulation_time, const std::string file_name) {
  IniAccess ini_file(file_name);

  const double bias_s = ini_file.ReadDouble("ClockSensor", "bias_s");
  const int prescaler = ini_file.ReadInt("ClockSensor", "prescaler");
  ClockSensor clock_sensor(prescaler, clock_generator, simulation_time, bias_s);

  return clock_sensor;
}
