import serial
ser = serial.Serial('/dev/ttyUSB0')
print(ser.name)
while 1:
    line = ser.readline().decode('utf-8').rstrip()
    print(line)
    xd = str(input("enter a number: ")).encode('utf-8')
    ser.write(xd + b'\n')
    line = ser.readline().decode('utf-8').rstrip()
    print(line)
