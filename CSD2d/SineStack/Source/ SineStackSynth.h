

/*******************************************************************************
 The block below describes the properties of this PIP. A PIP is a short snippet
 of code that can be read by the Projucer and used to generate a JUCE project.

 BEGIN_JUCE_PIP_METADATA

 name:            Sine Synth
 version:          2.0.0
 vendor:           JUCE
 website:          http://juce.com
 description:      Synthesiser with midi input.

 dependencies:     juce_audio_basics, juce_audio_devices, juce_audio_formats,
                   juce_audio_processors, juce_audio_utils, juce_core,
                   juce_data_structures, juce_events, juce_graphics,
                   juce_gui_basics, juce_gui_extra
 exporters:        xcode_mac, vs2017, linux_make

 type:             Component
 mainClass:        MainContentComponent

 useLocalCopy:     1

 END_JUCE_PIP_METADATA

*******************************************************************************/


#pragma once

//==============================================================================
struct SineWaveSound   : public SynthesiserSound
{
    SineWaveSound() {}

    bool appliesToNote    (int) override        { return true; }
    bool appliesToChannel (int) override        { return true; }
};

//==============================================================================
//Sinewave struct to use with synthesizer, calculates frequency and waveform from midi input
//note on, note off information 4 voice polyphonic
struct SineWaveVoice   : public SynthesiserVoice
{
    SineWaveVoice() {}

    bool canPlaySound (SynthesiserSound* sound) override
    {
        return dynamic_cast<SineWaveSound*> (sound) != nullptr;
    }

    void startNote (int midiNoteNumber, float velocity,
                    SynthesiserSound*, int /*currentPitchWheelPosition*/) override
    {
        currentAngle = 0.0;
        level = velocity * 0.15;
        tailOff = 0.0;

        auto cyclesPerSecond = MidiMessage::getMidiNoteInHertz (midiNoteNumber);
        auto cyclesPerSample = cyclesPerSecond / getSampleRate();

        angleDelta = cyclesPerSample * 2.0 * MathConstants<double>::pi;
    }

    void stopNote (float /*velocity*/, bool allowTailOff) override
    {
        if (allowTailOff)
        {
            if (tailOff == 0.0)
                tailOff = 1.0;
        }
        else
        {
            clearCurrentNote();
            angleDelta = 0.0;
        }
    }

    void pitchWheelMoved (int) override      {}
    void controllerMoved (int, int) override {}

    void renderNextBlock (AudioSampleBuffer& outputBuffer, int startSample, int numSamples) override
    {
        if (angleDelta != 0.0)
        {
            if (tailOff > 0.0) // [7]
            {
                while (--numSamples >= 0)
                {
                    auto currentSample = (float) (std::sin (currentAngle) * level * tailOff);

                    for (auto i = outputBuffer.getNumChannels(); --i >= 0;)
                        outputBuffer.addSample (i, startSample, currentSample);

                    currentAngle += angleDelta;
                    ++startSample;

                    tailOff *= 0.99; // [8]

                    if (tailOff <= 0.005)
                    {
                        clearCurrentNote(); // [9]

                        angleDelta = 0.0;
                        break;
                    }
                }
            }
            else
            {
                while (--numSamples >= 0) // [6]
                {
                    auto currentSample = (float) (std::sin (currentAngle) * level);

                    for (auto i = outputBuffer.getNumChannels(); --i >= 0;)
                        outputBuffer.addSample (i, startSample, currentSample);

                    currentAngle += angleDelta;
                    ++startSample;
                }
            }
        }
    }

private:
    double currentAngle = 0.0, angleDelta = 0.0, level = 0.0, tailOff = 0.0;
};

//==============================================================================
class SynthAudioSource   : public AudioSource
{
public:
    SynthAudioSource (MidiKeyboardState& keyState)
        : keyboardState (keyState)
    {
        for (auto i = 0; i < 4; ++i)
            synth.addVoice (new SineWaveVoice());

        synth.addSound (new SineWaveSound());
    }

    void setUsingSineWaveSound()
    {
        synth.clearSounds();
    }

    void prepareToPlay (int /*samplesPerBlockExpected*/, double sampleRate) override
    {
        synth.setCurrentPlaybackSampleRate (sampleRate);
        midiCollector.reset (sampleRate);
    }

    void releaseResources() override {}

    void getNextAudioBlock (const AudioSourceChannelInfo& bufferToFill) override
    {
        bufferToFill.clearActiveBufferRegion();

        MidiBuffer incomingMidi;
        midiCollector.removeNextBlockOfMessages (incomingMidi, bufferToFill.numSamples);

        keyboardState.processNextMidiBuffer (incomingMidi, bufferToFill.startSample,
                                             bufferToFill.numSamples, true);

        synth.renderNextBlock (*bufferToFill.buffer, incomingMidi,
                               bufferToFill.startSample, bufferToFill.numSamples);
    }

    MidiMessageCollector* getMidiCollector()
    {
        return &midiCollector;
    }

private:
    MidiKeyboardState& keyboardState;
    Synthesiser synth;
    MidiMessageCollector midiCollector;
};

//==============================================================================
//wave table for calculated sine, 128 sample buffer
class WavetableOscillator
{
public:
    WavetableOscillator (const AudioSampleBuffer& wavetableToUse)
        : wavetable (wavetableToUse),
          tableSize (wavetable.getNumSamples() - 1)
    {
        jassert (wavetable.getNumChannels() == 1);
    }

    void setFrequency (float frequency, float sampleRate)
    {
        auto tableSizeOverSampleRate = tableSize / sampleRate;
        tableDelta = frequency * tableSizeOverSampleRate;
    }

    forcedinline float getNextSample() noexcept
    {
        auto index0 = (unsigned int) currentIndex;
        auto index1 = index0 + 1;

        auto frac = currentIndex - (float) index0;

        auto* table = wavetable.getReadPointer (0);
        auto value0 = table[index0];
        auto value1 = table[index1];

        auto currentSample = value0 + frac * (value1 - value0);

        if ((currentIndex += tableDelta) > tableSize)
            currentIndex -= tableSize;

        return currentSample;
    }

private:
    const AudioSampleBuffer& wavetable;
    const int tableSize;
    float currentIndex = 0.0f, tableDelta = 0.0f;
};

//==============================================================================
//main component for gui, and audio player
class MainContentComponent   : public AudioAppComponent,
                               public Timer,
                               public Slider::Listener,
                               public MidiInputCallback
{
public:
    MainContentComponent()
        : synthAudioSource  (keyboardState),
          keyboardComponent (keyboardState, MidiKeyboardComponent::horizontalKeyboard)
    {
        audioDeviceManager.setMidiInputEnabled("MPKmini2", true);
        audioDeviceManager.addMidiInputCallback ("", this);

        //labels and gui for midi information (keyboard)
        midiLabel.setText("midiText", sendNotification);
        addAndMakeVisible(midiLabel);
        addAndMakeVisible (midiInputListLabel);
        midiInputListLabel.setText ("MIDI Input:", dontSendNotification);
        midiInputListLabel.attachToComponent (&midiInputList, true);

        auto midiInputs = MidiInput::getAvailableDevices();
        addAndMakeVisible (midiInputList);
        midiInputList.setTextWhenNoChoicesAvailable ("No MIDI Inputs Enabled");

        StringArray midiInputNames;
        for (auto input : midiInputs)
            midiInputNames.add (input.name);

        midiInputList.addItemList (midiInputNames, 1);
        midiInputList.onChange = [this] { setMidiInput (midiInputList.getSelectedItemIndex()); };

        for (auto input : midiInputs)
        {
            if (deviceManager.isMidiInputDeviceEnabled (input.identifier))
            {
                setMidiInput (midiInputs.indexOf (input));
                break;
            }
        }

        if (midiInputList.getSelectedId() == 0)
            setMidiInput (0);
        //labels and sliders for all gui information
        addAndMakeVisible (keyboardComponent);
        addAndMakeVisible (frequencySlider);
        addAndMakeVisible (spreadSlider);
        addAndMakeVisible (tremoloSlider);
        spreadSlider.setRange(1,12,1);
        spreadSlider.setTextValueSuffix("Semitones");
        spreadSlider.addListener(this);
        spreadLabel.setText("Spread",dontSendNotification);
        spreadLabel.attachToComponent (&spreadSlider, true);
        tremoloSlider.setRange(0.1,1);
        tremoloSlider.addListener(this);
        tremoloLabel.setText("Tremolo Speed",dontSendNotification);
        tremoloLabel.attachToComponent (&tremoloSlider, true);
        frequencySlider.setRange (1, 20, 1);          // [1]
        frequencySlider.setTextValueSuffix ("");     // [2]
        frequencySlider.addListener (this);             // [3]
        addAndMakeVisible (frequencyLabel);
        frequencyLabel.setText ("Amount of Oscillators", dontSendNotification);
        frequencyLabel.attachToComponent (&frequencySlider, true); // [4]

        cpuUsageLabel.setText ("CPU Usage", dontSendNotification);
        cpuUsageText.setJustificationType (Justification::right);
        addAndMakeVisible (cpuUsageLabel);
        addAndMakeVisible (cpuUsageText);

        //startup settings for all sliders
        createWavetable();
        spreadSlider.setValue(3);
        tremoloSlider.setValue(0.1);
        frequencySlider.setValue (5); // [5]
        //set app size and stereo channels
        setAudioChannels (0, 2);
        setSize (600, 400);
        startTimer (400);
    }

    ~MainContentComponent() override
    {
        shutdownAudio();
    }
    //gui information, label and slider size and orientatio
    void resized() override
    {
        auto sliderLeft = 120;
        tremoloSlider.setBounds(sliderLeft, 110, getWidth()-sliderLeft-10, 30);
        spreadSlider.setBounds(sliderLeft, 70, getWidth()-sliderLeft-10, 30);
        frequencySlider.setBounds (sliderLeft, 30, getWidth() - sliderLeft - 10, 30);
        midiInputList    .setBounds (200, 10, getWidth() - 210, 20);
        keyboardComponent.setBounds (10,  250, getWidth() - 20, getHeight() - 250);
    }
    //handlws midi data to be sent to wavetable
   void handleIncomingMidiMessage(MidiInput*, const MidiMessage& message) override
{
    DBG(message.getNoteNumber());
    noteCalc++;
    int noteChecker2;
    //checks if note has to be played (on/off midi info)
    noteChecker = message.getNoteNumber();
    if (noteCalc%2==0){
    if (noteChecker2!=noteChecker){
        prepareToPlay(128, 44100);
    } else {
        oscillators.clear();
    }
    }

    //display label text debug information
    String midiText;
    if (message.isNoteOnOrOff()) {
        midiText << "NoteOn: Channel " << message.getChannel();
        midiText << ":Number" << message.getNoteNumber();
        midiText << ":Velocity" << message.getVelocity();
    }
    midiLabel.getTextValue() = midiText;
    noteChecker2 = message.getNoteNumber();
}
    //checks sliders after every value change
    void sliderValueChanged (Slider* slider) override
    {
        if (slider == &frequencySlider)
            durationSlider.setValue (1.0 / frequencySlider.getValue(), dontSendNotification);
        else if (slider == &durationSlider)
            frequencySlider.setValue (1.0 / durationSlider.getValue(), dontSendNotification);
        prepareToPlay(128, 44100);
    }
    //harmonic wavetable for sine wave stacks
    void createWavetable()
    {
        sineTable.setSize (1, (int) tableSize + 1);
        sineTable.clear();

        auto* samples = sineTable.getWritePointer (0);

        int harmonics[] = { 1, 3, 5, 6, 7, 9, 13, 15 };
        float harmonicWeights[] = { 0.5f, 0.1f, 0.05f, 0.125f, 0.09f, 0.005f, 0.002f, 0.001f };

        jassert (numElementsInArray (harmonics) == numElementsInArray (harmonicWeights));

        for (auto harmonic = 0; harmonic < numElementsInArray (harmonics); ++harmonic)
        {
            auto angleDelta = MathConstants<double>::twoPi / (double) (tableSize - 1) * harmonics[harmonic];
            auto currentAngle = 0.0;

            for (unsigned int i = 0; i < tableSize; ++i)
            {
                auto sample = std::sin (currentAngle);
                samples[i] += (float) sample * harmonicWeights[harmonic];
                currentAngle += angleDelta;
            }
        }

        samples[tableSize] = samples[0];
    }
//create the amountn of oscillators with the played midi pitch and spread
//notes get randomly spread to the size of spreadslider
    void prepareToPlay (int samplesPerBlockExpected, double sampleRate) override
    {

        synthAudioSource.prepareToPlay (samplesPerBlockExpected, sampleRate);
        auto numberOfOscillators = int(frequencySlider.getValue());
        oscillators.clear();

        for (auto i = 0; i < numberOfOscillators; ++i)
        {
            auto* oscillator = new WavetableOscillator (sineTable);

            auto midiNote = Random::getSystemRandom().nextDouble() * spreadSlider.getValue() + noteChecker;
            std::cout<<noteChecker<<"  "<<midiNote<<std::endl;
            auto frequency = 440.0 * pow (2.0, (midiNote - 69.0) / 12.0);

            oscillator->setFrequency ((float) frequency, (float) sampleRate);
            oscillators.add (oscillator);
        }
    }
//play buffer and add tremolo slider information
    void getNextAudioBlock (const AudioSourceChannelInfo& bufferToFill) override
    {
        level2 =tremoloSlider.getValue()/100;
        if(ampMeter==0&&level>0.001){
            level= level-level2;
        } else if(ampMeter==0&&level<0.001){
            level= level-level2;
            ampMeter=1;
        } else if(ampMeter==1&&level<0.2){
            level=level+level2;
        } else if(ampMeter==1&&level>0.2){
            level=level+level2;;
            ampMeter=0;
        }
        std::cout<<level<<std::endl;

        synthAudioSource.getNextAudioBlock (bufferToFill);
        auto* leftBuffer  = bufferToFill.buffer->getWritePointer (0, bufferToFill.startSample);
        auto* rightBuffer = bufferToFill.buffer->getWritePointer (1, bufferToFill.startSample);

        bufferToFill.clearActiveBufferRegion();

        for (auto oscillatorIndex = 0; oscillatorIndex < oscillators.size(); ++oscillatorIndex)
        {
            auto* oscillator = oscillators.getUnchecked (oscillatorIndex);

            for (auto sample = 0; sample < bufferToFill.numSamples; ++sample)
            {
                auto levelSample = oscillator->getNextSample() * level;

                leftBuffer[sample]  += levelSample;
                rightBuffer[sample] += levelSample;
            }
        }
    }

    void releaseResources() override
    {
        synthAudioSource.releaseResources();
    }


private:
  //labels/sliders
    Slider frequencySlider;
    Slider spreadSlider;
    Label spreadLabel;
    Slider tremoloSlider;
    Label tremoloLabel;
    Label frequencyLabel;
    Slider durationSlider;
    Label durationLabel;
    Label cpuUsageLabel;
    Label cpuUsageText;

    const unsigned int tableSize = 1 << 7;
    float level = 0.0f;

    AudioSampleBuffer sineTable;
    OwnedArray<WavetableOscillator> oscillators;
    void timerCallback() override
    {
        auto cpu = deviceManager.getCpuUsage() * 100;
        cpuUsageText.setText (String (cpu, 6) + " %", dontSendNotification);
        keyboardComponent.grabKeyboardFocus();
        stopTimer();
    }

    void setMidiInput (int index)
    {
        auto list = MidiInput::getAvailableDevices();

        deviceManager.removeMidiInputDeviceCallback (list[lastInputIndex].identifier, synthAudioSource.getMidiCollector());

        auto newInput = list[index];

        if (! deviceManager.isMidiInputDeviceEnabled (newInput.identifier))
            deviceManager.setMidiInputDeviceEnabled (newInput.identifier, true);

        deviceManager.addMidiInputDeviceCallback (newInput.identifier, synthAudioSource.getMidiCollector());
        midiInputList.setSelectedId (index + 1, dontSendNotification);

        lastInputIndex = index;
    }

    //==========================================================================
    SynthAudioSource synthAudioSource;
    MidiKeyboardState keyboardState;
    MidiKeyboardComponent keyboardComponent;
    AudioDeviceManager audioDeviceManager;
    Label midiLabel;
    ComboBox midiInputList;
    Label midiInputListLabel;
    int lastInputIndex = 0;
    int noteChecker;
    int noteCalc =0;
    int ampMeter=0;
    double level2=0;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainContentComponent)
};
