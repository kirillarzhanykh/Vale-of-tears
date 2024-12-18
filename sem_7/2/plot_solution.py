
import os
import sys
import numpy as np
import matplotlib.pyplot as plt

def read_solution(filename):
    t_data = []
    x_data = []
    u_data = []
    with open(filename, 'r') as file:
        for line in file:
            t, x, x2, p1, p2, u = map(float, line.split()[:6])
            t_data.append(t)
            x_data.append(x)
            u_data.append(u)
    return t_data, x_data, u_data

def plot_solution(t_data, x_data, u_data, output_image, h):
    plt.plot(t_data, x_data, color='black', linestyle='-', label=f'x(t) for h={h}')
    plt.scatter(t_data, x_data, color='red', s=10, label='Data points')

    plt.plot(t_data, u_data, color='green', linestyle='-', label=f'u(t) for h={h}')
    plt.scatter(t_data, u_data, color='yellow', s=10, label='Data points')

    plt.xlabel('t')
    plt.ylabel('x(t), u(t)')
    plt.title(f'Solution with h={h}')
    plt.legend()
    plt.grid(True)
    
    # Сохранение графика в файл
    plt.savefig(output_image)
    plt.close()

if __name__ == "__main__":
    if len(sys.argv) < 4:
        print("Usage: python3 plot_solution.py <input_file> <output_image> <h>")
        sys.exit(1)

    input_file = sys.argv[1]
    output_image = sys.argv[2]
    h = sys.argv[3]

    t_data, x_data, u_data = read_solution(input_file)
    
    plot_solution(t_data, x_data, u_data, output_image, h)