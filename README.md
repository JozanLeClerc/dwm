# README in progress

# Joe's dwm (the dynamic window manager) laptop build

The original [dwm](https://dwm.suckless.org/) desktop manager build use to use on my ThinkPad.

Based on version 6.2.



## Dependencies

  `gcc`  
  `make`  
  `xorg`  
  `libX11`  
  `libXft`

## Installation

To install this open a terminal and run these commands:
```shell
git clone https://github.com/JozanLeClerc/dwm-laptop.git
cd dwm-laptop
sudo make clean install
```
To use it as a default WM, if you are using xinit, add this to your `.xinitrc`:
```shell
exec dwm
```
I am not shure about how to set it up on `gdm`, `lightdm`, etc...

## Bindings

Some of the main key bindings:
- **switch to workspace** 1-10 with `super+{F1-F10}`
- **show all workspaces at once** with `super+F12`
- **move a window to workspace** 1-10 with `super+shift+{F1-F10}`

My own autostart script can be found on my (dotfiles)[https://github.com/JozanLeClerc/dotfiles.git] repository. It should be placed in `~/.dwm/` directory.