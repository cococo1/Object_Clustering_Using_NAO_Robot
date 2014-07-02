#include <iostream>
#include <exception>
#include "NAO.h"
#ifdef __linux__
    #include <alerror/alerror.h>
    #include <alproxies/altexttospeechproxy.h>
    #include <alproxies/almotionproxy.h>
    #include <alproxies/alrobotpostureproxy.h>
    #include <alproxies/alnavigationproxy.h>
#else
    #include <unistd.h>
#endif
//#include "opencv2/opencv.hpp"


// We have objects;
// Each of these objects have a center;
// This center is given in image coordinates;
// We need to transform it into ROBOT_FRAME's coordinates;
//1. We need to select the closest object to robot;
//2. We compute the angle towards robot;
//3. We compute the distance between object and robot;
//4. Robot turns and walks to the object;
// We repeat steps 1-4;

// How to compute the angle?
// What info do we have?
// - robot's position in ROBOT_FRAME;
// - object's position in ROBOT_FRAME;
// - robot's current angle of view;




void testNAO2(const std::string& robotIp);
void say(std::string robotIp, std::string text);
void lookDown(std::string robotIp);
void cluster(std::string robotIp);
void sitDown(std::string robotIp);


int main(int argc, char* argv[])
{
  if(argc != 2)
  {
    std::cerr << "Wrong number of arguments!" << std::endl;
    std::cerr << "Usage: naoClustering NAO_IP" << std::endl;
    exit(EXIT_FAILURE);
  }
    try
    {
        std::string robotIp = argv[1];
        
        AbstractFactory *factory = new AbstractFactory();
        NAO fitik(robotIp, factory);

        cv::Mat mat;
        Image image(mat);
        Object object(image);
////        fitik.getLocomotion().pickObject(object);

//        fitik.getLocomotion().setStiffnessOnAndStand();
//        fitik.getLocomotion().pickObject(object);
//        fitik.getLocomotion().giveObjectAndSayResult(object);

//        fitik.getHead().getSpaceOrientation().getBottomCameraPosition();
//        fitik.getLocomotion().move(0.3,0.3,0);
//        fitik.getLocomotion().setStiffnessOnAndStand();
//        fitik.getHead().getSpaceOrientation().getBottomCameraPosition();

//        fitik.getLocomotion().setStiffnessOnAndStand();
//        fitik.getHead().getSpaceOrientation().initializePosition();
//        testNAO2(robotIp);
//        std::cout << "asas" <<
//        fitik.getHead().getSpaceOrientation().getNaoPositionInRobotFrame()
//                  << std::endl;


//        fitik.getLocomotion().setStiffnessOnAndStand();
//        sleep(15);
//        fitik.getLocomotion().move(0.2, 0, 0);
//        fitik.getLocomotion().move(0, 0.2, 0);
//        fitik.getLocomotion().move(0, 0, 1);

        fitik.startInteraction();

//        lookDown(robotIp);
//        cluster(robotIp);
//    //    testNAO2(robotIp);
        sleep(1);
        sitDown(robotIp);

}
catch (std::exception& e)
{
    std::cerr << "Exceptionale: " << e.what() << std::endl;
}
    exit(EXIT_SUCCESS);
}

void testNAO2(const std::string& robotIp)
{
#ifdef __linux__
    try
    {
    AL::ALNavigationProxy navigation(robotIp);
    AL::ALMotionProxy motion(robotIp);
    bool useSensors = true;
    std::vector<float> currentWorldPosition =
        motion.getRobotPosition(useSensors);
    std::cout << currentWorldPosition << std::endl;


    motion.moveInit();

    navigation.moveTo(0.5, 0, 0 ); // 1 meter on x
    motion.waitUntilMoveIsFinished();
//    currentWorldPosition = motion.getRobotPosition(useSensors);
//    std::cout << currentWorldPosition << std::endl;

//    sleep(15);

    navigation.moveTo(0,  -.2, 0); // 1 meter on y
    motion.waitUntilMoveIsFinished();
//    currentWorldPosition = motion.getRobotPosition(useSensors);
//    std::cout << currentWorldPosition << std::endl;

//    sleep(7);

    navigation.moveTo(0, 0, M_PI/4); //rotate to 180 degrees
    motion.waitUntilMoveIsFinished();
//    currentWorldPosition = motion.getRobotPosition(useSensors);
//    std::cout << currentWorldPosition << std::endl;

//    sleep(7);
    }
    catch (const AL::ALError& e)
    {
      std::cerr << "Caught exception: " << e.what() << std::endl;
      exit(EXIT_FAILURE);
    }


#endif
}

void cluster(std::string robotIp)
{

    AbstractFactory *factory = new AbstractFactory();
    NAO fitik(robotIp, factory);
//    fitik.getHead().initializePosition();
//    fitik.getHead().getNaoPositionOnImage();
//    fitik.getHead().getNaoPositionOnImage();
//    fitik.getHead().getNaoPositionOnImage();

//    cv::Point2d nao =
//    fitik.getHead().computePointInRobotFrameGivenPointOnImage(
//                                  fitik.getHead().getNaoPositionOnImage());
//    nao = fitik.getHead().computePointOnImageGivenPointInRobotFrame(nao);
//    std::cout << "Nao: " << nao << std::endl;
//    fitik.getHead().computePointInRobotFrameGivenPointOnImage(nao);
        fitik.startInteraction();

//    std::vector<Object> objects = fitik.detectObjects();
//    fitik.clusterObjects(objects);
//    fitik.moveObjects(objects);
}

void say(std::string robotIp, std::string text)
{
#ifdef __linux__
    try
    {
        AL::ALTextToSpeechProxy tts(robotIp);
        /** Call the say method */
        //Change the language !!!
        tts.say(text);
    }
    catch (const AL::ALError& e)
    {
      std::cerr << "Caught exception: " << e.what() << std::endl;
      exit(EXIT_FAILURE);
    }
#else
    std::cout << "say not on linux:" << text << std::endl;
#endif
}

void sitDown(std::string robotIp)
{
#ifdef __linux__
    /** The name of the joint to be moved. */
//    const AL::ALValue jointName = AL::ALValue::array("HeadPitch", "HeadYaw");
    try {

        AL::ALRobotPostureProxy robotPosture(robotIp);
        float maxSpeedFraction = 0.5f; //[0;1]
        bool postureReached = robotPosture.goToPosture("Sit", maxSpeedFraction);
        if (! postureReached) say(robotIp, "Could not sit down.");
    }
    catch (const AL::ALError& e) {
      std::cerr << "Caught exception: " << e.what() << std::endl;
      exit(EXIT_FAILURE);
    }
#else
    std::cout << "lookDown not on linux" << std::endl;
#endif
}

void lookDown(std::string robotIp)
{
#ifdef __linux__
    /** The name of the joint to be moved. */
    const AL::ALValue jointName = AL::ALValue::array("Body");
    try {

        AL::ALMotionProxy motion(robotIp);

        /** Target stiffness. */
        AL::ALValue stiffness = 1.0f;
        /** Time (in seconds) to reach the target. */
        AL::ALValue time = 1.0f;
        /** Call the stiffness interpolation method. */
        motion.stiffnessInterpolation(jointName, stiffness, time);

//        std::cout << jointName << std::endl;
        AL::ALRobotPostureProxy robotPosture(robotIp);
        float maxSpeedFraction = 0.5f; //[0;1]
        bool postureReached = robotPosture.goToPosture("Stand",
                                                       maxSpeedFraction);
        if (! postureReached) say(robotIp, "Could not Stand");

        AL::ALNavigationProxy navigationProxy(robotIp);
        float x = .5 ,y = 0, theta = 0;
//        navigationProxy.moveTo(x, y, theta);






      /** Make sure the head is stiff to be able to move it.
      * To do so, make the stiffness go to the maximum in one second.
      */
      /** Target stiffness. */
//      AL::ALValue stiffness = 1.0f;
      /** Time (in seconds) to reach the target. */
//      AL::ALValue time = 1.0f;
      /** Call the stiffness interpolation method. */
//      motion.stiffnessInterpolation(jointName, stiffness, time);

      /** Set the target angle list, in radians.
        Max pitch: 29.5 degrees = 0.514872129 rad
*/
      float degrees  = 21.0f;
      float rads = degrees * M_PI / 180;
      AL::ALValue targetAngles = AL::ALValue::array(rads, 0.0f);
      /** Set the corresponding time lists, in seconds. */
      AL::ALValue targetTimes = AL::ALValue::array(1.0f, 1.0f);
      /** Specify that the desired angles are absolute. */
      bool isAbsolute = true;

      /** Call the angle interpolation method. The joint will reach the
      * desired angles at the desired times.
      */
//      motion.angleInterpolation(jointName,
//        targetAngles,
//        targetTimes,
//        isAbsolute);

      /** Remove the stiffness on the head. */
      stiffness = 0.0f;
      time = 1.0f;
//      motion.stiffnessInterpolation(jointName, stiffness, time);

    }
    catch (const AL::ALError& e) {
      std::cerr << "Caught exception: " << e.what() << std::endl;
      exit(EXIT_FAILURE);
    }
#else
    std::cout << "lookDown not on linux" << std::endl;
#endif
}
