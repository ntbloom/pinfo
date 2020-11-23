# Pinfo

Quickly get current information about GPIO pins. Works great on Raspberry Pi and other Linux boxes
with gpio support.

#### compile on your machine using gcc

```sh
$ make pinfo
```

#### put it somewhere your path will pick it up

```sh
$ sudo cp pinfo /usr/local/bin
```

#### specify a pin or group of pins

```sh
$ pinfo 18 19
# Pin 18
#     direction:      out
#     edge:           none
#     value:          1
#     active_low:     0
#
# Pin 19
#     direction:      in
#     edge:           rising
#     value:          0
#     active_low:     1
```

#### or just see what all of your pins are doing

```sh
$ pinfo
# Pin 1
#     direction:      out
#     edge:           none
#     value:          1
#     active_low:     0
#
# Pin 2
#     direction:      in
#     edge:           rising
#     value:          0
#     active_low:     1
# Pin 3
#     direction:      in
#     edge:           rising
#     value:          0
#     active_low:     1
```

#### remove all exported pins

```sh
$ echo 18 > /sys/class/gpio/export
$ echo 19 > /sys/class/gpio/export
$ pinfo
# Pin 18
#     direction:      in
#     edge:           none
#     value:          0
#     active_low:     0
# Pin 19
#     direction:      in
#     edge:           rising
#     value:          0
#     active_low:     1
$ pinfo --kill
# killing pin 18
# killing pin 19
$ pinfo
# pinfo: no GPIO pins currently exported
```
