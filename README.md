<div align="center" id="top"> 
  <img src="./.github/app.gif" alt="Vintuosocpp" />

  &#xa0;

  <!-- <a href="https://vintuosocpp.netlify.app">Demo</a> -->
</div>

<h1 align="center">Vintuosocpp</h1>

<p align="center">
  <img alt="Github top language" src="https://img.shields.io/github/languages/top/stsier/vintuosocpp?color=56BEB8">

  <img alt="Github language count" src="https://img.shields.io/github/languages/count/stsier/vintuosocpp?color=56BEB8">

  <img alt="Repository size" src="https://img.shields.io/github/repo-size/stsier/vintuosocpp?color=56BEB8">

  <img alt="License" src="https://img.shields.io/github/license/stsier/vintuosocpp?color=56BEB8">

  <!-- <img alt="Github issues" src="https://img.shields.io/github/issues/stsier/vintuosocpp?color=56BEB8" /> -->

  <!-- <img alt="Github forks" src="https://img.shields.io/github/forks/stsier/vintuosocpp?color=56BEB8" /> -->

  <!-- <img alt="Github stars" src="https://img.shields.io/github/stars/stsier/vintuosocpp?color=56BEB8" /> -->
</p>

<!-- Status -->

<!-- <h4 align="center"> 
	🚧  Vintuosocpp 🚀 Under construction...  🚧
</h4> 

<hr> -->

<p align="center">
  <a href="#dart-about">About</a> &#xa0; | &#xa0; 
  <a href="#sparkles-features">Features</a> &#xa0; | &#xa0;
  <a href="#rocket-technologies">Technologies</a> &#xa0; | &#xa0;
  <a href="#white_check_mark-requirements">Requirements</a> &#xa0; | &#xa0;
  <a href="#checkered_flag-starting">Starting</a> &#xa0; | &#xa0;
  <a href="#memo-license">License</a> &#xa0; | &#xa0;
  <a href="#link-references">References</a> &#xa0; | &#xa0;
  <a href="https://github.com/stsier" target="_blank">Author</a>
</p>

<br>

## :dart: About ##

Describe your project

## :sparkles: Features ##

:heavy_check_mark: Feature 1;\
:heavy_check_mark: Feature 2;\
:heavy_check_mark: Feature 3;

## :rocket: Technologies ##

The following tools were used in this project:

- [Expo](https://expo.io/)
- [Node.js](https://nodejs.org/en/)
- [React](https://pt-br.reactjs.org/)
- [React Native](https://reactnative.dev/)
- [TypeScript](https://www.typescriptlang.org/)

## :white_check_mark: Requirements ##

Before starting :checkered_flag:, you need to have [Git](https://git-scm.com) and [Node](https://nodejs.org/en/) installed.

## :checkered_flag: Starting ##

```bash
# OpenCV prerequisites

$ sudo apt update && sudo apt install -y cmake g++ wget unzip
$ wget -O opencv.zip https://github.com/opencv/opencv/archive/master.zip
$ unzip opencv.zip; rm opencv.zip
$ git clone https://github.com/opencv/opencv_contrib.git
$ cd opencv-master
$ mkdir -p build && cd build
$ cmake -DOPENCV_EXTRA_MODULES_PATH=../opencv_contrib/modules  -DWITH_GTK=ON -DOPENCV_GENERATE_PKGCONFIG=YES  -DBUILD_SHARED_LIBS=OFF -DCMAKE_INSTALL_PREFIX=/home/sergei/Vintuoso/vintuosocpp/vinlib/opencv .. 
$ cmake -DOPENCV_EXTRA_MODULES_PATH=../opencv_contrib/modules  -DWITH_GTK=OFF -DOPENCV_GENERATE_PKGCONFIG=NO -DCMAKE_BUILD_TYPE=Release -DENABLE_PIC=OFF -DBUILD_SHARED_LIBS=OFF -DWITH_PNG=NO  -DCMAKE_INSTALL_PREFIX="/usr/local" ..
$ cmake --build .
$ make -j5
# Clone this project
$ git clone https://github.com/stsier/vinlib

# Access
$ cd vinlib
$ mkdir build; cd build

# Build
$ cmake ..
$ cmake --build .

# Init node project 
$ npm init -y

# Install dependencies
$ npm install -S node-addon-api
$ npm install -S bindings
$ npm install -g cmake-js


# Or
~~$ npm install -g node-gyp~~
~~$ node-gyp configure~~
~~$ node-gyp build~~

# Build

# Run the project
$ node index.js

# The server will initialize in the <http://localhost:3000>
```

## :memo: License ##

This project is under license from MIT. For more details, see the [LICENSE](LICENSE.md) file.


Made with :heart: by <a href="https://github.com/stsier" target="_blank">Sergei TSIER</a>


## :link: References ##

<a href="https://medium.com/jspoint/a-simple-guide-to-load-c-c-code-into-node-js-javascript-applications-3fcccf54fd32">Node js C++</a>
<a href="https://docs.opencv.org/4.5.2/d1/de0/tutorial_py_feature_homography.html">OpenCV Python Homography</a>
<a href="https://docs.opencv.org/3.4/d7/dff/tutorial_feature_homography.html">OpenCV C++ Homography</a>
<a href="https://stackoverflow.com/questions/57075719/filtering-out-false-positives-from-feature-matching-homography-opencv">Filtering with Homography</a>
<a href="https://towardsdatascience.com/improving-your-image-matching-results-by-14-with-one-line-of-code-b72ae9ca2b73">BEBILD</a>


&#xa0;

<a href="#top">Back to top</a>
