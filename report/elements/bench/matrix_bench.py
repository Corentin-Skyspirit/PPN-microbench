from elements.bench.base import AbstractBench

import json
import matplotlib.pyplot as plt
import numpy as np
import os

class Matrix_Bench(AbstractBench):
    def __init__(self, obj, bench_obj):
        self.obj = obj  # The complete JSON object
        self.bench_obj = bench_obj  # The specific benchmark object

    def to_html(self):
        # Generate the plot and return the HTML content
        self.gen_images()
        wd = os.getcwd()
        header = "<h2 id='Matrix_Bench'>Matrix Multiplication DGEMM</h2>"
        imgs = f"<img src='{wd}/out/matrix_benchmark_plot.png'/>"
        p = "<p>This benchmark evaluates the performance of dense matrix multiplication using Eigen. Below is the GFLOPS achieved for various matrix sizes.</p>"
        return header + imgs + p

    def gen_images(self):
        # Access data directly from self.obj
        # self.bench_obj is a dictionary containing the benchmark results
        results = self.bench_obj["results"]
        summary = self.bench_obj["summary"]
    
        sizes = [entry["size"] for entry in results]
        gflops = [entry["Gflops"] for entry in results]
   
        # Create the plot
        plt.figure(figsize=(10, 6))
        plt.plot(sizes, gflops, marker='o', color='blue', label="GFLOPS (per size)")
        plt.ylim(0)
            
        # Add lines for max and average GFLOPS
        plt.axhline(summary["gflops_max"], color='red', linestyle='--', label=f"Max GFLOPS: {summary['gflops_max']:.1f}")
        plt.axhline(summary["gflops_avg"], color='green', linestyle='--', label=f"Average GFLOPS: {summary['gflops_avg']:.1f}")
     
        # Add annotations on the points
        for x, y in zip(sizes, gflops):
            plt.text(x, y + 0.5, f"{y:.1f}", ha='center', fontsize=9)
        
        # Calculate the error (e.g., ±5% of GFLOPS values)
        error = [0.05 * g for g in gflops]

        # Plot the error band
        plt.fill_between(
            sizes,
            [g - e for g, e in zip(gflops, error)],  # Lower values
            [g + e for g, e in zip(gflops, error)],  # Upper values
            color='cyan',
            alpha=0.2,
            label='Error Band (±5%)',
            edgecolor='blue',
            linewidth=2,  
        )        

        # Format the plot
        plt.title("Matrix Multiplication performance (GFLOPS)")
        plt.xlabel("Matrix Size (N x N)")
        plt.ylabel("GFLOPS")
        plt.grid(True)
        plt.legend()
        plt.tight_layout()
    
        # Create the output directory and save the plot
        os.makedirs("out", exist_ok=True)
        plt.savefig("out/matrix_benchmark_plot.png", dpi=300)
        plt.close()

    def get_index(self):
        # Return the index entry for the Matrix Multiplication section
        return "<li><a href='#Matrix_Bench'>Matrix Multiplication DGEMM</a></li>"
