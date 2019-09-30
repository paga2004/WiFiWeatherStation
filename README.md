# WiFi Weather Station

A simple IoT weather station built with a wemos d1 mini.

## Introduction

The wemos d1 mini is connected to a [HYT939](https://www.ist-ag.com/sites/default/files/DHHYT939_E.pdf) humidity and temperature sensor. It will connect to a WiFi network, measure, and send data to the web server every couple minutes. The webserver accepts HTTP POST request on /api/entry in the following format:

```
temp=xx&humidity=xx
```

The web server stores the entries in a sqlite database. You can use the api at /api/entry or /api/entries to get data in json format or use the web interface.

Example request:

```bash
$ curl http://localhost:8080/api/entries
[{"time": 1569840382.546, "temp": 26.03, "humidity": 47.02}, {"time": 1569841008.17, "temp": 27.31, "humidity": 48.04}]
```

## Wiring

wemos d1 mini | HYT939
:--- | ---:
5V | VCC 
GND | GND
D1 | SCL
D2 | SDA
D0 <-> RST | -

## Dependecies

Make sure you have python2.7 and pip installed and install them by running the following command:
```bash
$ cd web
$ pip install -r requirements.txt
```


The sketches for the microcontroller have some dependencies.

Please install them first:

* ESP8266WiFi - https://github.com/esp8266/Arduino
* ESP8266HTTPClient - https://github.com/esp8266/Arduino/tree/master/libraries/ESP8266HTTPClient


If you are using [Platformio](https://platformio.org/) you can simply install them with the library manager.

## Built With

* [web.py](http://webpy.org/) - Web framework
* [axios](https://github.com/axios/axios) - Promise based HTTP client for the browser and node.js
* [Chart.js](https://www.chartjs.org/) - Javascript library for charts


## Contributing

If you have a feature suggestion or a bug to report, feel free to [open a pull request](https://github.com/paga2004/WiFiWeatherStation/pulls) or [open a new issue](https://github.com/paga2004/WiFiWeatherStation/issues/new).

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details
