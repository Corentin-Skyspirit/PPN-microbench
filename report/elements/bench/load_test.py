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

        imgs = f"<img src='{wd}/out/load_test.png'/>"
        title = "<center><p>Load test in number of FMA per seconds</p></center>"
        
        return header+ imgs  + title

    def gen_images(self):
        data = np.array(self.bench_obj["results"])

        plt.plot(data)

        plt.xlabel("Sample")
        plt.ylabel("Fma per seconds")
        plt.grid(True, which='major', axis='y', linestyle='--', alpha=0.7)

        plt.savefig("out/load_test.png")
        plt.clf()
        plt.close()

    def get_index(self):
        return "<li><a href='#LoadTest'>Load test</a></li>"
