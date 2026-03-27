def create_plane(kal):
    plane = input("Введите название самолета: ")
    while plane in kal:
        plane = input("Номер самолета уже занят, выберите другой: ")
    numtown = input("Введите число городов: ")
    while not numtown.isdigit():
        numtown = input("Ошибка. Нельзя использовать буквы. Введите число городов: ")
    numtown = int(numtown)
    numplanetown = [input("Название города: ") for _ in range(numtown)]
    kal[plane] = numplanetown

def planes_for_town(kal, town):
    print(f"Самолеты летающие через {town}:")
    found = False
    for plane, towns in kal.items():
        if town in towns:
            print(f"Самолет {plane}")
            found = True
    if not found:
        print(f"Нет пролетающих самолетов через {town}")

def towns_for_plane(kal, plane):
    if plane in kal:
        towns = kal[plane]
        print(f"Города, через которые пролетает самолет {plane}:")
        for town in towns:
            print(town)
    else:
        print(f"Самолет {plane} не найден.")

def planes(kal):
    for plane, towns in kal.items():
        print(f"Самолет {plane} останавливается в этих городах:")
        for town in towns:
            print(town)
        print()

    
print("Все команды: CREATE_PLANE, PLANES_FOR_TOWN, TOWNS_FOR_PLANE, PLANES, EXIT")
kal = {}
while True:
    comands = input("Введите команду: ")
    if comands == "CREATE_PLANE":
        create_plane(kal)
    elif comands == "PLANES":
        planes(kal)
    elif comands == "PLANES_FOR_TOWN":
        town = input("Введите название города: ")
        planes_for_town(kal, town)
    elif comands == "TOWNS_FOR_PLANE":
        plane = input("Введите номер самолета: ")
        towns_for_plane(kal, plane)
    elif comands == "EXIT":
        break
    else:
        print("Неверный ввод")
