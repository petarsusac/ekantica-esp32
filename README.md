# eKantica

## Komparator LM393 i sonda HL-69 - vlaga tla

Potrebna je AD pretvorba signala za dobivanje vlage tla. Granice za vlažno i suho tlo dobivene su eksperimentalno (čitaj - gledala sam koja je vrijednost kad je sonda u zraku, suhoj zemlji i totalno potopljenoj zemlji, rip moj sukulent).

| LM393 | ESP32C3 |
|:------:|:-------------------:|
| GND    | GND                  |
| A0    | Pin 0                 |
| D0    | -                 |
| 5V    | 5V                 |

## DHT11 - temperatura i vlaga zraka

Postoji gotov kod za ovo, nalazi se ovdje: https://github.com/UncleRus/esp-idf-lib/tree/master/components/dht.
Treba samo definirati koji DHT se koristi, pokrenuti gotovu funkciju i _voila_.

Možda koristan link za teorijski dio vezan za relativnu vlažnost:
https://www.circuitbasics.com/how-to-set-up-the-dht11-humidity-sensor-on-an-arduino/

| DHT11 | ESP32C3 |
|:------:|:-------------------:|
| S    | Pin 10                 |
| GND (-)    | GND                  |
| 5V (+)   | 5V                 |
