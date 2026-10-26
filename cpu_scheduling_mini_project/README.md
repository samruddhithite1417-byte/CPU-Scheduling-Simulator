# CPU Scheduling Simulator — Operating Systems Mini Project

## Included files
- `cpu_scheduling.c` — complete C source code
- `project_report.pdf` — engineering mini-project report
- `flowchart.png` — main program flowchart
- `sample_output.txt` — example program run

## Algorithms
1. FCFS (First Come First Served)
2. SJF (non-preemptive)
3. Priority Scheduling (non-preemptive; smaller number means higher priority)
4. Round Robin (positive user-defined time quantum)

The program displays a Gantt chart, completion time (CT), turnaround time (TAT), waiting time (WT), and average waiting and turnaround times.

## Compile and run
Linux: `gcc cpu_scheduling.c -o cpu_scheduling && ./cpu_scheduling`
Windows: `gcc cpu_scheduling.c -o cpu_scheduling.exe` then run `cpu_scheduling.exe`.

## Sample processes
P0: AT=0, BT=5, Priority=2
P1: AT=1, BT=3, Priority=1
P2: AT=2, BT=8, Priority=3
P3: AT=3, BT=6, Priority=2
Choose option 5 to run all algorithms and use time quantum 2.
