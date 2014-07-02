This repository contains the source for the project "Object Clustering using NAO robot" for Linux and Mac OS X. This is my Bachelor Diploma project. Both on Mac OS X and Linux OpenCV 2.4.9 or later is required. On Linux NAO C++ SDK should be installed.

This project makes NAO robot group the objects in front of him. On Mac OS X the functionality is limited to reading two images from filesystem, detecting the objects from them and showing which object is part of which group. On Linux, the program connects to the robot and remotely uses some of his modules, to acquire the images from the camera, move, speak and grasp the objects.


Here is a slightly simplified version of the interaction between objects and flow of messages:


![sequenceDiagram.png](https://bitbucket.org/repo/nRoGER/images/3667000871-sequenceDiagram.png)

And here are the dependencies and relationships between classes:



![image.jpg](https://bitbucket.org/repo/nRoGER/images/618423058-image.jpg)

![objectDiagram-diag.jpg](https://bitbucket.org/repo/nRoGER/images/2183852322-objectDiagram-diag.jpg)

![clusteringDiagram-diag.jpg](https://bitbucket.org/repo/nRoGER/images/2273875195-clusteringDiagram-diag.jpg)

![speechDiagram.jpg](https://bitbucket.org/repo/nRoGER/images/3297864333-speechDiagram.jpg)

![locomotionDiagram-diag.jpg](https://bitbucket.org/repo/nRoGER/images/3792704163-locomotionDiagram-diag.jpg)

![Head-diag.jpg](https://bitbucket.org/repo/nRoGER/images/181093453-Head-diag.jpg)

![NAO-diag.jpg](https://bitbucket.org/repo/nRoGER/images/3153616659-NAO-diag.jpg)