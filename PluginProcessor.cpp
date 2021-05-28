/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
NoiseGateAudioProcessor::NoiseGateAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                     .withInput  ("Sidechain", juce::AudioChannelSet::stereo(), true)
                       )
#endif
{
    UserParams[gain]=0.0f; // implicit castigul este 0
    UserParams[release]=0.0f;
    UserParams[attack] = 0.0f;
    UserParams[holdtime] = 0.0f;
    UIUpdateFlag=true; // se cere update de la interfața grafică
}

NoiseGateAudioProcessor::~NoiseGateAudioProcessor()
{
}

//==============================================================================
const juce::String NoiseGateAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool NoiseGateAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool NoiseGateAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool NoiseGateAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double NoiseGateAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int NoiseGateAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int NoiseGateAudioProcessor::getCurrentProgram()
{
    return 0;
}

void NoiseGateAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String NoiseGateAudioProcessor::getProgramName (int index)
{
    return {};
}

void NoiseGateAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void NoiseGateAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
}

void NoiseGateAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool NoiseGateAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void NoiseGateAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    // This is the place where you'd normally do the guts of your plugin's
    // audio processing...
    // Make sure to reset the state if your inner loop is processing
    // the samples and the outer loop is handling the channels.
    // Alternatively, you can process the samples with the channels
    // interleaved by keeping the same state.
    
    double rel = round(release*getSampleRate()); //Fs
    double att = round(attack*getSampleRate());
    double ht = round(holdtime*getSampleRate());
    std::vector<double> h(buffer.getNumSamples());
    std::vector<double> y(buffer.getNumSamples());
    double a1= -2*a;
    double a2= a*a;
    double b= (1-a)*(1-a);
    
    
    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        std::vector<double>g(buffer.getNumSamples(),0);
        double lthcnt = 0;
        double uthcnt =0;
        double ymax = 0.001;
        double xmax = 0.001;
        double hmax = 0.001;
        double ltrhold = -70;
        double utrhold = 0;
        std::vector<double> w(2,0);
        
        
        auto* channelData = buffer.getWritePointer (channel);

        // ..do something to the data...
        
        for(int j=0; j<buffer.getNumSamples();j++)
        {
            double wn =abs(channelData[j]-a1*w[0]-a2*w[1]);
            h[j] = wn * b;
            w[1] = w[0];
            w[0] = wn;


            if (h[j] > hmax)
                hmax = h[j];
            if (abs(channelData[j]) > hmax)
                xmax = abs(channelData[j]);
        
        
        }

        for (int j = 0; j < buffer.getNumSamples(); j++)
        {
            if (((h[j] / hmax) <= ltrhold) || (((h[j] / hmax) < utrhold) && (lthcnt > 0)))
            {
                lthcnt++;
                uthcnt = 0;
                if (lthcnt > ht)
                {
                    if (lthcnt > (rel + ht))
                        g[j] = 0;
                    else
                        g[j] = 1 - (lthcnt - ht) / rel;
                }
                else if ((j + 1 < ht) && (lthcnt == j + 1))
                {
                    g[j] = 0;
                }
                else
                    g[j] = 1;


            }
            else if ((h[j] / hmax >= utrhold) || ((h[j] / hmax > ltrhold) && (uthcnt > 0)))
            {
                uthcnt++;
                if (g[j - 1] < 1)
                {
                    if (uthcnt / att > g[j - 1])
                        g[j] = uthcnt / att;
                    else
                        g[j] = g[j-1];
                   
                }
                else
                    g[j] = 1;
                lthcnt = 0;
            }
            else
            {
                g[j] = g[j - 1];
                lthcnt = 0;
                uthcnt = 0;
            }
            y[j] = channelData[j] * g[j];

            if (abs(y[j]) > ymax)
                ymax = abs(y[j]);
        }
        for (int j = 0; j < buffer.getNumSamples(); j++)
        {
            channelData[j] = y[j] * xmax / ymax;
        }
        
        
        for (int j = 0; j < buffer.getNumSamples(); j++)
        {
            channelData[j] = channelData[j] * powf(10.f, UserParams[gain] / 20.f);
        }
    }
    
    
    
    
    
   
        
}

//==============================================================================
bool NoiseGateAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* NoiseGateAudioProcessor::createEditor()
{
    return new NoiseGateAudioProcessorEditor (this);
}

//==============================================================================
void NoiseGateAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
    XmlElement root("Root");
    XmlElement* el;
    el = root.createNewChildElement("Gain");
    el->addTextElement(String(UserParams[gain]));

    el = root.createNewChildElement("Release");
    el->addTextElement(String(UserParams[release]));
    el = root.createNewChildElement("Attack");
    el->addTextElement(String(UserParams[attack]));
    el = root.createNewChildElement("Holdtime");
    el->addTextElement(String(UserParams[holdtime]));
    el = root.createNewChildElement("A");
    el->addTextElement(String(UserParams[a]));

    copyXmlToBinary(root, destData);
}

void NoiseGateAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
    static std::unique_ptr< XmlElement > pRoot = getXmlFromBinary(data, sizeInBytes);
    if (pRoot != NULL)
    {
        forEachXmlChildElement((*pRoot), pChild)
        {
            if (pChild->hasTagName("Gain"))
            {
                String text = pChild->getAllSubText();
                setParameter(gain, text.getFloatValue());
            }
            if (pChild->hasTagName("Release"))
            {
                String text = pChild->getAllSubText();
                setParameter(release, text.getFloatValue());
            }
            if (pChild->hasTagName("Attack"))
            {
                String text = pChild->getAllSubText();
                setParameter(attack, text.getFloatValue());
            }
            if (pChild->hasTagName("Holdtime"))
            {
                String text = pChild->getAllSubText();
                setParameter(holdtime, text.getFloatValue());
            }
            if (pChild->hasTagName("A"))
            {
                String text = pChild->getAllSubText();
                setParameter(a, text.getFloatValue());
            }
        }
        UIUpdateFlag = true; 
    }
}



//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new NoiseGateAudioProcessor();
}



int NoiseGateAudioProcessor::getNumParameters()
{
    return totalNumParam;
}

float NoiseGateAudioProcessor::getParameter (int index)
{
    switch(index)
    {
        case gain: // exemplu
            return UserParams[gain];
      case release:
           return UserParams[release];
     case attack:
          return UserParams[attack];
     case holdtime:
         return UserParams[holdtime];
     case a:
         return UserParams[a];
        default: return 0.0f; // index invalid
    }
}

void NoiseGateAudioProcessor::setParameter (int index, float newValue)
{
    switch(index)
    {
        case gain:
            UserParams[gain]=newValue;
            break;
       case release:
         UserParams[release]=newValue;
          break;
       case attack:
         UserParams[attack]=newValue;
       case holdtime:
           UserParams[holdtime] = newValue;
       case a:
           UserParams[a] = newValue;

         break;
        default: return;
      }
UIUpdateFlag=true;
}


const String NoiseGateAudioProcessor::getParameterName (int index)
{
    switch(index)
    {
        case gain: return "Gain";
         break;
        case release: return "Release";
         break;
        case attack: return "Attack";
            break;
        case holdtime: return "Holdtime";
            break;
        case a: return "A";
            break;
        default:return String();
    }
}


const String NoiseGateAudioProcessor::getParameterText (int index)
{
    if (index>=0 && index<totalNumParam)
        
            return String(UserParams[index]);
            
    else 
            return String();
}



