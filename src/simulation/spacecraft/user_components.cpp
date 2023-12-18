/**
 * @file user_components.cpp
 * @brief An example of user side components management installed on a spacecraft
 */

#include "user_components.hpp"

#include <library/initialize/initialize_file_access.hpp>
#include <library/utilities/macros.hpp>

#ifdef USE_C2A
#include "src_user/Settings/port_config.h"
#endif

UserComponents::UserComponents(const Dynamics *dynamics, Structure *structure, const LocalEnvironment *local_environment,
                               const GlobalEnvironment *global_environment, const SimulationConfiguration *configuration,
                               ClockGenerator *clock_generator, const unsigned int spacecraft_id)
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

  // Component instances
#ifdef USE_C2A
  obc_ = new ObcWithC2a(clock_generator, 100);
  exp_serial_communication_ = new ExampleSerialCommunicationWithObc(clock_generator, 1, 1, obc_);

  obc_->ConnectComPort(PORT_CH_RS422_MOBC_EXT, 1024, 1024);  // UART通信用にとりあえず繋いでおく
#endif
}

UserComponents::~UserComponents() {
  delete exp_serial_communication_;
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

void UserComponents::LogSetup(Logger &logger) {
  // Users can set log output when they need component log
  UNUSED(logger);
}
