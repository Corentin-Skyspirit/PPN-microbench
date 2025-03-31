# PPN-microbench

A portable microbenchmarking tool for compute node caracterisation.

# Architecture support

This tool is developed and tested for **64 bit ARM and x86**

# Benchmarks

Bellow is a list of currently implemented benchmarks, more info in the [wiki](https://github.com/ppn-microbench/ppn-microbench/wiki).

| Benchmark | Description |
|---|---|
| CPU frequency | CPU clock frequency in single and multi-core loads |
| CPU OPS | Max. operation per seconds for 32, 64 bit and vector integers and floats |
| Core to core latency | Latency of core to core communications |
| Cache latency | Latency of cache and ram access |

# Running

## Via the run script

The simplest way to run the application is from the `run` script. Upon executing it, a pdf will be output to `report/out/` containing results for all benchmarks.

The `run` script executes the following steps:
 - building the application
 - running the application
 - creating a python vitrual environment if none exists
 - creating the pdf report from the application output

If you have an earlier version of python, you might need to install `python<version>-venv` through your package manager.

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

You can now simply run the executable. Note that by default, the json will be output to `./`.

### Report generation

To generate the pdf report, move into `report/`. The python expects to find the json results in `report/out.json`.

`Mathplotlib` is the only required python package. `weasyprint` is also needed to convert an html file into the final pdf, but it is not strictly required. You can simply run `pip install -r requirements.txt` to install all dependencies.

Finally, running the python is as easy as `python3 main.py`

## Arguments

It is possible to run individual / groups of benchmarks by passing arguments to the script or application.

| argument           | alias | description                                                                       |
| ------------------ | ----- | --------------------------------------------------------------------------------- |
| `--debug`          | `-d`  | Sets logging level to debug, showing extra information on screen                  |
| `--output`         | `-o`  | Sets output file name and location. can be either a directory or a full file path |
| `--cpu-frequency`  |       | Adds the CPU frequency benchmark for execution                                    |
| `--ops`            |       | Adds the CPU OPS benchmark for execution                                          |
| `--c2c`            |       | Adds the CPU core to core latency benchmark for execution                         |
| `--cache-latency`  |       | Adds the Memory latency benchmark for execution                                   |
| `--cpu`            |       | Adds all cpu-related benchmarks to the pool. (CPU Frequency, CPU OPS, C2C lat.)   |
| `--mem`            |       | Adds all memory-related benchmarks to the pool. (Memory latency)                  |

If no benchmark is explicitly specified, all of them will be run.

# Requirements and libraries

The only requirement to run the tool is `cmake 3.25`. The following libraries will be downloaded and compiled at build time:
 - [nlohmann-json](https://github.com/nlohmann/json)
 - [spdlog](https://github.com/gabime/spdlog)
 - [CLI11](https://github.com/CLIUtils/CLI11)