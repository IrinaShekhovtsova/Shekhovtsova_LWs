#!C:\Users\irina\AppData\Local\Programs\Python\Python310\python.exe
import cgi, pickle, cgitb, codecs, sys, datetime, os, html
from msg import *

sys.stdout = codecs.getwriter("utf-8")(sys.stdout.detach())


class msgLogic:
    def __init__(self, formData):
        to = formData.getfirst("to", "50")
        self.to = html.escape(to)
        msg = formData.getfirst("msg", "")
        self.msg = html.escape(msg)

        self.id = Message.ClientID

        if (msg != "" and self.to != "50"):
            Message.SendMessage(int(self.to), MT_DATA, msg)
        if (msg != "" and self.to == "50"):
            Message.SendMessage(MR_ALL, MT_DATA, msg)
        try:
            self.printHeader()
            self.printBody()
            self.printFooter()
        except Exception as e:
            print(e)

    def printHeader(self):
        print("Content-type: text/html\n")
        print("""<!DOCTYPE HTML>
            <html>
            <head>
                <meta charset="utf-8">
                <title>New Year's Chat</title>
            </head>
            <body>""")

    def printBody(self):
        print(f"<h2>Client  {Message.ClientID}</h2>")
        print(f"""<form action="./form.py">
            <p>Enter ID 50 to send message to all users</p>
             <ul>
                <li>
                  <label for="to">To Client:</label>
                  <input type="text" id="to" name="to" value="50">
                  <br>
                </li>
                <li>
                  <label for="msg">Message:</label>
                  <textarea id="msg" name="msg"></textarea>
                  <input type="hidden" name="id" value ="{Message.ClientID}">
                <input type="submit" value="Send">
                </li>
            </ul>
            
        </form>
    
            <form action="./form.py">
            <input type="hidden" name="id" value="{Message.ClientID}">
            <input type="submit" value="Обновить">
            </form>""")

    def printFooter(self):
        print("""</body>
            </html>""")

def Client():
    Message.SendMessage(MR_BROKER, MT_INIT)


def main():
    Client()
    formData = cgi.FieldStorage()
    msg = msgLogic(formData)


main()