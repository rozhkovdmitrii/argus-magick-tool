##### Argus magick tool 1.0.0 
---

## Summary

`argus-magic-tool` is a simple command-line utility that provides various basic image processing operations. Currently, loading, saving, blurring, resizing, and displaying operations are available.

The `argus-magic-tool` app was developed as part of the argus-soft challenge. It's based on [Magick++ that is the object-oriented C++ API to the ImageMagick image-processing library](https://imagemagick.org/Magick++/)

## Building recipe

##### Clone from github
```bash
git clone --recursive git@github.com:rozhkovdmitrii/argus-magick-tool.git
```
##### Building
```bash
mkdir argus-magick-tool/build && cd argus-magick-tool/build
cmake .. && cmake --build .
```

## Commands

**help, h**:       print this message

**load, ld**: load <name> <filename> 
                loads image from file
                <name> - key value provides image in other commands
                <filename> - file path to be loaded

**store, s**: store <name> <filename> 
                stores image in file
                <name> - key value to get image
                <filename> - file path to save image to

**blur**:       blur <from_name> <to_name> <size>
                apply blur effect to image
                <from_name> - key value to get image to be blured
                <to_name> - key value to put resulting image
                <size> - blur algorithm radius value

**resize**:   resize <from_name> <to_name> <new_width> <new_height>
               resizes image
               <from_name> - key value to get image to be resized
               <to_name> - key value to put resulting image
               <new_width> - new width size to resize <from_name>
               <new_height> - new height size to resize <from_name>

**display**: display <name>
                display image <name>

**exit, quit, q**: terminate program execution

## Examples

```bash
Argus magick tool 1.0.0
Usage: argus-magick-tool
Type "help" or "h" for more information.
> load origin gg
Unexpected Magick++ error: Magick: unable to open image 'gg': No such file or directory @ error/blob.c/OpenBlob/3537
> load origin ./origin.jpg
Command performed: LoadCommand: imageName: "origin", fileName: "origin.jpg"
> display origin
Command performed: DisplayCommand: imageName: "origin"
> resize origin origin 500 500
image: "origin" already exists - will be overwritten
Command performed: ResizeCommand: srcImageName: "origin", dstImageName: "origin", newWidth: 500, newHeight: 500
> display origin
Command performed: DisplayCommand: imageName: "origin"
> blur origin out 10
Command performed: BlurCommand: srcImageName: "origin", dstImageName: "out", blurSize: 10
> store out out.jpg
Command performed: StoreCommand: imageName: "out", fileName: "out.jpg"
> display out
Command performed: DisplayCommand: imageName: "out"
> quit
quit ...
```

## Build environment

`argus-magick-too` was built on `Arch GNU/Linux 5.7.12` with `g++ (GCC) 10.1.0`, `cmake 3.18.1`, `imagemagick 7.0.10.25-1`