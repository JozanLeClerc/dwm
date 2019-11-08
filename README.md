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
I am not shure about how to set it up on `gdm`/`lightdm`/etc...