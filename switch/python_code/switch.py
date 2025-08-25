#nesse arquivo eu coloco o programa principal

import serial 

arduino = None

def conexao():
    global arduino
    while True: 
        try:  
            arduino = serial.Serial('COM7', 9600) 
            print('Arduino conectado')
            break
        except:
            pass

def medicao_bobina():
    global arduino
    arduino.write((int(42)).to_bytes(1, 'big'))
    dados=int(arduino.read(3))
    dados1=int(arduino.read(3))

    print("switch 1 com bobinha ",dados,"ligada" )
    print("switch 2 com bobinha ",dados1,"ligada" )

def bobina(switch,cmd):
    global arduino
    valor = switch*10+cmd
    arduino.write(int(valor).to_bytes(1, 'big'))

def zerar():
    global arduino
    arduino.write(int(10).to_bytes(1, 'big'))
    dados=int(arduino.read(3))
    dados1=int(arduino.read(3))
    
    print("switch 1 com bobinha ",dados,"ligada" )
    print("switch 2 com bobinha ",dados1,"ligada" )
  
def close():
    global arduino
    arduino.close()