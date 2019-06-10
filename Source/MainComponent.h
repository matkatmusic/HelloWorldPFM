/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/
template<typename ButtonType>
struct ButtonWrapper : public Button::Listener
{
    template<typename ... Args>
    ButtonWrapper( std::function<void()> onClickHandler,
                   Args&& ... args ) :
    onClick( std::move( onClickHandler ) ),
    button( std::forward<Args>(args) ... )
    {
        button.addListener(this);
    }
    ~ButtonWrapper() { button.removeListener(this); }
    void buttonClicked(Button* b) override
    {
        if( onClick )
            onClick();
    }
    
    //operator Component*() { return &button; }
    operator Component&() { return button; }
    Button* operator->() { return &button; }
private:
    std::function<void()> onClick;
    ButtonType button;
};

template<typename ButtonType>
struct HeapButtonWrapper : public Button::Listener
{
    HeapButtonWrapper(std::function<void()> onClickHandler,
                      std::unique_ptr<ButtonType> heapButton) :
    onClick( std::move( onClickHandler ) ),
    button( std::move(heapButton) )
    {
        setupButton();
    }
    
    HeapButtonWrapper(std::function<void()> onClickHandler,
                      ButtonType* rawButtonPtr) :
    HeapButtonWrapper(onClickHandler,
                      std::unique_ptr<ButtonType>(rawButtonPtr) )
    {
        
    }
    
    
    ~HeapButtonWrapper()
    {
        if( button.get() )
            button->removeListener(this);
    }
    void buttonClicked(Button* b) override
    {
        if( onClick )
            onClick();
    }
    
    operator Component*()
    {
        if( button.get() != nullptr )
            return button.get();
        return nullptr;
    }
    Button* operator->() { return button.get(); }
private:
    void setupButton()
    {
        jassert( button.get() != nullptr );
        if( button.get() )
            button->addListener(this);
    }
    std::function<void()> onClick;
    std::unique_ptr<ButtonType> button;
};


class MainComponent   : public Component
{
public:
    //==============================================================================
    MainComponent();
    ~MainComponent();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;

private:
    ButtonWrapper<TextButton> button {[]() { DBG( "you clicked the button" ); }, "textB" };
    std::unique_ptr<HeapButtonWrapper<TextButton>> heapButton;
    //==============================================================================
    // Your private member variables go here...


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
