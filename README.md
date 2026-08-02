# MARGE (v0.11.0) - Camera Update

*MARGE - Modular Advanced Raytracing & Graphics Engine*<br>

## Changes
This update majorly reworks the camera in the renderer. Each render, the camera can be positioned anywhere, rotated anyhow, and zoomed any amount.<br><br>

<img width="2199" height="1234" alt="Screenshot 2026-08-02 193004" src="https://github.com/user-attachments/assets/19910c2b-b9a8-4b88-a265-f07f5fa9952d" /><br>

MARGE is a lightweight raytracing graphics engine built from scratch in raw C++. It's current main focus is building a solid understanding of graphics and rendering through minimal, controlled implementation of new concepts such as math, data types, etc.

***DISCLAIMER: MARGE is not entirely my own work. It is being built by following along with the Raytracing in One Weekend series by Peter Shirley, Trevor David Brown, and Steve Hollasch, although I do my best to make it my own by using different standard practices, data types, definitions, naming conventions, and modern C++ features that the book does not use.***

## Goal
MARGE's goal is to build a clean, lightweight, easy-to-use, open-source graphics engine from the ground up, starting with single-image generation and gradually expanding into a frame-based renderer that can be used for game engines, CAD software, etc.

## Current Status
MARGE is in early development (v0.11.0).  
At this stage, the focus is correctness and structure, not feature completeness.

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

## Future/Planned Features
- Additional Materials
- Various Different Shapes (Planes, Triangles, Boxes, etc.)
- Lighting/Shadows
- Major Performance Improvements
- Frame-Based Rendering

## Build and Run

*Warning: MARGE compatibility with MacOS has not yet been tested. MARGE is fully compatible with Windows and Linux.*

MARGE uses a simple C++ build process with no external dependencies.

### Requirements

You need a C++ compiler with C++ 20 support:

- **macOS:** Apple Clang (via Xcode Command Line Tools)
- **Linux:** g++ (GCC)
- **Windows:** MinGW-w64 or MSYS2 (g++)
