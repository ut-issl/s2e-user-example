/**
 * @file user_components.cpp
 * @brief An example of user side components management installed on a spacecraft
 */

#include "user_components.hpp"

#include <setting_file_reader/initialize_file_access.hpp>
#include <utilities/macros.hpp>

UserComponents::UserComponents(const s2e::dynamics::Dynamics *dynamics, s2e::spacecraft::Structure *structure,
                               const s2e::environment::LocalEnvironment *local_environment,
                               const s2e::environment::GlobalEnvironment *global_environment,
                               const s2e::simulation::SimulationConfiguration *configuration, s2e::environment::ClockGenerator *clock_generator,
                               const unsigned int spacecraft_id)
    : configuration_(configuration),
      dynamics_(dynamics),
      structure_(structure),
      local_environment_(local_environment),
      global_environment_(global_environment) {
  // These variables are unused because this is a sample code.
  UNUSED(spacecraft_id);
  UNUSED(configuration_);
  UNUSED(dynamics_);
  UNUSED(structure_);
  UNUSED(local_environment_);
  UNUSED(global_environment_);

  // Common
  s2e::setting_file_reader::IniAccess spacecraft_ini_file = s2e::setting_file_reader::IniAccess(configuration_->spacecraft_file_list_[spacecraft_id]);
  const double compo_step_sec = global_environment_->GetSimulationTime().GetComponentStepTime_s();
  std::string component_ini_file_name;

  // Component instances
  obc_ = new UserOnBoardComputer(clock_generator, *this);

  // Initialize of GyroSensor class
  component_ini_file_name = spacecraft_ini_file.ReadString("COMPONENT_FILES", "gyro_file");
  configuration_->main_logger_->CopyFileToLogDirectory(component_ini_file_name);
  gyro_sensor_ = new s2e::components::GyroSensor(s2e::components::InitGyroSensor(clock_generator, 1, component_ini_file_name, compo_step_sec, dynamics));

  // Initialize of ReactionWheel class
  component_ini_file_name = spacecraft_ini_file.ReadString("COMPONENT_FILES", "reaction_wheel_file");
  configuration_->main_logger_->CopyFileToLogDirectory(component_ini_file_name);
  reaction_wheel_ = new s2e::components::ReactionWheel(s2e::components::InitReactionWheel(clock_generator, 1, component_ini_file_name, compo_step_sec));
}

UserComponents::~UserComponents() {
  // OBC must be deleted the last since it has com ports
  delete gyro_sensor_;
  delete reaction_wheel_;
  delete obc_;
}

s2e::math::Vector<3> UserComponents::GenerateForce_b_N() {
  // There is no orbit control component, so it remains 0
  s2e::math::Vector<3> force_b_N(0.0);
  return force_b_N;
}

s2e::math::Vector<3> UserComponents::GenerateTorque_b_Nm() {
  // No attitude control component
  s2e::math::Vector<3> torque_b_Nm(0.0);
  torque_b_Nm = reaction_wheel_->GetOutputTorque_b_Nm();
  return torque_b_Nm;
}

void UserComponents::LogSetup(s2e::logger::Logger &logger) {
  // Users can set log output when they need component log
  UNUSED(logger);
}
