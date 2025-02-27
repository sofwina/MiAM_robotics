#ifndef VISION_DISTORTION_RADTAN_HPP
#define VISION_DISTORTION_RADTAN_HPP

#include <vision/distortion_model.hpp>

namespace vision {

//--------------------------------------------------------------------------------------------------
// Class declaration
//--------------------------------------------------------------------------------------------------

class DistortionRadTan : public DistortionModel {

public:

  DISALLOW_EVIL_CONSTRUCTORS(DistortionRadTan);
  DistortionRadTan(Eigen::VectorXd const& distortion_coeffs);

public:

  inline int getNumCoeffs() const;
  void getDistortionCoeffs(cv::Mat* coeffs) const;
  void distort(Eigen::Vector2d* point, Eigen::Matrix2d* jacobian) const;

}; // class DistortionRadTan

//--------------------------------------------------------------------------------------------------
// Inline functions
//--------------------------------------------------------------------------------------------------

int DistortionRadTan::getNumCoeffs() const
{
  return 5;
}

//--------------------------------------------------------------------------------------------------

} // namespace vision

#endif // VISION_DISTORTION_RADTAN_HPP
