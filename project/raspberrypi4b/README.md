### 1. Board

#### 1.1 Board Info

Board Name: Raspberry Pi 4B.

GPIO Pin: SCLK/DIN GPIO27/GPIO17.

### 2. Install

#### 2.1 Dependencies

Install the necessary dependencies.

```shell
sudo apt-get install libgpiod-dev pkg-config cmake -y
```

#### 2.2 Makefile

Build the project.

```shell
make
```

Install the project and this is optional.

```shell
sudo make install
```

Uninstall the project and this is optional.

```shell
sudo make uninstall
```

#### 2.3 CMake

Build the project.

```shell
mkdir build && cd build 
cmake .. 
make
```

Install the project and this is optional.

```shell
sudo make install
```

Uninstall the project and this is optional.

```shell
sudo make uninstall
```

Test the project and this is optional.

```shell
make test
```

Find the compiled library in CMake. 

```cmake
find_package(tm1640 REQUIRED)
```

### 3. TM1640

#### 3.1 Command Instruction

1. Show tm1640 chip and driver information.

    ```shell
    tm1640 (-i | --information)  
    ```

2. Show tm1640 help.

    ```shell
    tm1640 (-h | --help)        
    ```

3. Show tm1640 pin connections of the current board.

    ```shell
    tm1640 (-p | --port)        
    ```

4. Run tm1640 write test.

    ```shell
    tm1640 (-t write | --test=write )      
    ```

5. Run tm1640 write function,  address is the start address and the range is 0 - 7.

    ```shell
    tm1640 (-e write | --example=write) [--addr=<address>] [--num=<0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9>]   
    ```
    
6. Run tm1640 init function.

    ```shell
    tm1640 (-e init | --example=init)

7. Run tm1640 deinit function.

    ```shell
    tm1640 (-e deinit | --example=deinit)

8. Run tm1640 on function.

    ```shell
    tm1640 (-e on | --example=on)

9. Run tm1640 off function.

    ```shell
    tm1640 (-e off | --example=off)

#### 3.2 Command Example

```shell
./tm1640 -i

tm1640: chip is Titan Micro Electronics TM1640.
tm1640: manufacturer is Titan Micro Electronics.
tm1640: interface is GPIO.
tm1640: driver version is 1.0.
tm1640: min supply voltage is 3.0V.
tm1640: max supply voltage is 5.5V.
tm1640: max current is 200.00mA.
tm1640: max temperature is 85.0C.
tm1640: min temperature is -40.0C.
```

```shell
./tm1640 -p

tm1640: GPIO interface SCLK connected to GPIO27(BCM).
tm1640: GPIO interface DIN connected to GPIO17(BCM).
```

```shell
./tm1640 -t write

tm1640: chip is Titan Micro Electronics TM1640.
tm1640: manufacturer is Titan Micro Electronics.
tm1640: interface is GPIO.
tm1640: driver version is 1.0.
tm1640: min supply voltage is 3.0V.
tm1640: max supply voltage is 5.5V.
tm1640: max current is 200.00mA.
tm1640: max temperature is 85.0C.
tm1640: min temperature is -40.0C.
tm1640: start write test.
tm1640: address auto increment mode.
tm1640: address fix mode.
tm1640: set pulse width 12.
tm1640: set pulse width 10.
tm1640: set pulse width 2.
tm1640: display off.
tm1640: display on.
tm1640: finish write test.
```

```shell
./tm1640 -e init

tm1640: init.
```

```shell
./tm1640 -e write --addr=0 --num=0

tm1640: write address 0 number 0.
```
```shell
./tm1640 -e on

tm1640: display on.
```
```
./tm1640 -e off

tm1640: display off.
```
```shell
./tm1640 -e deinit

tm1640: deinit.
```
```shell
./tm1640 -h

Usage:
  tm1640 (-i | --information)
  tm1640 (-h | --help)
  tm1640 (-p | --port)
  tm1640 (-t write | --test=write)
  tm1640 (-e init | --example=init)
  tm1640 (-e deinit | --example=deinit)
  tm1640 (-e on | --example=on)
  tm1640 (-e off | --example=off)
  tm1640 (-e write | --example=write) [--addr=<address>]
         [--num=<0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9>]

Options:
      --addr=<address>                   Set the start address and the range is 0-7.([default: 0])
  -e <init | deinit | write | on | off>, --example=<init | deinit | write | on | off>
                                         Run the driver example.
  -h, --help                             Show the help.
  -i, --information                      Show the chip information.
  -p, --port                             Display the pin connections of the current board.
      --num=<0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9>([default: 0])
                                         Set display number.
  -t <write>, --test=<write>             Run the driver test.
```
