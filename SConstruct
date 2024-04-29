#!/bin/env python
# SConstruct

# Import the SCons module
import os

# Set the path to MinGW-w64 compiler
MINGW_PATH = '/usr/bin/x86_64-w64-mingw32-'  # Adjust this path as per your system configuration

# Define the environment
env = Environment()

# Set the compiler to MinGW-w64
env['CC'] = MINGW_PATH + 'g++'
env['CXX'] = MINGW_PATH + 'g++'

env.Append(CCFLAGS=['-Ofast', '-Wno-narrowing'])
env.Append(CXXFLAGS=['-Ofast', '-Wno-narrowing'])

# Define source files
engine_source = 'engine.cpp'
dll_source = 'vlibdmk.cpp'
header_files = ['vlibdmk.h']  # Add header files here

# Define the target executable
target_exe = 'engine.exe'  # Windows executable extension

# Define the target DLL
target_dll = 'vlibdmk.dll'  # Windows DLL extension

# Create a build/bin directory if it doesn't exist
bin_dir = Dir('build/bin')
if not os.path.exists(bin_dir.abspath):
    os.makedirs(bin_dir.abspath)

# Build the DLL
dll = env.SharedLibrary(target=bin_dir.File(target_dll), source=dll_source)

# Build the executable
exe = env.Program(target=bin_dir.File(target_exe), source=engine_source, LIBS=['vlibdmk', 'raylib'], LIBPATH=[bin_dir])

# Set the default target to the executable
# Get the target parameter from the command line
if 'target' in ARGUMENTS:
    target = ARGUMENTS['target']
else:
    print("Error: No target specified. Please specify 'engine' or 'vlibdmk' as the target.")
    Exit(1)

# Build the specified target
if target == 'engine':
    # Build the executable
    Default(exe)
elif target == 'vlibdmk':
    # Build the DLL
    Default(dll)
else:
    print("Error: Unknown target. Please specify 'engine' or 'vlibdmk' as the target.")
    Exit(1)

# Copy header files to the include directory
include_dir = Dir('build/include')
for header in header_files:
    env.Install(include_dir, header)
