
import matplotlib.pyplot as plt

processes = [1, 2, 4, 8]

# Exercise 2 - Parallel Sum
sum_times = [0.000036, 0.000076, 0.000010, 0.000027]

# Exercise 3 - Monte Carlo Pi
pi_times = [0.141574, 0.072471, 0.039136, 0.024042]

def create_graphs(times, name):
    speedup = [times[0] / t for t in times]

    # Graph 1 - Execution Time
    plt.figure()
    plt.plot(processes, times, marker="o")
    plt.xlabel("Number of Processes")
    plt.ylabel("Execution Time (seconds)")
    plt.title(name + " - Execution Time")
    plt.xticks(processes)
    plt.grid(True)
    plt.tight_layout()
    plt.savefig(name + "_time.png", dpi=300)
    plt.close()

    # Graph 2 - Speedup
    plt.figure()
    plt.plot(processes, speedup, marker="o",
             label="Measured Speedup")
    plt.plot(processes, processes, "--",
             label="Ideal Speedup")
    plt.xlabel("Number of Processes")
    plt.ylabel("Speedup")
    plt.title(name + " - Speedup")
    plt.xticks(processes)
    plt.legend()
    plt.grid(True)
    plt.tight_layout()
    plt.savefig(name + "_speedup.png", dpi=300)
    plt.close()

create_graphs(sum_times, "MPI_Sum")
create_graphs(pi_times, "MPI_Pi")

print("All 4 graphs saved successfully!")
