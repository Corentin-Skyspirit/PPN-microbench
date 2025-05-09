from elements.bench import *

from abc import ABC, abstractmethod
import json
import datetime

class AbstractElement(ABC):

    obj = None

    @abstractmethod
    def to_html(self):
        raise NotImplementedError("Abstract method call")

    @abstractmethod
    def get_index(self):
        raise NotImplementedError("Abstract method call")

class Report(AbstractElement):
    def __init__(self, json_path):
        self.json_path = json_path

        self.mapping = {
            "OPS" : Ops,
            "CPU Frequency": CpuFrequency,
            "Core To Core Latency": CoreToCoreLatency,
            "Cache Latency" : Cache_Latency,
            "Matrix Multiplication" : MatrixBench,
            "Load Test" : LoadTest,
            "Memory bandwidth" : MemBandwidth,
            "STREAM" : Stream,
            "GPU_H2D_Bandwidth" : GPUH2DBandwidth,
        }

        self.generate()

    def generate(self):
        with open(self.json_path, "r") as f:
            AbstractElement.obj = json.load(f)

        self.pages = [Cover(), Index(), SysInfo()]

        for bench_obj in AbstractElement.obj["data"]:
            self.pages.append(self.mapping[bench_obj["name"]](AbstractElement.obj, bench_obj))

        self.pages[1].set_pages(self.pages)

    def to_html(self):
        tmp = ""
        for p in self.pages:
            tmp += f"<div>{p.to_html()}</div>"

        html = f"""
<!DOCTYPE html>
<html lang="en">
    <head>
        <meta charset="UTF-8">
        <meta name="viewport" content="width=device-width, initial-scale=1.0">
        <link rel="stylesheet" href="../elements/styles/styles.css">
        <title>PPN-microbench</title>
    </head>
    <body>
        {tmp}
    </body>
</html>
"""
        return html

    def get_index(self):
        pass

class Cover(AbstractElement):
    """cover page"""
    def to_html(self):
        html = f"""
<header>
    <h1>PPN-microbench Automatic Report<h1>
    <p>{datetime.datetime.now()}</p>
    <p>{len(AbstractElement.obj["data"])} microbenches</p>
</header>
"""
        return html

    def get_index(self):
        return f"<li><a href='#Cover'>Cover</a></li>"

class Index(AbstractElement):
    """report index"""

    def set_pages(self, pages):
        self.pages = pages

    def to_html(self):
        tmp = ""
        for p in self.pages:
            tmp += p.get_index()
        html = f"""
<h2 id='Index'>Index</h2>
<ul>
    {tmp}
</ul>
"""
        return html

    def get_index(self):
        return f"<li><a href='#Index'>Index</a></li>"

class SysInfo(AbstractElement):
    """cpu, ram and gpu information"""
    def to_html(self):
        obj = AbstractElement.obj
        cpu_info = "<tr><th colspan='2'>CPU informations</th></tr>"
        for key, info in obj["meta"]["cpu_info"].items():
            cpu_info += f"<tr><th>{str(key)}</th><td>{self.format_info(info)}</td></tr>"
        cpu_info = f"<table>{cpu_info}</table>"

        mem_info = "<tr><th colspan='2'>Cache / Memory informations</th></tr>"
        mem_info += f"""<tr><th>Total memory</th><td>{round(obj["meta"]["mem_info"]["total_mem"] / (1 << 30), 3)}GiB</td></tr>"""
        del obj["meta"]["mem_info"]["total_mem"]
        for key, info in obj["meta"]["mem_info"].items():
            mem_info += f"<tr><th>{str(key)}</th><td>{info / 1024}KiB</td></tr>"
        mem_info = f"<table>{mem_info}</table>"

        gpu_info = "<tr><th colspan='2'>OpenCL Devices & GPUs</th></tr>"
        for d in obj["meta"]["gpu_info"]["devices"]:
                gpu_info += f"<tr><th colspan='2'>{d['name']}</th></tr>"
                gpu_info += f"<tr><th>Total memory</th><td>{round(d['total_memory'] / 1e9, 3)}GB</td></tr>"
                gpu_info += f"<tr><th>Max clock speed</th><td>{d['max_freq']}MHz</td></tr>"
                gpu_info += f"<tr><th>Compute units</th><td>{d['compute_units']}</td></tr>"
        gpu_info = f"<table>{gpu_info}</table>"

        return f"<h2 id='SysInfo'>System information</h2>" + cpu_info + mem_info + gpu_info
    
    def format_info(self, info):
        if isinstance(info, list):
            return ", ".join(map(str, info))
        return info
    
    def get_index(self):
        return f"<li><a href='#SysInfo'>System information</a></li>"
