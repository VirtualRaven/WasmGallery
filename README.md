# WasmGallery
This is a C++ implementation of the image layout algorithm used in my photo website [photos.rahmn.net](https://photos.rahmn.net).
The source code for the website itself is available here [WebGallery](https://github.com/VirtualRaven/WebGallery). 

The system is a simple image layout algorithm that sizes images for display in fixed size
rows such that the row is compleatly filled and image aspect ratio preserved. The task of this program 
is to calculate the resulting size of each image whilst the actual layout is done in javascript. See WebASM.js in 
the website source.

Data.hpp contains all meta data for the images included in the gallery which is compiled into the resulting binary. This 
is generated using the generate.py script bundled with the website. 

