# PPN-microbench

A (hopefully) portable microbenchmarking tool for compute node caracterisation.

## Requirements

| lib | version | comment |
|---|---|---|
| nlohmann-json3 | 3.10 | https://github.com/nlohmann/json |
| cmake | >=3.35 | |

## Installing

```sh
git clone git@github.com:PPN-microbench/PPN-microbench.git
mkdir PPN-microbench/build
cd PPN-microbench/build
cmake .. && make
```

## Context

The `context` class contains all system informations relevant to the  benchmarks, or needed for the final reports. It includes:

- [ ] Cpu architecture
- [ ] Word size
- [ ] Core count
- [ ] Hyperthreading
- [ ] AVX capabilities
- [ ] Total RAM
- [ ] L3 cache
- [ ] L2 cache
- [ ] L1 cache

as well as other general purpose information such as executed bench set, date/time...