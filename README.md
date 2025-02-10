# Project Rough Procedure

Welcome to the **Project Rough Procedure** repository! This project outlines the steps and procedures for setting up and running a C++ application in a containerized environment using Docker. Below, you'll find a detailed guide on how to replicate the setup and run the project on your local machine.

## Overview

This project involves setting up a virtual machine (VM) on the cloud, configuring Docker to run a C++ application, and managing the containerized environment. The goal is to parallelize the execution of the C++ code and ensure it runs efficiently in a Docker container.

## Prerequisites

Before you begin, make sure you have the following installed:

- **Virtual Machine (VM)**: You can use any cloud provider to set up a VM. We used a cloud-based VM for this project.
- **Docker**: Ensure Docker is installed on your VM. You can check if Docker is installed by running `docker --version` in the terminal.
- **Ubuntu**: The project assumes you're using an Ubuntu-based system for the VM.
- **SSH Key**: Set up an SSH key for secure remote access to the VM.

## Steps to Set Up the Project

### 1. Set Up the Virtual Machine
- Create a VM on your preferred cloud provider (e.g., AWS, Google Cloud, Azure).
- Ensure the VM has at least **2 CPUs** and **8GB RAM**.
- Set up an SSH key for secure access to the VM.

### 2. Install Docker on the VM
- Once the VM is set up, install Docker by running the following commands:
  ```bash
  sudo apt-get update
  sudo apt-get install docker.io
  ```
- Verify the installation by running `docker --version`.

### 3. Create a Dockerfile
- Create a `Dockerfile` in your project directory. This file contains the instructions to build the Docker image for your C++ application.
- Example `Dockerfile`:
  ```Dockerfile
  FROM ubuntu:latest
  RUN apt-get update && apt-get install -y g++
  COPY . /app
  WORKDIR /app
  CMD ["g++", "your_cpp_file.cpp", "-o", "output"]
  ```

### 4. Build the Docker Image
- Build the Docker image using the following command:
  ```bash
  docker build -t your_image_name .
  ```
- This will create an immutable Docker image that contains your C++ application.

### 5. Run the Docker Container
- Once the image is built, you can run the container using:
  ```bash
  docker run -it your_image_name
  ```
- This will start the container and execute your C++ code.

### 6. Parallelize the C++ Code
- The project involves parallelizing the C++ code to improve performance. You can use libraries like OpenMP or MPI to achieve this.
- After parallelizing the code, rebuild the Docker image and run the container again to test the changes.

### 7. Use Multiple Docker Containers
- If your application requires multiple containers (e.g., for different parts of the code), you can create separate Docker images for each part.
- Run each container independently to test the parallel execution.

## Important Notes

- **Docker Images are Immutable**: Once a Docker image is created, you cannot modify it. If you need to make changes, you must rebuild the image.
- **Isolation**: When running in a Docker container, you are isolated from the host system. You cannot access host system files directly from the container.
- **SSH Key Security**: Ensure your SSH key is securely stored and not shared publicly.

## Running the Application

To run the application, follow these steps:

1. Clone this repository to your VM.
2. Navigate to the project directory.
3. Build the Docker image using the provided `Dockerfile`.
4. Run the Docker container to execute the C++ code.
5. Check the output to ensure the application is running as expected.

## Conclusion

This project demonstrates how to set up a C++ application in a Docker container and parallelize its execution. By following the steps outlined in this README, you should be able to replicate the setup and run the application on your local machine or cloud environment.

If you have any questions or run into issues, feel free to open an issue on this repository. Happy coding!

---
