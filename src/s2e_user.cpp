/**
 * @file s2e_user.cpp
 * @brief The main file of S2E-USER
 */

#ifdef WIN32
#define _WINSOCKAPI_  // stops windows.h including winsock.h
#include <tchar.h>
#include <windows.h>
#endif

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <string>

// Simulator includes
#include "library/logger/initialize_log.hpp"

// Add custom include files
#include <./simulation/monte_carlo_simulation/initialize_monte_carlo_simulation.hpp>

#include "./simulation/case/user_case.hpp"

void print_path(std::string path) {
#ifdef WIN32
  std::cout << path << std::endl;
#else
  const char *rpath = realpath(path.c_str(), NULL);
  if (rpath) {
    std::cout << rpath << std::endl;
    free((void *)rpath);
  }
#endif
}

#ifdef WIN32
int main(int argc, _TCHAR *argv[])
#else
int main(int argc, char *argv[])
#endif
{
  using namespace std::chrono;

  system_clock::time_point start, end;
  start = system_clock::now();

  std::string data_path = "../../data/";
  std::string ini_path = INI_FILE_DIR_FROM_EXE;
  std::string ini_file = ini_path + "/user_simulation_base.ini";

  // Parsing arguments:  SatAttSim <data_path> [ini_file]
  if (argc == 0) {
    std::cout << "Usage: SatAttSim <data_path> [ini file path]" << std::endl;
    return EXIT_FAILURE;
  }
  if (argc > 1) {
    data_path = std::string(argv[1]);
    if (data_path.back() != '/') data_path += "/";
  }
  if (argc > 2) {
    ini_file = std::string(argv[2]);
  }

  std::cout << "Starting simulation..." << std::endl;
  std::cout << "\tData path: ";
  print_path(data_path);
  std::cout << "\tIni file: ";
  print_path(ini_file);

  MonteCarloSimulationExecutor *mc_simulator = InitMonteCarloSimulation(ini_file);
  Logger *log_mc_simulator = InitMonteCarloLog(ini_file, mc_simulator->IsEnabled());

  while (mc_simulator->WillExecuteNextCase()) {
    auto simulation_case = UserCase(ini_file, *mc_simulator, log_mc_simulator->GetLogPath());
    // Initialize
    log_mc_simulator->AddLogList(&simulation_case);
    if (mc_simulator->GetNumberOfExecutionsDone() == 0) log_mc_simulator->WriteHeaders();
    simulation_case.Initialize();

    // Main
    log_mc_simulator->WriteValues();  // log initial value
    simulation_case.Main();
    mc_simulator->AtTheEndOfEachCase();
    log_mc_simulator->WriteValues();  // log final value
    log_mc_simulator->ClearLogList();
  }

  delete log_mc_simulator;
  delete mc_simulator;

  end = system_clock::now();
  double time = static_cast<double>(duration_cast<microseconds>(end - start).count() / 1000000.0);
  std::cout << std::endl << "Simulation execution time: " << time << "sec" << std::endl << std::endl;

  return EXIT_SUCCESS;
}
