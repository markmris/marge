# MARGE (v0.10.1) - Dielectrics Update

*MARGE - Modular Advanced Raytracing & Graphics Engine*<br>

## Changes
This update brings a new category of materials into the engine, dielectrics. The first dielectric introduced is a solid glass sphere. v0.10.1 includes minor edge case handling and introduces Schlick Approximation.<br><br>

<img width="2196" height="1234" alt="Screenshot 2026-07-30 192350" src="https://github.com/user-attachments/assets/e7b78a84-ae17-40ec-b334-b9bfebb42783" /><br>

MARGE is a lightweight raytracing graphics engine built from scratch in raw C++. It's current main focus is building a solid understanding of graphics and rendering through minimal, controlled implementation of new concepts such as math, data types, etc.

***DISCLAIMER: MARGE is not entirely my own work. It is being built by following along with the Raytracing in One Weekend series by Peter Shirley, Trevor David Brown, and Steve Hollasch, although I do my best to make it my own by using different standard practices, data types, definitions, naming conventions, and modern C++ features that the book does not use.***

## Goal
MARGE's goal is to build a clean, lightweight, easy-to-use, open-source graphics engine from the ground up, starting with single-image generation and gradually expanding into a frame-based renderer that can be used for game engines, CAD software, etc.

## Current Status
MARGE is in early development (v0.10.1).  
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

You need a C++ compiler with C++ 17 support:

- **macOS:** Apple Clang (via Xcode Command Line Tools)
- **Linux:** g++ (GCC)
- **Windows:** MinGW-w64 or MSYS2 (g++)
