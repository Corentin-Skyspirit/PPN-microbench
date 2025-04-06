from elements.bench.base import AbstractBench

import json
import matplotlib.pyplot as plt
import numpy as np
import os

class Matrix_Bench(AbstractBench):
    def __init__(self, obj, bench_obj):
        self.obj = obj
        self.bench_obj = bench_obj

    def to_html(self):
        self.gen_images()
        wd = os.getcwd()
        header = "<h2 id='Matrix_Bench'>Matrix Bench</h2>"
        imgs = f"<img src='{wd}/out/matrix_benchmark_plot.png'/>"
        p = "<p>Matrix benchmark results for DGEMM.</p>"
        return header + imgs + p

    def gen_images(self):
        # Load data
        data = self.obj
        sizes = np.array(data["sizes"])
        gflops = np.array(data["gflops"])
        
        

# Load JSON data
with open("matrix_dgemm_results.json", "r") as f:
    data = json.load(f)

results = data["results"]
summary = data["summary"]

sizes = [entry["size"] for entry in results]
gflops = [entry["gflops"] for entry in results]

# Plot the results
plt.figure(figsize=(10, 6))
plt.plot(sizes, gflops, marker='o', label="GFLOPS (by size)")
plt.axhline(summary["gflops_max"], color='r', linestyle='--', label=f"Max: {summary['gflops_max']:.2f} GFLOPS")
plt.axhline(summary["gflops_avg"], color='g', linestyle='--', label=f"Average: {summary['gflops_avg']:.2f} GFLOPS")

# Formatting
plt.title("DGEMM Benchmark - Performance in GFLOPS")
plt.xlabel("Matrix size (N x N)")
plt.ylabel("GFLOPS")
plt.grid(True)
plt.legend()
plt.tight_layout()

# Save the plot
os.makedirs("out", exist_ok=True)
plt.savefig("out/matrix_benchmark_plot.png")
plt.close()

# Show the plot        
plt.show()

def get_index(self):
    return {
        "title": "Matrix Bench",
        "id": "Matrix_Bench",
        "description": "Matrix benchmark results for DGEMM.",
        "icon": "matrix_bench_icon.png"
    }