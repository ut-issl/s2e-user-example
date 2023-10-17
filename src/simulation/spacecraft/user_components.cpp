/**
 * @file user_components.cpp
 * @brief An example of user side components management installed on a spacecraft
 */

#include "user_components.hpp"

#include <library/initialize/initialize_file_access.hpp>
#include <library/utilities/macros.hpp>

UserComponents::UserComponents(const Dynamics *dynamics, Structure *structure, const LocalEnvironment *local_environment,
                               const GlobalEnvironment *global_environment, const SimulationConfiguration *configuration,
                               ClockGenerator *clock_generator, const unsigned int spacecraft_id)
    : configuration_(configuration),
      dynamics_(dynamics),
      structure_(structure),
      local_environment_(local_environment),
      global_environment_(global_environment) {
  // These variables are unused because this is a sample code.
  UNUSED(structure_);
  UNUSED(local_environment_);

  // Component instances
  obc_ = new OnBoardComputer(clock_generator);

  // Common
  IniAccess iniAccess = IniAccess(configuration_->spacecraft_file_list_[spacecraft_id]);
  const double compo_step_sec = global_environment_->GetSimulationTime().GetComponentStepTime_s();

  // Initialize of GYRO class
  std::string file_name = iniAccess.ReadString("COMPONENT_FILES", "gyro_file");
  configuration_->main_logger_->CopyFileToLogDirectory(file_name);
  gyro_sensor_ = new GyroSensor(InitGyroSensor(clock_generator, 1, file_name, compo_step_sec, dynamics_));
}

UserComponents::~UserComponents() {
  delete gyro_sensor_;
  // OBC must be deleted the last since it has com ports
  delete obc_;
}

Vector<3> UserComponents::GenerateForce_b_N() {
  // There is no orbit control component, so it remains 0
  Vector<3> force_b_N(0.0);
  return force_b_N;
}

Vector<3> UserComponents::GenerateTorque_b_Nm() {
  // No attitude control component
  Vector<3> torque_b_Nm(0.0);
  return torque_b_Nm;
}

void UserComponents::LogSetup(Logger &logger) { logger.AddLogList(gyro_sensor_); }
