# rc2xml

## Description
rc2xml is a tool that translates [Open
interface](https://en.wikipedia.org/wiki/Open_Interface) resource files
(Text-based representation of GUIs) to an XML format that can be used by Qt.

At it's core, our tool is a compiler and it consist of three main components:

* A Scanner that is used to transform the input resource file into a list of
  tokens.
* A Parser that is used to organise those tokens into an Abstract Syntax Tree.
* A Codegen that is used to produce the appropriate XML code based on templates
  and AST nodes.

## Requirements
- C++ compiler that supports C++17 features
- CMake >= 3.14

## Build
```Shell
$ git clone https://github.com/iamkhalil/rc2xml.git
$ cd rc2xml/
$ mkdir build && cd build   # Create a directory to hold the build output and cd to it.
$ cmake ..                  # Generate native build scripts.
$ cmake --build .
```

## Usage
To use the program, run the executable `rc2xml`. The program takes a resource
file (\*.rc) as an argument and generates an XML file (\*.ui) that will be written in the same
directory as the input resource file.
```Shell
$ ./rc2xml file.rc
```

## Screenshots

#### Example 1:

**Before**
![interface.rc](https://i.imgur.com/dn02FzS.png)

**After**
![interface.ui](https://i.imgur.com/N8pahGj.png)

#### Example 2:
**Before**
![test.rc](https://i.imgur.com/J20rGJX.png)

**After**\
![test.ui](https://i.imgur.com/61MGj9w.png)

## Todo
- Add support for more widgets and properties.

## Author
- **Mohamed khalil El-Bechir** - [medkhalilelb@gmail.com](medkhalilelb@gmail.com) | [GitHub/iamkhalil](https://github.com/iamkhalil)
## Licence

MIT License
