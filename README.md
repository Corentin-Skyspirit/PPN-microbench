# PPN-microbench

A portable microbenchmarking tool for compute node caracterisation.

## Architecture support

This tool is developed and tested for **64 bit ARM and x86**

## Benchmarks

Bellow is a list of currently implemented benchmarks, more info in the [wiki](https://github.com/ppn-microbench/ppn-microbench/wiki).

| Benchmark | Description |
|---|---|
| CPU frequency | CPU clock frequency in single and multi-core loads |
| CPU OPS | Max. operation per seconds for 32, 64 bit and vector integers and floats |
| Memory latency | Latency of cache and ram access |

## Running

The simplest way to run the application is from the `run` script. Upon executing it, a pdf will be output to `report/out/` containing results for all benchmarks.
It is possible to run individual / groups of benchmarks by passing arguments to the script or application.

The `run` script executes the following steps:
 - building the application
 - running the application
 - creating a python vitrual environment if none exists
 - creating the pdf report from the application output

If you have an earlier python version, you might need to install `python<version>-venv` through your package manager.

### Arguments

| argument | alias | description |
|---|---|---|
| `--debug` | `-d` | Sets logging level to debug, showing extra information on screen |
| `--output` | `-o` | Sets output file name and location. can be either a directory ore a full file path |
| `--cpu_frequency` |  | Adds the CPU frequency benchmark for execution |
| `--ops` |  | Adds the CPU OPS benchmark for execution |
| `--memory_latency` |  | Adds the Memory latency benchmark for execution |
| `--cpu` |  | Adds all cpu-related benchmarks to the pool. (CPU Frequency, CPU OPS) |
| `--mem` |  | Adds all memory-related benchmarks to the pool. (Memory latency) |

If no benchmark is explicitly specified, all of them will be run.

## Requirements and libraries

The only requirement to run the tool is `cmake 3.25`. The following libraries will be downloaded and compiled at build time:
 - [nlohmann-json](https://github.com/nlohmann/json)
 - [spdlog](https://github.com/gabime/spdlog)
 - [CLI11](https://github.com/CLIUtils/CLI11)