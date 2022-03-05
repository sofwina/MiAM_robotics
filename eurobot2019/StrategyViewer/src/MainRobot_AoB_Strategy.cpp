/// \author Matthieu Vigne
/// \copyright GNU GPLv3
#include "ViewerRobot.h"
#include <miam_utils/trajectory/Utilities.h>
#include <miam_utils/trajectory/ArcCircle.h>

using namespace miam::trajectory;

// Define robot constants for trajectory generation.
namespace robotdimensions
{
    double const wheelSpacing = 106.0; ///< Wheel spacing from robot center, in mm.
    double const maxWheelSpeedTrajectory = 400; ///< Maximum wheel speed, in mm/s.
    double const maxWheelAccelerationTrajectory = 400; ///< Maximum wheel acceleration, in mm/s^2.
}

// Robot dimension.
double const CHASSIS_FRONT = 150.0;
double const CHASSIS_BACK = 150.0;
double const CHASSIS_WIDTH = 150.0;


void mainRobotAgeOfBotsStrategy(ViewerRobot &robot)
{
    robot.trajectory_.clear();
    robot.clearScore();
    std::cout << "Computing main robot strategy, obstacle at " << robot.obstacleX_ << " " << robot.obstacleY_ << std::endl;

    // Update config.
    miam::trajectory::setTrajectoryGenerationConfig(robotdimensions::maxWheelSpeedTrajectory,
                                                    robotdimensions::maxWheelAccelerationTrajectory,
                                                    robotdimensions::wheelSpacing);

    // Create required variables.
    RobotPosition targetPosition;
    TrajectoryVector traj;
    RobotPosition endPosition;
    std::vector<RobotPosition> positions;
    bool wasMoveSuccessful = true;
    robot.updateScore(2); 

    // Set initial position
    targetPosition.x = CHASSIS_BACK;
    targetPosition.y = 1200;
    targetPosition.theta = 0;
    robot.resetPosition(targetPosition, true, true, true);

    //**********************************************************
    // Go get the statue 
    //**********************************************************
    targetPosition = robot.getCurrentPosition();
    positions.push_back(targetPosition);
    targetPosition.x = 450;
    positions.push_back(targetPosition);
    targetPosition.y = 450;
    positions.push_back(targetPosition);
    // Move at 45degree angle toward the statue
    targetPosition.x += 80;
    targetPosition.y += 80;
    positions.push_back(targetPosition);
    traj = miam::trajectory::computeTrajectoryRoundedCorner(positions, 200.0, 0.2);
    robot.setTrajectoryToFollow(traj);
    wasMoveSuccessful = robot.waitForTrajectoryFinished();
    targetPosition = robot.getCurrentPosition();
    //Go back
    traj = miam::trajectory::computeTrajectoryStraightLine(targetPosition,-180.0);
    robot.setTrajectoryToFollow(traj);
    robot.updateScore(15);
    positions.clear();
    targetPosition = robot.getCurrentPosition();
    positions.push_back(targetPosition);
    //Rotate
    targetPosition.x = 500;
    targetPosition.y = 500;
    positions.push_back(targetPosition);
    targetPosition.x = 450;
    targetPosition.y = 450;
    positions.push_back(targetPosition);
    traj = miam::trajectory::computeTrajectoryRoundedCorner(positions, 200.0, 0.2);
    robot.setTrajectoryToFollow(traj);
    robot.updateScore(15);
    robot.updateScore(15); 
    
    //**********************************************************
    // Go back to the side distributor
    //**********************************************************
    //targetPosition = robot.getCurrentPosition();
    //Go back
    //traj = miam::trajectory::computeTrajectoryStraightLine(targetPosition,-250.0);
    //robot.setTrajectoryToFollow(traj);
    //wasMoveSuccessful = robot.waitForTrajectoryFinished();

    //**********************************************************
    // Round to the side distributor
    //**********************************************************
    positions.clear();
    targetPosition = robot.getCurrentPosition();
    positions.push_back(targetPosition);
    //Rotate
    targetPosition.x = 102+40+CHASSIS_WIDTH;
    targetPosition.y = 500;
    positions.push_back(targetPosition);
    targetPosition.y = 800;
    positions.push_back(targetPosition);
    traj = miam::trajectory::computeTrajectoryRoundedCorner(positions, 200.0, 0.5);
    robot.setTrajectoryToFollow(traj);
    wasMoveSuccessful = robot.waitForTrajectoryFinished();
    robot.updateScore(3); 
    

    //**********************************************************
    // Go to the display
    //**********************************************************
    positions.clear();
    targetPosition = robot.getCurrentPosition();
    endPosition.x = targetPosition.x ;
    endPosition.y = 2000-40-CHASSIS_FRONT;
    positions.push_back(targetPosition);
    traj = miam::trajectory::computeTrajectoryStraightLineToPoint(targetPosition,endPosition,0.0,false);
    robot.setTrajectoryToFollow(traj);
    wasMoveSuccessful = robot.waitForTrajectoryFinished();
    robot.updateScore(15); 

    //**********************************************************
    // Go to the side distributor
    //**********************************************************
    positions.clear();
    targetPosition = robot.getCurrentPosition();
    positions.push_back(targetPosition);
    targetPosition.y = 1700 ;
    positions.push_back(targetPosition);
    targetPosition.x = CHASSIS_FRONT + 40 ;
    positions.push_back(targetPosition);
    traj = miam::trajectory::computeTrajectoryRoundedCorner(positions, 200.0, 0.5);
    robot.setTrajectoryToFollow(traj);
    wasMoveSuccessful = robot.waitForTrajectoryFinished();
    robot.updateScore(1); 

    //**********************************************************
    // Go back to the gallery & side distributor
    //**********************************************************
    
    targetPosition = robot.getCurrentPosition();
    //Go back
    traj = miam::trajectory::computeTrajectoryStraightLine(targetPosition,-1100.0);
    robot.setTrajectoryToFollow(traj);
    wasMoveSuccessful = robot.waitForTrajectoryFinished();
    robot.updateScore(3); 

    //**********************************************************
    // Rotate to the gallery
    //**********************************************************
    positions.clear();
    targetPosition = robot.getCurrentPosition();
    positions.push_back(targetPosition);
    targetPosition.x = 930;
    positions.push_back(targetPosition);
    targetPosition.y = 2000- CHASSIS_FRONT - 100 - 40 ;
    positions.push_back(targetPosition);
    traj = miam::trajectory::computeTrajectoryRoundedCorner(positions, 200.0, 0.5);
    robot.setTrajectoryToFollow(traj);
    wasMoveSuccessful = robot.waitForTrajectoryFinished();
    robot.updateScore(8); 

    //**********************************************************
    // Go to the side distributor
    //**********************************************************
    //positions.clear();
    //targetPosition = robot.getCurrentPosition();
    //positions.push_back(targetPosition);
    //targetPosition.y = 2000- CHASSIS_FRONT - 100 - 40 ;
    //positions.push_back(targetPosition);
    //targetPosition.x = 1350;
    //positions.push_back(targetPosition);
    //traj = miam::trajectory::computeTrajectoryRoundedCorner(positions, 200.0, 0.5);
    //robot.setTrajectoryToFollow(traj);
    //wasMoveSuccessful = robot.waitForTrajectoryFinished();
    //robot.updateScore(15); 
    
     //**********************************************************
    // Go to the central zone
    //**********************************************************
    positions.clear();
    targetPosition = robot.getCurrentPosition();
    positions.push_back(targetPosition);
    targetPosition.x = 500;
    positions.push_back(targetPosition);
    targetPosition.y = 1325 ;
    positions.push_back(targetPosition);
     targetPosition.x = 675;
    positions.push_back(targetPosition);
    traj = miam::trajectory::computeTrajectoryRoundedCorner(positions, 200.0, 0.5);
    robot.setTrajectoryToFollow(traj);
    wasMoveSuccessful = robot.waitForTrajectoryFinished();
    robot.updateScore(15); 
    
     //**********************************************************
    // Rotate to the gallery
    //**********************************************************
    positions.clear();
    targetPosition = robot.getCurrentPosition();
    positions.push_back(targetPosition);
    targetPosition.y = 2000- CHASSIS_FRONT - 100 - 40 ;
    positions.push_back(targetPosition);
    traj = miam::trajectory::computeTrajectoryRoundedCorner(positions, 200.0, 0.5);
    robot.setTrajectoryToFollow(traj);
    wasMoveSuccessful = robot.waitForTrajectoryFinished();
    robot.updateScore(9); 
    
         //**********************************************************
    // Rotate to the zone de fouille
    //**********************************************************
    positions.clear();
    targetPosition = robot.getCurrentPosition();
    positions.push_back(targetPosition);
    targetPosition.x = 1200;
    targetPosition.y = 800 ;
    positions.push_back(targetPosition);
    targetPosition.x = 800;
    targetPosition.y = 450 ;
    positions.push_back(targetPosition);
    targetPosition.x = 510 ;
    targetPosition.y = 320 ;
    positions.push_back(targetPosition);
    traj = miam::trajectory::computeTrajectoryRoundedCorner(positions, 200.0, 0.5);
    robot.setTrajectoryToFollow(traj);
    wasMoveSuccessful = robot.waitForTrajectoryFinished();
    robot.updateScore(15); 
    
    //**********************************************************
    // Rotate to measure
    //**********************************************************
    positions.clear();
    targetPosition = robot.getCurrentPosition();
    positions.push_back(targetPosition);
    targetPosition.x = 450;
    targetPosition.y = CHASSIS_WIDTH + 40 ;
    positions.push_back(targetPosition);
    targetPosition.x = 1350;
    positions.push_back(targetPosition);
    traj = miam::trajectory::computeTrajectoryRoundedCorner(positions, 200.0, 0.5);
    robot.setTrajectoryToFollow(traj);
    wasMoveSuccessful = robot.waitForTrajectoryFinished();
    robot.updateScore(40); 
    
    //**********************************************************
    // Rotate to come back to the campment
    //**********************************************************
    positions.clear();
    targetPosition = robot.getCurrentPosition();
    positions.push_back(targetPosition);
    targetPosition.x = 900;
    targetPosition.y = 600;
    positions.push_back(targetPosition);
    targetPosition.x = 975;
    positions.push_back(targetPosition);
    traj = miam::trajectory::computeTrajectoryRoundedCorner(positions, 200.0, 0.5);
    robot.setTrajectoryToFollow(traj);
    wasMoveSuccessful = robot.waitForTrajectoryFinished();
    robot.updateScore(20);

}
