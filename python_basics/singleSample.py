import simpleaudio as sa
import time
import random
BPMSet = True
samples = [sa.WaveObject.from_wave_file("kit/hihat.wav"),
            sa.WaveObject.from_wave_file("kit/snare.wav"),
                sa.WaveObject.from_wave_file("kit/kick.wav"),]
BPM = 120
noteDurations = [1, 0.5, 0.5, 1, 0.5, 0.5]
timeStamps16th = []
timestamps = []
loopCount = 0
i = 0

print("How many times do you want to loop the sequence?:")
try:
    loopCount = int(input())
except:
    print("Please Enter a Number!")
    exit()

#Geeft standaard BPM en vraagt om BPM Keuze
while BPMSet == True:
    print("Current BPM:", BPM, '\n' "Change it to whatever number you want or enter 120 to keep it:")
    try:
        BPM = int(input())
        BPMSet = False
    except:
        print("Please Enter a Number!")

#Verandert nootlengtes naar stappen
#voegt een begin noot toe
def durationsToTimestamps16th(noteDurations):
    timeStamps16th.append(0)
    step = 0
    for noteDuration in noteDurations:
        timeStamps16th.append(noteDuration*4+step)
        step = step + noteDuration*4
        print(timeStamps16th)

#Verandert de stappen naar tijdwaardes
def timeStamps(timeStamps16th, BPM):
    step = 0
    for timestamp in timeStamps16th:
        step = step+1
        timestamps.append((timestamp * (60/BPM)/4))

durationsToTimestamps16th(noteDurations)
timeStamps(timeStamps16th, BPM)


#speelt de sample in een loop af voor loopCount aantal keer, herstart als er nog maar 1 tijdwaarde in zit
#neemt de overige tijd om de maat vol te maken als pauze
while i < loopCount:
    timestampsloop = list(timestamps)
    timestamp = timestampsloop.pop(0)
    startTime = time.time()
    i = i+1
    x = 0
    while x == 0:
        currentTime = time.time()
        if(currentTime - startTime >= timestamp):
            print(timestamp)
            samples[random.randint(0,2)].play()
            if len(timestampsloop)>1:
                timestamp = timestampsloop.pop(0)
            else:
                x = 1
                timestampsloop = list(timestamps)
        else:
            time.sleep(0.001)
    time.sleep(BPM/60-timestamp)
