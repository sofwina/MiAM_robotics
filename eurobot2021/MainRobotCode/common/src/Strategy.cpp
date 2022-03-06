/// \author MiAM Robotique, Matthieu Vigne
/// \copyright GNU GPLv3
#include <unistd.h>
#include <math.h>

#include <miam_utils/trajectory/ArcCircle.h>
#include <miam_utils/trajectory/StraightLine.h>
#include <miam_utils/trajectory/PointTurn.h>
#include <miam_utils/trajectory/Utilities.h>
#include "Parameters.h"
#include "Strategy.h"

// Robot dimension.
double const CHASSIS_FRONT = 115.0;
double const CHASSIS_BACK = 121.0;
double const CHASSIS_WIDTH = 150.0;
double const SUCTION_CENTER = 180.0;

using namespace miam::trajectory;
using miam::RobotPosition;

void matchStrategy(AbstractRobot *robot, ServoHandler *servo)
{
    std::cout << "Strategy thread started." << std::endl;

    //while(true) {

        /* servo->ouvrirlesbrasdebugbas();
        std::cout << "bas" << std::endl;
        usleep(2000000);

        servo->ouvrirlesbrasdebugmilieu();
        std::cout << "milieu" << std::endl;
        usleep(2000000);

        servo->ouvrirlesbrasdebughaut();
        std::cout << "haut" << std::endl;
        usleep(2000000); */

        /* servo->figurineArmMiddle();
        std::cout << "milieu" << std::endl;
        usleep(2000000); */
/*         usleep(5000000);


        servo->figurineArmHigh();
        std::cout << "haut" << std::endl;
        usleep(2000000);

        servo->figurineArmLow();
        std::cout << "bas" << std::endl;
        usleep(2000000); */


    //}
    

    //while(true) {
        //std::cout << "waiting" << std::endl;
        //usleep(100000);
    //}

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
    robot->updateScore(2); 

    // Set initial position
    targetPosition.x = CHASSIS_BACK;
    targetPosition.y = 1200;
    targetPosition.theta = 0;
    robot->resetPosition(targetPosition, true, true, true);

    //**********************************************************
    // Go get the statue 
    //**********************************************************
    targetPosition = robot->getCurrentPosition();
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
    robot->setTrajectoryToFollow(traj);
    wasMoveSuccessful = robot->waitForTrajectoryFinished();
    targetPosition = robot->getCurrentPosition();
    //Go back
    traj = miam::trajectory::computeTrajectoryStraightLine(targetPosition,-131.0);
    robot->setTrajectoryToFollow(traj);
    robot->updateScore(15);
    positions.clear();
    targetPosition = robot->getCurrentPosition();
    positions.push_back(targetPosition);
    //Rotate
    targetPosition.x = 500;
    targetPosition.y = 500;
    positions.push_back(targetPosition);
    targetPosition.x = 450;
    targetPosition.y = 450;
    positions.push_back(targetPosition);
    traj = miam::trajectory::computeTrajectoryRoundedCorner(positions, 200.0, 0.2);
    robot->setTrajectoryToFollow(traj);
    robot->updateScore(15);
    robot->updateScore(15); 
    
    //**********************************************************
    // Go back to the side distributor
    //**********************************************************
    targetPosition = robot->getCurrentPosition();


    std::cout << targetPosition << std::endl;

    // Go back
    traj = miam::trajectory::computeTrajectoryStraightLine(targetPosition,-250.0);
    robot->setTrajectoryToFollow(traj);
    wasMoveSuccessful = robot->waitForTrajectoryFinished();

    //**********************************************************
    // Round to the side distributor
    //**********************************************************
    positions.clear();
    targetPosition = robot->getCurrentPosition();
    positions.push_back(targetPosition);
    //Rotate
    targetPosition.x = 102+40+CHASSIS_WIDTH+50;
    targetPosition.y = 500;
    positions.push_back(targetPosition);
    targetPosition.y = 800;
    positions.push_back(targetPosition);
    traj = miam::trajectory::computeTrajectoryRoundedCorner(positions, 150.0, 0.5);
    robot->setTrajectoryToFollow(traj);
    wasMoveSuccessful = robot->waitForTrajectoryFinished();
    robot->updateScore(3); 
    

    //**********************************************************
    // Go to the display
    //**********************************************************


    // go forward
    targetPosition = robot->getCurrentPosition();
    traj = miam::trajectory::computeTrajectoryStraightLine(targetPosition, 500.0);
    robot->setTrajectoryToFollow(traj);
    wasMoveSuccessful = robot->waitForTrajectoryFinished();

    // then a little to the left
    targetPosition = robot->getCurrentPosition();
    endPosition = targetPosition;
    endPosition.x = 100 + CHASSIS_WIDTH;
    endPosition.y += 100;
    traj = miam::trajectory::computeTrajectoryStraightLineToPoint(targetPosition,endPosition,0.0,false);
    robot->setTrajectoryToFollow(traj);
    wasMoveSuccessful = robot->waitForTrajectoryFinished();


    // finally go straight
    positions.clear();
    targetPosition = robot->getCurrentPosition();
    endPosition.x = targetPosition.x ;
    endPosition.y = 2000-40-CHASSIS_FRONT - 40;
    positions.push_back(targetPosition);
    traj = miam::trajectory::computeTrajectoryStraightLineToPoint(targetPosition,endPosition,0.0,false);
    robot->setTrajectoryToFollow(traj);
    wasMoveSuccessful = robot->waitForTrajectoryFinished();
    robot->updateScore(15); 

    // go back a little
    targetPosition = robot->getCurrentPosition();
    traj = miam::trajectory::computeTrajectoryStraightLine(targetPosition,-100.0);
    robot->setTrajectoryToFollow(traj);
    wasMoveSuccessful = robot->waitForTrajectoryFinished();

    //**********************************************************
    // Go to the side distributor
    //**********************************************************
    positions.clear();
    targetPosition = robot->getCurrentPosition();
    positions.push_back(targetPosition);
    targetPosition.y = 1700 ;
    positions.push_back(targetPosition);
    targetPosition.x = CHASSIS_FRONT + 40 + 20 ;
    positions.push_back(targetPosition);
    traj = miam::trajectory::computeTrajectoryRoundedCorner(positions, 200.0, 0.5);
    robot->setTrajectoryToFollow(traj);
    wasMoveSuccessful = robot->waitForTrajectoryFinished();
    robot->updateScore(1); 

    //**********************************************************
    // Go back to the gallery & side distributor
    //**********************************************************
    
    //Go back
    targetPosition = robot->getCurrentPosition();
    traj = miam::trajectory::computeTrajectoryStraightLine(targetPosition,-1100.0);
    robot->setTrajectoryToFollow(traj);
    wasMoveSuccessful = robot->waitForTrajectoryFinished();
    robot->updateScore(3); 

    //**********************************************************
    // Rotate to the gallery
    //**********************************************************

    double y_front_of_the_gallery = 2000- CHASSIS_FRONT - 100 - 60;

    positions.clear();
    targetPosition = robot->getCurrentPosition();
    positions.push_back(targetPosition);
    targetPosition.x = 930;
    targetPosition.y -= 150;
    positions.push_back(targetPosition);
    targetPosition.y = y_front_of_the_gallery ;
    positions.push_back(targetPosition);
    traj = miam::trajectory::computeTrajectoryRoundedCorner(positions, 200.0, 0.5);
    robot->setTrajectoryToFollow(traj);
    wasMoveSuccessful = robot->waitForTrajectoryFinished();
    robot->updateScore(8); 

    // go back a little
    targetPosition = robot->getCurrentPosition();
    traj = miam::trajectory::computeTrajectoryStraightLine(targetPosition,-100.0);
    robot->setTrajectoryToFollow(traj);
    wasMoveSuccessful = robot->waitForTrajectoryFinished();

    //**********************************************************
    // Go to the side distributor
    //**********************************************************
    //positions.clear();
    //targetPosition = robot->getCurrentPosition();
    //positions.push_back(targetPosition);
    //targetPosition.y = 2000- CHASSIS_FRONT - 100 - 40 ;
    //positions.push_back(targetPosition);
    //targetPosition.x = 1350;
    //positions.push_back(targetPosition);
    //traj = miam::trajectory::computeTrajectoryRoundedCorner(positions, 200.0, 0.5);
    //robot->setTrajectoryToFollow(traj);
    //wasMoveSuccessful = robot->waitForTrajectoryFinished();
    //robot->updateScore(15); 
    
     //**********************************************************
    // Go to the central zone
    //**********************************************************
    positions.clear();
    targetPosition = robot->getCurrentPosition();
    positions.push_back(targetPosition);
    targetPosition.x = 500;
    positions.push_back(targetPosition);
    targetPosition.y = 1325 ;
    positions.push_back(targetPosition);
     targetPosition.x = 675;
    positions.push_back(targetPosition);
    traj = miam::trajectory::computeTrajectoryRoundedCorner(positions, 200.0, 0.5);
    robot->setTrajectoryToFollow(traj);
    wasMoveSuccessful = robot->waitForTrajectoryFinished();
    robot->updateScore(15); 
    
     //**********************************************************
    // Rotate to the gallery
    //**********************************************************
    positions.clear();
    targetPosition = robot->getCurrentPosition();
    positions.push_back(targetPosition);
    targetPosition.y = y_front_of_the_gallery ;
    positions.push_back(targetPosition);
    traj = miam::trajectory::computeTrajectoryRoundedCorner(positions, 200.0, 0.5);
    robot->setTrajectoryToFollow(traj);
    wasMoveSuccessful = robot->waitForTrajectoryFinished();
    robot->updateScore(9); 

    // go back a little
    targetPosition = robot->getCurrentPosition();
    traj = miam::trajectory::computeTrajectoryStraightLine(targetPosition,-100.0);
    robot->setTrajectoryToFollow(traj);
    wasMoveSuccessful = robot->waitForTrajectoryFinished();
    
    //**********************************************************
    // Rotate to the zone de fouille
    //**********************************************************
    positions.clear();
    targetPosition = robot->getCurrentPosition();
    positions.push_back(targetPosition);
    targetPosition.x = 1200;
    targetPosition.y = 800 ;
    positions.push_back(targetPosition);
    targetPosition.x = 800;
    targetPosition.y = 450 ;
    positions.push_back(targetPosition);
    targetPosition.x = 450 ;
    targetPosition.y = 220 ;
    positions.push_back(targetPosition);
    traj = miam::trajectory::computeTrajectoryRoundedCorner(positions, 200.0, 0.5);
    robot->setTrajectoryToFollow(traj);
    wasMoveSuccessful = robot->waitForTrajectoryFinished();
    robot->updateScore(15); 


    // go back a big little
    targetPosition = robot->getCurrentPosition();
    traj = miam::trajectory::computeTrajectoryStraightLine(targetPosition,-150.0);
    robot->setTrajectoryToFollow(traj);
    wasMoveSuccessful = robot->waitForTrajectoryFinished();
    
    //**********************************************************
    // Rotate to measure
    //**********************************************************
    positions.clear();
    targetPosition = robot->getCurrentPosition();
    positions.push_back(targetPosition);
    targetPosition.x = 450;
    targetPosition.y = CHASSIS_WIDTH + 40 +20;
    positions.push_back(targetPosition);
    targetPosition.x = 1350;
    positions.push_back(targetPosition);
    traj = miam::trajectory::computeTrajectoryRoundedCorner(positions, 200.0, 0.5);
    robot->setTrajectoryToFollow(traj);
    wasMoveSuccessful = robot->waitForTrajectoryFinished();
    robot->updateScore(40); 
    
    //**********************************************************
    // Rotate to come back to the campment
    //**********************************************************
    positions.clear();
    targetPosition = robot->getCurrentPosition();
    positions.push_back(targetPosition);
    targetPosition.x = 900;
    targetPosition.y = 600;
    positions.push_back(targetPosition);
    targetPosition.x = 975;
    positions.push_back(targetPosition);
    traj = miam::trajectory::computeTrajectoryRoundedCorner(positions, 200.0, 0.5);
    robot->setTrajectoryToFollow(traj);
    wasMoveSuccessful = robot->waitForTrajectoryFinished();
    robot->updateScore(20);

    std::cout << "Strategy thread ended" << robot->getMatchTime() << std::endl;
}
