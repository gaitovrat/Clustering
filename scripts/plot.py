from sys import argv

import pandas as pd
import matplotlib.pyplot as plt


def plot(filepath: str, xname: str, yname: str):
    csv = pd.read_csv(filepath)

    plt.xlabel(xname)
    plt.ylabel(yname)
    plt.scatter(csv.loc[:, xname], csv.loc[:, yname])
    plt.show()


if __name__ == "__main__":
    if len(argv) < 4:
        print("Usage:\n\tplot.py filepath xname yname")
        exit(1)

    plot(*argv[1:])
