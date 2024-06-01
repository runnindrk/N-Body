import matplotlib.pyplot as plt
import matplotlib.patches as patches
import numpy as np

def draw_points(fig, ax, color, points):

    for mass, center_x, center_y, velocity_x, velocity_y, force_x, force_y in points:

        force_magnitude = np.sqrt(force_x**2 + force_y**2)

        ax.scatter(center_x, center_y, color=color, s=25)
        ax.quiver(center_x, center_y, force_x/force_magnitude, force_y/force_magnitude, angles='xy', scale_units='xy', scale=1, color='green')

def draw_squares(fig, ax, color, squares, max_depth):
            
    for depth, center_x, center_y, center_mass_x, center_mass_y, total_mass, size in squares:

        if (depth > max_depth):
            continue
        
        if (depth == max_depth):
            plt.scatter(center_mass_x, center_mass_y, marker="x", color="black", s=12.5)
        
        lower_left_x = center_x - size / 2
        lower_left_y = center_y - size / 2
        square = patches.Rectangle(
            (lower_left_x, lower_left_y), 
            size, 
            size, 
            edgecolor=color,
            facecolor='none', 
            linewidth=1
        )
        ax.add_patch(square)
        
squaresAllInformation = np.loadtxt("test/tree/tree.dat")
pointsAllInformation = np.loadtxt("test/tree/bodies.dat")

squares = squaresAllInformation
points = pointsAllInformation
max_depth = max(squares[0, :])

# ----------------------------------------------------------------

fig, ax = plt.subplots()

draw_points(fig, ax, 'red', points)
draw_squares(fig, ax, 'k', squares, max_depth)
draw_squares(fig, ax, 'blue', squares, 4)

ax.set_aspect('equal', 'box')
plt.xlim(-64, 64)
plt.ylim(-64, 64)

plt.show()