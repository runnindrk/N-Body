import numpy as np
import matplotlib.pyplot as plt
import matplotlib.animation as animation

def animate(i, data, scatters):

    time = data[i, 0]
    positions = data[i, 1:]

    for j, scatter in enumerate(scatters):
        scatter.set_offsets([positions[j*7 + 1], positions[j*7 + 2]])
    
    return scatters

def plot_data():

    data = np.loadtxt("test/simulation/simulation.dat")

    fig, ax = plt.subplots()
    ax.set_xlim(-64, 64)
    ax.set_ylim(-64, 64)
    ax.set_aspect('equal', adjustable='box')
    
    num_bodies = (len(data[0, :]) - 1) // 7
    scatters = [ax.scatter([], []) for _ in range(num_bodies)]

    ani = animation.FuncAnimation(fig, animate, frames=len(data), fargs=(data, scatters), interval=100)

    plt.show()

# ----------------------------------------------------------------

plot_data()