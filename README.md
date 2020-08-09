# scenes
A text and graphics tooll for terminal.

# Make and install.
Linux only.  
Requires g++ and ncurses.  
This will clone the repo, build and then copy the binary to ```~/.local/bin/```  

```
$ git clone https://github.com/jameschip/scenes.git
cd sccenes
$ make
$ make install
```

# Use

```
scenes file_name
```
I if the file does not exist it will be created when  you ssave the project.  

Tab changes between drawing and text mode.  

In text mode just type away.  
In draw mode 1 - 8 draws shades of grey.  

ctrl + s saves to input file  
ctrl + q quits
