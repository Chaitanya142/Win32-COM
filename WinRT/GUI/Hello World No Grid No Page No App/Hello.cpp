#include "pch.h"
#include "Hello.h"

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


void MyCallBackMethod(Windows::UI::Xaml::ApplicationInitializationCallbackParams^ params) {
	App^ app = ref new App();
}
int main(Array<String^>^ args) {
	ApplicationInitializationCallback^ callback = ref new ApplicationInitializationCallback(MyCallBackMethod);
	Application::Start(callback);
	return 0;
}

void App::OnLaunched(Windows::ApplicationModel::Activation::LaunchActivatedEventArgs^ args) {
	Page^ page = ref new Page();

	Grid^ grid = ref new Grid();
	grid->Background = ref new SolidColorBrush(Windows::UI::Colors::Black);

	TextBlock^ textBlock = ref new TextBlock();
	textBlock->Text = "Hello World!!!";
	textBlock->FontFamily = ref new Windows::UI::Xaml::Media::FontFamily("Seoge UI");
	textBlock->FontSize = 120;
	textBlock->FontStyle = Windows::UI::Text::FontStyle::Oblique;
	textBlock->FontWeight = Windows::UI::Text::FontWeights::Bold;
	textBlock->Foreground = ref new  SolidColorBrush(Windows::UI::Colors::Gold);
	textBlock->HorizontalAlignment = Windows::UI::Xaml::HorizontalAlignment::Center;
	textBlock->VerticalAlignment = Windows::UI::Xaml::VerticalAlignment::Center;

	grid->Children->Append(textBlock);

	page->Content = grid;

	Window::Current->Content = page;
	Window::Current->Activate();

}