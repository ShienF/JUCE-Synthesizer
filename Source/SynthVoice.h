#pragma once
#include <JuceHeader.h>
#include "SynthSound.h"
#include <string>
#include <fstream> //read and write library
#define DEBUG 1 // for DEBUG, if 0 don't compile

class SynthVoice : public juce::SynthesiserVoice
{
public:
	#ifdef DEBUG
	SynthVoice();
	
	~SynthVoice();
	#endif 

	bool canPlaySound(juce::SynthesiserSound* sound) override;

	void startNote(int midiNoteNumber, float velocity, juce::SynthesiserSound* sound, int currentPitchWheelPosition) override;

	void stopNote(float velocity, bool allowTailOff) override;

	void pitchWheelMoved(int newPitchWheelValue) override;

	void controllerMoved(int controllerNumber, int newControllerValue) override;

	void renderNextBlock(juce::AudioBuffer <float> &outputBuffer, int startSample, int numSamples) override;

	void setLevel(float newLevel);

	#ifdef DEBUG // DEBUG
	void toText(std::string value); // to text file
	#endif 

	
private:
	float level;
	float frequency;
	int noteMidiNumber;
	float currentAngle;
	float angleIncrement;
	float tailOff;
	bool isPlaying = false;
	#ifdef DEBUG
	std::fstream file; //create a file
	#endif
};