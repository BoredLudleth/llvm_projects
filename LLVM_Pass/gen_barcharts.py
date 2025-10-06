#!/usr/bin/env python3

import numpy as np
from collections import Counter
from pathlib import Path
import matplotlib.pyplot as plt
from matplotlib.colors import LinearSegmentedColormap

def read_trace(file_path: str = "trace.log") -> list[str]:
    if not Path(file_path).is_file():
        raise FileNotFoundError(f"File {file_path} not found.")
    with open(file_path, 'r', encoding='utf-8') as f:
        return [line.strip() for line in f if line.strip()]

def get_log_events(lines: list[str]) -> list[str]:
    """Extract all 'op <- op' strings as events."""
    events = []
    for line in lines:
        if " <- " in line:
            parts = line.split(" <- ", 1)
            if len(parts) == 2 and parts[0] and parts[1]:
                events.append(line)
    return events

def find_frequent_patterns(events: list[str], max_len: int = 5, top_k: int = 10) -> dict[int, list[tuple[str, int]]]:
    results = {}
    for length in range(1, max_len + 1):
        pattern_counts = Counter()
        for i in range(len(events) - length + 1):
            pattern = "\n".join(events[i:i + length])
            pattern_counts[pattern] += 1
        results[length] = pattern_counts.most_common(top_k)
    return results

def plot_patterns(patterns_by_len: dict[int, list[tuple[str, int]]], output_dir: str = "images"):
    Path(output_dir).mkdir(exist_ok=True)
    
    blue_to_orange = LinearSegmentedColormap.from_list("blue_to_orange", ["#1f77b4", "#ff7f0e"])

    for length, top_patterns in patterns_by_len.items():
        if not top_patterns:
            continue

        labels, counts = zip(*top_patterns)
        counts = list(counts)
        n = len(counts)
        colors = blue_to_orange(np.linspace(0, 1, n))

        fig_width = max(10, n * 1.8)
        fig, ax = plt.subplots(figsize=(fig_width, 6))

        bar_width = 0.6
        x_positions = range(n)
        bars = ax.bar(x_positions, counts, color=colors, width=bar_width)

        ax.set_title(f"{length}-length Patterns", fontsize=14, weight='bold')
        ax.set_ylabel("Frequency", fontsize=12)
        ax.set_xticks(x_positions)
        ax.set_xticklabels(labels, rotation=0, fontsize=9, ha='center')

        for i, (bar, count) in enumerate(zip(bars, counts)):
            offset = 0.0 if n <= 5 else (i % 2) * 0.2 - 0.1
            ax.text(bar.get_x() + bar.get_width() / 2 + offset,
                    bar.get_height() + max(counts) * 0.01,
                    str(count), ha='center', va='bottom', fontsize=9)

        plt.tight_layout(pad=3.0)
        plt.savefig(f"{output_dir}/pattern_{length}.png", dpi=150)
        plt.close(fig)

def main():
    lines = read_trace()
    events = get_log_events(lines)
    print(f"Loaded {len(events)} dependency events.")
    patterns = find_frequent_patterns(events, max_len=5, top_k=10)
    plot_patterns(patterns)
    print("Charts saved to './images/'")

if __name__ == "__main__":
    main()