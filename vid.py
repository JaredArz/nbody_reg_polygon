import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation
import numpy as np

plt.style.use('dark_background')
fig, ax = plt.subplots()

def animation(i):
    ax.clear()
    ax.set_axis_off()
    plt.plot(105,200+i,'ro')

def main():

    animate_obj = FuncAnimation(fig, animation, interval=100)
    plt.show()


if __name__ == "__main__":
    main()
