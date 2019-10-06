#Imports
from midiutil import MIDIFile
import simpleaudio as sa
import time
import random
#Settings
kick = []
snare = []
hat = []
setup = 0
BPMSet = True
BPM = 120
loop = True
samples = [sa.WaveObject.from_wave_file("BeatGen/Hat1.wav"),
            sa.WaveObject.from_wave_file("BeatGen/Hat2.wav"),
                sa.WaveObject.from_wave_file("BeatGen/Snare1.wav"),
                    sa.WaveObject.from_wave_file("BeatGen/Snare2.wav"),
                        sa.WaveObject.from_wave_file("BeatGen/Kick1.wav"),
                            sa.WaveObject.from_wave_file("BeatGen/Kick2.wav"),]

print("Irregular Beat Generator V1")
print("Set a time signature like this: 'Integer/Integer'")
print("The second integer has to be a 4 or an 8")

#Asks for a time signature and puts both numbers in a list
#Asks again if the time signature is not valid
while setup == 0:
    print("Set the time signature:")
    timeSig = input()
    try:
        timeSig = timeSig.split("/")
    except:
        print("Invalid Input")
        continue
    try:
        for i in range(0, len(timeSig)):
            timeSig[i] = int(timeSig[i])
            setup = 1
    except:
        print("Invalid Input")
        setup = 0
        continue
    if len(timeSig) == 2:
        if timeSig[1] == 4 or timeSig[1] == 8:
            pass
        else:
            print("Invalid Input")
            setup = 0
    else:
        print("Invalid Input")
        setup = 0

#Asks for tempo
while BPMSet == True:
    print("Current BPM:", BPM)
    print("Change it to whatever number you want or enter 120 to keep it:")
    try:
        BPM = int(input())
        BPMSet = False
    except:
        print("Please Enter a Number!")

#Calculations on the time signature and adds necessary numbers
if timeSig[1] == 4:
    timeSig.insert(3,4)
    timeSig.insert(2,timeSig[0]*4)
    timeSig[1] = timeSig[1]*4
elif timeSig[1] == 8:
    timeSig.insert(3,2)
    timeSig.insert(2,timeSig[0]*2)
    timeSig[1] = timeSig[1]*2

#Calculates kick placement, always on first beat and "halfway"(odd signature)
#adds random placement, 1 for soft 2 for loud sound.
for i in range(timeSig[2]):
    if i == 0 or i == (round((timeSig[0]+0.5))/2)*timeSig[3]:
        kick.append(2)
    elif random.randint(0,100) >= 75:
        kick.append(random.randint(1,2))
    else:
        kick.append(0)
#Calculates snare placement, not on the same spot as kick + random placement
for i in range(timeSig[2]):
    if kick[i] > 0:
        snare.append(0)
    elif random.randint(0,100) >= 50:
        snare.append(random.randint(1,2))
    else:
        snare.append(0)
#Calculates hi-hat placement
for i in range(timeSig[2]):
    if random.randint(0,100) >= 30:
        hat.append(random.randint(1,2))
    else:
        hat.append(0)

#MIDIFile Settings
degrees  = kick # MIDI note number
track    = 0
channel  = 9
timer     = 0   # In beats
tempo    = BPM  # In BPM
volume   = 100 # 0-127, as per the MIDI standard
# Adds 1 miditrack
MyMIDI = MIDIFile(1)
MyMIDI.addTempo(track,timer, tempo)
#Write track for kick
for volume in degrees:
    MyMIDI.addNote(track, channel, 36, timer, 0.25, volume*50)
    timer = timer + 0.25
#Write track for snare
degrees = snare
timer = 0
for volume in degrees:
    MyMIDI.addNote(track, channel, 38, timer, 0.25, volume*50)
    timer = timer + 0.25
#Write track for hi0hat
degrees = hat
timer = 0
for volume in degrees:
    MyMIDI.addNote(track, channel, 42, timer, 0.25, volume*50)
    timer = timer + 0.25
#Write midi File
with open("Generated-Beat.mid", "wb") as output_file:
    MyMIDI.writeFile(output_file)

#Changes BPM to 16th note milliseconds
BPM = ((60000/BPM)/1000)/4
print(kick)
print(snare)
print(hat)

#Checks every 16th note what needs to be played and loops when done
i = 0
while loop == True:
    if i == len(kick):
        exit()
    else:
        startTime = time.time()
        x = 0
        while x == 0:
            currentTime = time.time()
            if(currentTime - startTime >= BPM):
                if kick[i] == 1:
                    samples[4].play()
                    if hat[i] == 1:
                        samples[0].play()
                        x =1
                    elif hat[i] == 2:
                        samples[1].play()
                        x = 1
                    x = 1
                elif kick[i] == 2:
                    samples[5].play()
                    if hat[i] == 1:
                        samples[0].play()
                        x =1
                    elif hat[i] == 2:
                        samples[1].play()
                        x = 1
                    x = 1
                elif snare[i] == 1:
                    samples[2].play()
                    if hat[i] == 1:
                        samples[0].play()
                        x =1
                    elif hat[i] == 2:
                        samples[1].play()
                        x = 1
                    x = 1
                elif snare[i] == 2:
                    samples[3].play()
                    if hat[i] == 1:
                        samples[0].play()
                        x =1
                    elif hat[i] == 2:
                        samples[1].play()
                        x = 1
                    x = 1
                elif hat[i] == 1:
                    samples[0].play()
                    x = 1
                elif hat[i] == 2:
                    samples[1].play()
                    x = 1
                else:
                    x = 1
            else:
                pass
    i += 1
    i = i % len(kick)
