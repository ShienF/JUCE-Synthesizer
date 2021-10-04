#include "SynthVoice.h"

#ifdef DEBUG
SynthVoice::SynthVoice() 
{
	file.open("C:\\Users\\Fan\\Desktop\\Coding\\JUCE\\Square\\Sawtooth_value.txt", std::ios::out | std::ios::trunc); //open file when construction
}

SynthVoice::~SynthVoice()
{
	file.close(); //open file when de-construction
}
#endif


bool SynthVoice::canPlaySound(juce::SynthesiserSound* sound)
{
	return dynamic_cast<SynthSound*>(sound) != nullptr;
}

void SynthVoice::startNote(int midiNoteNumber, float velocity, juce::SynthesiserSound* sound, int currentPitchWheelPosition)
{
	noteMidiNumber = midiNoteNumber;
	frequency = juce::MidiMessage::getMidiNoteInHertz(midiNoteNumber);
	currentAngle = 0.f;
	angleIncrement = frequency / getSampleRate() * juce::MathConstants<float>::twoPi; // 2Pi * f * 1/fs
	tailOff = 0.0;
	level = 1;
	isPlaying = true;
}

void SynthVoice::stopNote(float velocity, bool allowTailOff)
{
	if (allowTailOff)
	{
		if (tailOff == 0.0)
			tailOff = 1.0;
	}
	else
	{
		clearCurrentNote();
		level = 0;
		currentAngle = 0.f;
	}
}

void SynthVoice::pitchWheelMoved(int newPitchWheelValue)
{
	// handle pitch wheel moved midi event
}

void SynthVoice::controllerMoved(int controllerNumber, int newControllerValue)
{
	// handle midi control change
}

void SynthVoice::renderNextBlock(juce::AudioBuffer <float> &outputBuffer, int startSample, int numSamples)
{
	if (isPlaying)
	{
		if (tailOff > 0.0)
		{
			for (int i = startSample; i < (startSample + numSamples); i++) //numSamples = after how many times it will return 
			{	///*
				// Sawtooth
				if (currentAngle > juce::MathConstants<float>::twoPi)
				{
					currentAngle -= juce::MathConstants<float>::twoPi;
				}
				float value = (1 / juce::MathConstants<float>::pi * currentAngle - 1) * level * tailOff;
				outputBuffer.addSample(0, i, value);
				outputBuffer.addSample(1, i, value);
				//*/

				/*
				// Triangle
				if (currentAngle > juce::MathConstants<float>::twoPi)
				{
					currentAngle -= juce::MathConstants<float>::twoPi;
				}
				if(currentAngle < 1/2 * juce::MathConstants<float>::pi)
				{
					float value = 2 / juce::MathConstants<float>::pi * currentAngle * level * tailOff;
					outputBuffer.addSample(0, i, value);
					outputBuffer.addSample(1, i, value);
				}
				else if(1/2 * juce::MathConstants<float>::pi < currentAngle < 3/2 * juce::MathConstants<float>::pi){
					float value = (-2 / juce::MathConstants<float>::pi * currentAngle + 2) * level * tailOff;
					outputBuffer.addSample(0, i, value);
					outputBuffer.addSample(1, i, value);
				}
				else if (currentAngle > 3/2 * juce::MathConstants<float>::pi) {
					float value = (2 / juce::MathConstants<float>::pi * currentAngle - 4) * level * tailOff;
					outputBuffer.addSample(0, i, value);
					outputBuffer.addSample(1, i, value);
				}
				*/


				/*
				// Square
				if(std::sin(currentAngle) > 0){
					float value = 1 * level * tailOff;
					outputBuffer.addSample(0, i, value);
					outputBuffer.addSample(1, i, value);
				}
				else if(std::sin(currentAngle) < 0){
					float value = -1 * level * tailOff;
					//DBG("value: " << value);
					outputBuffer.addSample(0, i, value);
					outputBuffer.addSample(1, i, value);
				}
				*/


				/*
				// Sine Wave
				 float value = std::sin(currentAngle) * level * tailOff;
				 outputBuffer.addSample(0, i, value);
				 outputBuffer.addSample(1, i, value);
				*/

				currentAngle += angleIncrement;
				tailOff *= 0.99;


				if (tailOff <= 0.05)
				{
					clearCurrentNote();
					angleIncrement = 0.0;
					level = 0.0;
					isPlaying = false; //press button to start to fill buffer
					break;
				}
			}


		}
		else
		{
			for (int i = startSample; i < (startSample + numSamples); i++)
			{
				//*
				// Sawtooth
				if (currentAngle > juce::MathConstants<float>::twoPi)
				{
					currentAngle -= juce::MathConstants<float>::twoPi;
				}
				float value = (1 / juce::MathConstants<float>::pi * currentAngle - 1) * level;

				//DBG(value);
				outputBuffer.addSample(0, i, value);
				outputBuffer.addSample(1, i, value);
				//*/
				#ifdef DEBUG
				toText(std::to_string(value));
				#endif


				/*
				// Triangle
				if (currentAngle > juce::MathConstants<float>::twoPi)
				{
					currentAngle -= juce::MathConstants<float>::twoPi;
				}
				if (currentAngle < 1 / 2 * juce::MathConstants<float>::pi)
				{
					float value = 2 / juce::MathConstants<float>::pi * currentAngle * level;
					toText(value);
					outputBuffer.addSample(0, i, value);
					outputBuffer.addSample(1, i, value);
				}
				else if (1/2 * juce::MathConstants<float>::pi < currentAngle < 3/2 * juce::MathConstants<float>::pi) {
					float value = (-2 / juce::MathConstants<float>::pi * currentAngle + 2) * level;
					toText(value);
					outputBuffer.addSample(0, i, value);
					outputBuffer.addSample(1, i, value);
				}
				else if (currentAngle > 3/2 * juce::MathConstants<float>::pi) {
					float value = (2 / juce::MathConstants<float>::pi * currentAngle - 4) * level;
					toText(value);
					outputBuffer.addSample(0, i, value);
					outputBuffer.addSample(1, i, value);
				}
				*/


				/*
				// Square
				if (std::sin(currentAngle) > 0) {
					float value = 1 * level;
					toText(value);
					outputBuffer.addSample(0, i, value);
					outputBuffer.addSample(1, i, value);
				}
				else if (std::sin(currentAngle) < 0) {
					float value = -1 * level;
					toText(value);
					outputBuffer.addSample(0, i, value);
					outputBuffer.addSample(1, i, value);
				}
				*/


				/*
				// Sine Wave
				float value = std::sin(currentAngle) * level;
				outputBuffer.addSample(0, i, value);
				outputBuffer.addSample(1, i, value);
				*/

				currentAngle += angleIncrement;
			}
		}
	}
}

void SynthVoice::setLevel(float newLevel)
{
	level = newLevel;
}

#ifdef DEBUG
void SynthVoice::toText(std::string value)
{
	file << value << std::endl; //value -> file
}
#endif