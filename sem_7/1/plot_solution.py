
import os
import sys
import numpy as np
import matplotlib.pyplot as plt

def read_solution(filename):
    x_data = []
    u_data = []
    with open(filename, 'r') as file:
        for line in file:
            # Считываем только первые два столбца x и u, игнорируя третий
            x, u, _ = map(float, line.split()[:3])
            x_data.append(x)
            u_data.append(u)
    return x_data, u_data

def plot_solution(x_data, u_data, output_image, h):
    plt.plot(x_data, u_data, color='black', linestyle='-', label=f'Solution for h={h}')
    plt.scatter(x_data, u_data, color='red', s=10, label='Data points')

    plt.xlabel('x')
    plt.ylabel('u(x)')
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

    x_data, u_data = read_solution(input_file)
    
    plot_solution(x_data, u_data, output_image, h)