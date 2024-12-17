from abc import ABC, abstractmethod
import matplotlib.pyplot as plt

class AbstractBench(ABC):
    @abstractmethod
    def to_html(self):
        raise NotImplementedError("Abstract method call")
    
    @abstractmethod
    def gen_images(self):
        raise NotImplementedError("Abstract method call")
    
    def gen_index(self):
        raise NotImplementedError("Abstract method call")
