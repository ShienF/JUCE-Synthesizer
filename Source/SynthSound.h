#pragma once

class SynthSound : public juce::SynthesiserSound
{

public:
	bool appliesToNote(int midiNoteNumber) override
	{
		return true;
	}

	bool appliesToChannel(int midiNoteNumber) override
	{
		return true;
	}
};