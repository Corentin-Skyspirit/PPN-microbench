from elements.bench.base import AbstractBench

import matplotlib.pyplot as plt
import numpy as np
import os.path
from matplotlib.ticker import MultipleLocator

class LoadTest(AbstractBench):
    def __init__(self, obj, bench_obj):
        self.obj = obj
        self.bench_obj = bench_obj

    def to_html(self):
        self.gen_images()
        wd = os.getcwd()

        header = "<h2 id='LoadTest'>Load test</h2>"

        # img = f"<img src='{wd}/out/load_test.svg'/>"
        # title = "<center><p>Load test in frequency per core</p></center>"

        img = f"<img src='{wd}/out/load_test.svg'/>"
        # title = "<center><p>Frequency variation of load test with FMA</p></center>"
        
        return header+ img # + title

    def gen_images(self):
        data = self.bench_obj["results"]

        fig, truc = plt.subplots(1, 1, figsize=(12, 8))

        plotList = []

        for coreList in data:
            coreList = np.array(coreList)

            minimum = np.min(coreList)
            q1 = np.percentile(coreList, 25)
            median = np.median(coreList)
            q3 = np.percentile(coreList, 75)
            maximum = np.max(coreList)

            plotList.append(coreList)

        truc.boxplot(plotList)

        # Axis options
        fig_width, _ = fig.get_size_inches() * fig.dpi

        # 1 tick every 10 pixels
        tick_spacing = int(len(plotList) / (fig_width / 10) + 1)
        tick_indices = np.arange(0, len(plotList), tick_spacing)

        truc.set_xlabel('Cores')
        truc.set_ylabel('Frequency (GHz)')
        truc.set_ylim(bottom=0, top=6)
        truc.hlines(self.obj["meta"]["cpu_info"]["max_mhz"] / 1000, 0.5, len(data) + 0.5, colors="grey", linestyles="--", label="max frequency")
        truc.legend()
        truc.grid(True, which='major', axis='y', linestyle='--', alpha=0.7)
        plt.figtext(0.5, 0.93, "Frequency variation of load test with FMA", horizontalalignment = 'center', size='large')

        plt.savefig("out/load_test.svg")
        plt.clf()
        plt.close()

    def get_index(self):
        return "<li><a href='#LoadTest'>Load test</a></li>"
