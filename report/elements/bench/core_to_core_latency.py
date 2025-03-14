from elements.bench.base import AbstractBench

import matplotlib.pyplot as plt
import matplotlib.colors as mcolors
import numpy as np
import os.path

class CoreToCoreLatency(AbstractBench):
    def __init__(self, obj, bench_obj):
        self.obj = obj
        self.bench_obj = bench_obj

    def to_html(self):
        self.gen_images()
        wd = os.getcwd()

        header = "<h2 id='CoreToCoreLatency'>Core-To-Core Latency</h2>"

        minImgs = f"<img src='{wd}/out/core_to_core_latency_min.png'/>"
        minTitle = "<center><p>Core-to-core minimum latency graph in nanoseconds</p></center>"
        
        meanImgs = f"<img src='{wd}/out/core_to_core_latency_mean.png'/>"
        meanTitle = "<center><p>Core-to-core mean latency graph in nanoseconds</p></center>"
        
        return header + minImgs + minTitle + meanImgs + meanTitle

    def gen_images(self):
        for m in range(2) :
            if m == 0 :
                mode = "min"
            elif m == 1 :
                mode = "mean"
            data = self.bench_obj["results"][mode]

            matrix = np.array(data)

            fig, ax = plt.subplots(figsize=(10, 10))
            plt.tight_layout(pad=3.5)

            colors = plt.cm.viridis(np.linspace(0, 1, 256))
            colors[0] = [0.4, 0.4, 0.4, 1]
            new_cmap = mcolors.ListedColormap(colors)
            cax = ax.imshow(matrix, cmap=new_cmap, interpolation="nearest", aspect='auto')

            # ax.figtext(0.5, 0.05, "Core-to-core latency", horizontalalignment = 'center', size='x-large')

            # Show values
            for i in range(matrix.shape[0]):
                for j in range(matrix.shape[1]):
                    ax.text(j, i, str(matrix[i, j] if matrix[i, j] != 0 else ""), ha='center', va='center', color='white')

            # Axis options
            ax.set_xticks(range(matrix.shape[1]))
            ax.set_yticks(range(matrix.shape[0]))
            ax.set_yticklabels(f"Core {j}" for j in range(matrix.shape[0]))
            ax.xaxis.set_ticks_position('top')
            ax.tick_params(axis='x', labeltop=True, labelbottom=False)

            fig.colorbar(cax, fraction=0.03, pad=0.04)

            plt.savefig("out/core_to_core_latency_" + mode + ".png")
            plt.clf()
            plt.close()

    def get_index(self):
        return "<li><a href='#CoreToCoreLatency'>Core-to-core latency</a></li>"
