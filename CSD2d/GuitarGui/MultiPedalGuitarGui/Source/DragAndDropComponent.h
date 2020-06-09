/*
  ==============================================================================

    DragAndDropComponent.h
    Created: 9 Jun 2020 7:34:15pm
    Author:  Eric Schuster

  ==============================================================================
*/
//Class to add List and Dragging functionality

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class DragAndDropComponent  : public Component,
                         public DragAndDropContainer
{
public:
    DragAndDropComponent()
    {
        setName ("Drag-and-Drop");

        sourceListBox.setModel (&sourceModel);
        sourceListBox.setMultipleSelectionEnabled (true);
        //create list box and target boxes
        addAndMakeVisible (sourceListBox);
        addAndMakeVisible (target);
        addAndMakeVisible (target2);
        addAndMakeVisible (target3);
    }

    void resized() override
    {
        //draw list and target boxes
        sourceListBox.setBounds (7,250,93,137);
        target.setBounds (137,230,271,157);
        target2.setBounds  (408,230,271,157);
        target3.setBounds(679,230,271,157);
    }

private:
    //==============================================================================
    struct SourceItemListboxContents  : public ListBoxModel
    {
        // The following methods implement the necessary virtual functions from ListBoxModel,
        // telling the listbox how many rows there are, painting them, etc.
        int getNumRows() override
        {
            return 8;
        }

        void paintListBoxItem (int rowNumber, Graphics& g,
                               int width, int height, bool rowIsSelected) override
        {
            if (rowIsSelected)
                g.fillAll (Colours::lightblue);

            g.setColour (LookAndFeel::getDefaultLookAndFeel().findColour (Label::textColourId));
            g.setFont (height * 0.7f);
            //This nice big if statement lists the different effects in the listbox
            if(rowNumber==0){
                g.drawText ("Compressor",
                        5, 0, width, height,
                        Justification::centredLeft, true);
            } else if(rowNumber ==1){
                g.drawText ("Delay",
                5, 0, width, height,
                Justification::centredLeft, true);
            } else if(rowNumber ==2){
                g.drawText ("Distortion",
                5, 0, width, height,
                Justification::centredLeft, true);
            } else if(rowNumber ==3){
                g.drawText ("Filter",
                5, 0, width, height,
                Justification::centredLeft, true);
            } else if(rowNumber ==4){
                g.drawText ("Reverb",
                5, 0, width, height,
                Justification::centredLeft, true);
            } else if(rowNumber ==5){
                g.drawText ("RingMod",
                5, 0, width, height,
                Justification::centredLeft, true);
            } else if(rowNumber ==6){
                g.drawText ("Tuner",
                5, 0, width, height,
                Justification::centredLeft, true);
            } else if(rowNumber ==7){
                g.drawText ("Vol/Pan",
                5, 0, width, height,
                Justification::centredLeft, true);
            }
        };


        var getDragSourceDescription (const SparseSet<int>& selectedRows) override
        {
            // for our drag description, we'll just make a comma-separated list of the selected row
            // numbers - this will be picked up by the drag target and displayed in its box.
            StringArray rows;

            for (int i = 0; i < selectedRows.size(); ++i)
                rows.add (String (selectedRows[i] + 1));

            return rows.joinIntoString (", ");
        }
    };
    //==============================================================================
    // and this is a component that can have things dropped onto it..
    class DragAndDropTargetDemo : public Component,
                                  public DragAndDropTarget,
                                  public FileDragAndDropTarget,
                                  public TextDragAndDropTarget
    {
    public:
        DragAndDropTargetDemo()    {}

        void paint (Graphics& g) override
        {
            g.fillAll (Colours::grey.withAlpha (0.8f));

            // draw a red line around the comp if the user's currently dragging something over it..
            if (somethingIsBeingDraggedOver)
            {
                g.setColour (Colours::red);
                g.drawRect (getLocalBounds(), 3);
            }

            g.setColour (getLookAndFeel().findColour (Label::textColourId));
            g.setFont (14.0f);
            g.drawFittedText (message, getLocalBounds().reduced (10, 0), Justification::centred, 4);
        }

        //==============================================================================
        // These methods implement the DragAndDropTarget interface, and allow our component
        // to accept drag-and-drop of objects from other JUCE components..

        bool isInterestedInDragSource (const SourceDetails& /*dragSourceDetails*/) override
        {
         //always interesting apparantly :)
            return true;
        }

        void itemDragEnter (const SourceDetails& /*dragSourceDetails*/) override
        {
            somethingIsBeingDraggedOver = true;
            repaint();
        }

        void itemDragMove (const SourceDetails& /*dragSourceDetails*/) override
        {
        }

        void itemDragExit (const SourceDetails& /*dragSourceDetails*/) override
        {
            somethingIsBeingDraggedOver = false;
            repaint();
        }
//Loads message for "plugin"
        void itemDropped (const SourceDetails& dragSourceDetails) override
        {
            if (dragSourceDetails.description.toString()=="1"){
                message = "Compressor Loaded";
            } else if (dragSourceDetails.description.toString()=="2"){
                message = "Delay Loaded";
            } else if (dragSourceDetails.description.toString()=="3"){
                           message = "Distortion Loaded";
            } else if (dragSourceDetails.description.toString()=="4"){
                           message = "Filter Loaded";
            } else if (dragSourceDetails.description.toString()=="5"){
                           message = "Reverb Loaded";
            } else if (dragSourceDetails.description.toString()=="6"){
                           message = "RingMod Loaded";
            } else if (dragSourceDetails.description.toString()=="7"){
                           message = "Tuner Loaded";
            } else if (dragSourceDetails.description.toString()=="8"){
                           message = "Volume/Panner Loaded";
            }
            somethingIsBeingDraggedOver = false;
            repaint();
        }

        //==============================================================================
        // These methods implement the FileDragAndDropTarget interface, and allow our component
        // to accept drag-and-drop of files not yet implemented in this prototype

        bool isInterestedInFileDrag (const StringArray& /*files*/) override
        {
            return true;
        }

        void fileDragEnter (const StringArray& /*files*/, int /*x*/, int /*y*/) override
        {
            somethingIsBeingDraggedOver = true;
            repaint();
        }

        void fileDragMove (const StringArray& /*files*/, int /*x*/, int /*y*/) override
        {
        }

        void fileDragExit (const StringArray& /*files*/) override
        {
            somethingIsBeingDraggedOver = false;
            repaint();
        }

        void filesDropped (const StringArray& files, int /*x*/, int /*y*/) override
        {
            message = "Files dropped: " + files.joinIntoString ("\n");

            somethingIsBeingDraggedOver = false;
            repaint();
        }

        //==============================================================================
        // These methods implement the TextDragAndDropTarget interface, and allow our component
        // to accept drag-and-drop of text, not yet implemented in this prototype

        bool isInterestedInTextDrag (const String& /*text*/) override
        {
            return true;
        }

        void textDragEnter (const String& /*text*/, int /*x*/, int /*y*/) override
        {
            somethingIsBeingDraggedOver = true;
            repaint();
        }

        void textDragMove (const String& /*text*/, int /*x*/, int /*y*/) override
        {
        }

        void textDragExit (const String& /*text*/) override
        {
            somethingIsBeingDraggedOver = false;
            repaint();
        }

        void textDropped (const String& text, int /*x*/, int /*y*/) override
        {
            message = "Text dropped:\n" + text;

            somethingIsBeingDraggedOver = false;
            repaint();
        }

    private:
        String message  { "Drag a plugin into the chain to use it."};
        bool somethingIsBeingDraggedOver = false;
    };

    //==============================================================================
    ListBox sourceListBox  { "D+D source", nullptr };
    SourceItemListboxContents sourceModel;
    DragAndDropTargetDemo target;
    DragAndDropTargetDemo target2;
    DragAndDropTargetDemo target3;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DragAndDropComponent)
};

