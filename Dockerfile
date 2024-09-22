# Use Ubuntu 22.04 as the base image
FROM ubuntu:22.04

# Install basic dependencies
RUN apt-get update && apt-get install -y \
    build-essential \
    cmake \
    ninja-build \
    python3 \
    git \
    curl \
    wget \
    lsb-release \
    software-properties-common \
    ca-certificates \
    pkg-config

# Remove any existing CMake installation
RUN apt-get remove --purge cmake -y

# Set working directory to /tmp
WORKDIR /tmp

# Download CMake 3.30.3 from the official GitHub release
RUN wget https://github.com/Kitware/CMake/releases/download/v3.30.3/cmake-3.30.3-linux-x86_64.sh

# Make the downloaded .sh file executable
RUN chmod +x cmake-3.30.3-linux-x86_64.sh

# Install CMake 3.30.3 to /usr (default system directory)
RUN ./cmake-3.30.3-linux-x86_64.sh --prefix=/usr --skip-license

# Verify the installation
RUN cmake --version

# Add the official LLVM repository for Ubuntu 22.04 (Jammy) to get LLVM 19
RUN wget https://apt.llvm.org/llvm-snapshot.gpg.key -O - | apt-key add -
RUN add-apt-repository "deb http://apt.llvm.org/jammy/ llvm-toolchain-jammy-19 main"

# Add PPA for GCC 13
RUN add-apt-repository ppa:ubuntu-toolchain-r/test

# Update and install LLVM 19 (clang, lldb, etc.), GCC 13.x, and GDB 14.2
RUN apt-get update && apt-get install -y \
    llvm-19 \
    clang-19 \
    lldb-19 \
    lld-19 \
    clang-tools-19 \
    libclang-19-dev \
    clangd-19 \
    libomp-19-dev \
    libc++-19-dev \
    libc++abi-19-dev \
    gcc-13 g++-13 \
    gdb

# Set the default GCC, G++, Clang, and LLDB versions
RUN update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-13 100 \
 && update-alternatives --install /usr/bin/g++ g++ /usr/bin/g++-13 100 \
 && update-alternatives --install /usr/bin/clang clang /usr/bin/clang-19 100 \
 && update-alternatives --install /usr/bin/clang++ clang++ /usr/bin/clang++-19 100 \
 && update-alternatives --install /usr/bin/lldb lldb /usr/bin/lldb-19 100

# Verify the installations
RUN clang --version && lldb --version && gcc --version && g++ --version && gdb --version


# --- Install Libraries ---

# Boost (installed via apt-get)
RUN apt-get install -y libboost-all-dev

# fmt (via package manager)
RUN apt-get install -y libfmt-dev

# Abseil (from source)
WORKDIR /tmp
RUN git clone https://github.com/abseil/abseil-cpp.git && \
    cd abseil-cpp && \
    mkdir build && cd build && \
    cmake -DCMAKE_CXX_STANDARD=20 -DCMAKE_BUILD_TYPE=Release .. && \
    make -j$(nproc) && \
    make install && \
    rm -rf /tmp/abseil-cpp

# GoogleTest (from source)
WORKDIR /tmp
RUN git clone https://github.com/google/googletest.git && \
    cd googletest && \
    mkdir build && cd build && \
    cmake .. && \
    make -j$(nproc) && \
    make install && \
    rm -rf /tmp/googletest

# TBB (via apt-get)
RUN apt-get install -y libtbb-dev

# Eigen (from source)
WORKDIR /tmp
RUN git clone https://gitlab.com/libeigen/eigen.git && \
    cd eigen && \
    mkdir build && cd build && \
    cmake .. && \
    make install && \
    rm -rf /tmp/eigen

# Protobuf (from source)
WORKDIR /tmp
RUN git clone https://github.com/protocolbuffers/protobuf.git && \
    cd protobuf && \
    git submodule update --init --recursive && \
    mkdir build && cd build && \
    cmake -DCMAKE_BUILD_TYPE=Release .. && \
    make -j$(nproc) && \
    make install && \
    ldconfig && \
    rm -rf /tmp/protobuf

# spdlog (via apt-get)
RUN apt-get install -y libspdlog-dev

# Poco (via apt-get)
RUN apt-get install -y libpoco-dev

# SQLite (via apt-get)
RUN apt-get install -y libsqlite3-dev

# SFML (via apt-get)
RUN apt-get install -y libsfml-dev

# Clean up unnecessary files from apt-get installations to reduce image size
RUN apt-get clean && rm -rf /var/lib/apt/lists/*

# Set the working directory for your project
WORKDIR /workspace

# Default command to start the container
CMD ["/bin/bash"]