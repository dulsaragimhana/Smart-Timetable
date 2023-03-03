import paho.mqtt.publish as publish
import time

free=[]
absent=["M1", "E1"]
day=1        #0-MONDAY 1-TUESDAY 2-WEDNESDAY 3-THURSDAY 4-FRIDAY
periods=[]


for i in absent:
    if i=="M1":
        f1=open("M1.txt","r")
        x=(f1.read()).split(';')
        f1.close()
        for k in x:
            periods.append(k)
        
    elif i=="M2":
        f1=open("M2.txt","r")
        x=(f1.read()).split(';')
        f1.close()
        for k in x:
            periods.append(k)
    elif i=="S1":
        f1=open("S1.txt","r")
        x=(f1.read()).split(';')
        f1.close()
        for k in x:
            periods.append(k)
    elif i=="S2":
        f1=open("S2.txt","r")
        x=(f1.read()).split(';')
        f1.close()
        for k in x:
            periods.append(k)
    elif i=="E1":
        f1=open("E1.txt","r")
        x=(f1.read()).split(';')
        f1.close()
        for k in x:
            periods.append(k)
    elif i=="E2":
        f1=open("E2.txt","r")
        x=(f1.read()).split(';')
        f1.close()
        for k in x:
            periods.append(k)

f=open("FreePeriods.txt","r")
freeWeek=(f.read()).split(';')
f.close()


offPeriods=[]    
freeTeachers=(freeWeek[day].split('/'))
for i in range(0,len(absent)):
    offPeriods.append((periods[day+(i*5)].split(' ')))
le=len(offPeriods)

messagesToBeSent = []
x = ""

f_w = open("Answers.txt", "a")
for i in range(0,le):
    for k in range(0,4):
        if offPeriods[i][k]!="FREE":
            if freeTeachers[k][0:2] not in absent:
                x = "Assign "+(freeTeachers[k][0:2])+" to the class "+offPeriods[i][k]+" in period "+str(k+1)
                print(x)
                messagesToBeSent.append(x)
                f_w.write(x+"\n")
            elif freeTeachers[k][3:5] not in absent:
                x = "Assign "+(freeTeachers[k][3:5])+" to the class "+offPeriods[i][k]+" in period "+str(k+1)
                print(x)
                messagesToBeSent.append(x)
                f_w.write(x+"\n")
            else:
                print("No teachers to assign")
                f_w.write("No teachers to assign"+"\n")
f_w.close()

time.sleep(10)

for i in messagesToBeSent:
    if i[7:9] == "S1":
        msg = '{"payload":"Dear Teacher, You have assigned period '+i[37:38]+' in '+i[23:26]+'",'+'"number":"+94763475089"}'
        publish.single("school/test",msg, hostname="Broker.mqttdashboard.com")
        time.sleep(5)




 




