from elements.bench.base import AbstractBench

import matplotlib.pyplot as plt
import numpy as np
import os.path

class Ops(AbstractBench):
    def __init__(self, obj):
        self.obj = obj

    def to_html(self):

        self.gen_images()

        header = "<h1 id='Ops'>Integer and Floating point operations per seconds</h1>"
        img = f"<img src='{os.getcwd()}/out/ops.png'/>"
        return header + img

    def gen_images(self):
        data = None

        data = np.array(self.obj["data"][0]["results"])
        ops_count = self.obj["data"][0]["ops_count"]
        cpus = self.obj["meta"]["cpu_info"]["cpus"]

        x = [i for i in range(len(data[0]))]

        print(np.sum(data[0] + data[1] + data[2] + data[3]) / 1e9)

        data[0] = 1e9 / data[0] * ops_count * cpus
        data[1] = 1e9 / data[1] * ops_count * cpus
        data[2] = 1e9 / data[2] * ops_count * cpus
        data[3] = 1e9 / data[3] * ops_count * cpus
        data[4] = 1e9 / data[4] * ops_count * cpus
        data[5] = 1e9 / data[5] * ops_count * cpus

        plt.yscale("log")

        plt.plot(x, data[0])
        plt.plot(x, data[1])
        plt.plot(x, data[2])
        plt.plot(x, data[3])
        plt.plot(x, data[4])
        plt.plot(x, data[5])

        plt.savefig("out/ops.png")

    def get_index(self):
        return "<li><a href='#Ops'>Integer and Floating point operations per seconds</a></li>"