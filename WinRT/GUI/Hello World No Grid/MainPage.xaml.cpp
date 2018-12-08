//
// MainPage.xaml.cpp
// Implementation of the MainPage class.
//

#include "pch.h"
#include "MainPage.xaml.h"

using namespace HelloWorldWithoutGrid;

using namespace Platform;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Controls::Primitives;
using namespace Windows::UI::Xaml::Data;
using namespace Windows::UI::Xaml::Input;
using namespace Windows::UI::Xaml::Media;
using namespace Windows::UI::Text;
using namespace Windows::UI::Xaml::Navigation;

// The Blank Page item template is documented at https://go.microsoft.com/fwlink/?LinkId=402352&clcid=0x409

MainPage::MainPage()
{
	InitializeComponent();
	Grid^ grid = ref new Grid();
	grid->Background = ref new SolidColorBrush(Windows::UI::Colors::Black);
	TextBlock^ textblock =ref new TextBlock();
	textblock->Text = "Hello World!!!";
	textblock->FontFamily = ref new Windows::UI::Xaml::Media::FontFamily("Segeo UI");
	textblock->FontSize = 120;
	textblock->FontStyle = Windows::UI::Text::FontStyle::Oblique;
	textblock->FontWeight = Windows::UI::Text::FontWeights::Bold;
	textblock->Foreground = ref new SolidColorBrush(Windows::UI::Colors::Gold);
	textblock->HorizontalAlignment = Windows::UI::Xaml::HorizontalAlignment::Center;
	textblock->VerticalAlignment = Windows::UI::Xaml::VerticalAlignment::Center;

	grid->Children->Append(textblock);
	this->Content = grid;


}
