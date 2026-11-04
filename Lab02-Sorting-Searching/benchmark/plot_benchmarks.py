import csv
import os
import matplotlib.pyplot as plt

def generate_benchmark_plots():
    csv_file = "benchmark_results.csv"
    if not os.path.exists(csv_file):
        print(f"[ERROR] {csv_file} not found.")
        return

    # Data structure: data[data_type][algorithm] = {size: time_ms}
    data = {}
    with open(csv_file, "r") as f:
        reader = csv.DictReader(f)
        for row in reader:
            algo = row["Algorithm"]
            dtype = row["DataType"]
            size = int(row["Size"])
            time_ms = float(row["TimeMs"])

            if dtype not in data:
                data[dtype] = {}
            if algo not in data[dtype]:
                data[dtype][algo] = {}
            data[dtype][algo][size] = time_ms

    colors = {
        "Bubble Sort": "#e74c3c",
        "Selection Sort": "#e67e22",
        "Insertion Sort": "#f1c40f",
        "Merge Sort": "#2ecc71",
        "Quick Sort": "#3498db",
        "Heap Sort": "#9b59b6",
        "Radix Sort": "#1abc9c"
    }

    markers = {
        "Bubble Sort": "o",
        "Selection Sort": "s",
        "Insertion Sort": "^",
        "Merge Sort": "D",
        "Quick Sort": "v",
        "Heap Sort": "p",
        "Radix Sort": "x"
    }

    # Plot for each data type
    for dtype, algos in data.items():
        plt.figure(figsize=(10, 6), dpi=150)
        for algo, size_map in algos.items():
            sizes = sorted(size_map.keys())
            times = [size_map[s] for s in sizes]
            plt.plot(sizes, times, marker=markers.get(algo, 'o'), label=algo,
                     color=colors.get(algo, '#333333'), linewidth=2, markersize=7)

        plt.title(f"Empirical Sorting Performance on {dtype} Data (IC-307D DSA Lab)", fontsize=13, fontweight='bold', pad=12)
        plt.xlabel("Input Array Size (N)", fontsize=11, fontweight='bold')
        plt.ylabel("Execution Time (milliseconds)", fontsize=11, fontweight='bold')
        plt.grid(True, linestyle="--", alpha=0.6)
        plt.legend(loc="upper left", framealpha=0.9)
        plt.tight_layout()

        filename = f"benchmark_{dtype.lower()}.png"
        plt.savefig(filename)
        plt.close()
        print(f"[SUCCESS] Saved {filename}")

    # Logarithmic summary comparison across all algorithms at N=10000
    plt.figure(figsize=(11, 6), dpi=150)
    import numpy as np

    algorithms = list(colors.keys())
    x = np.arange(len(algorithms))
    width = 0.25

    times_random = [data.get("Random", {}).get(a, {}).get(10000, 0.0) for a in algorithms]
    times_sorted = [data.get("Sorted", {}).get(a, {}).get(10000, 0.0) for a in algorithms]
    times_reverse = [data.get("Reverse", {}).get(a, {}).get(10000, 0.0) for a in algorithms]

    plt.bar(x - width, times_random, width, label='Random Data', color='#3498db', edgecolor='black', alpha=0.85)
    plt.bar(x, times_sorted, width, label='Sorted Data', color='#2ecc71', edgecolor='black', alpha=0.85)
    plt.bar(x + width, times_reverse, width, label='Reverse Data', color='#e74c3c', edgecolor='black', alpha=0.85)

    plt.yscale('log')
    plt.ylabel("Execution Time in ms (Logarithmic Scale)", fontsize=11, fontweight='bold')
    plt.title("Comparative Performance across Input Distributions at N = 10,000", fontsize=13, fontweight='bold', pad=12)
    plt.xticks(x, algorithms, rotation=20, ha='right', fontsize=10, fontweight='bold')
    plt.legend(framealpha=0.95)
    plt.grid(True, which="both", ls="--", alpha=0.4)
    plt.tight_layout()

    plt.savefig("benchmark_all_summary.png")
    plt.close()
    print("[SUCCESS] Saved benchmark_all_summary.png")

if __name__ == "__main__":
    generate_benchmark_plots()
