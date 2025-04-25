# PPN-microbench

A portable microbenchmarking tool for compute node caracterisation.

# Architecture support

This tool is (currently) developed and tested for **64-bit Arm and x86 architectures.**

# Benchmarks

Below is a list of currently implemented benchmarks; detailed information is available in the [wiki](https://github.com/ppn-microbench/ppn-microbench/wiki).

| Benchmark            | Description                                                                                       |
| -------------------- | ------------------------------------------------------------------------------------------------- |
| CPU frequency        | CPU clock frequency in single- and multi-core light workloads                                     |
| CPU OPS              | Peak integer & floating-point operations per second for 32-, 64-bit and SIMD arithmetic workloads |
| Core-to-core latency | Latency of core-to-core communications                                                            |
| Load test            | CPU cock frequency in single- and multi-core heavy workloads                                      |
| Cache latency        | Latency of different cache level accesses                                                         |
| Memory bandwidth     | Single- and multi-core memory latency with `memcpy`                                               |
| Stream               | Stream-like benchmark, measures memory bandwidth in multiple scenarios                            |

# Running

## Via the run script

The simplest way to run the application is from the `run` script. Upon executing it, a pdf will be output to `report/out/` containing results for all benchmarks.

The `run` script executes the following steps:
1. Build the application
2. Run the application
3. Creat a python vitrual environment if none exists
4. Generate a PDF report from the application output

If you have an earlier version of Python, you might need to install `python<version>-venv` through your package manager.

## Manually

### Building

In order to build the application, run the following commands:

```bash
# -G Ninja drastically improves build times
cmake -B build [-G Ninja]
cmake --build build/
```

The executable will be located in `build/main/`.

### Running

You can now simply run the executable. Note that by default, the JSON will be dumped to `./`.

### Report generation

To generate the PDF report, move into `report/`. The Python script expects to find the JSON results in `report/out.json`.

`mathplotlib` and `weasypring` are the only required Python packages. You can install both dependencies by running `pip install -r requirements.txt`.

Finally, running the Python script is as easy as `python3 main.py`

## Arguments

It is possible to run individual/groups of benchmarks by passing arguments directly to the Python script or C++ application:

| argument           | alias | description                                                                              |
| ------------------ | ----- | ---------------------------------------------------------------------------------------- |
| `--debug`          | `-d`  | Sets logging level to debug, showing extra information on screen                         |
| `--output`         | `-o`  | Sets output file name and location. can be either a directory or a full file path        |
| `--cpu-frequency`  |       | Adds the CPU frequency benchmark for execution                                           |
| `--ops`            |       | Adds the CPU OPS benchmark for execution                                                 |
| `--c2c`            |       | Adds the CPU core to core latency benchmark for execution                                |
| `--load-test`      |       | Adds the CPU load test benchmark for execution                                           |
| `--cache-latency`  |       | Adds the Cache latency benchmark for execution                                           |
| `--mem-bandwidth`  |       | Adds the memcpy bandwidth benchmark for execution                                        |
| `--stream`         |       | Adds the Stream benchmark for execution                                                  |
| `--cpu`            |       | Adds all cpu-related benchmarks to the pool. (CPU Freq. CPU OPS, C2C lat., Load freq.)   |
| `--mem`            |       | Adds all memory-related benchmarks to the pool. (Cache latency, Stream)                  |

If no benchmark is explicitly specified, all of them will be run.

# Requirements and libraries

The only requirement to run the tool is `cmake 3.25`. The following libraries will be downloaded and compiled at build time:
 - [nlohmann-json](https://github.com/nlohmann/json)
 - [spdlog](https://github.com/gabime/spdlog)
 - [CLI11](https://github.com/CLIUtils/CLI11)