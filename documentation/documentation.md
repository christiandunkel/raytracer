
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
	 - [Camera](#camera)
	 - [Material](#material)
	 - [Light](#light)

<br />
<br />
<br />

## General remarks

This raytracer completely works on one thread of the CPU, with no support for GPU and multi-threading. Therefore, the rendering rendering process for images, especially with a lot of objects, higher resolution and graphic settings, can range from a few seconds to a few minutes. *Although this time can be considerably reduced, if you build the project as a release build instead of a debug build.*

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

You can build the project on both Windows and Linux (tested on Ubuntu). But **make sure** to build it as a *Release build* instead of a *Debug build*, which will result in a considerably faster rendering process.

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

After you have built the project using CMake, you can execute the `raytracer.exe` file using the terminal. Navigate to the top level directory of the project and use the following command:

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

*Every scene needs to have at least one root composite, a material, a shape, a camera and a render definition.*

### Definitions
- [Camera](#camera)
- [Material](#material)
- [Light](#light)

<br />
<br />

---

### Camera

```
define camera <name> <pos> <up-vec> <right-vec>
```

The camera front vector is on the z-axis and looks towards the negative z-values. It is defined using a position, a vector that points up and a vector that points to the right from its origin.

- `name` is a string, defining the name of the camera.
- `pos` is the position of the camera in world space and consists of 3 numbers for the x-, y- and z-axis that are separated by spaces.
- `up-vec` is the vector pointing up from the origin of the camera. The parameter consists of 3 numbers for the x-, y- and z-axis that are separated by spaces.
- `right-vec` is the vector pointing to the right from the origin of the camera. The parameter consists of 3 numbers for the x-, y- and z-axis that are separated by spaces.

*Example definition:*

```
define camera eye 20.0 0 200 200 0 -1 -1 0 1 0
```

<br />
<br />

---

### Material

```
define material <name> <ambient> <diffuse> <specular> <specular-reflection-exponent> <reflection-coefficient> <refraction-index> <opacity> 
```

The material defines the surface properties of all shapes it's assigned to, which includes color, reflection, refraction and opacity.

- `name` is a string, defining the name of the material.
- `ambient` defines the ambient color as a RGB value, consisting of 3 numbers from 0 to 1 that are separated by spaces.
- `diffuse` defines the diffuse color as a RGB value, consisting of 3 numbers from 0 to 1 that are separated by spaces.
- `specular` defines the specular color as a RGB value, consisting of 3 numbers from 0 to 1 that are separated by spaces.
- `specular-reflection-exponent` defines the specular reflection exponent, which should be a number to the power of 2, for example 8, 16 or 32.
- `reflection-coefficient` defines how strongly the rays should experience partial reflectance when passing through a transparent shape. It should be a number between 0 and 1
- `refraction-index` defines how fast the rays pass through a shape, which results in distortion of the background seen through transparent shapes. To turn it off, set it to 0. To turn it on, set the value higher than 1. A number between 1.05 and 1.5 produces the best results.
- `opacity` defines how transparent the object is. It has to be a number from 0 to 1, whereas 0 is non-transparent and 1 is fully-see-through.

*Example definition:*

```
define material pink 1 0 1 1 0 1 0 1 1 8 0 0 0
define material transparent_green 0 1 0 0 1 0 0 1 0 248 1 1.3 .5
define material reflective_red 1 0 0 1 0 0 1 0 0 16 0.2 0 0
define material mirror_white 0.1 0.1 0.1 0.1 0.1 0.1 0.1 0.1 0.1 8 0.9 0 0
```

<br />
<br />

---

### Light

There are two definitions for light, one for *ambient lights*, which affect the color and lighting of the whole scene, and *diffuse point lights*, which have a position in world space and can throw shadows.

*Ambient Light:*

```
define light <name> <color> <intensity>
```

*Diffuse Point Light:*

```
define light <name> <pos> <color> <intensity>
```

- `name` is a string, defining the name of the light.
- `pos` is the position of the diffuse point light in world space, consists of 3 numbers that are separated by spaces for the x-, y- and z-axis.
- `color` defines the light color as a RGB value, consisting of 3 numbers from 0 to 1 that are separated by spaces.
- `intensity` is the light intensity. It is a single number that has to be in the range of 0 to 1.

*Example definitions:*

```
define light point_light1 -20 200 -40 1 1 1 0.4
define light ambient_light1 -20 20 -40 1 1 0.2 0.1
```
