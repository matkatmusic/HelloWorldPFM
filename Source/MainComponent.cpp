/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#include "MainComponent.h"

DualButton::DualButton()
{
    addAndMakeVisible(button1);
    addAndMakeVisible(button2);
    
    button1.onClick = [this]()
    {
        DBG( "Button1's size: " << this->button1.getBounds().toString() );
    };
    
    button2.onClick = [this]()
    {
        DBG( "Button2's size: " << this->button2.getBounds().toString() );
    };
}

void DualButton::resized()
{
    auto bounds = getLocalBounds();
    button1.setBounds(bounds.removeFromLeft(30) );
    button2.setBounds(bounds);
}
///==============================================================================

///==============================================================================
OwnedArrayComponent::OwnedArrayComponent()
{
    for( int i = 0; i < 10; ++i )
    {
        auto* widget = buttons.add( new TextButton(String(i)) );
        addAndMakeVisible(widget);
        widget->addListener(this);
    }
}
OwnedArrayComponent::~OwnedArrayComponent()
{
    for( auto* widget : buttons )
    {
        widget->removeListener(this);
    }
}
void OwnedArrayComponent::resized()
{
    auto width = getWidth() / static_cast<float>(buttons.size());
    int x = 0;
    auto h = getHeight();
    for( auto* widget : buttons )
    {
        widget->setBounds(x, 0, width, h);
        x += width;
    }
}

void OwnedArrayComponent::buttonClicked(Button *buttonThatWasClicked)
{
    if( buttonThatWasClicked == buttons.getFirst() )
    {
        DBG( "you clicked the first button" );
    }
    else if( buttonThatWasClicked == buttons.getLast() )
    {
        DBG( "you clicked the last button" );
    }
    else
    {
        DBG( "you clicked some other button" );
    }
}
//==============================================================================
MainComponent::MainComponent()
{
    addAndMakeVisible(comp);
//    comp.addMouseListener(this, false);
    
    addAndMakeVisible(ownedArrayComp);
    ownedArrayComp.addMouseListener(this, true);
    addAndMakeVisible(dualButton);
    
    addAndMakeVisible(repeatingThing);
    
    setSize (600, 400);
}

MainComponent::~MainComponent()
{
    comp.removeMouseListener(this);
}

//==============================================================================
void MainComponent::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));

    g.setFont (Font (16.0f));
    g.setColour (Colours::white);
    g.drawText ("Hello World!", getLocalBounds(), Justification::centred, true);
}

void MainComponent::resized()
{
    // This is called when the MainComponent is resized.
    // If you add any child components, this is where you should
    // update their positions.
    
    comp.setBounds(30, 30, 100, 100);
    ownedArrayComp.setBounds(comp.getX(),
                             comp.getBottom() + 5,
                             getWidth() - comp.getX(),
                             getHeight() - comp.getBottom());
    
    dualButton.setBounds(comp.getBounds()
                             .withX(comp.getRight()+5));
    
    repeatingThing.setBounds(dualButton.getBounds().withX(dualButton.getRight() + 5));
}
