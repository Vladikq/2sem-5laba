class Item:
    def __init__(self, name, quantity):
        self.name = name
        self.quantity = quantity

class Sklad:
    def __init__(self):
        self.storage = {}
        self.zones = []

    def add(self, address, name, quantity):
        if address in self.storage:
            if self.storage[address].name != name and self.storage[address].name != "":
                print("Ошибка, ячейка занята!")
            else:
                if self.storage[address].quantity + quantity <= 10:
                    self.storage[address] = Item(name, self.storage[address].quantity + quantity)
                else:
                    print("Ошибка, не хватает места в ячейке!")
        else:
            print("Ошибка, нет такой ячейки!")

    def remove(self, address, quantity):
        if address in self.storage:
            if self.storage[address].quantity - quantity == 0:
                self.storage[address] = Item("", 0)
            elif self.storage[address].quantity - quantity > 0:
                self.storage[address].quantity -= quantity
            else:
                print("Ошибка, не хватает продуктов для удаления!")
        else:
            print("Ошибка, нет такой ячейки!")

    def info(self):
        print("Адресс\tПродукт\tКол-во")
        count_occupied = 0.0
        for address, item in self.storage.items():
            if item.quantity != 0:
                print(f"{address}\t{item.name}\t{item.quantity}")
                count_occupied += 1

        total_count = len(self.storage)
        print("Загруженность склада: ", end="")
        print(f"{(count_occupied / total_count) * 100}%")

        print("Загруженность каждой зоны:")
        total_zones = total_count / len(self.zones)
        count_occupied_zones = [0.0] * len(self.zones)
        for i, zone in enumerate(self.zones):
            for address, item in self.storage.items():
                if address[0] == zone and item.quantity > 0:
                    count_occupied_zones[i] += 1

            print(f"Зона {zone}: ", end="")
            print(f"{(count_occupied_zones[i] / total_zones) * 100}%")

        print("Пустые ячейки: ", end="")
        for address, item in self.storage.items():
            if item.quantity == 0:
                print(address, end=" ")
        print()

    def generate_address(self):
        zones = ['A', 'B', 'C']
        self.zones = zones
        for zone in zones:
            for shelf in range(1, 6):
                for section in range(1, 6):
                    for rack in range(1, 4):
                        address = f"{zone}{rack}{section}{shelf}"
                        self.storage[address] = Item("", 0)


warehouse = Sklad()
warehouse.generate_address()

print("Выберите команду: ADD, REMOVE, INFO, EXIT для выхода: ")
k = True
while k:
    command = input()
    if command == "ADD":
        address, name, quantity = input().split()
        quantity = int(quantity)
        warehouse.add(address, name, quantity)
    elif command == "REMOVE":
        address, quantity = input().split()
        quantity = int(quantity)
        warehouse.remove(address, quantity)
    elif command == "EXIT":
        print("Выход из программы...")
        k = False
    elif command == "INFO":
        warehouse.info()
    else:
        print("Ошибка команды")
