/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
LayeredPluginAudioProcessorEditor::LayeredPluginAudioProcessorEditor (LayeredPluginAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    // Setup title label
    titleLabel.setText("Layered - AI Music Production Copilot", juce::dontSendNotification);
    titleLabel.setFont(juce::FontOptions(24.0f, juce::Font::bold));
    titleLabel.setJustificationType(juce::Justification::centred);
    titleLabel.setColour(juce::Label::textColourId, juce::Colours::white);
    addAndMakeVisible(titleLabel);
    
    // Setup text input
    textInput.setMultiLine(true);
    textInput.setReturnKeyStartsNewLine(true);
    textInput.setScrollbarsShown(true);
    textInput.setCaretVisible(true);
    textInput.setPopupMenuEnabled(true);
    textInput.setTextToShowWhenEmpty("Describe what you want to create in your music production session...", juce::Colours::grey);
    textInput.setColour(juce::TextEditor::backgroundColourId, juce::Colour(0xff2a2a2a));
    textInput.setColour(juce::TextEditor::textColourId, juce::Colours::white);
    textInput.setColour(juce::TextEditor::highlightColourId, juce::Colour(0xff4a90e2));
    textInput.setColour(juce::TextEditor::outlineColourId, juce::Colour(0xff555555));
    textInput.setFont(juce::FontOptions(14.0f));
    addAndMakeVisible(textInput);
    
    // Setup generate button
    generateButton.setButtonText("Generate");
    generateButton.setColour(juce::TextButton::buttonColourId, juce::Colour(0xff4a90e2));
    generateButton.setColour(juce::TextButton::buttonOnColourId, juce::Colour(0xff357abd));
    generateButton.setColour(juce::TextButton::textColourOffId, juce::Colours::white);
    generateButton.setColour(juce::TextButton::textColourOnId, juce::Colours::white);
    generateButton.onClick = [this] { generateButtonClicked(); };
    addAndMakeVisible(generateButton);
    
    // Set plugin size
    setSize (500, 400);
}

LayeredPluginAudioProcessorEditor::~LayeredPluginAudioProcessorEditor()
{
}

//==============================================================================
void LayeredPluginAudioProcessorEditor::paint (juce::Graphics& g)
{
    // Modern dark gradient background
    juce::ColourGradient gradient(juce::Colour(0xff1a1a1a), 0, 0,
                                  juce::Colour(0xff2d2d2d), 0, getHeight(), false);
    g.setGradientFill(gradient);
    g.fillAll();
    
    // Add subtle border
    g.setColour(juce::Colour(0xff444444));
    g.drawRect(getLocalBounds(), 1);
}

void LayeredPluginAudioProcessorEditor::resized()
{
    auto area = getLocalBounds();
    const int margin = 20;
    const int buttonHeight = 40;
    const int titleHeight = 50;
    
    area.reduce(margin, margin);
    
    // Title at the top
    titleLabel.setBounds(area.removeFromTop(titleHeight));
    area.removeFromTop(10); // spacing
    
    // Generate button at the bottom
    generateButton.setBounds(area.removeFromBottom(buttonHeight));
    area.removeFromBottom(10); // spacing
    
    // Text input fills the remaining space
    textInput.setBounds(area);
}

void LayeredPluginAudioProcessorEditor::generateButtonClicked()
{
    juce::String userInput = textInput.getText();
    
    if (userInput.isEmpty())
    {
        juce::AlertWindow::showMessageBoxAsync(
            juce::AlertWindow::InfoIcon,
            "Layered AI Copilot",
            "Please enter a description of what you'd like to create!",
            "OK"
        );
        return;
    }
    
    // For now, show a placeholder response
    juce::AlertWindow::showMessageBoxAsync(
        juce::AlertWindow::InfoIcon,
        "Layered AI Copilot",
        "Processing your request: \"" + userInput + "\"\n\n"
        "AI integration coming soon! This will connect to your music production AI service.",
        "OK"
    );
}
