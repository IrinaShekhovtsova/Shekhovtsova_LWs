import json
from Session import *
import threading
import socket, struct, time, sys
from venv import create
from message import *

def ProcessMessages():
    while True:
        m = Session.getData()
        if m.Type == MT_DATA:
            print(f"Пользователь {m.From} отправил: {m.Data}" )
        elif m.Type == MT_GETUSERS:
            if(len(m.Data) > 0 ):
                print("Другие пользователи: ")
                print(m.Data)
            else:
                print("Других пользователей нет!")
        elif m.Type == MT_GETLAST:
            if(len(m.Data) > 0 ):
                data = str(m.Data).replace("'",'"')
                data = json.loads(data)
                for item in data:
                    for key, value in item.items():
                        print(f"Пользователь {key} отправил: {value}" )
        else:
            time.sleep(2)

def Menu():
        print(" 1. Отправить сообщение пользователю.")
        print(" 2. Отправить сообщение всем.")
        print(" 3. Запросить список пользователей.")
        print(" 4. загрузить все последние сообщения.")
        print(" 5. Выход")
        
def Client():
    s = Session()
    t = threading.Thread(target=ProcessMessages, daemon = True)
    t.start()             
    while True:
        Menu()
        sw = input()
        if(sw.isdigit()):
            if sw == "1":
                print('Введите id пользователя: ')
                to = input()
                if(sw.isdigit()):
                    print('Введите сообщение: ')
                    s.send(int(to), MT_DATA, input())
                else:
                    print("Неправильный формат id!")

            elif sw == "2":
                print('Введите сообщение: ')
                s.send(MR_ALL, MT_DATA, input())

            elif sw == "3":
                s.getUsers()

            elif sw == "4":
                s.getLast()

            elif sw == "5":
                break

Client()