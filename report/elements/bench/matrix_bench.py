from elements.bench.base import AbstractBench

import json
import matplotlib.pyplot as plt
import numpy as np
import os

class Matrix_Bench(AbstractBench):
    def __init__(self, obj, bench_obj):
        self.obj = obj  # Le JSON complet
        self.bench_obj = bench_obj

    def to_html(self):
        self.gen_images()
        wd = os.getcwd()
        header = "<h2 id='Matrix_Bench'>Matrix Multipication</h2>"
        imgs = f"<img src='{wd}/out/matrix_benchmark_plot.png'/>"
        p = "<p>This benchmark evaluates the performance of dense matrix multiplication using Eigen. Below is the GFLOPS achieved for various matrix sizes.</p>"
        return header + imgs + p

    def gen_images(self):
        # Accès aux données depuis self.obj
        bench_data = self.obj["data"][0]
        results = bench_data["results"]
        summary = bench_data["summary"]

        sizes = [entry["size"] for entry in results]
        gflops = [entry["Gflops"] for entry in results]

        # Création du graphique
        plt.figure(figsize=(10, 6))
        plt.plot(sizes, gflops, marker='o', color='blue', label="GFLOPS (par taille)")

        # Ligne de max et moyenne
        plt.axhline(summary["gflops_max"], color='red', linestyle='--', label=f"Max GFLOPS: {summary['gflops_max']:.2f}")
        plt.axhline(summary["gflops_avg"], color='green', linestyle='--', label=f"Moyenne GFLOPS: {summary['gflops_avg']:.2f}")

        # Annotations sur les points
        for x, y in zip(sizes, gflops):
            plt.text(x, y + 0.5, f"{y:.1f}", ha='center', fontsize=9)

        # Mise en forme du graphique
        plt.title("Benchmark DGEMM - Performance (GFLOPS)")
        plt.xlabel("Taille des matrices (N x N)")
        plt.ylabel("GFLOPS")
        plt.grid(True)
        plt.legend()
        plt.tight_layout()

        # Création du dossier de sortie et sauvegarde
        os.makedirs("out", exist_ok=True)
        plt.savefig("out/matrix_benchmark_plot.png", dpi=300)
        plt.close()

    def get_index(self):
        return "<li><a href='#Matrix_Bench'>Matrix Multiplication DGEMM</a></li>"
