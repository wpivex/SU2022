# VEXcode makefile 2019_03_26_01

# show compiler output
VERBOSE = 0
CXXFLAGS= -std=c++17 -O3 # optimize at O2 level

# include toolchain options
include vex/mkenv.mk

# location of the project source cpp and c files
SRC_C  = $(wildcard src/*.cpp) 
SRC_C += $(wildcard include/*.cpp)
SRC_C += $(wildcard include/**/*.cpp)
SRC_C += $(wildcard include/**/**/*.cpp)
SRC_C += $(wildcard include/**/**/**/*.cpp)



OBJ = $(addprefix $(BUILD)/, $(addsuffix .o, $(basename $(SRC_C))) )

# location of include files that c and cpp files depend on
SRC_H  += $(wildcard include/**/**/**/**/*.h)
SRC_H  += $(wildcard include/**/**/**/*.h)
SRC_H  += $(wildcard include/**/**/*.h)
SRC_H  += $(wildcard include/**/*.h)
SRC_H  += $(wildcard include/*.h)

# additional dependancies
SRC_A  = makefile

# project header file locations
INC_F  = include

# build targets
all: $(BUILD)/$(PROJECT).bin

# include build rules
include vex/mkrules.mk
