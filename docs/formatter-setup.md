# Formatter Setup Guide

To make the project as clean as possible, we use the [Artistic Style](http://astyle.sourceforge.net/) to format our code. Below are the steps to setup the formatter on Qt Creator.

## Download and install Astyle

### Ubuntu
```
sudo apt install astyle
```

### MacOS
```
brew install astyle
```

### Windows

https://sourceforge.net/projects/astyle/files/

http://astyle.sourceforge.net/install.html#_Windows_Version

## Setup Astyle on Qt Creator
1. Open Qt Creator, select **Help > About Plugins > C++ > Beautifier** to enable the plugin.
2. Select **Restart Now** to restart Qt Creator and load the plugin.
3. Select **Tools > Options > Beautifier**.
4. Select the **Enable auto format on file save** check box to automatically beautify files when you save them. In the **Tool** field, select **Artistic Style**.
5. Select the **Artistic Style** tab. In **Configuration group**, specify the path to the tool executable in the Artistic Style command (for Ubuntu or MacOS, just simply put `astyle` and that should be fine).
6. In the **Options** group, select **Use file defined in project files**.