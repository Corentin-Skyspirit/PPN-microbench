from elements.bench.base import AbstractBench

import matplotlib.pyplot as plt
from matplotlib.ticker import FuncFormatter
import numpy as np
import os.path

class MemBandwidth(AbstractBench):
    def __init__(self, obj, bench_obj):
        self.obj = obj
        self.bench_obj = bench_obj

    def to_html(self):
        self.gen_images()
        wd = os.getcwd()

        header = "<h2 id='MEMBandwidth'>Memory Bandwidth</h2>"

        imgs = f"<img src='{wd}/out/mem_bandwidth.png'/>"
        
        return header + imgs

    def gen_images(self):
        data = self.bench_obj["results"]

        runs = data["runs"]
        
        sizes = np.array(data["sizes"])
        reps = np.array(data["reps"])
        times = np.array(data["times"])

        avg = np.sum(times, axis=0) / runs
    
        x = sizes / 1024
        y = sizes * reps / avg

        _error = []
        for a in times:
            _error.append(sizes * reps / a)
        error = np.std(_error, axis=0)

        plt.figure(figsize=(10, 6))
        plt.errorbar(x, y, error, marker=".", ecolor="grey")

        plt.xscale("log", base=2)
        plt.yscale("log", base=2)
        # matfloplib
        plt.gca().yaxis.set_major_formatter(FuncFormatter(lambda a, b: a))

        plt.xlabel("Buffer Size (KiB)")
        plt.ylabel("Bandwidth (GiB/s)")
        plt.title("Memory Bandwidth")
        plt.grid(True, which="both", ls="--")

        caches = [
            int(self.obj["meta"]["mem_info"]["l1d"] / 1024),
            int(self.obj["meta"]["mem_info"]["l2"] / 1024),
            int(self.obj["meta"]["mem_info"]["l3"] / 1024)
        ]

        plt.axvline(x=caches[0], color='green', linestyle='--', label=f'L1 size: {caches[0]} KiB')
        plt.axvline(x=caches[1], color='green', linestyle='--', label=f'L2 size: {caches[1]} KiB')
        plt.axvline(x=caches[2], color='green', linestyle='--', label=f'L3 size: {caches[2]} KiB')

        plt.legend()
        plt.savefig("out/mem_bandwidth.png")
        plt.clf()

    def get_index(self):
        return "<li><a href='#MEMBandwidth'>Memory Bandwidth</a></li>"
