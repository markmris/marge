# MARGE (v0.5)

*MARGE - Modular Advanced Raytracing & Graphics Engine*

<img width="1053" height="590" alt="Screenshot_2026-07-05_00-17-20" src="https://github.com/user-attachments/assets/6e81d30f-c862-436b-b5e9-5c3442a5f075" />

MARGE is a lightweight raytracing graphics engine built from scratch in raw C++. It's current main focus is building a solid understanding of graphics and rendering through minimal, controlled implementation of new concepts such as math, data types, etc.

***DISCLAIMER: MARGE is not entirely my own work. It is being built by following along with the Raytracing in One Weekend series by Peter Shirley, Trevor David Brown, and Steve Hollasch, although I do my best to make it my own by using different standard practices, data types, definitions, naming conventions, and modern C++ features that the book does not use.***

## Goal
MARGE's goal is to build a clean, lightweight, easy-to-use, open-source graphics engine from the ground up, starting with single-image generation and gradually expanding into a frame-based renderer that can be used for game engines, CAD software, etc.

## Current Status
MARGE is in early development (v0.5).  
At this stage, the focus is correctness and structure, not feature completeness.

## Current Features
- Basic Scene Setup
- Single PPM Image Output
- Simple Camera Object
- Ray-Sphere Intersection
- Minimal Rendering Pipeline (Ray -> Math -> Pixel)

## Future/Planned Features
- Different Materials (Reflective/Mirrors, Diffuse)
- Various Different Shapes (Planes, Triangles, Boxes, etc.)
- Lighting/Shadows
- Performance Improvements
- Frame-Based Rendering

## Build and Run

*Warning: MARGE may not perform well on Windows. MacOS compatibility has not been tested. Linux is completely compatible.*

MARGE uses a simple C++ build process with no external dependencies.

### Requirements

You need a C++ compiler with C++17 support:

- **macOS:** Apple Clang (via Xcode Command Line Tools)
- **Linux:** g++ (GCC)
- **Windows:** MinGW-w64 or MSYS2 (g++)
