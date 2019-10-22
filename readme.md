# Summary.

Builds same game/app code across a range of platforms, current support is
* Windows
* Linux
* WebAssembly

Project is seperated into 2 projects
* Core - Cross platform Framework
* Game - The game

Feel free to use as a basis for your project, if you make any changes it would be nice to merge back for future users.

# Information

More information can be found here: http://www.shardedtools.com/code/opengl-framework/
and more tools/code etc can be seen: http://www.shardedtools.com

# Build Instructions.

1. Clone this repo
    ```git clone https://github.com/sharded-gaming/opengl-cross-platform-example.git```
2. Grab a copy of the glm headers ```https://glm.g-truc.net/0.9.9/index.html```

## Windows

1. Install VS2017/19 
2. Install glew 
2. Open project/example.sln
3. Build

## Linux

1. Install GCC and tools (Recommend VSCode as IDE)
2. Install Apache-Ant and ant-contrib
3. Install SDL
4. Open Terminal
5. To Build run command   ```ant linux```

## WebAssembly

1. Install Python 
2. Install Apache ant and Ant-contrib
3. Open Terminal and run command  ```ant html5```


# GNU General Public License v3.0.

See LICENSE.md for the full license.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND


   
