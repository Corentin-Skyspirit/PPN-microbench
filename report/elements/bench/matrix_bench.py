from elements.bench.base import AbstractBench

import matplotlib.pyplot as plt
import os
import subprocess
import sysconfig

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

        # Compute Rpeak and get summary
        rpeak, flops_unit, cores, freq = self.compute_rpeak()
        gflops_max = self.bench_obj["summary"]["gflops_max"]

        # Calculate efficiency
        efficiency = self.efficiency()
       

        # Generate HTML table comparing theoretical and experimental
        table = f"""
        <h3>Performance Comparison</h3>
        <table border='1' style='border-collapse: collapse; text-align: center;'>
            <tr><th>Metric</th><th>Value</th></tr>
            <tr><td>Theoretical Rpeak</td><td>{rpeak:.2f} GFLOPS</td></tr>
            <tr><td>Experimental RMax</td><td>{gflops_max:.2f} GFLOPS</td></tr>
            <tr><td>Efficiency</td><td>{efficiency:.2f} %</td></tr>
        </table>
        """

        return header + imgs + p + table

    def gen_images(self):
        results = self.bench_obj["results"]
        summary = self.bench_obj["summary"]

        sizes = [entry["size"] for entry in results]
        gflops = [entry["Gflops"] for entry in results]

        # Create the plot
        plt.figure(figsize=(10, 6))
        plt.plot(sizes, gflops, marker='o', color='blue', label="GFLOPS (per size)")
        plt.ylim(0, self.compute_rpeak()[0] * 1.1)
        plt.axhline(summary["gflops_max"], color='red', linestyle='--', label=f"RMax : {summary['gflops_max']:.1f} GFLOPS")
        plt.axhline(self.compute_rpeak()[0], color='orange', linestyle='--', label=f"Rpeak: {self.compute_rpeak()[0]:.1f} GFLOPS")

        error_Gflops = self.bench_obj["summary"].get("error_Gflops", [0.05 * g for g in gflops])
        for x, y, e in zip(sizes, gflops, error_Gflops):
            plt.text(x, y + e + 0.5, f"{y:.1f}", ha='center', fontsize=9)

        plt.fill_between(
            sizes,
            [g - e for g, e in zip(gflops, error_Gflops)],
            [g + e for g, e in zip(gflops, error_Gflops)],
            color='cyan',
            alpha=0.2,
            label='Error Band',
            edgecolor='blue',
            linewidth=2,
        )

        plt.title("Matrix Multiplication performance (GFLOPS)")
        plt.xlabel("Matrix Size (N x N)")
        plt.ylabel("GFLOPS")
        plt.grid(True)
        plt.legend()
        plt.tight_layout()
        os.makedirs("out", exist_ok=True)
        plt.savefig("out/matrix_benchmark_plot.png", dpi=300)
        plt.close()

    def compute_rpeak(self):
        
        data = self.obj
        
        cores_per_socket = data["meta"]["cpu_info"]["cpus"]
        sockets = data["meta"]["cpu_info"]["sockets"]

        num_cores = cores_per_socket * sockets

        max_mhz = data["meta"]["cpu_info"]["max_mhz"] 
        clock_ghz = max_mhz / 1000


        flags = sysconfig.get_config_var("CFLAGS") #prenddre les flages du json plutot
        flags = flags.split() if flags else []

        if "avx512f" in flags:
            flops_per_cycle_per_core = 32
        elif "avx2" in flags:
            flops_per_cycle_per_core = 16
        elif "avx" in flags:
            flops_per_cycle_per_core = 8
        else:
            flops_per_cycle_per_core = 4

        rpeak = num_cores * clock_ghz * flops_per_cycle_per_core

        return rpeak, flops_per_cycle_per_core, num_cores, clock_ghz

    def efficiency(self):
        data = self.obj
        gflops_max = self.bench_obj["summary"]["gflops_max"]
        rpeak, _, _, _ = self.compute_rpeak()

        if rpeak == 0:
            return 0
        
        efficiency = gflops_max / rpeak * 100

        return efficiency

        
    def get_index(self):
        return "<li><a href='#Matrix_Bench'>Matrix Multiplication DGEMM</a></li>"


# faire la perf crête théorique : Rpeak = # of FP64 units (per core) * # of cores * max clock rate
#mettre des warnings que le rpeak sur chaque architecture est arbitraire pour 2 threads par coeur
#mettre un deuxieme warning pour dire que si le rpeak est plus petit que le expérimentale alors c'est pas bon

# est-ce que sysconfig fonctionne sur ARM comme sur X86_64 ?

# le pb c'est qu'il ne détecte pas le max MHz dans sysconf, il met 0 
# mettre des if pour dire que ça ne fonctionne pas si pas de rpeak