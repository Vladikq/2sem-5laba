schedule = []

while True:
    N = int(input("Введите число операций: "))

    for _ in range(N):
        operation = input("Введите операцию: ")

        if operation == "CLASS":
            day, discipline = input("Введите номер дня и название предмета: ").split()
            day = int(day)
            schedule.append((day, discipline))  # Добавляем занятие в расписание

        elif operation == "NEXT":
            last_day = 29  # Предпоследний день текущего месяца
            schedule = [(last_day, cls[1]) for cls in schedule]  # Переносим все занятия на предпоследний день
            print("Перенос всех занятий на предпоследний день текущего месяца выполнен.")

        elif operation == "VIEW":
            day = int(input("Введите номер дня: "))
            classes_on_day = [cls for cls in schedule if cls[0] == day]

            print(f"В {day} день", end=" ")
            if classes_on_day:
                print(f"1 занятие в университете: {classes_on_day[0][1]}", end="")
                for cls in classes_on_day[1:]:
                    print(f", {cls[1]}", end="")
            else:
                print("У нас свободный день!", end="")
            print()

        elif operation == "EXIT":
            print("Программа завершает работу.")
