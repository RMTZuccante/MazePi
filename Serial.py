import serial, time

def init(port, baudrate):
    try:
        global device
        device = serial.Serial(port, baudrate)
        time.sleep(1.7)
        return device != None
    except:
        return False

def read():
    return device.readline(2000).replace('\r\n', '')

def write(msg):
    device.write(msg + '\n')