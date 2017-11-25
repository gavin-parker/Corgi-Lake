cmake_minimum_required(VERSION 3.8)
project(Advanced_Architecture)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES
        Simulator/Simulator/src/components/alu.cpp
        Simulator/Simulator/include/alu.h
        Simulator/Simulator/src/testing/assembler.cpp
        Simulator/Simulator/include/assembler.h
        Simulator/Simulator/include/bank.h
        Simulator/Simulator/src/testing/benchmark_runner.cpp
        Simulator/Simulator/include/benchmark_runner.h
        Simulator/Simulator/src/modules/branch_predictor.cpp
        Simulator/Simulator/include/branch_predictor.h
        Simulator/Simulator/src/components/branch_unit.cpp
        Simulator/Simulator/include/branch_unit.h
        Simulator/Simulator/src/modules/buffer.cpp
        Simulator/Simulator/include/buffer.h
        Simulator/Simulator/src/components/component.cpp
        Simulator/Simulator/include/component.h
        Simulator/Simulator/include/data.h
        Simulator/Simulator/src/components/fetcher.cpp
        Simulator/Simulator/include/fetcher.h
        Simulator/Simulator/src/data_model/instruction.cpp
        Simulator/Simulator/include/instruction.h
        Simulator/Simulator/src/components/load_store.cpp
        Simulator/Simulator/include/load_store.h
        Simulator/Simulator/src/components/memory.cpp
        Simulator/Simulator/include/memory.h
        Simulator/Simulator/src/data_model/opcode.cpp
        Simulator/Simulator/include/opcode.h
        Simulator/Simulator/include/opcode_settings.h
        Simulator/Simulator/include/operation.h
        Simulator/Simulator/include/register_file.h
        Simulator/Simulator/src/modules/RegisterFile.cpp
        Simulator/Simulator/src/data_model/result.cpp
        Simulator/Simulator/include/result.h
        Simulator/Simulator/src/Simulator.cpp
        Simulator/Simulator/include/simulator.h
        Simulator/Simulator/include/simulator_state.h
        Simulator/Simulator/include/state.h
        Simulator/Simulator/src/stdafx.cpp
        Simulator/Simulator/include/stdafx.h
        Simulator/Simulator/include/targetver.h Simulator/Simulator/src/components/bank.cpp)

add_executable(Advanced_Architecture ${SOURCE_FILES})