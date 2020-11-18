# Windows build guide

The first and foremost step is to install Qt.

Follow [this link](https://www.qt.io/download-qt-installer) to download the installer.

Now, if your IDE is Qt Creator, you have finished. All you need to do is to open `src\trading-platform-pp.pro` with `Qt Creator`, and then `build` it.

If that is not the case, we need to run `scripts\build.sh`, and to run it we need to add `qmake` and `make` to `PATH`, which are shipped with Qt.

(Take a look at [this](https://www.architectryan.com/2018/03/17/add-to-the-path-on-windows-10/) if you don't know what is "adding to `PATH`.)

To add `qmake` and `make` to `PATH`,

1. Locate your `Qt` folder (default path is `C:\Qt`).

2. Look for a path that looks like `5.12.34\mingw56_78\bin`, and add it to `PATH`.

3. Look for a path that looks like `Tools\mingw56_78\bin`, open the folder, create a copy of `mingw32-make.exe`, name it `make.exe`, and add the folder path to `PATH`.


