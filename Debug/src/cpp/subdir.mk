################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/cpp/archivate.cpp \
../src/cpp/checkrus.cpp \
../src/cpp/dbworker.cpp \
../src/cpp/filework.cpp \
../src/cpp/index.cpp \
../src/cpp/main.cpp \
../src/cpp/parser.cpp \
../src/cpp/posting.cpp \
../src/cpp/query.cpp \
../src/cpp/ranking.cpp \
../src/cpp/statistics.cpp 

OBJS += \
./src/cpp/archivate.o \
./src/cpp/checkrus.o \
./src/cpp/dbworker.o \
./src/cpp/filework.o \
./src/cpp/index.o \
./src/cpp/main.o \
./src/cpp/parser.o \
./src/cpp/posting.o \
./src/cpp/query.o \
./src/cpp/ranking.o \
./src/cpp/statistics.o 

CPP_DEPS += \
./src/cpp/archivate.d \
./src/cpp/checkrus.d \
./src/cpp/dbworker.d \
./src/cpp/filework.d \
./src/cpp/index.d \
./src/cpp/main.d \
./src/cpp/parser.d \
./src/cpp/posting.d \
./src/cpp/query.d \
./src/cpp/ranking.d \
./src/cpp/statistics.d 


# Each subdirectory must supply rules for building sources it contributes
src/cpp/%.o: ../src/cpp/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


