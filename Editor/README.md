# Sam's Virtual Editor

Graphical editor based on Qt5.

![Imgur](https://i.imgur.com/dPGK7jQ.png)

## Development

You will need a working Qt5 environment.

The build process is the following:

```
$ mkdir -p build && cd build
$ qmake ..
$ make
$ open editor.app
```

The GUI (file [src/mainwindow.ui](src/mainwindow.ui)) is created using [Qt Creator](https://en.wikipedia.org/wiki/Qt_Creator).
