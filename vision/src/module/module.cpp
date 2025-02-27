#include <memory>

#include <yaml-cpp/yaml.h>

#include <common/yaml_serialization.hpp>
#include <module/module.hpp>
#include <network/socket_exception.hpp>
#include <vision/distortion_null.hpp>
#include <vision/distortion_radtan.hpp>

namespace module {

//--------------------------------------------------------------------------------------------------
// Constructor and destructor
//--------------------------------------------------------------------------------------------------

Module::Module(std::string const& filename)
{
  // Load the configuration file
  YAML::Node const params = YAML::LoadFile(filename);
  
  // Get the board dimensions
  YAML::Node const& board = params["board"];
  assert(board.IsMap());
  this->board_.width = board["width"].as<double>();
  this->board_.height = board["height"].as<double>();
  
  // Launch the camera thread
  YAML::Node const camera_node = params["camera"];
  std::string const camera_name = "camera";
  vision::Camera::UniquePtr camera_ptr =
    vision::Camera::buildCameraFromYaml(camera_name, camera_node);
  Eigen::Affine3d const T_WM =
    common::yaml_serialization::deserializePose(params["T_WM"]);
  Eigen::Affine3d const T_RC =
    common::yaml_serialization::deserializePose(params["T_RC"]);
  Eigen::Matrix<double,6,6> const cov_T_RC =
    common::yaml_serialization::deserializePoseCovariance(params["cov_T_RC"]);
  this->camera_thread_ptr_.reset(new vision::CameraThread(T_WM, T_RC, cov_T_RC,
    std::move(camera_ptr)));

  // Launch the server thread
  int const port = 30000;
  try {
      this->server_thread_ptr_.reset(new network::ServerThread(port));
  } catch(network::SocketException const& e) {
      std::cout << e.description() << std::endl;
  }
}

//--------------------------------------------------------------------------------------------------

Module::~Module()
{}

//--------------------------------------------------------------------------------------------------

} // namespace module
