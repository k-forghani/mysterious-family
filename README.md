# Mysterious Family

## Introduction

This is a simple secure implementation of family tree, developed as the final project of **Data Structures and Algorithms** (**Fall 2023**) course at **Iran University of Science and Technology**. The architecture of the project is based on the [project description](schema/description.pdf) provided by teaching assistants.

## Dependencies

On Ubuntu operating system, install these dependencies:

```bash
sudo apt-get install g++
sudo apt-get install libjsoncpp-dev
sudo apt-get install libboost-dev
wget https://github.com/CrowCpp/Crow/releases/download/v1.0%2B5/crow-v1.0+5.deb
sudo apt-get install crow-v1.0+5.deb
```

## Compilation

On Unix-like operating systems, to compile the project and run the web application, just run `run.sh` with `app` argument:

```bash
chmod +x run.sh
./run.sh app
```

Instead of using the web application, you may run the test to debug the project:

```bash
./run.sh test
```

**Note**: You can also run these commands to compile and run the web application:

```bash
g++ -c libs/*.cpp -ljsoncpp
g++ -o app.out app.cpp *.o -ljsoncpp
./app.out
```

Then you can run `main` to use the interface.

## Schema

You can take a look at [classes diagrams](schema/uml.md).

## Developer

This project was developed by [*Kazem Forghani*](https://github.com/k-forghani), a student of Computer Science Department of Iran University of Science and Technology.

You can contact via k_forghani@mathdep.iust.ac.ir.

## License

This project has been released under *MIT License*.