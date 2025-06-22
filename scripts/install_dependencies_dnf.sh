#!/bin/bash

# Exit immediately if a command exits with a non-zero status.
set -e

echo "Updating package lists..."
sudo dnf check-update # Or 'sudo dnf upgrade --refresh' for full update

echo "Installing required development libraries for SDL_mixer and other dependencies..."
# Note: Package names might differ slightly between distributions
sudo dnf install -y \
    libopusfile-devel \
    libxmp-devel \
    libmodplug-devel \
    fluidsynth-devel \
    wavpack-devel \
    libogg-devel \
    libvorbis-devel \
    flac-devel \
    mpg123-devel \
    libmikmod-devel \
    libgme-devel \
    SDL2-devel \
    SDL2_mixer-devel \
    pkgconf \
    @development-tools # Installs common build tools like gcc, make

echo "All specified dependencies should now be installed."