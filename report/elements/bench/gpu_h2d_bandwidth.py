from elements.bench.base import AbstractBench

import matplotlib.pyplot as plt
import matplotlib as mpl
from matplotlib.ticker import FuncFormatter
import numpy as np
import os.path

class GPUH2DBandwidth(AbstractBench):
    def __init__(self, obj, bench_obj):
        self.obj = obj
        self.bench_obj = bench_obj

    def to_html(self):
        self.gen_images()
        wd = os.getcwd()

        header = "<h2 id='GPUH2DBandwidth'>Host to device memory bandwidth</h2>"

        if (not self.bench_obj["info"]):
            img = f"<img src='{wd}/out/gpu_h2d_bandwidth.png'/>"
            i = self.obj["meta"]["gpu_info"]["main_device_index"]
            txt = f"<p>cl::enqueueWriteBuffer() of increasing sizes. Device {i} is chosen, with the following specs:</p>"
            txt += f"""<table>
            <tr><th>Device name</th><td>{self.obj["meta"]["gpu_info"]["devices"][i]["name"]}</td></tr>
            <tr><th>Total memory</th><td>{self.obj["meta"]["gpu_info"]["devices"][i]["total_memory"] / (1 << 30)}GiB</td></tr>
            </table>"""
        else:
            img = ""
            # TODO: maybe add a cool html warning or something
            txt = f"<p>WARNING: bench could not finish for the following reason: {self.bench_obj['info']}</p>"
        return header + img + txt

    def gen_images(self):
        sizes = np.array(self.bench_obj["meta"])
        data = np.array(self.bench_obj["data"])

        means = np.mean(sizes / data, axis=0)
        std_devs = np.std(sizes / data, axis=0)

        plt.figure(figsize=(10, 6))
        plt.errorbar(sizes / 1024, means, yerr=std_devs, fmt='-o', capsize=5, label='Host to GPU Bandwidth')

        plt.xscale('log', base=2)

        plt.xlabel('Buffer Size (KiB)')
        plt.ylabel('Bandwidth (GiB/sec)')
        plt.title('GPU host to device bandwidth')
        plt.grid(True, which="both", ls="--")
        plt.legend()
        plt.tight_layout()
        plt.savefig("out/gpu_h2d_bandwidth.png")

    def get_index(self):
        return "<li><a href='#GPUH2DBandwidth'>Host to device memory bandwidth</a></li>"