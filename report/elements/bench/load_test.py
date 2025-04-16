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

        img = f"<img src='{wd}/out/load_test_boxplot.png'/>"
        title = "<center><p>Frequency variation of load test with FMA</p></center>"
        
        return header+ img + title

    def gen_images(self):
        data = self.bench_obj["results"]

        plotList = []
        # stdList = []

        # for coresList in data:
        #     plotList.append(np.mean(coresList))
        #     stdList.append(np.std(coresList))


        # plt.plot(range(1, len(plotList)+1), plotList, color='orange')
        # plt.errorbar(range(1, len(plotList) + 1), plotList, yerr=stdList, marker=".", label='Fequency', capsize=5, capthick=1, ecolor='gray')
        # plt.ylim(bottom=0)

        # plt.xlabel("Cores")
        # plt.ylabel("Frequency")
        # plt.grid(True, which='major', axis='y', linestyle='--', alpha=0.7)

        # plt.savefig("out/load_test.png")
        # plt.clf()

        np.array(plotList)

        minimum = np.min(data)
        q1 = np.percentile(data, 25)
        median = np.median(data)
        q3 = np.percentile(data, 75)
        maximum = np.max(data)

        plt.boxplot(data)
        plt.xlabel('Cores')
        plt.ylabel('Frequency')
        plt.grid(True, which='major', axis='y', linestyle='--', alpha=0.7)

        plt.savefig("out/load_test.png")
        plt.clf()
        plt.close()

    def get_index(self):
        return "<li><a href='#LoadTest'>Load test</a></li>"
