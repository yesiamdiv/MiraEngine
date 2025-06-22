#!/bin/bash

# Exit immediately if a command exits with a non-zero status.
set -e

echo "Updating package lists..."
sudo apt update

echo "Installing required development libraries for SDL_mixer and other dependencies..."
sudo apt install -y \
    libopusfile-dev \
    libxmp-dev \
    libmodplug-dev \
    libfluidsynth-dev \
    libwavpack-dev \
    libogg-dev \
    libvorbis-dev \
    libvorbisfile-dev \
    libflac-dev \
    libmpg123-dev \
    libmikmod-dev \
    libgme-dev \
    libsdl2-dev \
    libsdl2-mixer-dev \
    pkg-config \
    build-essential

echo "All specified dependencies should now be installed."