import pyvisa
import numpy as np
import matplotlib.pyplot as plt
import pandas as pd
import time as ti


def teste_equipamento():
    rm = pyvisa.ResourceManager()
    my_instrument = rm.open_resource(rm.list_resources()[0])
    my_instrument.query('*IDN?') #comunicação com dispositivo
    my_instrument.query('FREQ?') #devolve a frequencia de comunicação
    return my_instrument

def resolucao(primeiro_valor=0.005,ultimo_valor=0.050,passo=0.001):
    a=np.arange(primeiro_valor, ultimo_valor, passo)
    return a

def medicao(my_instrument,a):
    
    Rdut=[]
    Vdut=[]
    idut=[]
    R=1000000
    my_instrument.write('APHS')
    for t in a:
        my_instrument.write(f'SLVL {t}') #pega os valores que tão em 'a' e coloca no seno 
        if(t<0.006):
            ti.sleep(0.5) #precisa de mais tempo pra fazer a leitura do primeiro valor 
        else:
            ti.sleep(0.2)
        v = float(my_instrument.query('OUTP? X'.rstrip())) #le o valor sem aspas
        Vdut.append(v)
        req = (v*R)/(t-v)
        Rdut.append(req)
        idut.append(v/req)
        #ti.sleep(0.2)
    my_instrument.write('SLVL 0.005')
    return idut,Vdut

def grafico(idut,Vdut,Res):

    plt.plot(idut,Vdut,'b.')
    plt.xlabel('corrente (A)')
    plt.ylabel('tensão (V)')
    A,B = np.polyfit(idut,Vdut,1) #achando coeficiente linear e angular dos diros diretos
    Res.append(A)
    print(A)
    y=np.zeros(len(idut))
    j=0
    for i in idut:
        y[j]=i*A+B
        j=j+1
        
    plt.plot(idut,y,'r',label='R = '+str(round(A,2))+'Ω')

    #plt.text(2,2,'R='+str(round(A))+'Ω')
    #print(A)
    plt.legend()
    plt.show()
    return Res
    #np.savetxt('valorees_resistencias.txt', Res, newline='\n')


def valor():
    print("oi")
