import simpleaudio as sa                                                                    #Importeer time en simpleaudio module
import time

wave_obj = sa.WaveObject.from_wave_file('RythmicPlaybackSample.wav')                        #Laadt Sample in
Loop=0
RythmValues=[]

while Loop==0:                                                                              #Blijft loopen tot je een correct nummer invoert
    playAmount = input("How many times do you want to play the sample? ")
    if( playAmount.isdigit()):                                                              #Checkt of je een correct nummer invoert voor aantal sample plays
        Loop=1
        playAmount = int(playAmount)                                                        #Verandert de playamount string in een integer
        print("Give each note its own length, 1 = quarter note, 0.5 = 8th note etc.")
        for x in range(playAmount):                                                         #voor het aantal sample plays wordt een lijst gemaakt met nootlengtes
            NoteLength = input("Length of note " + str(x+1) + "? ")
            try:
                float(NoteLength)
                RythmValues.insert(x, NoteLength)
            except:
                print("Please enter a number")
                exit()

    else:
        print("Please enter a number")

BPM = input("What BPM should the samples be played at? ")                                   #vraagt naar en berekent het juiste tempo
if( BPM.isdigit()):
    BPM = 60000/int(BPM)
else:
    print("Please enter a number")
    exit()

for i in RythmValues:                                                                       #speelt de sample het opgegeven aantal keren af met de juiste afstanden in tijd
    i = float(i)
    play_obj = wave_obj.play()
    print(i*BPM)
    time.sleep((i*BPM)/1000)
