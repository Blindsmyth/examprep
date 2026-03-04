# Lightweight image for practicing GDB (and compiling C) on M1 Mac
FROM ubuntu:22.04

RUN apt-get update && apt-get install -y --no-install-recommends \
    build-essential \
    gdb \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /workspace

# Run bash so you can compile and run gdb
CMD ["bash"]
