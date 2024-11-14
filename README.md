# PPN-microbench

A (hopefully) portable microbenchmarking tool for compute node caracterisation.

# Requirements

| lib | version | comment |
|---|---|---|
| nlohmann-json3 | 3.10 | https://github.com/nlohmann/json |
| cmake | >=3.35 | |

# Installing

```sh
git clone git@github.com:PPN-microbench/PPN-microbench.git
mkdir PPN-microbench/build
cd PPN-microbench/build
cmake .. && make
```