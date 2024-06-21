# Computação Grafica

## Objetivos 

Implementar no OPENGL usando os shaders de vertice e fragmento em arquivos separados (main.c; vertex.s; fragment.s):

* inclusão de 2 objetos 3D na cena;
* implementar no Shader de Vértice a matriz de rotação para rotacionar os objetos na cena;
* aplicar no shader de fragmento a implementação da luz ambiente com coeficiente em 0.3


## Compiling and Running the Project

Sure, here's a simple instruction set for compiling and executing a C++ project that uses multiple source files and has dependencies on external libraries like GLM and GLFW:

## Compiling and Running the Project

1. **Prerequisites**: Ensure you have a C++ compiler and the necessary libraries installed on your system. For Linux, you can use `g++`.

    You also need to install the `GLM` library for handling vectors and matrices, and `GLFW` for creating windows and handling input. You can install them via your package manager as well. For example, on Ubuntu, you can use the following commands:

```bash
sudo apt-get install libglm-dev
sudo apt-get install libglfw3-dev
sudo apt-get install g++ cmake
```

2. **Compiling the Code**: Navigate to the project directory and create a new directory for the build files:

```bash
mkdir build
cd build
```

Then, run CMake to generate the build files:

```bash
cmake ..
```

And finally, compile the code:

```bash
make
```

This will create an executable file named `Trabalho` in your project directory.


3. **Running the Program**: You can run the program using the following command:

```bash
./Trabalho
```
