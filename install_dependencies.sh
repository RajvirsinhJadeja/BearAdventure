#!/bin/bash

echo "Updating package list..."
sudo apt-get update

echo "Installing dependencies..."
sudo apt-get install -y \
    cmake \
    libopenal-dev \
    libvorbis-dev \
    libogg-dev \
    libxrandr-dev \
    libudev-dev \
    libfreetype6-dev \
    libjpeg-dev \
    libsndfile1-dev \
    libxcursor-dev \
    libgl1-mesa-dev

echo "Dependencies installed."

