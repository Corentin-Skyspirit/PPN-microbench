from elements.bench.base import AbstractBench

import matplotlib.pyplot as plt
import numpy as np
import os.path
from matplotlib.ticker import MultipleLocator

class CpuFrequency(AbstractBench):
    def __init__(self, obj, bench_obj):
        self.obj = obj
        self.bench_obj = bench_obj

    def to_html(self):
        self.gen_images()
        wd = os.getcwd()

        header = "<h2 id='CPUFrequency'>CPU Frequency</h2>"

        imgs = ""

        for page in range(0, len(self.bench_obj["results"]), 8):
            imgs += f"<img src='{wd}/out/cpu_frequency_multiplot_{page}.svg'/>"
        # title = "<center><p>Frequencies of cores in GHz depending of their number</p></center>"
        
        return header + imgs # + title

    def gen_images(self):
        full_data = self.bench_obj["results"]

        for page in range(0, len(self.bench_obj["results"]), 8):
            data = full_data[page:page+8]

            # Lignes
            lin = 1
            if len(data) == 2 :
                lin = 2
            elif len(data) in [3,5,6] :
                lin = 3
            elif len(data) in [4,7, 8] :
                lin = 4

            # Colonnes
            col = 1
            if len(data) > 4 :
                col = 2

            fig, truc = plt.subplots(lin, col, figsize=(10,12))

            plt.subplots_adjust(hspace=0.35, wspace=0.1)
            plt.figtext(0.5, 0.02, "Frequencies of cores in GHz depending on their number", horizontalalignment = 'center', size='x-large')

            for nb, sub_plot in enumerate(data) :
                values = []

                if len(sub_plot) == 1 :
                    mot = ' Core'
                else :
                    mot = ' Cores'

                for core in sub_plot :
                    temp = []
                    for val in core :
                        temp.append(val)

                    np.array(temp)

                    minimum = np.min(temp)
                    q1 = np.percentile(temp, 25)
                    median = np.median(temp)
                    q3 = np.percentile(temp, 75)
                    maximum = np.max(temp)

                    values.append(temp)

                if len(data) < 4 :
                    cadre = truc[nb]
                else :
                    cadre = truc[nb // 2, nb % 2] 

                cadre.boxplot(values)
                cadre.set_xlabel('Cores')
                cadre.set_ylabel('Frequency (GHz)')
                cadre.set_ylim(bottom=0)
                cadre.grid(True, which='major', axis='both', linestyle='--', alpha=0.7)
                
                # Axis options
                fig_width, _ = fig.get_size_inches() * fig.dpi

                # 1 tick every 10 pixels
                tick_spacing = int(len(values) / (fig_width / 10) + 1)
                tick_indices = np.arange(0, len(values), tick_spacing)

            # if (np.std(all_vals) / np.mean(all_vals) * 100 > 5.0) :
            #     plt.figtext(0.5, 0.035, "/!\ Warning /!\ Standard deviation is too high : {:.2f}%".format(np.std(all_vals) / np.mean(all_vals) * 100), horizontalalignment = 'center', color="red")
            # else :
            #     plt.figtext(0.5, 0.035, "Standard deviation is : {:.2f}%".format(np.std(all_vals) / np.mean(all_vals) * 100), horizontalalignment = 'center')

            plt.tight_layout(pad=3)

            plt.savefig("out/cpu_frequency_multiplot_" + str(page) + ".svg")
            plt.clf()
            plt.close()

    def get_index(self):
        return "<li><a href='#CPUFrequency'>CPU Frequency</a></li>"
