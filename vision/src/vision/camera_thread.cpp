#include <vision/camera_thread.hpp>

namespace vision {

//--------------------------------------------------------------------------------------------------
// Constructor and destructor
//--------------------------------------------------------------------------------------------------

CameraThread::CameraThread(
  Eigen::Affine3d const& T_WM,
  Eigen::Affine3d const& T_RC,
  Eigen::Matrix<double,6,6> const& cov_T_RC,
  Camera::UniquePtr camera_ptr)
: T_WM_       (T_WM),
  T_RC_       (T_RC),
  cov_T_RC_   (cov_T_RC),
  camera_ptr_ (std::move(camera_ptr))
{
  this->pose_filter_ptr_.reset(new CameraPoseFilter(T_WM, T_RC, cov_T_RC));
  this->thread_ptr_.reset(new std::thread([=](){this->runThread();}));
}

//--------------------------------------------------------------------------------------------------

CameraThread::~CameraThread()
{
  this->thread_ptr_->join();
  std::cout << "Destruction" << std::endl;
}

//--------------------------------------------------------------------------------------------------
// Methods
//--------------------------------------------------------------------------------------------------

void CameraThread::runThread()
{
  // Initialization : scan the board looking for the central marker to initialize
  bool initialized = false;
  while(!initialized)
  {
    // Take picture
    // TODO: incrementPosition();
    cv::Mat image;
    // TODO: takePicture();

    // Detect the markers
    DetectedMarkerList detected_markers;
    this->camera_ptr_->detectMarkers(image, &detected_markers);

    // Check if the central marker (n°42) is detected
    DetectedMarkerList::const_iterator it = detected_markers.cbegin();
    for(it; it != detected_markers.cend(); ++it)
      if(it->marker_id == 42) break;

    // If so => initialize the camera pose filter and go to the next step
    if(it != detected_markers.cend())
    {
      Eigen::Affine3d const T_CM = it->T_CM;
      Eigen::Matrix<double,6,6> const cov_T_CM = it->cov_T_CM;
      this->pose_filter_ptr_->setStateAndCovariance(
        CameraPoseFilter::InitType::T_CM, T_CM, cov_T_CM);
      break;
    }
  }
  
  // Routine : scan the board and detect all the markers
  while(true)
  {
    // Check if a specific request has been received
    // If so, realize it (don't forget to propagate the filter while doing it).
    
    // Rotate the camera
    // Propagate the filter
    // Take a picture
    // Detect all the markers
    // Check if the central marker is detected => if so: update the filter
    // Update the pose estimate of all other markers
  }
  std::cout << "Camera thread" << std::endl;
}

//--------------------------------------------------------------------------------------------------

} // namespace vision
