# block-shooters
This is a simple shooter with blocks.

![Menu](https://github.com/SairenDelight/my-repository-images/blob/master/block-shooter/Block_Shooters_Menu.png)


![Game](https://github.com/SairenDelight/my-repository-images/blob/master/block-shooter/Block_Shooters_Game.png)



***
## Setting up Linkers for SDL
Please refer to this Youtube video to set up SDL2 with Visual Studio 2017: [Setting up SDL2](https://www.youtube.com/watch?v=Sfn7yOiwJLw)    
Download SDL2's development library here: [SDL2 Library](https://www.libsdl.org/download-2.0.php)     
![SDL Development Library](https://github.com/SairenDelight/my-repository-images/blob/master/block-shooter/SDL2_dev_lib.png)    



      
Download SDL2's TTF development library here: [SDL2 TTF](https://www.libsdl.org/projects/SDL_ttf/)     
![SDL2 TTF Development Library](https://github.com/SairenDelight/my-repository-images/blob/master/block-shooter/SDL2_ttf_dev_lib.png)    



     
Download SDL2's image development library here: [SDL2 Image](https://www.libsdl.org/projects/SDL_image/)
![SDL2 Image Development Library](https://github.com/SairenDelight/my-repository-images/blob/master/block-shooter/SDL2_image_dev_lib.png)           


***

## Setup
Download the all files from this repository. Open up Visual Studio 2017 and click on `File > Open > Project/Solution` and select the `Game.sln` file from the repository files. Visual Studio should set up the project structure for you (if the vcxproj.filters files are inside).

***
### Steps to set up linkers
1. After downloading all the development libraries go to `Project > Properties...` and a configuration menu should appear.     
2. Go to the `C/C++` tab and click on `General`. Inside that tab go to `Additional Include Directories` and add the paths to the library's `[SDL2s Library Name]/include` folder. Press okay.
![SDL 2 Development Includes Config](https://github.com/SairenDelight/my-repository-images/blob/master/block-shooter/Project_Config_Properties_C_C%2B%2B.png)     
3. Go to the `Linker` tab and click on `General`. Inside the tab go to `Additional Library Directories` and add the path to the folder `[SDL2 Library Name]/lib/x86` or `[SDL2 Library Name]/lib/x64` depending on your system. Press okay.     
![SDL 2 Development Library Config](https://github.com/SairenDelight/my-repository-images/blob/master/block-shooter/Project_Config_Properties_Linker_General.png)
4. Then, continuing in the `Linker` tab, click on the `Input` tab. Inside it go to `Addtional Dependencies` and type the file names within each of the libraries. Add all the files with `.lib` extension. Press okay.
![SDL 2 Development Lib Config](https://github.com/SairenDelight/my-repository-images/blob/master/block-shooter/Project_Config_Properties_Linker_Input.png)     
5. At the bottom of the configuation menu, press apply and okay.     
6. From each of the libaries, drag the `.dll` files into the Game project folder where all the C source files and header files are.     


***
## Resources
Refer to this site for tutorial: [Lazy Foo](http://lazyfoo.net/tutorials/SDL/index.php)     
Here is the documentation for SDL2 Library: [SDL2 Wiki](https://wiki.libsdl.org/FrontPage)
