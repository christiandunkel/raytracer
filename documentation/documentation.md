
# Documentation
[Back to main page](../README.md)

## Overview

 - [General remarks](#general-remarks)
 - [Raytracing process](#raytracing-process)
 - [How to install](#how-to-install)
	 - [Windows](#windows)
	 - [Linux](#linux)
 - [How to use](#how-to-use)
 - [Creating a scene](#creating-a-scene)

<br />
<br />
<br />

## General remarks

This raytracer completely works on one thread of the CPU, with no support for GPU and multi-threading. Therefore, the rendering rendering process for images, especially with a lot of objects, higher resolution and graphic settings, can range from a few seconds to a few minutes.

<br />
<br />
<br />

## Raytracing process

The program reads an `.sdf` file that contains data about a scene. The scene consists of shapes, lights, transformations, cameras, and rendering information. The program will construct a scene from this information that contains the references to all the shapes, cameras, and lights. Using the rendering information, the raytracer will now generate a **Netpbm** image of the _**P**ortable **P**ix**M**ap_ format.

![A screenshot of an sdf file containing information about the materials and shapes in a scene.](images/raytracer_sdf_file.png)

The raytracer will send out a ray for every pixel from the camera. The ray will hit the closest object or the background, which will be the base color. After that, it will reflect and possibly hit other objects or the background, of which the colors will be used to calculate the final color of the given pixel. 

Additionally, rays from all light sources will be sent out towards the intersection of ray and shape to calculate shadows. In addition to ambient lights, they will influence the final color of the pixel as well.

![An illustration of a camera shooting out a ray towards a rectangle, which reflects and hits a circle, and two lights shooting rays at the intersection.](images/raytracer_illustration.png)

There are also options to define reflection and refraction effects in the materials. The final colors from the ray will also go through a short post-processing using anti-aliasing, tone mapping and gamma correction.

Finally, the program has generated a full array of all pixels for the image. A picture will then be generated as a `.ppm` file. 

The program also supports animations and outputs the defined frames as `.ppm` files if an 'animated scene' is selected in the options. There's also an option to generate animated `.sdf` files instead.

<br />
<br />
<br />

## How to install

This project is written in `C++` and build using the tool [CMake](https://cmake.org/), version `3.1` or higher.

The build was tested in *Linux (Ubuntu)* and *Windows 10*.

In order to run this project, you first want to clone the project by entering the following command in the command prompt in windows or the terminal in Linux.

```
git clone https://github.com/christiandunkel/raytracer
```

### Windows

The recommended process for building this project in Windows is to install `Visual Studio 2017` and then `Visual Studio Code`. Install the extensions `CMake 0.0.17` and `CMake Tools 1.1.1` in Visual Studio Code, then open the project folder inside Visual Studio Code. Make a clean build of *source > raytracer* in the new *Cmake* section in the toolbar, and you're done.

After the build is finished, the program will be executed inside the terminal of Visual Studio Code. If you want to find the `.exe` file, it is located in *build > source > raytracer.exe*.

### Linux

In order to build this project in Linux, open the terminal. You have to navigate towards the directory into which you cloned the remote.

```
cd directory/raytracer
```

Enter the following commands in order, which will create the build.

```
mkdir build
cd build
cmake ..
make all
```

After the build is finished, you can directly execute the raytracer by using the following commands in order:

```
cd build/source
./raytracer
```

<br />
<br />
<br />

## How to use

After you have built the project using CMake, you can execute the `raytrace.exe` file from the top level of the directory using the terminal with the following command:

```
.\build\source\raytracer.exe
```

Doing so will render the scene file that is currently defined in the source code of `raytracer.cpp`. If you want to render a custom scene with *(optionally)* custom settings, you can do so via parameters in your command.
```
.\build\source\raytracer.exe --file "scene.sdf"
```

You can define multiple parameters behind each other. The following parameters currently exist:

- `--file` defines a path to the scene (sdf file)
- `--frames` defines the amount of images to be generated (if there is an animation definition in the scene file)
- `--aa` enables anti-aliasing
- `--recursion` defines the maximum recursion depth per ray *(how often a ray is reflected from surface to surface to determine the pixel color)*
- `--help` show help menu

<br />
<br />
<br />

## Creating a scene

In order to write a custom scene, you need to create a `.sdf` file, which will contain all the definitions for the scene.

**Every scene needs to have at least one root composite, a material, a shape, a camera and a render definition.**
