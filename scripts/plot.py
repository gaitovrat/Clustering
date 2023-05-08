from sys import argv
from typing import Optional

import pandas as pd
import matplotlib.pyplot as plt


def plot(filepath: str, xname: str, yname: str, sname: Optional[str] = None):
    csv = pd.read_csv(filepath)
    labels = None

    if sname is not None:
        labels = csv.loc[:, sname]

    plt.xlabel(xname)
    plt.ylabel(yname)
    scatter = plt.scatter(csv.loc[:, xname], csv.loc[:, yname], c=labels)
    plt.legend(*scatter.legend_elements())
    plt.show()


if __name__ == "__main__":
    if len(argv) < 4:
        print("Usage:\n\tplot.py filepath xname yname [sname]")
        exit(1)

    plot(*argv[1:])
