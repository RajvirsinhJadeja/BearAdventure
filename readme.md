# Bear Adventure

Bear Adventure is a C++ project that leverages the SFML library to create platformer game. In this game, players must overcome obstacles and try to achieve the hightest score they can. The project demonstrates proficiency in C++, algorithms and usage of libraries to achieve goals.

![image](https://github.com/user-attachments/assets/b624940a-8622-43f8-a7f1-b240f9fdc2ac)


## Table of Contents
- [Building the Project](#building-the-project)
- [Running the Game](#running-the-game)
- [Usage Example](#usage-example)
- [Development Setup](#development-setup)
- [Contributing](#contributing)
- [License](#license)

## Building the Project
To build and run the game, follow these steps:

1. Clone the repository:

    ```
    git clone https://github.com/yourusername/BearAdventure.git
    ```

2. Navigate to the project directory:

    ```
    cd BearAdventure
    ```

3. Create a build directory and navigate into it:

    ```
    mkdir build
    cd build
    ```

4. Run CMake to configure the project:

    ```
    cmake ..
    ```

5. Build the project in Release mode:

    ```
    cmake --build . --config release
    ```

## Running the Game
1. Navigate to the build directory where the executable is located. This is typically in a subdirectory like `Release`:

    ```
    cd Release
    ```

2. Run the game executable:

    ```
    BearAdventure.exe
    ```
    
3. Press either up arrow or down arrow to start playing

## Usage Example
There are no command-line arguments or configurations required to run the game. Simply build the project and execute the `BearAdventure.exe` file from the `Release` directory.

## Development Setup
For development purposes, ensure you have the following:

- **CMake**: Required to build the project.
- **SFML**: Make sure the SFML-2.6.1 library is in the correct directory as specified in `CMakeLists.txt`.

1. Install dependencies (if not already installed):

```
sudo apt-get install cmake
```

2. Clone the repository and build the project (as shown in the Building the Project section).

## Contributing

I welcome contributions to improve the game! Please follow these steps to contribute:

1. Fork the repository: [https://github.com/RajvirsinhJadeja/BearAdventure/fork](url)

2. Create a new branch for your feature or fix:

```
git checkout - b feature/your-feature
```

3. Commit your changes:

```
git commit -am 'Added some Feature'
```

4. Push the branch:

```
git push origin feature/your-feature
```

5. Create a Pull Request: Go to the repository on GitHub and create a new Pull Request.

## Meta

Rajvirsinh Jadeja – rjs.jadeja@gmail.com

Distributed under the MIT license. See `LICENSE` for more information.

[https://github.com/RajvirsinhJadeja/](https://github.com/RajvirsinhJadeja)

