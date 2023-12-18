/*
  ==============================================================================

    CustomSlider.h
    Created: 7 Nov 2023 2:56:42am
    Author:  Navaneeth Suresh Kumar

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class CustomSlider : public juce::LookAndFeel_V4
{
public:
    CustomSlider()
    {
        setColour(juce::Slider::thumbColourId, juce::Colours::white);
    }


    void drawRotarySlider(juce::Graphics& g, int x, int y, int width, int height, float sliderPos,
        const float rotaryStartAngle, const float rotaryEndAngle, juce::Slider&) override
    {
        auto radius = (float)juce::jmin(width / 2, height / 2) - 4.0f;
        auto centreX = (float)x + (float)width * 0.5f;
        auto centreY = (float)y + (float)height * 0.5f;
        auto rx = centreX - radius;
        auto ry = centreY - radius;
        auto rw = radius * 2.0f;
        auto angle = rotaryStartAngle + sliderPos * (rotaryEndAngle - rotaryStartAngle);

        // fill
        g.setColour(juce::Colour::fromRGB(56, 35, 18));
        g.fillEllipse(rx, ry, rw, rw);

        // outline
        g.setColour(juce::Colour::fromRGB(8,5,2));
        g.drawEllipse(rx, ry, rw, rw, 5.0f);

        juce::Path p;
        auto pointerLength = radius * 0.85f;
        auto pointerThickness = 4.0f;
        p.addRectangle(-pointerThickness * 0.5f, -radius, pointerThickness, pointerLength);
        p.applyTransform(juce::AffineTransform::rotation(angle).translated(centreX, centreY));

        // pointer
        g.setColour(juce::Colour::fromRGB(128, 10, 4));
        g.fillPath(p);
    }

private:

};
