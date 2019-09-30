import web

import time

db = web.database(dbn='sqlite', db='weatherstation.db')


def new_entry(temp, humidity):
    db.insert('indoor', time=time.time(), temp=float(temp), humidity=float(humidity))

def get_entry():
    return db.select("indoor", where="time=(SELECT MAX(time) FROM indoor)")[0]

def get_entries():
    return list(db.select("indoor", order="time"))