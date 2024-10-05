/**
 * @file user_satellite.hpp
 * @brief An example of user side spacecraft class
 */

#ifndef S2E_SIMULATION_SPACECRAFT_USER_SATELLITE_HPP_
#define S2E_SIMULATION_SPACECRAFT_USER_SATELLITE_HPP_

#include <simulation/spacecraft/spacecraft.hpp>

#include "user_components.hpp"

/**
 * @class UserSatellite
 * @brief An example of user side spacecraft class
 */
class UserSatellite : public s2e::spacecraft::Spacecraft {
 public:
  /**
   * @fn UserSatellite
   * @brief Constructor
   */
  UserSatellite(const s2e::simulation::SimulationConfiguration *simulation_configuration,
                const s2e::environment::GlobalEnvironment *global_environment, const unsigned int spacecraft_id);
  /**
   * @fn Update
   * @brief Override Spacecraft::Update
   */
  virtual void Update(const s2e::environment::SimulationTime *simulation_time) override;

 private:
  /**
   * @fn ControlAlgorithm
   * @brief Control algorithm
   */
  void ControlAlgorithm(void);
};

#endif  // S2E_SIMULATION_SPACECRAFT_USER_SATELLITE_HPP_
