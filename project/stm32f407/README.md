### 1. Chip

#### 1.1 Chip Info

Chip Name: STM32F407ZGT6.

Extern Oscillator: 8MHz.

UART Pin: TX/RX PA9/PA10.

GPIO Pin: SCLK/DIN PA0/PA8.

### 2. Development and Debugging

#### 2.1 Integrated Development Environment

LibDriver provides both Keil and IAR integrated development environment projects.

MDK is the Keil ARM project and your Keil version must be 5 or higher.Keil ARM project needs STMicroelectronics STM32F4 Series Device Family Pack and you can download from https://www.keil.com/dd2/stmicroelectronics/stm32f407zgtx.

EW is the IAR ARM project and your IAR version must be 9 or higher.

#### 2.2 Serial Port Parameter

Baud Rate: 115200.

Data Bits : 8.

Stop Bits: 1.

Parity: None.

Flow Control: None.

#### 2.3 Serial Port Assistant

We use '\n' to wrap lines.If your serial port assistant displays exceptions (e.g. the displayed content does not divide lines), please modify the configuration of your serial port assistant or replace one that supports '\n' parsing.

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
tm1640 -i

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
tm1640 -p

tm1640: GPIO interface SCLK connected to GPIOA PIN0.
tm1640: GPIO interface DIN connected to GPIOA PIN8.
```

```shell
tm1640 -t write

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
tm1640 -e init

tm1640: init.
```

```shell
tm1640 -e write --addr=0 --num=0

tm1640: write address 0 number 0.
```
```shell
tm1640 -e on

tm1640: display on.
```
```
tm1640 -e off

tm1640: display off.
```
```shell
tm1640 -e deinit

tm1640: deinit.
```
```shell
tm1640 -h

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
