# Fortress

Fortress is a project developed by fomgleb and Logar1t. This README file will guide you through the process of downloading, installing, and running the project.

## Download

To download the Forte project, follow these steps:

1. Open a terminal.
2. Change the current working directory to the location where you want to clone the Forte directory. Let's assume this is the folder `src`.
3. Clone Forte from GitHub by pasting the following command:

    ```sh
    git clone git@github.com\:fomgleb/fortress.git
    ```

## Installation

To install and build the project, follow these steps:

1. Navigate to the project directory:

    ```sh
    cd fortress
    ```

2. Create a build directory and configure the project using CMake:

    ```sh
    cmake -B build
    ```

3. Build the project:

    ```sh
    cmake --build build
    ```

## Usage

To run the project, use the following command:

```sh
./build/src/main_app
