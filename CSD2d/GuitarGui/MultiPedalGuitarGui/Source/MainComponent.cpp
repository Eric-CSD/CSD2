/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent()
{
    setSize (1000, 400);
    
    //parameter value changer slider and label
    valueChanger.setRange(0, 10000);
    valueChanger.setSliderStyle(Slider::LinearBar);
    valueChanger.setColour(Slider::trackColourId, Colours::skyblue);
    valueChanger.setColour(Slider::textBoxOutlineColourId, Colours::darkgrey);
    valueChanger.setTextBoxStyle(Slider::TextBoxBelow, false, 50, 20);
    addAndMakeVisible(valueChanger);
    
    addAndMakeVisible (valueLabel);
    valueLabel.setText (":", dontSendNotification);
    valueLabel.attachToComponent (&valueChanger, true);
    valueLabel.setColour (Label::textColourId, Colours::darkgrey);
    valueLabel.setJustificationType (Justification::right);
    
    //buttons
    addAndMakeVisible(FXButtonRight);
    FXButtonRight.setButtonText(">");
    
    addAndMakeVisible(FXButtonLeft);
    FXButtonLeft.setButtonText("<");
    
    //drag and drop componnent
    addAndMakeVisible(dragAndDrop1);

    //boxes
    addAndMakeVisible (envelopeBox);
    envelopeBox.setColour(3,Colours::blue);
    envelopeBox.addSectionHeading ("Distortion");
    envelopeBox.addItem ("Drive",1);
    envelopeBox.addItem ("Tone",2);
    envelopeBox.addSeparator();
    envelopeBox.addSectionHeading ("Delay");
    envelopeBox.addItem ("Dry",3);
    envelopeBox.addItem ("Wet",4);
    envelopeBox.addItem ("Feedback",5);
    envelopeBox.addItem ("Time",6);
    envelopeBox.addItem ("PreDelay",7);
    envelopeBox.addSeparator();
    envelopeBox.setSelectedId (0);
    
    addAndMakeVisible (LFOBox);
    LFOBox.setColour(2,Colours::blue);
    LFOBox.addSectionHeading ("Distortion");
    LFOBox.addItem ("Drive",1);
    LFOBox.addItem ("Tone",2);
    LFOBox.addSeparator();
    LFOBox.addSectionHeading ("Delay");
    LFOBox.addItem ("Dry",3);
    LFOBox.addItem ("Wet",4);
    LFOBox.addItem ("Feedback",5);
    LFOBox.addItem ("Time",6);
    LFOBox.addItem ("PreDelay",7);
    LFOBox.addSeparator();
    LFOBox.setSelectedId (0);
    
    addAndMakeVisible (LFOForm);
    LFOForm.addItem ("Sine",1);
    LFOForm.addItem ("Square",2);
    LFOForm.addItem ("Saw",3);
    LFOBox.setSelectedId (0);
    
    //sliders
    modSens.setSliderStyle(Slider::LinearBar);
    modSens.setColour(Slider::trackColourId, Colour(0x80343d46));
    modSens.setColour(Slider::textBoxOutlineColourId, Colours::darkgrey);
    modSens.setRange(0.0, 1.0);
    modSens.setSkewFactor(0.5, false);
    modSens.setTextBoxStyle(Slider::NoTextBox, true, 90, 0);
    addAndMakeVisible(modSens);
    modSens.addListener (this);
    
    modOffset.setSliderStyle(Slider::LinearBar);
    modOffset.setColour(Slider::trackColourId, Colour(0x80343d46));
    modOffset.setColour(Slider::textBoxOutlineColourId, Colours::darkgrey);
    modOffset.setRange(0.0, 1.0);
    modOffset.setSkewFactor(0.5, false);
    modOffset.setTextBoxStyle(Slider::NoTextBox, true, 90, 0);
    addAndMakeVisible(modOffset);
    modOffset.addListener(this);
    
    modAttack.setSliderStyle(Slider::LinearBarVertical);
    modAttack.setColour(Slider::trackColourId, Colour(0x80343d46));
    modAttack.setColour(Slider::textBoxOutlineColourId, Colours::darkgrey);
    modAttack.setRange(0.0, 1000,1);
    modAttack.setSkewFactor(0.5, false);
    modAttack.setTextBoxStyle(Slider::NoTextBox, true, 90, 0);
    addAndMakeVisible(modAttack);
    modAttack.addListener(this);
    
    modDecay.setSliderStyle(Slider::LinearBarVertical);
    modDecay.setColour(Slider::trackColourId, Colour(0x80343d46));
    modDecay.setColour(Slider::textBoxOutlineColourId, Colours::darkgrey);
    modDecay.setRange(0.0, 1000,1);
    modDecay.setSkewFactor(0.5, false);
    modDecay.setTextBoxStyle(Slider::NoTextBox, true, 90, 0);
    addAndMakeVisible(modDecay);
    modDecay.addListener(this);
    
    modSustain.setSliderStyle(Slider::LinearBarVertical);
    modSustain.setColour(Slider::trackColourId, Colour(0x80343d46));
    modSustain.setColour(Slider::textBoxOutlineColourId, Colours::darkgrey);
    modSustain.setRange(0.0, 1);
    modSustain.setSkewFactor(0.5, false);
    modSustain.setTextBoxStyle(Slider::NoTextBox, true, 90, 0);
    addAndMakeVisible(modSustain);
    modSustain.addListener(this);
    
    modRelease.setSliderStyle(Slider::LinearBarVertical);
    modRelease.setColour(Slider::trackColourId, Colour(0x80343d46));
    modRelease.setColour(Slider::textBoxOutlineColourId, Colours::darkgrey);
    modRelease.setRange(0, 1000,1);
    modRelease.setSkewFactor(0.5, false);
    modRelease.setTextBoxStyle(Slider::NoTextBox, true, 90, 0);
    addAndMakeVisible(modRelease);
    modRelease.addListener(this);
    
    modFloor.setSliderStyle(Slider::LinearBar);
    modFloor.setColour(Slider::trackColourId, Colour(0x80343d46));
    modFloor.setColour(Slider::textBoxOutlineColourId, Colours::darkgrey);
    modFloor.setRange(0.0, 1.0);
    modFloor.setSkewFactor(0.5, false);
    modFloor.setTextBoxStyle(Slider::NoTextBox, true, 90, 0);
    addAndMakeVisible(modFloor);
    modFloor.addListener (this);
    
    modThreshold.setSliderStyle(Slider::LinearBar);
    modThreshold.setColour(Slider::trackColourId, Colour(0x80343d46));
    modThreshold.setColour(Slider::textBoxOutlineColourId, Colours::darkgrey);
    modThreshold.setRange(0.0, 1.0);
    modThreshold.setSkewFactor(0.5, false);
    modThreshold.setTextBoxStyle(Slider::NoTextBox, true, 90, 0);
    addAndMakeVisible(modThreshold);
    modThreshold.addListener (this);
    
    modMeter.setSliderStyle(Slider::LinearBar);
    modMeter.setColour(Slider::trackColourId, Colours::darkred);
    modMeter.setColour(Slider::textBoxOutlineColourId, Colours::darkgrey);
    modMeter.setRange(0.0, 1.0);
    modMeter.setSkewFactor(0.5, false);
    modMeter.setTextBoxStyle(Slider::NoTextBox, true, 90, 0);
    addAndMakeVisible(modMeter);
    modMeter.addListener (this);
    
    LFOMeter.setSliderStyle(Slider::LinearBar);
    LFOMeter.setColour(Slider::trackColourId, Colours::darkred);
    LFOMeter.setColour(Slider::textBoxOutlineColourId, Colours::darkgrey);
    LFOMeter.setRange(0.0, 1.0);
    LFOMeter.setSkewFactor(0.5, false);
    LFOMeter.setTextBoxStyle(Slider::NoTextBox, true, 90, 0);
    addAndMakeVisible(LFOMeter);
    LFOMeter.addListener (this);
    
    LFOFreq.setSliderStyle(Slider::LinearBar);
    LFOFreq.setColour(Slider::trackColourId, Colour(0x80343d46));
    LFOFreq.setColour(Slider::textBoxOutlineColourId, Colours::darkgrey);
    LFOFreq.setRange(0.0, 10.0);
    LFOFreq.setSkewFactor(0.5, false);
    LFOFreq.setTextBoxStyle(Slider::NoTextBox, true, 90, 0);
    addAndMakeVisible(LFOFreq);
    LFOFreq.addListener (this);
    
    LFODepth.setSliderStyle(Slider::LinearBar);
    LFODepth.setColour(Slider::trackColourId, Colour(0x80343d46));
    LFODepth.setColour(Slider::textBoxOutlineColourId, Colours::darkgrey);
    LFODepth.setRange(0.0, 1.0);
    LFODepth.setSkewFactor(0.5, false);
    LFODepth.setTextBoxStyle(Slider::NoTextBox, true, 90, 0);
    addAndMakeVisible(LFODepth);
    LFODepth.addListener(this);
    
    //Buttons
    addAndMakeVisible(modInvert);
    modInvert.setColour(ToggleButton::tickColourId,Colours::darkgrey);
    modInvert.setColour(ToggleButton::tickDisabledColourId,Colours::darkgrey);
    
    addAndMakeVisible(modON);
    modON.setColour(ToggleButton::tickColourId,Colours::darkgrey);
    modON.setColour(ToggleButton::tickDisabledColourId,Colours::darkgrey);
    
    addAndMakeVisible(LFOON);
    LFOON.setColour(ToggleButton::tickColourId,Colours::darkgrey);
    LFOON.setColour(ToggleButton::tickDisabledColourId,Colours::darkgrey);
}

MainComponent::~MainComponent()
{
}

//==============================================================================
void MainComponent::paint (Graphics& g)
{
    //background colour
    g.fillAll (Colours::skyblue);
    
    //drawing all squares
    g.setColour (Colours::orange);
    Rectangle<int> Logo (Point<int> (4, 5),
                         Point<int> (88, 35));
    g.fillRect (Logo);
    
    g.setColour (Colours::lightgrey);
    Rectangle<int> modSquare (Point<int> (5, 40),
                         Point<int> (990, 200));
    g.fillRect (modSquare);
    
    g.setColour (Colours::darkgrey);
    Rectangle<int> modOutline (Point<int> (5, 40),
                         Point<int> (990, 200));
    g.drawRect(modOutline,3.0f);
    
    g.setColour (Colours::darkgrey);
    Rectangle<int> modHeaderOutline (Point<int> (5, 40),
                         Point<int> (990, 60));
    g.drawRect(modHeaderOutline,3.0f);
    
    g.setColour (Colours::darkgrey);
    Rectangle<int> mod1Outline (Point<int> (5, 40),
                         Point<int> (990, 120));
    g.drawRect(mod1Outline,3.0f);
    
    g.setColour (Colours::darkgrey);
    Rectangle<int> mod2Outline (Point<int> (5, 40),
                         Point<int> (990, 180));
    g.drawRect(mod2Outline,3.0f);
    
    g.setColour (Colours::darkgrey);
    Rectangle<int> FXOutline (Point<int> (5, 40),
                         Point<int> (990, 180));
    g.drawRect(FXOutline,3.0f);
    
    g.setColour (Colours::lightgrey);
    Rectangle<int> fxSquare (Point<int> (5, 210),
                         Point<int> (990, 390));
    g.fillRect (fxSquare);
    
    g.setColour (Colours::darkgrey);
    Rectangle<int> fxOutline (Point<int> (5, 210),
                         Point<int> (990, 390));
    g.drawRect(fxOutline,3.0f);
    
    g.setColour (Colours::darkgrey);
    Rectangle<int> fxHeaderOutline (Point<int> (5, 210),
                         Point<int> (990, 230));
    g.drawRect(fxHeaderOutline,3.0f);
    
    //drawing all text
    
    //grey
    g.setColour(Colours::darkgrey);
    g.setFont(Font("Helvetica", 30.0f, 0));
    g.drawFittedText("Guitar Multi FX", 5, 20, getWidth(), 5, 0, 1);
    
    g.setFont(Font("Helvetica", 13.0f, 0));
    g.drawFittedText("Last Parameter Change:", 220, 19, getWidth(), 5, 0, 1);
    
    g.setFont(Font("Helvetica", 10.0f, 0));
    g.drawFittedText("MODULATION", 10, 50, getWidth(), 5, 0, 1);
    
    g.drawFittedText("EFFECTS", 10, 220, getWidth(), 5, 0, 1);
    
    g.drawFittedText("Auto Envelope 1:", 10, 70, getWidth(), 5, 0, 1);
    
    g.drawFittedText("LFO 1:", 10, 130, getWidth(), 5, 0, 1);
    
    g.drawFittedText("Add Effect:", 10, 240, getWidth(), 5, 0, 1);
    
    g.drawFittedText("WAVEFORM:", 365, 130, getWidth(), 5, 0, 1);
    
    g.drawFittedText("INVERT:", 540, 70, getWidth(),5, 0 ,1);
    
    g.drawFittedText("ON/OFF:", 900, 70, getWidth(),5, 0 ,1);
    
    g.drawFittedText("ON/OFF:", 900, 132, getWidth(),5, 0 ,1);
    
    //blue
    g.setColour(Colours::darkslateblue);
    g.drawFittedText("ADD MODULATION +", 10, 185, getWidth(), 5, 0, 1);
    
    //orange
    g.setColour(Colours::orange);
    g.setFont(Font("Helvetica", 13.0f, 1));
    g.drawFittedText("SENSITIVITY", 205, 74, getWidth(), 5, 0, 1);
    
    g.drawFittedText("OFFSET", 205, 99, getWidth(), 5, 0, 1);
    
    g.drawFittedText("FREQUENCY", 205, 136, getWidth(), 5, 0, 1);
    
    g.drawFittedText("DEPTH", 205, 161, getWidth(), 5, 0, 1);
    
    g.drawFittedText("A", 315, 99, getWidth(), 5, 0, 1);
    g.drawFittedText("D", 345, 99, getWidth(), 5, 0, 1);
    g.drawFittedText("S", 375, 99, getWidth(), 5, 0, 1);
    g.drawFittedText("R", 405, 99, getWidth(), 5, 0, 1);
    
    g.drawFittedText("FLOOR", 435, 74, getWidth(), 5, 0, 1);
    
    g.drawFittedText("THRESHOLD", 435, 99, getWidth(), 5, 0, 1);
    
    //red
    g.setColour(Colours::red);
    g.drawFittedText("METER", 545, 99, getWidth(), 5, 0, 1);
    
    g.drawFittedText("METER", 545, 161, getWidth(), 5, 0, 1);


    
}

void MainComponent::resized()
{
    //draw envelope
    modOffset.setBounds(200,90,100,20);
    modSens.setBounds(200,65,100,20);
    envelopeBox.setBounds (90, 62, 100, 20);
    modAttack.setBounds(310,65,20,45);
    modDecay.setBounds(340, 65,20,45);
    modSustain.setBounds(370, 65,20,45);
    modRelease.setBounds(400,65,20,45);
    modFloor.setBounds(430,65,100,20);
    modThreshold.setBounds(430,90,100,20);
    modMeter.setBounds(540, 90, 100, 20);
    modInvert.setBounds(580,60,25,25);
    modON.setBounds(950,60,25,25);
    
    
    
    //draw lfo
    LFOForm.setBounds(430,122,100,20);
    LFODepth.setBounds(200,152,100,20);
    LFOFreq.setBounds(200,127,100,20);
    LFOMeter.setBounds(540,152,100,20);
    LFOBox.setBounds(90,122,100,20);
    LFOON.setBounds(950,122,25,25);
    valueChanger.setBounds(500,10,100,20);
    
    //draw effects panel
    FXButtonRight.setBounds(950,230, 37, 157);
    FXButtonLeft.setBounds(100,230,37,157);
    dragAndDrop1.setBounds(getLocalBounds().reduced (1));
    
}

void MainComponent::sliderValueChanged(Slider* slider)
{
    //sending all changed parameter data to top slider
    if (slider == &modSens){
        valueChanger.setValue(modSens.getValue());
        valueLabel.setText ("Envelope Sensitivity:", dontSendNotification);
    } else if (slider == &modOffset){
        valueChanger.setValue(modOffset.getValue());
        valueLabel.setText ("Envelope Offset:", dontSendNotification);
    } else if (slider == &modAttack){
        valueChanger.setValue(modAttack.getValue());
        valueLabel.setText ("Envelope Attack:", dontSendNotification);
    } else if (slider == &modDecay){
        valueChanger.setValue(modDecay.getValue());
        valueLabel.setText ("Envelope Decay:", dontSendNotification);
    } else if (slider == &modSustain){
        valueChanger.setValue(modSustain.getValue());
        valueLabel.setText ("Envelope Sustain:", dontSendNotification);
    } else if (slider == &modRelease){
        valueChanger.setValue(modRelease.getValue());
        valueLabel.setText ("Envelope Release:", dontSendNotification);
    } else if (slider == &modFloor){
        valueChanger.setValue(modFloor.getValue());
        valueLabel.setText ("Envelope Floor:", dontSendNotification);
    } else if (slider == &modThreshold){
        valueChanger.setValue(modThreshold.getValue());
        valueLabel.setText ("Envelope Threshold:", dontSendNotification);
    } else if (slider == &LFOFreq){
        valueChanger.setValue(LFOFreq.getValue());
        valueLabel.setText ("LFO Frequency:", dontSendNotification);
    } else if (slider == &LFODepth){
        valueChanger.setValue(LFODepth.getValue());
        valueLabel.setText ("LFO Depth:", dontSendNotification);
    }
}
