/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "DragAndDropComponent.h"

//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/
class MainComponent   : public Component,
public Slider::Listener
{
public:
    //==============================================================================
    MainComponent();
    ~MainComponent();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;

private:
    void sliderValueChanged(Slider* slider)override;
   
    Array<int> newModel = {0,2,3};
    Slider valueChanger;
    Label valueLabel;
    
    //envelope sliders and boxes
    ComboBox envelopeBox;
    Slider modSens;
    Slider modOffset;
    Slider modAttack;
    Slider modDecay;
    Slider modSustain;
    Slider modRelease;
    Slider modFloor;
    Slider modThreshold;
    Slider modMeter;
    ToggleButton modInvert;
    ToggleButton modON;
    
    //lfo sliders and boxes
    ComboBox LFOBox;
    ComboBox LFOForm;
    Slider LFOFreq;
    Slider LFODepth;
    Slider LFOMeter;
    ToggleButton LFOON;
    
    //efects sliders boxes buttons and lists
    TextButton FXButtonRight;
    TextButton FXButtonLeft;
    DragAndDropComponent dragAndDrop1;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
