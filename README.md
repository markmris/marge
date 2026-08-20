# MARGE (v0.16.0) - Texture Update

*MARGE - Modular Advanced Raytracing & Graphics Engine*<br>

## Changes
This update introduces basic textures. The first texture of which added is a checkerboard texture.

<img width="2199" height="1236" alt="image" src="https://github.com/user-attachments/assets/ee2b9cda-d049-4d16-8cc5-24a22b710779" /><br>

MARGE is a lightweight raytracing graphics engine built from scratch in raw C++. It's current main focus is building a solid understanding of graphics and rendering through minimal, controlled implementation of new concepts such as math, data types, etc.

***DISCLAIMER: MARGE is not entirely my own work. It is being built by following along with the Raytracing in One Weekend series by Peter Shirley, Trevor David Brown, and Steve Hollasch, although I do my best to make it my own by using different standard practices, data types, definitions, naming conventions, and modern C++ features that the book does not use.***

## Goal
MARGE's goal is to build a clean, lightweight, easy-to-use, open-source graphics engine from the ground up, starting with single-image generation and gradually expanding into a frame-based renderer that can be used for game engines, CAD software, etc.

## Current Status
MARGE is in early development (v0.16.0).  
At this stage, the focus is correctness and structure, not feature completeness. MARGE is currently run entirely on the CPU, but will be transformed into a GPU renderer in the future.

## Current Features
- Basic Scene Setup
- Single PPM Image Output
- Simple Camera Object
- Ray-Sphere Intersection
- Antialiasing
- Diffuse Materials
- Metal/Mirror Materials (With fuzz)
- Dielectrics (Glass)
- Positionable/Rotatable/Zoomable Camera
- Defocus Blur/Motion Blur
- Random scene generation
- Bounding Volume Hierarchies (BVH)
- Basic Textures

## Future/Planned Features
- Additional Materials/Textures
- Various Different Shapes (Planes, Triangles, Boxes, etc.)
- Lighting/Shadows
- Major Performance Improvements
- Frame-Based Rendering
- MacOS Compatibility<br><br>

### v0.13.0 introduced custom commands for MARGE to be run from the terminal. Instead of modifying variables and recompiling, variables are now modifiable through the command line. The options are:

objectcount (integer) The amount of objects to be rendered in the scene. Has some performance impact the higher it is. Default set to 20

pixelsamples (integer). The higher this number is, the better the image looks, but the longer it takes to render. Default set to 32. Anything around 50 looks pretty good.

rayDepth (integer). The higher this is, the more realistic reflections will look. Default set to 13.

focusDistance (decimal) The distance from the camera where objects are perfectly in focus. This is disabled when defocusAngle is set to 0. Default set to 8.0.

defocusAngle (decimal). The higher this number is, the more blurred objects will look the further they are from the focus distance. Default set to 0.6.

fov (decimal). The lower this number is, the more zoomed in the camera is. Default set to 90.

yaw (decimal). The left-right rotation of the camera. Set in degrees. Default set to 0.

pitch (decimal) The up-down rotation of the camera. Set in degrees. Default set to -40.<br><br>

## Install and Run

*MARGE does not have a readily available MacOS executable yet. There are executables available for Windows and Debian (.deb) Linux systems.*<br>

### Step 1: 
Go to the latest release page (https://github.com/markmris/marge/releases/tag/v0.13.0) and download MARGE.zip for windows or MARGE.tar.gz for Linux.<br>

### Step 2:
Extract the file wherever.<br>

### Step 3:
Open a terminal and run this command:
`
cd ~/path-to/MARGE
` (Replace path-to with the file path to the folder. For example, Documents/"Hack Club"/MARGE)<br>

### Step 4:
Run this command FIRST to gain a short overview on how to use MARGE: 
`
./MARGE --help
`<br>

## Step 5:
In the MARGE folder, look for a new file called "image.ppm". Open it (Note: On Windows, you will need an app that supports .ppm image files, GIMP, Portable Images Viewer, and Krita are free ones that work.)

## Step 6: Use MARGE however you like!
