# -*- coding: utf-8 -*-
import web
from web.httpserver import StaticMiddleware
import model
import json

urls = (
    '/', 'index',
    '/api/entry', 'entry',
    '/api/entries', 'entries'
)




class index:
    def GET(self):
       raise web.seeother('/static/index.html')

class entry:
    def POST(self):
        i = web.input()
        print(i)
        model.new_entry(i.temp, i.humidity)
        return ""
    def GET(self):
        web.header('Content-type', 'text/json') 
        d = model.get_entry()
        return json.dumps(dict(temp=d.temp, humidity= d.humidity, time=d.time))

class entries:
    def GET(self):
        web.header('Content-type', 'text/json') 
        d = model.get_entries()
        return json.dumps(d)

app = web.application(urls, globals())

# get the wsgi app from web.py application object
wsgiapp = app.wsgifunc(StaticMiddleware)

if __name__ == "__main__":
    app.run()
