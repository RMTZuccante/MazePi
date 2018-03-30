import serial

def init(port, baudrate):
    try:
        global device
        device = serial.Serial(port, baudrate)
        device.setDTR(False)
        return device != None
    except:
        return False

def read():
    return device.readline(2000).replace('\r\n', '')

def write(msg):
    device.write(msg + '\n')


print init("/dev/ttyACM0", 115200)
write("okciko\n")
print(read())