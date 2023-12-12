import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation
import numpy as np

plt.style.use('dark_background')
fig, ax = plt.subplots()
plt.rcParams["figure.figsize"] = [7.00, 3.50]
def main():
    ax.clear()
    #ax.set_axis_off()
    plt.rc('axes.formatter', useoffset=False)
    plt.plot(100,100,'ro')
    #animate_obj = FuncAnimation(fig, animation, interval=100)
    plt.show()


if __name__ == "__main__":
    main()
