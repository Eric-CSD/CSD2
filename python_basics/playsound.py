import simpleaudio as sa

wave_obj = sa.WaveObject.from_wave_file('playsoundsample.wav')
loopje=0

while loopje==0:
    playAmount = input("How many times do you want to play the sample? ")
    if( playAmount.isdigit()):
        loopje=1
        playAmount = int(playAmount)
        for x in range(playAmount):
            print(x+1)
            play_obj = wave_obj.play()
            play_obj.wait_done()
    else:
        print("Please enter a number")
