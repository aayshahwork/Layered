/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class LayeredPluginAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    LayeredPluginAudioProcessorEditor (LayeredPluginAudioProcessor&);
    ~LayeredPluginAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    LayeredPluginAudioProcessor& audioProcessor;

    // UI Components
    juce::TextEditor textInput;
    juce::TextButton generateButton;
    juce::Label titleLabel;
    
    // Button click handler
    void generateButtonClicked();

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LayeredPluginAudioProcessorEditor)
};
