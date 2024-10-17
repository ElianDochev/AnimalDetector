# Animelody - Detecting and Identifying Animal Sounds Using a Drone

This project, **Animelody - Detecting and Identifying Animal Sounds**, is designed to detect and classify animal sounds using a drone. It employs machine learning (ML) models to accurately identify different animals from their sounds. The system is primarily intended to be used with an ESP32 microcontroller, integrated with sound classification models trained on Edge Impulse, and deployable via a drone for real-time monitoring and identification of animal sounds.

## Team Members

- **Charles Fassel-ashley**
- **Eliyan Dochev**
- **Oscar Frank**
- **Théotime Schmeltz**
- **Thomas Fiancette**
- **Vlad Zaharia**
- **Younès Boufrioua**

## Repository Structure

The repository is organized into several directories and files to support the different components of this AIOT project:

- **./UnsortedData**:  
  This folder contains the raw data that has been directly imported from the Edge Impulse project. The data includes various animal sounds used to train the detection model.

- **./Data**:  
  This directory stores the sorted and pre-processed data that has been extracted and organized by the `extract.py` script. These data sets are used for further refinement and training of the machine learning models.

- **./DetectionModel**:  
  Inside this folder, you will find the machine learning model that powers the animal sound detection and classification functionality. The model has been exported from Edge Impulse as a C++ library for integration with the ESP32 microcontroller.

- **./DetectionModelCompiled**:  
  This directory contains the compiled version of the machine learning model, including the C++ code and binary files ready to be flashed onto a physical device like the ESP32. The model in this folder is the more accurate version of the two models developed.

- **server.py**:  
  The `server.py` script acts as a simulation for sound sensors, supplying .wav files for animal sounds. Since Wokwi (the simulation environment) does not support sound input, this script serves as a substitute. It exposes two API endpoints:

  - `/random`: Returns a random animal sound file.
  - `/specific/animal`: Returns the sound of a specific animal (e.g., bird, cat, cow, dog, lion, sheep).

  The only external package required for this script is **Flask**.

- **arduino.cpp**:
  This file contains the Arduino code that runs on the ESP32 microcontroller. It integrates with the detection model and uses the sound files provided by `server.py` to detect and classify the sounds. You can also find the same code in the Wokwi simulation project.

## Links to Models and Simulations

This project uses two machine learning models hosted on Edge Impulse:

- **Lighter Model (Less Accurate):**
  [Link to Lighter Model on Edge Impulse](https://studio.edgeimpulse.com/public/534296/live)

- **More Accurate Model (Used in C++ and Compiled Versions):**
  [Link to More Accurate Model on Edge Impulse](https://studio.edgeimpulse.com/public/536362/live)

To simulate the project, you can find it on Wokwi here:
[Link to Wokwi Project](https://wokwi.com/projects/411820177457844225)

FIY: The Wokwi project is a simulation of the ESP32 microcontroller running the Arduino code. It uses the `server.py` script to fetch sound files for detection and classification. Remember to port forward the server to the Wokwi project to enable sound input.
