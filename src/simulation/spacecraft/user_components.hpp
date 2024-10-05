/**
 * @file sample_components.hpp
 * @brief An example of user side components management installed on a spacecraft
 */

#ifndef S2E_SIMULATION_SPACECRAFT_USER_COMPONENTS_HPP_
#define S2E_SIMULATION_SPACECRAFT_USER_COMPONENTS_HPP_

#include <dynamics/dynamics.hpp>
#include <environment/global/global_environment.hpp>
#include <environment/local/local_environment.hpp>
#include <math_physics/math/vector.hpp>
#include <simulation/spacecraft/installed_components.hpp>

// include for components
#include <components/real/cdh/on_board_computer.hpp>

#include "../../components/clock_sensor.hpp"

class UserComponents : public s2e::spacecraft::InstalledComponents {
 public:
  UserComponents(const s2e::dynamics::Dynamics *dynamics, s2e::spacecraft::Structure *structure,
                 const s2e::environment::LocalEnvironment *local_environment, const s2e::environment::GlobalEnvironment *global_environment,
                 const s2e::simulation::SimulationConfiguration *configuration, s2e::environment::ClockGenerator *clock_generator,
                 const unsigned int spacecraft_id);
  ~UserComponents();
  s2e::math::Vector<3> GenerateForce_b_N();
  s2e::math::Vector<3> GenerateTorque_b_Nm();
  void LogSetup(s2e::logger::Logger &logger);

 private:
  // Components
  s2e::components::OnBoardComputer *obc_;  //!< Onboard Computer
  ClockSensor *clock_sensor_;              //!< Clock sensor

  // States
  const s2e::simulation::SimulationConfiguration *configuration_;  //!< Simulation settings
  const s2e::dynamics::Dynamics *dynamics_;                        //!< Dynamics information of the spacecraft
  s2e::spacecraft::Structure *structure_;                          //!< Structure information of the spacecraft
  const s2e::environment::LocalEnvironment *local_environment_;    //!< Local environment information around the spacecraft
  const s2e::environment::GlobalEnvironment *global_environment_;  //!< Global environment information
};

#endif  // S2E_SIMULATION_SPACECRAFT_USER_COMPONENTS_HPP_
