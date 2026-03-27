from heapq import heappop, heappush

def queue_peoples(visitors, num_windows):
    window_times = [0] * num_windows
    windows = [[] for _ in range(num_windows)]

    visitors = [(-time, -talon) for time, talon in visitors]
    heapq.heapify(visitors)

    while visitors:
        time, talon = heappop(visitors)
        min_window_index = window_times.index(min(window_times))
        windows[min_window_index].append(-talon)
        window_times[min_window_index] -= time

    for i, window in enumerate(windows):
        print(f"Окно {i+1} ({window_times[i]} минут):", ' '.join(f"T{-talon}" for talon in window))


peoples = []
print(">>> Введите кол-во рабочих окон:")
num_windows = int(input("<<< "))

print(">>> Для получения талона введите: ENQUEUE и время посещения\n\tДля формирования очереди введите: DISTRIBUTE\n\t\tДля выхода введите: EXIT")
talon = 100
while True:
    command = input("<<< ")
    if command == "ENQUEUE":
        time = int(input())
        talon += 10
        print(f">>> T{talon}")
        heappush(peoples, (-time, -talon))
    elif command == "DISTRIBUTE":
        queue_peoples(peoples, num_windows)
    elif command == "EXIT":
        print(">>> Выход...")
        break
    else:
        print(">>> Команда введена неверно")
