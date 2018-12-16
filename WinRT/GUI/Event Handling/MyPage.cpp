#include "pch.h"
#include "MyPage.h"

using namespace Windows::ApplicationModel;
using namespace Windows::ApplicationModel::Activation;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Controls::Primitives;
using namespace Windows::UI::Xaml::Data;
using namespace Windows::UI::Xaml::Input;
using namespace Windows::UI::Xaml::Interop;
using namespace Windows::UI::Xaml::Media;
using namespace Windows::UI::Xaml::Navigation;
using namespace Platform;
using namespace Windows::Foundation;

MyPage::MyPage() {
	Window::Current->CoreWindow->KeyDown += ref new TypedEventHandler<CoreWindow^, KeyEventArgs^>(this, &MyPage::OnKeyDown);

	Grid^ grid = ref new Grid();
	grid->Background = ref new SolidColorBrush(Windows::UI::Colors::Black);

	textBlock = ref new TextBlock();
	textBlock->Text = "Hello World!!!";
	textBlock->FontFamily = ref new Windows::UI::Xaml::Media::FontFamily("Seoge UI");
	textBlock->FontSize = 120;
	textBlock->FontStyle = Windows::UI::Text::FontStyle::Oblique;
	textBlock->FontWeight = Windows::UI::Text::FontWeights::Bold;
	textBlock->Foreground = ref new  SolidColorBrush(Windows::UI::Colors::Gold);
	textBlock->HorizontalAlignment = Windows::UI::Xaml::HorizontalAlignment::Center;
	textBlock->VerticalAlignment = Windows::UI::Xaml::VerticalAlignment::Center;

	grid->Children->Append(textBlock);

	Button^ button = ref new Button();
	button->Content = "Click Me";
	button->Width = 400;
	button->Height = 200;
	button->BorderThickness = 12;
	button->BorderBrush = ref new SolidColorBrush(Windows::UI::Colors::Gold);
	button->Foreground = ref new SolidColorBrush(Windows::UI::Colors::Red);
	button->FontFamily = ref new Windows::UI::Xaml::Media::FontFamily("Seoge UI");
	button->FontSize = 50;
	button->FontWeight = Windows::UI::Text::FontWeights::Bold;
	button->FontStyle = Windows::UI::Text::FontStyle::Oblique;
	button->HorizontalAlignment= Windows::UI::Xaml::HorizontalAlignment::Center;
	button->VerticalAlignment= Windows::UI::Xaml::VerticalAlignment::Bottom;
	button->Click += ref new RoutedEventHandler(this,&MyPage::OnButtonClick);

	grid->Children->Append(button);

	this->Content = grid;
}

void MyPage::OnKeyDown(CoreWindow^ sender, KeyEventArgs^ args) {
	textBlock->Text = "Key Pressed";
}

void MyPage::OnButtonClick(Object^ sender, RoutedEventArgs^ args) {
	textBlock->Text = "Mouse is clicked";

}