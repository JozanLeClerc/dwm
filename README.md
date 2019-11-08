# README in progress

# Joe's dwm (the dynamic window manager) laptop build

The original [dwm](https://dwm.suckless.org/) desktop manager build I used to run on my ThinkPad.

Based on version 6.2.

As I am not using dwm anymore, developpement on my build might stop on this version.

## Dependencies

   `gcc`  
   `make`  
   `xorg`  
   `libX11`  
   `libXft`

Optional:
   `st`
   `slock`  
   `dmenu`

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

"Window" or "tile" is being called "stack" in this segment as it an apropriate name.

Some of the main key bindings:
- **switch** to workspace 1-10 with `super+{F1-F10}`
- **show all workspaces** at once with `super+F12`
- **move** selected stack to workspace 1-10 with `super+shift+{F1-F10}`
- **fire up** `st` terminal with `super+return`
- **kill** selected stack with `super+q`
- **cycle through** stacks down/up with `super+j/k`
- **move** selected stack down/up with `super+shift+j/k`
- **resize** master stack to left/right with `super+h/l`
- **invoke** `dmenu_run` application launcher with `super+p`. Get it [here](https://tools.suckless.org/dmenu/)
- **invoke** `slock` screen locker with `super+shift+l`. Get it [here](https://tools.suckless.org/slock/)
- toggle **normal tiled mode** with `super+s`
- toggle **alternative tiled mode** with `super+shift+s`
- toggle **maximized mode** (monocle) on selected stack with `super+f`
- toggle **floating mode** on selected stack with `super+space`
- toggle **top bar** with `super+escape`. Hidden by default
- **exit** dwm with `super+shift+e`

## Patches

My own autostart script can be found under my [dotfiles](https://github.com/JozanLeClerc/dotfiles.git) repository. It should be placed in `~/.dwm/` directory.