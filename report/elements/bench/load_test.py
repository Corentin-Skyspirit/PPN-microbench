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

        # img = f"<img src='{wd}/out/load_test.png'/>"
        # title = "<center><p>Load test in frequency per core</p></center>"

        img = f"<img src='{wd}/out/load_test.png'/>"
        # title = "<center><p>Frequency variation of load test with FMA</p></center>"
        
        return header+ img # + title

    def gen_images(self):
        data = self.bench_obj["results"]

        plotList = []

        for coreList in data:
            coreList = np.array(coreList)

            minimum = np.min(coreList)
            q1 = np.percentile(coreList, 25)
            median = np.median(coreList)
            q3 = np.percentile(coreList, 75)
            maximum = np.max(coreList)

            plotList.append(coreList)

        plt.boxplot(plotList)
        plt.xlabel('Cores')
        plt.ylabel('Frequency (GHz)')
        plt.ylim(bottom=0)
        plt.grid(True, which='major', axis='y', linestyle='--', alpha=0.7)
        plt.figtext(0.5, 0.93, "Frequency variation of load test with FMA", horizontalalignment = 'center', size='large')

        plt.savefig("out/load_test.png")
        plt.clf()
        plt.close()

    def get_index(self):
        return "<li><a href='#LoadTest'>Load test</a></li>"
