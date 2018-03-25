import serial

def init(port, baudrate):
    try:
        global device
        device = serial.Serial(port, baudrate)
        return device != None
    except:
        return False

def read():
    return device.readline().replace('\r\n', '')

def write(msg):
    device.write(msg + '\n')