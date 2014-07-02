cmake_minimum_required(VERSION 2.8)
project(naoClassifier)

find_package(qibuild)


# Create a list of source files
set(_srcs
AbstractFactory.h
AbstractFactory.cpp
AbstractImageFetcher.h
AbstractImageFetcher.cpp
Camera.h
Camera.cpp
KMeansClusteringAlgorithm.h
KMeansClusteringAlgorithm.cpp
AbstractClusterAlgorithm.h
AbstractClusterAlgorithm.cpp
Object.h
Object.cpp
Head.h
Head.cpp
Image.h
Image.cpp
ImageFetcherOnOSX.h
ImageFetcherOnOSX.cpp
NAO.h
NAO.cpp
ObjectDetector.h
ObjectDetector.cpp
SpaceOrientation.h
SpaceOrientation.cpp
Speech.h
Speech.cpp
Locomotion.h
Locomotion.cpp
CustomMoves.h
CustomMoves.cpp

 #helloworld.h
  main.cpp
)

#for arc4random() function:
#set(CMAKE_CXX_FLAGS "-lbsd" )

# Create a executable named naoClassifier
# with the source file: main.cpp
qi_create_bin(naoClassifier ${_srcs})

# Here we say that our executable depends on
# - ALCOMMON (main naoqi lib)
# - ALVISION (for vision definitions)
# - OPENCV (display

# This will set the libraries to link naoClassifier with,
# the include paths, and so on
qi_use_lib(naoClassifier ALCOMMON ALVISION ALAUDIO OPENCV2_CORE OPENCV2_HIGHGUI OPENCV2_IMGPROC OPENCV2_VIDEO )
